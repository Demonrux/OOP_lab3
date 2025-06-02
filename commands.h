#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"
#include <cctype>

class AppendCommand : public Command {
public:
    AppendCommand(const std::string& text) : mText(text) {}

    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        if (mText == ".") {
            if (!currentText.empty() && currentText.back() == ')') {
                calculator.notifyError("Decimal point after parenthesis is not allowed");
                return currentText;
            }

            if (currentText.empty() || isOperator(currentText.back()))
                return currentText + "0.";

            std::string lastNum;
            for (auto it = currentText.rbegin(); it != currentText.rend(); ++it) {
                char c = *it;
                if (std::isdigit(c) || c == '.') {
                    lastNum.insert(0, 1, c);
                } else {
                    break;
                }
            }

            if (lastNum.find('.') != std::string::npos)  {
                calculator.notifyError("Number already has decimal point");
                return currentText;
            }

            return currentText + ".";
        }
        return currentText + mText;
    }

private:
    std::string mText;
    bool isOperator(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
};

class CalculateCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        return calculateFirst(calculator, currentText);
    }
};

class ClearCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        return "";
    }
};

class DeleteCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        if (currentText.empty()) return currentText;
        return currentText.substr(0, currentText.length() - 1);
    }
};

class SquareRootCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.squareRoot(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

class ReciprocalCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.reciprocal(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

class SineCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.sine(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

class CosineCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.cosine(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

class TangentCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.tangent(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

class CotangentCommand : public Command {
public:
    std::string execute(CalculatorFacade& calculator, const std::string& currentText) override {
        try {
            std::string valueStr = calculateFirst(calculator, currentText);
            double value = std::stod(valueStr);
            return calculator.formatNumber(calculator.cotangent(value));
        }
        catch (const CalculationError& error) {
            calculator.notifyError(error.what());
            return currentText;
        }
    }
};

#endif // COMMANDS_H
