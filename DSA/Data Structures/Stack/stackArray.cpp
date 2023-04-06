#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class MyStack
{
public:
    int *Stack, capacity, length, top;

    MyStack()
    {
        capacity = 1000000;
        top = -1;
        length = 0;
        Stack = new int[capacity];
    }

    MyStack(int _capacity)
    {
        capacity = _capacity;
        top = -1;
        length = 0;
        Stack = new int[capacity];
    }

    void push(int data)
    {
        if (length < capacity) /** do not increase the top before checking if it's overflow */
        {
            Stack[++top] = data;
            length++;
        }
        else /** if u use top (ঝামেলা): if top is already in the last index (capacity - 1),
                                it has a value in it so cannot push anymore */
        {
            cout << "Stack overflow" << endl;
        }
    }

    void pop()
    {
        if (isEmpty())
            cout << "Empty Stack" << endl;
        else
        {
            Stack[top--] = 0;
            length--;
        }
    }

    int peek()
    {
        if (isEmpty())
        {
            cout << "Empty stack; returned : ";
            return -1;
        }
        return Stack[top];
    }

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == capacity;
    }   

    int size()
    {
        return length;
    }

    void clear()
    {
        if (isEmpty())
            return;
        memset(Stack, 0, sizeof(Stack));
        length = 0;
        top = -1;
    }

    int search_index(int indx)
    {
        if (indx >= length)
        {
            cout << "Wrong index; returned : ";
            return -1;
        }
        if (isEmpty())
        {
            cout << "Empty stack; returned : ";
            return -1;
        }
        return Stack[indx];
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