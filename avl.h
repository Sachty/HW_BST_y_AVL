#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
using namespace std;

template <typename T>

class AVLTree {
private:
    struct NodeBT {
        T data;
        int height;
        NodeBT* left;
        NodeBT* right;
        NodeBT() : left(nullptr), right(nullptr), height(0) {}
        NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0) {}

        void killSelf(){
            if(left != nullptr) left->killSelf();
            if(right != nullptr) right->killSelf();
            delete this;
        }
    };


    NodeBT *root;

public:
    AVLTree() : root(nullptr) {}

    void insert(T value) {
        insert(this->root, value);
    }

    bool find(T value) {
        return find(this->root, value);
    }

    string getPreOrder() {
        return getPreOrder(this->root);
    }

    string getInOrder(){
        return getInOrder(this->root);
    }

    string getPostOrder(){
        return getPostOrder(this->root);
    }

    int height() {
        return height(this->root);
    }

    T minValue() {
        return minValue(this->root);
    }

    T maxValue() {
        return maxValue(this->root);
    }

    bool isBalanced() {
        return isBalanced(this->root);
    }

    int size() {
        return size(this->root);
    }

    void remove(T value) {
        remove(this->root, value);
    }

    void displayPretty() {
        displayPretty(this->root, 1);
    }


    ~AVLTree() {
        if (this->root != nullptr) {
            this->root->killSelf();
        }
    }

private:
    string getPreOrder(NodeBT *node);
    string getInOrder(NodeBT *node);
    string getPostOrder(NodeBT *node);
    void insert(NodeBT *&node, T value); //*
    bool find(NodeBT *node, T value);
    int height(NodeBT *node);      //*
    bool isBalanced(NodeBT *node); //*
    T minValue(NodeBT *node);
    T maxValue(NodeBT *node);
    int size(NodeBT *node);
    void remove(NodeBT *&node, T value); //*
    void displayPretty(NodeBT *node, int level);

    /* propio del  avl*/
    int balancingFactor(NodeBT*node);
    void updateHeight(NodeBT *node);
    void balance(NodeBT *&node);
    void left_rota(NodeBT *&node);
    void right_rota(NodeBT*&node);
};


// ----------------------------------------------------------
// Desarrollo de las funciones:
template <typename T>
string AVLTree<T>::getPreOrder(NodeBT *node) {
    if (node == nullptr)
        return "";
    string cadena = "";
    cadena += std::to_string(node->data) + " ";

    if(node->left!= nullptr){
        cadena += getPreOrder(node->left);
    }
    if(node->right!= nullptr) {
        cadena += getPreOrder(node->right);;
    }
    return cadena;
}

template <typename T>
string AVLTree<T>::getInOrder(NodeBT* node){
    if (node == nullptr)
        return "";
    string cadena = "";

    if(node->left!= nullptr){
        cadena += getInOrder(node->left);
    }

    cadena += std::to_string(node->data) + " ";

    if(node->right!= nullptr) {
        cadena += getInOrder(node->right);;
    }
    return cadena;
}

template <typename T>
string AVLTree<T>::getPostOrder(NodeBT* node){
    if (node == nullptr)
        return "";
    string cadena = "";

    if(node->left!= nullptr){
        cadena += getPostOrder(node->left);
    }

    if(node->right!= nullptr) {
        cadena += getPostOrder(node->right);;
    }

    cadena += std::to_string(node->data) + " ";

    return cadena;
}


template <typename T>
void AVLTree<T>::insert(NodeBT *&node, T value) {
    if (node == nullptr)
        node = new NodeBT(value);
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);

    // Siempre actualizar alturas
    updateHeight(node);

    // Si no esta balanceado. ejecutar balanceo
    balance(node);
}

template <typename T>
bool AVLTree<T>::find(NodeBT *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}


template <typename T>
int AVLTree<T>::height(NodeBT *node)
{
    if (node == nullptr)
        return -1;
    else
        return max(height(node->left), height(node->right)) + 1;
}


template <typename T>
bool AVLTree<T>::isBalanced(NodeBT *node) //O(n^2)
{
    if (node == nullptr)
        return true;
    else
        return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template <typename T>
T AVLTree<T>::minValue(NodeBT *node)
{
    if (node == nullptr)
        throw("El AVL esta vacio");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}


template <typename T>
T AVLTree<T>::maxValue(NodeBT *node)
{
    if (node == nullptr)
        throw("El AVL esta vacio");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}


template <typename T>
int AVLTree<T>::size(NodeBT *node)
{
    if (node == nullptr)
        return 0;
    else
        return 1 + size(node->left) + size(node->right);
}

template <typename T>
void AVLTree<T>::remove(NodeBT *&node, T value)
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node; //free
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }
    updateHeight(node);
    balance(node);
}

template <typename T>
void AVLTree<T>::displayPretty(NodeBT *node, int level) {
    if (node == nullptr)
        return;
    displayPretty(node->right, level + 1);
    cout << endl;
    if (node == this->root)
        cout << "ROOT ->";
    else {
        for (int i = 0; i < level; i++)
            cout << "       ";
    }
    cout << node->data << "(" << node->height << ")";
    displayPretty(node->left, level + 1);
}


/* propio del avl*/
template<typename T>
int AVLTree<T>::balancingFactor(NodeBT *node) {
    if(node == nullptr)
        return 0;
    return (height(node->left)- height(node->right));
}

template<typename T>
void AVLTree<T>::updateHeight(NodeBT *node) {
    // Si el nodo esta vacio, no se actualiza nada
    if(node == nullptr)
        return;

    // Actualizar altura, escoger maximo y sumar 1
    node->height = max(height(node->left), height(node->right)) + 1;
}

template<typename T>
void AVLTree<T>::balance(NodeBT *&node) {
    //en base a la ppt de AVL;
    if (balancingFactor(node)>= 2){
        if (balancingFactor(node->left) <= -1){
            left_rota(node->left);
        }
        right_rota(node);
    }

    if (balancingFactor(node) <= -2){
        if(balancingFactor(node->right) >= 1){
            right_rota(node->right);
        }
        left_rota(node);
    }
}

template<typename T>
void AVLTree<T>::left_rota(NodeBT *&node) {
    // Como saco a node?, si node es padre de k2
    NodeBT* k2 = node->right;

    // El nuevo hijo derecho de node es el antiguo hijo izquierdo de k2
    node->right = k2->left;

    // Hijo izquierdo de k2
    k2->left = node;

    // update heights
    updateHeight(node);
    updateHeight(k2);

    // Se actualiza totalmente k2
    node = k2;

}

template<typename T>
void AVLTree<T>::right_rota(NodeBT *&k2) {
    // node = k2
    // Hijo del actual root
    NodeBT* k1 = k2 ->left;
    // Ahora, k2 tiene como hijo izq al hijo derecho de k1
    k2->left = k1->right;
    // k1 es nuevo root, el nodo pasa a ser hijo derecho
    k1 -> right = k2;
    // Actualizar alturas
    updateHeight(k2);
    updateHeight(k1);
    // Por ultimo, actualizar el root
    k2 = k1;
}


#endif