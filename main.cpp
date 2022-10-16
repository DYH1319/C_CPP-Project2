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

        getline(cin, calculate.input);

        if (calculate.input == "\\q") {
            return 0;
        }

        calculate.trimSpace();

        while (true) {
            if (calculate.checkIsAssignmentExpression()) {
                getline(cin, calculate.input);
            } else {
                break;
            }
        }

        calculate.convertVariablesToNumber();

        if (!calculate.checkValidity()) {
            cout << "You input is illegal, please check it." << endl;
            continue;
        }

        calculate.standardise();
        calculate.convertToStandardFormat();

        cout << calculate.calculate() << endl;

        calculate.stdFormat.clear();
        calculate.computeStack.pop();
    }

}

