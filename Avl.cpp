#include <iostream>
#include <math.h>
using namespace std;
#define COUNT 10
struct Node
{
  Node *Left;
  Node *Right;
  int key;
  int height;
};
Node *CreateNode(int data)
{
  return new Node{nullptr, nullptr, data, 1};
}
int GetHeight(Node *root)
{
  if (root == nullptr)
    return 0  ;
  return root->height;
}
Node *RightRotate(Node *root)
{
  Node *x = root->Left;
  root->Left = x->Right;
  x->Right = root;
  x->height = 1 + max(GetHeight(x->Left), GetHeight(x->Right));
  root->height = 1 + max(GetHeight(root->Left), GetHeight(root->Right));
  return x;
}
Node *LeftRotate(Node *root)
{
  Node *x = root->Right;
  root->Right = x->Left;
  x->Left = root;
  x->height = 1 + max(GetHeight(x->Left), GetHeight(x->Right));
  root->height = 1 + max(GetHeight(root->Left), GetHeight(root->Right));
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
  root->height = max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
  int banlance = GetHeight(root->Left) - GetHeight(root->Right);
  // cout << banlance << endl;
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
Node *MinValueNode(Node *root)
{
  Node *i = root->Right;
  while (i->Left != nullptr)
  {
    i = i->Left;
  }
  return i;
}
Node *DeleteNode(Node *root, int data)
{
  if (root == nullptr)
    return root;
  if (data > root->key)
  {

    root->Right = DeleteNode(root->Right, data);
  }
  else if (data < root->key)
  {

    root->Left = DeleteNode(root->Left, data);
  }
  else
  {

    if (root->Left == nullptr || root->Right == nullptr)
    {
      Node *temp = root->Left;
      if (root->Right != NULL)
        temp = root->Right;

      if (temp == NULL)
      {
        temp = root;
        root = NULL;
        delete temp;
      }
      else
      {
        *root = *temp;
        delete temp;
      }
    }
    else 
    {
      Node * temp = MinValueNode(root);
      root->key=temp->key;
      root->Right=DeleteNode(root->Right,temp->key);
      //cout<<"jdjdj";
    }
  }
  if (root == nullptr)
    return root;
  root->height = 1 + max(GetHeight(root->Left), GetHeight(root->Right));
 // cout<<" "<<root->height;
  int banlance = GetHeight(root->Left) - GetHeight(root->Right);
  //cout<<banlance<<GetHeight(root->Right)<< GetHeight(root->Left)<<endl;
  if (banlance > 1 && data < root->Left->key)
  {
    // cout<<"{"<<endl;
     //cout<<"jdjdj";
    return RightRotate(root);
  }
  if (banlance < -1 && data > root->Right->key)
  {
         
    //  cout<<"#"<<endl;
    return LeftRotate(root);
  }
  if (banlance > 1 && data > root->Left->key)
  {
       
   cout<<"!"<<endl;
    root->Left = LeftRotate(root->Left);
    return RightRotate(root);
  }
  if (banlance < -1 && data < root->Right->key)
  {
         cout<<"jdjdj";
     cout<<"?"<<endl;
    root->Right = RightRotate(root->Right);
    return LeftRotate(root);
  }
  return root;
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
Node *SearchNode(Node* root ,int key)
{
  Node * p = root;
  while(p!=nullptr)
  {
    if(key>p->key) p=p->Right;
    else if(key<p->key) p = p->Left;
    else return p;
  }
  return nullptr;
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
  // print2DUtil(Root);
  Root = DeleteNode(Root, 69);
  Root = DeleteNode(Root, 25);
  print2DUtil(Root);
  Node * NodeFind = SearchNode(Root,23); 
  if(NodeFind!=nullptr) cout<<"Result :"<<NodeFind->key;
  else cout<<"Not Found :";
  return 0;
}