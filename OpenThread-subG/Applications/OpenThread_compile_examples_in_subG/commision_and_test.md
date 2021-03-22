---
sort: 2
---

# Commission the node to the OTBR at thread level for a test:

This is to test the Thread transport layer is working ok.

## configure the border router to create a subG network:

first restart the RCP to default settings by connecting to the RPi and issuing:

```
sudo ot-ctl factoryreset
```

Now, we will configure the border router:

```
> sudo ot-ctl

>> thread stop  ##--> shutdown the stack
>> ifconfig down  ##--> stop OTBR network
>> channel 4  ##--> to move the radio to a subG channel (1 to 10)
>> ifconfig up  ## --> to take into account new configured IPv6 settings
>> thread start ## --> restart stack
>> ipaddr ##--> to check node addresses like example below
	fdde:ad00:beef:0:0:ff:fe00:fc00
	fdde:ad00:beef:0:0:ff:fe00:9c00
	fdde:ad00:beef:0:c318:e941:15a6:99f3
	fe80:0:0:0:a413:e4c7:d91a:2deb
>> channel ##--> 4
>> panid  ##--> 0xface
>> masterkey
	##--> 00112233445566778899aabbccddeeff   
	##-->  useful for the commissioning of the nodes in the second section.
```

## commission the node :

Now we move to the node to be added to this subG OpenThread network.
Oopen a terminal (TeraTerm ) or other to connect to the node CLI

```
> factoryreset
> state
	--> should be disabled
> dataset channel 4
> dataset panid 0xdaf7
	--> panid of the OTBR above to join its network
> dataset masterkey 00112233445566778899aabbccddeeff
	--> reuse OTBR masterkey above
> dataset commit active

> ifconfig up   
> thread start  --> start stack and proceed with commissioning using committed dataset
> ipaddr --> to check node addresses like example below
	fdde:ad00:beef:0:0:ff:fe00:4001
	fdde:ad00:beef:0:429:a43b:e1a2:d383
	fe80:0:0:0:a41f:7ddb:4504:7a82
```

## test:

Now to check the node is in the network you ping the OTBR:

```
> ping fdde:ad00:beef:0:0:ff:fe00:fc00  ##--> address of the OTBR
	--> should give you a confirmation the node is on the network
```





 
