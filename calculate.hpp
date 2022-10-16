#include "string"

using namespace std;

string add(string num1, string num2);       //Add two numbers in string form

string subtract(string num1, string num2);  //Subtract two numbers in string form

string multiply(string num1, string num2);  //Multiplying two numbers in string form

string divide(string num1, string num2);    //Divide two numbers in string form

int compareValue(string num1, string num2); //Compare the size of two string numbers

//By adding 0 before the integer part and after the decimal part, the two numbers have the same length, which is convenient for calculation
string *addZeroToSameLengthAndRemoveSpot(string num1, string num2);

string removeZero(string num);  //Remove the redundant 0