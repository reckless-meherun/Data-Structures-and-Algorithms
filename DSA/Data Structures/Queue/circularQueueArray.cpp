#include <bits/stdc++.h>
using namespace std;
int Max = 1000000;

class MyQueue
{
public:
    int *queue;
    int front;
    int rear;
    int total_elements;
    int capacity;

    MyQueue(int x = Max)
    {
        front = 0;
        rear = -1;
        queue = new int[x];
        total_elements = 0;
        capacity = x;
    }

    bool empty()
    {
        return total_elements == 0;
    }

    bool overflow()
    {
        return total_elements == capacity;
    }

    void push(int data)
    {
        if (overflow())
        {
            cout << "Queue Overflow" << endl;
        }
        else
        {
            rear++;
            queue[rear %= capacity] = data;
            total_elements++;
        }
    }

    void pop()
    {
        if (empty())
            cout << "Empty Queue" << endl;
        else
        {
            (front %= capacity)++;
            total_elements--;
        }
    }

    int front()
    {
        return queue[front];
    }

    void clear()
    {
        for (int i = 0; i < capacity; i++)
        {
            queue[i] = 0;
        }
        front = 0;
        rear = -1;
    }

    void printQueue()
    {
        if (empty())
        {
            cout << "Empty Queue" << endl;
            return;
        }
        int i = front;
        while (i != rear)
        {
            cout << queue[i % capacity] << " ";
            i++;
            i %= capacity;
        }
        cout << queue[rear] << endl;
    }

    int size()
    {
        return total_elements;
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    MyQueue q(5);
    for (int i = 0; i < 8; i++)
    {
        q.push(i);
    }
    q.printQueue();
    q.pop();
    q.printQueue();
    q.push(5);
    q.printQueue();
    // cout<<q.size()<<endl;
    return 0;
}