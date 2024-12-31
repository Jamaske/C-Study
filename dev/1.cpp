#include <iostream>
#include <immintrin.h>
#include <stack>

/*
types of operands
1) const - t,f
imidiate result no opStak or value in progress needed
2) inversion, evevalention - !(...), xxxx
not imidiate has to wait untill iner expression is evaluated
need opStak entry to regurn to after iner exp evaluation
has only one argument so as soon as it is ready can get the answer.
has no intermidiate result. so no data storage required
3) comosits - &(...), |(...)
it is not immidiate too. opStack entry needed
has multiple arguments need to waite untill all.
So have to store intermidiate result.
But we can implement short-circuit evaluation.
Just stop bother with calculation if it already predetermined
so until short-circuit mode is on default values will be
& - true
| - false
thus no need to store anything.
*/

enum Op :const char {
    Exp,
    Not = '!',
    And = '&',
    Or = '|',
};



class Solution {
public:
    std::stack<Op> opStack;
    const char* cur;
    //fast forward to end of scope of the operation
    void fast_forward() {
        int br = 1;

        ++cur;
        while (true) {
            switch (*cur) {
            case '(':
                ++br;
            case ',':
                cur += 2;
                break;
            case ')':
                if (!--br) return;
                ++cur;
                break;
            }
        }

    }

    bool parseBoolExpr(std::string expression) {
        cur = expression.c_str();

        // artificialty envelop the expresion with AND
        // to make use of existion logic and avoid edge case cheack
        opStack.push(Op::Exp);

        //all oparation regurn the result throught this variable
        bool reg;

    call:
        switch (opStack.top()) {
        case Op::Exp:
            switch (*cur) {//parse argument
                //call an operation
            case '!': case '&':case '|':
                opStack.push(static_cast<Op>(*cur));
                cur += 2;
                goto call;
                //evaluate constants
            case 't': reg = true; break;
            case 'f': reg = false; break;
                //at function return pass the value furhter
            case ')': break;
            }
            ++cur;
            goto ret;


        case Op::Not:
            switch (*cur) {
            case '!': case '&':case '|':
                opStack.push(static_cast<Op>(*cur));
                cur += 2;
                goto call;
            case 't': reg = false; break;
            case 'f': reg = true; break;
            case ')': reg = !reg; break;
            }
            ++cur;
            goto ret;

        case Op::And:
            do {//argument interation
                switch (*cur) {//parse argument
                case '!': case '&':case '|'://initiate call
                    opStack.push(static_cast<Op>(*cur));
                    cur += 2;
                    goto call;
                case 't':
                    continue;
                case ')':
                    if (reg) continue;
                case 'f':
                    fast_forward();
                    reg = false;
                    goto ret;
                }
            } while (*++cur != ')');//more arguments?
            reg = true;
            goto ret;

        case Op::Or:
            do {
                switch (*cur) {
                case '!': case '&':case '|':
                    opStack.push(static_cast<Op>(*cur));
                    cur += 2;
                    goto call;
                case 'f':
                    continue;
                case ')':
                    if (!reg) continue;
                case 't':
                    fast_forward();
                    reg = true;
                    goto ret;
                }
            } while (*++cur != ')');
            reg = false;
            goto ret;

        }
    ret:
        opStack.pop();
        if (!opStack.empty()) goto call;
        return reg;
    }
};

int main() {
    Solution solution;
    std::string expr;
    std::cin >> expr;
    std::cout << solution.parseBoolExpr(expr) << std::endl;




    return 0;
}