#ifndef NUMBERFORMATTER_H
#define NUMBERFORMATTER_H

#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <iomanip>
#include <algorithm>

class NumberFormatter {
public:
    static std::string format(double value);

private:
    NumberFormatter() = delete;
    ~NumberFormatter() = delete;

    static void removeTrailingZeros(std::string& str);
};

#endif // NUMBERFORMATTER_H
