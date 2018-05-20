/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//#include <ZPCA9685.h>

//#include <Adafruit_MCP23008.h>
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio



void enableChar(int _charToEnable){
	
	switch (_charToEnable)
	{
		case 0:
		digitalWrite(1,LOW); // A0
		digitalWrite(3,LOW); // A1
		digitalWrite(4,LOW); // A2
		break;
		case 1:
		digitalWrite(1,HIGH); // A0
		digitalWrite(3,LOW); // A1
		digitalWrite(4,LOW); // A2
		break;
		case 2:
		digitalWrite(1,LOW); // A0
		digitalWrite(3,HIGH); // A1
		digitalWrite(4,LOW); // A2
		break;
		case 3:
		digitalWrite(1,HIGH); // A0
		digitalWrite(3,HIGH); // A1
		digitalWrite(4,LOW); // A2
		break;
		case 4:
		digitalWrite(1,LOW); // A0
		digitalWrite(3,LOW); // A1
		digitalWrite(4,HIGH); // A2
		break;
		case 5:
		digitalWrite(1,HIGH); // A0
		digitalWrite(3,LOW); // A1
		digitalWrite(4,HIGH); // A2
		break;
		case 6:
		digitalWrite(1,LOW); // A0
		digitalWrite(3,HIGH); // A1
		digitalWrite(4,HIGH); // A2
		break;
		case 7:
		digitalWrite(1,HIGH); // A0
		digitalWrite(3,HIGH); // A1
		digitalWrite(4,HIGH); // A2
		break;
	}
	
}


void setup() {
	// put your setup code here, to run once:
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	
	digitalWrite(0,HIGH);
}

int decoderDelay = 100;

void loop() {
	// put your main code here, to run repeatedly:
	for (int i = 0; i<8;i++){
		enableChar(i);
		delay(100);
	}
	
}



