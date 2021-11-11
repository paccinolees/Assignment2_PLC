#include <Galil.h>
#include <EmbeddedFunctions.h>
#include <gclib.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>

#include <conio.h>

using namespace System;
using namespace System::Threading;

#define address "192.168.0.120 -d" // address of PLC

int main() {
	EmbeddedFunctions FuncObj; 
	Galil myGalil(&FuncObj, address);

	//q1:
	while (1) {
		myGalil.DigitalOutput(0);

		if (_kbhit()) {
			myGalil.DigitalBitOutput(1, 0);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 0);

			myGalil.DigitalBitOutput(1, 1);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 1);

			myGalil.DigitalBitOutput(1, 2);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 2);

			myGalil.DigitalBitOutput(1, 3);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 3);

			myGalil.DigitalBitOutput(1, 4);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 4);

			myGalil.DigitalBitOutput(1, 5);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 5);

			myGalil.DigitalBitOutput(1, 6);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 6);

			myGalil.DigitalBitOutput(1, 7);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 7);

			myGalil.DigitalBitOutput(1, 8);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 8);

			myGalil.DigitalBitOutput(1, 9);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 9);

			myGalil.DigitalBitOutput(1, 10);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 10);

			myGalil.DigitalBitOutput(1, 11);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 11);

			myGalil.DigitalBitOutput(1, 12);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 12);

			myGalil.DigitalBitOutput(1, 13);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 13);

			myGalil.DigitalBitOutput(1, 14);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 14);

			myGalil.DigitalBitOutput(1, 15);
			Thread::Sleep(100);
			myGalil.DigitalBitOutput(0, 15);

			_getch();
		}
	}
	
	//Q2:
	/*myGalil.DigitalOutput(0);

	myGalil.AnalogOutput(0, 3);

	while (1) {
		if (myGalil.ReadEncoder() == 0) {
			myGalil.DigitalOutput(65535);
		}
	}*/


	Console::ReadKey(); 
	return 0;
};
