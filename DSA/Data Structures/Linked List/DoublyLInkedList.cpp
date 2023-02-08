#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class doubNode
{
public:
    doubNode *prev;
    int data;
    doubNode *next;

    doubNode()
    {
        prev = NULL;
        data = 0;
        next = NULL;
    }
    doubNode(doubNode *_prev, int _data, doubNode *_next)
    {
        prev = _prev;
        data = _data;
        next = _next;
    }
};
doubNode *first_doubNode = NULL;
class Doublinkedlist
{
public:
    doubNode *head;
    Doublinkedlist()
    {
        head = NULL;
    }

    void insertFirst(int data)
    {
        doubNode *temp = new doubNode(NULL, data, NULL);
        temp->next = head;
        head->prev = temp;
        head = temp;
    }

    void insertAfterdoubNode(int indx, int data) // gonna insert 'data' after doubNode 'curr'
    {
        doubNode *curr = head;
        int count = 1;
        while (count <= indx)
        {
            count++;
            curr = curr->next;
        }
        doubNode *temp = new doubNode(NULL, data, NULL);
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
            doubNode *curr = head;
            int count = 0;
            while (curr->next != NULL)
            {
                curr = curr->next;
                count++;
            }
            cout << count << endl;
            // insertAfterdoubNode(count-1, data);
            doubNode *temp = new doubNode(NULL, data, NULL);
            curr->next = temp;
            temp->prev = curr;
            temp->next = NULL;    
            first_doubNode = temp;       
        }
    }

    void deleteFirst()
    {
        doubNode *top = head;
        head = top->next;
        head->prev=NULL;
        delete (top);
    }

    void deleteAfterNode(int del) // delete the del_th element from the linkedlist
    {
        doubNode *curr = head;
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
        doubNode *curr;
        for (curr = head; curr->next->next != NULL; curr = curr->next)
        {

        }
        curr->next = NULL;
        first_doubNode = curr;
        delete (curr->next);
    }

    void printListForward(doubNode *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty DoubLinkedList" << endl;
        }
        else
        {
            for (doubNode *curr = HEAD; curr != NULL; curr = curr->next)
            {
                cout << curr->data << " ";
            }
            cout << endl;
        }
    }
    void printListBackward(doubNode *HEAD)
    {
        if (!HEAD)
        {
            cout << "Empty DoubLinkedList" << endl;
        }
        else
        {
            for (doubNode *curr = HEAD; curr != NULL; curr = curr->prev)
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
            a.head = new doubNode(NULL, x, NULL);
            first_doubNode = a.head;
        }
        else
        {
            doubNode *temp = a.head;
            a.head = new doubNode(NULL, x, a.head);
            temp->prev = a.head;
        }
    }
    doubNode *curr = a.head;

    a.insertAfterdoubNode(3, 10); //insert after 3rd index
    a.insertFirst(90);
    a.insertLast(100);
    a.deleteFirst();
    a.deleteLast();
    a.deleteAfterNode(2);
    a.printListForward(a.head);
    a.printListBackward(first_doubNode);
    return 0;
}