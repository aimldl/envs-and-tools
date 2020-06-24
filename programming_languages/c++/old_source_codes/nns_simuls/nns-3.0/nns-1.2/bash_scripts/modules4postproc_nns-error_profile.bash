#!/bin/bash
# modules4postproc_nns-error_profile.bash
#
# This file is designed to be sourced by a bash script nns.bash.
# Usage:
#
#   source filename;
#
# Last updated:  Mar. 10, 2011 (Thu)
# First written: Feb, 2008

# Assumption 1. The output is processed on the same day for this option.
# Assumption 2. The target output directory has sub-directories only.
DIR_TARGETOUTPUT="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";  # Assumption 1

if test ! -d ${DIR_TARGETOUTPUT}; then
  echo "${DIR_TARGETOUTPUT} doesn't exist. Exiting...";
  exit 1;
else
  cd ${DIR_TARGETOUTPUT};
  safe_rm ${FILE_SIMPLELIST};
  safe_rm ${FILE_FULLLIST};
  for dir_name in `ls`; do  # Assumption 2
    # Simple list
    echo ${dir_name} >> ${FILE_SIMPLELIST};
    head -n 6 ${dir_name}/${FILE_ERROR_PROFILE} >> ${FILE_SIMPLELIST};
    tail -n 1 ${dir_name}/${FILE_ERROR_PROFILE} >> ${FILE_SIMPLELIST};
    echo "">> ${FILE_SIMPLELIST};

    # Full list
    echo ${dir_name} >> ${FILE_FULLLIST};
    head ${dir_name}/${FILE_ERROR_PROFILE} >> ${FILE_FULLLIST};
    tail ${dir_name}/${FILE_ERROR_PROFILE} >> ${FILE_FULLLIST};
    echo "">> ${FILE_FULLLIST};
  done
  gedit ${DIR_TARGETOUTPUT}/${FILE_SIMPLELIST};
  gedit ${DIR_TARGETOUTPUT}/${FILE_FULLLIST};
fi
#EOF

