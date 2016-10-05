extern "C" {
	#include <stdio.h>
	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "rom/ets_sys.h"
	#include "esp_system.h"
	#include "nvs_flash.h"
	#include "driver/gpio.h"
	#include "sdkconfig.h"
}
#include "Core.h"

extern void loop() ;
extern void setup() ;

static void __loopCore_task(void *pvParameter) {
	setup();
	while(1) {
		loop();
	}
}

extern "C" void app_main(void) {
    nvs_flash_init();
    system_init();
    xTaskCreate(&__loopCore_task, "__loopCore_task", 2048, NULL, 5, NULL);
}