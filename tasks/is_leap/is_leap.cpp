#include "is_leap.h"

bool IsLeap(int year) {
    const int four = 4;
    const int hundred = 100;
    const int four_hundreds = 400;
    return (year % four == 0 && year % hundred != 0) || (year % four_hundreds == 0)
}
