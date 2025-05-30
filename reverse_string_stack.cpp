// reverse_string_stack.cpp
// Reverses a string using a stack data structure in C++. Demonstrates LIFO property for string reversal.
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string str;
    cout << "Enter a string: ";
    cin >> str;

    // Create a stack to hold the characters
    stack<char> s;

    // Push all characters of the string onto the stack
    for (char c : str)
    {
        s.push(c);
    }

    // Pop all characters from the stack and append to the result
    string reversedStr;
    while (!s.empty())
    {
        reversedStr += s.top();
        s.pop();
    }

    cout << "Reversed string: " << reversedStr << endl;

    return 0;
}