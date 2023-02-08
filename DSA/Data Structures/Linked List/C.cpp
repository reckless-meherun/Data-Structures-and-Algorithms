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
    void insertFirst(int data)
    {
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
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
    node* removeDuplicates()
    {  
        if(!head) //no element
            return head;
        else if(head->next==NULL) //one element
        {
            return head;
        }
        else if(head->next->next==NULL) //two elements
        {
            if(head->data==head->next->data)
            {
                return NULL;
            }
            else
                return head;
        }

        //more than two elements
        insertFirst(-1);
        node *curr = head;
        int count=0;
        while(curr->next->next!=NULL)
        {
            if(curr->next->data == curr->next->next->data)
            {
                int keep = curr->next->data;
                while(curr->next->data==keep)
                {
                    deleteAfterNode(count);
                }                                
            }
            else
            {
                curr = curr->next;
                count++;
            }
        }
        return head->next;
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
    cin >> n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        if (i == 0)
        {
            a.head = new node(x, NULL);
        }
        else
        {
            a.head = new node(x, a.head);
        }
    }
    a.head = a.reverseList();
    a.head = a.removeDuplicates();
    a.printList(a.head);
    return 0;
}