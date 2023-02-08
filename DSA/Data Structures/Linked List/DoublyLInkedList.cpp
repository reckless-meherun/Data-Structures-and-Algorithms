#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    node *prev;
    int data;
    node *next;

    node()
    {
        prev = NULL;
        data = 0;
        next = NULL;
    }
    node(node *_prev, int _data, node *_next)
    {
        prev = _prev;
        data = _data;
        next = _next;
    }
};

node *first_node = NULL;
class Doublinkedlist
{
public:
    node *head;
    Doublinkedlist()
    {
        head = NULL;
    }

    void insertFirst(int data)
    {
        node *temp = new node(NULL, data, NULL);
        temp->next = head;
        head->prev = temp;
        head = temp;
    }

    void insertAfternode(int indx, int data) // gonna insert 'data' after node 'curr'
    {
        node *curr = head;
        int count = 1;
        while (count <= indx)
        {
            count++;
            curr = curr->next;
        }
        node *temp = new node(NULL, data, NULL);
        temp->next = curr->next;
        temp->prev = curr;
        curr->next->prev = temp;
        curr->next = temp;
    }

    void insertLast(int data)
    {
        if (!head)
            insertFirst(data);
        else
        {
            node *curr = head;
            int count = 0;
            while (curr->next != NULL)
            {
                curr = curr->next;
                count++;
            }
            cout << count << endl;
            // insertAfternode(count-1, data);
            node *temp = new node(NULL, data, NULL);
            curr->next = temp;
            temp->prev = curr;
            temp->next = NULL;    
            first_node = temp;       
        }
    }

    void deleteFirst()
    {
        node *top = head;
        head = top->next;
        head->prev=NULL;
        delete (top);
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
        curr->next->next->prev = curr;
        curr->next = curr->next->next;                
    }

    void deleteLast()
    {
        node *curr;
        for (curr = head; curr->next->next != NULL; curr = curr->next)
        {

        }
        curr->next = NULL;
        first_node = curr;
        delete (curr->next);
    }

    void printListForward(node *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty DoubLinkedList" << endl;
        }
        else
        {
            for (node *curr = HEAD; curr != NULL; curr = curr->next)
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
    }
    void printListBackward(node *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty DoubLinkedList" << endl;
        }
        else
        {
            for (node *curr = HEAD; curr != NULL; curr = curr->prev)
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    Doublinkedlist a;
    
    int n;
    cin >> n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        if (i == 0)
        {
            a.head = new node(NULL, x, NULL);
            first_node = a.head;
        }
        else
        {
            node *temp = a.head;
            a.head = new node(NULL, x, a.head);
            temp->prev = a.head;
        }
    }
    node *curr = a.head;

    a.insertAfternode(3, 10); //insert after 3rd index
    a.insertFirst(90);
    a.insertLast(100);
    a.deleteFirst();
    a.deleteLast();
    a.deleteAfterNode(2);
    a.printListForward(a.head);
    a.printListBackward(first_node);
    return 0;
}