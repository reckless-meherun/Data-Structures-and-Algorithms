#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    string data;
    node *next;

    node()
    {
        data = "0";
        next = NULL;
    }
    node(string _data, node *_next)
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

    node *search(string data)
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

    void insertFirst(string data)
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

    void insertAfterNode(node *curr, string data) // gonna insert 'data' after node 'curr'
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

    void insertLast(string data)
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

    void remove(string val)
    {
        node *dummy = new node("-1", NULL);
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
    void push(string val)
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
    string top()
    {
        if (empty())
        {
            cout << "Empty Stack" << endl;
            return " ";
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
            Stack.tail->data = "0";
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

int main()
{
    string postfix;
    //stack<string> infix;
    MyStack infix;
    cin >> postfix;
    for (int i = 0; i < postfix.length(); i++)
    {
        if ((postfix[i] >= 'A' and postfix[i] <= 'Z') or (postfix[i] >= 'a' and postfix[i] <= 'z') or (postfix[i] >= '0' and postfix[i] <= '9'))
        {
            infix.push(string(1, postfix[i])); //converting a single character to a string
            // string class has a constructor
            // that allows us to specify size of
            // string as first parameter and character
            // to be filled in given size as second
            // parameter.
        }
        else
        {
            string operand_one = infix.top();
            infix.pop();
            string operand_two = infix.top();
            infix.pop();
            char operator_between = postfix[i];

            string need_to_push = "(" + operand_two + operator_between + operand_one + ")";
            infix.push(need_to_push);
        }
    }

    cout << infix.top() << endl;

    return 0;
}