```
# This part is take out from install_kubeflow.

echo ""
echo "------------------------------------------------------"
echo "  Create the virtual environment ${BASE_DIR_NAME}"
echo "------------------------------------------------------"

conda update -n base -c defaults conda
conda create -n ${BASE_DIR_NAME} python=3 anaconda

echo "---------------------------"
echo "  Verify the installation  "
echo "---------------------------"

conda info -e
conda activate ${BASE_DIR_NAME}

#CommandNotFoundError: Your shell has not been properly configured to use 'conda activate'.
#To initialize your shell, run
#
#    $ conda init <SHELL_NAME>
#
#Currently supported shells are:
#  - bash
#  - fish
#  - tcsh
#  - xonsh
#  - zsh
#  - powershell
#
#See 'conda init --help' for more information and options.
#
#IMPORTANT: You may need to close and restart your shell after running 'conda init'

```

