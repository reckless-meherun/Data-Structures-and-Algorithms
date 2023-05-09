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
        for (; curr1->next != NULL; curr1 = curr1->next)
        {
            for (node *curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next)
            {
                if (curr1->data > curr2->data)
                {
                    swap(curr1->data, curr2->data);
                }
            }
        }
    }

    int searchAtIndex(int indx)
    {
        if (!head)
        {
            cout << "empty linked list" << endl;
        }
        if (indx >= size)
        {
            cout << "Wrong index!!" << endl;
        }

        node *curr = head;
        int i = 0;
        while (i != indx and curr)
        {
            curr = curr->next;
            i++;
        }
        return curr->data;
    }

    int findMax()
    {
        if (!head)
        {
            cout << "Empty Linked list; returning -1" << endl;
            return -1;
        }
        node *curr = head;
        int maxElm = curr->data;
        while (curr)
        {
            if (curr->data > maxElm)
                maxElm = curr->data;
            curr = curr->next;
        }
        return maxElm;
    }

    int findMin()
    {
        if (!head)
        {
            cout << "Empty Linked list; returning -1" << endl;
            return -1;
        }
        node *curr = head;
        int minElm = curr->data;
        while (curr)
        {
            if (curr->data < minElm)
                minElm = curr->data;
            curr = curr->next;
        }
        return minElm;
    }

    void bucketSort()
    {
        int maxElm = findMax();
        int minElm = findMin();
        int range = (maxElm - minElm) / 15;
        vector<vector<int>> temp;

        for (int i = 0; i < 25; i++)
        {
            temp.push_back(vector<int>());
        }

        for (int i = 0; i < size; i++)
        {
            int elem = searchAtIndex(i);
            int diff = (int)(elem - minElm) / range - (int)(elem - minElm) / range;
            // cout<<"elem "<<elem<<" minElem "<<minElm<<endl;
            // 	cout<<"index "<<(int)((elem - minElm)/range)-1<<endl;
            if (diff == 0 and elem != minElm)
            {
                temp[(int)((elem - minElm) / range) - 1].push_back(elem);
            }
            else
            {
                temp[(int)((elem - minElm) / range)].push_back(elem);
            }
        }

        for (int i = 0; i < temp.size(); i++)
        {
            if (!temp.empty())
            {
                sort(temp[i].begin(), temp[i].end());
            }
        }

        node *curr = head;
        for (vector<int> &a : temp)
        {
            if (!a.empty())
            {
                for (int b : a)
                {
                    curr->data = b;
                    curr = curr->next;
                }
            }
        }
    }

    node *findMid(node *st, node *ed)
    {
        if (!st)
            return NULL;

        node *first = st, *last = st->next;
        while (last != ed)
        {
            last = last->next;
            if (last != ed)
            {
                last = last->next;
                first = first->next;
            }
        }
        return first;
    }

    bool binarySearch(int find)
    {
        node *start = head, *end = tail, *mid;

        while (end != NULL and end != start)
        {
            mid = findMid(start, end);
            if (!mid)
            {
                return false;
            }
            if (mid->data < find)
            {
                start = mid->next;
            }
            else if (mid->data > find)
            {
                end = mid;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};

class MyStack
{
public:
    linkedlist Stack;
    int length, capacity;

    MyStack()
    {
        capacity = 1000000;
        length = 0;
    }

    MyStack(int _capacity)
    {
        capacity = _capacity;
        length = 0;
    }

    bool empty()
    {
        return Stack.head == NULL;
    }

    bool isFull()
    {
        return length == capacity;
    }

    void push(int val)
    {
        if (isFull())
        {
            // cout << "Stack overflow" << endl;
            return;
        }
        if (!Stack.head)
            Stack.insertFirst(val);
        else
            Stack.insertLast(val);
        length++;
    }

    void pop()
    {
        Stack.deleteLast();
        length--;
    }

    int top()
    {
        if (empty())
        {
            cout << "Empty Stack" << endl;
            return ' ';
        }
        else
        {
            Stack.tail = Stack.head;
            while (Stack.tail->next)
            {
                Stack.tail = Stack.tail->next;
            }
            return Stack.tail->data;
        }
    }

    void clear()
    {
        if (!Stack.head)
            return;
        Stack.tail = Stack.head;
        while (Stack.tail)
        {
            Stack.tail->data = 0;
            Stack.tail = Stack.tail->next;
            length--;
        }
    }
    void printStack()
    {
        if (empty())
            cout << "Empty Stack" << endl;
        else
            Stack.printList();
    }
    int size()
    {
        return length;
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    MyStack inputStack(150);
    MyStack tempStack(150);
    linkedlist sLink;
    int diffArray[150 + 1];

    for (int i = 0; i < 150; i++)
    {
        inputStack.push(rand() / 100000000);
        if (i == 0)
        {
            sLink.head = sLink.tail = new node(inputStack.top(), NULL);
            // a.insertFirst(x);
        }
        else
        {
            sLink.tail->next = new node(inputStack.top(), NULL);
            sLink.tail = sLink.tail->next;
            //  a.insertLast(x);
        }
        sLink.size++;
    }

    while (!inputStack.empty())
    {
        int currentElement = inputStack.top();
        inputStack.pop();

        if (tempStack.empty() == true or currentElement >= tempStack.top())
        {
            tempStack.push(currentElement);
        }

        if (currentElement < tempStack.top())
        {
            while (!tempStack.empty() and tempStack.top() >= currentElement)
            {
                inputStack.push(tempStack.top());
                tempStack.pop();
            }
            tempStack.push(currentElement);
        }
    }

    while (!tempStack.empty())
    {
        inputStack.push(tempStack.top());
        tempStack.pop();
    }

    cout << "The unsorted linked list " << endl;
    sLink.printList();
    sLink.bucketSort();
    cout << endl
         << "The sorted linked list using bucket sort " << endl;
    sLink.printList();
    int i = 0;
    cout << endl
         << "input stack after sorting : " << endl;
    while (!inputStack.empty() and i < 150)
    {
        cout << inputStack.top() << " ";
        diffArray[i] = inputStack.top() - sLink.searchAtIndex(i);
        // cout<<" the index "<<i<<" ";
        i++;
        inputStack.pop();
    }
    cout << endl;

    cout << endl
         << "The difference array between sorted inputStack and sorted sLink : " << endl;
    for (int i = 0; i < 150; i++)
    {
        cout << diffArray[i] << " ";
        // if(diffArray[i]!=0)
        // {
        // 	cout<<" the different index : "<<i<<endl;
        // }
    }
    cout << endl;
    return 0;
}