// infix_to_postfix.cpp
// Converts infix expressions to postfix (Reverse Polish Notation) using a stack-based algorithm in C++.
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <map>
#include <cmath>

class InfixToPostfixConverter
{
private:
  // Define operator precedence
  std::map<char, int> precedence = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};

  // Check if character is an operator
  bool isOperator(char ch) const
  {
    return precedence.find(ch) != precedence.end();
  }

  // Check if character is an operand (alphanumeric)
  bool isOperand(char ch) const
  {
    return std::isalnum(ch);
  }

  // Get precedence of an operator
  int getPrecedence(char op) const
  {
    auto it = precedence.find(op);
    return (it != precedence.end()) ? it->second : 0;
  }

  // Check if operator is right associative (only ^ in this case)
  bool isRightAssociative(char op) const
  {
    return op == '^';
  }

  // Check if op1 has higher or equal precedence than op2
  bool hasHigherOrEqualPrecedence(char op1, char op2) const
  {
    int prec1 = getPrecedence(op1);
    int prec2 = getPrecedence(op2);

    if (isRightAssociative(op2))
    {
      return prec1 > prec2;
    }
    return prec1 >= prec2;
  }

public:
  // Main function to convert infix to postfix
  std::string convertToPostfix(const std::string &infix)
  {
    std::stack<char> operatorStack;
    std::string postfix = "";

    for (char ch : infix)
    {
      // Skip whitespace
      if (std::isspace(ch))
      {
        continue;
      }

      // If operand, add to output
      if (isOperand(ch))
      {
        postfix += ch;
      }
      // If opening parenthesis, push to stack
      else if (ch == '(')
      {
        operatorStack.push(ch);
      }
      // If closing parenthesis, pop until opening parenthesis
      else if (ch == ')')
      {
        while (!operatorStack.empty() && operatorStack.top() != '(')
        {
          postfix += operatorStack.top();
          operatorStack.pop();
        }
        // Pop the opening parenthesis
        if (!operatorStack.empty())
        {
          operatorStack.pop();
        }
      }
      // If operator
      else if (isOperator(ch))
      {
        // Pop operators with higher or equal precedence
        while (!operatorStack.empty() &&
               operatorStack.top() != '(' &&
               hasHigherOrEqualPrecedence(operatorStack.top(), ch))
        {
          postfix += operatorStack.top();
          operatorStack.pop();
        }
        operatorStack.push(ch);
      }
    }

    // Pop remaining operators from stack
    while (!operatorStack.empty())
    {
      postfix += operatorStack.top();
      operatorStack.pop();
    }

    return postfix;
  }

  // Function to evaluate postfix expression
  double evaluatePostfix(const std::string &postfix)
  {
    std::stack<double> valueStack;

    for (char ch : postfix)
    {
      if (std::isdigit(ch))
      {
        // Convert char digit to double
        valueStack.push(ch - '0');
      }
      else if (isOperator(ch))
      {
        if (valueStack.size() < 2)
        {
          throw std::runtime_error("Invalid postfix expression");
        }

        double operand2 = valueStack.top();
        valueStack.pop();
        double operand1 = valueStack.top();
        valueStack.pop();
        double result;

        switch (ch)
        {
        case '+':
          result = operand1 + operand2;
          break;
        case '-':
          result = operand1 - operand2;
          break;
        case '*':
          result = operand1 * operand2;
          break;
        case '/':
          if (operand2 == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          result = operand1 / operand2;
          break;
        case '%':
          if (operand2 == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          result = static_cast<int>(operand1) % static_cast<int>(operand2);
          break;
        case '^':
          result = std::pow(operand1, operand2);
          break;
        default:
          throw std::runtime_error("Unknown operator");
        }

        valueStack.push(result);
      }
    }

    if (valueStack.size() != 1)
    {
      throw std::runtime_error("Invalid postfix expression");
    }

    return valueStack.top();
  }

  // Function to test conversion and evaluation
  void testConversion(const std::string &infix)
  {
    std::cout << "Infix:    " << infix << std::endl;

    try
    {
      std::string postfix = convertToPostfix(infix);
      std::cout << "Postfix:  " << postfix << std::endl;

      // Try to evaluate if expression contains only digits and operators
      bool canEvaluate = true;
      for (char ch : infix)
      {
        if (std::isalpha(ch))
        {
          canEvaluate = false;
          break;
        }
      }

      if (canEvaluate && !postfix.empty())
      {
        try
        {
          double result = evaluatePostfix(postfix);
          std::cout << "Result:   " << result << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Evaluation error: " << e.what() << std::endl;
        }
      }
    }
    catch (const std::exception &e)
    {
      std::cout << "Conversion error: " << e.what() << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
  }

  // Display operator precedence table
  void displayPrecedenceTable()
  {
    std::cout << "Operator Precedence Table:" << std::endl;
    std::cout << "Operator | Precedence | Associativity" << std::endl;
    std::cout << "---------|------------|-------------" << std::endl;
    std::cout << "   ^     |     3      | Right" << std::endl;
    std::cout << " *, /, % |     2      | Left" << std::endl;
    std::cout << "  +, -   |     1      | Left" << std::endl;
    std::cout << "  ( )    |   N/A      | N/A" << std::endl;
    std::cout << std::endl;
  }
};

int main()
{
  std::cout << "=== Infix to Postfix Converter (C++) ===" << std::endl
            << std::endl;

  InfixToPostfixConverter converter;

  // Display precedence table
  converter.displayPrecedenceTable();

  // Test cases
  std::cout << "Test Cases:" << std::endl;
  converter.testConversion("a+b*c");
  converter.testConversion("(a+b)*c");
  converter.testConversion("a+b*c-d");
  converter.testConversion("a^b^c");
  converter.testConversion("(a+b)*(c-d)");
  converter.testConversion("a+b*(c^d-e)^(f+g*h)-i");
  converter.testConversion("2+3*4");
  converter.testConversion("(2+3)*4");
  converter.testConversion("2^3^2");
  converter.testConversion("(1+2)*(3+4)");
  converter.testConversion("3+4*2/(1-5)^2^3");

  // Interactive mode
  std::string input;
  std::cout << std::endl
            << "Enter an infix expression to convert (or 'quit' to exit):" << std::endl;
  std::cout << "Note: Use single characters for variables (a-z, A-Z) and digits (0-9)" << std::endl;
  std::cout << "Supported operators: +, -, *, /, %, ^, (, )" << std::endl
            << std::endl;

  while (true)
  {
    std::cout << "> ";
    std::getline(std::cin, input);

    if (input == "quit")
    {
      break;
    }

    if (input.empty())
    {
      continue;
    }

    converter.testConversion(input);
  }

  std::cout << "Goodbye!" << std::endl;
  return 0;
}