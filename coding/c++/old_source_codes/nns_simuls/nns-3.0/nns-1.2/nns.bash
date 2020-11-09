#!/bin/bash
# nns.bash
#
# is a utility program to automate simulations with different simulation parameters.
# The purpose is to save the labor of baby-sitting the entire process of simulations.
#
# Version: 1.1
#   Last updated:  Mar. 10, 2011 (Thu)
#   First written: Feb, 2008
#
# A suggested way to use nns.bash is to consider nns.bash as the main interface to control the
# simulations. The commands to run nns.bash is suggested to be stored in a bash script file and
# save it to directory bash_scripts. For example, create a bash script run_a_simulation.
#
#   -----------------------------------------
#   #!/bin/bash
#   # run_a_simulation
#   nns.bash -h
#   -----------------------------------------
#
# and then run the script.
#
#   $ ./run_a_simulation
#
# In this manner, the structure of nns.bash remains the same while the simulation parameters can be stored.
#
# Directory structure
#   \ - bash_scripts      All bash scripts except install and nns.bash are stored here.
#     |
#     - bin               executables are stored
#     |
#     - config_files      config files
#     |
#     - outputs           postprocessed results are collected here for convenience
#     |
#     - results	          simulation and postprocessed results are stored
#     |
#     - source_codes      c++ source codes
#
# Type `./nns.bash -h` to see the usage.
#
# Written by Tae-Hyung "T" Kim, mrtonnet [at] gmail [dot] com

##################################################################################
#   			Options and Configuration				 #
##################################################################################

#####################################
# Default options and configuration #
#####################################
# PLEASE DO NOT CHANGE THIS!
VERSION="1.2";
VER_RELEASED="Mar. 19, 2011 (Sat)";
OPT_OPTION=0;
OPT_SILENTMODE=0;
OPT_MAKE=0;
OPT_MAKECLEAN=0;
OPT_DUMMYCOMMAND=0;
OPT_POSTPROCESS=0;
OPT_EMAIL=0;

#####################################
#               Time                #
#####################################
TIME_START=`date +"%X, %F";`;
TODAY=`date +"%F";`;
# PLEASE DO NOT CHANGE THIS!

#####################################
#  Strings to send an email notice  #
#####################################

# CHANGE THIS PART AT YOUR OWN RISK TO CUSTOMIZE THIS PROGRAM.
EMAIL_RECIPIENTS="user_name@gmail.com";  # The email recipient should be hardcoded here.
# CHANGE THIS PART AT YOUR OWN RISK TO CUSTOMIZE THIS PROGRAM.

################################################################################
#                                Procedures                                    #
################################################################################
# This is part is solely for option -o
showShortUsage() {
echo "Usage: nns.bash [config_file] [options]
  This script should ALWAYS be run in the project directory.
Shell options:
  -o   options
Examples:
  ./nns.bash -o 0
Values before/after the options are set:
  -o   OPT_OPTION=-1;   OPT_OPTION=n; n is an integer taken from the input argument.
Type \`nns.bash -h\` for more help.";
}

# This is part is solely for option -h
showUsage() {
echo "  nns.bash is a wrapper around the main program nns-${VERSION}.exe or nns-${VERSION}-dbg.exe
which are written in C++. These programs performs a single simulation by reading a config file.
The role of this script is to manage a multiple number of simulations with different design parameters.

The default configuration file default.cfg is located in directory config_files.
There are two different options to run nns.bash.
(1) A single run of nns-${VERSION}.exe
    This is identical to run nns-${VERSION}.exe on a terminal.

  (input)     |-----------|    (trace)
Config file-->|nns-${VERSION}.exe|-->trace files
              |-----------|

  There are several different ways to run a single simulation. A few examples are below.

    $ nns.bash
    $ nns.bash your_config_file
    $ nns.bash -o 0
    $ nns.bash -o 1

  where your_config_file is a configuration file, e.g. mytest.cfg.
  Note option 0 is dedicated to a single run.
  Note -d -e and -s can be added if neccessary.

(2) A multiple runs of nns-${VERSION}.exe
    This is the true purpose of using nns.bash. When you want to change a multiple runs of
    nns-${VERSION}.exe by tweaking the design parameters, use the -i option.

  (input)     |-----------|    (trace)      |--------------|   (output)
Config file-->|nns-${VERSION}.exe|-->trace files-->|nns_postproces|-->a single output file
              |-----------|                 |--------------|

  There are several different ways to run multiple simulations. A few examples are below.

    $ nns.bash -o 2
    $ nns.bash your_config_file -o 2

  where your_config_file is a configuration file, e.g. mytest.cfg.
  In an example 'nns.bash -o 1', it is assumed option 1 is customized for multiple simulations.
  Note -d -e and -s can be added if neccessary.

Usage: nns.bash [config_file] [options]
  Shell options:
    -h   help. Type \`nns.bash -h\` for help.
    -c   make clean
    -d   display dummy command only. This option does not run simulations, but just show
         the (dummy) commands. One can check what commands will be run without actually
         running the program. Be careful not to use this option to run actual simulations.
    -e   email when the job is done.
         Command 'mail' should be properly configured in advance to use this feature.
         Talk to your system administrator to configure 'mail'. EMAIL_RECIPIENTS is hardcoded.
         Change variable EMAIL_RECIPIENTS in this file if neccessary.
    -m   make
    -o   options
    -p   postprocess the trace files in the target output directory.
         Use this option only for multiple simulation runs.
    -s   silent mode
         -d wins -s because the silent mode is used when commands are run.
         When both options are turned on, the dummy commands will be displayed.
    -v   version information

Examples:
   To compile or make nns-${VERSION}.exe
      $ nns.bash -m
   To remove or make clean nns-${VERSION}.exe
      $ nns.bash -c
   To run nns-${VERSION}.exe,
      $ nns.bash
Values before/after the options are set:
   -c       OPT_MAKECLEAN=0;       OPT_MAKECLEAN=1;
   -d       OPT_DUMMYCOMMAND=0;    OPT_DUMMYCOMMAND=1;
   -e       OPT_EMAIL=0;           OPT_EMAIL=1;
   -o       OPT_OPTION=-1;         OPT_OPTION=n; n is an integer taken from the input argument.
   -m       OPT_MAKE=0;            OPT_MAKE=1;
   -p       OPT_POSTPROCESS=0;     OPT_POSTPROCESS=1;
   -s       OPT_SILENTMODE=0;      OPT_SILENTMODE=1;

Bug report: Please report bugs at mrtonnet [at] gmail [dot] com.";
}

# This is part is solely for option -v
show_version_info() {
   echo "  nns version ${VERSION}, ${VER_RELEASED}. ";
}

evaluate () {
# Usage: 'evaluate OPT_DONTRUN COMMAND2RUN'
#   When OPT_DONTRUN is 0, a string COMMAND2RUN will be evaluated.
#   Otherwise, only the dummy command will be displayed.
#   Note the string COMMAND2RUN should include a valid command.
# Examples:
#   evaluate 0 "cd ${DIR_ROOT}/${DIR_BIN}";
#   evaluate 1 "cd ${DIR_ROOT}/${DIR_BIN}";
#
#   The first example will actually cd to the specified directory after displaying
# the command "cd ${DIR_ROOT}/${DIR_BIN}" on the standard output.
#   The second example won't cd to the directory. Only the command will be displayed.
#
# It is suggested to use this procedure whenever a command should be run.
# The command will take care of the issue with the -d option.
# If -d is on, only a string COMMAND2RUN will be displayed and the command
# won't actually be executed.

  local OPT_DONTRUN=$1;
  local COMMAND2RUN=$2;

  echo "  ${COMMAND2RUN}";
  if [ ${OPT_DONTRUN} -eq 0 ];then
    eval ${COMMAND2RUN};
  fi
}

safe_mkdir () {
# Make directory if the directory does not exist.
# Usage example
#
#   safe_mkdir ${DIR_OUTPUT}/${TODAY} ${OPT_SILENTMODE}

  DIR_TARGET=$1;
  IS_SILENTMODE=$2;

  if test ! -d ${DIR_TARGET}; then
    COMMAND2RUN="mkdir ${DIR_TARGET}";
    if [ ${IS_SILENTMODE} -eq 0 ]; then
      echo "  ${COMMAND2RUN}";
    fi
    eval ${COMMAND2RUN};
#    mkdir ${DIR_TARGET};
  fi
  # Reset the internal variables just in case the name conflicts below.
  DIR_TARGET="";
  IS_SILENTMODE="";
}

mksubdir ()
{
# Create a sub-directory in the target directory. An alternative proc name could be safe_mksubdir.
# If the target directory exists, the directory name is conveniently changed by incrementing an suffix.
#
# A suggested way to use this procedure is to name the target directory as today's date.
# Say the sub-directory name under directory outputs is '2009-08-05' or
#
#   ${DIR_ROOT}/${DIR_OUTPUTS}/2009-08-05
#
# , the suggested way is to set the absolute path to the target directory name.
# (Of course, one can set the relative path as the target directory as well.)
#
# In directory outputs, the sub-directory '2009-08-05' is attempted to be made.
# If it exists, a suffix is added. For example, '2009-08-05-0'.
# If '2009-08-05-0' exists, the suffix is incremented to '2009-08-05-1'.
# The suffix is incremented until the procedure finds a name that doesn't conflict with others.
#
# Usage example
#
#   mksubdir ${DIR_OUTPUT}/${TODAY} ${OPT_SILENTMODE}
#
#
  DIR_TARGET=$1;
  IS_SILENTMODE=$2;

  # If the directory does not exist, create one.
  if test ! -d ${DIR_TARGET}; then
    if [ ${IS_SILENTMODE} -eq 0 ]; then
      COMMAND2RUN="mkdir ${DIR_TARGET}";
      echo "  ${COMMAND2RUN}";
    fi
    eval ${COMMAND2RUN};
#    mkdir ${DIR_TARGET};
  else
    echo "Directory ${DIR_TARGET} exists. Proceed anyway? (y/n)";
    read;
    if [ ${REPLY} == "y" -o  ${REPLY} == "Y" ];then
      if [ ${IS_SILENTMODE} -eq 0 ]; then
        # Add a suffix at the end of the directory name.
        # Increase the counter while a directory pre-exists.
        count=0;
        DIR_TMP="${DIR_TARGET}";
        while test -d ${DIR_TMP}; do
        DIR_TMP="${DIR_TARGET}-${count}";
          let count=count+1;
        done
        DIR_TARGET="${DIR_TMP}";
        mkdir ${DIR_TARGET};
        echo "  mkdir ${DIR_TARGET};";
        # Reset the internal variables just in case the name conflicts below.
        count="";
        DIR_TMP="";
      fi
    elif [ ${REPLY} == "n" -o  ${REPLY} == "N" ];then
      echo "Exiting...";
      exit 1;
      else
      echo "Wrong input. Type in either y or n. Exiting...";
      exit 1;
    fi
  fi
  # Reset the internal variables just in case the name conflicts below.
  DIR_TARGET="";
  IS_SILENTMODE="";
}

# This procedure was designed to be used for postprocessing.
# I'm not sure if I'll use this for the version-up, but leave it as it is
# just in case I need it.

aggregate_sample_result () {

# Aggregate samples of all results in a single file.
# The purpose is to conveniently check the output results.
# Show the first and the last three lines of all results.

  # Extract the total number of outputs.
  TARGET=$1;        # e.g. 6-1-1, same as the directory name.
  DIR_RESULTS=$2;   # e.g. 2009-08-04
  FILE_RESULTS=$3;  # e.g. 2009-08-04.trc
  FILE="${DIR_RESULTS}/${FILE_RESULTS}";
  # e.g. 4 for 2x2 board size.
  index_max=`cat ${TARGET}.log|grep "index_max="|awk '{split($3,a,"=");print a[2];}'`;
  # e.g. csrn
  nn_architecture=`cat ${TARGET}.cfg | grep "simul_architecture" | awk '{ print $3; }'`;

  echo "-------------------------------------------" >> ${FILE};
  echo "${TARGET}" >> ${FILE};
  FILE_NAME="${nn_architecture}.out";
  echo "${FILE_NAME}" >> ${FILE};
  head -n 3 ${FILE_NAME} >> ${FILE};
  tail -n 3 ${FILE_NAME} >> ${FILE};
  echo "-------------------------------------------" >> ${FILE};
  echo "" >> ${FILE}

  index=0;
  while [ ${index} -lt ${index_max} ];do
    FILE_NAME="cell${index}.out";
    echo "${FILE_NAME}" >> ${FILE};
    head -n 3 ${FILE_NAME} >> ${FILE};
    tail -n 3 ${FILE_NAME} >> ${FILE};
    echo "" >> ${FILE};
    let index=index+1;
  done
}

change_template_next_line ()
{
   # Usage: change_template_next_line file_name string_to_match new_value
   #    Given the template file, new_value is overwritten if string_to_match
   #    matches the line.

   # If the string matches the next line is changed.
   local file2change=$1;
   local string2match=$2;
   local new_value=$3;
   local file_tmp="${file2change}.tmp";

   cat $file2change | awk ' BEGIN {
      # Comand line input to awk
      file_awk_output=ARGV[1]; delete ARGV[1];
      expr2match=ARGV[2]; delete ARGV[2];
      value2change=ARGV[3]; delete ARGV[3];
      flag_found=0;
   } {
         if ( $1 == expr2match && flag_found==0 )
	 {
	    print > file_awk_output;
            flag_found=1;
	 } else if ( flag_found==1 )
	 {
	    printf("\t\t( %d, {\n",value2change) > file_awk_output;
            flag_found=0;
	 } else
	 {
	    print > file_awk_output;
	 }
   } END {
      close(file_awk_output);                       # Explicitly close the opened file.
   }' $file_tmp $string2match $new_value;
   mv ${file_tmp} ${file2change};
}

# change_template_int, change_template_float, and change_template_string are
# identical except only one line. The different lines for each of the above
# functions are shown below.
#
#     printf("%s = %d\n",expr2match, value2change)> file_awk_output;
#     printf("%s = %2.1f\n",expr2match, value2change)> file_awk_output;
#     printf("%s = %s\n",expr2match, value2change)> file_awk_output;
#
# As can be seen, the difference is the data type of to print value2change.
# The first line outputs an integer; the second a floating point; the last a string.

change_template_int () {
   # Usage: change_template_int file_name string_to_match new_value
   #    Given the template file, new_value is overwritten if string_to_match
   #    matches the line.

   # Note that matching line and the line that changes the value are identical.
   local file2change=$1;
   local string2match=$2;
   local new_value=$3;
   local file_tmp=${file2change}'.tmp';

   cat $file2change | awk ' BEGIN {
      # Comand line input to awk
      file_awk_output=ARGV[1]; delete ARGV[1];
      expr2match=ARGV[2]; delete ARGV[2];
      value2change=ARGV[3]; delete ARGV[3];
   } {
         if ( $1 == expr2match )
	 {
	    printf("%s = %d\n",expr2match, value2change)> file_awk_output;
	 } else
	 {
	    print> file_awk_output;
	 }
   } END {
      close(file_awk_output);                       # Explicitly close the opened file.
   }' $file_tmp $string2match $new_value;
   mv ${file_tmp} ${file2change};
}

change_template_float () {
   # Usage: change_template_float file_name string_to_match new_value
   #    Given the template file, new_value is overwritten if string_to_match
   #    matches the line.

   # Note that matching line and the line that changes the value are identical.
   local file2change=$1;
   local string2match=$2;
   local new_value=$3;
   local file_tmp=${file2change}'.tmp';

   cat $file2change | awk ' BEGIN {
      # Comand line input to awk
      file_awk_output=ARGV[1]; delete ARGV[1];
      expr2match=ARGV[2]; delete ARGV[2];
      value2change=ARGV[3]; delete ARGV[3];
   } {
         if ( $1 == expr2match )
	 {
	    printf("%s = %2.1f\n",expr2match, value2change)> file_awk_output;
	 } else
	 {
	    print> file_awk_output;
	 }
   } END {
      close(file_awk_output);                       # Explicitly close the opened file.
   }' $file_tmp $string2match $new_value;
   mv ${file_tmp} ${file2change};
}

change_template_string () {
   # Usage: change_template_string file_name string_to_match new_value
   #    Given the template file, new_value is overwritten if string_to_match
   #    matches the line.

   # Note that matching line and the line that changes the value are identical.
   local file2change=$1;
   local string2match=$2;
   local new_value=$3;
   local file_tmp=${file2change}'.tmp';

   cat $file2change | awk ' BEGIN {
      # Comand line input to awk
      file_awk_output=ARGV[1]; delete ARGV[1];
      expr2match=ARGV[2]; delete ARGV[2];
      value2change=ARGV[3]; delete ARGV[3];
   } {
         if ( $1 == expr2match )
	 {
	    printf("%s = %s\n",expr2match, value2change)> file_awk_output;
	 } else
	 {
	    print> file_awk_output;
	 }
   } END {
      close(file_awk_output);                       # Explicitly close the opened file.
   }' $file_tmp $string2match $new_value;
   mv ${file_tmp} ${file2change};
}

################################################################################
#   Directory, files, and options changed from the command-line options        #
################################################################################
# This part is central to automate the simulations.
# Given the command line options, appropriate changes are made in this part.
# If you want to change options and configuration, please do so in this part,
# NOT in the default options and configuration part.

################################################################################
#                          Command line arguments                              #
################################################################################
MIN_NUM_OF_ARGS=0;
if [ $# -lt ${MIN_NUM_OF_ARGS} ];then
   showUsage;
   exit 1;
fi

################################################################################
#                           Command line options                               #
################################################################################
COMMAND_LINE_OPTS=":hcdgemo:psv";

while getopts ${COMMAND_LINE_OPTS} Option; do
   case ${Option} in
      h ) showUsage; exit 1; ;;
      c ) OPT_MAKECLEAN=1; ;;
      d ) OPT_DUMMYCOMMAND=1; ;;
      e ) OPT_EMAIL=1;
          echo -e "\033[36mWhen the job's done, an email will be sent to ${EMAIL_RECIPIENTS}.\033[0m";
          ;;
      m ) OPT_MAKE=1; ;;
      o ) OPT_OPTION=${OPTARG}; ;;
      p ) OPT_POSTPROCESS=1; ;;

      s ) OPT_SILENTMODE=1; ;;
      v ) show_version_info; exit 1; ;;
      * ) echo "Unknown command line option."; # -${Option}.";
      	  echo "Type \`nns.bash -h\` for help.";
      	  exit 1;
      	  ;;
   esac
done
shift $((${OPTIND} -1))

#####################################
#        Directory Structure        #
#####################################
# Assume this script is located in the project directory.
DIR_ROOT=~+;  # Same as `pwd`
DIR_BIN="bin";
DIR_CONFIGFILES="config_files";
DIR_OUTPUTS="outputs";
DIR_RESULTS="results";
DIR_SCRIPTS="bash_scripts";0
DIR_TEMPLATE=${DIR_CONFIG_FILES};
DIR_SRC="source_codes";
DIR_BUILD="build";
DIR_BUILD_DBG="build_dbg";

DIR_MODULE=${DIR_ROOT}/${DIR_SCRIPTS};

# Set the path for the executables.
export PATH="${PATH}:${DIR_ROOT}"
export PATH="${PATH}:${DIR_ROOT}/${DIR_BIN}"

# If the directory does not exist, create one.
safe_mkdir ${DIR_RESULTS} ${OPT_SILENTMODE};
safe_mkdir ${DIR_OUTPUTS} ${OPT_SILENTMODE};

#####################################
#              Files                #
#####################################
CMD4NNS="nns-${VERSION}.exe";
CMD2POSTPROC="postproc_nns";
FILE_CONFIG="default.cfg";

################################################################################
#                             The Main Part                                    #
################################################################################
# This is part is solely for option -c and -m.
# Note most of the remaining part will be bypassed for option -c and -m.

if [ ${OPT_MAKE} -eq 1 ];then
  make -C "${DIR_ROOT}/${DIR_SRC}/${DIR_BUILD}";
  make -C "${DIR_ROOT}/${DIR_SRC}/${DIR_BUILD_DBG}";
  exit 0;
fi

if [ ${OPT_MAKECLEAN} -eq 1 ];then
  make -C "${DIR_ROOT}/${DIR_SRC}/${DIR_BUILD}" clean;
  make -C "${DIR_ROOT}/${DIR_SRC}/${DIR_BUILD_DBG}" clean;
  exit 0;
fi

##################################################################################
#   				Run Simulations				 	 #
##################################################################################
# There are two main parts:
#   a single simulation run (OPT_RUN_NNS=0) and
#   multiple simulation runs (OPT_RUN_NNS=1).
#
# * A single simulation run
#   There are only two commands associated with it.
#   First, cd to directory bin and then run the program nns-${VERSION}.exe.
#   In other words, it's equivalent to run the following commands.
#
#     $ cd my_root_dir/bin
#     $ nns-1.2.exe default.cfg
#
#   Here directory my_root_dir is assumed to be the program's root directory and
#   default.cfg is used for the configuration file even if any configuration file
#   can be used for nns-1.2.exe. The version number is also assumed to be 1.2.
#
# * Multiple simulation runs
#   This part should be implemented in a separate file which is imported in this file.
#
#
#
#   This part is more complicated than the single simulation run.
#   One can customize this part in order to run simulations with different
#   design parameters. A suggested way to code this part is as follows.
#
#   1. Set up a simulation run.
#      1.1. Create a directory to store relevant files.
#      1.2. Create a configuration file from a template configuration file.
#           This configuration file will be used by nns-${VERSION}.exe.
#         1.2.1. Copy the template configuration file.
#         1.2.2. Modify the template file to customize for this simulation run.
#                In other words, replace a parameter in the template file to
#                the desired value or string.
#   2. Run a simulation.
#      In essence, the command is
#
#        $ cd my_root_dir/bin
#        $ nns-1.2.exe new_config_file
#
#      where new_config_file is the configuration file obtained from the
#      template configuration file.
#
#   3. Set up the next loop (if neccessary)
#      Change the design parameter for the next step and return to step 1.
#      Otherwise, escape the loop and finish simulations.

if [ ${OPT_SILENTMODE} -eq 0 ]; then
  echo -e "\033[36mStart of the simulations: ${TIME_START}\033[0m";
fi

#####################################
#              Options              #
#####################################
# One can specify the option number in the input argument with option -i and
# modify nns.bash in order to associate a group of options.

if [ ${OPT_OPTION} -eq 0 ]; then
  DIR_THISRUN="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";
  evaluate ${OPT_DUMMYCOMMAND} "mksubdir ${DIR_THISRUN} ${OPT_SILENTMODE}";

  evaluate ${OPT_DUMMYCOMMAND} "cd ${DIR_ROOT}/${DIR_BIN}";
  evaluate ${OPT_DUMMYCOMMAND} "./${CMD4NNS} ${FILE_CONFIG} ${DIR_THISRUN}";
elif [ ${OPT_OPTION} -eq 1 ]; then
  # This option is identical to option 0 except this option shows an example
  # how to source an external file.
  source ${DIR_MODULE}/modules4nns-single_run.bash;
else
  # CHANGE THIS PART AT YOUR OWN RISK TO CUSTOMIZE THIS PROGRAM.
  source ${DIR_MODULE}/modules4nns-multiple_runs.bash;
  # CHANGE THIS PART AT YOUR OWN RISK TO CUSTOMIZE THIS PROGRAM.
fi

if [ ${OPT_SILENTMODE} -eq 0 ]; then
  # I think it's better to display the end of the simulation even for the dummy command mode.
  TIME_FINISH=`date +"%X, %F";`;
  echo -e "\033[36mEnd of the simulations: ${TIME_FINISH}\033[0m";
fi

##################################################################################
#         Postprocesses the trace files in the target output directory           #
##################################################################################

if [ ${OPT_POSTPROCESS} -eq 1 ]; then
  echo "OPT_POSTPROCESS Not implemented yet";
  # CMD2POSTPROC
fi

################################################################################
#                     mail the status report to the user                       #
################################################################################
# Send an email to notify the end of simulation with command "mail"
# The following terminal command sends an email with title "hello, T" and body
# "This is the mail body." to a mail recipient "mrtonnet@gmail.com".
# Test this command in the linux machine to see if the machine is configured to
# send an email. Hit enter after typing in the command
#
#   $ echo "This is the mail body." | mail -s "hello, T" mrtonnet@gmail.com
#   $
#

if [ ${OPT_EMAIL} -eq 1 ];then
  MAIL_TITLE="nns.bash. Job done.";
  MAIL_MESSAGE="TIME_START=${TIME_START}. TIME_FINISH=${TIME_FINISH}.";

  if [ ${OPT_SILENTMODE} -eq 0 ]; then
    echo -e "\033[36mSending an email notice to ${EMAIL_RECIPIENTS}...\033[0m";
  fi
  echo ${MAIL_MESSAGE} | mail -s "${MAIL_TITLE}" ${EMAIL_RECIPIENTS};
fi

################################################################################
exit 0;
#EOF

################################################################################
#             I keep these lines just in case I need them later                #
################################################################################
#       m ) OPT_OPTION=1;
#          STRING=$OPTARG;
#       	  SUB_STRING_1=${STRING%:*};
#       	  SUB_STRING_2=${STRING#*:};
#
#	        OPT_OPTION_1=${SUB_STRING_1%:*};
#	        OPT_OPTION_2=${SUB_STRING_1#*:};
#	        OPT_OPTION_3=${SUB_STRING_2#*:};
#
#    -m   mode of simulation.
#         Specify the options to run simulations delimited by colon \":\", i.e.
#         \"input_type:run_type:option\".
#	       For example, sv:sr:na or mv:mr:na.
#	       sv (Single-valued input) vs. mi (Multi-valued input)
#	       sr (Single run)          vs. mr (Multiple runs)
#	       na (Not available)
#    -u   Configure the number of mobile users per sector to simulate.
#        The format is \"from:increment:to\" delimited by colon \":\".
#	For example, "-u 24:4:52" are internally mapped to:
#           CFG_USER_PER_SECTOR_FROM=24; CFG_USER_PER_SECTOR_INCR=4; CFG_USER_PER_SECTOR_TO=52;
# [-u CFG_USER_PER_SECTOR_FROM:CFG_USER_PER_SECTOR_INCR:CFG_USER_PER_SECTOR_TO]
# [-t OPT_TRAFFIC_TYPE]
