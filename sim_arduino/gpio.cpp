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

void pinMode(int pin, int mode) {
	// printf("in pinMode\r\n");
	// gpio_pad_select_gpio(static_cast<gpio_num_t>(pin));
	// gpio_pad_select_gpio((gpio_num_t)5);
	// gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_OUTPUT);
	if (mode == INPUT_PULLUP) {
		gpio_set_pull_mode(static_cast<gpio_num_t>(pin), GPIO_PULLUP_ONLY);
		gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_INPUT);
	} else if (mode == INPUT_PULLDOWN) {
		gpio_set_pull_mode(static_cast<gpio_num_t>(pin), GPIO_PULLDOWN_ONLY);
		gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_INPUT);
	} else if (mode == INPUT || mode == OUTPUT) {
		gpio_set_pull_mode(static_cast<gpio_num_t>(pin), GPIO_FLOATING);
		gpio_set_direction(static_cast<gpio_num_t>(pin), (mode == OUTPUT) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT);
	}
}

void digitalWrite(int pin, int level) {
	// printf("in digitalWrite\r\n");
	gpio_set_level(static_cast<gpio_num_t>(pin), static_cast<gpio_level_t>(level));
}

int digitalRead(int pin) {
	// printf("in digitalRead\r\n");
	return gpio_get_level(static_cast<gpio_num_t>(pin));
}

void delay(long ms) {
	vTaskDelay(ms / portTICK_RATE_MS);
	// ets_delay_us(ms * 1000);
}

void delayMicroseconds(long us) {
	ets_delay_us(us);
}