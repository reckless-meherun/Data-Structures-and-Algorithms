#include<bits/stdc++.h>
using namespace std;
int Max = 1000000;

class MyQueue
{
public:
    int *queue;
    int top;
    int tail;

    MyQueue()
    {
        top = 0;
        tail = -1;
        queue = new int[Max];
    }

    bool empty()
    {        
        if(top>tail)
        {
            top=0;
            tail=-1;
            return true;
        }
        return false;
    }

    void push(int data)
    {
        if (tail < Max - 1)
        {
            tail++;
            queue[tail] = data;
        }
        else
            cout<<"Queue Overflow"<<endl;
    }

    void pop()
    {
        if(empty())
            cout<<"Empty Queue"<<endl;
        else
            top++;
    }

    int front()
    {
        return queue[top];
    }

    void clear()
    {
        for (int i = 0; i <= tail; i++)
        {
            queue[i]=0;
        }        
    }

    void printQueue()
    {
        for (int i = top; i <= tail; i++)
        {
            cout<<queue[i]<<" ";
        }
        cout<<endl;
    }

    int size()
    {
        if(tail>=top)
            return tail-top + 1;
        return 0;
    }

};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    MyQueue q;
    for (int i = 0; i < 5; i++)
    {
        q.push(i);
    }
    q.printQueue();
    cout<<q.size()<<endl;
    while (!q.empty())
    {
        q.pop();
    }
    cout<<q.size()<<endl;
    q.printQueue();    
    return 0;
}