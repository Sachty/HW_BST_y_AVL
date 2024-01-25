#include <iostream>
using namespace std;

#include "bst.h"
#include "avl.h"

int main() {
    cout << "\n\nProbando funciones de BST" << endl;
    BSTree<int> bst;

    // Insertar elementos
    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert( 1);
    bst.insert( 6);
    bst.insert( 4);
    bst.insert( 7);
    bst.insert( 14);
    bst.insert( 13);


    cout << "Recorrido BFS: ";
    bst.BFS();

    cout << "Recorrido DFS: ";
    bst.DFS();

    cout << "Recorrido Preorder: ";
    bst.Preorder();

    cout << "Recorrido PostOrder: ";
    bst.Postorder();

    cout << "Recorrido Inorder: ";
    bst.Inorder();

    cout << "Altura del arbol: " << bst.height(bst.root) << endl;

    cout << "Valor Minimo: " << bst.minValue(bst.root) << endl;
    cout << "Valor Maximo: " << bst.maxValue(bst.root) << endl;

    int valFind = 3;
    cout << "Esta " << valFind << " en el arbol " << (bst.find(bst.root, valFind) ? "Si" : "No") << endl;

    int valR = 6;
    cout << "Remover " << valR  << endl;
    bst.remove(valR);

    cout << "Recorrido BFS con el nodo eliminado: ";
    bst.BFS();

    int valS = 3;
    cout << "Sucesor de " << valS << ": " << bst.successor(valS) << endl;

    int valP = 3;
    cout << "Precesor de " << valP << ": " << bst.predecessor(valP) << endl;


    //------------------------------------------------------------------------------
    cout << "\n\nProbando funciones de AVL" << endl;
    AVLTree<int> avlTree;

    // Insertar elementos en el árbol
    avlTree.insert(50);
    avlTree.insert(30);
    avlTree.insert(70);
    avlTree.insert(20);
    avlTree.insert(40);
    avlTree.insert(60);
    avlTree.insert(80);

    // Mostrar el árbol en preorden
    cout << "Arbol AVL en preorden: " << avlTree.getPreOrder() << endl;
    cout << "Arbol AVL en inorder: " << avlTree.getInOrder() << endl;
    cout << "Arbol AVL en postorden: " << avlTree.getPostOrder() << endl;

    // Verificar si un elemento está presente
    cout << "El elemento 40 esta presente: " << (avlTree.find(40) ? "Sí" : "No") << endl;

    // Obtener la altura del árbol
    cout << "Altura del arbol AVL: " << avlTree.height() << endl;

    // Obtener el valor mínimo y máximo en el árbol
    cout << "Valor minimo en el arbol AVL: " << avlTree.minValue() << endl;
    cout << "Valor maximo en el arbol AVL: " << avlTree.maxValue() << endl;

    // Verificar si el árbol está balanceado
    cout << "El arbol AVL está balanceado :" << (avlTree.isBalanced() ? "Si" : "No") << endl;

    // Obtener el tamaño del árbol
    cout << "Tamanio del arbol AVL: " << avlTree.size() << endl;

    // Eliminar un elemento del árbol
    avlTree.remove(40);

    // Mostrar el árbol de manera visual
    cout << "Representacion visual del árbol AVL:" << endl;
    avlTree.displayPretty();

    return 0;
}
