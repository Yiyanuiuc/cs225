/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

#include <iostream>
using namespace std;

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    if (s.size()==0) return T();
    else {
        T removed = s.top();
        s.pop();
        T accumulated = removed + sum(s);
        s.push(removed);
        return accumulated;
    }
    // return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    // Your code here
    int i=1;
    while (!q.empty()) {
        if (i%2==0) {
            // Use stack to help reverse the elements
            for (int j=0; j<i; j++) {
                s.push(q.front());
                q.pop();
                if (q.empty()) break;
            }
            while (!s.empty()) {
                q2.push(s.top());
                s.pop();
            }
        }
        else {
            // Just move the elements directly without changing the order
            for (int j=0; j<i; j++) {
                q2.push(q.front());
                q.pop();
                if (q.empty()) break;
            }
        }
        i++;
        // cout << "yo" << endl;
    }
    // Move elements from q2 back to q
    while (!q2.empty()) {
        q.push(q2.front());
        q2.pop();
        // cout << "ha" << endl;
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    // bool retval = true; // optional
    // if (s.size()<=0) return true;
    // if (s.size()==1) return s.top()==q.front();
    // else {
    //     T tempS = s.top();
    //     s.pop();
    //     for (int i=0; i<(int)(q.size()-1); i++) {
    //         q.push(q.front());
    //         q.pop();
    //     }
    //     T tempQ = q.front();
    //     q.pop();
    //     retval = verifySame(s, q);
    //     s.push(tempS);
    //     q.push(tempQ);
    // }
    // return retval;
    bool retval = true; // optional
    // Base case
    if (s.size()<=0) return true;
    else if (s.size()==1) return s.top()==q.front();

    else {
        T tempS = s.top();
        s.pop();
        retval = verifySame(s,q);
        // Make stack and queue unchanged
        q.push(q.front());
        q.pop();
        s.push(tempS);

        if (retval) retval = (s.top()==q.front());
        if (s.size()==q.size()) {
            q.push(q.front());
            q.pop();
        }
        return retval;
    }
}

}