#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class minHeap
{
public:
    int *heap; // the array
    int capacity;
    int size;

    minHeap()
    {
        capacity = 1000000;
        size = 0;
        heap = new int[capacity];
    }
    minHeap(int _capacity)
    {
        capacity = _capacity;
        size = 0;
        heap = new int[capacity];
    }

    int parent(int indx)
    {
        return (indx - 1) / 2;
    }

    int leftChild(int indx)
    {
        return (2 * indx + 1);
    }

    int rightChild(int indx)
    {
        return (2 * indx + 2);
    }

    int getMinimum()
    {
        if(size>0)
            return heap[0];
        cout<<"Empty heap and returned -1 "<<endl;
        return -1;
    }

    void upHeapify(int indx)
    {
        // heapify from the leaves to root
        while (indx != 0 and heap[parent(indx)] > heap[indx])
        {
            swap(heap[indx], heap[parent(indx)]);
            indx = parent(indx);
        }
    }

    void downHeapify(int indx) // from ith index to leaves
    {
        int leftChildIndex = leftChild(indx);
        int rightChildIndex = rightChild(indx);
        int smallest = indx;

        if (leftChildIndex < size and heap[leftChildIndex] < heap[smallest])
            smallest = leftChildIndex;

        if (rightChildIndex < size and heap[rightChildIndex] < heap[smallest])
            smallest = rightChildIndex;

        if (smallest != indx)
        {
            swap(heap[smallest], heap[indx]);
            downHeapify(smallest);
        }
    }

    void insert(int data)
    {
        if (size == capacity)
        {
            cout << "heap overflow" << endl;
            return;
        }

        size++;
        heap[size - 1] = data;
        int indx = size - 1;

        upHeapify(indx);
    }

    void decreaseData(int indx, int new_data) // cannot replace with a larger data
    {
        heap[indx] = new_data;
        upHeapify(indx);
    }

    int extractMin()
    {
        if (size <= 0)
        {
            return INT_MAX;
        }
        if (size == 1)
        {
            size--;
            return heap[0];
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        downHeapify(0);

        return root;
    }

    void deleteDataAtIndex(int indx)
    {
        if (indx >= size)
        {
            cout << "wrong index" << endl;
            return;
        }
        decreaseData(indx, INT_MIN);
        extractMin();
    }

    void printHeap()
    {
        if (size == 0)
        {
            cout << "empty heap" << endl;
            return;
        }
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

void heapSort(int arr[], int n)
{
    minHeap mxhp(n);
    for (int i = 0; i <n; i++)
    {
        mxhp.insert(arr[i]);
    }
    for (int i = 0; i <n; i++)
    {
        arr[i] = mxhp.extractMin();
    }
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    // minHeap heap(20);
    // for (int i = 10; i >= 0; i--)
    // {
    //     heap.insert(i);
    // }
    // heap.printHeap();
    // heap.insert(3);
    // heap.insert(15);
    // heap.insert(45);
    // heap.printHeap();
    // cout << heap.extractMin() << " ";
    // cout << heap.getMinimum() << " ";
    // heap.decreaseData(2, 1);
    // cout << heap.getMinimum();

    int arr[100];
    for(int i=0; i<6; i++)
    {
    	cin>>arr[i];
    }
    heapSort(arr, 6);
    for(int i=0; i<6; i++)
    {
    	cout<<arr[i]<<" ";
    }
    return 0;
}