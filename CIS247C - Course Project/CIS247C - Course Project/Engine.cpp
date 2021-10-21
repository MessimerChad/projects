#include "Engine.h"

#include "Vehicle.h"

Engine::Engine()
{
	numCylinders = 0;
	horsePower = 0;
}


Engine::Engine(short numCyclinders, short horsePower)
{
	setNumCylinders(numCylinders);
	setHorsePower(horsePower);
}

Engine::~Engine()
{
	
}

// behaviors
string Engine::toString()
{
	return "numClinders: " + to_string(numCylinders) + ", horsePower: " + to_string(horsePower);
}

// accessors and mutators
short Engine::getNumCylinders()
{
	return numCylinders;
}

void Engine::setNumCylinders(short numCylinders)
{
	if (numCylinders > 0 && numCylinders < 13)
		this->numCylinders = numCylinders;
	else
		this->numCylinders = 0;
}

short Engine::getHorsePower()
{
	return horsePower;
}

void Engine::setHorsePower(short horsePower)
{
	if (horsePower > 0 && horsePower < 1000)
		this->horsePower = horsePower;
	else
		this->horsePower = 0;
}