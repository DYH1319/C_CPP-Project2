#include <string>
#include <map>
#include "stack"
#include "vector"

using namespace std;

//Character level
enum SYMBOL_LV {
    LV0 = 0,    //Others
    LV1 = 1,    //' ','.'
    LV2 = 2,    //'0'~'9'
    LV3 = 3,    //'+','-'
    LV4 = 4,    //'*','/'
    LV5 = 5,    //'{','}'
    LV6 = 6,    //'[',']'
    LV7 = 7,    //'(',')'
};

struct Calculate {
    string input;                   //User input
    stack<char> symbolStack;        //Symbol stack, used to store the symbols that appear
    stack<string> computeStack;     //Compute stack, used for computing
    vector<string> stdFormat;       //Customized standardization order
    map<string, string> customVar;  //Mapping of custom variables to their values

    Calculate();                            //Constructor
    void trimSpace();                       //Clear space in expression
    static int getSymbol_lv(char symbol);   //Get the level of the character
    bool checkIsAssignmentExpression();     //Judge whether the input is a formula or an assignment statement
    void convertVariablesToNumber();        //Replace the variable in the expression with its value
    bool checkValidity() const;             //Check the validity of expressions
    void standardise();                     //Change "-*" to "0-*", and change "+*" to "0+*"
    void convertToStandardFormat();         //Convert to custom standardized order
    string calculate();                     //Calculate
};

