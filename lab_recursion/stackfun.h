/**
 * @file stackfun.h
 * Contains the StackFun namespace definition.
 */

#ifndef STACKFUN_H
#define STACKFUN_H

#include <stack>
#include <queue>

using std::stack;
using std::queue;

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace StackFun
{
    template <typename T>
    T sum(stack<T> & s);
    
    template <typename T>
    void scramble(queue<T> & q);

    template <typename T>
    bool verifySame(stack<T> & s, queue<T> & q);
};

#include "stackfun.cpp"
#endif
