#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include "stack.h"
#include "operator.h"
using namespace std;
// 最大表达式长度



int precedence(char op)
{

    switch (op) {
    case Plus :case Minus:
        return 1;
    case Multiply:case Divide:case Modulo:
        return 2;
    case Power:
        return 3;
    case Negate: case Absolute:
        return 4;
    default:
        return 0;
    }
}
// 获取运算符需要的操作数
int typeOp(char op) {
    switch (op)
    {
    case Negate: case Absolute:
        return 1;
    default:
        return 2;
    }
}

// 返回值代表是否计算成功
bool calculate(Stack& values,Stack& ops)
{
    char op = ops.top();
    ops.pop();
    int b = values.top();
    values.pop();
    int a = 0;
    if (typeOp(op) == 2)
    {
        if (values.isEmpty())return false;
        a = values.top();
        values.pop();
    }
    int value = 0;
    switch (op)
    {
    case Plus:
        value =  a + b;
        break;
    case Minus:
        value = a - b;
        break;
    case Multiply:
        value = a * b;
        break;
    case Divide:
        if (b == 0)return false;
        value = a / b ;
        break;
    case Modulo:
        if (b == 0)return false;
        value = a % b;
        break;
    case Power:
        if (a == 0 && b == 0)return false;
        value = (int)pow(a, b);
        break;
    case Negate:
        value = 0-b;
        break;
    case Absolute:
        value = abs(b);
        break;
    default:
        return false;
    }
    values.push(value);
    return true;
}

// 对表达式进行处理的函数, 进行运算符符号转换
string deal(const string& str) {
    int len = str.length();
    string expr;
    for (int i = 0; i < len; i++) {
        char ch = str[i];
        if (ch == ' ')continue;
        if (ch == 'a') {
            i += 2;
        }
        else if (ch == '-') {  // 判断是单目-还是双目-
            if (!expr.size() || expr.back() == '(')
                ch = 'm';
        }
        expr.push_back(ch);
    }
    return expr;
}

bool evaluateExpression(const string& str, int& ans)
{
    Stack values;
    Stack ops;
    string expr = deal(str);
    int len = expr.length();
    for (int i = 0; i < len; i++) {
        char ch = expr[i];
        if (isdigit(ch)) {  // 处理操作数
            int value = 0;
            while (i < len && isdigit(ch = expr[i])) {
       
                value = value * 10 + ch - '0';
                i++;
            }
            i--;
            values.push(value);
        }
        else if (ch == 'a') {  // 处理abs()运算符
            ops.push('a');
        }
        else if (ch == '(') {  // 处理(
            ops.push('(');
        }
        else if (ch == ')') {
            while (!ops.isEmpty() && ops.top() != '(') {
                if (!calculate(values, ops))return false;
            }
            // 如果这个时候运算符空了说明括号不完整
            if (ops.isEmpty())return false;
            ops.pop(); // 去除'('
        }
        else {
            while (!ops.isEmpty() && precedence(ops.top()) >= precedence(ch)) {
                if (!calculate(values, ops))return false;
            }
            ops.push(ch);
        }
    }
    while (!ops.isEmpty()) {
        if (!calculate(values, ops))return false;
    }
    if (values.size() > 1 || values.isEmpty())return false;
    ans = values.pop();
    return true;
}

int main()
{
    string expression;
    do {
        cout << "输入运算符表达式(输入quit退出):" << endl;
        getline(cin, expression);
        //getchar();
        if (expression == "quit")break;
        int ans;
        bool flag = evaluateExpression(expression, ans);
        if (flag) {
            cout << "Result:" << ans << endl;
        }
        else {
            cout << "NULL" << endl;
        }
    } while (true);
    
 
    return 0;
}
