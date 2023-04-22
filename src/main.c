#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ch.h>
#include <hal.h>
#include <memory_protection.h>
#include "main.h"
#include "chprintf.h"
#include <usbcfg.h>
#include "leds.h"

#define DOUBLE_BUFFERING

static void serial_start(void){
	static SerialConfig ser_cfg = {
	    115200,
	    0,
	    0,
	    0,
	};

	sdStart(&SD3, &ser_cfg); // UART3.
}
static void timer12_start(void){
    //General Purpose Timer configuration   
    //timer 12 is a 16 bit timer so we can measure time
    //to about 65ms with a 1Mhz counter
    static const GPTConfig gpt12cfg = {
        1000000,        /* 1MHz timer clock in order to measure uS.*/
        NULL,           /* Timer callback.*/
        0,
        0
    };

    gptStart(&GPTD12, &gpt12cfg);
    //let the timer count to max value
    gptStartContinuous(&GPTD12, 0xFFFF);
}
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  chRegSetThreadName("Thread1");
  while (true) {
    chprintf((BaseSequentialStream *)&SD3, "Starting Thread 1 \n");
    set_led(LED1,2);
    chprintf((BaseSequentialStream *)&SD3, "Ending Thread 1 \n");
    chThdSleepMilliseconds(500);
  }
}
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
  (void)arg;
  chRegSetThreadName("Thread2");
  while (true) {
    chprintf((BaseSequentialStream *)&SD3, "Starting Thread 2 \n");
    set_led(LED3,2);
    chprintf((BaseSequentialStream *)&SD3, "Ending Thread 2 \n");
    chThdSleepMilliseconds(500);
  }
}
static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg) {
  (void)arg;
  chRegSetThreadName("Thread3");
  while (true) {
    chprintf((BaseSequentialStream *)&SD3, "Starting Thread 3 \n");
    set_led(LED5,2);
    chprintf((BaseSequentialStream *)&SD3, "Ending Thread 3 \n");
    chThdSleepMilliseconds(500);
  }
}

int main(void) {
  halInit();
  chSysInit();
  mpu_init();
  serial_start();
  timer12_start();
  usb_start();
  
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO-1, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO-2, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO-3, Thread3, NULL);

  while (true) {
    chprintf((BaseSequentialStream *)&SD3, "Starting Thread main \n");
    set_led(LED7,2);
    chprintf((BaseSequentialStream *)&SD3, "Ending Thread main \n");
    chThdSleepMilliseconds(500);
  }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}


/*
    chSysLock();
    volatile uint16_t time = 0;
    GPTD12.tim->CNT = 0;

    // function
    
    time = GPTD12.tim->CNT;
    chprintf((BaseSequentialStream *)&SD3, "time 3 = %d \n",time);
    chSysUnlock();
*/

// REMEMBER CH_CFG_TIME_QUANTUM WAS SET TO 0