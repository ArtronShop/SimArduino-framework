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