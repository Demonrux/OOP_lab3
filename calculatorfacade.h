#ifndef CALCULATORFACADE_H
#define CALCULATORFACADE_H

#include "calculator.h"
#include "calculationerror.h"
#include "numberformatter.h"
#include <functional>
#include <string>

class CalculatorFacade {
public:
    using ErrorHandler = std::function<void(const std::string&)>;
    std::string formatNumber(double value) const;

    explicit CalculatorFacade(ErrorHandler errorHandler = nullptr);

    double calculate(const std::string& expression);
    void clear();
    double squareRoot(double x);
    double reciprocal(double x);
    double sine(double x);
    double cosine(double x);
    double tangent(double x);
    double cotangent(double x);
    void notifyError(const std::string& message) const;

private:
    Calculator calculator;
    ErrorHandler errorHandler;
};

#endif // CALCULATORFACADE_H
