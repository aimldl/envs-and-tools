#!/bin/bash
# module4postproc_nns-old_code.bash
#
#   Last updated:  Mar. 8, 2011 (Tue)
#   First written: Feb, 2008
#
#   This file includes lines for multiple simulation runs. Basically,
# The old "nns.bash" is split into two files: "nns.bash" and source files.
# A source file is used to keep the new "nns.bash" unchanged while
# the changes need to be made in a source file. To include this file in
# "nns.bash", add the following line
#
#   source module4nns_postproc-old_code.bash
#
# Guidelines

if [ ${OPT_OPTION} -eq 2 ]; then
  echo "Option 2 isn't implemented yet. Only the old codes are stored. Even though you see an error message, don't worry about it.";
done

# I'm saving this file as a part of postproc_nns.
# This is the old code. 

# Process the command-line arguments
if [ $# -eq 0 ];then
  # This is when nns.exe is run with the default options.
  # default.trc is stored in ../outputs.
  # Keep this because this is a convenient way to check the code change.
  FILE_OUTPUT=${DIR_OUTPUTS}/${FILE_OUTPUT_DEFAULT};
elif [ $# -eq 1 ];then
  # This is when the output file is specified in the command line.
  # The default directory is the the current directory or "." so that
  # "$ nns_postproc this.out" will do, not "$ nns_postproc ./this.out".
  # However, the directory can also be able to specified such as 
  # "$ nns_postproc outputs/8-5-2009/16-2-5/this.out".

  # Extract a substring after the last /. 
  # This conveniently returns the string itself if no / exists.
  # e.g. STRING="test/this.out";
  #      DIR_OUTPUTS="test";
  #      FILE_OUTPUT="this.out";
  DIR_OUTPUTS=`dirname $1`;
  FILE_OUTPUT=`basename $1`;
################################################################################

echo "  DIR_OUTPUTS=${DIR_OUTPUTS}";
echo "  FILE_OUTPUT=${FILE_OUTPUT}";

else
   showUsage;
   exit 1;
fi

################################################################################
#     Procedures: procs used when the command line arguments are processed.    #
################################################################################
# process_output()
#   processes the nns output file, e.g. default.trc.
#   In essence, process_output() is the core part of nns_postproc and
#   that of this procedure is to perform the following line iteratively.
#
#     "cat output_file | grep "string" > string.out;"
#
#   For example,   
#     cat ${FILE_OUTPUT} | grep "Cmlp" > cmlp.out;
#     cat ${FILE_OUTPUT} | grep "Cell.*0.*(" > cell0.out;
#     cat ${FILE_OUTPUT} | grep "Cell.*1.*(" > cell1.out;
#     cat ${FILE_OUTPUT} | grep "Cell.*2.*(" > cell2.out;
#     cat ${FILE_OUTPUT} | grep "Cell.*3.*(" > cell3.out;
#
#   

process_output()
{
  name=$1;
  size=$2;
  let index_max=size*size;
  echo "    name=${name}, size=${size}, index_max=${index_max}";

  if [ ${name} == "CMLP" ];then
    cat ${DIR_OUTPUTS}/${FILE_OUTPUT} | grep "Cmlp" > ${DIR_OUTPUTS}/cmlp.out;
  elif [ ${name} == "CPSRN" ];then
    cat ${DIR_OUTPUTS}/${FILE_OUTPUT} | grep "Cpsrn" > ${DIR_OUTPUTS}/cpsrn.out;
  elif [ ${name} == "CSRN" ];then
    cat ${DIR_OUTPUTS}/${FILE_OUTPUT} | grep "Csrn" > ${DIR_OUTPUTS}/csrn.out;
  fi

  index=0;
  while [ ${index} -lt ${index_max} ];do
    cat ${DIR_OUTPUTS}/${FILE_OUTPUT} | grep "Cell.*${index}.*(" \
      > ${DIR_OUTPUTS}/cell${index}.out;
    let index=index+1;
  done
}

open_postprocessed_files()
{
  name=$1;
  size=$2;
  let index_max=size*size;
#  echo "    name=${name}, size=${size}, index_max=${index_max}";

  if [ ${name} == "CMLP" ];then
    gedit ${DIR_OUTPUTS}/cmlp.out;
  elif [ ${name} == "CPSRN" ];then
    gedit ${DIR_OUTPUTS}/cpsrn.out;
  elif [ ${name} == "CSRN" ];then
    gedit ${DIR_OUTPUTS}/csrn.out;
  fi
  
  echo -n "    .";

  index=0;
  while [ ${index} -lt ${index_max} ];do
    gedit ${DIR_OUTPUTS}/cell${index}.out;
    echo -n ".";
    let index=index+1;
  done
  echo "";
}

# Read the first line of the output file and pull up some information.
# Examples:
#   ARCHITECTURE_NAME=CMLP; or ARCHITECTURE_NAME=CSRN;
#   ARCHITECTURE_SIZE=2; or ARCHITECTURE_NAME=19;

ARCHITECTURE_NAME=`head -n 1 ${DIR_OUTPUTS}/${FILE_OUTPUT} | awk '{ print $4; }'`;
ARCHITECTURE_SIZE=`head -n 1 ${DIR_OUTPUTS}/${FILE_OUTPUT} | awk '{ print $5; }'`;

echo "  ARCHITECTURE_NAME=${ARCHITECTURE_NAME}";
echo "  ARCHITECTURE_SIZE=${ARCHITECTURE_SIZE}";

if [ ${ARCHITECTURE_NAME} != "CMLP" ] && \
   [ ${ARCHITECTURE_NAME} != "CPSRN" ] && \
   [ ${ARCHITECTURE_NAME} != "CSRN" ];then
   echo "Error: ${ARCHITECTURE_NAME} is not supported in ${COMMAND_NAME}.";
   exit 1;
fi

echo "  FILE_OUTPUT=${FILE_OUTPUT}";

RUN_COMMAND="process_output ${ARCHITECTURE_NAME} ${ARCHITECTURE_SIZE}";
echo "  ${RUN_COMMAND}";
eval ${RUN_COMMAND};

if [ ${OPT_OPENFILES} -eq 1 ];then
  RUN_COMMAND="open_postprocessed_files ${ARCHITECTURE_NAME} ${ARCHITECTURE_SIZE}";
  echo "  ${RUN_COMMAND}";
  eval ${RUN_COMMAND};
fi

#EOF
