#include "Core.h"

#define TYPE_DHT11 1
#define TYPE_DHT12 2
#define TYPE_DHT21 3
#define TYPE_DHT22 4

class DHT {
	public:
		float tempC = 0, tempF = 0, humidity = 0;
		
		DHT();
		bool read(int pin, int type) ;
		
	private:
		char tmpData[5] = {0, 0, 0, 0, 0};
}
;