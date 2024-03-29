#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int data, degree;
    node *parent, *leftChild, *rightSibling;

    node(int data)
    {
        this->data = data;
        degree = 0;
        parent = leftChild = rightSibling = NULL;
    }
};

class binomialHeap
{
private:
    node *mergeRootList(node *root_1, node *root_2)
    {
        node *root_0 = new node(0);
        node *temp = root_0; // adding an extra root in front of the whole rootlist

        while (root_1 != NULL and root_2 != NULL)
        {
            if (root_1->degree <= root_2->degree)
            {
                temp->rightSibling = root_1;
                temp = temp->rightSibling;
                root_1 = root_1->rightSibling;
            }
            else
            {
                temp->rightSibling = root_2;
                temp = temp->rightSibling;
                root_2 = root_2->rightSibling;
            }
        }

        while (root_1 != NULL)
        {
            temp->rightSibling = root_1;
            temp = temp->rightSibling;
            root_1 = root_1->rightSibling;
        }

        while (root_2 != NULL)
        {
            temp->rightSibling = root_2;
            temp = temp->rightSibling;
            root_2 = root_2->rightSibling;
        }

        return root_0->rightSibling;
    }

    node *minimumNode()
    {
        node *curr = root, *minNode = root;

        while (curr != NULL)
        {
            if (curr->data < minNode->data)
                minNode = curr;
            curr = curr->rightSibling;
        }
        return minNode;
    }

    node *reverse(node *root)
    {
        node *prev = NULL, *curr = root, *next = NULL;
        while (curr)
        {
            next = curr->rightSibling; /** save the right sibling to next before changing it*/
            curr->rightSibling = prev; /** changing right sibling of curr*/
            prev = curr;               /** save the curr to prev before changing it*/
            curr = next;               /** changing curr*/
        }
        return prev;
    }

public:
    node *root;
    binomialHeap()
    {
        root = NULL;
    }
    void merge(node *other)
    {
        node *root1 = root, *root2 = other;
        node *mergedRoot = mergeRootList(root1, root2);
        root = mergedRoot;

        if (root == NULL)
            return;

        node *curr1 = root, *curr2 = root->rightSibling;
        node *prev = NULL;

        // next = curr2
        // curr = cur1
        while (curr2 != NULL)
        {
            if (curr1->degree != curr2->degree or (curr2->rightSibling != NULL and curr2->rightSibling->degree == curr1->degree))
            {
                prev = curr1;
                curr1 = curr2;
            }
            else if (curr1->data <= curr2->data)
            {
                curr1->rightSibling = curr2->rightSibling;
                curr2->parent = curr1;
                curr2->rightSibling = curr1->leftChild;
                curr1->leftChild = curr2;
                curr1->degree++;
            }
            else
            {
                if (prev == NULL)
                {
                    mergedRoot = curr2;
                }
                else
                {
                    prev->rightSibling = curr2;
                }
                curr1->parent = curr2;
                curr1->rightSibling = curr2->leftChild;
                curr2->leftChild = curr1;
                curr2->degree++;
                curr1 = curr2;
            }
            curr2 = curr1->rightSibling;
        }
        root = mergedRoot;
    }

    int minimumData()
    {
        return minimumNode()->data;
    }

    void insert(int data)
    {
        binomialHeap bh;
        bh.root = new node(data);
        merge(bh.root);
    }

    void decreaseData(node *curr, int newData)
    {
        if (newData == curr->data)
            return;

        curr->data = newData;
        while (curr->parent and curr->parent->data > curr->data)
        {
            swap(curr->data, curr->parent->data);
            curr = curr->parent;
        }
    }

    int extractMin()
    {
        node *minNode = minimumNode();
        int minData = minNode->data;
        node *temp = minNode->leftChild;
        delete minNode;

        node *newRoot = temp;
        newRoot = reverse(newRoot);
        binomialHeap bh;
        bh.root = newRoot;
        merge(bh.root);

        return minData;
    }

    void deleteNode(node *curr)
    {
        decreaseData(curr, INT_MIN);
        extractMin();
    }

    void printRootlist()
    {
        node *curr = root;
        while (curr)
        {
            cout << curr->data << " ";
            curr = curr->rightSibling;
        }
        cout << endl;
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    binomialHeap bh;
    bh.insert(7);
    bh.insert(25);

    binomialHeap bh2;
    bh2.insert(12);
    bh2.insert(30);

    binomialHeap bh3;
    bh2.insert(1);
    bh2.insert(5);

    bh2.merge(bh.root);
    cout<<bh2.minimumData()<<endl;

    cout<<bh2.root->degree<<endl;
    bh2.merge(bh3.root);
    cout<<bh2.minimumData()<<endl;
    bh2.printRootlist();    

    return 0;
}