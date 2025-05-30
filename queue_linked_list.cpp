// queue_linked_list.cpp
// Implements a queue using a singly linked list. Supports enqueue, dequeue, and various utility operations.
#include <iostream>
#include <stdexcept>
#include <string>

// Node structure for the linked list
struct Node
{
  int data;
  Node *next;

  // Constructor
  Node(int value) : data(value), next(nullptr) {}
};

class LinkedListQueue
{
private:
  Node *frontPtr;  // Pointer to the front node
  Node *rearPtr;   // Pointer to the rear node
  int currentSize; // Current number of elements in queue

public:
  // Constructor
  LinkedListQueue() : frontPtr(nullptr), rearPtr(nullptr), currentSize(0) {}

  // Destructor
  ~LinkedListQueue()
  {
    clear();
  }

  // Copy constructor
  LinkedListQueue(const LinkedListQueue &other) : frontPtr(nullptr), rearPtr(nullptr), currentSize(0)
  {
    Node *current = other.frontPtr;
    while (current != nullptr)
    {
      enqueue(current->data);
      current = current->next;
    }
  }

  // Assignment operator
  LinkedListQueue &operator=(const LinkedListQueue &other)
  {
    if (this != &other)
    {
      clear();
      Node *current = other.frontPtr;
      while (current != nullptr)
      {
        enqueue(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  // Enqueue operation - add element to rear
  void enqueue(int item)
  {
    Node *newNode = new Node(item);

    // If queue is empty, both front and rear point to new node
    if (isEmpty())
    {
      frontPtr = rearPtr = newNode;
    }
    else
    {
      // Add new node at rear and update rear pointer
      rearPtr->next = newNode;
      rearPtr = newNode;
    }
    currentSize++;
  }

  // Dequeue operation - remove element from front
  int dequeue()
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - cannot dequeue");
    }

    Node *nodeToDelete = frontPtr;
    int frontData = frontPtr->data;

    // Move front pointer to next node
    frontPtr = frontPtr->next;

    // If queue becomes empty, update rear pointer
    if (frontPtr == nullptr)
    {
      rearPtr = nullptr;
    }

    delete nodeToDelete;
    currentSize--;
    return frontData;
  }

  // Get front element without removing it
  int front() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no front element");
    }
    return frontPtr->data;
  }

  // Get rear element without removing it
  int rear() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no rear element");
    }
    return rearPtr->data;
  }

  // Check if queue is empty
  bool isEmpty() const
  {
    return frontPtr == nullptr;
  }

  // Get current size of queue
  int size() const
  {
    return currentSize;
  }

  // Clear all elements from queue
  void clear()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }

  // Display queue contents
  void display() const
  {
    if (isEmpty())
    {
      std::cout << "Queue is empty" << std::endl;
      return;
    }

    std::cout << "Queue contents (front to rear): ";
    Node *current = frontPtr;
    while (current != nullptr)
    {
      std::cout << current->data;
      if (current->next != nullptr)
      {
        std::cout << " <- ";
      }
      current = current->next;
    }
    std::cout << std::endl;
  }

  // Display detailed queue state
  void displayDetailed() const
  {
    std::cout << "=== Queue State ===" << std::endl;
    std::cout << "Size: " << currentSize << std::endl;
    std::cout << "Is Empty: " << (isEmpty() ? "Yes" : "No") << std::endl;

    if (!isEmpty())
    {
      std::cout << "Front Element: " << front() << std::endl;
      std::cout << "Rear Element: " << rear() << std::endl;
      std::cout << "Front Address: " << frontPtr << std::endl;
      std::cout << "Rear Address: " << rearPtr << std::endl;
    }

    // Display linked list structure
    std::cout << "Linked List Structure: ";
    if (isEmpty())
    {
      std::cout << "NULL" << std::endl;
    }
    else
    {
      Node *current = frontPtr;
      while (current != nullptr)
      {
        std::cout << "[" << current->data << "]";
        if (current == frontPtr)
          std::cout << "(F)";
        if (current == rearPtr)
          std::cout << "(R)";
        if (current->next != nullptr)
        {
          std::cout << " -> ";
        }
        else
        {
          std::cout << " -> NULL";
        }
        current = current->next;
      }
      std::cout << std::endl;
    }
    std::cout << "===================" << std::endl;
  }

  // Additional utility functions

  // Check if queue contains a specific value
  bool contains(int value) const
  {
    Node *current = frontPtr;
    while (current != nullptr)
    {
      if (current->data == value)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // Get element at specific position (0 = front)
  int getAt(int position) const
  {
    if (position < 0 || position >= currentSize)
    {
      throw std::out_of_range("Position out of range");
    }

    Node *current = frontPtr;
    for (int i = 0; i < position; i++)
    {
      current = current->next;
    }
    return current->data;
  }

  // Print all elements with their positions
  void printWithPositions() const
  {
    if (isEmpty())
    {
      std::cout << "Queue is empty" << std::endl;
      return;
    }

    std::cout << "Queue elements with positions:" << std::endl;
    Node *current = frontPtr;
    int position = 0;
    while (current != nullptr)
    {
      std::cout << "Position " << position << ": " << current->data
                << " (Address: " << current << ")" << std::endl;
      current = current->next;
      position++;
    }
  }

  // Reverse the queue (for demonstration purposes)
  void reverse()
  {
    if (isEmpty() || currentSize == 1)
    {
      return;
    }

    Node *prev = nullptr;
    Node *current = frontPtr;
    Node *next = nullptr;

    // Swap front and rear pointers
    Node *temp = frontPtr;
    frontPtr = rearPtr;
    rearPtr = temp;

    // Reverse the links
    while (current != nullptr)
    {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
  }

  // Get the nth element from the end (1-indexed)
  int getNthFromEnd(int n) const
  {
    if (n <= 0 || n > currentSize)
    {
      throw std::out_of_range("Invalid position from end");
    }

    // Calculate position from front
    int positionFromFront = currentSize - n;
    return getAt(positionFromFront);
  }

  // Count occurrences of a value
  int countOccurrences(int value) const
  {
    int count = 0;
    Node *current = frontPtr;
    while (current != nullptr)
    {
      if (current->data == value)
      {
        count++;
      }
      current = current->next;
    }
    return count;
  }

  // Find maximum element
  int findMax() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no maximum element");
    }

    int maxVal = frontPtr->data;
    Node *current = frontPtr->next;
    while (current != nullptr)
    {
      if (current->data > maxVal)
      {
        maxVal = current->data;
      }
      current = current->next;
    }
    return maxVal;
  }

  // Find minimum element
  int findMin() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no minimum element");
    }

    int minVal = frontPtr->data;
    Node *current = frontPtr->next;
    while (current != nullptr)
    {
      if (current->data < minVal)
      {
        minVal = current->data;
      }
      current = current->next;
    }
    return minVal;
  }
};

// Demo class to test the queue
class LinkedQueueDemo
{
public:
  static void demonstrateBasicOperations()
  {
    std::cout << "=== Basic Linked List Queue Operations Demo ===" << std::endl;

    LinkedListQueue queue;

    std::cout << "Created empty queue" << std::endl;
    queue.displayDetailed();

    // Enqueue operations
    std::cout << "\nEnqueuing elements: 10, 20, 30, 40" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.display();
    queue.displayDetailed();

    // Front and rear operations
    std::cout << "\nFront element: " << queue.front() << std::endl;
    std::cout << "Rear element: " << queue.rear() << std::endl;

    // Test utility functions
    std::cout << "Contains 20? " << (queue.contains(20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 50? " << (queue.contains(50) ? "Yes" : "No") << std::endl;
    std::cout << "Element at position 2: " << queue.getAt(2) << std::endl;

    // Dequeue operations
    std::cout << "\nDequeuing elements:" << std::endl;
    while (!queue.isEmpty())
    {
      std::cout << "Dequeued: " << queue.dequeue() << std::endl;
      queue.display();
    }

    std::cout << std::endl;
  }

  static void demonstrateDynamicGrowth()
  {
    std::cout << "=== Dynamic Growth Demo ===" << std::endl;

    LinkedListQueue queue;

    std::cout << "Adding many elements to show dynamic growth:" << std::endl;
    for (int i = 1; i <= 10; i++)
    {
      queue.enqueue(i * 5);
      std::cout << "Added " << (i * 5) << ", Size: " << queue.size() << std::endl;
    }

    queue.display();
    queue.printWithPositions();

    std::cout << "\nRemoving half the elements:" << std::endl;
    for (int i = 0; i < 5; i++)
    {
      int removed = queue.dequeue();
      std::cout << "Removed " << removed << ", Size: " << queue.size() << std::endl;
    }

    queue.display();
    std::cout << std::endl;
  }

  static void demonstrateErrorHandling()
  {
    std::cout << "=== Error Handling Demo ===" << std::endl;

    LinkedListQueue queue;

    // Test empty queue operations
    std::cout << "Testing operations on empty queue:" << std::endl;
    try
    {
      queue.dequeue();
    }
    catch (const std::exception &e)
    {
      std::cout << "Dequeue error: " << e.what() << std::endl;
    }

    try
    {
      queue.front();
    }
    catch (const std::exception &e)
    {
      std::cout << "Front error: " << e.what() << std::endl;
    }

    try
    {
      queue.getAt(0);
    }
    catch (const std::exception &e)
    {
      std::cout << "GetAt error: " << e.what() << std::endl;
    }

    try
    {
      queue.findMax();
    }
    catch (const std::exception &e)
    {
      std::cout << "FindMax error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
  }

  static void demonstrateAdvancedFeatures()
  {
    std::cout << "=== Advanced Features Demo ===" << std::endl;

    LinkedListQueue queue;

    // Add some elements with duplicates
    int elements[] = {5, 10, 15, 10, 25, 5, 30};
    int numElements = sizeof(elements) / sizeof(elements[0]);

    std::cout << "Adding elements: ";
    for (int i = 0; i < numElements; i++)
    {
      queue.enqueue(elements[i]);
      std::cout << elements[i] << " ";
    }
    std::cout << std::endl;

    queue.display();

    // Test advanced functions
    std::cout << "\nAdvanced function tests:" << std::endl;
    std::cout << "Maximum element: " << queue.findMax() << std::endl;
    std::cout << "Minimum element: " << queue.findMin() << std::endl;
    std::cout << "Occurrences of 10: " << queue.countOccurrences(10) << std::endl;
    std::cout << "Occurrences of 5: " << queue.countOccurrences(5) << std::endl;
    std::cout << "2nd element from end: " << queue.getNthFromEnd(2) << std::endl;

    // Test reverse
    std::cout << "\nReversing queue:" << std::endl;
    queue.reverse();
    queue.display();
    queue.displayDetailed();

    std::cout << std::endl;
  }

  static void demonstrateCopyOperations()
  {
    std::cout << "=== Copy Operations Demo ===" << std::endl;

    LinkedListQueue original;
    original.enqueue(100);
    original.enqueue(200);
    original.enqueue(300);

    std::cout << "Original queue:" << std::endl;
    original.display();

    // Test copy constructor
    LinkedListQueue copied(original);
    std::cout << "\nCopied queue (copy constructor):" << std::endl;
    copied.display();

    // Test assignment operator
    LinkedListQueue assigned;
    assigned = original;
    std::cout << "\nAssigned queue (assignment operator):" << std::endl;
    assigned.display();

    // Modify original to show independence
    std::cout << "\nModifying original queue:" << std::endl;
    original.enqueue(400);
    original.dequeue();

    std::cout << "Original after modification:" << std::endl;
    original.display();
    std::cout << "Copied queue (unchanged):" << std::endl;
    copied.display();
    std::cout << "Assigned queue (unchanged):" << std::endl;
    assigned.display();

    std::cout << std::endl;
  }
};

int main()
{
  std::cout << "=== Linked List-based Queue Implementation Demo ===" << std::endl
            << std::endl;

  try
  {
    LinkedQueueDemo::demonstrateBasicOperations();
    LinkedQueueDemo::demonstrateDynamicGrowth();
    LinkedQueueDemo::demonstrateErrorHandling();
    LinkedQueueDemo::demonstrateAdvancedFeatures();
    LinkedQueueDemo::demonstrateCopyOperations();

    // Interactive mode
    std::cout << "=== Interactive Linked List Queue Testing ===" << std::endl;
    LinkedListQueue userQueue;
    std::string command;

    std::cout << "Commands: enqueue <value>, dequeue, front, rear, display, size, clear, contains <value>, getat <pos>, reverse, max, min, quit" << std::endl;

    while (true)
    {
      std::cout << "> ";
      std::cin >> command;

      if (command == "quit")
      {
        break;
      }
      else if (command == "enqueue")
      {
        int value;
        std::cin >> value;
        userQueue.enqueue(value);
        std::cout << "Enqueued " << value << std::endl;
      }
      else if (command == "dequeue")
      {
        try
        {
          int value = userQueue.dequeue();
          std::cout << "Dequeued " << value << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else if (command == "front")
      {
        try
        {
          std::cout << "Front: " << userQueue.front() << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else if (command == "rear")
      {
        try
        {
          std::cout << "Rear: " << userQueue.rear() << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else if (command == "display")
      {
        userQueue.display();
        userQueue.displayDetailed();
      }
      else if (command == "size")
      {
        std::cout << "Size: " << userQueue.size() << std::endl;
      }
      else if (command == "clear")
      {
        userQueue.clear();
        std::cout << "Queue cleared" << std::endl;
      }
      else if (command == "contains")
      {
        int value;
        std::cin >> value;
        std::cout << "Contains " << value << "? " << (userQueue.contains(value) ? "Yes" : "No") << std::endl;
      }
      else if (command == "getat")
      {
        int pos;
        std::cin >> pos;
        try
        {
          std::cout << "Element at position " << pos << ": " << userQueue.getAt(pos) << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else if (command == "reverse")
      {
        userQueue.reverse();
        std::cout << "Queue reversed" << std::endl;
        userQueue.display();
      }
      else if (command == "max")
      {
        try
        {
          std::cout << "Maximum: " << userQueue.findMax() << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else if (command == "min")
      {
        try
        {
          std::cout << "Minimum: " << userQueue.findMin() << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      else
      {
        std::cout << "Unknown command. Available: enqueue, dequeue, front, rear, display, size, clear, contains, getat, reverse, max, min, quit" << std::endl;
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "Goodbye!" << std::endl;
  return 0;
}