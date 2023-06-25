#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *parent;
    Node *left;
    Node *right;
    bool black;
};
class BRTree
{
    public:
        Node *root;
        BRTree(){this->root = NULL;};
        //Node * 
        void rootTree(int x);
        Node * newNode(Node* par, int data); 
        Node *grandparent(Node *n);
        Node *uncle(Node *n);
        Node * botherLeft(Node* cur);
        void rotateLeft(Node *n);
        void rotateRight(Node *n);
        void changeColor(Node *node);
        void print(Node *node);
        void insertNode(Node *par, int data);
};

//Node *
void BRTree::rootTree(int data) 
{    //функция, создающая корень
    Node* tr = new Node;
    tr->value = data;
    tr->black = true;
    tr->left = tr->right = NULL;
    tr->parent = NULL;
    root = tr;
    //return tr;
}
Node *  BRTree::newNode(Node* par, int data) 
{ //создание узла
    Node *n = new Node();
    n->value = data;
    n->black = false;
    n->left = n->right = NULL;
    n->parent = par;
    return n;
}
void BRTree::rotateLeft(Node *node)
{   //поворот влево
    /*Node rotateLeft(h : Node) 
      x = h.right
      h.right = x.left
      x.left = h
      x.color = h.color
      h.color = RED
      return x*/

    Node *x = node->right;
    node->right = x->left;
    x->left = node;
    x->black = node->black;
    node->black = false;
    /*Node *pivot = node->right;
	pivot->parent = node->parent; 
    
    if (node->parent) 
    {
        if (node->parent->left == node) node->parent->left = pivot;
        else node->parent->right = pivot;
    }		
    node->right = pivot->left;
    
    if (pivot->left) pivot->left->parent = node;
    
    node->parent = pivot;
    pivot->left = node;*/
    if (node == root) {x->black = true; root = x; }
    //root = pivot;
}

void BRTree::rotateRight(Node *node)
{   // поворот вправо
/*      x = h.left  ----x=pivot, h=node
      h.left = x.right
      x.right = h
      x.color = h.color
      h.color = RED*/
    Node *x = node->left;
    node->left = x->right;
    x->right = node;
    x->black = node->black;
    node->black = false;
    /*Node *pivot = node->left;

    pivot->parent = node->parent; 
    
    if (node->parent) 
    {
        if (node->parent->left == node) node->parent->left = pivot;
        else node->parent->right = pivot;
    }		
    node->left = pivot->right;
    
    if (pivot->right) pivot->right->parent = node;
    
    node->parent = pivot;
    pivot->right = node;*/
    if (node == root) {x->black = true; root = x; }
    //root = pivot;
}

void BRTree::changeColor(Node *node)
{   //переворот цвета
    node->black = ! node->black;
    node->left->black = ! node->left->black;
    node->right->black = ! node->right->black;
    if (node == root) node->black = true;
}

void BRTree::insertNode(Node *par, int data)
{   // функция вставки элемента в дерево
    if (!par) return rootTree(data);
    if(par->value == data) return;
    if (par->value > data)  // идем по левой ветке
        if (!par->left) par->left = newNode(par, data);
        else insertNode(par->left, data);
    else    // идем по правой ветке
        if (!par->right) par->right = newNode(par, data);
        else insertNode(par->right, data);
    
    if(par->right && par->left && !par->right->black && par->left->black)
        rotateLeft(par);// левый поворот, если правый красный, а левый черный
    else
        if(par->left && par->left->left && !par->left->black && !par->left->left->black)
        rotateRight(par);   // правый поворот если два подряд левых елемента красные
    
    if (par->left && par->right && !par->left->black && !par->left->black)
        changeColor(par);   // оюа ребенка красные = переворачиваем цвета
    
    if (!par->left && par->right && !par->right->black)
        {   // есть только правый ребенок и он красный
            Node *r;
            Node *p;
            r = par->right;
            p = par->parent;
            if (p) 
                if(p->left == par) p->left = r;
                else p->right = r;
            r->parent = p;
            par->parent = r;
            r->left = par;
            par->right = NULL;
            if (par == root) 
            {
                r->black = true;
                root = r;
            }
        }
}

void BRTree::print(Node *node)
{   // печать узла
    if(node == NULL)
        return;
    cout << node->value;
    if (node->black) cout << "  BLACK" << endl;
    else cout << "  RED" << endl;

    if(node->left)
    {
        cout << "L: " << node->left->value;
        if (node->left->black) cout << "  BLACK" << endl;
        else cout << "  RED" << endl;
    }

    if(node->right){
        cout << "R: " << node->right->value;
        if (node->right->black) cout << "  BLACK" << endl;
        else cout << "  RED" << endl;
    }

    print(node->left);
    print(node->right);
}   

int main() 
{   
    int data;
    BRTree *tree = new BRTree();
    cout << "Введите значения для дерева от 0 до 100." << endl;

     while (true)
    {
        cout << "Введите значение (число больше 100 - конец ввода)";
        cin >> data;
        if (data > 100) break;
        tree->insertNode(tree->root, data);
        tree->print(tree->root);
    }
     
    tree->print(tree->root);

    return 0;
}