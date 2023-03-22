#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int val;
    node *left, *right, *parent;
    node()
    {
        val = 0;
        left = right = parent = NULL;
    }
    node(int _val)
    {
        val = _val;
        left = right = parent = NULL;
    }
};

class bst
{
public:
    node *root;
    bst()
    {
        root = NULL;
    }

    void insert(int val)
    {
        node *curr = root;
        if (!root)
        {
            root = new node(val);
            return;
        }
        insert_rec(root, val);
    }

    // both the insert_rec functions (commented out and commented in) works perfectly fine

    void insert_rec(node *curr, int val)
    {
        if (val < curr->val)
        {
            if (!curr->left)
            {
                curr->left = new node(val);
                curr->left->parent = curr;
                return;
            }
            insert_rec(curr->left, val);
        }
        else
        {
            if (!curr->right)
            {
                curr->right = new node(val);
                curr->right->parent = curr;
                return;
            }
            insert_rec(curr->right, val);
        }
    }

    // void insert_rec(node *&curr, int val) // here is the crucial point, u have to use
    // // *&curr (not *curr) otherwise it won't link up in this function
    // // because a copy of the node is being passed here
    // {
    //     if (!curr)
    //     {
    //         curr = new node(val);
    //         return;
    //     }
    //     if (val < curr->val)
    //         insert_rec(curr->left, val);
    //     else
    //         insert_rec(curr->right, val);
    // }

    node *search(int val)
    {
        node *curr = root;
        if (!root)
        {
            cout << "Empty BST" << endl;
            return NULL;
        }

        while (1)
        {
            if (val < curr->val)
            {
                if (!curr->left)
                {
                    cout << "Not found " << endl;
                    return NULL;
                }
                curr = curr->left;
            }
            else if (val > curr->val)
            {
                if (!curr->right)
                {
                    cout << "Not found " << endl;
                    return NULL;
                }
                curr = curr->right;
            }
            else
            {
                if (curr == NULL)
                    cout << "it is null in search function too" << endl;
                cout << "Found " << endl;
                return curr;
            }
        }
    }

    node *findMin(node *curr)
    {
        if (!curr)
        {
            return NULL;
        }
        while (curr->left)
        {
            curr = curr->left;
        }
        return curr;
    }

    node *findMax(node *curr)
    {
        if (!curr)
        {
            return NULL;
        }
        while (curr->right)
        {
            curr = curr->right;
        }
        return curr;
    }

    bool isLeaf(node *curr)
    {
        return curr->left == NULL and curr->right == NULL;
    }

    bool isRoot(node *curr)
    {
        return !curr->parent;
    }

    bool hasOneNode(node *curr)
    {
        return !curr->left or !curr->right;
    }

    void deleteNode(int val)
    {
        node *to_delete = search(val);

        // if (isLeaf(to_delete)) // if the node is a leaf
        // {
        //     cout << "it's a leaf" << endl;
        //     to_delete = NULL;
        //     if (!to_delete)
        //         cout << "made null in delete function" << endl;
        //     return;
        // }

        if (hasOneNode(to_delete)) // has only one node
        {
            if (to_delete->left)
            {
                if (isRoot(to_delete)) // if the node is the root
                {
                    root = root->left;
                    free(root);
                    return;
                }
                if (to_delete->parent->left == to_delete)
                    to_delete->parent->left = to_delete->left;
                else if (to_delete->parent->right == to_delete)
                    to_delete->parent->right = to_delete->left;
            }
            else
            {
                if (isRoot(to_delete))
                {
                    root = root->right;
                    free(root);
                    return;
                }
                if (to_delete->parent->left == to_delete)
                    to_delete->parent->left = to_delete->right;
                else if (to_delete->parent->right == to_delete)
                    to_delete->parent->right = to_delete->right;
            }
            free(to_delete);
        }

        else // has both nodes
        {
            node *to_swap = findMin(to_delete->right); // find inorder successor
            to_delete->val = to_swap->val;
            if (!isLeaf(to_swap))
            {
                to_swap->parent->left = to_swap->right;
            }
            free(to_swap);
        }
    }

    void preorderTraverse(node *curr)
    {
        cout << curr->val << " ";
        if (curr->left)
            preorderTraverse(curr->left);
        if (curr->right)
            preorderTraverse(curr->right);
        return;
    }

    void inorderTraverse(node *curr)
    {
        if (curr->left)
        {
            inorderTraverse(curr->left);
        }
        cout << curr->val << " ";
        if (curr->right)
        {
            inorderTraverse(curr->right);
        }
    }

    void postorderTraverse(node *curr)
    {
        if (curr->left)
        {
            postorderTraverse(curr->left);
        }
        if (curr->right)
        {
            postorderTraverse(curr->right);
        }
        cout << curr->val << " ";
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    bst b;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        b.insert(x);
    }
    b.inorderTraverse(b.root);
    return 0;
}