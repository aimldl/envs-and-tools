* Draft: 2021-05-19 (Wed)

# How to Configure Your Local Machines


## Windows machine
Step 1. Install Anaconda

Step 2. Verify the installed programs.

<img src='images/win10-menu-anaconda3_64-bit.png'>

Step 3. Open `Anaconda Powershell Prompt`.

Step 4. Create a new Conda virtual environment.
        The name is set to `tf2`, but you may choose one you like.

```powershell
(base) PS  C:\Users\aimldl> conda create -n tf2 python=3 anaconda
```
Enter `y` to proceed.
```powershell
  ...
Proceed ([y]/n)?
  ...
# To activate this environment, use
#
#     $ conda activate tf2
#
# To deactivate an active environment, use
#
#     $ conda deactivate

(base) PS C:\Users\aimldl> 
```

Step 5. Activate the created environment.
```powershell
(base) PS C:\Users\aimldl> conda activate tf2
(tf2) PS C:\Users\aimldl>
```
From now on `(tf2) > ` will be used instead of (tf2) PS C:\Users\aimldl> for simplicity.
```powershell
(tf2) > pip install --upgrade pip --user
```
The `--user` option is used because the permission error may occur.

Step 6. Let's check the GPU.
```powershell
(tf2) > nvidia-smi
Wed May 19 22:39:03 2021
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 456.71       Driver Version: 456.71       CUDA Version: 11.1     |
|-------------------------------+----------------------+----------------------+
| GPU  Name            TCC/WDDM | Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce GTX 1080   WDDM  | 00000000:01:00.0  On |                  N/A |
|  0%   37C    P8     8W / 200W |    757MiB /  8192MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      1228    C+G   Insufficient Permissions        N/A      |
|    0   N/A  N/A      1640    C+G   ...ram Files\XMind\XMind.exe    N/A      |
|    0   N/A  N/A      2052    C+G   ...me\Application\chrome.exe    N/A      |
|    0   N/A  N/A      3136    C+G   ...lPanel\SystemSettings.exe    N/A      |
|    0   N/A  N/A      3960    C+G   ...bbwe\Microsoft.Photos.exe    N/A      |
|    0   N/A  N/A      6180    C+G   C:\Windows\explorer.exe         N/A      |
|    0   N/A  N/A      6832    C+G   ...ropbox\Client\Dropbox.exe    N/A      |
|    0   N/A  N/A      7248    C+G   ...5n1h2txyewy\SearchApp.exe    N/A      |
|    0   N/A  N/A      8000    C+G   ...ekyb3d8bbwe\YourPhone.exe    N/A      |
|    0   N/A  N/A      9120    C+G   ...nputApp\TextInputHost.exe    N/A      |
|    0   N/A  N/A      9792    C+G   ...wekyb3d8bbwe\Video.UI.exe    N/A      |
|    0   N/A  N/A     10808    C+G   ...b3d8bbwe\WinStore.App.exe    N/A      |
|    0   N/A  N/A     10880    C+G   ...y\ShellExperienceHost.exe    N/A      |
+-----------------------------------------------------------------------------+
(tf2) > 
```
