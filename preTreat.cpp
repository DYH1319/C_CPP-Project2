#include <iostream>
#include "preTreat.hpp"
#include "calculate.hpp"

Calculate::Calculate() = default;

void Calculate::trimSpace() {
    int index = 0;
    if (!input.empty()) {
        while ((index = (int) input.find(' ', index)) != string::npos) {
            input.erase(index, 1);
        }
    }
}

int Calculate::getSymbol_lv(char symbol) {
    if (symbol == ' ' || symbol == '.') {
        return SYMBOL_LV::LV1;
    } else if ((symbol >= '0' && symbol <= '9')) {
        return SYMBOL_LV::LV2;
    } else if (symbol == '+' || symbol == '-') {
        return SYMBOL_LV::LV3;
    } else if (symbol == '*' || symbol == '/') {
        return SYMBOL_LV::LV4;
    } else if (symbol == '{' || symbol == '}') {
        return SYMBOL_LV::LV5;
    } else if (symbol == '[' || symbol == ']') {
        return SYMBOL_LV::LV6;
    } else if (symbol == '(' || symbol == ')') {
        return SYMBOL_LV::LV7;
    } else {
        return SYMBOL_LV::LV0;
    }
}

bool Calculate::checkIsAssignmentExpression() {
    int index = 0;
    if (!input.empty()) {
        if ((index = (int) input.find('=', index)) != string::npos && index != 0 && index != input.size()) {
            string var = input.substr(0, index);
            string value = input.substr(index + 1);
            for (char c: value) {
                if ((c < '0' || c > '9') && c != '.') {
                    cout << "The value " << value << " is not a number, please check it." << endl;
                    getline(cin, input);
                    checkIsAssignmentExpression();
                }
            }
            for (char c: var) {
                if (getSymbol_lv(c) > 0) {
                    cout << "The name " << var
                         << " of the variable is not allowed, please change you variable name, don't use number or operational symbol."
                         << endl;
                    getline(cin, input);
                    checkIsAssignmentExpression();
                }
            }
            customVar[var] = value;
            return true;
        }
    }
    return false;
}

void Calculate::convertVariablesToNumber() {
    map<string, string>::iterator iter;
    for (iter = customVar.begin(); iter != customVar.end(); iter++) {
        input.replace(input.find(iter->first), iter->first.size(), iter->second);
    }
}

bool Calculate::checkValidity() const {
    stack<char> checkSymbol;
    stack<char> brackets;
    bool haveNum = false;
    for (int i = 0; i < input.size(); i++) {
        char c = input.at(i);
        if (getSymbol_lv(c) == 0) {
            return false;
        }
        if (c == '.') {
            if (i == 0 || i == input.size() - 1 || getSymbol_lv(input.at(i - 1)) != 2 || getSymbol_lv(input.at(i + 1)) != 2) {
                return false;
            }
        }
        if (getSymbol_lv(c) == 2) {
            haveNum = true;
        }
        if (getSymbol_lv(c) == 3) {
            if (!checkSymbol.empty() && (getSymbol_lv(checkSymbol.top()) == 3 || getSymbol_lv(checkSymbol.top()) == 4)) {
                return false;
            }
        }
        if (getSymbol_lv(c) == 4) {
            if (checkSymbol.empty() || getSymbol_lv(checkSymbol.top()) == 3 || getSymbol_lv(checkSymbol.top()) == 4
                || checkSymbol.top() == '(' || checkSymbol.top() == '[' || checkSymbol.top() == '{') {
                return false;
            }
        }
        if (getSymbol_lv(c) >= 2) {
            checkSymbol.push(c);
        }
        if (c == '(' || c == '[' || c == '{') {
            if ((brackets.empty() || getSymbol_lv(c) > getSymbol_lv(brackets.top()))
                && (i == 0 || getSymbol_lv(input.at(i - 1)) == 1 || getSymbol_lv(input.at(i - 1)) == 3 ||
                    getSymbol_lv(input.at(i - 1)) == 4)) {
                brackets.push(c);
                continue;
            } else {
                return false;
            }
        }
        if (c == ')' || c == ']' || c == '}') {
            if (!brackets.empty() && getSymbol_lv(c) == getSymbol_lv(brackets.top()) && getSymbol_lv(input.at(i - 1)) <= 2
                && (i + 1 == input.size() || getSymbol_lv(input.at(i + 1)) == 1) || getSymbol_lv(input.at(i + 1)) == 3 ||
                getSymbol_lv(input.at(i + 1)) == 4) {
                brackets.pop();
                continue;
            } else {
                return false;
            }
        }
    }
    if (!brackets.empty()) {
        return false;
    } else {
        return haveNum;
    }
}

void Calculate::standardise() {
    bool state = false;
    for (int i = 0; i < input.size(); i++) {
        char c = input.at(i);
        if (c == '(' || c == '[' || c == '{') {
            state = true;
            continue;
        }
        if (c == '+' || c == '-') {
            if (i == 0) {
                input.insert(0, 1, '0');
            } else if (state) {
                input.insert(i, 1, '0');
                state = false;
            }
        }
        if (c != ' ') {
            state = false;
        }
    }
}

void Calculate::convertToStandardFormat() {
    for (int i = 0; i < input.size(); i++) {
        char c = input.at(i);
        string temp;

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (symbolStack.empty() || symbolStack.top() == '(' || symbolStack.top() == '[' || symbolStack.top() == '{') {
                symbolStack.push(c);
            } else {
                while (!symbolStack.empty() && getSymbol_lv(c) <= getSymbol_lv(symbolStack.top()) &&
                       getSymbol_lv(symbolStack.top()) <= 4) {
                    temp += symbolStack.top();
                    stdFormat.push_back(temp);
                    symbolStack.pop();
                    temp = "";
                }
                symbolStack.push(c);
            }
        } else if (c == '(' || c == '[' || c == '{') {
            symbolStack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            while (getSymbol_lv(symbolStack.top()) != getSymbol_lv(c)) {
                temp += symbolStack.top();
                stdFormat.push_back(temp);
                symbolStack.pop();
                temp = "";
            }
            symbolStack.pop();
        } else if (c >= '0' && c <= '9') {
            temp += c;
            while (i + 1 < input.size() && (getSymbol_lv(input.at(i + 1)) == 2 || input.at(i + 1) == '.')) {
                temp += input.at(i + 1);
                i++;
            }
            stdFormat.push_back(temp);
        }
    }
    while (!symbolStack.empty()) {
        string temp;
        temp += symbolStack.top();
        stdFormat.push_back(temp);
        symbolStack.pop();
    }
}

string Calculate::calculate() {
    for (string s: stdFormat) {
        char c = s.at(0);
        if (getSymbol_lv(c) == 2) {
            computeStack.push(s);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            string num2 = computeStack.top();
            computeStack.pop();
            string num1 = computeStack.top();
            computeStack.pop();
            if (c == '+') {
                computeStack.push(add(num1, num2));
            } else if (c == '-') {
                computeStack.push(subtract(num1, num2));
            } else if (c == '*') {
                computeStack.push(multiply(num1, num2));
            } else {
                computeStack.push(divide(num1, num2));
                if (computeStack.top() == "error") {
                    return "Divide by 0 is not allowed!";
                }
            }
        }
    }
    return computeStack.top();
}
