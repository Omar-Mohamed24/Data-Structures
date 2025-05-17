#include <iostream>
using namespace std;
//------------------------------ Node -------------------------------//
template <typename T, int order>
struct Node
{
    T *keys;
    Node **childs;
    int keyCount;
    bool leaf;
    //////////////////////////////////////
    Node(bool LeafNode = true)
    {
        this->leaf = LeafNode;
        keys = new T[order];
        childs = new Node<T, order> *[order + 1];
        keyCount = 0;
        for (int i = 0; i <= order; i++)
        {
            childs[i] = nullptr;
        }
    }
    //////////////insert_func//////////////
    Node<T, order> *insert(T key, Node<T, order> *node, Node<T, order> *root)
    {
        if (leaf)
        {
            int i = keyCount - 1;
            while (i >= 0 && keys[i] > key)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            keyCount++;
        }
        else
        {
            int i = 0;
            while (i < keyCount && key > keys[i])
            {
                i++;
            }
            childs[i]->insert(key, this, root);
        }

        if (keyCount == order)
        {
            if (this == root)
            {
                Node *temp = new Node<T, order>;
                temp->leaf = false;
                temp->childs[0] = this;
                temp->split(this);
                return temp;
            }
            else
            {
                node->split(this);
            }
        }
        return root;
    }
    //////////////print_func//////////////
    void traverse(int level = 0)
    {
        for (int i = 0; i < level; i++)
        {
            cout << " ";
        }

        for (int i = 0; i < keyCount; ++i)
        {
            if (i != 0)
            {
                cout << ",";
            }
            cout << keys[i];
        }

        cout << endl;

        for (int i = 0; i < keyCount + 1; ++i)
        {
            if (childs[i] != nullptr)
            {
                childs[i]->traverse(level + 1); 
            }
        }
    }
    //////////////split_func//////////////
    void split(Node<T, order> *node)
    {
        Node *rightNode = new Node<T, order>;
        int idx = 0, mid_idx = (order - 1) / 2;
        T mid_val = node->keys[mid_idx];
        int n = node->keyCount;

        for (int i = mid_idx + 1; i < n; i++)
        {
            rightNode->keys[idx] = node->keys[i];
            idx++;
            node->keyCount = (node->keyCount) - 1;
            rightNode->keyCount = (rightNode->keyCount) + 1;
        }

        if (!node->leaf)
        {
            int j = 0;
            for (int i = (order + 1) / 2; i <= order; i++)
            {
                rightNode->childs[j++] = node->childs[i];
            }
            rightNode->leaf = node->leaf;
        }

        int j = order - 1;
        while (childs[j] != node)
        {
            childs[j + 1] = childs[j];
            j--;
        }

        childs[j + 1] = rightNode;
        j = keyCount;

        while (j > 0 && keys[j - 1] > mid_val)
        {
            keys[j] = keys[j - 1];
            j--;
        }

        keys[j] = mid_val;
        keyCount++;
        node->keyCount = (node->keyCount) - 1;
    }
};
//------------------------------ B_Tree -------------------------------//
template <typename T, int order>
class BTree
{
private:
    Node<T, order> *root;

public:
    BTree() : root(nullptr) {}
    //////////////insert_func//////////////
    void Insert(T key)
    {
        if (root == nullptr)
        {
            root = new Node<T, order>;
            root->keys[0] = key;
            root->keyCount++;
        }
        else
        {
            root = root->insert(key, root, root);
        }
    }
    //////////////print_func//////////////
    void Print()
    {
        if (root != nullptr)
        {
            root->traverse(0);
        }
    }
    //////////////////////////////////////
    ~BTree()
    {
        delete root;
    }
};
//------------------------------- MAIN -------------------------------//
int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */
    BTree<char, 5> t; // Construct a BTree of order 5, which stores char data, Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print(); // Should output the following on the screen:
    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */

    return 0;
}