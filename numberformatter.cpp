#include "numberformatter.h"

std::string NumberFormatter::format(double value) {
    constexpr int MAX_DECIMALS = 15;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(MAX_DECIMALS) << value;
    std::string result = oss.str();

    removeTrailingZeros(result);

    if (result == "0" && std::abs(value) > std::numeric_limits<double>::min()) {
        int decimals = static_cast<int>(std::ceil(-std::log10(std::abs(value))));
        decimals = std::min(decimals, MAX_DECIMALS);

        oss.str("");
        oss << std::fixed << std::setprecision(decimals) << value;
        result = oss.str();
        removeTrailingZeros(result);
    }

    return result;
}

void NumberFormatter::removeTrailingZeros(std::string& str) {
    size_t dotPos = str.find('.');
    if (dotPos != std::string::npos) {
        str = str.substr(0, str.find_last_not_of('0') + 1);

        if (!str.empty() && str.back() == '.')
            str.pop_back();
    }
}
