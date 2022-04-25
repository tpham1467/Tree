#include <iostream>
using namespace std;
struct Node
{
  Node * Right;
  Node * Left;
  int key ;
};
Node * CreateNode(int data)
{
  return new Node { nullptr,nullptr,data};
}
Node * Insert(Node * root, int data)
{

}
int main()
{
  Node * Root = nullptr;

  return 0;
}