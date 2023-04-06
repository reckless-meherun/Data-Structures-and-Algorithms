#include <bits/stdc++.h>
using namespace std;

class MyQueue
{
public:
    int *queue, top, tail, capacity, length;

    MyQueue()
    {
        capacity = 1000000;
        top = 0;
        tail = -1;
        length = 0;
        queue = new int[capacity];
    }

    MyQueue(int _capacity)
    {
        capacity = _capacity;
        top = 0;
        tail = -1;
        length = 0;
        queue = new int[capacity];
    }

    void push(int data)
    {
        if (length < capacity)
        {
            queue[++tail] = data;
            length++;
        }
        else
            cout << "Queue Overflow" << endl;
    }

    void pop()
    {
        if (empty())
            cout << "Empty Queue" << endl;
        else
        {
            top++;
            length--;
        }
    }

    int front()
    {
        if (empty())
        {
            cout << "Empty queue; returned : ";
            return -1;
        }
        return queue[top];
    }

    int back()
    {
        if (empty())
        {
            cout << "Empty queue; returned : ";
            return -1;
        }
        return queue[tail];
    }

    bool empty()
    {
        return length == 0;
    }

    bool full()
    {
        return length == capacity;
    }

    int size()
    {
        return length;
    }

    void clear()
    {
        if (empty())
            return;
        memset(queue, 0, sizeof(queue));
        length = 0;
        top = 0;
        tail = -1;
    }

    int search_index(int indx)
    {
        if (indx >= length)
        {
            cout << "Wrong index; returned : ";
            return -1;
        }
        if (empty())
        {
            cout << "Empty queue; returned : ";
            return -1;
        }
        return queue[indx];
    }

    void printQueue()
    {
        if (empty())
        {
            cout << "Empty queue" << endl;
            return;
        }

        for (int i = top; i <= tail; i++) // no need to use "till empty" as queue has two pointers: top and tail
        {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    MyQueue q(10);
    for (int i = 0; i < 5; i++)
    {
        q.push(i);
    }
    q.printQueue();
    cout << q.size() << endl;
    while (!q.empty())
    {
        q.pop();
    }
    cout << q.size() << endl;
    q.printQueue();
    q.push(19);
    q.push(50);
    q.printQueue();
    cout << q.back() << endl;
    cout << q.size() << endl;
    cout << q.search_index(3);
    return 0;
}