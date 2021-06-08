#pragma once

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
#include <iostream>
#include <algorithm>

namespace ariel {
    template<typename T>
    class BinaryTree {
    private:

        // inner class
        struct Node {
            T val;
            bool _is_left;
            Node *right;
            Node *left;
            Node *father;

            Node(const T &v, Node *n_f, bool is_left = false)
                    : val(v), father(n_f), right(nullptr), left(nullptr), _is_left(is_left) {
            }
        };

        // fields
        Node *root;

        explicit BinaryTree(const T &v) {
            root = new Node(v, nullptr);
        }

        void copy_tree(Node *&r, const BinaryTree &b) {
            if (r->left != nullptr) {
                this->add_left(r->val, r->left->val);
                copy_tree(r->left, b);
            }
            if (r->right != nullptr) {
                this->add_left(r->val, r->right->val);
                copy_tree(r->right, b);
            }

        }

        void delete_tree(Node *&r) {
            if (r) {
                if (r->left != nullptr) {
                    delete_tree(r->left);
                }
                if (r->right != nullptr) {
                    delete_tree(r->right);
                }
                if (r->left == nullptr && r->right == nullptr) {
                    delete r;
                    r = nullptr;
                }
            }

        }

    public:
        //defult constructor
        BinaryTree() {
            root = nullptr;
        }

        //move constructor
        BinaryTree(BinaryTree &&other) noexcept {
            root = other.root;
            other.root = nullptr;
        }

        //copy constructor- deep copy
        BinaryTree(const BinaryTree &b) {
            root = nullptr;
            if (b.root == nullptr) {
                return;
            }
            add_root(b.root->val);
            copy_tree(root, b);
        }

        //destructor
        ~ BinaryTree() {
            delete_tree(root); //delete all!!
        }

        //move operator =
        BinaryTree &operator=(BinaryTree &&other) noexcept {
            if (this->root != other.root) {
                if (root) {
                    // delete *this;
                }
                root = other.root;
                other.root = nullptr;
            }
            return *this;
        }

        //operator = deep copy
        BinaryTree &operator=(const BinaryTree &b) {
            if (this->root != b.root) {
                if (root)//not empty
                {
                    // ~BinaryTree<T>();//delete this?
                }
                root = nullptr;
                if (b.root == nullptr) {
                    return *this;
                }
                add_root(b.root->val);
                copy_tree(root, b);

            }
            return *this;
        }

        BinaryTree<T> &add_root(const T &val) {
            if (root == nullptr) {
                *this = BinaryTree{val};
            } else {
                root->val = val;
            }
            return *this;
        }

        BinaryTree<T> &add_left(const T &val_father, const T &val) {
            // auto itr = std::find(begin(), end(), val_father);
            auto itr = begin_preorder();
            auto end = end_preorder();
            for (; itr != end; ++itr) {
                if (*itr == val_father) {
                    break;
                }
            }
            if (itr != end) {

                if (itr.get_pointer()->left == nullptr) {
                    itr.get_pointer()->left = new Node{val, itr.get_pointer(), true};
                } else {
                    itr.get_pointer()->left->val = val;
                }

            } else {
                throw std::invalid_argument{"Error. no such node exist."};

            }
            return *this;
        }

        BinaryTree<T> &add_right(const T &val_father, const T &val) {
            // auto itr = std::find(begin(), end(), val_father);
            auto itr = begin_preorder();
            auto end = end_preorder();

            for (; itr != end; ++itr) {
                if (*itr == val_father) {
                    break;
                }
            }
            if (itr != end) {

                if (itr.get_pointer()->right == nullptr) {
                    itr.get_pointer()->right = new Node{val, itr.get_pointer()};
                } else {
                    itr.get_pointer()->right->val = val;
                }

            } else {
                throw std::invalid_argument{"Error. no such node exist."};

            }
            return *this;
        }

        //----------------------------------
        // friend global IO operators
        //----------------------------------
        friend std::ostream &operator<<(std::ostream &output, const BinaryTree &binary_tree) {
            return (output << "hello");
        }


        //-------------------------------------------------------------------
        // iterator related code:
        // inner class and methods that return instances of it)
        //-------------------------------------------------------------------
        class iterator {

//            using iterator_category = std::forward_iterator_tag;
//            using difference_type = std::ptrdiff_t;
//            using value_type = T;
//            using pointer = T *;  // or also value_type*
//            using reference = T &;  // or also value_type&

        protected:
            Node *pointer_to_current_node;
            Node *root;

        public:
            Node *&get_pointer() {
                return pointer_to_current_node;
            }

            explicit iterator(Node *ptr = nullptr)
                    : pointer_to_current_node(ptr), root(ptr) {
            }

            // Note that the method is const as this operator does not
            // allow changing of the iterator.
            // Note that it returns T& as it allows to change what it points to.
            // A const_iterator class will return const T&
            // and the method will still be const
            T &operator*() const {
                //return *pointer_to_current_node;
                return pointer_to_current_node->val;
            }

            T *operator->() const {
                return &(pointer_to_current_node->val);
            }

            bool operator==(const iterator &rhs) const {
                return pointer_to_current_node == rhs.pointer_to_current_node;
            }

            bool operator!=(const iterator &rhs) const {
                return pointer_to_current_node != rhs.pointer_to_current_node;
            }
        };  // END OF CLASS ITERATOR

        class iterator_preorder : public iterator {
        public:
            explicit iterator_preorder(Node *ptr = nullptr) : iterator(ptr) {}

            // ++i;
            virtual iterator_preorder operator++() {
                if (this->pointer_to_current_node)//if not nullptr
                {
                    if (this->pointer_to_current_node->left)//if has left
                    {
                        this->pointer_to_current_node = this->pointer_to_current_node->left;

                    } else if (this->pointer_to_current_node->right)//if has
                    {
                        this->pointer_to_current_node = this->pointer_to_current_node->right;

                    } else//doesn't have sons
                    {
                        while (this->pointer_to_current_node != this->root) {//while left son
                            bool is_left = this->pointer_to_current_node->_is_left;
                            this->pointer_to_current_node = this->pointer_to_current_node->father;
                            if (is_left && this->pointer_to_current_node->right) {
                                this->pointer_to_current_node = this->pointer_to_current_node->right;
                                return *this;
                            }
                        }

                        this->pointer_to_current_node = nullptr;


                    }
                }
                return *this;

            }


            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual iterator_preorder operator++(int) {
                iterator_preorder tmp = *this;
                ++(*this);
                return tmp;
            }


        };  // END OF CLASS ITERATOR_PREORDER
        class iterator_inorder : public iterator {

        public:

            explicit iterator_inorder(Node *ptr = nullptr) : iterator(ptr) {
                if (this->pointer_to_current_node) {//move to the right location of the first.
                    while (this->pointer_to_current_node->left)//has left
                    {
                        this->pointer_to_current_node = this->pointer_to_current_node->left;//go left
                    }
                }
            }


            // ++i;
            //https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
            iterator_inorder &operator++() {

                if (this->pointer_to_current_node)//not end
                {
                   if (this->pointer_to_current_node->right)//has right
                    {
                        //move one step right
                        this->pointer_to_current_node = this->pointer_to_current_node->right;
                        //move left as much as possibale
                        while (this->pointer_to_current_node->left) {
                            this->pointer_to_current_node = this->pointer_to_current_node->left;
                        }
                    } else {
                        //move up, skiped one left step
                        bool is_left;
                        do {
                            is_left = this->pointer_to_current_node->_is_left;
                            this->pointer_to_current_node = this->pointer_to_current_node->father;
                        } while (!is_left);
                        if (this->root==this->pointer_to_current_node){
                            this->pointer_to_current_node=nullptr;
                        }

                    }
                }
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual iterator_inorder operator++(int) {
                iterator_inorder tmp = *this;
                ++(*this);
                return tmp;
            }


        };  // END OF CLASS ITERATOR_INORDER
        class iterator_postorder : public iterator {
        public:

            explicit iterator_postorder(Node *ptr = nullptr) : iterator(ptr) {}


            // ++i;
            virtual iterator_postorder &operator++() {

                if (this->pointer_to_current_node) {
                    this->pointer_to_current_node = this->pointer_to_current_node->left;
                    // return iterator_preorder{nullptr};
                }
                return *this;

            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual iterator_postorder operator++(int) {
                iterator_postorder tmp = *this;
                if (this->pointer_to_current_node) {
                    this->pointer_to_current_node = this->pointer_to_current_node->left;
                    // return iterator_preorder{nullptr};
                }
                return tmp;

            }
        };  // END OF CLASS ITERATOR_POSTORDER
        // class const_iterator_inorder {

        // protected:
        //     Node *pointer_to_current_node;

        // public:

        //     const_iterator_inorder(Node *ptr = nullptr)
        //             : pointer_to_current_node(ptr) {
        //     }

        //     // Note that the method is const as this operator does not
        //     // allow changing of the iterator.
        //     // Note that it returns T& as it allows to change what it points to.
        //     // A const_iterator class will return const T&
        //     // and the method will still be const
        //     const T &operator*() const {
        //         //return *pointer_to_current_node;
        //         return pointer_to_current_node->m_value;
        //     }

        //     const T *operator->() const {
        //         return &(pointer_to_current_node->m_value);
        //     }


        //     // ++i;
        //     const const_iterator_inorder &operator++() {
        //         //++pointer_to_current_node;
        //         this->pointer_to_current_node = this->pointer_to_current_node->m_next;
        //         return *this;
        //     }

        //     // i++;
        //     // Usually iterators are passed by value and not by const& as they are small.
        //     const const_iterator_inorder operator++(int) {
        //         const_iterator_inorder tmp = *this;
        //         this->pointer_to_current_node = this->pointer_to_current_node->m_next;
        //         return tmp;
        //     }

        //     bool operator==(const iterator &rhs) const {
        //         return pointer_to_current_node == rhs.pointer_to_current_node;
        //     }

        //     bool operator!=(const iterator &rhs) const {
        //         return pointer_to_current_node != rhs.pointer_to_current_node;
        //     }
        // };  // END OF CLASS ITERATOR

        iterator_preorder begin_preorder() {
            return iterator_preorder{root};
        }

        iterator_preorder end_preorder() {
            return iterator_preorder{nullptr};
        }

        iterator_inorder begin_inorder() {
            return iterator_inorder{root};
        }

        iterator_inorder end_inorder() {
            return iterator_inorder{nullptr};
        }

        iterator_inorder begin() {
            return begin_inorder();
        }

        iterator_inorder end() {
            return end_inorder();
        }

        iterator_postorder begin_postorder() {
            return iterator_postorder{root};
        }

        iterator_postorder end_postorder() {
            return iterator_postorder{nullptr};
        }

        // const_iterator_inorder cbegin() const {
        //     return const_iterator_inorder{root};
        // }

        // const_iterator_inorder cend() const {
        //     return const_iterator_inorder{nullptr};
        // }



    };
}