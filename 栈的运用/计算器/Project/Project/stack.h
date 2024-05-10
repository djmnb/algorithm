#pragma once
#define MAXSIZE 300
class Stack
{
private:
    int data[MAXSIZE];
    int pos = -1;

public:
    void push(int value)
    {
        data[++pos] = value;
    }

    int pop()
    {
        assert(!isEmpty());
        int value = data[pos--];
        return value;
    }

    int top()
    {
        assert(!isEmpty());
        return data[pos];
    }

    bool isEmpty()
    {
        return pos == -1;
    }

    int size() {
        return pos + 1;
    }
};