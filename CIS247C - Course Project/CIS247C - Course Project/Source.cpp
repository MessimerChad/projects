/*
Chad Messimer
05/24/2020
CIS247C Course Project
*/

#include <iostream>

#include <string>

#include <fstream>

#include <iomanip> // setw, setprecision

#include "Vehicle.h"

#include "SUV.h"

#include "GasCar.h""

#include "ElectricCar.h"

#include "Engine.h"

#include "Car.h"
using namespace std;

/// Entry point for the application

// prototypes

void saveToFile(Vehicle* ptrVehicle);
string determineChildType(Vehicle* ptrVehicle);

int main()
{
	// create your Vehicles using specific classes
	const int NUM_CARS = 4;
	Vehicle* vehicles[NUM_CARS];
	vehicles[0] = new Car("Za45356", "Ford", "Mustang", 2010, 10000.0, 2, false, Engine(8, 315));
	vehicles[1] = new SUV("S45893", "Honda", "Civic", 2018, 24000.0, 8, 47.7f, Engine(6, 250));
	vehicles[2] = new GasCar("E459345", "Chevy", "Corvette", 2010, 20000, 2, false, 18, 19, Engine(0, 271));
	vehicles[3] = new ElectricCar("G124589", "Tesla", "Model 3", 2018, 25000.0, 4, false, 75, 240, 136, Engine(0, 327));


	// check the size
	cout << "Size of Vehicle pointer: "
			<< sizeof(vehicles[0]) << endl; // Much Smaller!!
	cout << "Size of Vehicle object (dereferenced): "
		<< sizeof(*vehicles[0]) << endl;
	cout << endl; // blank line

	// delete file if it exists
	remove("data.txt");

	// call the method to write your Car to the file

	for (int i = 0; i < NUM_CARS; i++)
	{
		delete vehicles[i];
	}

	//pause
	cout << endl;
	system("pause");

	return 0;
}

void saveToFile(Vehicle* ptrVehicle)
{
	// open the pipe to the file
	ofstream outToFile("data.txt", ios::app); // app means "Append"

	// determine the child type and write the child data
	string childType = determineChildType(ptrVehicle);

	// if the file is open, write the data to the file
	if (outToFile.is_open())
	{
		// write the child type AND STAY ON THE SAME OUTPUT LINE
		outToFile << childType << ',';

		// ON THE SAME LINE, write parent information using the parent reference
		outToFile << ptrVehicle->getVin() << ',' << ptrVehicle->getMake() << ','
			<< ptrVehicle->getModel() << ',' << ptrVehicle->getYear() << ','
			<< ptrVehicle->getPrice() << ',' 
			<< ptrVehicle->getMotor().getNumCylinders() << ',' //Notice the composition
			<< ptrVehicle->getMotor().getHorsePower() << endl;

		// dynamic cast to get child object and write child info ON SAME LINE
		if (childType == "SUV")
		{
			SUV* s1 = dynamic_cast<SUV*>(ptrVehicle);
			outToFile << ',' << s1->getNumSeats()
				<< ',' << s1->getCargoSize();
		}

		if (childType == "Car")
		{
			// write info if Car or child of Car (GasCar or ElectricCar)
			Car* c1 = dynamic_cast<Car*>(ptrVehicle);
			outToFile << ',' << c1->getNumDoors()
				<< ',' << c1->getHatchback();
		}

		if (childType == "ElectricCar")
		{
			ElectricCar* e1 = dynamic_cast<ElectricCar*>(ptrVehicle);
			outToFile << ',' << e1->getBatterySize() << ','
				<< e1->getRange() << ',' << e1->getMpgE();
		}

		else if (childType == "GasCar")
		{
			GasCar* g1 = dynamic_cast<GasCar*>(ptrVehicle);
			outToFile << ',' << g1->getTankSize() << ',' << g1->getMPG();
		}

		// drop down to next line in file so we are ready for the next record
		outToFile << endl;

		// close the pipe
		outToFile.close();

		// tell user that the data was written
		cout << ptrVehicle->getMake() << "" << ptrVehicle->getModel() << " was written to the file!" << endl;
	}
}

//determine the child type and write the child datastring childType = determineChildType(ptrVehicle)

string determineChildType(Vehicle* ptrVehicle)
{
	ElectricCar* e1 = dynamic_cast<ElectricCar*>(ptrVehicle);
	if (e1 != nullptr)
		return "ElectricCar";

	GasCar* g1 = dynamic_cast<GasCar*>(ptrVehicle);
	if (g1 != nullptr)
		return "GasCar";

	Car* c1 = dynamic_cast<Car*>(ptrVehicle);
	if (c1 != nullptr)
		return "Car";

	SUV* s1 = dynamic_cast<SUV*>(ptrVehicle);
	if (s1 != nullptr)
		return "SUV";

	return "Error";
}