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

class linkedlist
{
public:
    node *head;
    linkedlist()
    {
        head = NULL;
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
        // delete(curr->next);
        curr->next = curr->next->next;
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

    void printList(node *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty LinkedList" << endl;
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
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    linkedlist a;
    int n;
    cin>>n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        if (i == 0)
            a.head = new node(x, NULL);
        else
            a.head = new node(x, a.head);
    }
    //a.insertAfterNode(a.head, 3);
    /* can be used to insert last too,
    but you have to provide the pointer of the last element :3
    so u'd better create an insertLast() */
    // a.head = new node(5, a.head);
    // a.insertFirst(0);
    // a.insertLast(9);
    // a.printList(a.head);
    // a.deleteLast();
    // a.printList(a.head);
    // a.deleteFirst();
    // a.printList(a.head);
    // a.deleteAfterNode(2);
    // a.printList(a.head);
    // node *rev_head = a.reverseList();
    // a.printList(rev_head);
    a.printList(a.head);
    return 0;
}