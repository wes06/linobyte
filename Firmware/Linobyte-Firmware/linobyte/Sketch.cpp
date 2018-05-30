#include <Arduino.h>

#include <Wire.h>
#include "wiring_private.h"
#include <Adafruit_MCP23008.h>


Adafruit_MCP23008 mcp_bits;
Adafruit_MCP23008 mcp_status;

TwoWire displayI2C(&sercom1, 11, 13);

//https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include "PCA9685.h"

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

//Adafruit_PWMServoDriver charDisp0 = Adafruit_PWMServoDriver(&displayI2C, 0x40);

Adafruit_PWMServoDriver charDisp[] =
{
	Adafruit_PWMServoDriver(&displayI2C, 0x40),
	Adafruit_PWMServoDriver(&displayI2C, 0x41),
	Adafruit_PWMServoDriver(&displayI2C, 0x42),
	Adafruit_PWMServoDriver(&displayI2C, 0x44),
	Adafruit_PWMServoDriver(&displayI2C, 0x45),
	Adafruit_PWMServoDriver(&displayI2C, 0x46),
	Adafruit_PWMServoDriver(&displayI2C, 0x47),
	Adafruit_PWMServoDriver(&displayI2C, 0x48)
};





#include "ASCII-16Seg.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void enableChar(int _charToEnable);
void writeCharDisp(uint16_t _charToShow, Adafruit_PWMServoDriver& _charDisp);
//End of Auto generated function prototypes by Atmel Studio


void setup() {

	SerialUSB.begin(500000);
	
	
	mcp_bits.begin(0);
	mcp_status.begin(1);
	
	// i2c for mcp23008
	Wire.setClock(400000);
	
	
	mcp_bits.pinMode(0, INPUT);
	mcp_bits.pinMode(1, INPUT);
	mcp_bits.pinMode(2, INPUT);
	mcp_bits.pinMode(3, INPUT);
	mcp_bits.pinMode(4, INPUT);
	mcp_bits.pinMode(5, INPUT);
	mcp_bits.pinMode(6, INPUT);
	mcp_bits.pinMode(7, INPUT);
	
	mcp_status.pinMode(0, INPUT);
	mcp_status.pinMode(1, INPUT);
	mcp_status.pinMode(2, INPUT);
	mcp_status.pinMode(3, INPUT);
	mcp_status.pinMode(4, INPUT);
	mcp_status.pinMode(5, INPUT);
	mcp_status.pinMode(6, INPUT);
	mcp_status.pinMode(7, INPUT);

	//decoder
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	
	//enable decoder
	digitalWrite(0,HIGH);
	
	displayI2C.begin();
	displayI2C.setClock(400000);
	
	// Assign pins 13 & 11 to SERCOM functionality
	pinPeripheral(11, PIO_SERCOM);
	pinPeripheral(13, PIO_SERCOM);



	//charDisp0.begin();
	charDisp[0].setPWMFreq(1000);
	
}



int decoderDelay = 100;
int charToWrite = 33;

void loop() {
	for (int i = 0; i<8;i++){
		SerialUSB.print(i);
		SerialUSB.print(" being checked...");
		SerialUSB.print("");
		
		enableChar(i);
		delayMicroseconds(15000);
		
		SerialUSB.print(mcp_status.digitalRead(7-i));
		if(mcp_status.digitalRead(7-i)){

			SerialUSB.print("\tAttached: ");
			SerialUSB.write(mcp_bits.readGPIO());
			SerialUSB.print(SixteenSegmentASCII[mcp_bits.readGPIO()-32],BIN);
			/*
			// Array starts with "space", ASCII no 32, hence "-32"
			SixteenSegmentASCII[mcp_bits.readGPIO()-32]
			*/

			SerialUSB.println();
		}
		else{
			SerialUSB.print("\tNot Attached...\r\n");
		}
		delayMicroseconds(15000);
	}


	writeCharDisp(charToWrite, charDisp[0]);
	charToWrite++;
	if(charToWrite == 59) charToWrite = 33;
	delay(200);
	
}



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



/*
LED0	C	3
LED1	L	12
LED2	D2	4
LED3	M	13
LED4	N	14
LED5	D1	5
LED6	E	6
LED7	P	15

LED8	K	11
LED9	F	7
LED10	G	8
LED11	A1	0
LED12	H	9
LED13	J	10
LED14	A2	1
LED15	B	2
*/


//	U	T	S	R	P	N	M	K	H	G	F	E	 D	C	B	A
//	P	N	M	L	K	J	H	G	F	E	D1	D2	C	B	A2	A1
//	15	14	13	12	11	10	9	8	7	6	5	4	3	2	1	0

// mapping from ascii library to hardware layout, i.e.: 0b0000000000000001 == LED 11
const int bitToPCA9685Map [16] = {11,14,15,0,2,5,6,9,10,12,13,8,1,3,4,7};

void writeCharDisp(uint16_t _charToShow, Adafruit_PWMServoDriver& _charDisp){
	for(int i = 0; i < 16; i++){
		if((1 << i) & SixteenSegmentASCII[_charToShow]){
			_charDisp.setPin(bitToPCA9685Map[i],1024,true);
		}
		else{
			_charDisp.setPin(bitToPCA9685Map[i],0,true);
		}
	}
}