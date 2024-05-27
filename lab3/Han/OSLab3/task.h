#ifndef OSLAB3_TASK_H

#include <iostream>
#include <functional>
#include <string>
#include <sstream>

#define OSLAB3_TASK_H


class Task {
    typedef std::function<int(int, int, char)> func_t;
public:
    Task() {}

    Task(int x, int y, char op, func_t func)
            : _x(x), _y(y), _op(op), _callBack(func) {}

    std::string operator()()//消费者调用
    {
        int result = _callBack(_x, _y, _op);
        std::ostringstream oss;
        oss << _x << " " << _op << " " << _y << "= "<<result;
        return oss.str();
    }

    std::string toString()//生产者调用
    {
        std::ostringstream oss;
        oss << _x << " " << _op << " " << _y << "=?";
        return oss.str();
    }

private:
    int _x;
    int _y;
    char _op;//加减乘除
    func_t _callBack;//回调函数
};

int myMath(int x, int y, char op) {
    int result = 0;
    switch (op) {
        case '+':
            result = x + y;
            break;
        case '-':
            result = x - y;
            break;
        case '*':
            result = x * y;
            break;
        case '/': {
            if (y == 0) {
                std::cerr << "div zero error" << std::endl;
                result = -1;
            } else
                result = x / y;
        }
            break;
        default:
            break;
    }
    return result;
}

#endif //OSLAB3_TASK_H
