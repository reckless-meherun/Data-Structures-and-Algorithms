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
    int size;
    linkedlist()
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
        if (!head)
        {
            head = new node(data, NULL);
            tail = head;
            size++;
            return;
        }
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
        tail = temp;
        size++;
    }

    void insertAfterIndex(int ins, int data) // gonna insert 'data' after node 'curr'
    {
        if (ins >= size)
        {
            cout << "Wrong Index to insert after" << endl;
            return;
        }
        node *curr = head;
        int Index = 0;
        while (Index != ins)
        {
            Index++;
            curr = curr->next;
        }
        node *temp = new node(data, NULL);
        temp->next = curr->next;
        curr->next = temp;
        // be careful about the order so the link doesn't get lost
        if (ins == size - 1)
            tail = temp;
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
        free(top);
        size--;
    }

    void deleteLast() // this cannot be done in O(1) as it is a singly linked list
    {
        if (!head)
            return;
        node *curr = head;
        if (!curr->next)
        {
            curr = NULL;
            head = NULL;
            tail = NULL; // unless u don't make head and tail NULL, they still are refering to a valid node
            size--;
            return;
        }
        for (; curr->next->next != NULL; curr = curr->next)
        {
        }
        node *to_delete = curr->next = NULL;
        tail = curr;
        size--;
        free(to_delete);
    }

    void deleteAtIndex(int del) // delete the del_th element from the linkedlist
    {
        if (del >= size)
        {
            cout << "Wrong Index to delete" << endl;
            return;
        }
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
        node *to_delete = curr->next;
        curr->next = curr->next->next;
        free(to_delete);
        size--;
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

    void printList()
    {
        if (!head)
        {
            cout << "Empty LinkedList" << endl;
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
    void sortList()
    {
        node *temp = head;

        // Traverse the List
        while (temp)
        {
            node *min = temp;
            node *r = temp->next;

            // Traverse the unsorted sublist
            while (r)
            {
                if (min->data > r->data)
                    min = r;

                r = r->next;
            }

            // Swap Data
            int x = temp->data;
            temp->data = min->data;
            min->data = x;
            temp = temp->next;
        }
    }
    void selectionSort()
    {
        node *curr1 = head;
        for (; curr1->next!=NULL; curr1 = curr1->next)
        {
            for (node *curr2 = curr1->next; curr2!=NULL; curr2 = curr2->next)
            {
                if(curr1->data > curr2->data)
                {
                    swap(curr1->data, curr2->data);
                }
            }            
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
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (i == 0)
        {
            a.head = a.tail = new node(x, NULL);
            // a.insertFirst(x);
        }
        else
        {
            a.tail->next = new node(x, NULL);
            a.tail = a.tail->next;
            //  a.insertLast(x);
        }

        a.size++; // remember to update this!!!
    }

    a.printList();
    // a.insertAfterIndex(1, 34); // done
    // a.insertFirst(10);         // done
    // a.insertLast(9);           // done
    // a.insertAfterIndex(1, 34); // done
    // a.insertFirst(10);         // done
    // a.insertLast(9);           // done
    // a.printList();
    // a.deleteLast();  // done
    // a.deleteFirst(); // done
    // a.printList();
    // a.deleteAtIndex(0); //    done
    // a.deleteAtIndex(a.size - 1);
    // a.printList();
    // a.head = a.reverseList();
    // a.printList();
    // a.insertFirst(5);
    // // a.insertFirst(6);
    // a.insertLast(7);
    // a.insertLast(8);
    // a.insertLast(9);
    // // a.insertFirst(8);
    // a.printList();
    a.sortList();
    a.printList();
    return 0;
}