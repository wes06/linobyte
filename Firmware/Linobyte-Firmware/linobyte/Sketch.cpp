#include <Arduino.h>

#include <Wire.h>
#include "wiring_private.h"
#include <Adafruit_MCP23008.h>
#include "PCA9685.h"

#include "ASCII-16Seg.h"

Adafruit_MCP23008 mcp_bits;
Adafruit_MCP23008 mcp_status;

TwoWire displayI2C(&sercom1, 11, 13);

Adafruit_PWMServoDriver charDisp[] =
{
	Adafruit_PWMServoDriver(&displayI2C, 0x60),
	Adafruit_PWMServoDriver(&displayI2C, 0x61),
	Adafruit_PWMServoDriver(&displayI2C, 0x62),
	Adafruit_PWMServoDriver(&displayI2C, 0x63),
	Adafruit_PWMServoDriver(&displayI2C, 0x64),
	Adafruit_PWMServoDriver(&displayI2C, 0x65),
	Adafruit_PWMServoDriver(&displayI2C, 0x66),
	Adafruit_PWMServoDriver(&displayI2C, 0x67)
};







//function prototypes
void enableChar(int _charToEnable);
void writeCharDisp(uint16_t _charToShow, Adafruit_PWMServoDriver& _charDisp, uint16_t _brightness);
void writeCharDisp_Off(Adafruit_PWMServoDriver& _charDisp);

EPortType port1;
EPortType port3;
EPortType port4;

uint32_t pinMask1;
uint32_t pinMask3;
uint32_t pinMask4;



void setup() {

	SerialUSB.begin(500000);
	
	mcp_bits.begin(0); // address 0
	mcp_status.begin(1); // address 1
	
	// i2c for mcp23008
	Wire.setClock(400000);
	
	// sets pins in both MCP23008 as INPUTs
	mcp_bits.write8(MCP23008_IODIR, 0b11111111);
	mcp_status.write8(MCP23008_IODIR, 0b11111111);

	//decoder
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	
	//enable decoder
	digitalWrite(0,HIGH);
	
	displayI2C.begin();
	displayI2C.setClock(800000);
	
	// Assign pins 13 & 11 to SERCOM functionality
	pinPeripheral(11, PIO_SERCOM);
	pinPeripheral(13, PIO_SERCOM);


	for(int i = 0; i< 8; i++){
		charDisp[i].setPWMFreq(1000);
		writeCharDisp_Off(charDisp[i]);
		//writeCharDisp(0, charDisp[i], 4095);
	}
	
	
	port1 = g_APinDescription[1].ulPort;
	uint32_t pin1 = g_APinDescription[1].ulPin;
	pinMask1 = (1ul << pin1);
	
	port3 = g_APinDescription[3].ulPort;
	uint32_t pin3 = g_APinDescription[3].ulPin;
	pinMask3 = (1ul << pin3);
	
	port4 = g_APinDescription[4].ulPort;
	uint32_t pin4 = g_APinDescription[4].ulPin;
	pinMask4 = (1ul << pin4);
}


int charBeingChecked = 0;

double delayBetweenChars = 1000000.0f;
int charsLooped = 1;


unsigned long lastStep = 0;

int mcpVal = 0;

int delayState = 0;

void loop() {
	


	
	// 	SerialUSB.print(charBeingChecked);
	// 	SerialUSB.print(" being checked...");
	// 	SerialUSB.print("");
	//
	//
	// 	//delayMicroseconds(15000);
	//
	// 	SerialUSB.print(mcp_status.digitalRead(7-charBeingChecked));
	//
	// 	//	if(mcp_status.digitalRead(7-charBeingChecked)){
	//
	// 	SerialUSB.print("\tAttached: ");
	// 	SerialUSB.write(mcp_bits.readGPIO());
	// 	SerialUSB.print(SixteenSegmentASCII[mcp_bits.readGPIO()-32],BIN);
	//
	//
	// 	/*
	// 	// Array starts with "space", ASCII no 32, hence "-32"
	// 	SixteenSegmentASCII[mcp_bits.readGPIO()-32]
	// 	*/
	//

	// 	SerialUSB.println();
	// 	}
	// 	else{
	// 		SerialUSB.print("\tNot Attached...\r\n");
	// 	}
	

	if(micros() - lastStep > delayBetweenChars){
		lastStep = micros();
		enableChar(charBeingChecked);
		if(delayBetweenChars > 2000){
			delay(2);
		}
		else{
			//
		}

		// reads the char
		mcpVal = mcp_bits.readGPIO() - 32;

		if(delayState != 2){
			if (mcpVal > 32 && mcpVal < 59){
				writeCharDisp(mcpVal, charDisp[charBeingChecked], 4095);
			}
			else{
				writeCharDisp(999,charDisp[charBeingChecked],4095);
			}
			
			
			if(charBeingChecked !=0)
			writeCharDisp_Off(charDisp[charBeingChecked-1]);
			else
			writeCharDisp_Off(charDisp[7]);
		}
		
		
		
		if(delayState == 0){
			delayBetweenChars = delayBetweenChars/1.02f;
			if (delayBetweenChars < 1500) delayState++;
		}
		else if(delayState == 1){
			delayBetweenChars = 0;
			if(charsLooped > 800) delayState++;
		}
		else if(delayState == 2){
			//delay(10000);
			if (mcpVal > 32 && mcpVal < 59){
				//writeCharDisp(mcpVal, charDisp[charBeingChecked], 1000);
				writeCharDisp(mcpVal, charDisp[charBeingChecked], 4095);
			}
			else{
				writeCharDisp(999,charDisp[charBeingChecked],1000);
			}
			if(charsLooped > 3000) {
				for(int i = 0; i < 8; i++){
					writeCharDisp_Off(charDisp[i]);
					
				}
				delayState = 0;
				charsLooped = 1;
				delayBetweenChars = 1000000.0f;
			}
		}

		charBeingChecked++;
		if(charBeingChecked == 8) {
			charBeingChecked = 0;
			charsLooped++;

		}	
	}
	
}



void enableChar(int _charToEnable){
	
	switch (_charToEnable)
	{
		case 0:
		PORT->Group[port1].OUTCLR.reg = pinMask1; // A0
		PORT->Group[port3].OUTCLR.reg = pinMask3; // A1
		PORT->Group[port4].OUTCLR.reg = pinMask4; // A2
		break;
		case 1:
		PORT->Group[port1].OUTSET.reg = pinMask1;
		//PORT->Group[port3].OUTCLR.reg = pinMask3;
		//PORT->Group[port4].OUTCLR.reg = pinMask4;
		break;
		case 2:
		PORT->Group[port1].OUTCLR.reg = pinMask1;
		PORT->Group[port3].OUTSET.reg = pinMask3;
		//PORT->Group[port4].OUTCLR.reg = pinMask4;
		break;
		case 3:
		
		PORT->Group[port1].OUTSET.reg = pinMask1;
		PORT->Group[port3].OUTSET.reg = pinMask3;
		//PORT->Group[port4].OUTCLR.reg = pinMask4;
		break;
		case 4:
		
		PORT->Group[port1].OUTCLR.reg = pinMask1;
		PORT->Group[port3].OUTCLR.reg = pinMask3;
		PORT->Group[port4].OUTSET.reg = pinMask4;
		break;
		case 5:
		
		PORT->Group[port1].OUTSET.reg = pinMask1;
		//PORT->Group[port3].OUTCLR.reg = pinMask3;
		//PORT->Group[port4].OUTSET.reg = pinMask4;
		break;
		case 6:
		PORT->Group[port1].OUTCLR.reg = pinMask1;
		PORT->Group[port3].OUTSET.reg = pinMask3;
		//PORT->Group[port4].OUTSET.reg = pinMask4;
		break;
		case 7:
		
		PORT->Group[port1].OUTSET.reg = pinMask1;
		//PORT->Group[port3].OUTSET.reg = pinMask3;
		//PORT->Group[port4].OUTSET.reg = pinMask4;
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

void writeCharDisp(uint16_t _charToShow, Adafruit_PWMServoDriver& _charDisp, uint16_t _brightness){

	for(int i = 0; i < 16; i++){
		if((1 << i) & SixteenSegmentASCII[_charToShow]){
			_charDisp.setPin(bitToPCA9685Map[i],_brightness,true);
		}
		else{
			_charDisp.setPin(bitToPCA9685Map[i],0,true);
		}
	}

}


void writeCharDisp_Off(Adafruit_PWMServoDriver& _charDisp){
	_charDisp.setAllOff();
	
}