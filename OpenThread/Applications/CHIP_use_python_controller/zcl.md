---
sort: 3
---

# Send ZCL command to the node :

## Light Example :
If you are working on a Light example, you can now toggle the led of the example with the following command:

```
> chip-device-ctrl > zcl OnOff Toggle <NodeId> <EndpointId> <GroupId>
```

In our example:

```
> chip-device-ctrl > zcl OnOff Toggle 12121212 1 0
```
 
## Window Covering Example :
If you are working on a Window covering example, you can now close the window covering with the following command:

```
> chip-device-ctrl > zcl WindowCovering WindowCoveringDownClose <NodeId> <EndpointId> <GroupId>
```

In our example:

```
> chip-device-ctrl > zcl WindowCovering WindowCoveringDownClose 12121212 1 0
```
