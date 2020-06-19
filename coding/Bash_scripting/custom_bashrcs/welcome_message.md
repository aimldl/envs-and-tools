

#####################
#  Welcome Message  #
#####################
# Welcome to ubuntu18.04, conda 4.8.2, Python 3.7.6
linux_distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
python_version=`python --version`
echo "Welcome to $linux_distribution, $python_version"  # ubuntu18.04
 
# TODO: Fix "bash: conda: command not found"
#anaconda_version=`conda -V`
#if [ ! -z $anaconda_version]; then  # if not empty
#  echo "Welcome to $linux_distribution, $anaconda_version, $python_version"  # ubuntu18.04
#else
#  echo "Welcome to $linux_distribution, $python_version"  # ubuntu18.04
#fi

