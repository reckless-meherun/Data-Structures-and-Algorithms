#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    char data;
    node *next;

    node()
    {
        data = 0;
        next = NULL;
    }
    node(char _data, node *_next)
    {
        data = _data;
        next = _next;
    }
};

class linkedlist
{
public:
    node *head, *tail;
    int flag = 0;
    int flag_rev = 0;
    linkedlist()
    {
        head = NULL;
        tail = NULL;
    }

    node *search(char data)
    {
        for (node *curr = head; curr != NULL; curr = curr->next)
        {
            if (curr->data == data)
            {
                cout << "found at " << curr << endl;
                return curr;
            }
        }
        cout << "not found" << endl;
        return NULL;
    }

    void insertFirst(char data)
    {
        node *temp = new node(data, NULL);
        if (temp == NULL)
        {
            cout << "Stack Overflow" << endl;
            return;
        }
        temp->next = head;
        head = temp;
        tail = head;
    }

    void insertAfterNode(node *curr, char data) // gonna insert 'data' after node 'curr'
    {
        node *temp = new node(data, NULL);
        if (temp == NULL)
        {
            cout << "Stack Overflow" << endl;
            return;
        }
        temp->next = curr->next;
        curr->next = temp; // be careful about the order so the link doesn't get lost
    }

    void insertLast(char data)
    {
        if (!head)
            insertFirst(data);
        else
        {
            node *curr = tail;
            if (flag == 0)
            {
                while (curr->next != NULL)
                    curr = curr->next;
                flag = 1;
            }
            insertAfterNode(curr, data);
            tail = curr->next;
        }
    }

    void deleteFirst()
    {
        node *top = head;
        head = top->next;
        delete (top);
    }

    void deleteLast()
    {
        if (head->next == NULL)
        {
            head = NULL;
            return;
        }

        node *curr;

        for (curr = head; curr->next->next != NULL; curr = curr->next)
        {
        }
        curr->next = NULL;
        delete (curr->next);
    }

    void deleteAfterNode(int del) // delete the del_th element from the linkedlist
    {
        node *curr = head;
        int Index = 0;
        while (Index != del)
        {
            curr = curr->next;
            Index++;
        }
        node *to_delete = curr->next;
        curr->next = curr->next->next;
        delete (to_delete);
    }

    void remove(char val)
    {
        node *dummy = new node(-1, NULL);
        dummy->next = head;
        node *curr = dummy;
        while (curr != NULL and curr->next != NULL)
        {
            if (curr->next->data == val)
            {
                curr->next = curr->next->next;
            }
            else
            {
                curr = curr->next;
            }
        }
        head = dummy->next;
        return;
    }

    node *reverseList()
    {
        node *prev_head = head;
        node *temp1 = NULL, *temp2 = NULL;
        while (prev_head != NULL)
        {
            temp2 = prev_head->next;
            prev_head->next = temp1;
            temp1 = prev_head;
            prev_head = temp2;
            if (flag_rev == 0)
            {
                tail = temp1;
                flag_rev = 1;
            }
        }
        prev_head = temp1;
        return prev_head;
    }

    void printList()
    {
        if (!head)
        {
            cout << "Empty LinkedList" << endl;
        }
        else
        {
            head = reverseList();
            for (node *curr = head; curr != tail->next; curr = curr->next)
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
    }
};

class MyStack
{
public:
    linkedlist Stack;
    bool empty()
    {
        return Stack.head == NULL;
    }
    void push(int val)
    {
        if (!Stack.head)
            Stack.insertFirst(val);
        else
            Stack.insertLast(val);
    }
    void pop()
    {
        Stack.deleteLast();
    }
    int top()
    {
        if (empty())
        {
            cout << "Empty Stack" << endl;
            return ' ';
        }
        else
        {
            Stack.tail = Stack.head;
            while (Stack.tail->next)
            {
                Stack.tail = Stack.tail->next;
            }
            return Stack.tail->data;
        }
    }
    void clear()
    {
        Stack.tail = Stack.head;
        while (Stack.tail)
        {
            Stack.tail->data = 0;
            Stack.tail = Stack.tail->next;
        }
    }
    void printStack()
    {
        Stack.printList();
    }
    int size()
    {
        int count = 0;
        Stack.tail = Stack.head;
        while (Stack.tail)
        {
            count++;
            Stack.tail = Stack.tail->next;
        }
        return count;
    }
};

int check_precedence(char oper)
{
    if (oper == '/')
        return 4;
    if (oper == '*')
        return 4;
    if (oper == '+')
        return 3;
    if (oper == '-')
        return 3;
    return 0;
}

int main()
{
    // stack<char> s;
    MyStack s;
    string infix;
    cin >> infix; // take vector<string> if infix contains space

    string postfix = "";

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(' or infix[i] == '{' or infix[i] == '[')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == '}')
        {
            while (s.top() != '{')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (infix[i] == ']')
        {
            while (s.top() != '[')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if ((infix[i] >= 'a' and infix[i] <= 'z') or (infix[i] >= 'A' and infix[i] <= 'Z') or (infix[i] >= '0' and infix[i] <= '9'))
        {
            postfix += infix[i];
        }
        else
        {
            while (!s.empty() and (check_precedence(s.top()) >= check_precedence(infix[i])))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
    }

    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    cout << "Postfix notation: " << postfix << endl;

    return 0;
}