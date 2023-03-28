#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class MyStack
{
public:
    int capacity, length, top;
    int Stack[1000000];

    MyStack()
    {
        capacity = 1000000;
        top = -1;
    }

    MyStack(int _capacity)
    {
        capacity = _capacity;
        top = -1;
    }

    void push(int data)
    {
        if (top >= capacity - 1) /** if top is already in the last index (capacity - 1),
                                 it has a value in it so cannot push anymore */
            cout << "Stack overflow" << endl;
        else                       /** do not increase the top before checking if it's overflow */
        {
            Stack[++top] = data;
            length++;
        }
    }

    int search_index(int indx)
    {
        return Stack[indx];
    }

    void pop()
    {
        if (top == -1)
            cout << "Empty Stack" << endl;
        else
        {
            Stack[top--] = 0;
            length--;
        }
    }

    int peek()
    {
        return Stack[top];
    }

    bool isFull()
    {
        return length == capacity;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void printStack()
    {
        int x = top; // save the top so that it remains the same after print operation
        while (!isEmpty())
        {
            cout << Stack[top--] << " ";
        }
        cout << endl;
        top = x; // reset top to its previous value
    }
    int size()
    {
        return length;
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    MyStack s(10);

    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }

    s.printStack();
    s.pop();
    s.printStack();
    s.push(1);
    s.printStack();
    s.push(2);
    s.printStack();
    cout << s.size() << endl;
    cout << s.search_index(3) << endl;

    return 0;
}