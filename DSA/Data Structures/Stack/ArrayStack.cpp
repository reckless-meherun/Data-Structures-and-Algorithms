#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
class MyStack
{
public:
    int Stack[10000+5];
    int top = -1;

    void push(int data)
    {
        top++;
        if(top<100000)
            Stack[top] = data;
        else
            cout<<"Stack overflow"<<endl;
    }

    int search_index(int indx)
    {
        return Stack[indx];
    }

    void pop()
    {
        if(top==-1)
            cout<<"Empty Stack"<<endl;
        else
            Stack[top--] = 0;
    }    
    
    int peek()
    {
        return Stack[top];
    }

    bool isFull()
    {
        return top == 100000-1;
    }

    bool isEmpty()
    {
        return top==-1;
    }

    void printStack()
    {
        while (!isEmpty())
        {
            cout<<Stack[top--]<<" ";
        }        
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    MyStack s;
   
    return 0;
}