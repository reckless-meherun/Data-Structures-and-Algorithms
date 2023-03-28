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
    	if(!head)
    	{
    		return NULL;
    	}
        int count = 0;
        if(head->data == data)
        {
        	cout << "found at index : " << count << endl;
        	return head;
        }
        count++;
        for (node *curr = head->next; curr != NULL; curr = curr->next)
        {
        	if(curr == head)
            	break;
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
        node *temp = new node(data, NULL);
        temp->next = head;
        head = temp;
        tail->next = head;
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
        {
            tail = temp;
            tail->next = head;
        }
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
        tail->next = head;
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
        if (curr->next == head)
        {
            curr = NULL;
            head = NULL;
            tail = NULL; // unless u don't make head and tail NULL, they still are refering to a valid node
            size--;
            return;
        }
        for (; curr->next->next != head; curr = curr->next)
        {
        }
        node* to_delete = curr->next;
        curr->next = head;
        tail = curr;
        tail->next = head;
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
        if (curr->next->next == head) // if the indexing is at the last node
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
            cout<<head->data<<" ";
            for (node *curr = head->next; curr != NULL; )
            {
                cout << curr->data << " ";
                curr = curr->next;
                if(curr ==  head->next)
                    break;
            }
            cout << endl;
        }
    }
};

int main()
{
   
    linkedlist a;
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
            a.tail->next = a.head;
        }
        else
        {
            a.tail->next = new node(x, NULL);
            a.tail = a.tail->next;
            a.tail->next = a.head;
        }
        a.size++; // remember to update this!!!
    }

    a.printList();
	a.insertAfterIndex(1, 34); // done
	a.printList();
    a.insertFirst(10);         // done
	a.printList();
    a.insertLast(9);           // done
    a.printList();
    a.deleteFirst(); // done
	a.printList();
	a.deleteAtIndex(0); //    done
	a.printList();
	a.deleteAtIndex(a.size - 1);
	a.printList();
	a.deleteLast();  //done
	a.printList();
    
    a.search(2);
    a.search(5);
    a.search(34);
    a.search(6);
    
    a.head = a.reverseList();
    a.printList();
    return 0;
}