#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calculationerror.h"
#include <stack>
#include <string>

class Calculator {
public:
    Calculator();
    ~Calculator();

    double calculate(const std::string& expression);
    bool isValidExpression(const std::string& expression);
    void processOperator(std::stack<char>& operators, std::stack<double>& values);
    double applyOperation(double a, double b, char op);
    int getPrecedence(char op);
    double squareRoot(double x);
    double reciprocal(double x);
    double sine(double x);
    double cosine(double x);
    double tangent(double x);
    double cotangent(double x);
};

#endif // CALCULATOR_H
