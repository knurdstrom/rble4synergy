# Introduction #
The source and patches provided in this repository are designed to allow the use of the RBLE stack with any Synergy Microcontroller.
The patches provided ensure that no dependency is created on the ThreadX RTOS (unlike the BLE Framework) enabling use on the S124 MCU.

The instructions below assume that the user is well-versed with operating the e2studio (eclipse) environment.

# Patching the RBLE Stack for Synergy #
Follow the procedure below to update your RBLE stack to v1.21. Note that *X* is the major version number and *YY* is the minor version number of the RBLE stack downloaded from the Renesas website.

## Common Steps ##

1. Copy the rBLE folder from ```BLE_Software_Ver_X_YY\Renesas\BLE_Software_Ver_X_YY\BLE_Sample\src``` to your destination project.
2. Copy the **deps** folder distributed with this archive into the rBLE folder in the destination project.
3. Copy the ```vXpYY.diff``` patch file distributed with this archive into the rBLE folder in the destination project. The directory structure of rBLE should now look like: 

```

    .
    +-- deps
    +-- src
    +-- v1p11.diff

    2 directories, 1 file
```

## Using bash terminal ##
1. Open a bash terminal (such as cygwin) and navigate into the rBLE directory created using the Common Steps defined above.
2. Input the command ``` patch -p2 < vXpYY.diff ``` to patch the files.

## Using e2studio ##
1. Copy the rBLE folder created in Common Steps in to your target Synergy project under ```src```.
2. Open the Synergy Project in e2studio and navigate to ```src/rBLE``` using the Project Explorer tab.
3. Right-click on the src folder and select *Team > Apply Patch*.
4. Select the vXpYY.diff patch file located under the **Synergy Project\src\rBLE folder**. And select Next.
6. Choose the Synergy project in the Target Resource and select Next.
7. Change the **Ignore leading path name segments** value such that the patch contents no longer shows the **file does not exist** error. (The value should be 3).
8. Select Finish to finish patching.
9. Delete **Synergy Project\src\rBLE\src\sample_app** folder.


## Verification ##
1. Open **Synergy Project\src\rBLE\src\include\rble.h** and verify that the RBLE major and minor number is 0x01 and 0x21 respectively.

# Building the project #
After patching and adding the the rBLE source code to a Synergy Project, use the steps below before proceeding to build the project.
## Compiler Includes ##
Add the following paths to the compiler include paths

    "${workspace_loc:/${ProjName}/src/rBLE/src/include}"
    "${workspace_loc:/${ProjName}/src/rBLE/src/include/host}"
    "${workspace_loc:/${ProjName}/src/rBLE/src/rscip}"
    "${workspace_loc:/${ProjName}/src/rBLE/src/sample_profile}"
    "${workspace_loc:/${ProjName}/src/rBLE/deps}"
    "${workspace_loc:/${ProjName}/src/rBLE/deps/serial}"
    "${workspace_loc:/${ProjName}/src/rBLE/deps/timer}"
    "${workspace_loc:/${ProjName}/src/rBLE/deps/logger}"
	
## Configure dependencies ##
The RBLE stack requires one instance of the following:

1. UART Driver with the following settings:
	- The baud rate configured to match the settings made for the RL78/G1D project. Typically 4800-8N1.
	- The callback function set to ```ble_uart_callback``` (defined in uart.c).
2. A periodic (General Purpose) Timer with the following settings:
	- The callback function set to ```rBLE_timer_isr``` (defined in timer.c).
	- Periodic interrupt interval set to **10ms**.
    
## Bluetooth Developer Studio Generated output ##
1. Create the folder ```${ProjName}/src/rBLE/src/sample_profile/sam```
2. Follow the instructions in [r20an0400ej0200-g1dbdsp.pdf](https://www.renesas.com/en-us/software/D6001494.html) for Code Generation.
3. Copy the files below to folder created in step 1.
	- sams.c
	- sams.h
	- sam.h
4. Copy db_handle.h and place it under ```${ProjName}/src/rBLE/src/sample_profile```
5. Use the API provided under sams.h to complete the operation of your application.

## Copy Sample Application ##
1. Copy the folder ```sample_app``` from the archive and add it to ```${ProjName}/src/rBLE/src```.

# Typical Usage #

The following is an example usage of the API provided by the modified RBLE Host Stack. Include **rble_host.h** in the C-File.

    extern RBLE_STATUS RBLE_Init_Timer(void * p_arg);
    extern bool APP_Init(void * p_uart);
    extern RBLE_STATUS APP_Run( void );
    extern const timer_instance_t g_timer_ble;
    extern const uart_instance_t g_uart_ble;
    
    /* 
     * TODO: 
     * Provide an instance which connects to RL78/G1D (use SSP configurator to match baud rate settings) 
     */
    uart_instance_t const * const p_uart_ble = &g_uart_ble;

    /** 1. Initialize the RBLE Modem on the PMOD Interface */
    {
        /* Reset the Modem */
        g_ioport_on_ioport.pinWrite(RL78G1D_TOOL0, IOPORT_LEVEL_HIGH);
        g_ioport_on_ioport.pinWrite(RL78G1D_RESET, IOPORT_LEVEL_LOW);
        R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
        g_ioport_on_ioport.pinWrite(RL78G1D_RESET, IOPORT_LEVEL_HIGH);

        /* Wait for Reset to complete */
        R_BSP_SoftwareDelay(3, BSP_DELAY_UNITS_SECONDS);
    }
    
    /** 2. Initialize a 10ms Periodic RBLE Timer to control timing for the stack */
    rble_status = RBLE_Init_Timer((void*)&g_timer_ble);

    if(RBLE_OK==rble_status)
    {
        /** 3. Initialize the Application and the RBLE Host stack */
        rble_status = (true==APP_Init(p_uart_ble)) ? RBLE_OK:RBLE_ERR;
    }

    while(RBLE_OK!=rble_status)
    {
        /* Wait here if initialization fails */
        ;
    }   
    
    while(1)
    {
        /** 4. Run pending actions needed for the Application */
        rble_status = APP_Run();

        /** 5. Exchange information to the Modem over the UART */
        rble_status = rBLE_Run();
    }