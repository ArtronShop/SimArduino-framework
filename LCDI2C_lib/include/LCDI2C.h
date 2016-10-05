/*
   Name: LCDI2C
   File: LCDI2C.h
   Author: IOXhop
   Website: http://www.ioxhop.com/
*/

// #include <Arduino.h>
#include "Core.h"
#include <Wire.h>

class LCDI2C {
	public:
	
		LCDI2C(int addr);
		LCDI2C(int addr, int pinSCL, int pinSDA);
		
		void begin(int len, int line) ;
		
		void clear() ;
		void write(byte data) ;
		void print(String text) ;
		void print(char ch) ;
		void print(char arr[]) ;
		void print(int number) ;
		void print(long number) ;
		void print(double number) ;
		
		void setCursor(int x, int y) ;
		void setCursor(int pos) ;
		void scrollDisplayLeft() ;
		void scrollDisplayRight() ;
		
		void cursor() ;
		void noCursor() ;
		void blink() ;
		void noBlink() ;
		void display() ;
		void noDisplay() ;
		void blacklight() ;
		void noBlacklight() ;
		
		void createChar(int id, byte data[]) ;
		
	private:
		int _pinSCL = 4;
		int _pinSDA = 5;
		int _dev_addr = 0;
		int _w = 16;
		int _h = 2;
		
		bool PIN_RS = false;
		
		int BIT_EN = 0x04;
		int BIT_RS = 0x01;
		int BIT_BLACKLIGHT = 0x08;
		
		int BIT_BLINK = 0x01;
		int BIT_CURSOR = 0x02;
		int BIT_DISPLAY = 0x04;
		
		bool BLINK = false;
		bool CURSOR = false;
		bool sDISPLAY = true;
		bool BLACKLIGHT = true;
		
		
		void SEND(byte data) ;
		void CMD(byte data) ;
		void upCr() ;
}
;
