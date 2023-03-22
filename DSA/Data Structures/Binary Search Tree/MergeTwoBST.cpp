
#include <bits/stdc++.h>
using namespace std;
 
class Node {
public:
    int val;
    Node* left;
    Node* right;
};
 
/* Utility function to create a new Binary Tree Node */
Node* newNode(int data)
{
    Node* temp = new Node;
    temp->val = data;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}
 
/* UTILITY FUNCTIONS */
/* MoveNode() function takes the
node from the front of the source,
and move it to the front of the dest.
It is an error to call this with the
source list empty.
  
Before calling MoveNode():
source == {1, 2, 3}
dest == {1, 2, 3}
  
After calling MoveNode():
source == {2, 3}
dest == {1, 1, 2, 3} */
void MoveNode(Node** destRef, Node** sourceRef)
{
    /* the front source node */
    Node* newNode = *sourceRef;
    assert(newNode != NULL);
  
    /* Advance the source pointer */
    *sourceRef = newNode->right;
  
    /* Link the old dest of the new node */
    newNode->right = *destRef;
  
    /* Move dest to point to the new node */
    *destRef = newNode;
}
 
 
/* Merge sorted Double linked list */
Node* mergeLinkedList(Node* a, Node* b)
{
      Node dummy;
  
    /* tail points to the last result node */
    Node* tail = &dummy;
  
    /* so tail->next is the place to
    add new nodes to the result. */
    dummy.right = NULL;
    while (1) {
        if (a == NULL) {
            /* if either list runs out, use the
            other list */
            tail->right = b;
            break;
        }
        else if (b == NULL) {
            tail->right = a;
            break;
        }
        if (a->val <= b->val)
            MoveNode(&(tail->right), &a);
        else
            MoveNode(&(tail->right), &b);
  
        tail = tail->right;
    }
    return (dummy.right);
}
 
/* convert sorted Double linked list */
void convertIntoSortedDLL(Node* root, Node*& head)
{
      //base case
    if (root == NULL)
        return;
   
    convertIntoSortedDLL(root->right, head);
    root->right = head;
   
    if (head != NULL)
        head->left = root;
   
    head = root;
   
    convertIntoSortedDLL(root->left, head);
}
 
/* Function to print nodes in a given linked list */
void printList(Node* head)
{
    while (head) {
        printf("%d ", head->val);
        head = head->right;
    }
}
 
int main()
{
    Node *root1 = nullptr, *root2 = nullptr;
 
    /* Let us create the following tree as first tree
       3
      / \
      1 5
    */
    root1 = newNode(3);
    root1->left = newNode(1);
    root1->right = newNode(5);
 
    /* Let us create the following tree as second tree
       4
      / \
      2 6
    */
    root2 = newNode(4);
    root2->left = newNode(2);
    root2->right = newNode(6);
 
    // Convert BST into sorted DLL
      Node*head1=NULL;
    Node*head2=NULL;
    convertIntoSortedDLL(root1,head1);
    convertIntoSortedDLL(root2,head2);
 
    // merge sorted DLL
    Node* ans = mergeLinkedList(head1, head2);
     
    printList(ans);
    return 0;
  // This code is contributed by Ajay Rawat(theajayrawat)
}