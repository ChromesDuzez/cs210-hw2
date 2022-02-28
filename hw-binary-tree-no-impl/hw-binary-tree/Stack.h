#pragma once
#include "List.h"

template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& top() const
    {
        return *theList.end();
    }
    void push(const Object& x)
    {
        theList.push_back(x);
    }
    Object& pop()
    {
        const Object& back = theList.back();
        Object popped = back;
        theList.pop_back();
        return popped;
    }
private:
    List<Object> theList;
};