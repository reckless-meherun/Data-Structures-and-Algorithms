#include<bits/stdc++.h>
using namespace std;

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

    void insertFirst(int data)
    {
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
    }

    void insertAfterNode(node *curr, int data) // gonna insert 'data' after node 'curr'
    {
        node *temp = new node(data, NULL);
        temp->next = curr->next;
        curr->next = temp; // be careful about the order so the link doesn't get lost
    }

    void insertLast(int data)
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
        delete(to_delete);
    }

    void remove(int val)
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

    node* reverseList()
    {
        node *prev_head = head;
        node *temp1 = NULL, *temp2 = NULL;
        while(prev_head!=NULL)
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
            cout << "Empty Queue" << endl;
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

class MyQueue
{
public:
    linkedlist queue;
    bool empty()
    {
        return queue.head == NULL;
    }
    void push(int data)
    {
        if(!queue.head)
            queue.insertFirst(data);
        else
            queue.insertLast(data);
    }
    void pop()
    {
        queue.deleteFirst();
    }
    int front()
    {
        return queue.head->data;
    }
    int size()
    {
        int count=0;
        node *curr = queue.head;
        for (; curr!=NULL ; curr = curr->next)
        {
            count++;
        }
        return count;
    }
    void printQueue()
    {
        queue.printList();
    }
    void clear()
    {
        node *curr = queue.head;
        while(curr)
        {
            curr->data = 0;
            curr = curr->next;
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    MyQueue q;
    for(int i=0; i<5; i++)
        q.push(i);
    q.printQueue();
    q.pop();
    q.printQueue();
    while (!q.empty())
    {
        q.pop();
    }
    q.printQueue();
    return 0;
}