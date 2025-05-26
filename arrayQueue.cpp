// Array-based Queue Implementation - C++ (Non-template version)
#include <iostream>
#include <stdexcept>
#include <string>

class ArrayQueue
{
private:
  int *array;      // Dynamic array to store queue elements
  int capacity;    // Maximum capacity of the queue
  int frontIndex;  // Index of the front element
  int rearIndex;   // Index of the rear element
  int currentSize; // Current number of elements in queue

public:
  // Constructor
  explicit ArrayQueue(int cap = 10) : capacity(cap), frontIndex(0), rearIndex(-1), currentSize(0)
  {
    if (cap <= 0)
    {
      throw std::invalid_argument("Queue capacity must be positive");
    }
    array = new int[capacity];
  }

  // Destructor
  ~ArrayQueue()
  {
    delete[] array;
  }

  // Copy constructor
  ArrayQueue(const ArrayQueue &other)
      : capacity(other.capacity), frontIndex(other.frontIndex),
        rearIndex(other.rearIndex), currentSize(other.currentSize)
  {
    array = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
      array[i] = other.array[i];
    }
  }

  // Assignment operator
  ArrayQueue &operator=(const ArrayQueue &other)
  {
    if (this != &other)
    {
      delete[] array;

      capacity = other.capacity;
      frontIndex = other.frontIndex;
      rearIndex = other.rearIndex;
      currentSize = other.currentSize;

      array = new int[capacity];
      for (int i = 0; i < capacity; i++)
      {
        array[i] = other.array[i];
      }
    }
    return *this;
  }

  // Enqueue operation - add element to rear
  void enqueue(int item)
  {
    if (isFull())
    {
      throw std::overflow_error("Queue is full - cannot enqueue");
    }

    rearIndex = (rearIndex + 1) % capacity; // Circular increment
    array[rearIndex] = item;
    currentSize++;
  }

  // Dequeue operation - remove element from front
  int dequeue()
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - cannot dequeue");
    }

    int frontElement = array[frontIndex];
    frontIndex = (frontIndex + 1) % capacity; // Circular increment
    currentSize--;

    return frontElement;
  }

  // Get front element without removing it
  int front() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no front element");
    }
    return array[frontIndex];
  }

  // Get rear element without removing it
  int rear() const
  {
    if (isEmpty())
    {
      throw std::underflow_error("Queue is empty - no rear element");
    }
    return array[rearIndex];
  }

  // Check if queue is empty
  bool isEmpty() const
  {
    return currentSize == 0;
  }

  // Check if queue is full
  bool isFull() const
  {
    return currentSize == capacity;
  }

  // Get current size of queue
  int size() const
  {
    return currentSize;
  }

  // Get maximum capacity of queue
  int getCapacity() const
  {
    return capacity;
  }

  // Clear all elements from queue
  void clear()
  {
    frontIndex = 0;
    rearIndex = -1;
    currentSize = 0;
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
    for (int i = 0; i < currentSize; i++)
    {
      int index = (frontIndex + i) % capacity;
      std::cout << array[index];
      if (i < currentSize - 1)
      {
        std::cout << " <- ";
      }
    }
    std::cout << std::endl;
  }

  // Display detailed queue state
  void displayDetailed() const
  {
    std::cout << "=== Queue State ===" << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Size: " << currentSize << std::endl;
    std::cout << "Front Index: " << frontIndex << std::endl;
    std::cout << "Rear Index: " << rearIndex << std::endl;
    std::cout << "Is Empty: " << (isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Is Full: " << (isFull() ? "Yes" : "No") << std::endl;

    if (!isEmpty())
    {
      std::cout << "Front Element: " << front() << std::endl;
      std::cout << "Rear Element: " << rear() << std::endl;
    }

    std::cout << "Array Layout: [";
    for (int i = 0; i < capacity; i++)
    {
      if (i > 0)
        std::cout << ", ";

      // Check if this position contains a queue element
      bool isQueueElement = false;
      if (!isEmpty())
      {
        for (int j = 0; j < currentSize; j++)
        {
          if ((frontIndex + j) % capacity == i)
          {
            isQueueElement = true;
            break;
          }
        }
      }

      if (isQueueElement)
      {
        std::cout << array[i];
        if (i == frontIndex)
          std::cout << "(F)";
        if (i == rearIndex)
          std::cout << "(R)";
      }
      else
      {
        std::cout << "_";
      }
    }
    std::cout << "]" << std::endl;
    std::cout << "===================" << std::endl;
  }

  // Resize queue (creates new queue with larger capacity)
  void resize(int newCapacity)
  {
    if (newCapacity <= currentSize)
    {
      throw std::invalid_argument("New capacity must be larger than current size");
    }

    int *newArray = new int[newCapacity];

    // Copy elements in order from front to rear
    for (int i = 0; i < currentSize; i++)
    {
      int oldIndex = (frontIndex + i) % capacity;
      newArray[i] = array[oldIndex];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
    frontIndex = 0;
    rearIndex = currentSize - 1;
  }

  // Additional utility functions

  // Check if queue contains a specific value
  bool contains(int value) const
  {
    for (int i = 0; i < currentSize; i++)
    {
      int index = (frontIndex + i) % capacity;
      if (array[index] == value)
      {
        return true;
      }
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
    int index = (frontIndex + position) % capacity;
    return array[index];
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
    for (int i = 0; i < currentSize; i++)
    {
      int index = (frontIndex + i) % capacity;
      std::cout << "Position " << i << ": " << array[index] << std::endl;
    }
  }
};

// Demo class to test the queue
class QueueDemo
{
public:
  static void demonstrateBasicOperations()
  {
    std::cout << "=== Basic Queue Operations Demo ===" << std::endl;

    ArrayQueue queue(5);

    std::cout << "Created queue with capacity 5" << std::endl;
    queue.displayDetailed();

    // Enqueue operations
    std::cout << "\nEnqueuing elements: 10, 20, 30" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();
    queue.displayDetailed();

    // Front and rear operations
    std::cout << "\nFront element: " << queue.front() << std::endl;
    std::cout << "Rear element: " << queue.rear() << std::endl;

    // Test contains function
    std::cout << "Contains 20? " << (queue.contains(20) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 50? " << (queue.contains(50) ? "Yes" : "No") << std::endl;

    // Test getAt function
    std::cout << "Element at position 1: " << queue.getAt(1) << std::endl;

    // Dequeue operations
    std::cout << "\nDequeuing elements:" << std::endl;
    while (!queue.isEmpty())
    {
      std::cout << "Dequeued: " << queue.dequeue() << std::endl;
      queue.display();
    }

    std::cout << std::endl;
  }

  static void demonstrateCircularBehavior()
  {
    std::cout << "=== Circular Queue Behavior Demo ===" << std::endl;

    ArrayQueue queue(4);

    // Fill the queue
    std::cout << "Filling queue with 65, 66, 67, 68 (representing A, B, C, D):" << std::endl;
    queue.enqueue(65); // A
    queue.enqueue(66); // B
    queue.enqueue(67); // C
    queue.enqueue(68); // D
    queue.displayDetailed();

    // Dequeue some elements
    std::cout << "\nDequeuing 2 elements:" << std::endl;
    queue.dequeue();
    queue.dequeue();
    queue.displayDetailed();

    // Add more elements to show circular behavior
    std::cout << "\nAdding 69 and 70 (representing E and F) - circular wrap-around:" << std::endl;
    queue.enqueue(69); // E
    queue.enqueue(70); // F
    queue.displayDetailed();

    std::cout << std::endl;
  }

  static void demonstrateErrorHandling()
  {
    std::cout << "=== Error Handling Demo ===" << std::endl;

    ArrayQueue queue(2);

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

    // Test full queue operations
    std::cout << "\nFilling queue to capacity and testing overflow:" << std::endl;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.display();

    try
    {
      queue.enqueue(3);
    }
    catch (const std::exception &e)
    {
      std::cout << "Enqueue error: " << e.what() << std::endl;
    }

    std::cout << std::endl;
  }

  static void demonstrateResizing()
  {
    std::cout << "=== Queue Resizing Demo ===" << std::endl;

    ArrayQueue queue(3);

    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);

    std::cout << "Original queue:" << std::endl;
    queue.displayDetailed();

    std::cout << "\nResizing to capacity 6:" << std::endl;
    queue.resize(6);
    queue.displayDetailed();

    std::cout << "\nAdding more elements after resize:" << std::endl;
    queue.enqueue(400);
    queue.enqueue(500);
    queue.display();
    queue.printWithPositions();

    std::cout << std::endl;
  }

  static void demonstrateUtilityFunctions()
  {
    std::cout << "=== Utility Functions Demo ===" << std::endl;

    ArrayQueue queue(6);

    // Add some elements
    for (int i = 1; i <= 5; i++)
    {
      queue.enqueue(i * 10);
    }

    std::cout << "Queue after adding 10, 20, 30, 40, 50:" << std::endl;
    queue.display();

    // Test utility functions
    std::cout << "\nUtility function tests:" << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    std::cout << "Capacity: " << queue.getCapacity() << std::endl;
    std::cout << "Contains 30? " << (queue.contains(30) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 60? " << (queue.contains(60) ? "Yes" : "No") << std::endl;

    queue.printWithPositions();

    std::cout << "\nClearing queue..." << std::endl;
    queue.clear();
    queue.display();

    std::cout << std::endl;
  }
};

int main()
{
  std::cout << "=== Array-based Queue Implementation Demo (Non-template) ===" << std::endl
            << std::endl;

  try
  {
    QueueDemo::demonstrateBasicOperations();
    QueueDemo::demonstrateCircularBehavior();
    QueueDemo::demonstrateErrorHandling();
    QueueDemo::demonstrateResizing();
    QueueDemo::demonstrateUtilityFunctions();

    // Interactive mode
    std::cout << "=== Interactive Queue Testing ===" << std::endl;
    ArrayQueue userQueue(5);
    std::string command;

    std::cout << "Commands: enqueue <value>, dequeue, front, rear, display, size, clear, contains <value>, getat <pos>, quit" << std::endl;

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
        try
        {
          userQueue.enqueue(value);
          std::cout << "Enqueued " << value << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cout << "Error: " << e.what() << std::endl;
        }
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
      else
      {
        std::cout << "Unknown command. Available: enqueue, dequeue, front, rear, display, size, clear, contains, getat, quit" << std::endl;
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