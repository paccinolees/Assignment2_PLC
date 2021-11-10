//-------------Following Jame's "includes" in the first lab recording of assignment 2------------//
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <math.h> // for power function: pow()

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
	uint16_t result = 0; // will store the 16bits value as decimal
	int bitValue;

	for (int bit = 0; bit < 16; bit++) {
		sprintf_s(command, "MG @IN[%d]", bit);
		Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

		bitValue = atoi(ReadBuffer); // convert the decimal number to int (1.0000 --> 1) 
		result += pow(2,bit) * bitValue; 
	}
	
	return result;
}

uint8_t Galil::DigitalByteInput(bool bank)		// Read either high or low byte, as specified by user in 'bank' 0 = low, 1 = high
{
	uint8_t result = 0;
	int bitValue;
	int high_bitpos = 0; // bits position for the highbyte

	if (bank) {
		for (int bit = 8; bit < 16; bit++) {
			sprintf_s(command, "MG @IN[%d]", bit);
			Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

			bitValue = atoi(ReadBuffer); 
			result += pow(2, high_bitpos) * bitValue;

			high_bitpos++;
		}
	}
	else {
		for (int bit = 0; bit < 8; bit++) {
			sprintf_s(command, "MG @IN[%d]", bit);
			Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

			bitValue = atoi(ReadBuffer); 
			result += pow(2, bit) * bitValue;
		}
	}
	//printf("result:%d", result); //for testing purpose
	return result;
}

bool Galil::DigitalBitInput(uint8_t bit)	// Read single bit from current digital inputs. Above functions may use this function (I didnt use cuz I did those first)
{
	int bitValue;

	sprintf_s(command, "MG @IN[%d]", bit);
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
	
	bitValue = atoi(ReadBuffer);
	//printf("bitVal:%d", bitValue); //for testing purpose
	return bitValue;
}
//-----------------------------------------------------//

bool Galil::CheckSuccessfulWrite()	// Check the string response from the Galil to check that the last command executed correctly. 1 = succesful. NOT AUTOMARKED
{
	bool check;

	char response = ReadBuffer[strlen(ReadBuffer) - 1];
	if (response == ':') {
		check = 1;
		//std::cout << "right" << std::endl; //for testing purpose
	}
	else {
		check = 0;
		//std::cout << "wrong" << std::endl; //for testing purpose
	}

	return check;
}


//-----------------ANALOG FUNCITONS--------------------//
float Galil::AnalogInput(uint8_t channel)						// Read Analog channel and return voltage
{
	float result;

	sprintf_s(command, "MG @AN[%d]", channel);
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

	result = atof(ReadBuffer);
	//std::cout << result << std::endl; //for testing purpose
	return result;
}

void Galil::AnalogOutput(uint8_t channel, double voltage)		// Write to any channel of the Galil, send voltages as 2 decimal place in the command string
{
	sprintf_s(command, "AO%d,%.2f", channel, voltage);
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}

void Galil::AnalogInputRange(uint8_t channel, uint8_t range)	// Configure the range of the input channel with the desired range code
{
	sprintf_s(command, "AQ%d,%d", channel, range);
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
	//NOTE TO SELF: didnt test yet cuz not sure what/how to test...
}
//-----------------------------------------------------//


//-----------------ENCODER/CONTROL FUNCTIONS--------------------//
void Galil::WriteEncoder()		// Manually Set the encoder value to zero
{
	sprintf_s(command, "WE3"); // only set channel0's encoder to 0 (?)
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);
}

int Galil::ReadEncoder()	// Read from Encoder
{
	int encoderValue;

	sprintf_s(command, "QE0");
	Functions->GCommand(g, command, ReadBuffer, sizeof(ReadBuffer), 0);

	encoderValue = atoi(ReadBuffer);
	printf("enc. Val:%d", encoderValue); //for testing purpose
	return encoderValue;
}
//-----------------------------------------------------//
Galil::~Galil()
{
	if (g) {
		Functions->GClose(g);
	}
}
