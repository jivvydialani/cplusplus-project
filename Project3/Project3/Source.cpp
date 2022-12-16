#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int userChoice;
string searchTerm;
string fileLine;

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//Menu fuction
void menu()
{
	//Display menu and get user-input
	cout << "1: Produce a list of all items purchased with quantities of each item" << endl;
	cout << "2: Produce a number representing how many times a specific item was purchased" << endl;
	cout << "3: Produce a text-based histogram of each item" << endl;
	cout << "4: Exit\n" << endl;
	cout << "Enter your selection as a number: 1, 2, 3, or 4: " << endl;
	cin >> userChoice;

	//Conditional statement to call the appropriate function
	if (userChoice == 1) {
		cout << endl << "Items and quantities sold: \n" <<endl;
		CallProcedure("ItemCounter");
		cout << endl;
		return;
	}
	else if (userChoice == 2) {
		cout << "\nPlease enter the item name:" << endl;
		cin >> searchTerm;
		cout << endl;
		searchTerm[0] = toupper(searchTerm[0]);
		cout << "Printing the number of items sold for " << searchTerm << ":\n";
		cout << searchTerm << ": " << callIntFunc("CountInstances", searchTerm) << "\n\n";
		return;
	}
	else if (userChoice == 3) {
		cout << "\nWriting items and quantities sold today to a file:\n" << endl;
		CallProcedure("DataWriter");
		ifstream frequencyFile("frequency.dat");
		string item;
		int count;
		//While loop to chech each line of the file
		while (getline(frequencyFile, fileLine)) {
			istringstream iss(fileLine);
			if (!(iss >> item >> count)) { break; } //Error
			//Prints the item name and asterisks
			cout << item << " " << string(count, '*') << endl;
		}
		cout << endl << endl;
		return;
	}
	else if (userChoice == 4) {
		cout << "\nExiting program...";
		exit(EXIT_SUCCESS);
	}
	else {
		cout << "\nPlease enter a valid input.\n" << endl;
		return;
	}
}


int main() {
	//While loop that loops until user exits program
	while (true) {
		menu();
	}

	return 0;
}
