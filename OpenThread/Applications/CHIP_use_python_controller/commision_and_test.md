---
sort: 2
---

# Commission the node to an existing OTBR:

## Retrieve Thread network information :

To commission chip node you will need first channel, panid and masterkey of your existing Thread network. If no network is created follow this procedure:
[https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/OpenThread_Border_Router/install.html](https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/OpenThread_Border_Router/install.html)

Type the following to retrieve information of you thread network:

```
pi@raspberrypi:~ $ sudo ot-ctl
> channel
11
> panid
0xb434
> masterkey
8a806b4eb634cb342a41a23b603c2a47
>ipadrr
2001:db8:0:0:138e:f869:5848:66be
fdde:ad00:beef:0:0:ff:fe00:fc00
fdde:ad00:beef:0:0:ff:fe00:2800
fdde:ad00:beef:0:cf03:ffc0:3383:5fae
fe80:0:0:0:49:9a6b:56f9:679f

```

For route configuration, you will also need IPV6 address used by network interface of your OTBR:

```
pi@raspberrypi:~ $ ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.0.22  netmask 255.255.255.0  broadcast 192.168.0.255
        inet6 fe80::ba27:ebff:fe7d:3049  prefixlen 64  scopeid 0x20<link>
        inet6 2002::2  prefixlen 64  scopeid 0x0<global>
```

First we are going to confirure IPV6 route to your CHIP node (through OTBR)

Assign an IPV6 prefix to interface of your machine

```
sudo ifconfig <interface> inet6 add 2002::1/64
```

Create routes to the chip node based on OTBR global prefix configured 

```
sudo ip route add 2001:db8:0:0::/64 via 2002::2
sudo ip route add fdde:ad00:beef::/64 via 2002::2
```
Where 2002::2 is IPV6 address of network interface used by your OTBR

## Commission node using python programmer :

Now we are going to commission a CHIP example to the Thread network.
You can find the procedure to build and flash a light example here:
[https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/CHIP_compile_lighting_example/](https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/CHIP_compile_lighting_example/)

Once your chip node is running, prform a factoryReset of the device. Example should now be advertising on BLE and ready to be commissioned by our chip device controller.
 
Launch chip-device-ctrl by specifying the bluetooth controller in use:
```
 chip-device-ctrl --bluetooth-adapter=hci0
```
Depending on repository version you might need to use the following command instead:

```
chip-device-ctrl > ble-adapter-print
2020-11-23 17:41:53,116 ChipBLEMgr   INFO     adapter 0 = DE:AD:BE:EF:00:00
2020-11-23 17:41:53,116 ChipBLEMgr   INFO     adapter 1 = DE:AD:BE:EF:01:01
2020-11-23 17:41:53,116 ChipBLEMgr   INFO     adapter 2 = DE:AD:BE:EF:02:02

chip-device-ctrl > ble-adapter-select DE:AD:BE:EF:00:00

```

Start a ble scanning. You should see you Chip example:

```
chip-device-ctrl > ble-scan
2021-03-10 17:40:27,718 ChipBLEMgr   INFO     use default adapter
2021-03-10 17:40:27,880 ChipBLEMgr   INFO     scanning started
2021-03-10 17:40:28,495 ChipBLEMgr   INFO     Name            = EFR32_XXXXX
2021-03-10 17:40:28,495 ChipBLEMgr   INFO     ID              = d558231f-fb05-389c-bae2-6b797b364d28
2021-03-10 17:40:28,495 ChipBLEMgr   INFO     RSSI            = -34
2021-03-10 17:40:28,496 ChipBLEMgr   INFO     Address         = 00:0B:57:31:62:49
2021-03-10 17:40:28,497 ChipBLEMgr   INFO     Pairing State   = 0
2021-03-10 17:40:28,497 ChipBLEMgr   INFO     Discriminator   = 3840
2021-03-10 17:40:28,497 ChipBLEMgr   INFO     Vendor Id       = 57600
2021-03-10 17:40:28,497 ChipBLEMgr   INFO     Product Id      = 64768
2021-03-10 17:40:28,498 ChipBLEMgr   INFO     Adv UUID        = 0000feaf-0000-1000-8000-00805f9b34fb
2021-03-10 17:40:28,498 ChipBLEMgr   INFO     Adv Data        = 00000f00e100fd
2021-03-10 17:40:28,498 ChipBLEMgr   INFO    

```
Put aside the discriminator id. You will need it later.

Set Thread credentials that we retrieved from OTBR at the top on this procedure:

```
chip-device-ctrl > set-pairing-thread-credential <channel> <pan id[HEX]> <master_key>
```

In our example:

```
chip-device-ctrl > set-pairing-thread-credential 11 0xb434 8a806b4eb634cb342a41a23b603c2a47
```

Connect to device using discriminator and setup pin code. Pincode is provided on RTT console of CHIP example. You can specify here a optionnal nodeId that will be used to send ZCL command later. A random node id will be printed during commisionnig if not specified:

```
connect -ble <discriminator> <setup pin code> [<nodeid>]

```

In our example :

```
chip-device-ctrl > connect -ble 3840 12345678 12121212

```

Node should now be commissioned on thread network.

