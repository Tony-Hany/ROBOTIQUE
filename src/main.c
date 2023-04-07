#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
#include <main.h>

#include "leds.h"

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  chRegSetThreadName("Thread1");
  while (true) {
    //Operation block requires (100ms)
    chThdYield();
  }
}
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
  (void)arg;
  chRegSetThreadName("Thread2");
  while (true) {
    //Operation block requires (50ms)
    chThdYield();
  }
}
static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg) {
  (void)arg;
  chRegSetThreadName("Thread3");
  while (true) {
    //Operation block requires (150ms)
    chThdYield();
  }
}
int main(void) {
  halInit();
  chSysInit();
  mpu_init();

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
 
  while (true) {
    //Operation block requires (200ms)
    chThdYield();
  }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
