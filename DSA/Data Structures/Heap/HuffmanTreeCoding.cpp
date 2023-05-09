#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    char data;
    int freq;
    node *left, *right;

    node(char data, int freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
    bool isLeaf()
    {
        return left == NULL and right == NULL;
    }
};

class minHeap
{
public:
    node **heap; // the array
    int capacity;
    int size;

    minHeap()
    {
        capacity = 100000;
        this->size = 0;
        heap = new node *[capacity];
    }

    minHeap(char data[], int freq[], int size)
    {
        capacity = size;
        this->size = 0;
        heap = new node *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            insert(data[i], freq[i]);
            //insertNode(new node(data[i], freq[i]));
        }
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

    node *getMinimum()
    {
        if (size > 0)
            return heap[0];
        cout << "Empty heap and returned -1 " << endl;
        return NULL;
    }

    int upHeapify(int indx)
    {
        // heapify from the leaves to root
        while (indx != 0 and heap[parent(indx)]->freq > heap[indx]->freq)
        {
            swap(heap[indx], heap[parent(indx)]);
            indx = parent(indx);
        }
        return indx;
    }

    void downHeapify(int indx) // from ith index to leaves
    {
        int leftChildIndex = leftChild(indx);
        int rightChildIndex = rightChild(indx);
        int smallest = indx;

        if (leftChildIndex < size and heap[leftChildIndex]->freq < heap[smallest]->freq)
            smallest = leftChildIndex;

        if (rightChildIndex < size and heap[rightChildIndex]->freq < heap[smallest]->freq)
            smallest = rightChildIndex;

        if (smallest != indx)
        {
            swap(heap[smallest], heap[indx]);
            downHeapify(smallest);
        }
    }

    void insertNode(node *curr)
    {
        if (size == capacity)
        {
            cout << "heap overflow" << endl;
            return;
        }
        size++;
        heap[size - 1] = new node(curr->data, curr->freq);
        int indx = size - 1;

        while (indx and curr->freq < heap[(indx - 1) / 2]->freq)
        {
            heap[indx] = heap[(indx - 1) / 2];
            indx = (indx - 1) / 2;
        }
        heap[indx] = curr;
    }

    void insert(char data, int freq)
    {
        if (size == capacity)
        {
            cout << "heap overflow" << endl;
            return;
        }

        size++;
        heap[size - 1] = new node(data, freq);
        int indx = size - 1;

        upHeapify(indx);
    }

    // void decreaseData(int indx, int new_data) // cannot replace with a larger data
    // {
    //     heap[indx] = new_data;
    //     upHeapify(indx);
    // }

    node *extractMin()
    {
        if (size <= 0)
        {
            cout << "No heap built" << endl;
            return NULL;
        }
        if (size == 1)
        {
            size--;
            return heap[0];
        }

        node *root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        downHeapify(0);
        return root;
    }

    // void deleteDataAtIndex(int indx)
    // {
    //     if (indx >= size)
    //     {
    //         cout << "wrong index" << endl;
    //         return;
    //     }
    //     decreaseData(indx, INT_MIN);
    //     extractMin();
    // }

    void printHeap()
    {
        if (size == 0)
        {
            cout << "empty heap" << endl;
            return;
        }
        for (int i = 0; i < size; i++)
            cout << heap[i]->data << " " << heap[i]->freq << endl;
    }
};

class huffmanTree
{
public:
    minHeap huffman;
    node *rootNode, *leftNode, *rightNode;
    int rootIndx, leftChildIndx, rightChildIndx;
    huffmanTree(char data[], int freq[], int size)
    {
        huffman = minHeap(data, freq, size);

        while (huffman.size != 1)
        {
            leftNode = huffman.extractMin();
            rightNode = huffman.extractMin();
            // cout<<leftNode->data<<" "<<leftNode->freq<<endl;
            // cout<<rightNode->data<<" "<<rightNode->freq<<endl;
            rootNode = new node('$', leftNode->freq + rightNode->freq);

            rootNode->left = leftNode;
            rootNode->right = rightNode;

            huffman.insertNode(rootNode);
        }
    }

    node *getRoot()
    {
        return huffman.extractMin();
    }

    void printCode(node *root, int charCodeArray[], int codeIndx)
    {
        cout << root->data << " " << root->freq << endl;
        if (root->left)
        {
            charCodeArray[codeIndx] = 0;
            printCode(root->left, charCodeArray, codeIndx + 1);
        }
        if (root->right)
        {
            charCodeArray[codeIndx] = 1;
            printCode(root->right, charCodeArray, codeIndx + 1);
        }

        /** when the node contains character that we want to encode */
        if (root->isLeaf())
        {
            cout << root->data << " in huffman code : ";
            /** print the whole array for the whole branch of the tree visited */
            for (int i = 0; i < codeIndx; i++)
            {
                cout << charCodeArray[i] << ",";
            }
            cout << '\n';
        }
    }
};

void showHuffmanCode(char data[], int freq[], int size)
{
    huffmanTree hfmt(data, freq, size);
    int charCodeArray[100000];
    hfmt.printCode(hfmt.getRoot(), charCodeArray, 0);
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {15, 3, 12, 3, 16, 4};

    minHeap mh(arr, freq, sizeof(arr) / sizeof(arr[0]));
    mh.printHeap();
    //showHuffmanCode(arr, freq, sizeof(arr) / sizeof(arr[0]));
    return 0;
}