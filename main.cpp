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

int main() {
	EmbeddedFunctions FuncObj;
	Galil myGalil(&FuncObj, address);


	//myGalil.DigitalOutput(257);	// TEST: bit 8 and 0 shud be 1 (tested)

	//myGalil.DigitalByteOutput(1, 8);		// TEST: highbyte bits shud equal 8 while lowbyte unchanged (tested)
	//myGalil.DigitalByteOutput(0, 8);		// TEST: vice versa... (tested)

	//myGalil.DigitalBitOutput(1, 0);			// TEST: bit 0 becomes 1 (tested)
	//myGalil.DigitalBitOutput(false, 0);		// TEST: bit 0 becomes 0 (tested)

	myGalil.DigitalInput();		// TEST: Should return the 16bits of Digital Input to this function

	return 0;
};
