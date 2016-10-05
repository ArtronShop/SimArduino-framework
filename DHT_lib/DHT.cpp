// #define DEBUG_Lib
// #define DEBUG_OUTPUT Serial

#include "DHT.h"

DHT::DHT() {

}

bool DHT::read(int pin, int type) {
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(20);
	pinMode(pin, INPUT_PULLUP);

	int timeCount=0;
	while(digitalRead(pin) == HIGH && timeCount<255) {
		timeCount++;
		delayMicroseconds(1);
	}

	if (timeCount<255) {
		for (int i=0;i<41;i++) {
			timeCount=0;
			while(digitalRead(pin) == LOW) ;
			while(digitalRead(pin) != LOW && timeCount < 255) {
				timeCount++;
				delayMicroseconds(1);
			}

			if (timeCount >= 255)
				break;

			if (i>0 && i<42) {
				tmpData[(i-1) / 8] <<= 1;
				tmpData[(i-1) / 8] |= (timeCount>40 ? 1 : 0);
			}
		}
	}

#ifdef DEBUG_Lib
    printf("timeCount: %d\r\n", timeCount);
    printf("tmpData[0]: 0x%x\r\n", tmpData[0]);
    printf("tmpData[1]: 0x%x\r\n", tmpData[1]);
    printf("tmpData[2]: 0x%x\r\n", tmpData[2]);
	printf("tmpData[3]: 0x%x\r\n", tmpData[3]);
	printf("tmpData[4]: 0x%x\r\n", tmpData[4]);
	printf("\r\n");
#endif

	if (timeCount >= 255 || (tmpData[4] != ((tmpData[0] + tmpData[1] + tmpData[2] + tmpData[3])&0xFF))) {
		tempC = tempF = humidity = 0;
		return false;
	}


	switch (type) {
		case TYPE_DHT11:
		case TYPE_DHT12:
			humidity = tmpData[0];
			tempC = tmpData[2];
			break;
	    case TYPE_DHT22:
	    case TYPE_DHT21:
	    	humidity = tmpData[0];
	    	humidity *= 256;
	    	humidity += tmpData[1];
	    	humidity *= 0.1;

	    	tempC = tmpData[2] & 0x7F;
	    	tempC *= 256;
	    	tempC += tmpData[3];
	    	tempC *= 0.1;
	    	if (tmpData[2] & 0x80) tempC *= -1;
	}
	tempF =  tempC * 9.0 / 5.0 + 32.0;

	return true;
}