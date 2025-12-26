#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>
#include <stdexcept>
#include "CalculatorCore.h"

enum class TokenType {
    Number,
    Operator,
    Function,
    LeftParenthesis,
    RightParenthesis
};

struct Token {
    TokenType type;
    std::string value;
    int precedence;
    bool rightAssociative;
};

class Calculator {
public:
    double evaluate(const std::string& expression) {
        auto tokens = tokenize(expression);
        auto rpn = shuntingYard(tokens);
        return calculateRPN(rpn);
    }

private:
    std::vector<Token> tokenize(const std::string& expression) {
        std::vector<Token> tokens;
        for (size_t i = 0; i < expression.length(); ++i) {
            char c = expression[i];
            if (isspace(c)) continue;

            if (isdigit(c) || c == '.') {
                std::string num;
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                    num += expression[i++];
                }
                --i;
                tokens.push_back({TokenType::Number, num, 0, false});
            } else if (isalpha(c)) {
                std::string func;
                while (i < expression.length() && isalpha(expression[i])) {
                    func += expression[i++];
                }
                --i;
                tokens.push_back({TokenType::Function, func, 4, false});
            } else if (c == '(') {
                tokens.push_back({TokenType::LeftParenthesis, "(", 0, false});
            } else if (c == ')') {
                tokens.push_back({TokenType::RightParenthesis, ")", 0, false});
            } else {
                // Handle unary minus
                if (c == '-' && (tokens.empty() || tokens.back().type == TokenType::Operator || tokens.back().type == TokenType::LeftParenthesis)) {
                    tokens.push_back({TokenType::Number, "0", 0, false});
                }
                
                std::string op(1, c);
                int prec = 0;
                bool rightAssoc = false;
                if (c == '+' || c == '-') prec = 2;
                else if (c == '*' || c == '/') prec = 3;
                else if (c == '^') { prec = 4; rightAssoc = true; }
                
                tokens.push_back({TokenType::Operator, op, prec, rightAssoc});
            }
        }
        return tokens;
    }

    std::queue<Token> shuntingYard(const std::vector<Token>& tokens) {
        std::queue<Token> outputQueue;
        std::stack<Token> operatorStack;

        for (const auto& token : tokens) {
            if (token.type == TokenType::Number) {
                outputQueue.push(token);
            } else if (token.type == TokenType::Function) {
                operatorStack.push(token);
            } else if (token.type == TokenType::Operator) {
                while (!operatorStack.empty() && operatorStack.top().type != TokenType::LeftParenthesis) {
                    auto o2 = operatorStack.top();
                    if ((!token.rightAssociative && token.precedence <= o2.precedence) ||
                        (token.rightAssociative && token.precedence < o2.precedence)) {
                        outputQueue.push(o2);
                        operatorStack.pop();
                    } else {
                        break;
                    }
                }
                operatorStack.push(token);
            } else if (token.type == TokenType::LeftParenthesis) {
                operatorStack.push(token);
            } else if (token.type == TokenType::RightParenthesis) {
                while (!operatorStack.empty() && operatorStack.top().type != TokenType::LeftParenthesis) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty()) operatorStack.pop(); // Pop '('
                if (!operatorStack.empty() && operatorStack.top().type == TokenType::Function) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
            }
        }

        while (!operatorStack.empty()) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }

        return outputQueue;
    }

    double calculateRPN(std::queue<Token>& rpn) {
        std::stack<double> stack;
        while (!rpn.empty()) {
            Token token = rpn.front();
            rpn.pop();

            if (token.type == TokenType::Number) {
                stack.push(std::stod(token.value));
            } else if (token.type == TokenType::Operator) {
                if (stack.size() < 2) throw std::runtime_error("Invalid expression");
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();
                if (token.value == "+") stack.push(a + b);
                else if (token.value == "-") stack.push(a - b);
                else if (token.value == "*") stack.push(a * b);
                else if (token.value == "/") {
                    if (b == 0) throw std::runtime_error("Division by zero");
                    stack.push(a / b);
                }
                else if (token.value == "^") stack.push(std::pow(a, b));
            } else if (token.type == TokenType::Function) {
                if (stack.empty()) throw std::runtime_error("Invalid expression");
                double a = stack.top(); stack.pop();
                if (token.value == "sin") stack.push(std::sin(a));
                else if (token.value == "cos") stack.push(std::cos(a));
                else if (token.value == "tan") stack.push(std::tan(a));
                else if (token.value == "log") stack.push(std::log10(a));
                else if (token.value == "ln") stack.push(std::log(a));
                else if (token.value == "sqrt") stack.push(std::sqrt(a));
            }
        }
        if (stack.size() != 1) throw std::runtime_error("Invalid expression");
        return stack.top();
    }
};

extern "C" {
    double add(double a, double b) {
        return a + b;
    }

    double calculate(const char* expression, int* errorCode) {
        try {
            Calculator calc;
            if (errorCode) *errorCode = 0;
            return calc.evaluate(expression);
        } catch (const std::exception& e) {
            if (errorCode) *errorCode = 1;
            return 0.0;
        }
    }
}