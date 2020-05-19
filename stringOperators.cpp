#include "stringOperators.h"


std::string toUpperCase(const std::string& str) {
    std::string str2 = str;
    toUpperCaseInPlace(str2);
    return str2;
}

void toUpperCaseInPlace(std::string& str) {
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        str[i] = toupper(str[i]);
    }
}
