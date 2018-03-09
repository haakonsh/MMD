/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2015  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
 
----------------------------------------------------------------------
File    : JLINK_MONITOR.c
Purpose : Implementation of debug monitor for J-Link monitor mode debug on Cortex-M devices.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "JLINK_MONITOR.h"
#include "app_timer.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

volatile int MAIN_MonCnt;   // Incremented in JLINK_MONITOR_OnPoll() while CPU is in debug mode

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

#if CONFIG_JLINK_MONITOR_ENABLED
STATIC_ASSERT(APP_TIMER_KEEPS_RTC_ACTIVE);


/********************************************************************* 
* 
*       JLINK_MONITOR_OnExit()
* 
*  Function description 
*    Called from DebugMon_Handler(), once per debug exit.
*    May perform some target specific operations to be done on debug mode exit.
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/ 
void JLINK_MONITOR_OnExit(void) {
  //
  // Add custom code here
  //
    app_timer_resume();
//  BSP_ClrLED(0);
}

/********************************************************************* 
* 
*       JLINK_MONITOR_OnEnter()
* 
*  Function description 
*    Called from DebugMon_Handler(), once per debug entry.
*    May perform some target specific operations to be done on debug mode entry
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/ 
void JLINK_MONITOR_OnEnter(void) {
  //
  // Add custom code here
  //
    app_timer_pause();
//  BSP_SetLED(0);
//  BSP_ClrLED(1);
}

/********************************************************************* 
* 
*       JLINK_MONITOR_OnPoll()
* 
*  Function description 
*    Called periodically from DebugMon_Handler(), to perform some actions that need to be performed periodically during debug mode.
* 
*  Notes 
*    (1) Must not keep the CPU busy for more than 100 ms
*/
void JLINK_MONITOR_OnPoll(void) {
  //
  // Add custom code here
  //
#if CONFIG_WATCHDOG_ENABLED
    nrf_drv_wdt_channel_feed(s_watchdog_channel);
#endif

  MAIN_MonCnt++;
//  BSP_ToggleLED(0);
//  _Delay(500000);
}
#endif
/****** End Of File *************************************************/
