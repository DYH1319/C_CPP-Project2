#include <string>
#include "stack"
#include "vector"

using namespace std;

enum SYMBOL_LV {
    LV0 = 0,
    LV1 = 1,
    LV2 = 2,
    LV3 = 3,
    LV4 = 4,
    LV5 = 5,
    LV6 = 6,
    LV7 = 7,
};

struct Calculate {
    string input;
    stack<char> symbolStack;
    stack<string> computeStack;
    vector<string> stdFormat;

    Calculate();
    static int getSymbol_lv(char symbol);
    bool checkValidity() const;
    void standardise();
    void convertToStandardFormat();
    string calculate();
};

