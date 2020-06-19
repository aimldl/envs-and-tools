#!/bin/bash
# modules4nns-multiple_runs.bash
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
#   source nns.bash;
#
# Guidelines
#
#   1. This bash script can't be executed standalone because it is designed
#      to be sourced by a bash script nns.bash.
#   2. Specify an option number of the -o option in for the chunk of lines 
#      you added/changed. Run "nns.bash" with the specified option number.
#      Say the number is 3. In the project root directory,
#
#        $ ./nns.bash -o 3
#
#   3. Change this file. There are four major steps.
#     3.1. Set up the simulations.
#     3.2. Copy the configuration file to your target output directory.
#          This file will be used as a template. Note all the associated files
#          should be stored in this directory.
#     3.3. Change the configuration file. A group of procedures can be used to
#          swap a value or string in the file: change_template_next_line, 
#          change_template_int, change_template_float, & change_template_string.
#          Usage examples are below.
#
#          change_template_next_line
#          change_template_float
#          change_template_string
#          change_template_int
#         
#     3.4. Run simulations.
#     3.5. Return to the output directory for this run.
#
#   Note:Do not evaluate commands other than the part that actually runs nns-1.2.
#        Using option -d will cause an error because evaluating a command won't
#        copy a file, make a directory, or cd to a target directory.
#
#   Known issues:
#     ./nns.bash: line 195: ./nns-1.2.exe: No such file or directory
#       If you see this error message, check if you have compiled the program.

if [ ${OPT_OPTION} -eq 2 ]; then
  ##############################################################################
  #                           Set up the simulations                           #
  ##############################################################################
  DIR_THISRUN="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";
  CFILE_OLD=${DIR_ROOT}/${DIR_CONFIGFILES}/${FILE_CONFIG};

  mksubdir ${DIR_THISRUN} ${OPT_SILENTMODE};
  echo "";

  # It's suggested not to indent a line starting with for.
  # Each row can be changed frequently; works are saved for indenting upon line changes.
  for PLAYER in white; do
  for W in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0; do
  for LAYERS in "3:1" "5:1" "7:1" "9:1" "11:1" "5:3:1" "7:3:1" "7:5:1" "9:3:1" "9:5:1" "9:7:1" "11:3:1" "11:5:1" "11:7:1" "11:9:1" "7:5:3:1"; do

  TARGET="${PLAYER}-${W}-${LAYERS}";
  echo -e "\033[36m  TARGET=${TARGET}\033[0m";
  ###############################################################
  # Copy the configuration file to your target output directory #
  ###############################################################
  DIR_TARGETOUTPUT=${DIR_THISRUN}/${TARGET};
  CFILE=${DIR_TARGETOUTPUT}/${FILE_CONFIG};

  safe_mkdir ${DIR_TARGETOUTPUT} ${OPT_SILENTMODE};
  echo "  cp ${CFILE_OLD} ${DIR_TARGETOUTPUT}";
  echo "  cd ${DIR_TARGETOUTPUT}";
  cp ${CFILE_OLD} ${DIR_TARGETOUTPUT};
  cd ${DIR_TARGETOUTPUT};

  #################################
  # Change the configuration file #
  #################################
  change_template_int ${CFILE}    simul_show_progress_bar 0;
  change_template_string ${CFILE} file_nn_init_weights weights-${TODAY}.cnn;
  change_template_string ${CFILE} cnn_initial_weights_mode random;

  change_template_string ${CFILE} simul_player ${PLAYER};
  change_template_float ${CFILE}  pso_w ${W};
  change_template_string ${CFILE} neuralnets_number_of_neurons_in_layers ${LAYERS};

  ###################
  # Run simulations #
  ###################
  evaluate ${OPT_DUMMYCOMMAND} "cd ${DIR_ROOT}/${DIR_BIN}";
  evaluate ${OPT_DUMMYCOMMAND} "./${CMD4NNS} ${CFILE} ${DIR_TARGETOUTPUT}";

  done
  done
  done

  ##############################################################################
  #                          Return to DIR_THISRUN                             #
  ##############################################################################
  cd ${DIR_THISRUN};

elif [ ${OPT_OPTION} -eq 3 ]; then
  ##############################################################################
  #                           Set up the simulations                           #
  ##############################################################################
  DIR_THISRUN="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";
  evaluate ${OPT_DUMMYCOMMAND} "mksubdir ${DIR_THISRUN} ${OPT_SILENTMODE}";
  CFILE=${DIR_ROOT}/${DIR_CONFIGFILES}/${FILE_CONFIG};

  # It's suggested not to indent a line starting with for.
  # Each row can be changed frequently; works are saved for indenting upon line changes.
  for PLAYER in black white; do
  for HLAYER_ACTFN in tansig logsig; do
  for HIST_RESET in 0 1; do
  for OFFSET in 0.0 1.0; do
  for FD_INIT in zeros ones random target rand_ternary; do
  for W in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0; do
  for VMAX in 1.0 10.0 100.0; do
  for XMIN in -10.0 -100.0 -500.0; do
  for XMAX in 10.0 100.0 500.0; do
  for C1 in 1.0 10.0 100.0; do
  for C2 in 1.0 10.0 100.0; do
  for LAYERS in "1:1" "3:1" "5:1" "7:1" "9:1" "11:1" "7:3:1"; do
  for SP_LOGSIG in 1.0 5.0 10.0 15.0; do
  for SP_TANSIG in 1.0 5.0 10.0 15.0; do

  TARGET="${PLAYER}-${HLAYER_ACTFN}-${HIST_RESET}-${OFFSET}-${FD_INIT}-${W}-${VMAX}-${XMIN}-${XMAX}-${C1}-${C2}-${LAYERS}-${SP_LOGSIG}-${SP_TANSIG}";

  ###############################################################
  # Copy the configuration file to your target output directory #
  ###############################################################
  DIR_TARGETOUTPUT=${DIR_THISRUN}/${TARGET};
  safe_mkdir ${DIR_TARGETOUTPUT} ${OPT_SILENTMODE};
  cp ${CFILE} ${DIR_TARGETOUTPUT};
  cd ${DIR_TARGETOUTPUT};

  #################################
  # Change the configuration file #
  #################################
  change_template_int ${CFILE}    "simul_show_progress_bar" 0;
  change_template_string ${CFILE} "file_nn_init_weights" weights-${TODAY}.cnn;
  change_template_string ${CFILE} "cnn_initial_weights_mode" random;

  change_template_string ${CFILE} "simul_player" ${PLAYER};
  change_template_string ${CFILE} "neuralnets_activation_function_hidden_layer" ${HLAYER_ACTFN};
  change_template_int ${CFILE}    "pso_use_particle_history_reset" ${HIST_RESET};
  change_template_float ${CFILE}  "data_representation_offset" ${OFFSET};
  change_template_string ${CFILE} "cnn_fd_input_initialization" ${FD_INIT};

  change_template_float ${CFILE}  "pso_w" ${W};

  change_template_float ${CFILE}  "pso_v_max" ${VMAX};
  change_template_float ${CFILE}  "pso_x_min" ${XMIN};
  change_template_float ${CFILE}  "pso_x_max" ${XMAX};
  change_template_float ${CFILE}  "pso_c1" ${C1};
  change_template_float ${CFILE}  "pso_c2" ${C2};

  change_template_string ${CFILE} "neuralnets_number_of_neurons_in_layers" ${LAYERS};
  change_template_float ${CFILE}  "neuralnets_slope_param_logsig" ${SP_LOGSIG};
  change_template_float ${CFILE}  "neuralnets_slope_param_tansig" ${SP_TANSIG};

  done
  done
  done
  done
  done
  done
  done
  done
  done
  done
  done
  done
  done
  done

  ###################
  # Run simulations #
  ###################
  evaluate ${OPT_DUMMYCOMMAND} "cd ${DIR_ROOT}/${DIR_BIN}";
  evaluate ${OPT_DUMMYCOMMAND} "./${CMD4NNS} ${CFILE} ${DIR_TARGETOUTPUT}";

  ##############################################################################
  #                          Return to DIR_THISRUN                             #
  ##############################################################################
  cd ${DIR_THISRUN};

elif [ ${OPT_OPTION} -eq 4 ]; then
  echo "  Option ${OPT_OPTION} has not been implemented yet.";
# IT IS SUGGESTED TO LEAVE THIS PART FOR FUTURE REFERENCE.
  ##############################################################################
  #                           Set up the simulations                           #
  ##############################################################################

#  DIR_THISRUN="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";
#  evaluate ${OPT_DUMMYCOMMAND} "mksubdir ${DIR_THISRUN} ${OPT_SILENTMODE}";
#  CFILE=${DIR_ROOT}/${DIR_CONFIGFILES}/${FILE_CONFIG};
#
#  for variable in param1 param2 ... paramn; do
#    command1
#    command2
#      ...
#    commandn
#  done
#
#  while [ condition ]; do
#    command1
#    command2
#      ...
#    commandn
#  done
#
#  An example of condition is "${variable} -le 6".

  ##############################################################################
  #        Copy the configuration file to your target output directory         #
  ##############################################################################
#  DIR_TARGET_OUTPUT=${DIR_THISRUN}/test;
#  cp ${CFILE} ${DIR_TARGET_OUTPUT};
#  cd ${DIR_TARGET_OUTPUT};
  ##############################################################################
  #                        Change the configuration file                       #
  ##############################################################################
#  change_template_next_line file_template expr2match   new_expression
#  change_template_float     file_template float2match  new_value
#  change_template_string    file_template string2match new_string
#  change_template_int       file_template int2match    new_value

  ##############################################################################
  #                              Run simulations                               #
  ##############################################################################
#  evaluate ${OPT_DUMMYCOMMAND} "cd ${DIR_ROOT}/${DIR_BIN}";
#  evaluate ${OPT_DUMMYCOMMAND} "./${CMD4NNS} ${CFILE} ${DIR_THISRUN}";
  ##############################################################################
  #                          Return to DIR_THISRUN                             #
  ##############################################################################
#  cd ${DIR_THISRUN};
# IT IS SUGGESTED TO LEAVE THIS PART FOR FUTURE REFERENCE.
else
  echo -e "\033[34mError: range of option -o is wrong.\033[0m";
  showShortUsage;
  exit 1;
fi
#EOF
