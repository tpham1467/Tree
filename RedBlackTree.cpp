#include <iostream>

using namespace std;
#define COUNT 10
struct node
{
    int key;
    node *parent;
    int color;
    node *left;
    node *right;
};
struct RBtree
{
    node *root;

    RBtree()
    {
       
        root = NULL;
    }
    node *Create(int key, int color)
    {
        return new node{key, nullptr, color, nullptr, nullptr};
    }
    node *successor(node *p)
    {
        node *y = NULL;
        if (p->left != NULL)
        {
            y = p->left;
            while (y->right != NULL)
                y = y->right;
        }
        else
        {
            y = p->right;
            while (y->left != NULL)
                y = y->left;
        }
        return y;
    }
    void leftrotate(node *p)
    {
        if (p->right == NULL)
            return;
        else
        {
            node *y = p->right;
            if (y->left != NULL)
            {
                p->right = y->left;
                y->left->parent = p;
            }
            else
                p->right = NULL;
            if (p->parent != NULL)
                y->parent = p->parent;
            if (p->parent == NULL)
                root = y;
            else
            {
                if (p == p->parent->left)
                    p->parent->left = y;
                else
                    p->parent->right = y;
            }
            y->left = p;
            p->parent = y;
        }
    }
    void rightrotate(node *p)
    {
        if (p->left == NULL)
            return;
        else
        {
            node *y = p->left;
            if (y->right != NULL)
            {
                p->left = y->right;
                y->right->parent = p;
            }
            else
                p->left = NULL;
            if (p->parent != NULL)
                y->parent = p->parent;
            if (p->parent == NULL)
                root = y;
            else
            {
                if (p == p->parent->left)
                    p->parent->left = y;
                else
                    p->parent->right = y;
            }
            y->right = p;
            p->parent = y;
        }
    }

    void insert(int key)
    {
        node *p, *q;
        node *t = Create(key, 1);
        p = root;
        q = nullptr;
        if (root == nullptr)
        {
            root = t;
            t->parent = nullptr;
        }
        else
        {
            while (p != NULL)
            {
                q = p;
                if (p->key < t->key)
                    p = p->right;
                else
                    p = p->left;
            }
            t->parent = q;
            if (q->key < t->key)
                q->right = t;
            else
                q->left = t;
        }
        insertfix(t);
    }
    void insertfix(node *t)
    {
        node *u;
        if (root == t)
        {
            t->color = 0;
            return;
        }
        while (t->parent != nullptr && t->parent->color == 1)
        {
            node *g = t->parent->parent;
            if (g->left == t->parent)
            {
                if (g->right != nullptr)
                {
                    u = g->right;
                    if (u->color == 1)
                    {
                        t->parent->color = 0;
                        u->color = 0;
                        g->color = 1;
                        t = g;
                    }
                }
                else
                {
                    if (t->parent->right == t)
                    {
                        t = t->parent;
                        leftrotate(t);
                    }
                    t->parent->color = 0;
                    g->color = 1;
                    rightrotate(g);
                }
            }
            else
            {
                if (g->left != nullptr)
                {
                    u = g->left;
                    if (u->color == 1)
                    {
                        t->parent->color = 1;
                        u->color = 1;
                        g->color = 0;
                        t = g;
                    }
                }
                else
                {
                    if (t->parent->left == t)
                    {
                        t = t->parent;
                        rightrotate(t);
                    }
                    t->parent->color = 0;
                    g->color = 1;
                    leftrotate(g);
                }
            }
            root->color = 0;
        }
    }
    void Delete(int key)
    {
        if (root == NULL)
            return;
        node *p;
        p = root;
        node *y = NULL;
        node *q = NULL;
        bool found = false;
        while (p != nullptr)
        {
            if (p->key > key)
                p = p->left;
            else if (p->key < key)
                p = p->right;
            else
            {
                found = true;
                break;
            }
        }
        if (!found )
        {
            cout << endl
                 << "Not Found" << endl;
            return;
        }
        else
        {
            if (p->left == NULL || p->right == NULL)
                y = p;
            else
                y = successor(p);
            if (y->left != NULL)
                q = y->left;
            else
            {
                if (y->right != NULL)
                    q = y->right;
                else
                    q = NULL;
            }
            if (q != NULL)
                q->parent = y->parent;
            if (y->parent == NULL)
                root = q;
            else
            {
                if (y == y->parent->left)
                    y->parent->left = q;
                else
                    y->parent->right = q;
            }
            if (y != p)
            {
                p->color = y->color;
                p->key = y->key;
            }
            if (y->color == 0)
                delfix(q);
        }
    }
    void delfix(node *p)
    {
        node *s;
        while (p != root && p->color == 0)
        {
            if (p->parent->left == p)
            {
                s = p->parent->right;
                if (s->color == 1)
                {
                    s->color = 0;
                    p->parent->color = 1;
                    leftrotate(p->parent);
                    s = p->parent->right;
                }
                if (s->right->color == 0 && s->left->color ==0 )
                {
                    s->color = 1;
                    p = p->parent;
                }
                else
                {
                    if (s->right->color == 0)
                    {
                        s->left->color == 0;
                        s->color = 0;
                        rightrotate(s);
                        s = p->parent->right;
                    }
                    s->color = p->parent->color;
                    p->parent->color = 0;
                    s->right->color = 0;
                    leftrotate(p->parent);
                    p = root;
                }
            }
            else
            {
                s = p->parent->left;
                if (s->color == 1)
                {
                    s->color = 0;
                    p->parent->color = 1;
                    rightrotate(p->parent);
                    s = p->parent->left;
                }
                if (s->left->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    p = p->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        s->right->color = 0;
                        s->color = 1;
                        leftrotate(s);
                        s = p->parent->left;
                    }
                    s->color = p->parent->color;
                    p->parent->color = 0;
                    s->left->color = 0;
                    rightrotate(p->parent);
                    p = root;
                }
            }
            p->color = 0;
            root->color = 0;
        }
    }
    void Search(int key)
    {
        node *p = root;
        while (p != nullptr)
        {
            if (p->key > key)
                p = p->left;
            else if (p->key < key)
                p = p->right;
            else
            {
                cout << endl
                     << "Result :" << key << endl;
                return;
            }
        }
        cout << endl
             << "Not Found" << endl;
        return;
    }
    string getColor(node *root)
    {
        if (root->color == 1)
            return "RED";
        return "BLACK";
    }
    void print2DUtil(node *root, int space)
    {
        if (root == NULL)
            return;
        space += COUNT;

        print2DUtil(root->right, space);
        cout << endl;

        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << root->key << " (" << getColor(root) << ") "
             << "\n";

        print2DUtil(root->left, space);
    }
    void print2D(node *root)
    {
        print2DUtil(root, 0);
    }
};
int main()
{
    RBtree tree;
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(8);
    tree.insert(2);
    tree.insert(9);
    tree.print2D(tree.root);
    // tree.Search(9);
    return 0;
}