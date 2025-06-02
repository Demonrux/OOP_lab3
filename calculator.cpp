#include "calculator.h"
#include "calculationerror.h"
#include <stack>
#include <map>
#include <cmath>
#include <sstream>
#include <cctype>
#include <regex>

namespace {
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
}

Calculator::Calculator() {}
Calculator::~Calculator() {}

void Calculator::processOperator(std::stack<char>& operators, std::stack<double>& values) {
    char op = operators.top();
    operators.pop();

    if (op == '~') {
        if (values.empty()) {
            throw CalculationError("Invalid unary operator");
        }
        double val = values.top();
        values.pop();
        values.push(-val);
        return;
    }

    if (values.size() < 2) {
        throw CalculationError("Not enough values for operation");
    }
    double val2 = values.top();
    values.pop();
    double val1 = values.top();
    values.pop();
    values.push(applyOperation(val1, val2, op));
}

double Calculator::applyOperation(double a, double b, char op) {
    const double epsilon = 1e-10;

    switch(op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (fabs(b) < epsilon) {
            throw CalculationError("Division by zero");
        }
        return a / b;
    default:
        throw CalculationError("Unknown operator");
    }

}

std::string normalizeNumber(std::string num) {
    if (num.empty()) return "0";
    if (num[0] == '.') return "0" + num;
    if (num.back() == '.') return num + "0";
    return num;
}

int Calculator::getPrecedence(char op) {
    switch(op) {
    case '~': return 4;
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    default:
        throw CalculationError("Unknown operator");
    }
}

double Calculator::calculate(const std::string& expression) {
    std::regex invalidOps(R"([\+\-\*\/]{2,})");
    if (std::regex_search(expression, invalidOps)) {
        throw CalculationError("Invalid operator sequence");
    }

    std::stack<char> operators;
    std::stack<double> values;
    bool expectUnary = true;

    for (size_t i = 0; i < expression.length(); ) {
        if (expression[i] == ' ') {
            i++;
            continue;
        }

        if (expression[i] == '(') {
            operators.push('(');
            i++;
            expectUnary = true;
            continue;
        }

        if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                processOperator(operators, values);
            }
            if (operators.empty())
                throw CalculationError("Mismatched parentheses");

            operators.pop();
            i++;
            expectUnary = false;
            continue;
        }

        if (isOperator(expression[i])) {
            char currentOp = expression[i];
            if (expectUnary && currentOp == '-')
                currentOp = '~';

            while (!operators.empty() && operators.top() != '(' &&
                   getPrecedence(operators.top()) >= getPrecedence(currentOp)) {
                processOperator(operators, values);
            }
            operators.push(currentOp);
            i++;
            expectUnary = true;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.') {
            std::stringstream numStr;
            while (i < expression.length() &&
                   (isdigit(expression[i]) || expression[i] == '.')) {
                numStr << expression[i];
                i++;
            }

            double num;
            if (!(numStr >> num))
                throw CalculationError("Invalid number format");

            values.push(num);
            expectUnary = false;
            continue;
        }

        throw CalculationError("Invalid character in expression");
    }

    while (!operators.empty()) {
        if (operators.top() == '(')
            throw CalculationError("Mismatched parentheses");

        processOperator(operators, values);
    }

    if (values.size() != 1)
        throw CalculationError("Invalid expression");

    return values.top();
}

bool Calculator::isValidExpression(const std::string& expression) {
    std::stack<char> parens;
    for (char c : expression) {
        if (c == '(') parens.push(c);
        else if (c == ')') {
            if (parens.empty()) return false;
            parens.pop();
        }
    }
    return parens.empty();
}

double Calculator::squareRoot(double x) {
    if (x < 0)
        throw CalculationError("Square root of negative number");

    return std::sqrt(x);
}

double Calculator::reciprocal(double x) {
    if (x == 0)
        throw CalculationError("Division by zero");

    return 1.0 / x;
}

double Calculator::sine(double x) {
    return std::sin(x);
}

double Calculator::cosine(double x) {
    return std::cos(x);
}

double Calculator::tangent(double x) {
    if (std::cos(x) == 0)
        throw CalculationError("Tangent undefined");

    return std::tan(x);
}

double Calculator::cotangent(double x) {
    if (std::sin(x) == 0)
        throw CalculationError("Cotangent undefined");

    return 1.0 / std::tan(x);
}
