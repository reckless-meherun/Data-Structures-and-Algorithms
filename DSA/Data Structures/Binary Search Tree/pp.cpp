#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> inorder_vector;

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

int min_diff = INT_MAX;

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

    int prev = -1;

    void inorderTraverse(TreeNode *curr)
    {
        if (curr->left)
        {
            inorderTraverse(curr->left);
        }
        // if (curr != root)
        //     // cout << curr->val << " ";
        //     min_diff = min(min_diff, curr->val - prev);
        // prev = curr->val;
        inorder_vector.push_back(curr->val);
        if (curr->right)
        {
            inorderTraverse(curr->right);
        }
    }

    int count = 1;
    int kLargest(TreeNode *curr, int k)
    {
        if (!curr)
            return 0;

        if (count == k)
            return curr->val;

        count++;

        return kLargest(curr->left, k) or kLargest(curr->right, k);
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

    TreeNode *bst_to_balanced(int start, int end)
    {
        if (start > end)
            return NULL;

        int mid = start + (end - start) / 2;
        TreeNode *curr;
        curr->val = inorder_vector[mid];

        curr->left = bst_to_balanced(start, mid - 1);
        curr->right = bst_to_balanced(mid + 1, end);

        return curr;
    }

    TreeNode *BST_to_Balanced()
    {
        inorderTraverse(root);
        int start = 0;
        int end = inorder_vector.size() - 1;
        return bst_to_balanced(start, end);
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
    // b.inorderTraverse(b.root);
    // cout << min_diff << endl;
    // cout << b.kLargest(b.root, k);

    bst balanced;
    balanced.root = b.BST_to_Balanced();



    return 0;
}