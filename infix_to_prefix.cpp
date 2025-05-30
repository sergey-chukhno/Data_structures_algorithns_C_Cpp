// infix_to_prefix.cpp
// Converts infix expressions to prefix (Polish Notation) using stack-based algorithms in C++.

// Infix, Postfix, Prefix:
// Infix: <operand><operator><operand> Ex.: 2+3

// Prefix (Polish notation): <operator><operand><operand>. Ex.: +23
// Postfix (Reverse Polish notation): <operand><operand><operator>. Ex.: 2,3+

// Infix to Prefix Converter - C++ Implementation
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <map>
#include <cmath>
#include <algorithm>

class InfixToPrefixConverter
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

  // For prefix conversion, we need to handle precedence differently
  // when processing from right to left
  bool hasHigherPrecedence(char op1, char op2) const
  {
    int prec1 = getPrecedence(op1);
    int prec2 = getPrecedence(op2);

    // For right associative operators, use > instead of >=
    if (isRightAssociative(op2))
    {
      return prec1 > prec2;
    }
    // For left associative operators, use > (not >=) for prefix
    return prec1 > prec2;
  }

  // Reverse a string
  std::string reverseString(const std::string &str) const
  {
    std::string reversed = str;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
  }

  // Swap parentheses in a string
  std::string swapParentheses(const std::string &str) const
  {
    std::string result = "";
    for (char ch : str)
    {
      if (ch == '(')
      {
        result += ')';
      }
      else if (ch == ')')
      {
        result += '(';
      }
      else
      {
        result += ch;
      }
    }
    return result;
  }

public:
  // Method 1: Convert infix to prefix using reverse and modify approach
  std::string convertToPrefixMethod1(const std::string &infix)
  {
    // Step 1: Reverse the infix expression
    std::string reversedInfix = reverseString(infix);

    // Step 2: Swap parentheses
    reversedInfix = swapParentheses(reversedInfix);

    // Step 3: Convert to postfix using modified algorithm
    std::stack<char> operatorStack;
    std::string postfix = "";

    for (char ch : reversedInfix)
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
        // For prefix, we use > instead of >= for precedence comparison
        while (!operatorStack.empty() &&
               operatorStack.top() != '(' &&
               hasHigherPrecedence(operatorStack.top(), ch))
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

    // Step 4: Reverse the result to get prefix
    return reverseString(postfix);
  }

  // Method 2: Direct conversion to prefix (alternative approach)
  std::string convertToPrefixMethod2(const std::string &infix)
  {
    std::stack<char> operatorStack;
    std::stack<std::string> operandStack;

    for (char ch : infix)
    {
      // Skip whitespace
      if (std::isspace(ch))
      {
        continue;
      }

      // If operand, push to operand stack
      if (isOperand(ch))
      {
        operandStack.push(std::string(1, ch));
      }
      // If opening parenthesis, push to operator stack
      else if (ch == '(')
      {
        operatorStack.push(ch);
      }
      // If closing parenthesis, process until opening parenthesis
      else if (ch == ')')
      {
        while (!operatorStack.empty() && operatorStack.top() != '(')
        {
          processOperator(operatorStack, operandStack);
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
        while (!operatorStack.empty() &&
               operatorStack.top() != '(' &&
               shouldPopOperator(operatorStack.top(), ch))
        {
          processOperator(operatorStack, operandStack);
        }
        operatorStack.push(ch);
      }
    }

    // Process remaining operators
    while (!operatorStack.empty())
    {
      processOperator(operatorStack, operandStack);
    }

    return operandStack.empty() ? "" : operandStack.top();
  }

private:
  // Helper function for method 2
  void processOperator(std::stack<char> &operatorStack, std::stack<std::string> &operandStack)
  {
    if (operatorStack.empty() || operandStack.size() < 2)
    {
      return;
    }

    char op = operatorStack.top();
    operatorStack.pop();

    std::string operand2 = operandStack.top();
    operandStack.pop();
    std::string operand1 = operandStack.top();
    operandStack.pop();

    std::string result = op + operand1 + operand2;
    operandStack.push(result);
  }

  // Helper function to determine if we should pop operator for method 2
  bool shouldPopOperator(char stackOp, char currentOp) const
  {
    int stackPrec = getPrecedence(stackOp);
    int currentPrec = getPrecedence(currentOp);

    if (isRightAssociative(currentOp))
    {
      return stackPrec > currentPrec;
    }
    return stackPrec >= currentPrec;
  }

public:
  // Function to evaluate prefix expression
  double evaluatePrefix(const std::string &prefix)
  {
    std::stack<double> valueStack;

    // Process from right to left for prefix evaluation
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
      char ch = prefix[i];

      if (std::isdigit(ch))
      {
        valueStack.push(ch - '0');
      }
      else if (isOperator(ch))
      {
        if (valueStack.size() < 2)
        {
          throw std::runtime_error("Invalid prefix expression");
        }

        double operand1 = valueStack.top();
        valueStack.pop();
        double operand2 = valueStack.top();
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
      throw std::runtime_error("Invalid prefix expression");
    }

    return valueStack.top();
  }

  // Function to test conversion and evaluation
  void testConversion(const std::string &infix)
  {
    std::cout << "Infix:     " << infix << std::endl;

    try
    {
      std::string prefix1 = convertToPrefixMethod1(infix);
      std::string prefix2 = convertToPrefixMethod2(infix);

      std::cout << "Prefix M1: " << prefix1 << std::endl;
      std::cout << "Prefix M2: " << prefix2 << std::endl;

      // Check if both methods give same result
      if (prefix1 == prefix2)
      {
        std::cout << "✓ Both methods agree" << std::endl;
      }
      else
      {
        std::cout << "⚠ Methods differ" << std::endl;
      }

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

      if (canEvaluate && !prefix1.empty())
      {
        try
        {
          double result = evaluatePrefix(prefix1);
          std::cout << "Result:    " << result << std::endl;
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

  // Display algorithm explanation
  void displayAlgorithmExplanation()
  {
    std::cout << "Infix to Prefix Conversion Methods:" << std::endl;
    std::cout << std::endl;
    std::cout << "Method 1 (Reverse & Modify):" << std::endl;
    std::cout << "1. Reverse the infix expression" << std::endl;
    std::cout << "2. Swap '(' with ')' and vice versa" << std::endl;
    std::cout << "3. Apply modified postfix algorithm" << std::endl;
    std::cout << "4. Reverse the result" << std::endl;
    std::cout << std::endl;
    std::cout << "Method 2 (Direct Stack-based):" << std::endl;
    std::cout << "1. Use two stacks: operators and operands" << std::endl;
    std::cout << "2. Process left to right" << std::endl;
    std::cout << "3. Build prefix expressions directly" << std::endl;
    std::cout << std::endl;
  }
};

int main()
{
  std::cout << "=== Infix to Prefix Converter (C++) ===" << std::endl
            << std::endl;

  InfixToPrefixConverter converter;

  // Display algorithm explanation
  converter.displayAlgorithmExplanation();

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