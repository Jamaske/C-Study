#include "expresion_solver.h"
#include <iostream>
#include "../source/NodeDataStracts/Stack.h"



void solve::preprocess(){
    /* Удаляет пробелы.
     * Распознаёт и заменяет следующие наборы символов
     * TRUE->1
     * FALSE->0
     * AND->&
     * OR->|
     * NOT->!
    */
    std::string temp = std::string("");
    char prev = ' ';
    int raw_len = solve::raw_expression.length();
    char ch;
    for(int i = 0; i < raw_len; i++) {
        ch = solve::raw_expression[i];

        if (('A' <= ch) && (ch <= 'Z')) {
            if (('A' <= prev) && (prev <= 'Z')) {
                switch (prev) {
                    case 'T':
                        temp.append("1");
                        i += 2;
                        break;
                    case 'F':
                        temp.append("0");
                        i += 3;
                        break;
                    case 'A':
                        temp.append("&");
                        i++;
                        break;
                    case 'O':
                        temp.append("|");
                        break;
                    case 'N':
                        temp.append("!");
                        i++;
                        break;
                    default:
                        std::cout << "can't recognize some word" << std::endl;
                }
                prev = ' ';
                continue;
            } else prev = ch;
        } else {
            if (('A' <= prev) && (prev <= 'Z')) temp.push_back(prev);
            if (ch != ' ') temp.push_back(ch);
        }
        prev = ch;
    }
    solve::raw_expression = temp;
}


int pror(char c){
    switch (c)
    {
        case '(':
        case ')':
            return 0;
        case '|':
            return 1;
        case '&':
            return 2;
        case '!':
            return 3;
    }
}


void solve::convert_to_polish(){
    Stack<char> oper_stack;

    for (char ch: solve::raw_expression) {

        if (isdigit(ch)) {
            solve::pol_notation += ch;
            continue;
        }

        if (!oper_stack.not_empty() || ch == '(') {
            oper_stack.push(ch);
            continue;
        }

        if (ch == ')') {
            while (oper_stack.not_empty()) {
                ch = oper_stack.pop();
                if(ch == '(') break;
                solve::pol_notation += ch;
            }
            continue;
        }

        while (oper_stack.not_empty() && (pror(oper_stack.peek()) >= pror(ch))) {
            solve::pol_notation += oper_stack.pop();
        }
        oper_stack.push(ch);
    }

    while(oper_stack.not_empty()) {
        solve::pol_notation += oper_stack.pop();
    }
}


void execute_operation(Stack<int> &operands, char operation){
    bool sec_operand;
    switch (operation) {
        case '|':
            sec_operand = operands.pop();
            operands.push(operands.pop() || sec_operand);
            break;
        case '&':
            sec_operand = operands.pop();
            operands.push(operands.pop() && sec_operand);
            break;
        case '!':
            operands.push(!operands.pop());
            break;
    }
}


bool solve::getvar(char name){
    return solve::vars[name-'A'];
}


bool solve::calculate_polish(){
    Stack<int> values;
    int num_start = -1;

    char ch;
    unsigned int pol_len = solve::pol_notation.length();
    for(int i = 0; i < pol_len; i++){
        ch = solve::pol_notation[i];


        if (std::isdigit(ch)) {//читаем символы числа
            if( num_start < 0) num_start = i;
            continue;
        }
        if(num_start >= 0){//сохраняем число
            values.push(std::stoi(solve::pol_notation.substr(num_start, i-num_start)));
            num_start = -1;
        }

        if(('A' <= ch) && (ch <= 'Z')){
            values.push(getvar(ch));
            continue;
        }
        execute_operation(values, ch);
    }
    return values.pop();
}


bool solve::calculate_raw(){
    Stack<char> oper_stack;
    Stack<int> values;

    int num_start = -1;
    //number reading.
    // -1  --> no number noticed
    // >=0 --> equal to number first idx

    char ch;
    unsigned int raw_len = solve::raw_expression.length();
    for (int i = 0; i < raw_len; i++) {
        ch = solve::raw_expression[i];

        if (std::isdigit(ch)) {//читаем символы числа
            if( num_start < 0) num_start = i;
            continue;
        }
        if(num_start >= 0){//сохраняем число
            values.push(std::stoi(solve::raw_expression.substr(num_start, i-num_start)));
            num_start = -1;
        }

        if(std::isalpha(ch)){
            values.push(getvar(ch));
        }

        if (!oper_stack.not_empty() || ch == '(') {
            oper_stack.push(ch);
            continue;
        }

        if (ch == ')') {
            while (oper_stack.not_empty()) {
                ch = oper_stack.pop();
                if(ch == '(') break;
                execute_operation(values, ch);
            }
            continue;
        }

        while (oper_stack.not_empty() && (pror(oper_stack.peek()) >= pror(ch))) {
            execute_operation(values, oper_stack.pop());

        }
        oper_stack.push(ch);
    }

    while(oper_stack.not_empty()) {
        execute_operation(values, oper_stack.pop());
    }
    return values.pop();
}


