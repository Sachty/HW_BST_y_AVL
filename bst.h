#include "iostream"
#include <queue>
#include <stack>
using namespace std;

/*
Métodos de BST
- Insert // inserta nodos al BST
- Remove // remueve un nodo especifico en el BST
- Height // altura del árbol
- MinValue // encuentra el nodo de mínimo valor en el BST
- MaxValue // encuentra el nodo de máximo valor en el BST
- Find // verifica la existencia de un nodo especifico en el BST
- Preorder // recorre el BST a través de Preorder
- Postorder // recorre el BST a través de Postorder
- Inorder // recorre el BST a través de Inorder
- BFS // recorre el BST a través de BFS
- DFS // recorre el BST a través de DFS
- FindNode // devuelve un nodo especifico en el BST
- Successor // Indica el valor del nodo sucesor de cierto nodo en el BST
- Predeccessor // Indica el valor del nodo predecesor de cierto nodo en el BST
 - Clear // Limpia todo el BST
*/
template <typename T>
class BSTree {
private:
    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;

        NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    NodeBT* insert(NodeBT* root,T value){
        if (root == nullptr) {
            return new NodeBT(value);
        }

        if (value < root->data) {
            root->left = insert(root->left, value);
        } else if (value > root->data) {
            root->right = insert(root->right, value);
        }

        return root;
    }

    NodeBT* remove(NodeBT* root, T value){
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = remove(root->left, value);
        } else if (value > root->data) {
            root->right = remove(root->right, value);
        } else {
            if (root->left == nullptr) {
                NodeBT* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                NodeBT* temp = root->left;
                delete root;
                return temp;
            }

            root->data = minValue(root->right);

            root->right = remove(root->right, root->data);
        }
        return root;
    }

    void clear(NodeBT* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);

        delete node;
    }

    void Preorder(NodeBT* node) {
        if (node == NULL)
            return;

        cout << node->data << " ";
        Preorder(node->left);
        Preorder(node->right);
    }

    void Inorder(NodeBT* node) {
        if (node == NULL)
            return;

        Inorder(node->left);
        cout << node->data << " ";
        Inorder(node->right);
    }

    void Postorder(NodeBT* node) {
        if (node == NULL)
            return;

        Postorder(node->left);
        Postorder(node->right);
        cout << node->data << " ";
    }

public:
    NodeBT *root;
    BSTree() : root(nullptr) {}
    void insert(T value) {
        root = insert(root, value);
    }

    void remove(T value) {
        root = remove(root, value);
    }

    int height(NodeBT* root) {
        if (root == nullptr) {
            return 0;
        }
        int lh = height(root->left);
        int rh = height(root->right);
        return 1 + max(lh, rh);
    }

    T minValue(NodeBT* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->data;
    }

    T maxValue(NodeBT* root) {
        while (root->right != nullptr) {
            root = root->right;
        }
        return root->data;
    }

    bool find(NodeBT* node, T value){
        if(node == nullptr)
            return false;
        else if(value < node->data)
            return find(node->left, value);
        else if(value > node->data)
            return find(node->right, value);
        else return true;
    }

    void Preorder() {
        Preorder(root);
        cout << endl;
    }

    void Postorder() {
        Postorder(root);
        cout << endl;
    }

    void Inorder() {
        Inorder(root);
        cout << endl;
    }

    void BFS() const {
        if (root == nullptr) {
            return;
        }

        queue<NodeBT*> q;
        q.push(root);

        while (!q.empty()) {
            NodeBT* current = q.front();
            cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }

            q.pop();
        }
        cout << endl;
    }

    void DFS(){
        stack<NodeBT*> s;
        s.push(root);

        while (!s.empty()) {
            NodeBT* current = s.top();
            cout << current->data << " ";
            s.pop();

            if (current->right != nullptr) {
                s.push(current->right);
            }

            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        cout << endl;
    }

    NodeBT* findNode(NodeBT* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return findNode(node->left, value);
        } else {
            return findNode(node->right, value);
        }
    }

    T successor(T value) {
        NodeBT* node = findNode(root, value);
        if (node == nullptr) {
            throw logic_error("No está el valor en el árbol");
        }

        if (node->right != nullptr) {
            return minValue(node->right);
        }

        NodeBT* succ = nullptr;
        NodeBT* current = root;

        while (current != nullptr) {
            if (value < current->data) {
                succ = current;
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                break;
            }
        }

        if (succ == nullptr) {
            throw logic_error("No hay sucesor");
        }

        return succ->data;
    }

    T predecessor(T value) {
        NodeBT* node = findNode(root, value);
        if (node == nullptr) {
            throw logic_error("No está el valor en el árbol");
        }

        if (node->left != nullptr) {
            return maxValue(node->left);
        }

        NodeBT* pred = nullptr;
        NodeBT* current = root;

        while (current != nullptr) {
            if (value > current->data) {
                pred = current;
                current = current->right;
            } else if (value < current->data) {
                current = current->left;
            } else {
                break;
            }
        }

        if (pred == nullptr) {
            throw logic_error("No hay precedor");
        }

        return pred->data;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }


};

