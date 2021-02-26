---
sort: 1
---

# OpenThread Border Router setup on a Rpi4

## Flash Raspian OS:

Download the [Raspberry Pi OS Lite image](https://www.raspberrypi.org/downloads/raspberry-pi-os/) to a local machine with a built-in or external SD card reader.

Flash the downloaded image on the SDcard with [Balena Etcher](https://www.balena.io/etcher/) if you are using a windows machine. Alternatives exist for Linux and Mac.

- Run balenaEtcher and select the unzipped Raspberry Pi OS image file
- Select the SD card drive
- Finally, click Burn to write the Raspberry Pi OS image to the SD card
- You'll see a progress bar. Once complete, the utility will automatically unmount the SD card so it's safe to remove it from your computer.

Replug the Sdcard and add an empty file to the root of the SDcard disk named "ssh" without any termination. This will allow you to access the RaspberryPi over telnet SSH.

## install the border router engine:

Once you have plugged the Sdcard and powered up the RPi, wait some seconds and connect it from you pc using telnet (RPI ip address is needed port 22)

- login is "pi"
- password is "raspberry"

Once connected issue the following commands:

```
> sudo apt-get update
> sudo apt-get install git
```

```
> git clone https://github.com/openthread/ot-br-posix
```

```
> cd ot-br-posix
> ./script/bootstrap
```

```
> NETWORK_MANAGER=0 ./script/setup
```


add the following line in /etc/default/otbr-agent:

```
OTBR_AGENT_OPTS="-I wpan0 -B eth0 spinel+hdlc+uart:///dev/ttyACM0?uart-baudrate=460800"
```

using

```
> sudo vi /etc/default/otbr-agent
```

then

```
> sudo reboot now
```

after reboot:

```
> sudo systemctl status
```

If the setup script was successful, the following services appear in the output:

- avahi-daemon.service
- otbr-agent.service
- otbr-web.service

```
> sudo ot-ctl state ## --> should respond disabled
```

```
> sudo ot-ctl prefix add 2001:db8::/64 paros
> sudo ip addr add dev eth0 2002::2/64
```

```
> sudo ot-ctl

>> thread stop  ##--> shutdown the stack
>> ifconfig down  ##--> stop OTBR network
>> ifconfig up  ## --> to take into account new configured IPv6 settings
>> thread start ## --> restart stack
>> ipaddr ##--> to check node addresses like example below
	2001:db8:0:0:a313:3b5a:e2bd:314b
	fdde:ad00:beef:0:0:ff:fe00:fc00
	fdde:ad00:beef:0:0:ff:fe00:9c00
	fdde:ad00:beef:0:c318:e941:15a6:99f3
	fe80:0:0:0:a413:e4c7:d91a:2deb
>> channel ##--> 11
>> panid  ##--> 0xface
>> masterkey
	##--> 00112233445566778899aabbccddeeff   
	##-->  useful for the comissioning of the nodes in the second section.
```



 
