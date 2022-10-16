#include "string"
#include <regex>
#include "calculate.hpp"

using namespace std;

string addInteger(string num1, string num2);

string subtractInteger(string num1, string num2);

string multiplyInteger(string num1, string num2);

string add(string num1, string num2) {
    if (num1.at(0) != '-' && num2.at(0) == '-') {
        num2 = num2.substr(1);
        return subtract(num1, num2);
    } else if (num1.at(0) == '-' && num2.at(0) != '-') {
        num1 = num1.substr(1);
        return subtract(num2, num1);
    } else if (num1.at(0) == '-' && num2.at(0) == '-') {
        num1 = num1.substr(1);
        num2 = num2.substr(1);
        return "-" + add(num1, num2);
    } else {
        string *result = addZeroToSameLengthAndRemoveSpot(num1, num2);
        num1 = result[0];
        num2 = result[1];
        int countNum1Digits = atoi(result[2].c_str());
        int countNum2Digits = atoi(result[3].c_str());

        delete[] result;

        string res = addInteger(num1, num2);
        if (countNum1Digits != 0 || countNum2Digits != 0) {
            res = res.insert(res.size() - countNum1Digits, ".");
        }

        return removeZero(res);
    }
}

string addInteger(string num1, string num2) {
    int num1Size = (int) num1.size();
    vector<int> ansArr = vector<int>(num1.size() + 1);

    for (int i = num1Size - 1; i >= 0; i--) {
        int x = num1.at(i) - '0';
        int y = num2.at(i) - '0';
        ansArr[i + 1] = x + y;
    }

    for (int i = num1Size; i > 0; i--) {
        ansArr[i - 1] += ansArr[i] / 10;
        ansArr[i] %= 10;
    }

    int index = (ansArr[0] == 0 ? 1 : 0);
    string ans;

    while (index <= num1Size) {
        ans += to_string(ansArr[index]);
        index++;
    }

    return ans;
}

string subtract(string num1, string num2) {
    if (num1.at(0) != '-' && num2.at(0) == '-') {
        num2 = num2.substr(1);
        return add(num1, num2);
    } else if (num1.at(0) == '-' && num2.at(0) != '-') {
        num1 = num1.substr(1);
        return "-" + add(num1, num2);
    } else if (num1.at(0) == '-' && num2.at(0) == '-') {
        num1 = num1.substr(1);
        num2 = num2.substr(1);
        return subtract(num2, num1);
    } else {
        string *result = addZeroToSameLengthAndRemoveSpot(num1, num2);
        num1 = result[0];
        num2 = result[1];
        int countNum1Digits = atoi(result[2].c_str());
        int countNum2Digits = atoi(result[3].c_str());

        delete[] result;

        int num1Bigger = compareValue(num1, num2);

        if (num1Bigger == 1) {
            string res = subtractInteger(num1, num2);
            if (countNum1Digits != 0 || countNum2Digits != 0) {
                res = res.insert(res.size() - countNum1Digits, ".");
            }
            return removeZero(res);
        } else if (num1Bigger == -1) {
            string res = subtractInteger(num2, num1);
            if (countNum1Digits != 0 || countNum2Digits != 0) {
                res = res.insert(res.size() - countNum1Digits, ".");
            }
            return "-" + removeZero(res);
        } else {
            return "0";
        }
    }
}

string subtractInteger(string num1, string num2) {
    int num1Size = (int) num1.size();
    vector<int> ansArr = vector<int>(num1.size() + 1);

    for (int i = num1Size - 1; i >= 0; i--) {
        int x = num1.at(i) - '0';
        int y = num2.at(i) - '0';
        ansArr[i + 1] = x - y;
    }

    for (int i = num1Size; i > 1; i--) {
        if (ansArr[i] < 0) {
            ansArr[i - 1]--;
            ansArr[i] += 10;
        }
    }

    int index = 1;
    string ans;

    while (index <= num1Size) {
        ans += to_string(ansArr[index]);
        index++;
    }

    return ans;
}

string multiply(string num1, string num2) {
    bool num1IsPositive = true;
    bool num2IsPositive = true;
    if (num1.at(0) == '-') {
        num1IsPositive = false;
        num1 = num1.substr(1);
    }
    if (num2.at(0) == '-') {
        num2IsPositive = false;
        num2 = num2.substr(1);
    }

    string beforeResult;
    if ((num1IsPositive ^ num2IsPositive)) {
        beforeResult = "-";
    } else {
        beforeResult = "";
    }

    int num1PointIndex = (int) num1.find('.');
    int num2PointIndex = (int) num2.find('.');
    int countDigits = 0;

    if (num1PointIndex > 0) {
        countDigits += (int) num1.size() - num1PointIndex - 1;
        num1.erase(remove(num1.begin(), num1.end(), '.'), num1.end());
    }
    if (num2PointIndex > 0) {
        countDigits += (int) num2.size() - num2PointIndex - 1;
        num2.erase(remove(num2.begin(), num2.end(), '.'), num2.end());
    }

    string res = multiplyInteger(num1, num2);
    if (num1PointIndex > 0 || num2PointIndex > 0) {
        res = res.insert(res.size() - countDigits, ".");
    }

    return beforeResult + removeZero(res);
}

string multiplyInteger(string num1, string num2) {

    if (removeZero(num1) == "0" || removeZero(num2) == "0") {
        return "0";
    }

    int num1Size = (int) num1.size(), num2Size = (int) num2.size();
    vector<int> ansArr = vector<int>(num1Size + num2Size); //可变数组记录其中一个数的每一位与另一个数的每一位依次相乘的结果

    for (int i = num1Size - 1; i >= 0; i--) {
        int x = num1.at(i) - '0';
        for (int j = num2Size - 1; j >= 0; j--) {
            int y = num2.at(j) - '0';
            ansArr[i + j + 1] += x * y;
        }
    }

    for (int i = num1Size + num2Size - 1; i > 0; i--) {
        ansArr[i - 1] += ansArr[i] / 10;
        ansArr[i] %= 10;
    }

    int index = (ansArr[0] == 0 ? 1 : 0);
    string ans;

    while (index < num1Size + num2Size) {
        ans += to_string(ansArr[index]);
        index++;
    }

    return ans;
}

string divide(string num1, string num2) {
    if (removeZero(num2) == "0") {
        return "error";
    }
    bool num1IsPositive = true;
    bool num2IsPositive = true;
    if (num1.at(0) == '-') {
        num1IsPositive = false;
        num1 = num1.substr(1);
    }
    if (num2.at(0) == '-') {
        num2IsPositive = false;
        num2 = num2.substr(1);
    }

    string beforeResult;
    if ((num1IsPositive ^ num2IsPositive)) {
        beforeResult = "-";
    } else {
        beforeResult = "";
    }

    int num1PointIndex = (int) num1.find('.');
    int num2PointIndex = (int) num2.find('.');
    int countNum1Digits = 0;
    int countNum2Digits = 0;

    if (num1PointIndex > 0) {
        countNum1Digits = (int) num1.size() - num1PointIndex - 1;
        num1.erase(remove(num1.begin(), num1.end(), '.'), num1.end());
    }
    if (num2PointIndex > 0) {
        countNum2Digits += (int) num2.size() - num2PointIndex - 1;
        num2.erase(remove(num2.begin(), num2.end(), '.'), num2.end());
    }

    int firstTimes = 0;
    while (compareValue(num1, num2) >= 0) {
        num1 = subtract(num1, num2);
        firstTimes++;
    }
    string ans = to_string(firstTimes);
    ans.append(".");

    for (int i = 0; i < 101; i++) {
        num1.append("0");
        int times = 0;
        while (compareValue(num1, num2) >= 0) {
            num1 = subtract(num1, num2);
            times++;
        }
        ans.append(to_string(times));
    }

    if (countNum1Digits > countNum2Digits) {
        for (int i = 0; i < countNum1Digits - countNum2Digits; i++) {
            ans = multiply(ans, "0.1");
        }
    } else if (countNum1Digits < countNum2Digits) {
        for (int i = 0; i < countNum2Digits - countNum1Digits; i++) {
            ans = multiply(ans, "10");
        }
    }
    return beforeResult + removeZero(ans);
}

//if num1 > num2, return 1; if num1 < num2, return -1; otherwise, return 0.
int compareValue(string num1, string num2) {
    if ((removeZero(num1) == "0" || removeZero(num1) == "-0") && (removeZero(num2) == "0" || removeZero(num2) == "-0")) {
        return 0;
    }

    bool num1IsPositive = true;
    bool num2IsPositive = true;
    if (num1.at(0) == '-') {
        num1IsPositive = false;
    }
    if (num2.at(0) == '-') {
        num2IsPositive = false;
    }

    if (num1IsPositive && !num2IsPositive) {
        return 1;
    } else if (!num1IsPositive && num2IsPositive) {
        return -1;
    } else if (!num1IsPositive && !num2IsPositive) {
        return compareValue(num2, num1);
    } else {
        string *res = addZeroToSameLengthAndRemoveSpot(num1, num2);
        num1 = res[0];
        num2 = res[1];
        delete[] res;

        for (int i = 0; i < (int) num1.size(); i++) {
            if (num1.at(i) > num2.at(i)) {
                return 1;
            } else if (num1.at(i) < num2.at(i)) {
                return -1;
            }
        }
        return 0;
    }
}

string *addZeroToSameLengthAndRemoveSpot(string num1, string num2) {
    int num1PointIndex = (int) num1.find('.');
    int num2PointIndex = (int) num2.find('.');
    int countNum1Digits = 0;
    int countNum2Digits = 0;
    int num1Size = (int) num1.size();
    int num2Size = (int) num2.size();

    if (num1PointIndex > 0) {
        countNum1Digits = num1Size - num1PointIndex - 1;
        num1.erase(remove(num1.begin(), num1.end(), '.'), num1.end());
    }
    if (num2PointIndex > 0) {
        countNum2Digits = num2Size - num2PointIndex - 1;
        num2.erase(remove(num2.begin(), num2.end(), '.'), num2.end());
    }

    if (countNum1Digits != 0 || countNum2Digits != 0) {
        if (countNum1Digits > countNum2Digits) {
            for (int i = 0; i < countNum1Digits - countNum2Digits; i++) {
                num2.insert(num2.size(), 1, '0');
            }
            countNum2Digits = countNum1Digits;
        } else if (countNum1Digits < countNum2Digits) {
            for (int i = 0; i < countNum2Digits - countNum1Digits; i++) {
                num1.insert(num1.size(), 1, '0');
            }
            countNum1Digits = countNum2Digits;
        }
    }

    if (num1PointIndex == -1) {
        num1PointIndex = num1Size;
    }
    if (num2PointIndex == -1) {
        num2PointIndex = num2Size;
    }

    if (num1PointIndex > num2PointIndex) {
        for (int i = 0; i < num1PointIndex - num2PointIndex; i++) {
            num2.insert(0, 1, '0');
        }
    } else if (num1PointIndex < num2PointIndex) {
        for (int i = 0; i < num2PointIndex - num1PointIndex; i++) {
            num1.insert(0, 1, '0');
        }
    }

    auto *res = new string[4]{num1, num2, to_string(countNum1Digits), to_string(countNum2Digits)};
    return res;
}

string removeZero(string num) {
    bool numIsPositive = true;
    if (num.at(0) == '-') {
        numIsPositive = false;
        num = num.substr(1);
    }

    int numPointIndex = (int) num.find('.');

    if (numPointIndex < 0) {
        for (int i = 0; i < num.size(); i++) {
            if (num.at(i) != '0') {
                return (numIsPositive ? "" : "-") + num.substr(i);
            }
        }
        return "0";
    } else {
        string left, right;
        for (int i = 0; i < numPointIndex; i++) {
            if (num.at(i) != '0') {
                left = num.substr(i, numPointIndex - i);
                goto label1;
            }
        }
        left = "0";

        label1:
        for (int i = (int) num.size() - 1; i > numPointIndex; i--) {
            if (num.at(i) != '0') {
                right = num.substr(numPointIndex + 1, num.size() - 1 - numPointIndex - (num.size() - 1 - i));
                goto label2;
            }
        }
        right = "0";

        label2:
        if (left == "0" && right == "0") {
            return "0";
        } else {
            return (numIsPositive ? "" : "-") + left + (right == "0" ? "" : "." + right);
        }
    }
}
