#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <deque>
#include <queue>

namespace details {    

    template<typename KeyT>
    struct Node {
        
        using pointer = Node<KeyT>*;
        using const_pointer = const Node<KeyT>*;
        using unique_ptr = std::unique_ptr<Node<KeyT>>;

        const KeyT key_;
        unique_ptr left_, right_;
    
        explicit Node(const KeyT& key = {}) :
            key_{key},
            left_{nullptr}, right_{nullptr} {};

        const_pointer minimum() const { 
            auto val = this;

            while(val->left_) {
                val = val->left_.get();
            }
            return val;
        }
    
        const_pointer maximum() const { 
            auto val = this;

            while(val->right_) {
                val = val->right_.get();
            } 
            return val;
        }
    
    }; // <--struct Node

    template <typename KeyT>
    std::unique_ptr<Node<KeyT>> buildTree(const std::vector<KeyT>& vec, std::size_t i = 0) {
        if(i >= vec.size()) return nullptr;

        auto root_ptr = std::make_unique<Node<KeyT>>(vec[i]);
        root_ptr->left_ = buildTree(vec, 2 * i + 1);
        root_ptr->right_ = buildTree(vec, 2 * i + 2);

        return root_ptr;
    }

    template <typename KeyT>
    bool isSymetric_w(Node<KeyT>* root) {
        if (!root) return true;

        std::deque<Node<KeyT>*> deque;
        deque.push_back(root);
        int counter = 1;

        while(deque.size()) {
            if(!is_palyndrom(deque))
                return false;
            
            counter = deque.size();
            while (counter > 0) {
                if (deque[0]) {
                        deque.push_back(deque[0]->left_.get());
                        deque.push_back(deque[0]->right_.get());
                } 
                deque.pop_front();
                --counter;
            }
        }
        return true;
    }

    template <typename KeyT>
    void deptSearch(Node<KeyT>* root, std::vector<KeyT>& vec) {
        if(!root) return;

        deptSearch(root->left_.get(), vec);
        vec.push_back(root->key_);
        deptSearch(root->right_.get(), vec);
    }

    template <typename KeyT>
    bool isSymetric_d(Node<KeyT>* root) {
        if(!root) return true;
        std::vector<KeyT> vec;

        deptSearch(root, vec);
        int j = vec.size() - 1;
        for(int i = 0; i < vec.size() / 2; ++i) {
            if(vec[i] != vec[j]) {
                return false;
            }
            --j;
        }
    }

    template <typename KeyT>
    int minDepth(Node<KeyT>* root) {
        if(!root) 
            return 0;

        int depth = 1, counter = 0;
        std::queue<Node<KeyT>*> queue;
        queue.push(root);

        while(!queue.empty()) {
            counter = queue.size();

            while(counter > 0) {
                Node<KeyT> *left, *right;
                left = queue.front()->left_.get();
                right = queue.front()->right_.get();

                if(!left && !right) return depth;
                if(!left) {
                    queue.push(right);
                } else if (!right) {
                    queue.push(left);
                } else {
                    queue.push(right);
                    queue.push(left);
                }
                queue.pop();
                --counter;
            }
            ++depth;
        }
        return depth;
    }

    //only makes sense for a search tree
    template <typename KeyT>
    int multiplication(Node<KeyT>* root) {
        int min = root->minimum()->key_;
        int max = root->maximum()->key_;
        return min * max;
    }

    template <typename KeyT>
    bool trees_are_equal(Node<KeyT>* root1, Node<KeyT>* root2) {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;

        if(root1->key_ != root2->key_)
            return false;

        return trees_are_equal(root1->left_.get(), root2->left_.get())&&trees_are_equal(root1->right_.get(), root2->right_.get());
    }

    template <typename T>
    bool is_palyndrom(std::deque<Node<T>*>& deque) {
        int size = deque.size();
        if(size == 1 || size == 0) return true;

        for(int i = 0; i < size / 2; ++i) {
            if (deque[i] == nullptr && deque[size - i - 1 ] == nullptr) {
                continue;
            } else if (deque[i] == nullptr || deque[size - i - 1] == nullptr) {
                return false;
            } else if (deque[i]->key_ != deque[size - i - 1]->key_) { 
                return false;
            }
        }
        return true;
    }

    template <typename T>
    void reading_data(std::vector<T>& data) {
        int size = data.size();
        for(int k = 0; k < size; ++k) std::cin >> data[k];
    }

    template <typename KeyT>
    void printTree(const Node<KeyT>* node, int level = 0, const std::string& prefix = "", bool isLeft = true) {
        if (!node) return;
        
        printTree(node->right_.get(), level + 1, prefix + (isLeft ? "│   " : "    "), false);
        
        std::cout << prefix;
        std::cout << (isLeft ? "└── " : "┌── ");
        std::cout << node->key_ << std::endl;
        
        printTree(node->left_.get(), level + 1, prefix + (isLeft ? "    " : "│   "), true);
    }

    }  // <-- namespace details

int main() {
    std::cout << "Task1: tree building" << std::endl;
    std::cout << "Enter size of second array" << std::endl;
   int size;
   std::cin >> size;
   std::vector<int> vec(size);
   std::cout << "Enter array" << std::endl;
   details::reading_data(vec);

   auto uniq_ptr = details::buildTree(vec);
   std::cout << "Built tree" << std::endl;
   details::printTree(uniq_ptr.get());
   std::cout << std::endl<< std::endl;

   std::cout << "Task2: Tree is symetric" << std::endl;
   std::cout <<  "Tree is symetric: "<< std::boolalpha << details::isSymetric_w(uniq_ptr.get()) << std::endl;
   details::minDepth(uniq_ptr.get());
   std::cout << std::endl<< std::endl;

   std::cout << "Task3: minimum depth of tree" << std::endl;
   std::cout << "Minimum depth of tree: " << details::minDepth(uniq_ptr.get());
   std::cout << std::endl<< std::endl;

   std::cout << "Task4: multiplication" << std::endl;
   std::cout << "result: " << details::multiplication(uniq_ptr.get());
   std::cout << std::endl<< std::endl;

   std::cout << "Task5: equality of trees" << std::endl;
   std::cout << "Enter size of second array" << std::endl;
   int size2;
   std::cin >> size2;
   std::vector<int> vec2(size2);
   std::cout << "Enter array" << std::endl;
   details::reading_data(vec2);
   auto uniq_ptr2 = details::buildTree(vec2);
   std::cout << "Trees are equal: " << std::boolalpha << details::trees_are_equal(uniq_ptr.get(), uniq_ptr2.get());

}   