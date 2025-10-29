#include "Calculator.h"
#include <iostream>
#include "Validation.h"
using namespace std;
int main() 
{
    Calculator calc;
    cout << "Calculator is running. Enter exit - to leave\n";

    string input;
    while (true) 
    {
        cout << "> ";
        getline(cin, input);
        trim(input);
        if (input == "exit") break;
        try 
        {
            calc.processCommand(input);
        }
        catch (const exception& e) 
        {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}