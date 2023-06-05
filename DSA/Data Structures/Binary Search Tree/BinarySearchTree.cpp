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

private:
    void delete_rec(node *curr, int val)
    {
        if (!curr)
            return;
        if (val < curr->val)
            delete_rec(curr->left, val);
        else if (val > curr->val)
            delete_rec(curr->right, val);
        else
        {
            if (hasOneNode(curr)) // has only one node
            {
                if (curr->left)
                {
                    if (isRoot(curr)) // if the node is the root
                    {
                        root = root->left;
                        free(root);
                        return;
                    }
                    if (curr->parent->left == curr)
                        curr->parent->left = curr->left;
                    else if (curr->parent->right == curr)
                        curr->parent->right = curr->left;
                }
                else
                {
                    if (isRoot(curr))
                    {
                        root = root->right;
                        free(root);
                        return;
                    }
                    if (curr->parent->left == curr)
                        curr->parent->left = curr->right;
                    else if (curr->parent->right == curr)
                        curr->parent->right = curr->right;
                }
                free(curr);
            }

            else // has both nodes
            {
                node *to_swap = findMin(curr->right); // find inorder successor

                curr->val = to_swap->val;
                // to_swap->parent->right = to_swap->right;
                // free(to_swap);
                delete_rec(curr->right, to_swap->val);
            }
        }
    }
    
public:
    void deleteNode(int val)
    {
    	delete_rec(root, val);
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
    int less = 0;
    int greater = 0;
    
    int lowerValuesCount(int x)
    {
    	if(!root)
    		return 0;
    	lowerGreater_rec(root, x);
    	int l = less;
    	less = 0;
    	return l;
    }
    
    int greaterValuesCount(int x)
    {
    	if(!root)
    		return 0;
    	lowerGreater_rec(root, x);
    	int g = greater;
    	greater = 0;
    	return g;
    }
    
    void lowerGreater_rec(node *curr, int val)
    {
        if (curr->left)
        {
            lowerGreater_rec(curr->left, val);
        }
        if(curr->val <= val)
        	less++;
        else
        	greater++;
        if (curr->right)
        {
        	lowerGreater_rec(curr->right, val);
        }
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);
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
    b.deleteNode(6);
    cout<<endl;
    b.inorderTraverse(b.root);
    cout<<endl<<b.lowerValuesCount(10)<<endl;
    return 0;
}