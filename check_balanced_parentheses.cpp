// check_balanced_parentheses.cpp
// Checks for balanced parentheses in an expression using a stack in C++. Demonstrates stack-based matching of brackets.
#include <iostream>
#include <string>
#include <vector>

class Stack
{
private:
  std::vector<char> data;

public:
  // Constructor
  Stack() {}

  // Destructor
  ~Stack() {}

  // Push element to stack
  void push(char item)
  {
    data.push_back(item);
  }

  // Pop element from stack
  char pop()
  {
    if (isEmpty())
    {
      std::cout << "Stack underflow!" << std::endl;
      return '\0';
    }
    char top = data.back();
    data.pop_back();
    return top;
  }

  // Peek top element of stack
  char peek() const
  {
    if (isEmpty())
    {
      return '\0';
    }
    return data.back();
  }

  // Check if stack is empty
  bool isEmpty() const
  {
    return data.empty();
  }

  // Get size of stack
  size_t size() const
  {
    return data.size();
  }
};

class BalancedParenthesesChecker
{
private:
  // Check if character is an opening bracket
  bool isOpeningBracket(char ch) const
  {
    return (ch == '(' || ch == '[' || ch == '{');
  }

  // Check if character is a closing bracket
  bool isClosingBracket(char ch) const
  {
    return (ch == ')' || ch == ']' || ch == '}');
  }

  // Check if opening and closing brackets match
  bool isMatchingPair(char opening, char closing) const
  {
    return ((opening == '(' && closing == ')') ||
            (opening == '[' && closing == ']') ||
            (opening == '{' && closing == '}'));
  }

public:
  // Main function to check if expression is balanced
  bool isBalanced(const std::string &expression)
  {
    Stack stack;

    for (char current : expression)
    {
      // If current character is an opening bracket, push to stack
      if (isOpeningBracket(current))
      {
        stack.push(current);
      }
      // If current character is a closing bracket
      else if (isClosingBracket(current))
      {
        // If stack is empty, no matching opening bracket
        if (stack.isEmpty())
        {
          return false;
        }

        // Pop the top element and check if it matches
        char top = stack.pop();
        if (!isMatchingPair(top, current))
        {
          return false;
        }
      }
      // Ignore other characters (letters, numbers, operators, etc.)
    }

    // Expression is balanced if stack is empty
    return stack.isEmpty();
  }

  // Function to test the balanced parentheses checker
  void testExpression(const std::string &expression)
  {
    std::cout << "Expression: " << expression << std::endl;
    if (isBalanced(expression))
    {
      std::cout << "Result: BALANCED" << std::endl;
    }
    else
    {
      std::cout << "Result: NOT BALANCED" << std::endl;
    }
    std::cout << "------------------------" << std::endl;
  }
};

int main()
{
  std::cout << "=== Balanced Parentheses Checker (C++) ===" << std::endl
            << std::endl;

  BalancedParenthesesChecker checker;

  // Test cases
  checker.testExpression("()");
  checker.testExpression("()[]{}");
  checker.testExpression("([{}])");
  checker.testExpression("((()))");
  checker.testExpression("(]");
  checker.testExpression("([)]");
  checker.testExpression("((()");
  checker.testExpression("())");
  checker.testExpression("{[()]}");
  checker.testExpression("a + (b * c) - [d / e]");
  checker.testExpression("if (x > 0) { print(arr[i]); }");
  checker.testExpression("((a + b) * (c - d))");
  checker.testExpression("[(a + b) * (c - d)]");
  checker.testExpression("[(a + b) * (c - d)");

  // Interactive mode
  std::string input;
  std::cout << std::endl
            << "Enter an expression to check (or 'quit' to exit):" << std::endl;

  while (true)
  {
    std::cout << "> ";
    std::getline(std::cin, input);

    if (input == "quit")
    {
      break;
    }

    checker.testExpression(input);
  }

  std::cout << "Goodbye!" << std::endl;
  return 0;
}
