#include <bits/stdc++.h>
using namespace std;
int Max = 1000000;

class MyQueue
{
public:
    int *queue;
    int top;
    int tail;
    int len;
    int n;

    MyQueue(int x = Max)
    {
        top = 0;
        tail = -1;
        queue = new int[x];
        len = 0;
        n=x;
    }

    bool empty()
    {
        return len == 0;
    }

    bool overflow()
    {
        return len == n;
    }

    void push(int data)
    {
        if (overflow())
        {
            cout << "Queue Overflow" << endl;
        }
        else
        {
            tail++;
            queue[tail %= n] = data;
            len++;
        }
    }

    void pop()
    {
        if (empty())
            cout << "Empty Queue" << endl;
        else
        {
            (top %= n)++;
            len--;
        }
    }

    int front()
    {
        return queue[top];
    }

    void clear()
    {
        for (int i = 0; i < n; i++)
        {
            queue[i] = 0;
        }
    }

    void printQueue()
    {
        if (empty())
        {
            cout << "Empty Queue" << endl;
            return;
        }
        int i=top;
        while (i != tail)
        {            
            cout << queue[i%n] << " ";
            i++;
            i%=n;
        }
        cout<<queue[tail]<<endl;
    }

    int size()
    {
        return len;
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
    //cout<<q.size()<<endl;
    return 0;
}