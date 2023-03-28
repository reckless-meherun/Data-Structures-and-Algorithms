#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int data;
    node *next, *prev;
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

class DoublyLinkedList
{
public:
    node *head, *tail;
    int size;
    DoublyLinkedList()
    {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    node *search(int data)
    {
        int count = 0;
        for (node *curr = head; curr != NULL; curr = curr->next)
        {
            if (curr->data == data)
            {
                cout << "found at index : " << count << endl;
                return curr;
            }
            count++;
        }
        cout << "not found" << endl;
        return NULL;
    }

    void insertFirst(int data)
    {
        if(!head) /** u cannot use head->prev when head is null */
        {
        	head = new node(NULL, data, NULL);
            tail = head;
            size++;
            return;
        }
        node *temp = new node(NULL, data, NULL);
        temp->next = head;
        head->prev = temp;
        head = temp;
        size++;
    }

    void insertAfterIndex(int ins, int data) // gonna insert 'data' after node 'curr'
    {
        if(ins >= size)
        {
            cout<< "Wrong index!"<<endl;
            return;
        }
        node *curr = head;
        int Index = 0;
        while (Index != ins)
        {
            Index++;
            curr = curr->next;
        }
        if (curr == tail) // if the indexing is at the last node
        {
            node *temp = new node(NULL, data, NULL);
            curr->next = temp;
            temp->prev = curr;
            tail = temp;
            size++;
            return;
        }
        node *temp = new node(NULL, data, NULL);
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        temp->prev = curr;
        // be careful about the order so the link doesn't get lost
        size++;
    }

    void insertLast(int data)
    {
        if (!head)
            insertFirst(data);
        else
        {
            insertAfterIndex(size - 1, data);
        }
    }

    void deleteFirst()
    {
        if (!head)
            return;
        node *top = head;
        head = top->next;
        if (!head)
        {
            tail = NULL;
            size--;
            return;
        }
        head->prev = NULL;
        free(top);
        size--;
    }

    void deleteLast()
    {
        if (!head)
            return;
        node *to_delete = tail;
        tail = tail->prev;
        if (!tail)
        {
            head = NULL;
            size--;
            return;
        }
        tail->next = NULL;
        free(to_delete);
        size--;
    }

    void deleteAtIndex(int del) // delete the element at index del (0 indexing) from the DoublyLinkedList
    {
        if (del == 0)
        {
            deleteFirst();
            return;
        }
        node *curr = head;
        int Index = 0;
        while (Index != del - 1)
        {
            Index++;
            curr = curr->next;
        }
        if (curr->next->next == NULL) // if the indexing is at the last node
        {
            deleteLast();
            return;
        }
        //cout << "index " << Index << " value " << curr->data << endl;
        node *to_delete = curr->next;
        curr->next->next->prev = curr;
        curr->next = curr->next->next; // cannot write this before as curr->next gets changed
        free(to_delete);
        size--;
    }

    void remove(int val)
    {
        node *dummy = new node(NULL, -1, NULL);
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

    void printListForward()
    {
        if (!head)
        {
            cout << "Empty DoublyLinkedList" << endl;
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
    void printListBackward()
    {
        if (!tail)
        {
            cout << "Empty DoublyLinkedList" << endl;
        }
        else
        {
            for (node *curr = tail; curr != NULL; curr = curr->prev)
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    DoublyLinkedList a;
    int n;
    cin >> n;
    
    /** u write either what's commented out or what's written*/
    
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (i == 0)
        {
            // a.head = new node(NULL, x, NULL);
            // a.tail = a.head;
            a.insertFirst(x);
        }
        else
        {
            // a.tail->next = new node(NULL, x, NULL);
            // a.tail->next->prev = a.tail;
            // a.tail = a.tail->next;
            a.insertLast(x);
        }
       // a.size++;
    }

	a.printListForward();
    cout << "Size : " << a.size << endl;
    cout << endl;
    a.insertFirst(50);
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    cout << endl;
    a.deleteFirst();
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    cout << endl;

    a.deleteLast();
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    cout << endl;
    a.deleteAtIndex(0);
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    cout << endl;
    a.insertAfterIndex(2, 10);
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    cout << endl;
    a.insertLast(60);
    a.printListForward();
    a.printListBackward();
    cout << "Size : " << a.size << endl;
    a.search(5);
    return 0;
}