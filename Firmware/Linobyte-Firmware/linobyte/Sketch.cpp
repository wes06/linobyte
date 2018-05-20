#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MCP23008.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void enableChar(int _charToEnable);
//End of Auto generated function prototypes by Atmel Studio

Adafruit_MCP23008 mcp;


void setup() {

	SerialUSB.begin(500000);
	
	
	mcp.begin(0);

	mcp.pinMode(0, INPUT);
	mcp.pinMode(1, INPUT);
	mcp.pinMode(2, INPUT);
	mcp.pinMode(3, INPUT);
	mcp.pinMode(4, INPUT);
	mcp.pinMode(5, INPUT);
	mcp.pinMode(6, INPUT);
	mcp.pinMode(7, INPUT);

	//decoder
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	//enable decoder
	digitalWrite(0,HIGH);
}



int decoderDelay = 100;

void loop() {
	for (int i = 0; i<8;i++){
		enableChar(i);
		delay(200);
		SerialUSB.print(mcp.digitalRead(0));
		SerialUSB.print(mcp.digitalRead(1));
		SerialUSB.print(mcp.digitalRead(2));
		SerialUSB.print(mcp.digitalRead(3));
		SerialUSB.print(mcp.digitalRead(4));
		SerialUSB.print(mcp.digitalRead(5));
		SerialUSB.print(mcp.digitalRead(6));
		SerialUSB.print(mcp.digitalRead(7));
		SerialUSB.println();
		delay(100);
	}

}


//https://github.com/NachtRaveVL/PCA9685-Arduino/blob/master/examples/SimpleExample/SimpleExample.ino



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
