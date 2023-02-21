#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    linkedlist()
    {
        head = NULL;
        tail = NULL;
    }

    node *search(int data)
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
        temp->next = head;
        head = temp;
    }

    void insertAfterNode(node *curr, char data) // gonna insert 'data' after node 'curr'
    {
        node *temp = new node(data, NULL);
        temp->next = curr->next;
        curr->next = temp; // be careful about the order so the link doesn't get lost
    }

    void insertLast(char data)
    {
        if (!head)
            insertFirst(data);
        else
        {
            node *curr = head;
            while (curr->next != NULL)
                curr = curr->next;
            insertAfterNode(curr, data);
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
    	if(head->next == NULL)
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
            for (node *curr = head; curr != NULL; curr = curr->next)
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
    bool isEmpty()
    {
        return Stack.head == NULL;
    }
    void push(char val)
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
    char peek()
    {
        if (isEmpty())
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

string rev_string(string x)
{
    MyStack s;
    int i = 0;
    while (i < x.length())
    {
        s.push(x[i++]);
    }
    i = 0;
    while (!s.isEmpty())
    {
        x[i] = s.peek();
        i++;
        s.pop();
    }
    return x;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    string x;
    cin >> x;
    cout << rev_string(x) << endl;
    return 0;
}
