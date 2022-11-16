#include <iostream>
#include <cstdlib>
using namespace std;
 
#define SIZE 1000
 
class Queue
{
    int *arr;       
    int capacity;   
    int front;      
    int rear;       
    int count;      
 
public:
    Queue(int size = SIZE);     
    ~Queue();                   
 
    int dequeue();
    void enqueue(int x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};
 
Queue::Queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}
 
Queue::~Queue() {
    delete[] arr;
}
 
int Queue::dequeue()
{
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    int x = arr[front];
    cout << "Removing " << x << endl;
 
    front = (front + 1) % capacity;
    count--;
 
    return x;
}
 
void Queue::enqueue(int item)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
 
    cout << "Inserting " << item << endl;
 
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}
 
int Queue::peek()
{
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}
 
int Queue::size() {
    return count;
}
 
bool Queue::isEmpty() {
    return (size() == 0);
}
 
bool Queue::isFull() {
    return (size() == capacity);
}
 