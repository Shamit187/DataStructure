#include <iostream>
#include "Stack.h"
#include <string>
#include <cctype>
#include <stdexcept>
#include "Queue.h"

float calculate(float var1, float var2, char operation) {
    switch (operation) {
        case '+':
            return var1 + var2;
        case '-':
            return var1 - var2;
        case '*':
            return var1 * var2;
        case '/':
            if (var2 == 0){
                throw std::logic_error("Expression invalid");
            }
            return var1 / var2;
        default:
            throw std::logic_error("Expression invalid");
    }
}
float expressionEvaluation(const std::string& expression){

    char token;
    char prevToken = ' ';
    bool decimalPoint = false;
    int decimalPlace = 10;

    Stack<float>operandStack;
    Stack<char>operatorStack;

    for(int i = 0; i < expression.size(); i++){

        token = expression[i];

        if(isdigit(token) || token == '.'){

            if(token == '.'){
                if(decimalPoint)throw std::logic_error("Expression invalid");
                decimalPoint = true;
                prevToken = token;
            }else {
                int dig = token - '0';
                float digit = (float)dig;
                if (isdigit(prevToken) || prevToken == '.') {
                    float totalValue = operandStack.seeTop();
                    operandStack.pop();
                    if(!decimalPoint)totalValue = totalValue * 10 + digit;
                    else {
                        totalValue = totalValue * decimalPlace + digit;
                        totalValue /= decimalPlace;
                        decimalPlace *= 10;
                    }
                    operandStack.push(totalValue);
                } else {
                    operandStack.push(digit);
                }
                prevToken = token;
            }
        }
        else{
            decimalPoint = false;
            decimalPlace = 10;
            switch (token) {

                case '+':
                    if(!operatorStack.isEmpty() && (operatorStack.seeTop() == '*' || operatorStack.seeTop() == '/')){
                        while(operatorStack.seeTop() == '*' || operatorStack.seeTop() == '/') {
                            float var2 = operandStack.seeTop();
                            operandStack.pop();
                            float var1 = operandStack.seeTop();
                            operandStack.pop();
                            char operation = operatorStack.seeTop();
                            operatorStack.pop();
                            float calculatedValue = 0;
                            try {
                                calculatedValue = calculate(var1, var2, operation);
                            } catch (const std::exception &e) {
                                throw std::logic_error("Expression invalid");
                            }
                            operandStack.push(calculatedValue);
                        }
                        operatorStack.push(token);
                    }else{
                        operatorStack.push(token);
                    }

                    prevToken = token;

                    break;


                case '-':
                    if(!isdigit(prevToken) && prevToken != ')'){
                        if(prevToken != '('){
                            throw std::logic_error("Expression invalid");
                        }
                        else{
                            float negativeValue = 0;
                            float digit = 0;
                            i++;
                            if (i == expression.size()) throw std::logic_error("Expression invalid");
                            while(expression[i] != ')'){
                                if(!isdigit(expression[i]) && expression[i] != '.') throw std::logic_error("Expression invalid");
                                if(expression[i] == '.'){
                                    if(decimalPoint)throw std::logic_error("Expression invalid");
                                    decimalPoint = true;
                                }else {
                                    int dig = expression[i] - '0';
                                    digit = (float)dig;
                                    if (!decimalPoint) {
                                        negativeValue = -negativeValue;
                                        negativeValue = negativeValue * 10 + digit;
                                        negativeValue = -negativeValue;
                                    }
                                    else {
                                        negativeValue = -negativeValue;
                                        negativeValue = negativeValue * decimalPlace + digit;
                                        negativeValue = -negativeValue;
                                        negativeValue /= decimalPlace;
                                        decimalPlace *= 10;
                                    }
                                }
                                i++;
                            }
                            operatorStack.pop();
                            operandStack.push(negativeValue);
                            decimalPoint = false;
                        }

                        prevToken = expression[i];
                        break;
                    }

                    if(!operatorStack.isEmpty() && (operatorStack.seeTop() == '*' || operatorStack.seeTop() == '/')){
                        while(operatorStack.seeTop() == '*' || operatorStack.seeTop() == '/') {
                            float var2 = operandStack.seeTop();
                            operandStack.pop();
                            float var1 = operandStack.seeTop();
                            operandStack.pop();
                            char operation = operatorStack.seeTop();
                            operatorStack.pop();
                            float calculatedValue = 0;
                            try {
                                calculatedValue = calculate(var1, var2, operation);
                            } catch (const std::exception &e) {
                                throw std::logic_error("Expression invalid");
                            }
                            operandStack.push(calculatedValue);
                        }
                        operatorStack.push(token);
                    }else{
                        operatorStack.push(token);
                    }

                    prevToken = token;

                    break;

                case '*': case '/': case '(':
                    operatorStack.push(token);

                    prevToken = token;

                    break;

                case ')':
                    while(operatorStack.seeTop() != '(') {
                        float var2 = 0;
                        try {
                            var2 = operandStack.seeTop();
                            operandStack.pop();
                        } catch (const std::exception &e) {
                            throw std::logic_error("Expression invalid");
                        }
                        float var1 = 0;
                        try {
                            var1 = operandStack.seeTop();
                            operandStack.pop();
                        } catch (const std::exception &e) {
                            throw std::logic_error("Expression invalid");
                        }
                        char operation = ' ';
                        try {
                            operation = operatorStack.seeTop();
                            operatorStack.pop();
                        } catch (const std::exception &e) {
                            throw std::logic_error("Expression invalid");
                        }
                        float calculatedValue = 0;
                        try {
                            calculatedValue = calculate(var1, var2, operation);
                        } catch (const std::exception &e) {
                            throw std::logic_error("Expression invalid");
                        }
                        operandStack.push(calculatedValue);
                    }
                    operatorStack.pop();

                    prevToken = token;

                    break;
                case ' ':case '\n':
                    if(prevToken == '.')throw std::logic_error("Expression invalid");
                    //ignore
                    break;
                default:
                    throw std::logic_error("Expression invalid");
            }
        }
    }

    if(!operatorStack.isEmpty()){
        throw std::logic_error("Expression invalid");
    }
    return operandStack.seeTop();
}

std::string firstNonRepeat(std::string charString){
    std::string returnString;
    Queue<char> charQueue;
    char charMap[26];
    for(int i = 0; i < 26; i++){
        charMap[i] = 0;
    }

    for(int i = 0; i < charString.size(); i++){
        char x = tolower(charString[i]);
        if(x == ' ' || x == '\n') continue;

        if((x - 'a') < 0 || (x - 'a') > 26) throw std::out_of_range("Character Not Valid");
        charQueue.enqueue(x);
        charMap[x - 'a']++;

        if(charMap[charQueue.seeFront() - 'a'] > 1){
            while(charMap[charQueue.seeFront() - 'a'] > 1 && !charQueue.isEmpty()){
                charQueue.dequeue();
                if(charQueue.isEmpty())break;
            }
            if(charQueue.isEmpty()) returnString.push_back('#');
            else returnString.push_back(charQueue.seeFront());
        }
        else returnString.push_back(charQueue.seeFront());
     }

    return returnString;
}

int main() {
    std::cout << "Expression evaluation" << std::endl << "Type \"Stop\" to end" << std::endl;
    while(true) {
        std::string expression;
        std::getline(std::cin , expression);
        if(expression == "Stop")break;
        expression.insert(expression.begin(), '(');
        expression.insert(expression.end(), ')');
        float value = 0;
        try {
            value = expressionEvaluation(expression);
            if(value == int(value)){
                value = int(value);
            }
            std::cout << value << std::endl;
        } catch (std::exception &e) {
            std::cout << "Expression Invalid" << std::endl;
        }
    }

    std::cout << "First non repeated character" << std::endl << "Type \"Stop\" to end" << std::endl;
    while(true){
        std::string input_string;
        std::getline(std::cin, input_string);
        if(input_string == "Stop")break;
        std::cout << firstNonRepeat(input_string) << std::endl;
    }

}
