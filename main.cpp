#include <valarray>
#include "iostream"
#include "calculate.hpp"
#include "preTreat.hpp"

using std::cout;
using std::endl;

int main() {

    Calculate calculate;

    while (true) {
        cout << "Please enter the formula you want to calculate (enter \\q to quit): " << endl;

        //Get user input
        getline(cin, calculate.input);

        //If the user enters \q, the program ends
        if (calculate.input == "\\q") {
            return 0;
        }

        //Clear space in expression
        calculate.trimSpace();

        //Judge whether the input is a formula or an assignment statement
        while (true) {
            if (calculate.checkIsAssignmentExpression()) {
                getline(cin, calculate.input);
            } else {
                break;
            }
        }

        //Replace the variable in the expression with its value
        calculate.convertVariablesToNumber();

        //Check the validity of expressions
        if (!calculate.checkValidity()) {
            cout << "You input is illegal, please check it." << endl;
            continue;
        }

        //Change "-*" to "0-*", and change "+*" to "0+*"
        calculate.standardise();
        //
        calculate.convertToStandardFormat();

        //Calculate and output results
        cout << calculate.calculate() << endl;

        //Clear the vectors and stacks used in the calculation process to facilitate the next calculation
        calculate.stdFormat.clear();
        calculate.computeStack.pop();
    }

}

