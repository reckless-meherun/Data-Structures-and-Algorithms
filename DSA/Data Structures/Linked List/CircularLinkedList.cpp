#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class circulnode
{
public:
    int data;
    circulnode *next;
    circulnode()
    {
        data = 0;
        next = NULL;
    }
    circulnode(int _data, circulnode *_next)
    {
        data = _data;
        next = _next;
    }
};

class circulinkedlist
{
public:
    circulnode *head;
    circulinkedlist()
    {
        head = NULL;
    }
    void printList(circulnode *HEAD, circulnode *first_circulnode)
    {
        if (!HEAD)
        {
            cout << "Empty LinkedList" << endl;
            return;
        }
        else
        {
            circulnode *curr = HEAD;
            cout<<curr->data<<" ";
            curr = curr->next;   

            while (curr!=HEAD)
            {
                cout<<curr->data<<" ";
                curr = curr->next;  
            }                
        }
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    circulinkedlist a;
    circulnode *first_circulnode = NULL;
    int n;
    cin >> n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        if (i == 0)
        {
            a.head = new circulnode(x, NULL);
            a.head->next = a.head;
            first_circulnode = a.head;
        }
        else
            a.head = new circulnode(x, first_circulnode);
    }
    a.printList(a.head, first_circulnode);
    return 0;
}