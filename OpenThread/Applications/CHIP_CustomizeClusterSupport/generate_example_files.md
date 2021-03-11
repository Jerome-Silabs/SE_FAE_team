---
sort: 1
---

# Generate Example Files using ZAP

## Prerequisites
- First, make sure that you have followed the [Build Instructions](https://github.com/brian-silabs/connectedhomeip/blob/CUSTOM_WindowCovering/docs/BUILDING.md) for the CHIP repo

- Then we need to have ZAP submodule ready

``` console
cd third_party/zap/repo
npm install
```

Note that (at the time of writing) threre are some version requirements for node and Python
Node requires v 14.x.x
Python v3 (3.8 is the one I used)

In order to easily manage node, I highly recommend to use a version manager such as nvm
A lot of guides exist to guide you through the installation (I took [this one](https://tecadmin.net/how-to-install-nvm-on-ubuntu-20-04/) written for Linux Ubuntu 20.04)

``` console
sudo apt install curl 
curl https://raw.githubusercontent.com/creationix/nvm/master/install.sh | bash 

source ~/.profile 

nvm install --lts
```

Once this is done, you should have node installed on your computer and the above npm commands should work just fine

## Editing the ZAP file 

Open the ZAP Tool UI:

``` console
npm run zap
```
Open the .zap file you want to edit (make sure to make a copy first, otherwise git is your friend)
<img src="./images/01_generate-example-files_ZAPUI.png" alt="" width="500" class="center">


## Generate the new sources 

Once the new .zap file is saved, we are simply going to use helper scripts available in *connectedhomeip/scripts/tools/*
There are a few ones:
* One that Re-Generates all zaps
* One that selectively generate one zap sources (path to zap passed as argument)
* One that generates the Controller's sources
* One that generates the chip-tool sources

Each uses specific templates that can not be used in the ZAP GUI
Therefore we simply want to run it from the repo root as follows :

``` console
source scripts/tools/zap_generate.sh *path/to/zap.zap*
```

If all goes well, you should see no error in the STDOUT

If you are facing some errors, this is probably tied to NodeJs version.
To update NodeJs to the last stable version, follow this procedure:

``` console
npm cache clean -f
npm install -g n
sudo n stable
```

## Note
The chip tool requires both controler and chiptool zaps to be generated

 
