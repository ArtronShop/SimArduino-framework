#ifdef __cplusplus
extern "C" {
#endif
	#include <stdio.h>
	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "esp_system.h"
	#include "nvs_flash.h"
	#include "driver/gpio.h"
	#include "sdkconfig.h"
	#include "rom/ets_sys.h"
#ifdef __cplusplus
}
#endif

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

void pinMode(int pin, int mode) ;
void digitalWrite(int pin, int level) ;
int digitalRead(int pin) ;
void delay(long ms) ;
void delayMicroseconds(long us) ;

void setup(void) ;
void loop(void) ;
