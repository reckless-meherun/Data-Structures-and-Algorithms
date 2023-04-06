#include<bits/stdc++.h>
using namespace std;

class node
{
public:
    double data;
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

    node *search(double data)
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

    void insertFirst(double data)
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

    void insertAfterIndex(int ins, double data) // gonna insert 'data' after node 'curr'
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

    void insertLast(double data)
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
    // void sortList()
    // {
    //     node *temp = head;

    //     // Traverse the List
    //     while (temp)
    //     {
    //         node *min = temp;
    //         node *r = temp->next;

    //         // Traverse the unsorted sublist
    //         while (r)
    //         {
    //             if (min->data > r->data)
    //                 min = r;

    //             r = r->next;
    //         }

    //         // Swap Data
    //         int x = temp->data;
    //         temp->data = min->data;
    //         min->data = x;
    //         temp = temp->next;
    //     }
    // }

    int search_index(int indx)
    {
        if(indx>=size)
        {
            cout<<"invalid"<<endl;
            return -1;
        }
        if(!head)
        {
            cout<<"empty, returned -1"<<endl;
            return -1;
        }
        node *curr = head;
        int i=0;
        while(i!=indx)
        {
            i++;
            curr = curr->next;
        }
        return curr->data;
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

    int find_max()
    {
        if(indx>=size)
        {
            cout<<"invalid"<<endl;
            return -1;
        }
        if(!head)
        {
            cout<<"empty, returned -1"<<endl;
            return -1;
        }
        node *curr = head;
        int Max = INT_MIN;
        int i=0;
        while(i!=indx)
        {
            if(curr->data > Max)
            {
                Max = curr->data;
            }
            i++;
            curr = curr->next;
        }
        return Max;
    }

    int find_min()
    {
        if(indx>=size)
        {
            cout<<"invalid"<<endl;
            return -1;
        }
        if(!head)
        {
            cout<<"empty, returned -1"<<endl;
            return -1;
        }
        node *curr = head;
        int Min = INT_MAX;
        int i=0;
        while(i!=indx)
        {
            if(curr->data < Min)
            {
                Min = curr->data;
            }
            i++;
            curr = curr->next;
        }
        return Min;
    }
};

void bucketSortLL(linkedlist &l)
{
    l.sortList();
    // vector<double> b[n];

    // for (int i = 0; i < 15; i++)
    // {
    //     int bi = 15 * arr[i]; 
    //     b[bi].push_back(arr[i]);
    // }

    // for (int i = 0; i < n; i++)
    //     InsertionSort(b[i], b[i].size());
    
    // int index = 0;
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < b[i].size(); j++)
    //         arr[index++] = b[i][j];
}

void selectionSort(linkedlist &l)
{
    for (node *curr1 = l.head; curr1->next!=NULL ; curr1 = curr1->next)
    {
        for (node *curr2 = curr2->next; curr2!=NULL ; curr2 = curr2->next)
        {
            if(curr1->data > curr2->data)
            {
                swap(curr1->data, curr2->data);
            }
        }    
    }   
}

void InsertionSort(vector<double> &v, int len)
{
    for (int outer = 1; outer < v.size(); outer++)
    {
        double toPlace = v[outer];
        int inner = outer - 1;
        while (inner >= 0 and (v[inner] - toPlace)>0.00001) // cannot write v[inner]>v[outer] as v[outer] gets changed after one shift in the inner loop
        {
            v[inner + 1] = v[inner];
            inner--;
        }
        v[inner + 1] = toPlace;
    }
}

void bucketSortLL(linkedlist &arr)
{
    double Max = arr.find_max();
    double Min = arr.find_min();
  
    // range (for buckets)
    double range = (Max - Min) / 15;
  
    vector<vector<double> > temp;
  
  // create empty buckets
  for (int i = 0; i < 15; i++) {
    temp.push_back(vector<double>());
  }
  
  // scatter the array elements into the correct bucket
  for (int i = 0; i < arr.size(); i++) {
    double diff = (arr.search_index(i) - Min) / range
      - int((arr.search_index(i) - Min) / range);
  
    // append the boundary elements to the lower array
    if (diff == 0 && arr.search_index(i) != Min) {
      temp[int((arr.search_index(i) - Min) / range) - 1]
        .push_back(arr.search_index(i));
    }
    else {
      temp[int((arr.search_index(i) - Min) / range)].push_back(
        arr.search_index(i));
    }
  }
  
  // Sort each bucket individually
  for (int i = 0; i < temp.size(); i++) {
    if (!temp[i].empty()) {
      sort(temp[i].begin(), temp[i].end());
    }
  }
  
  // Gather sorted elements to the original array
  int k = 0;
  for (vector<double>& lst : temp) {
    if (!lst.empty()) {
      for (double i : lst) {
        arr.search_index(k) = i;
        k++;
      }
    }
  }
}

// void BucketSortLL(linkedlist &l)
// {
//    // l.printList();
//     vector<int> b[15];
//     for (int i = 0; i < 15; i++)
//     {
//         cout<<l.search_index(i)<<endl;
//         int bi = 15*l.search_index(i);
//         b[bi].push_back(l.search_index(i));
//     }    

//     for (int i = 0; i < 5; i++)
//     {
//         sort(b[i].begin(), b[i].end());
//     }

//     int indx=0;

//     node *curr=l.head;

//     for(int i=0; i<5; i++)
//     {
//         for(int j=0; i<b[i].size(); i++)
//         {
//             //v[indx++]=b[i][j];
//             curr->data = b[i][j];
//             curr = curr->next;
//         }   
//     }        
// }

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    double arr[10000];
    
    linkedlist a;
    for (int i = 0; i < 15; i++)
    {
        double x = rand()/100000.0;

        if(i==0)
        {
            a.head = new node(x, NULL);
            a.tail = a.head;
            a.tail->next = NULL;
        }
        else 
        {
            a.tail->next = new node(x, NULL);
            a.tail = a.tail->next;
        }
        a.size++;
    }

   // a.printList();  
    bucketSortLL(a);  
    cout<<endl; 
    a.printList();
}
