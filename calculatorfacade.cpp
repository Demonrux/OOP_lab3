#include "calculatorfacade.h"

CalculatorFacade::CalculatorFacade(ErrorHandler errorHandler): errorHandler(std::move(errorHandler)),calculator() {}

double CalculatorFacade::calculate(const std::string& expression) {
    try {
        return calculator.calculate(expression);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

void CalculatorFacade::clear() {
}

double CalculatorFacade::squareRoot(double x) {
    try {
        return calculator.squareRoot(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

double CalculatorFacade::reciprocal(double x) {
    try {
        return calculator.reciprocal(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

double CalculatorFacade::sine(double x) {
    try {
        return calculator.sine(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

double CalculatorFacade::cosine(double x) {
    try {
        return calculator.cosine(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

double CalculatorFacade::tangent(double x) {
    try {
        return calculator.tangent(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

double CalculatorFacade::cotangent(double x) {
    try {
        return calculator.cotangent(x);
    }
    catch (const CalculationError& error) {
        notifyError(error.what());
        throw;
    }
}

std::string CalculatorFacade::formatNumber(double value) const {
    return NumberFormatter::format(value);
}

void CalculatorFacade::notifyError(const std::string& message) const {
    if (errorHandler)
        errorHandler(message);
}
