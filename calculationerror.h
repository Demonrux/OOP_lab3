#ifndef CALCULATIONERROR_H
#define CALCULATIONERROR_H

#include <stdexcept>
#include <string>

class CalculationError : public std::runtime_error {
public:
    explicit CalculationError(const std::string& whatArg): std::runtime_error(whatArg) {}
};

#endif // CALCULATIONERROR_H
