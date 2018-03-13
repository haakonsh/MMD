# Monitor Mode Debugging in Keil5

## Introduction
Monitor Mode Debugging enables you to halt and step through low priority code whilst letting high priority code execute as normal. With MMD you can debug your application while maintaining a BLE connection. 

Requirements:
* nRF5_SDK14.2
* nRF52DK (PCA10040)
* Keil µVision5
* nRF Connect (mobile or computer)


## What exactly is MMD?
Monitor Mode Debugging is essentially an interrupt service routine that contains an infinite loop. The MMD ISR has an execution priority equeal to or higher than your application, but lower than the code you want to run unimpeded. When the CPU receives a halt command from the debugger, it will execute the MMD ISR instead of halting, preempting the application code. While the CPU is busy running the MMD ISR (infinite loop), code with higher execution priority (SoftDevice, drivers, etc) can preempt the MMD ISR, but lower execution priority code (main application, libraries, etc) cannot.

When single stepping through code, a debugger will insert a breakpoint after each step. This means that MMD can also handle stepping through code of equal or lower priority without preempting higher priority calls. 


## Okay that sounds great, but i'm still not convinced that this is useful for me
I've made an example that will demonstrate the usefulness of MMD:

Steps:
1. Unzip/clone into SDK14.2/examples/ble_peripheral

2. Open the keil project file [ble_app_blinky_pca10040_s132.uvprojx](pca10040/s132/arm5_no_packs/ble_app_blinky_pca10040_s132.uvprojx)

3. Compile the example (F7).

4. Erase and flash an nRF52DK with 's132_nrf52_5.0.0_softdevice.hex' found in SDK14.2\components\softdevice\s132\hex

5. Flash the application to the nRF52DK via Keil (F8). 
NOTE: When prompted with the dialog box 'Monitor Mode missing license' you need to press 'No'. This is done to prevent the J-link driver to enter MMD when flashing the application. You can also flash the application through nrfjprog without any modification. 
![JlinkPromptNo](Documentation/Images/JLinkPromptNo.png " ")

6. Enter debug mode (ctrl+F5).
NOTE: When prompted with the dialog box 'Monitor Mode missing license' you need to press 'Yes'. 
![JlinkPromptYes](Documentation/Images/JLinkPromptYes.png " ")

7. Start code execution (F5).

8. Open nRF Connect and connect to 'NORDIC_BLINKY'. Expand the 'Nordic LED Button Service' and enable notifications for the Button characteristics (press the three downward pointing arrows button).

9. Press 'Button 1' on the nRF52DK and verify that the Button characteristic's Value field appears and changes value from 'Button pressed' to 'Button released' when pushing the button.

10. Stop code execution.

11. Verify that the button value in nRF Connect does not change when pressing 'Button 1'

12. Start code execution and verify that the value in nRF Connect now changes when pressing 'Button 1'. 

13. You have now verified that the BLE link remained intact despite halting the CPU. 

14. Feel free to play around with the LED and single stepping through application code. Now you can finnaly figure out what your BLE service is actually doing without losing the BLE link ^^


## Hey that really is neat, but how do I implement MMD in my project?
The differences between this example and the standard ble_app_blinky demo are listed below:

1. You need to compile the MMD ISR found in [JLINK_MONITOR_ISR_ARM.s](pca10040/s132/arm5_no_packs/JLINK_MONITOR_ISR_ARM.s)

2. You need to stop the app_timer (and feed a watchdog if needed) with the MMD utility functions that the assembly codeed ISR refers to in [JLINK_MONITOR.c](JLINK_MONITOR.c) and [JLINK_MONITOR.h](JLINK_MONITOR.h)

3. Enable MMD in the J-link driver: see line 10 and 11 in [JLinkSettings.ini](pca10040/s132/arm5_no_packs/JLinkSettings.ini)

## Wait, that's it!?
Youp, that's it!|

Happy debugging!

