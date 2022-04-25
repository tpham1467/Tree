#include <iostream>
#include <math.h>
using namespace std;
#define COUNT 10
struct Node
{
  Node *Left;
  Node *Right;
  int key;
};
Node *CreateNode(int data)
{
  return new Node{nullptr, nullptr, data};
}
int GetHeight(Node *root)
{
  if (root == NULL)
    return 0;
  return 1 + max(GetHeight(root->Left), GetHeight(root->Right));
}
Node *RightRotate(Node *root)
{
  Node *x = root->Left;
  root->Left = x->Right;
  x->Right = root;
  return x;
}
Node *LeftRotate(Node *root)
{
  Node *x = root->Right;
  root->Right = x->Left;
  x->Left = root;
  return x;
}
Node *Insert(Node *root, int data)

{
  if (root == nullptr)
    return CreateNode(data);
  if (root->key > data)
  {
    root->Left = Insert(root->Left, data);
  }
  else if (root->key < data)
  {
     root->Right = Insert(root->Right, data);
   
  }
  else
  {
    return root;
  }

  int banlance = GetHeight(root->Left) - GetHeight(root->Right);
  //cout<<banlance<<endl;
  if (banlance > 1 && data < root->Left->key)
  {
    // cout<<"{"<<endl;
    return RightRotate(root);
  }
  if (banlance < -1 && data > root->Right->key)
  {
    //  cout<<"#"<<endl;
    return LeftRotate(root);
  }
  if (banlance > 1 && data > root->Left->key)
  {
    //  cout<<"!"<<endl;
    root->Left = LeftRotate(root->Left);
    return RightRotate(root);
  }
  if (banlance < -1 && data < root->Right->key)
  {
    // cout<<"?"<<endl;
    root->Right = RightRotate(root->Right);
    return LeftRotate(root);
  }
  return root;
}

Node * DeleteNode(Node * root ,int data)
{
  // 
}
void print2DUtil(Node *root, int space)
{
  // Base case
  if (root == NULL)
    return;

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  print2DUtil(root->Right, space);

  // Print current node after space
  // count
  cout << endl;
  for (int i = COUNT; i < space; i++)
    cout << " ";
  cout << root->key << "\n";

  // Process left child
  print2DUtil(root->Left, space);
}
void print2DUtil(Node *root)
{
  // Pass initial space count as 0
  print2DUtil(root, 0);
}
int main()
{
  Node *Root = nullptr;
  Root = Insert(Root, 18);
  Root = Insert(Root, 12);
  Root = Insert(Root, 30);
  Root = Insert(Root, 25);
  Root = Insert(Root, 69);
    //   print2DUtil(Root);
    // cout<<endl<<endl;
  Root = Insert(Root, 23);
  print2DUtil(Root);
  return 0;
}