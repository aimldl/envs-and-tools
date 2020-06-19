#!/bin/bash
# nns_module-single_run.bash
#
# This file is designed to be sourced by a bash script nns.bash.
# Usage:
#
#   source filename;
#
# Last updated:  Mar. 8, 2011 (Tue)
# First written: Feb, 2008

DIR_THISRUN="${DIR_ROOT}/${DIR_OUTPUTS}/${TODAY}";
evaluate ${OPT_DUMMYCOMMAND} "mksubdir ${DIR_THISRUN} ${OPT_SILENTMODE}";

evaluate ${OPT_DUMMYCOMMAND} "cd ${DIR_ROOT}/${DIR_BIN}";
evaluate ${OPT_DUMMYCOMMAND} "./${CMD4NNS} ${FILE_CONFIG} ${DIR_THISRUN}";
#EOF
