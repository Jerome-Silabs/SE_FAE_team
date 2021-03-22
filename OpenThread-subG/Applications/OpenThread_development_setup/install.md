---
sort: 1
---


# Install OpenThread development setup on Linux VM or PC

## Install VirtualBox:

If you are running Windows, you will need to install a virtual machine to run an Ubuntu image.
For this, download [VirtualBox](https://www.virtualbox.org/)


### Install Ubuntu 20.04.xx:

Once VirtualBox is installed, create a new virtual machine as a Linux Ubuntu 64 bit. Then either install Linux from an iso available [here](https://ubuntu.com/download/desktop) or a virtual disk already prepared [here](https://www.osboxes.org/ubuntu/).

In case you're installing from the iso, size the VM disk to at least 20GB to have room for the install and CHIP.


### Configure the virtual machine:

Before running the VM, we need to configure networking setting and change network adapter to Bridge mode.

- Open the VirtualBox and click on ‘Settings’ of your Linux VM.
- Click on ‘Network’ and Select the ‘Adapter 1’ tab.
- Make sure ‘Bridge Adapter’ is selected in the ‘Attached to:’ box.
- Click OK.

go to Install commander step.


## Install on PC:

If you have a linux PC, then make only sure to have it installed with Ubuntu 20.04.xx.

Follow on with the commander install below.


## Install commander:

In order to flash your future binaries, you can optionnaly install commander from its linux link [here](https://www.silabs.com/mcu/programming-options).


## Install OpenThread:

Update the latest packages by typing following commands in terminal window:

```
> sudo apt update
> sudo apt install
> sudo apt-get install git gcc g++ python pkg-config libssl-dev libdbus-1-dev libglib2.0-dev libavahi-client-dev ninja-build python3-venv python3-dev unzip python3-pip
```

Then download and install OpenThread.

```
> git clone --recurse-submodules https://github.com/openthread/openthread.git
> cd openthread/
```

Finally

```
> ./script/bootstrap
> ./bootstrap
```






 
