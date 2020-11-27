/***************************************************************************//**
 * @file
 * @brief Callback implementation for ZigbeeMinimal sample application.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"

#include EMBER_AF_API_NETWORK_STEERING
#include EMBER_AF_API_NETWORK_CREATOR
#include EMBER_AF_API_NETWORK_CREATOR_SECURITY
#include EMBER_AF_API_FIND_AND_BIND_TARGET



#define WINDOW_COVERING_ENDPOINT (1)



EmberEventControl networkManagementEventControl;
EmberEventControl networkOpeningEventControl;




void networkManagementEventHandler(void);
void networkOpeningEventHandler(void);



void networkOpeningEventHandler(void) {
    emberEventControlSetInactive(networkOpeningEventControl);
    if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
        emberAfPermitJoin(45,false);
        emberAfPluginFindAndBindTargetStart(WINDOW_COVERING_ENDPOINT);
    }
}

void networkManagementEventHandler(void) {
     emberEventControlSetInactive(networkManagementEventControl);
     if (emberAfNetworkState() != EMBER_JOINED_NETWORK) {
        EmberStatus status = emberAfPluginNetworkCreatorStart(false);
        emberAfCorePrintln("%p network %p: 0x%X", "Form", "start", status);
     }
}

/** @brief Hal Button Isr
 *
 * This callback is called by the framework whenever a button is pressed on the
 * device. This callback is called within ISR context.
 *
 * @param button The button which has changed state, either BUTTON0 or BUTTON1
 * as defined in the appropriate BOARD_HEADER.  Ver.: always
 * @param state The new state of the button referenced by the button parameter,
 * either ::BUTTON_PRESSED if the button has been pressed or ::BUTTON_RELEASED
 * if the button has been released.  Ver.: always
 */
void emberAfHalButtonIsrCallback(int8u button,
                                 int8u state)
{
    if (state == BUTTON_RELEASED) {
        emberEventControlSetActive(networkOpeningEventControl);
    }
}


/** @brief Main Init
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup. Any
 * code that you would normally put into the top of the application's main()
 * routine should be put into this function. This is called before the clusters,
 * plugins, and the network are initialized so some functionality is not yet
 * available.
        Note: No callback in the Application Framework is
 * associated with resource cleanup. If you are implementing your application on
 * a Unix host where resource cleanup is a consideration, we expect that you
 * will use the standard Posix system calls, including the use of atexit() and
 * handlers for signals such as SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If
 * you use the signal() function to register your signal handler, please mind
 * the returned value which may be an Application Framework function. If the
 * return value is non-null, please make sure that you call the returned
 * function from your handler to avoid negating the resource cleanup of the
 * Application Framework itself.
 *
 */
void emberAfMainInitCallback(void)
{
    emberEventControlSetActive(networkManagementEventControl);
}


/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be notified
 * of changes to the stack status and take appropriate action.  The return code
 * from this callback is ignored by the framework.  The framework will always
 * process the stack status after the callback returns.
 *
 * @param status   Ver.: always
 */
bool emberAfStackStatusCallback(EmberStatus status)
{
  // This value is ignored by the framework.
  return false;
}

/** @brief Complete
 *
 * This callback is fired when the Network Steering plugin is complete.
 *
 * @param status On success this will be set to EMBER_SUCCESS to indicate a
 * network was joined successfully. On failure this will be the status code of
 * the last join or scan attempt. Ver.: always
 * @param totalBeacons The total number of 802.15.4 beacons that were heard,
 * including beacons from different devices with the same PAN ID. Ver.: always
 * @param joinAttempts The number of join attempts that were made to get onto
 * an open Zigbee network. Ver.: always
 * @param finalState The finishing state of the network steering process. From
 * this, one is able to tell on which channel mask and with which key the
 * process was complete. Ver.: always
 */
void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState)
{
  emberAfCorePrintln("%p network %p: 0x%X", "Join", "complete", status);
}


/** @brief Complete
 *
 * This callback notifies the user that the network creation process has
 * completed successfully.
 *
 * @param network The network that the network creator plugin successfully
 * formed. Ver.: always
 * @param usedSecondaryChannels Whether or not the network creator wants to
 * form a network on the secondary channels Ver.: always
 */
void emberAfPluginNetworkCreatorCompleteCallback(const EmberNetworkParameters *network,
                                                 bool usedSecondaryChannels)
{
    emberAfCorePrintln("%p network %p: 0x%X",
                       "Form distributed",
                       "complete",
                       EMBER_SUCCESS);
}




/** @brief Window Covering Cluster Window Covering Down Close
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringDownCloseCallback(void)
{
	emberAfCorePrintln("Down Close received");
    return false;
}

/** @brief Window Covering Cluster Window Covering Stop
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringStopCallback(void)
{
	emberAfCorePrintln("Stop received");
	return false;
}

/** @brief Window Covering Cluster Window Covering Up Open
 *
 *
 *
 */
boolean emberAfWindowCoveringClusterWindowCoveringUpOpenCallback(void)
{
    emberAfCorePrintln("Up Open received");
	return false;
}
