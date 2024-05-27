#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <vector>
using namespace std;
//-------------------------------------------------------class-----------------------------------------------------------------------
class Item
{
private:
    string itemName;
    string category;
    int price;

public:
    // Regular constructor
    Item(string itemName, string category, int price);

    // Copy constructor
    Item(const Item &other);

    // Getter methods
    string get_itemName() const;
    string get_category() const;
    int get_price() const;

    // Compare methods
    bool compareByPrice(const Item &I1, const Item &I2);

    // Display method
    void display(ostream &os) const;
    void display() const;

    // Overload comparison operators
    friend bool operator<(const Item &I1, const Item &I2);
    friend bool operator>(const Item &I1, const Item &I2);
    friend bool operator==(const Item &I1, const Item &I2);
};
//-----------------------------------------------class_implementation----------------------------------------------------------------
Item::Item(string itemName, string category, int price)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
}

Item::Item(const Item &other) : itemName(other.itemName), category(other.category), price(other.price) {}

string Item::get_itemName() const
{
    return itemName;
}

string Item::get_category() const
{
    return category;
}

int Item::get_price() const
{
    return price;
}

void Item::display(ostream &os) const
{
    os << "Item Name: " << itemName << "\n";
    os << "Category: " << category << "\n";
    os << "Price: " << price << "\n";
    os << "\n";
}

void Item::display() const
{
    display(cout);
}

bool operator<(const Item &I1, const Item &I2)
{
    if (I1.itemName != I2.itemName)
        return I1.itemName < I2.itemName;
    if (I1.category != I2.category)
        return I1.category < I2.category;
    return I1.price < I2.price;
}

bool operator>(const Item &I1, const Item &I2)
{
    return I2 < I1; // Just swap the arguments and use the < operator
}

bool operator==(const Item &I1, const Item &I2)
{
    return I1.itemName == I2.itemName && I1.category == I2.category && I1.price == I2.price;
}

bool compareByPrice(const Item &I1, const Item &I2)
{
    return I1.get_price() > I2.get_price();
}
//---------------------------------------------------------BST_Implementation--------------------------------------------------------
template <typename T>
struct BSTNode
{
    T Key;
    BSTNode<T> *leftlink;
    BSTNode<T> *rightlink;

    BSTNode() : leftlink(nullptr), rightlink(nullptr) {}

    BSTNode(const T &key) : Key(key), leftlink(nullptr), rightlink(nullptr) {}
};
//*********************************************************************************
template <typename T>
class BST
{
private:
    BSTNode<T> *root;

public:
    BST() : root(NULL) {}
    BSTNode<T> *getroot() const { return root; }
    /////////////////////helperfunc////////////////////////////
    void inOrder(BSTNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        inOrder(node->leftlink, items);
        items.push_back(node->Key);
        inOrder(node->rightlink, items);
    }

    void preOrder(BSTNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        items.push_back(node->Key);       // Visit the root node first
        preOrder(node->leftlink, items);  // Then traverse the left subtree
        preOrder(node->rightlink, items); // Finally traverse the right subtree
    }
    ////////////////////////// insert///////////////////////////
    void insert(const T &insertItem)
    {
        BSTNode<T> *current, *prev, *newNode;
        newNode = new BSTNode<T>(insertItem);
        if (root == NULL)
            root = newNode;
        else
        {
            current = root;
            while (current != NULL)
            {
                prev = current;
                if (current->Key == insertItem)
                {
                    cout << "The insert item is already in the list-";
                    cout << "duplicates are not allowed.";
                    insertItem.display();
                    return;
                }
                else if (insertItem < current->Key)
                    current = current->leftlink;
                else
                    current = current->rightlink;
            }
            if (insertItem < prev->Key)
                prev->leftlink = newNode;
            else
                prev->rightlink = newNode;
        }
    }
    /////////////////////////remove////////////////////////////////////////
    void deleteNode(BSTNode<T> *&node, const T &deleteItem)
    {
        BSTNode<T> *temp, *current, *prev;
        if (node == NULL)
            cerr << "Error: The node to be deleted is NULL." << endl;

        if (deleteItem < node->Key)
        {
            deleteNode(node->leftlink, deleteItem);
        }
        else if (deleteItem > node->Key)
        {
            deleteNode(node->rightlink, deleteItem);
        }
        else
        {
            if (node->leftlink == NULL && node->rightlink == NULL)
            {
                node = nullptr;
                delete node;
            }
            else if (node->leftlink == NULL)
            {
                temp = node;
                node = node->rightlink;
                delete temp;
            }
            else if (node->rightlink == NULL)
            {
                temp = node;
                node = node->leftlink;
                delete temp;
            }
            else
            {
                current = node->leftlink;
                prev = NULL;
                while (current->rightlink != NULL)
                {
                    prev = current;
                    current = current->rightlink;
                }
                node->Key = current->Key;
                if (prev == NULL)
                    node->leftlink = current->leftlink;
                else
                    prev->rightlink = current->leftlink;
                delete current;
            }
        }
    }

    void deleteitem(const T &deleteItem)
    {
        deleteNode(root, deleteItem);
    }
    /////////////////////////Display//////////////////////////
    void Display() const
    {
        vector<T> items;
        preOrder(root, items);
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their name ascending////////////////////////
    void displaySortedByNameascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end());
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their name descending////////////////////////
    void displaySortedByNamedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.rbegin(), items.rend());
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their prices ascending//////////////////////
    void displaySortedByPriceascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T &a, const T &b)
             { return a.get_price() < b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their prices descending//////////////////////
    void displaySortedByPricedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T &a, const T &b)
             { return a.get_price() > b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
};
//---------------------------------------------------------AVL_Implementation--------------------------------------------------------
template <class elemType>
struct AVLNode
{
    elemType value;
    int bf, height; // balance factor and height of the node
    AVLNode<elemType> *left;
    AVLNode<elemType> *right;

    AVLNode(const elemType &value) : value(value), bf(0), height(1), left(nullptr), right(nullptr) {}
};
//**********************************************************************************
template <typename elemType>
class AVL
{
private:
    AVLNode<elemType> *root;

public:
    AVL() : root(NULL) {}

    AVLNode<elemType> *getroot() const { return root; }

    int getHeight(AVLNode<elemType> *node) const
    {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode<elemType> *node) const
    {
        return node ? getHeight(node->right) - getHeight(node->left) : 0;
    }

    void updateHeightAndBalanceFactor(AVLNode<elemType> *node)
    {
        if (node)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
            node->bf = getBalanceFactor(node);
        }
    }

    /////////////////////helperfunc//////////////////////////////////////////////////
    void inOrder(AVLNode<elemType> *node, vector<elemType> &items) const
    {
        if (node == nullptr)
            return;
        inOrder(node->left, items);
        items.push_back(node->value);
        inOrder(node->right, items);
    }

    void preOrder(AVLNode<elemType> *node, vector<elemType> &items) const
    {
        if (node == nullptr)
            return;
        items.push_back(node->value);
        preOrder(node->left, items);
        preOrder(node->right, items);
    }

    // Re-balance a node if its balance factor is +2 or -2.
    AVLNode<elemType> *balance(AVLNode<elemType> *node)
    {
        updateHeightAndBalanceFactor(node);
        int balanceFactor = node->bf;

        if (balanceFactor > 1)
        {
            if (node->right->bf < 0)
            {
                node->right = rightRotation(node->right);
            }
            return leftRotation(node);
        }
        if (balanceFactor < -1)
        {
            if (node->left->bf > 0)
            {
                node->left = leftRotation(node->left);
            }
            return rightRotation(node);
        }
        return node;
    }

    AVLNode<elemType> *leftRotation(AVLNode<elemType> *node)
    {
        AVLNode<elemType> *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeightAndBalanceFactor(node);
        updateHeightAndBalanceFactor(newRoot);
        return newRoot;
    }

    AVLNode<elemType> *rightRotation(AVLNode<elemType> *node)
    {
        AVLNode<elemType> *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeightAndBalanceFactor(node);
        updateHeightAndBalanceFactor(newRoot);
        return newRoot;
    }

    // Helper method to find the leftmost node (which has the smallest value)
    elemType findMin(AVLNode<elemType> *node) const
    {
        while (node->left != nullptr)
            node = node->left;
        return node->value;
    }

    // Helper method to find the rightmost node (which has the largest value)
    elemType findMax(AVLNode<elemType> *node) const
    {
        while (node->right != nullptr)
            node = node->right;
        return node->value;
    }

    ////////////////////////// insert/////////////////////////////////////////////////
    AVLNode<elemType> *insertNode(AVLNode<elemType> *node, const elemType &value)
    {
        // Base case.
        if (node == nullptr)
            return new AVLNode<elemType>(value);

        // Insert node in left subtree.
        if (value < node->value)
        {
            node->left = insertNode(node->left, value);
        }
        // Insert node in right subtree.
        else if (value > node->value)
        {
            node->right = insertNode(node->right, value);
        }
        // Duplicate values are not allowed
        else
        {
            cout << "The insert item is already in the list-";
            cout << "duplicates are not allowed.";
            value.display();
            return node;
        }

        // Re-balance tree.
        return balance(node);
    }

    void insert(const elemType &value)
    {
        root = insertNode(root, value);
    }
    /////////////////////////remove///////////////////////////////////////////////////
    AVLNode<elemType> *deleteNode(AVLNode<elemType> *node, const elemType &deleteItem)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (deleteItem < node->value)
        {
            node->left = deleteNode(node->left, deleteItem);
        }
        else if (deleteItem > node->value)
        {
            node->right = deleteNode(node->right, deleteItem);
        }
        else
        {
            if (node->left == nullptr)
            {
                AVLNode<elemType> *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                AVLNode<elemType> *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                elemType minValue = findMin(node->right);
                node->value = minValue;
                node->right = deleteNode(node->right, minValue);
            }
        }
        return balance(node);
    }

    void deleteitem(const elemType &value)
    {
        root = deleteNode(root, value);
    }
    /////////////////////////Display//////////////////////////////////////////////////
    void Display() const
    {
        vector<elemType> items;
        preOrder(root, items);
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their name ascending/////////////////////////
    void displaySortedByNameascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end());
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their name descending////////////////////////
    void displaySortedByNamedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.rbegin(), items.rend());
        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their prices ascending///////////////////////
    void displaySortedByPriceascending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const elemType &a, const elemType &b)
             { return a.get_price() < b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
    ///////////////////Display sorted by their prices descending//////////////////////
    void displaySortedByPricedescending() const
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        vector<elemType> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const elemType &a, const elemType &b)
             { return a.get_price() > b.get_price(); });

        for (const auto &item : items)
        {
            item.display();
        }
    }
};
//---------------------------------------------------------Heaps_Implementation------------------------------------------------------
template <typename elemType>
class MaxHeap
{
private:
    vector<elemType> heap;

public:
    MaxHeap() {}

    void heapify()
    {
        int size = heap.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            int lchild = 2 * i + 1;
            int rchild = 2 * i + 2;
            int parent = i;

            if (lchild < size && heap[lchild] > heap[parent])
            {
                parent = lchild;
            }

            if (rchild < size && heap[rchild] > heap[parent])
            {
                parent = rchild;
            }

            if (parent != i)
            {
                swap(heap[i], heap[parent]);
            }
        }
    }

    void heapifyByPrice()
    {
        int size = heap.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            int lchild = 2 * i + 1;
            int rchild = 2 * i + 2;
            int parent = i;

            if (lchild < size && compareByPrice(heap[lchild], heap[parent]))
            {
                parent = lchild;
            }

            if (rchild < size && compareByPrice(heap[rchild], heap[parent]))
            {
                parent = rchild;
            }

            if (parent != i)
            {
                swap(heap[i], heap[parent]);
            }
        }
    }

    vector<elemType> getHeap()
    {
        return heap;
    }

    void setHeap(const vector<elemType> &items)
    {
        heap = items;
        heapify();
    }

    void insert(const elemType &item)
    {
        heap.push_back(item);
        heapify();
    }

    void deleteItem(const elemType &item)
    {
        auto del = find(heap.begin(), heap.end(), item);
        if (del == heap.end())
        {
            cout << "Element Not Found in Heap." << endl;
            return;
        }
        else
        {
            auto index = distance(heap.begin(), del);
            swap(heap[index], heap.back());
            heap.pop_back();
            heapify();
        }
    }

    void display() const
    {
        if (heap.size() == 0)
            cout << "Empty Heap" << endl;
        else
        {
            for (const auto &item : heap)
            {
                item.display();
            }
            cout << endl;
        }
    }
};

template <typename elemType>
class MinHeap
{
private:
    vector<elemType> heap;

public:
    MinHeap() {}

    void heapify()
    {
        int size = heap.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            int lchild = 2 * i + 1;
            int rchild = 2 * i + 2;
            int parent = i;

            if (lchild < size && heap[lchild] < heap[parent])
            {
                parent = lchild;
            }

            if (rchild < size && heap[rchild] < heap[parent])
            {
                parent = rchild;
            }

            if (parent != i)
            {
                swap(heap[i], heap[parent]);
            }
        }
    }

    void heapifyByPrice()
    {
        int size = heap.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            int lchild = 2 * i + 1;
            int rchild = 2 * i + 2;
            int parent = i;

            if (lchild < size && !compareByPrice(heap[lchild], heap[parent]))
            {
                parent = lchild;
            }

            if (rchild < size && !compareByPrice(heap[rchild], heap[parent]))
            {
                parent = rchild;
            }

            if (parent != i)
            {
                swap(heap[i], heap[parent]);
            }
        }
    }

    vector<elemType> getHeap()
    {
        return heap;
    }

    void setHeap(const vector<elemType> &items)
    {
        heap = items;
        heapify();
    }

    void insert(const elemType &item)
    {
        heap.push_back(item);
        heapify();
    }

    void deleteItem(const elemType &item)
    {
        auto del = find(heap.begin(), heap.end(), item);
        if (del == heap.end())
        {
            cout << "Element Not Found in Heap." << endl;
            return;
        }
        else
        {
            auto index = distance(heap.begin(), del);
            swap(heap[index], heap.back());
            heap.pop_back();
            heapify();
        }
    }

    void display() const
    {
        if (heap.size() == 0)
            cout << "Empty Heap" << endl;
        else
        {
            for (const auto &item : heap)
            {
                item.display();
            }
            cout << endl;
        }
    }
};

template <typename elemType>
class Heap
{
private:
    vector<elemType> items;
    MaxHeap<elemType> maxHeap;
    MinHeap<elemType> minHeap;

public:
    Heap() {}

    void insert(const elemType &item)
    {
        items.push_back(item);
        maxHeap.insert(item);
        minHeap.insert(item);
    }

    void deleteItem(const elemType &item)
    {
        auto del = find(items.begin(), items.end(), item);
        if (del == items.end())
        {
            cout << "Element Not Found in Heap." << endl;
            return;
        }
        else
        {
            auto index = distance(items.begin(), del);

            items.erase(del);
            maxHeap.deleteItem(item);
            minHeap.deleteItem(item);
        }
    }

    void display() const
    {
        if (items.size() == 0)
            cout << "Empty Heap" << endl;
        else
        {
            for (const auto &item : items)
            {
                item.display();
            }
            cout << endl;
        }
    }

    vector<elemType> HeapSort(bool ASC, bool ByPrice)
    {
        if (!ByPrice)
        {
            vector<elemType> SortedItems;
            if (!ASC)
            {
                MaxHeap<elemType> tempMaxHeap;
                tempMaxHeap.setHeap(maxHeap.getHeap());

                while (!tempMaxHeap.getHeap().empty())
                {
                    SortedItems.push_back(tempMaxHeap.getHeap()[0]);
                    tempMaxHeap.deleteItem(tempMaxHeap.getHeap()[0]);
                }
            }
            else
            {
                MinHeap<elemType> tempMinHeap;
                tempMinHeap.setHeap(minHeap.getHeap());

                while (!tempMinHeap.getHeap().empty())
                {
                    SortedItems.push_back(tempMinHeap.getHeap()[0]);
                    tempMinHeap.deleteItem(tempMinHeap.getHeap()[0]);
                }
            }

            return SortedItems;
        }
        else
        {
            vector<elemType> SortedItems;
            if (!ASC)
            {
                MaxHeap<elemType> tempMaxHeap;
                tempMaxHeap.setHeap(maxHeap.getHeap());
                tempMaxHeap.heapifyByPrice();

                while (!tempMaxHeap.getHeap().empty())
                {
                    SortedItems.push_back(tempMaxHeap.getHeap()[0]);
                    tempMaxHeap.deleteItem(tempMaxHeap.getHeap()[0]);
                    tempMaxHeap.heapifyByPrice();
                }
            }
            else
            {
                MinHeap<elemType> tempMinHeap;
                tempMinHeap.setHeap(minHeap.getHeap());
                tempMinHeap.heapifyByPrice();

                while (!tempMinHeap.getHeap().empty())
                {
                    SortedItems.push_back(tempMinHeap.getHeap()[0]);
                    tempMinHeap.deleteItem(tempMinHeap.getHeap()[0]);
                    tempMinHeap.heapifyByPrice();
                }
            }

            return SortedItems;
        }
    }

    void displaySortedByNameAscending()
    {
        vector SortedItems = HeapSort(true, false);
        for (auto item : SortedItems)
        {
            item.display();
        }
    }
    void displaySortedByNameDescending()
    {
        vector SortedItems = HeapSort(false, false);
        for (auto item : SortedItems)
        {
            item.display();
        }
    }
    void displaySortedByPriceAscending()
    {
        vector SortedItems = HeapSort(true, true);
        for (auto item : SortedItems)
        {
            item.display();
        }
    }

    void displaySortedByPriceDescending()
    {
        vector SortedItems = HeapSort(false, true);
        for (auto item : SortedItems)
        {
            item.display();
        }
    }
};
//-----------------------------------------------------------mainfunctions-----------------------------------------------------------
template <typename TreeType, typename T, typename C>
void readItems(istream &file, TreeType &bst, T &avl, C &heap)
{
    int itemCount;
    file >> itemCount;
    file.ignore();

    for (int i = 0; i < itemCount; ++i)
    {
        string name, category;
        int price;
        getline(file, name);
        getline(file, category);
        file >> price;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        Item item(name, category, price);
        bst.insert(item);
        avl.insert(item);
        heap.insert(item);
    }
}

void displayMenu()
{
    cout << "Choose a tree structure:" << endl;
    cout << "1. Binary Search Tree (BST)" << endl;
    cout << "2. Heap" << endl;
    cout << "3. AVL Tree" << endl;
    cout << "4. Exit" << endl;
}

void bstMenu(BST<Item> &bst)
{
    int choice;
    while (true)
    {
        cout << "BST Menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. remove item" << endl;
        cout << "3. Display items" << endl;
        cout << "4. Display items sorted by name (ascending)" << endl;
        cout << "5. Display items sorted by name (descending)" << endl;
        cout << "6. Display items sorted by price (ascending)" << endl;
        cout << "7. Display items sorted by price (descending)" << endl;
        cout << "8. Back to main menu" << endl;
        cin >> choice;

        if (choice == 1)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            bst.insert(Item(name, category, price));
        }
        else if (choice == 2)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            bst.deleteitem(Item(name, category, price));
        }
        else if (choice == 3)
        {
            bst.Display();
        }
        else if (choice == 4)
        {
            bst.displaySortedByNameascending();
        }
        else if (choice == 5)
        {
            bst.displaySortedByNamedescending();
        }
        else if (choice == 6)
        {
            bst.displaySortedByPriceascending();
        }
        else if (choice == 7)
        {
            bst.displaySortedByPricedescending();
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, try again." << endl;
        }
    }
}

void heapMenu(Heap<Item> &heap)
{
    int choice;
    while (true)
    {
        cout << "Heap Menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. remove item" << endl;
        cout << "3. Display items" << endl;
        cout << "4. Display items sorted by name (ascending)" << endl;
        cout << "5. Display items sorted by name (descending)" << endl;
        cout << "6. Display items sorted by price (ascending)" << endl;
        cout << "7. Display items sorted by price (descending)" << endl;
        cout << "8. Back to main menu" << endl;
        cin >> choice;

        if (choice == 1)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            heap.insert(Item(name, category, price));
        }
        else if (choice == 2)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            heap.deleteItem(Item(name, category, price));
        }
        else if (choice == 3)
        {
            heap.display();
        }
        else if (choice == 4)
        {
            heap.displaySortedByNameAscending();
        }
        else if (choice == 5)
        {
            heap.displaySortedByNameDescending();
        }
        else if (choice == 6)
        {
            heap.displaySortedByPriceAscending();
        }
        else if (choice == 7)
        {
            heap.displaySortedByPriceDescending();
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, try again." << endl;
        }
    }
}

void avlMenu(AVL<Item> &avl)
{
    int choice;
    while (true)
    {
        cout << "AVL Tree Menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. remove item" << endl;
        cout << "3. Display items" << endl;
        cout << "4. Display items sorted by name (ascending)" << endl;
        cout << "5. Display items sorted by name (descending)" << endl;
        cout << "6. Display items sorted by price (ascending)" << endl;
        cout << "7. Display items sorted by price (descending)" << endl;
        cout << "8. Back to main menu" << endl;
        cin >> choice;

        if (choice == 1)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            avl.insert(Item(name, category, price));
        }
        else if (choice == 2)
        {
            string name, category;
            int price;
            cout << "Enter item name: " << endl;
            cin >> name;
            cout << "Enter item category: " << endl;
            cin >> category;
            cout << "Enter item price: " << endl;
            cin >> price;
            avl.deleteitem(Item(name, category, price));
        }
        else if (choice == 3)
        {
            avl.Display();
        }
        else if (choice == 4)
        {
            avl.displaySortedByNameascending();
        }
        else if (choice == 5)
        {
            avl.displaySortedByNamedescending();
        }
        else if (choice == 6)
        {
            avl.displaySortedByPriceascending();
        }
        else if (choice == 7)
        {
            avl.displaySortedByPricedescending();
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, try again." << endl;
        }
    }
}
//---------------------------------------------------------------main----------------------------------------------------------------
int main()
{
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    BST<Item> bst;
    AVL<Item> avl;
    Heap<Item> heap;

    ifstream file("items.txt");
    if (file.is_open())
    {
        readItems(file,bst,avl,heap);
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << "\n";
    }

    int choice;
    while (true)
    {
        displayMenu();
        cin >> choice;
        if (choice == 1)
        {
            bstMenu(bst);
        }
        else if (choice == 2)
        {
            heapMenu(heap);
        }
        else if (choice == 3)
        {
            avlMenu(avl);
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
    
}