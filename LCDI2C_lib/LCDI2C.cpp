/*
   Name: LCDI2C
   File: LCDI2C.cpp
   Author: IOXhop
   Website: http://www.ioxhop.com/
*/

#include "LCDI2C.h"

LCDI2C::LCDI2C(int addr) {
	_dev_addr = addr;
}

LCDI2C::LCDI2C(int addr, int pinSCL, int pinSDA) {
	_dev_addr = addr;
	_pinSCL = pinSCL;
	_pinSDA = pinSDA;
	
}

void LCDI2C::SEND(byte data) {
	Wire.beginTransmission(_dev_addr);
    Wire.write((BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data);
	// delay(1);
	Wire.write(BIT_EN | (BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data);
	// delay(1);
    Wire.write((BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data);
	Wire.endTransmission();
}

void LCDI2C::CMD(byte data) {
	PIN_RS = false;
	SEND(data&0xF0);
	SEND((data<<4)&0xF0);
	PIN_RS = true;
}

void LCDI2C::begin(int len, int line) {
	Wire.begin(_pinSCL, _pinSDA);
	delay(10);
	
	for (int i=0;i<3;i++)
		SEND(0x30);
	for (int i=0;i<2;i++)
		SEND(0x20);
	SEND(0x10);
	SEND(0);
		
	SEND(0x08 | (BLINK ? BIT_BLINK : 0) | (CURSOR ? BIT_CURSOR : 0) | (sDISPLAY ? BIT_DISPLAY : 0));
	CMD(0x28);

	clear();
	
	upCr();
	_w = len;
	_h = line;
}

void LCDI2C::write(byte data) {
	PIN_RS = true;
	SEND(data&0xF0);
	SEND((data<<4)&0xF0);
}

void LCDI2C::print(String text) {
	int len = text.length();
	for (int i=0;i<len;i++) {
		write(text.charAt(i));
	}
}

void LCDI2C::print(char ch) {
	write(ch);
}

void LCDI2C::print(char arr[]) {
	int i = 0;
	while(arr[i] != '\0') {
		write(arr[i]);
		i++;
	}
}

void LCDI2C::print(int number) {
	print(String(number));
}

void LCDI2C::print(long number) {
	print(String(number));
}

void LCDI2C::print(double number) {
	print(String(number));
}

void LCDI2C::clear() {
	CMD(0x01);
}

void LCDI2C::setCursor(int x, int y) {
	byte toCode[] = { 0x80, 0xC0, 0x94, 0xD4 };
	CMD(toCode[y] + x);
}

void LCDI2C::setCursor(int pos) {
	setCursor(pos % _w, pos / _w);
}


void LCDI2C::scrollDisplayLeft() {
	CMD(0x18);
}
	
void LCDI2C::scrollDisplayRight() {
	CMD(0x1C);
}

void LCDI2C::cursor() {
	CURSOR = true;
	upCr();
}

void LCDI2C::noCursor() {
	CURSOR = false;
	upCr();
}

void LCDI2C::blink() {
	BLINK = true;
	upCr();
}

void LCDI2C::noBlink() {
	BLINK = false;
	upCr();
}

void LCDI2C::display() {
	sDISPLAY = true;
	upCr();
}

void LCDI2C::noDisplay() {
	sDISPLAY = false;
	upCr();
}

void LCDI2C::blacklight() {
	BLACKLIGHT = true;
	CMD(0);
}

void LCDI2C::noBlacklight() {
	BLACKLIGHT = false;
	CMD(0);
}

void LCDI2C::upCr() {
	PIN_RS = false;
	CMD(0x08 | (BLINK ? BIT_BLINK : 0) | (CURSOR ? BIT_CURSOR : 0) | (sDISPLAY ? BIT_DISPLAY : 0));
}

