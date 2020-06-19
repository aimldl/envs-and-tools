INSTALL.md
* Draft: 2020-0322 (Sun)
# Install

## Windows10
[CUDA Toolkit on Windows 10](https://medium.com/analytics-vidhya/cuda-toolkit-on-windows-10-20244437e036), medium, 2019-1214
### CUDA

Google search: nvidia cuda driver for windows
[CUDA Toolkit 10.2 Download](https://developer.nvidia.com/cuda-downloads)

### cuDNN

[Installation Guide](https://docs.nvidia.com/deeplearning/sdk/cudnn-install/index.html)
[Deep Learning SDK Documentation](https://docs.nvidia.com/deeplearning/sdk/)

4.3. Installing cuDNN On Windows
The following steps describe how to build a cuDNN dependent program. In the following sections the CUDA v9.0 is used as example:
Your CUDA directory path is referred to as C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2
Your cuDNN directory path is referred to as <installpath>
Navigate to your <installpath> directory containing cuDNN.
Unzip the cuDNN package.
cudnn-10.2-windows7-x64-v7.6.5.32.zip
or
cudnn-10.2-windows10-x64-v7.6.5.32.zip
Copy the following files into the CUDA Toolkit directory.
Copy <installpath>\cuda\bin\cudnn64_7.6.5.32.dll to C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\bin.
Copy <installpath>\cuda\ include\cudnn.h to C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\include.
Copy <installpath>\cuda\lib\x64\cudnn.lib to C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2\lib\x64.

Set the following environment variables to point to where cuDNN is located. To access the value of the $(CUDA_PATH) environment variable, perform the following steps:
Open a command prompt from the Start menu.
Type Run and hit Enter.
Issue the control sysdm.cpl command.
Select the Advanced tab at the top of the window.
Click Environment Variables at the bottom of the window.
Ensure the following values are set:
Variable Name: CUDA_PATH 
Variable Value: C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.2
Include cudnn.lib in your Visual Studio project.
Open the Visual Studio project and right-click on the project name.
Click Linker > Input > Additional Dependencies.
Add cudnn.lib and click OK.

## Linux
[Install Conda CUDA10.2 cuDNN7.6.5 Pytorch1.3.1 and Tensorflow2.0 in ubuntu 18.04 for deep learning](https://medium.com/datadriveninvestor/install-conda-cuda10-2-cudnn7-6-5-pytorch1-3-1-and-tensorflow2-0-in-ubuntu-18-04-for-deep-learning-5384ee09a503)
