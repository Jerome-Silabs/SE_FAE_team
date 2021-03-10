---
sort: 2
---

# Commission the node to an existing OTBR:

## Retrieve Thread network information :

To commission chip node you will need first channel, panid and masterkey of your existing Thread network. If no network is created follow this procedure:
https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/OpenThread_Border_Router/install.html

```
 sudo ot-ctl
> channel
11
> panid
0xb434
> masterkey
8a806b4eb634cb342a41a23b603c2a47
>ipadrr

```

## Comission node using python programmer :

Now we are going to commission a CHIP lighting-app example to the Thread network.
You can find the procedure to build and flash a light example here:
https://jerome-silabs.github.io/SE_FAE_team/OpenThread/Applications/CHIP_compile_lighting_example/

Perform a factoryReset on the light node. Example should now be advertising on BLE and ready to be commissioned by our chip device controller.
 
Launch chip-device-ctrl by specifying the blueteooth controller in use:
```
 chip-device-ctrl --bluetooth-adapter=hci0
```

Start a ble scanning. You should see you Lighging example:

```
chip-device-ctrl > ble-scan
2021-03-10 17:40:27,718 ChipBLEMgr   INFO     use default adapter
2021-03-10 17:40:27,880 ChipBLEMgr   INFO     scanning started
2021-03-10 17:40:28,495 ChipBLEMgr   INFO     Name            = EFR32_LIGHT
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

Set Thread credentials that we retrieved from OTBR:

```
chip-device-ctrl > set-pairing-thread-credential <channel> <pan id[HEX]> <master_key>
```

In our example:

```
chip-device-ctrl > set-pairing-thread-credential 11 0xb434 8a806b4eb634cb342a41a23b603c2a47
```

Connect to device using discriminator and setup pin code. Pincode is provided on RTT console of lighting exemple. You can specify here a nodeId that will be used to send ZCL command later:

```
connect -ble <discriminator> <setup pin code> [<nodeid>]

```

In our example :

```
chip-device-ctrl > connect -ble 3840 12345678 12121212

```

Node should now be commissioned on thread network.

At this point you need to confirure IPV6 route to your light node (through OTBR)

For example :

```
sudo ifconfig <interface> inet6 add 2002::1/64
sudo ip route add 2001:db8:0:0::/64 via 2002::2
sudo ip route add fdde:ad00:beef::/64 via 2002::2
```

Where 2002::2 is IPV6 address of network interface used by your OTBR


## Send ZCL command to the node :

You can toggle the led of the example with the following command:

```
> chip-device-ctrl > zcl OnOff Toggle <NodeId> <EndpointId> <GroupId>
```

In our example:

```
> chip-device-ctrl > zcl OnOff Toggle 12121212 1 0
```
 
