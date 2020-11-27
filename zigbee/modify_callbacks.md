---
sort: 2
---

# Modify the callbacks to integrate your application

- Open the file <your_project_name>_callbacks.c. You will find there all the callbacks we set earlier

- 	Add the following lines at the top of the file:

```c
#include EMBER_AF_API_NETWORK_CREATOR
#include EMBER_AF_API_NETWORK_CREATOR_SECURITY
#include EMBER_AF_API_FIND_AND_BIND_TARGET

#define WINDOW_COVERING_ENDPOINT (1)
EmberEventControl networkManagementEventControl;
EmberEventControl networkOpeningEventControl;

void networkManagementEventHandler(void);
void networkOpeningEventHandler(void);
```

-	Edit the emberAfMainInitCallback implementation so that it ends like this:

```c
void emberAfMainInitCallback(void) {
    emberEventControlSetActive(networkManagementEventControl);
}
```

-	Edit the networkManagementEventHandler as follows:

```c
void networkManagementEventHandler(void) {
     emberEventControlSetInactive(networkManagementEventControl);
     if (emberAfNetworkState() != EMBER_JOINED_NETWORK) {
        EmberStatus status = emberAfPluginNetworkCreatorStart(false);
        emberAfCorePrintln("%p network %p: 0x%X", "Form", "start", status);
     }
}   
```

-	Also, edit the network creator complete callback to have a feedback:

```c
void emberAfPluginNetworkCreatorCompleteCallback(const EmberNetworkParameters *network,
                                                 bool usedSecondaryChannels) {
    emberAfCorePrintln("%p network %p: 0x%X",
                       "Form distributed",
                       "complete",
                       EMBER_SUCCESS);
}
```

We have implemented the network formation part upon reset, now we will program its opening to other devices for joining.
-	Edit the networkOpeningEventHandler as follows :

```c
void networkOpeningEventHandler(void) {
    emberEventControlSetInactive(networkOpeningEventControl);
    if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
        emberAfPermitJoin(45,false);
        emberAfPluginFindAndBindTargetStart(WINDOW_COVERING_ENDPOINT);
    }
}
```

-	Edit the emberAfHalButtonIsrCallback as follows:

```c
void emberAfHalButtonIsrCallback(int8u button, int8u state) {
    if (state == BUTTON_RELEASED) {
        emberEventControlSetActive(networkOpeningEventControl);
    }
}
```

-	Finally, we will output the ZCL commands received by a remote :

```c
/** @brief Window Covering Cluster Window Covering Down Close
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringDownCloseCallback(void) {
    emberAfCorePrintln("Down Close received");
    return false;
}

/** @brief Window Covering Cluster Window Covering Up Open
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringUpOpenCallback(void) {
    emberAfCorePrintln("Up Open received");
    return false;
}

/** @brief Window Covering Cluster Window Covering Stop
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringStopCallback(void) {
    emberAfCorePrintln("Stop received");
    return false;
}
```

-	Build and flash the generated binary. Open a terminal on your kit.
-	Not working? Generate a bootloader project
-	Unreadable output? Retarget Vcom to enable through hardware configurator
-	Now, flash the remote-control binary on a second kit, and open a terminal.
-	Call the following CLI commands on it:

```console
zcl window up
'''

or

'''console
zcl window down
'''

or

'''console
zcl window stop
'''

then

'''console
bsend 1
'''

And look at the output on the motor side
