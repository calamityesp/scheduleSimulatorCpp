#include <iostream>
#include <cstdlib>
using namespace std;
 
// Define the default capacity of the stack
#define STACKSIZE 10
 
// A class to represent a stack
template<class T>
class Stack
{
    T *arr;
    int top;
    int capacity;
 
public:
    Stack(int size = STACKSIZE);         // constructor
    ~Stack();                       // destructor
 
    void push(T);
    T pop();
    T peek();
 
    int size();
    bool isEmpty();
    bool isFull();
};
 
// Constructor to initialize the stack
template<class T>
Stack<T>::Stack(int size)
{
    arr = new T[size];
    capacity = size;
    top = -1;
}
 
// Destructor to free memory allocated to the stack
template<class T>
Stack<T>::~Stack() {
    delete[] arr;
}
 
// Utility function to add an element `x` to the stack
template<class T>
void Stack<T>::push(T x)
{
    if (isFull())
    {
        cout << "StackOverflow. Quiting";
        exit(EXIT_FAILURE);
    }
     
    arr[++top] = x;
}
 
// Utility function to pop a top element from the stack
template<class T>
T Stack<T>::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Removing " << peek() << endl;
 
    // decrease stack size by 1 and (optionally) return the popped element
    return arr[top--];
}
 
// Utility function to return the top element of the stack
template<class T>
T Stack<T>::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
 
// Utility function to return the size of the stack
template<class T>
int Stack<T>::size() {
    return top + 1;
}
 
// Utility function to check if the stack is empty or not
template<class T>
bool Stack<T>::isEmpty() {
    return top == -1;               // or return size() == 0;
}
 
// Utility function to check if the stack is full or not
template<class T>
bool Stack<T>::isFull() {
    return top == capacity - 1;     // or return size() == capacity;
}