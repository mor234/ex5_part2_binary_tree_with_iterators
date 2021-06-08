#pragma once
namespace ariel {
    template<typename T>
    class BinaryTree {
    private:

        // inner class
        struct Node {
            T val;
            bool is_left;
            Node *right;
            Node *left;
            Node *father;

            Node(const T &v, Node *n_r, Node *n_l, Node *n_f)
                    : m_value(v), father(n_f), m_right(n_r), m_left(n_l),is_left(false) {
            }
        };

        // fields
        Node *root;

        BinaryTree(const T &v, const Node *&node) {
            node = new Node(v, nullptr, nullptr, nullptr);
        }

        void copy_tree(const Node *&r, const BinaryTree &b) {
            if (r->left != nullptr) {
                b.add_left(r->val, r->left->val);
                copy_tree(r->left, b);
            }
            if (r->right != nullptr) {
                b.add_left(r->val, r->right->val);
                copy_tree(r->right, b);
            }

        }

        void delete_tree(Node *&r) {
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

    public:
        //defult constructor
        BinaryTree() {
            root = nullptr;
        }

        //move constructor
        BinaryTree(BinaryTree &&other) {
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
            copy_tree(root, r);
        }

        //destructor
        ~ BinaryTree() {
            delete_tree(root); //delete all!!
        }

        //move operator =
        void operator=(BinaryTree &&other) {
            if (this.root != other.root) {
                if (root) {
                    ~BinaryTree();//delete this?
                }
                root = other.root;
                other.root = nullptr;
            }
        }

        //operator = deep copy
        BinaryTree &operator=(const BinaryTree &b) {
            if (this.root != other.root) {
                if (root)//not empty
                {
                    ~BinaryTree();//delete this?
                }
                root = nullptr;
                if (b.root == nullptr) {
                    return;
                }
                add_root(b.root->val);
                copy_tree(root, r);

            }
        }

        BinaryTree<T> &add_root(const T &val) {
            if (root == nullptr) {
                BinaryTree{val, root};
            } else {
                root->val = T;
            }
            return *this;
        }

        BinaryTree<T> &add_left(const T &val_father, const T &val) {
            auto itr = find(begin(), end(), val_father);
            if (itr != end()) {
                if (itr++ == nullptr) {
                    *itr.left = new Node{val, &(*itr)}
                } else {
                    *itr
                }

            } else {
                throw invalid_argument{"Error. no such node exist."};

            }
            return *this;
        }

        BinaryTree<T> &add_right(const T &val_father, const T &val) {
            return *this;
        }

        //----------------------------------
        // friend global IO operators
        //----------------------------------
        friend std::ostream &operator<<(std::ostream &output, const BinaryTree &binary_tree) {
            return (output << "hello");
        }


    public:

        //-------------------------------------------------------------------
        // iterator related code:
        // inner class and methods that return instances of it)
        //-------------------------------------------------------------------
        class iterator {

        protected:
            Node *pointer_to_current_node;

        public:

            iterator(Node *ptr = nullptr)
                    : pointer_to_current_node(ptr) {
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
                return &(pointer_to_current_node->m_value);
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
            iterator_preorder(Node *ptr = nullptr) : iterator(ptr) {}

            // ++i;
            virtual iterator_preorder &operator++() {
                if(this)
                ++this->pointer_to_current_node;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return *this;
                // return iterator_preorder{nullptr};

            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual const iterator_preorder operator++(int) {
                iterator_preorder tmp = *this;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return tmp;
                // return iterator_preorder{nullptr};

            }


        };  // END OF CLASS ITERATOR_PREORDER
        class iterator_inorder : public iterator {

        public:

            iterator_inorder(Node *ptr = nullptr) : iterator(ptr) {}


            // ++i;
            virtual iterator_inorder &operator++() {
                if (this->pointer_to_current_node->)
                    ++this->pointer_to_current_node;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return *this;
                // return iterator_inorder{nullptr};
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual const iterator_inorder operator++(int) {
                iterator_inorder tmp = *this;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return tmp;
                // return iterator_inorder{nullptr};

            }


        };  // END OF CLASS ITERATOR_INORDER
        class iterator_postorder : public iterator {
        public:

            iterator_postorder(Node *ptr = nullptr) : iterator(ptr) {}


            // ++i;
            virtual iterator_postorder &operator++() {
                ++this->pointer_to_current_node;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return *this;
                // return iterator_postorder{nullptr};

            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            virtual const iterator_postorder operator++(int) {
                iterator_postorder tmp = *this;
                this->pointer_to_current_node = this->pointer_to_current_node->m_next;
                return tmp;
                // return iterator_postorder{nullptr};

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

        ~BinaryTree() {
            if (root != nullptr) {
                delete root;
            }
        }


    };
}