#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Noah Archibald
06/20/2021
This program will combine both C++ and Python in order to read an input file
and display a menu which receives user input to either display and calculate
the number of times each grocery item occurs on the list (input file), 
the number of times a specific grocery item occurs on the list, 
or display a histogram representing the frequency of all grocery items from the list on the input file.
*/


void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonFile");
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
    pName = PyUnicode_FromString((char*)"PythonFile");
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
    pName = PyUnicode_FromString((char*)"PythonFile");
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


//Function to prompt for user input and handle each choice
void DrawMenu() {

    //Initialize variables for each method
    int menuLoop = 0;                                                       
    int wordCount = 0;                                                      
    int itemQuantity = 0;                                           
    string searchTerm;                                                      
    string itemName;                                                        
    string greenColor = "\033[32;1m";                       
    string defaultColor = "\033[0m";                        
    ifstream fileInput;                                                     

    while (menuLoop != 4) {

        //Prompt and collect user input
        cout << "1: Calculate the number of times each item appears" << endl;
        cout << "2: Calculate the frequency of a specific item" << endl;
        cout << "3: Display a histogram of the frequency of each item" << endl;
        cout << "4: Exit Program" << endl;

        cin >> menuLoop;

        //Check for valid input
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits< streamsize > ::max(), '\n');
            cout << "Please input a valid selection: ";
            cin >> menuLoop;
        }


        //Switch statement to handle each case the user chooses:
        switch (menuLoop) {

            //Calculate number of times each item appears and print a list displaying all of them
        case 1:
            system("CLS");                                          
            CallProcedure("CountAll");              //Call the Python function "CountAll"
            cout << endl;                           
            break;

            //Calculate number of times a specific item appears and print the result
        case 2:
            system("CLS");
            cout << "What item would you like to search for?" << endl;
            cin >> searchTerm;
            wordCount = callIntFunc("CountInstances", searchTerm); //Call Python function CountInstances and return frequency of item as an integer
            cout << endl << searchTerm << ": " << wordCount << endl << endl;
            break;

            //Display a histogram based on frequency of each item
        case 3:
            system("CLS");                                          
            CallProcedure("CollectData");           //Call the Python function "CollectData"
            fileInput.open("frequency.dat");        //Open frequency.dat file created in Python
            fileInput >> itemName;                            //Collect first item on list
            fileInput >> itemQuantity;                        //Collect first quantity on list

            //Loop to print histogram for each line in the frequency.dat file
            while (!fileInput.fail()) {
                
                cout << defaultColor;
                cout << setw(14) << left << itemName << setw(6); //Print the item name
                cout << greenColor;

                //Print asterisk for itemQuantity amount of times
                for (int i = 0; i < itemQuantity; i++) {
                    cout << right << "*";
                }
                cout << endl;
                fileInput >> itemName;
                fileInput >> itemQuantity;
            }

            //Close frequency.dat and end loop
            fileInput.close();
            cout << defaultColor << endl;
            break;

            //Exiting the program
        case 4:
            return;

            //Default case to handle invalid input
        default:
            cout << "Error! Please input a valid selection." << endl;
            cout << endl;
            break;
        }
    }
}

//Calls DrawMenu to collect input from user.
void main()
{
    DrawMenu();

}