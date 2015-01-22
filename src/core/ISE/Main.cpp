#pragma once 

// Beast Code
#include "ISE.h"

// Qt
#include <QApplication>

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>

using namespace ISE_space;

int main(int argc, char *argv[])
{
	//Set up the core application for ISE
	QApplication *a = new QApplication(argc, argv);
	//
	// 1. initialize kraken through spectr
	ISE *ourProgram = new ISE();
	ourProgram->initialize(a);

	// Execute the program.
	return a->exec();
}

