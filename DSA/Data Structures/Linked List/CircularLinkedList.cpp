#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int data;
    node *next;
    node()
    {
        data = 0;
        next = NULL;
    }
    node(int _data, node *_next)
    {
        data = _data;
        next = _next;
    }
};

class circulinkedlist
{
public:
    node *head;
    node *tail;

    circulinkedlist()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAfterNode(node *curr, int data) // gonna insert 'data' after node 'curr'
    {
        node *temp = new node(data, NULL);
        temp->next = curr->next;
        curr->next = temp; // be careful about the order so the link doesn't get lost
    }

    void insertFirst(int data)
    {
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
        tail->next = head;
    }

    void insertLast(int data)
    {
        insertAfterNode(tail, data);
    }

    void deleteFirst()
    {
        node *top = head;
        head = top->next;
        delete (top);
        tail->next = head;
        // tail->next = tail->next->next; // why isn't it working !!
    }

    void deleteLast()
    {
        node *curr = head;
        for (; curr->next->next != head; curr = curr->next)
        {
        }
        node *havetodel = curr->next;
        curr->next = curr->next->next;
        delete (havetodel);
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
        // delete(curr->next);
        curr->next = curr->next->next;
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
        head = prev_head;
        return prev_head;
    }
    void printList(node *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty LinkedList" << endl;
        }
        else
        {
            node *curr = HEAD;
            cout << curr->data << " ";
            curr = curr->next;
            for (; curr != NULL;)
            {
                cout << curr->data << " ";
                if (curr->next == HEAD)
                {
                    cout << endl;
                    return;
                }
                else
                {
                    curr = curr->next;
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    circulinkedlist a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (i == 0)
        {
            a.head = new node(x, NULL);
            a.tail = a.head;
        }
        else
        {
            a.head = new node(x, a.head);
        }
    }
    a.tail->next = a.head;    
    a.insertFirst(10);
    a.insertLast(20);
    a.printList(a.head);
    a.printList(a.head->next->next); // to prove that it's a circular linked list
    a.deleteFirst();
    a.deleteLast();
    a.deleteAfterNode(2);
    a.printList(a.head);    
    return 0;
}