#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class TreeNode
{
public:
    int val;
    TreeNode *left, *right, *parent;
    TreeNode()
    {
        val = 0;
        left = right = parent = NULL;
    }
    TreeNode(int _val)
    {
        val = _val;
        left = right = parent = NULL;
    }
};

class bst
{
public:
    TreeNode *root;
    bst()
    {
        root = NULL;
    }

    void insert(int val)
    {
        TreeNode *curr = root;
        if (!root)
        {
            root = new TreeNode(val);
            return;
        }
        insert_rec(root, val);
    }

    // both the insert_rec functions (commented out and commented in) works perfectly fine

    void insert_rec(TreeNode *curr, int val)
    {
        if (val < curr->val)
        {
            if (!curr->left)
            {
                curr->left = new TreeNode(val);
                curr->left->parent = curr;
                return;
            }
            insert_rec(curr->left, val);
        }
        else
        {
            if (!curr->right)
            {
                curr->right = new TreeNode(val);
                curr->right->parent = curr;
                return;
            }
            insert_rec(curr->right, val);
        }
    }

    // void insert_rec(TreeNode *&curr, int val) // here is the crucial point, u have to use
    // // *&curr (not *curr) otherwise it won't link up in this function
    // // because a copy of the TreeNode is being passed here
    // {
    //     if (!curr)
    //     {
    //         curr = new TreeNode(val);
    //         return;
    //     }
    //     if (val < curr->val)
    //         insert_rec(curr->left, val);
    //     else
    //         insert_rec(curr->right, val);
    // }

    TreeNode *search(int val)
    {
        TreeNode *curr = root;
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

    TreeNode *findMin(TreeNode *curr)
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

    TreeNode *findMax(TreeNode *curr)
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

    bool isLeaf(TreeNode *curr)
    {
        return curr->left == NULL and curr->right == NULL;
    }

    bool isRoot(TreeNode *curr)
    {
        return !curr->parent;
    }

    bool hasOneTreeNode(TreeNode *curr)
    {
        return !curr->left or !curr->right;
    }

    void deleteTreeNode(int val)
    {
        TreeNode *to_delete = search(val);

        // if (isLeaf(to_delete)) // if the TreeNode is a leaf
        // {
        //     cout << "it's a leaf" << endl;
        //     to_delete = NULL;
        //     if (!to_delete)
        //         cout << "made null in delete function" << endl;
        //     return;
        // }

        if (hasOneTreeNode(to_delete)) // has only one TreeNode
        {
            if (to_delete->left)
            {
                if (isRoot(to_delete)) // if the TreeNode is the root
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

        else // has both TreeNodes
        {
            TreeNode *to_swap = findMin(to_delete->right); // find inorder successor
            to_delete->val = to_swap->val;
            if (!isLeaf(to_swap))
            {
                to_swap->parent->left = to_swap->right;
            }
            free(to_swap);
        }
    }

    void preorderTraverse(TreeNode *curr)
    {
        cout << curr->val << " ";
        if (curr->left)
            preorderTraverse(curr->left);
        if (curr->right)
            preorderTraverse(curr->right);
        return;
    }

    void inorderTraverse(TreeNode *curr)
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

    void postorderTraverse(TreeNode *curr)
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

    int flag = 0;

    bool find(TreeNode *curr, int sum)
    {
        if (!curr)
            return false;
        TreeNode *otherOne = search(sum - curr->val);
        if (otherOne && otherOne != curr)
            return true;

        return find(curr->left, sum) || find(curr->right, sum);
    }
};

bool findTarget(TreeNode *root, int sum)
{
    bst b;
    b.root = root;
    return b.find(root, sum);
}

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
    int s;
    cin >> s;
    if (findTarget(b.root, s))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    // b.search(15);

    return 0;
}