/* 
  Thanks, code from https://github.com/feelfreelinux/ds18b20 
*/

#ifndef DS18B20_h
#define DS18B20_h

#include "Core.h"

class DS18B20
{
	private:
		int DS_GPIO;
		
		void send_byte(char data) ;
		unsigned char read(void) ;
		void send(char bit) ;
		unsigned char read_byte(void) ;
		unsigned char RST_PULSE(void) ;
	  
	public:
		DS18B20() ;
		float get_temp(int pin) ;

};

#endif
