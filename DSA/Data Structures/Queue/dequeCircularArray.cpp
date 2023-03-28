#include <bits/stdc++.h>
using namespace std;

int const N = 1e5;

class MycircularDeque
{
    int *deque;
    int total_elements;
    int front;
    int rear;
    int capacity;

public:
    MycircularDeque(int x = N)
    {
        capacity = x;
        deque = new int[capacity];
        total_elements = 0;
        front = 0;
        rear = -1;
    }
    bool empty()
    {
        return (!total_elements);
    }
    bool full()
    {
        return total_elements == capacity;
    }
    void pushFront(int x)
    {
        if (full())
        {
            cout << "Q is full.\n";
            return;
        }
        if (front == 0)
        {
            front = capacity - 1;
            deque[front] = x;
            total_elements++;
            return;
        }
        front--;
        total_elements++;
        deque[front] = x;
    }
    void pushRear(int x)
    {
        if (full())
        {
            cout << "Queue is full.\n";
            return;
        }
        rear++; // if it is not full, either left or right side is partially empty
        rear %= capacity;
        deque[rear] = x;
        total_elements++;
    }
    void popFront()
    {
        if (empty())
        {
            cout << "Empty Queue.\n";
            return;
        }
        total_elements--;
        front++;
        front %= capacity;
    }
    void popRear()
    {
        if (empty())
        {
            cout << "Empty Queue.\n";
            return;
        }
        total_elements--;
        if (rear == 0)
        {
            rear = capacity - 1;
        }
        else
        {
            rear--;
        }
    }
    int size()
    {
        return total_elements;
    }
    void printDeque()
    {
        if (empty())
        {
            return;
        }
        int i = front;
        while (i != rear)
        {
            cout << deque[i] << " ";
            i++;
            i %= capacity;
        }
        cout << deque[rear] << endl;
    }
};

int main()
{
    MycircularDeque deq = MycircularDeque(5);
    deq.pushFront(3);
    deq.pushRear(4);
    deq.pushRear(5);
    deq.printDeque();
    deq.popRear();
    deq.printDeque();
    deq.pushFront(2);
    deq.printDeque();
    deq.popFront();
    deq.printDeque();
    cout << deq.empty() << endl;
    return 0;
}