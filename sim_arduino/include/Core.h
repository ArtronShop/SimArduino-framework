#ifdef __cplusplus
extern "C" {
#endif
	#include <stdlib.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <stddef.h>
	#include <stdarg.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	
	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "esp_system.h"
	#include "nvs_flash.h"
	#include "driver/gpio.h"
	#include "sdkconfig.h"
	#include "rom/ets_sys.h"
	#include <stdlib.h>
#ifdef __cplusplus
}
#endif

#include "WCharacter.h"
#include "WString.h"
#include "Stream.h"

#define F_CPU 40000000L

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

void pinMode(int pin, int mode) ;
void digitalWrite(int pin, int level) ;
int digitalRead(int pin) ;
void delay(unsigned long ms) ;
void delayMicroseconds(unsigned int us) ;
unsigned long millis() ;
unsigned long micros() ;

typedef uint8_t boolean;
typedef uint8_t byte;

void setup(void) ;
void loop(void) ;
