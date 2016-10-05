/* 
  Thanks, code from https://github.com/feelfreelinux/ds18b20 
*/

#include "DS18B20.h"

DS18B20::DS18B20()
{

}

void DS18B20::send(char bit){
	pinMode(DS_GPIO, OUTPUT);
	digitalWrite(DS_GPIO, LOW);
	delayMicroseconds(5);
	if(bit==1) digitalWrite(DS_GPIO, HIGH);
	delayMicroseconds(80);
	digitalWrite(DS_GPIO, HIGH);
}
unsigned char DS18B20::read(void){
	unsigned char PRESENCE=0;
	pinMode(DS_GPIO, OUTPUT);
	digitalWrite(DS_GPIO, LOW);
	delayMicroseconds(2);
	digitalWrite(DS_GPIO, HIGH);
	delayMicroseconds(15);
	pinMode(DS_GPIO, INPUT_PULLUP);
	if(digitalRead(DS_GPIO)==1){PRESENCE=1;}else{PRESENCE=0;}
	return(PRESENCE);
}
void DS18B20::send_byte(char data){
	unsigned char i;
	unsigned char x;
	for(i=0;i<8;i++){
		x = data>>i;
		x &= 0x01;
		send(x);
	}
	delayMicroseconds(100);
}

unsigned char DS18B20::read_byte(void){
	unsigned char i;
	unsigned char data = 0;
	for (i=0;i<8;i++) {
		if(read()) data|=0x01<<i;
		delayMicroseconds(15);
	}
	return(data);
}

unsigned char DS18B20::RST_PULSE(void){
	unsigned char PRESENCE;
	pinMode(DS_GPIO, OUTPUT);
	digitalWrite(DS_GPIO, LOW);
	delayMicroseconds(500);
	digitalWrite(DS_GPIO, HIGH);
	pinMode(DS_GPIO, INPUT_PULLUP);
	delayMicroseconds(30);
	if(digitalRead(DS_GPIO)==0){PRESENCE=1;}else{PRESENCE=0;}
	delayMicroseconds(470);
	if(digitalRead(DS_GPIO)==1){PRESENCE=1;}else{PRESENCE=0;}
	return PRESENCE;
}

float DS18B20::get_temp(int pin) {
	DS_GPIO = pin;
	unsigned char check;
	char temp1=0, temp2=0;
	check=RST_PULSE();
	if(check==1) {
		send_byte(0xCC);
		send_byte(0x44);
		delay(750);
		check=RST_PULSE();
		send_byte(0xCC);
		send_byte(0xBE);
		temp1=read_byte();
		temp2=read_byte();
		check=RST_PULSE();
		float temp=0;
		temp=(float)(temp1+(temp2*256))/16;
		return temp;
	}
	else{return 0;}
}
