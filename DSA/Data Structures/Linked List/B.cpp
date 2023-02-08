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
    node *head, *tail;
    linkedlist()
    {
        head = NULL;
        tail = NULL;
    }
    void insertFirst(int data)
    {
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
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

node *mergeSortedLists(linkedlist &a, linkedlist &b)
{
    linkedlist merged;
    merged.head = new node(-1, NULL);
    node *curr_a = a.head;
    node *curr_b = b.head;
    while (curr_a != NULL and curr_b != NULL)
    {
        if (curr_a->data < curr_b->data)
        {
            merged.head = new node (curr_a->data, merged.head);
            curr_a = curr_a->next;
        }
        else if(curr_a->data > curr_b->data)
        {
            merged.head = new node (curr_b->data, merged.head);
            curr_b = curr_b->next;
        }
        else
        {
            merged.head = new node (curr_a->data, merged.head);
            merged.head = new node (curr_b->data, merged.head);
            curr_a = curr_a->next;
            curr_b = curr_b->next;
        }
    }
    while (curr_a!=NULL)
    {
        merged.head = new node (curr_a->data, merged.head);
        curr_a = curr_a->next;
    }
    while (curr_b!=NULL)
    {
        merged.head = new node (curr_b->data, merged.head);
        curr_b = curr_b->next;
    }
    merged.head = merged.reverseList();
    return merged.head->next;   
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    int n, m, x;
    cin >> n;
    vector<linkedlist> a(n);
    linkedlist merged;
    merged.head = new node(-100, NULL);
    for (int i = 0; i < n; i++)
    {        
        cin >> m;
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            if (j == 0)
            {
                a[i].head = new node(x, NULL);
            }
            else
            {
                a[i].head = new node(x, a[i].head);
            }
        }
        a[i].head = a[i].reverseList();    
        merged.head = mergeSortedLists(a[i], merged);        
    }
    merged.printList(merged.head->next);
    return 0;
}