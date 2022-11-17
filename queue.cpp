#include <iostream>
#include <cstdlib>
using namespace std;
 
#define SIZE 1000

template <class T> 
class Queue
{
    T *arr;       
    int capacity;   
    int front;      
    int rear;       
    int count;      
 
public:
    Queue(int size = SIZE);     
    ~Queue();                   
 
    T dequeue();
    void enqueue(T x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};

template <class T>
Queue<T>::Queue(int size)
{
    arr = new T[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}


template <class T>
Queue<T>::~Queue() {
    delete[] arr;
}


template <class T>
T Queue<T>::dequeue()
{
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    T x = arr[front];
 
    front = (front + 1) % capacity;
    count--;
 
    return x;
}
 

template <class T>
void Queue<T>::enqueue(T item)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }    
 
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}


template <class T>
int Queue<T>::peek()
{
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}

template <class T>
int Queue<T>::size() {
    return count;
}

template <class T>
bool Queue<T>::isEmpty() {
    return (size() == 0);
}

template <class T>
bool Queue<T>::isFull() {
    return (size() == capacity);
}
 