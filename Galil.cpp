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

void Galil::DigitalOutput(uint16_t value)	// Write to all 16 bits of digital output, 1 command to the Galil
{
	// Extract the high/low bytes
	uint8_t highByte = value >> 8;
	uint8_t lowByte = value & 0xff;

	// Generate the C-String command using stringstream
	std::stringstream ss; 
	ss << "OP" << lowByte << "," << highByte;
	std::string tmpString = ss.str();
	command = tmpString.c_str();

	// Send command to Galil
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}

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
	delete Functions;
	delete command;
}
