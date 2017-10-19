# Quick guide for GPU usage on Layers

This guide is provided for linux OS Ubuntu 16.04 distro. Not tested on mac nor other distribution. Remark this instructions can change 
from one distribution to other, or from distribution version to other. Moreover depending on your motherboard model (UEFI or BIOS) we could have different
behaviour after setting up. We have test this on Ubuntu 14 and Ubuntu 16 and with several motherboard so this should be enough to set up your computer. 
If you find specific way of setting up drivers and cuda in other distros, motherboards or OS, feel free to push and we will add to installation
instructions.

# Step 1: install drivers

For driver installation we assume you have plug in your Nvidia Card in the PCI bus. Check [nvidia](www.nvidia.com) 
for the hardware resources needed for your specific GPU (type of PCI, number of slots...). 

After plug in start your linux grub  (typically pressing esc key).  After move to the Ubuntu launcher and press key "e", go to the line 
which specify the boot parameters and add *nomodeset* at the end. This is not always necessary and only needed with some graphics card. 
Sometimes de nouveau drivers (linux drivers for Nvidia GPU) does not work properly,reasons [here](https://askubuntu.com/questions/207175/what-does-nomodeset-do). With this
we basically use BIOS modes for display. This is also necessary to log into your user, as we will not be able to do so if drivers are not properly set. If nouveau works well
you could go into your desktop without any issue.

After log into your user account download the driver for your specific model and OS [here](http://www.nvidia.es/Download/index.aspx?lang=es). You 
should get a .run file downloaded. Give execution permission (chmod +x). Then press ctrl+alt+F1 to start a virtual console. Log in and kill the X terminal
with *sudo service lightdm stop*. Newest version of the drivers does not let you install if this has not been done. In older version 
you could get conflicts when installation is done and undesired behaviour of your OS.

After this just execute sudo *path_to_file/nvidia_driver_installation.run*. Follow the steps and install. You could find to alternatives depending on
your motherboard model.

## Step 1.1: UEFI: sign drivers for kernel
When installing drivers if you find something related to sign kernels type yes for everything and tell the driver to generate a pair 
of keys. In some linux distributions we require the modules to be signed by a key so they can be trusted by the kernel 
when they are loaded. After installing drivers you need to use the mokutil from linux.

*sudo mokutil --import /usr/share/nvidia/nvidia\*.der* (your specific der file). Select a password. Then reboot and we should get a message
from the Bios telling us to enroll. Press enroll mok then continue then yes and finally type the password. Reboot and you could now
use your computer without problems.

If you do not find something related to sign kernels when installing this steps are not necessary.

# Step 2: install cuda

Download cuda from the internet, for your specific distribution. You will get a .run file. Give execution permission, then kill the X terminal
as above (maybe not necessary), and then execute your run file. You will be asked to install drivers, cuda and cuda samples. You only need to install
cuda.  Do NOT INSTALL DRIVERS. Cuda samples are optional.

# Step 3: using dedicated GPU and nvidia GPU

Maybe you are interested in using both GPUs for working into two monitors (or maybe in 4). You can plug in two monitor into the nvidia card, 
however using the dedicated GPU for displaying is a good idea. For this cannot let the nvidia driver installation to generate a xconf file. Tell not
to generate this file when installing, because this will set specific parameters to use the NVIDIA GPU for graphic interface.

After installing reboot your computer and enter into the bios settings. In my computer you have to press F7 to go to advanced mode, then go to advanced, go to System Agent config, go to graphics config. Here you have to enable IGPU, then select PCI as primary display and select adecuated memory in DVMT pre allocated. Maybe you have to enable IGPU and reboot to get the DVMT option. Try different memory sizes until you get the two screens working. DVMT is how much size of the RAM is dedicated for GPU working.
