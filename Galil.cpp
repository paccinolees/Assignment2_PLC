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

Galil::Galil() {}; // Default constructor (From James' first lab recording, it is left blank)

Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address)	// Constructor with EmbeddedFunciton initialization
{
	Functions = Funcs;
	Functions->GOpen(address, &g);
}
void Galil::DigitalOutput(uint16_t value)	// Write to all 16 bits of digital output, 1 command to the Galil
{
	//maybe use the command[128] I added, to send commands...
}
Galil::~Galil()
{
	if (g) {
		Functions->GClose(g);
	}
	delete Functions;
}
