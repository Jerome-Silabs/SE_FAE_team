---
sort: 2
---

# Commission the node to the OTBR:

## commission the node :

open a terminal (TeraTerm ) or other to connect to the node CLI

```
> factoryreset
> state
	--> should be disabled
> dataset channel 11
> dataset panid 0xdaf7
	--> panid of the OTBR above to join its network
> dataset masterkey 00112233445566778899aabbccddeeff
	--> reuse OTBR masterkey above
> dataset commit active

> ifconfig up   
> thread start  --> start stack and proceed with comissioning using commited dataset
> ipaddr --> to check node addresses like example below
	2001:db8:0:0:a313:3b5a:e2bd:314b
	fdde:ad00:beef:0:0:ff:fe00:fc00
	fdde:ad00:beef:0:0:ff:fe00:9c00
	fdde:ad00:beef:0:c318:e941:15a6:99f3
	fe80:0:0:0:a413:e4c7:d91a:2deb
```

## tested:

Now to check the node is in the network you can reopen telnet session with the OTBR and:

```
> sudo ot-ctl
>> child table
	--> display the commissioned nodes
>> ping 2001:db8:0:0:a313:3b5a:e2bd:314b
	--> should give you a confirmation the node is on the network
```





 
