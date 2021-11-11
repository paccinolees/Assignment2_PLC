#include <Galil.h>
#include <EmbeddedFunctions.h>
#include <gclib.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>

using namespace System;

#define address "192.168.0.120 -d" // address of PLC

int main() {//DELETE THESE BEFORE ASSESSMENT
	EmbeddedFunctions FuncObj; 
	Galil myGalil(&FuncObj, address);

	
	myGalil.DigitalOutput(257);	// TEST: bit 8 and 0 shud be 1 (tested)

	//myGalil.DigitalByteOutput(1, 8);		// TEST: highbyte bits shud equal 8 while lowbyte unchanged (tested)
	//myGalil.DigitalByteOutput(0, 8);		// TEST: vice versa... (tested)

	//myGalil.DigitalBitOutput(1, 0);			// TEST: bit 0 becomes 1 (tested)
	//myGalil.DigitalBitOutput(false, 0);		// TEST: bit 0 becomes 0 (tested)

	//myGalil.DigitalInput();		// TEST: Should return the 16bits value of Digital Input to this function (tested)

	//myGalil.DigitalByteInput(1);	// TEST: Should return the 8bits value of highbyte if Digital Input (tested)
	//myGalil.DigitalByteInput(0);	// TEST: Should return the 8bits value of lowbyte if Digital Input (tested)
	
	//myGalil.DigitalBitInput(17);		// TEST: Should return the 3rd bit value 1/0 (tested)
	
	//myGalil.CheckSuccessfulWrite(); // TEST: Should return ':' if previous command is correct, '?' if not (tested)

	//myGalil.AnalogInput(1);		// TEST: Return float value of a channel of analog input (tested)
	
	//myGalil.AnalogOutput(0, 1.244); // TEST: Set Channel0 of analogOutput to 1.24V (tested)
	
	//myGalil.WriteEncoder(); // TEST: Set ch0's enc. to 0 (tested(for ch0 only) )
	//myGalil.ReadEncoder(); // TEST: Should return ch0's enc. posiion/value, previously set to 0 by WriteEncoder() (tested(for ch0 only) )



	Console::ReadKey(); 
	return 0;
};
