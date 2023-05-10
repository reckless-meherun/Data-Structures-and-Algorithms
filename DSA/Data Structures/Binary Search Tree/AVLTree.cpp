#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node
{
public:
    int val;
    node *left, *right, *parent;
    int height;
    node()
    {
        val = 0;
        left = right = parent = NULL;
    }
    node(int _val)
    {
        val = _val;
        left = right = parent = NULL;
        height = 1;
    }
};

class avlTree
{
private:
    node *root;
    int height(node *curr)
    {
        if (!curr)
            return 0;
        return curr->height;
    }
    int balanceFactor(node *curr)
    {
        return height(curr->left) - height(curr->right); // used another function "height" to avoid calculating null
    }

    node *leftRotate(node *currRoot)
    {
        node *midNode = currRoot->right;
        node *midLeftNode = midNode->left;
        midNode->left = currRoot;
        currRoot->right = midLeftNode;

        currRoot->height = max(height(currRoot->left), height(currRoot->right));
        midNode->height = max(height(midNode->left), height(midNode->right));

        /** returning the new root of the branch */
        return midNode;
    }

    node *rightRotate(node *currRoot)
    {
        node *midNode = currRoot->left;
        node *midRightNode = midNode->right;
        midNode->right = currRoot;
        currRoot->left = midRightNode;

        currRoot->height = max(height(currRoot->left), height(currRoot->right));
        midNode->height = max(height(midNode->left), height(midNode->right));

        /** returning the new root of the branch */
        return midNode;
    }

    void insert_rec(node *curr, int val)
    {
        // cout<<"insert rec called at "<<curr->val<<endl;
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

        // cout<<"here curr root is "<<curr->val<<endl;
        curr->height = height(curr);
        int bf = balanceFactor(curr);
        // cout<<"bf "<<bf<<endl;
        if (bf > 1) // left height is longer
        {
            if (val < curr->left->val)
                curr = rightRotate(curr);
            else
            {
                curr->left = leftRotate(curr);
                curr = rightRotate(curr);
            }
            // cout<<"if okay "<<endl;
        }
        else if (bf < -1) // right height is longer
        {
            if (val > curr->left->val)
                curr = rightRotate(curr);
            else
            {
                curr->right = rightRotate(curr);
                curr = leftRotate(curr);
            }
            // cout<<"else if okay "<<endl;
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
                to_swap->parent->right = to_swap->right;
                free(to_swap);
            }
        }

        if (!curr)
            return;

        curr->height = height(curr);
        int bf = balanceFactor(curr);
        if (bf > 1) // left height is longer
        {
            if (val < curr->left->val)
                curr = rightRotate(curr);
            else
            {
                curr->left = leftRotate(curr);
                curr = rightRotate(curr);
            }
        }
        else if (bf < -1) // right height is longer
        {
            if (val > curr->left->val)
                curr = rightRotate(curr);
            else
            {
                curr->right = rightRotate(curr);
                curr = leftRotate(curr);
            }
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

public:
    avlTree()
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

    node *search(int val)
    {
        node *curr = root;
        if (!root)
        {
            cout << "Empty avlTree" << endl;
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
        delete_rec(root, val);
    }

    void preorder()
    {
        preorderTraverse(root);
    }

    void inorder()
    {
        inorderTraverse(root);
    }

    void postorder()
    {
        postorderTraverse(root);
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    avlTree b;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        b.insert(x);
    }
    b.inorder();
    b.deleteNode(15);
    cout << endl;
    b.inorder();
    
    return 0;
}