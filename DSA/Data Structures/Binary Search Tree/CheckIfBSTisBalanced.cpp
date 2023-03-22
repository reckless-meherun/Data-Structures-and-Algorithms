#include <bits/stdc++.h>
using namespace std;
 
// Structure of a tree node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    Node(int k)
    {
        key = k;
        left = right = NULL;
    }
};
 
// Function to check if tree is height balanced
int isBalanced(Node* root)
{
    if (root == NULL)
        return 0;
    int lh = isBalanced(root->left);
    if (lh == -1)
        return -1;
    int rh = isBalanced(root->right);
    if (rh == -1)
        return -1;
 
    if (abs(lh - rh) > 1)
        return -1;
    else
        return max(lh, rh) + 1;
}
 
// Driver code
int main()
{
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(30);
    root->right->left = new Node(15);
    root->right->right = new Node(20);
 
    if (isBalanced(root) > 0)
        cout << "Balanced";
    else
        cout << "Not Balanced";
    return 0;
}