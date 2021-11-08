//-------------Following Jame's "includes" in the first lab recording of assignment 2------------//
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
//-----------------------------------------------------------------------------------------------//

using namespace System;
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

Galil::Galil() // Default constructor. Initialize variables, open Galil connection and allocate memory.
{
	GCStringIn default_address = "192.168.0.120 -d";
	g = 0;
	EmbeddedFunctions Funcs;
	Functions = &Funcs;
	Functions->GOpen(default_address, &g);
} 
Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address)	// Constructor with EmbeddedFunciton initialization
{
	g = 0;
	Functions = Funcs;
	Functions->GOpen(address, &g);
}


//-----------------DIGITAL OUTPUTS--------------------//

void Galil::DigitalOutput(uint16_t value)	// Write to all 16 bits of digital output, 1 command to the Galil
{
	// Extract the high/low bytes
	uint8_t highByte = value >> 8;
	uint8_t lowByte = value & 0xff;

	// Generate the C-String command using stringstream
	sprintf_s(command, "OP%d,%d", lowByte, highByte);
	std::cout << command << std::endl; //for test
	// Send command to Galil
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}

void Galil::DigitalByteOutput(bool bank, uint8_t value)		// Write to one byte, either high or low byte, as specified by user in 'bank' 0 = low, 1 = high
{
	if (bank) {
		sprintf_s(command, "OP,%d", value);
	}
	else {
		sprintf_s(command, "OP%d", value);
	}

	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}

void Galil::DigitalBitOutput(bool val, uint8_t bit)		// Write single bit to digital outputs. 'bit' specifies which bit
{
	sprintf_s(command, "OB%d,%d", bit, val);
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}
//-----------------------------------------------------//


//-----------------DIGITAL INPUTS--------------------//

uint16_t Galil::DigitalInput()		// Return the 16 bits of input data Query the digital inputs of the GALIL, See Galil command library @IN
{
	uint16_t result = 0;
	int bitValue;

	for (int bit = 0; bit < 16; bit++) {
		sprintf_s(command, "MG @IN[%d]", bit);
		Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

		bitValue = atoi(ReadBuffer);
		result += (2 ^ bit) * bitValue;
		std::cout << "bit:" << bit << std::endl; //FOR DEBUG
		std::cout << ReadBuffer << std::endl;
		std::cout << "ReadBuffer[2]:"<< ReadBuffer[2] << std::endl;
		std::cout << "bitval:" << bitValue << std::endl;

	}
	std::cout << result;
	return result;
}

//-----------------------------------------------------//

void Galil::AnalogOutput(uint8_t channel, double voltage)		// Write to any channel of the Galil, send voltages as 2 decimal place in the command string
{

}

int Galil::ReadEncoder()	// Read from Encoder
{

	return 0;
}

Galil::~Galil()
{
	if (g) {
		Functions->GClose(g);
	}
}
