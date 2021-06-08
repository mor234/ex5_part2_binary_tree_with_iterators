/**
 * Demo file for the exercise on binary tree
 *
 * @author mor234
 * @since 2021-06
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#include "BinaryTree.hpp"

using namespace ariel;

template<typename T>
void display_b_tree(BinaryTree<T> &tree) {
    cout << tree << endl;
    cout << " pre order: ";
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << " in order: ";
    for (auto it = tree.begin_inorder(); it != tree.end_inorder(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << " post order: ";
    for (auto it = tree.begin_postorder(); it != tree.end_postorder(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << " in order- default: ";
    for (T element: tree) {  // this should work like inorder
        cout << element << " ";
    }
    cout << endl;

}


int main() {
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(1.7)
            .add_left(1.7, 2)      // Now 9 is the left child of 1
            .add_left(1.7, 3.5)      // Now 4 is the left child of 9
            .add_right(3.5, 6)     // Now 5 is the right child of 9
            .add_right(6, 8)     // Now 3 is the right child of 1
            .add_right(3.5, 4).add_left(8, 5).add_right(8,
                                                        -35.7);     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
    cout << " double tree: \n";
    display_b_tree(tree_of_doubles);


    // The same should work with other types, e.g. with strings:

    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("my")
            .add_left("my", "name")
            .add_left("name", "is")
            .add_right("name", "moriya")
            .add_right("my", " :)");
    cout << "\n strings tree: \n";
    display_b_tree(tree_of_strings);
    // demonstrate the arrow operator:
    cout <<endl<< " demonstrate -> of iterator: ";
    for (auto it = tree_of_strings.begin_postorder(); it != tree_of_strings.end_postorder(); ++it) {
        cout << " \"" << (*it) << "\"" << " length is " << it->size() << endl;
    }

}
