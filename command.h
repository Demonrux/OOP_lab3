#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "calculatorfacade.h"

class Command {
public:
    virtual ~Command() = default;
    virtual std::string execute(CalculatorFacade& calculator, const std::string& currentText) = 0;

protected:
    std::string calculateFirst(CalculatorFacade& calculator, const std::string& currentText) {
        if (currentText.empty()) {
            calculator.notifyError("Empty expression");
            return currentText;
        }

        try {
            return calculator.formatNumber(calculator.calculate(currentText));
        }
        catch (const CalculationError&) {
            return currentText;
        }
    }
};

#endif // COMMAND_H
