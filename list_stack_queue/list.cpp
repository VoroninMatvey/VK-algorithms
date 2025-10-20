#include <iostream>
#include <memory>

namespace details {

template <typename T> class List;

template <typename T> class Node {
  T data_ = T{};
  Node *prev_ = nullptr;
  std::unique_ptr<Node> next_ = nullptr;

  friend class List<T>;

public:
  Node(const T &data) : data_(data) {}
}; // <-- struct Node

template <typename T> class List {

  using value_type = T;
  using const_value_type = const value_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using node = Node<value_type>;
  using node_pointer = node *;
  using node_unique_ptr = std::unique_ptr<node>;

  std::size_t size_ = 0;
  node_unique_ptr head_ = nullptr;
  node_pointer tail_ = nullptr;

public:
  List() = default;

  bool empty() const { return size_ == 0; }
  std::size_t size() const { return size_; }

  void pop_front() {
    if (empty())
      return;

    if (size_ == 1) {
      node_unique_ptr deleted = std::move(head_);
      tail_ = nullptr;
    } else {
      node_unique_ptr deleted = std::move(head_);
      head_ = std::move(deleted->next_);
      head_->prev_ = nullptr;
    }
    --size_;
  }

  void pop_back() {
    if (empty())
      return;

    if (size_ == 1) {
      node_unique_ptr deleted = std::move(head_);
      tail_ = nullptr;
    } else {
      node_unique_ptr deleted = std::move(tail_->prev_->next_);
      tail_ = deleted->prev_;
    }
    --size_;
  }

  void erase(std::size_t num) {
    if (num == 0) {
      pop_front();
      return;
    } else if (num == size_ - 1) {
      pop_back();
      return;
    }

    node_pointer ptr = head_.get();
    for (std::size_t i = 0; i < num - 1; ++i) {
      ptr = ptr->next_.get();
    }

    node_unique_ptr deleted = std::move(ptr->next_);
    ptr->next_ = std::move(deleted->next_);
    ptr->next_->prev_ = ptr;
    --size_;
  }

  void push_front(const_reference data) {
    node_unique_ptr new_node_ptr = std::make_unique<node>(data);

    if (empty()) {
      tail_ = new_node_ptr.get();
    } else {
      new_node_ptr->next_ = std::move(head_);
      new_node_ptr->next_->prev_ = new_node_ptr.get();
    }

    head_ = std::move(new_node_ptr);
    ++size_;
  }

  void push_back(const_reference data) {
    node_unique_ptr new_node_ptr = std::make_unique<node>(data);

    if (empty()) {
      head_ = std::move(new_node_ptr);
      tail_ = head_.get();
    } else {
      tail_->next_ = std::move(new_node_ptr);
      tail_->next_->prev_ = tail_;
      tail_ = tail_->next_.get();
    }

    ++size_;
  }

  void insert(std::size_t num, const_reference data) {
    if (num == 0) {
      push_front(data);
      return;
    } else if (num == size_ - 1) {
      push_back(data);
      return;
    }

    node_pointer ptr = head_.get();
    for (std::size_t i = 0; i < num - 1; ++i) {
      ptr = ptr->next_.get();
    }

    node_unique_ptr new_node = std::make_unique<node>(data);
    new_node->next_ = std::move(ptr->next_);
    new_node->prev_ = ptr;
    new_node->next_->prev_ = new_node.get();
    ptr->next_ = std::move(new_node);
    ++size_;
  }

  void reverse() {
    if(size_ < 2) return;

    node_pointer head_ptr = head_.get();
    head_->prev_ = head_->next_.get();
    node_unique_ptr current = std::move(head_->next_);
    node_unique_ptr previous = std::move(head_);
    node_unique_ptr temp;

    while(current) {
        current->prev_ = current->next_.get();
        temp = std::move(previous);
        previous = std::move(current);
        current = std::move(previous->next_);
        previous->next_ = std::move(temp);
    }
    head_ = std::move(previous);
    tail_ = head_ptr;
  }

  reference middle_element() {
    if(!size_) throw std::out_of_range("empty list"); 

    node_pointer slow = head_.get(), fast = head_.get();
    while(fast && fast->next_) {
        slow = slow->next_.get();
        fast = fast->next_->next_.get();
    }
    return slow->data_;
  }

  //after using this method the list class object becomes invalid before use make_uncircular
  void make_circular() {
    head_ -> prev_ = tail_;
    tail_ -> next_ = std::move(head_);
  }

  void make_uncircular() {
    head_ = std::move(tail_->next_);
    head_->prev_ = nullptr;
  }

  bool is_circular() {
    if (size_ < 2) return false;

    node_pointer slow = head_ ? head_.get() : tail_->next_.get();
    node_pointer fast = slow->next_.get();

    while(slow != fast) {
        if(!fast || !fast->next_) 
            return false;

        slow = slow->next_.get();
        fast = fast->next_->next_.get();
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const List<T> &obj) {
    node_pointer ptr = obj.head_.get();
    while (ptr) {
      os << ptr->data_ << " ";
      ptr = ptr->next_.get();
    }
    return os;
  }

}; // <-- class List

template <typename T>
void read_data(std::size_t size, List<T>& list) {
    T cur_data;
    for(std::size_t i = 0; i < size; ++i) {
        std::cin >> cur_data;
        list.push_back(cur_data);
    }
}

} // namespace details

int main() { 
    std::cout << "enter size more than 2" << std::endl;
    std::size_t size;
    std::cin >> size;
    
    details::List<int> list;
    details::read_data(size, list);
    std::cout << "list is circular: " << std::boolalpha << list.is_circular() << std::endl;

    list.reverse();
    std::cout << "reverse list: " << list << std::endl;
    list.reverse();

    int mid = list.middle_element();
    std::cout << "middle element: " << mid << std::endl;

    list.erase(size/2);
    --size;
    std::cout << "list without middle element: " << list << std::endl;

    list.erase(0);
    --size;
    std::cout << "list without first element: " << list << std::endl;

    std::cout << "close list" << std::endl;
    list.make_circular(); // list invalid
    std::cout << "list is circular: " << std::boolalpha << list.is_circular() << std::endl;
    list.make_uncircular();
}