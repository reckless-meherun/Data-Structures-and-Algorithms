#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int data;
    node *left, *right, *parent;
    node()
    {
        data = 0;
        left = right = parent = NULL;
    }
    node(int _data)
    {
        data = _data;
        left = right = parent = NULL;
    }
};

class minHeap
{
public:
    node *root;
    int size;
    minHeap()
    {
        root = NULL;
        size = 0;
    }

    node *lastParentNode()
    {
        node *curr = root;
        queue<node *> q;

        q.push(root);
        node *ans = root;
        while (!q.empty())
        {
            ans = q.front();
            q.pop();
            if (!ans->left or !ans->right)
            {
                return ans;
            }
            else
            {
                q.push(ans->left);
                q.push(ans->right);
            }
        }
        return ans;
    }

    node *lastNode()
    {
        node *curr = root;
        queue<node *> q;

        q.push(root);
        node *ans = root;
        while (!q.empty())
        {
            ans = q.front();
            q.pop();
            if (ans->left)
                q.push(ans->left);
            if (ans->right)
                q.push(ans->right);
        }
        return ans;
    }

    void upHeapify(node *temp)
    {
        while (temp->parent and temp->parent->data > temp->data)
        {
            swap(temp->data, temp->parent->data);
            temp = temp->parent;
        }
    }

    void downHeapify(node *temp)
    {
        if (temp)
        {
            node *smallest = temp;
            if (temp->left and temp->left->data < smallest->data)
                smallest = temp->left;

            if (temp->right and temp->right->data < smallest->data)
                smallest = temp->right;

            if (smallest != temp)
            {
                swap(smallest->data, temp->data);
                downHeapify(smallest);
            }
        }
    }

    void insert(int val)
    {
        node *temp = new node(val);
        if (!root)
        {
            root = temp;
            size++;
            return;
        }

        node *lastParent = lastParentNode();
        if (!lastParent->left)
        {
            lastParent->left = temp;
            lastParent->left->parent = lastParent;
        }
        else
        {
            lastParent->right = temp;
            lastParent->right->parent = lastParent;
        }

        size++;
        upHeapify(temp);
    }

    int getMinimum()
    {
        if(!root)
        {
            cout<<"Empty heap and returned -1 "<<endl;
            return -1;
        }
        return root->data;
    }

    int extractMin()
    {
        if (!root)
        {
            cout << "Empty heap; nothing to extract" << endl;
            return INT_MAX;
        }

        int Min = root->data;

        if (size == 1)
        {
            size--;
            root = NULL;
            delete (root);
            return Min;
        }

        node *last = lastNode();
        swap(root->data, last->data);
        if(last == last->parent->left)
        {
            last->parent->left = NULL; // not "last = NULL" as that doesn't change anything in the heap because last in just another pointer pointing to the last node, the heap doesn't give a fuck if last points to null as it is not direct connected to the tree 
        }
        else
        {
            last->parent->right = NULL;
        }
        downHeapify(root);
        size--;

        return Min;
    }

    void inorderTraverse(node *curr)
    {
        if (curr->left)
        {
            inorderTraverse(curr->left);
        }
        cout << curr->data << " ";
        if (curr->right)
        {
            inorderTraverse(curr->right);
        }
    }

    void printHeap()
    {
        if (!root)
        {
            cout << "Empty Heap" << endl;
            return;
        }
        inorderTraverse(root);
        cout<<endl;
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
    minHeap h;

    for (int i = 0; i < 5; i++)
        h.insert(i);

    h.printHeap();
    h.extractMin();
    h.printHeap();
    h.extractMin();
    h.printHeap();
    h.extractMin();
    h.printHeap();
    h.extractMin();
    h.printHeap();
    h.extractMin();
    h.printHeap();
    return 0;
}