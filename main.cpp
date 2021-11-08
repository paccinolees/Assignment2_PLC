#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <fstream>
#include <string>

#include <Galil.h>
#include <EmbeddedFunctions.h>
#include <gclib.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>

using namespace System;
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

#define address "192.168.0.120 -d" // address of PLC

int main() {//SHOULD BE EMPTY BEFORE ASSESSMENT WK11, CUZ THEY GON ASSESS THAT WE KNOW HOW TO INSTANTIATE CLASS etc.. (DONT FORGET TO REMEM)
	EmbeddedFunctions FuncObj; 
	Galil myGalil(&FuncObj, address);


	//myGalil.DigitalOutput(257);	// TEST: bit 8 and 0 shud be 1 (tested)

	//myGalil.DigitalByteOutput(1, 8);		// TEST: highbyte bits shud equal 8 while lowbyte unchanged (tested)
	//myGalil.DigitalByteOutput(0, 8);		// TEST: vice versa... (tested)

	//myGalil.DigitalBitOutput(1, 0);			// TEST: bit 0 becomes 1 (tested)
	//myGalil.DigitalBitOutput(false, 0);		// TEST: bit 0 becomes 0 (tested)

	//myGalil.DigitalInput();		// TEST: Should return the 16bits value of Digital Input to this function (tested)

	//myGalil.DigitalByteInput(1);	// TEST: Should return the 8bits value of highbyte if Digital Input (tested)
	//myGalil.DigitalByteInput(0);	// TEST: Should return the 8bits value of lowbyte if Digital Input (tested)
	
	Console::ReadKey(); 
	return 0;
};
