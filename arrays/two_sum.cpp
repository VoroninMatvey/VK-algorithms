#include <iostream>
#include <vector>

namespace details { 

template <typename T>
std::pair<int, int> two_sum(const std::vector<T>& vec, T target) {
    if(vec.size() == 0) 
        throw std::runtime_error("Vector is empty");

    int left = 0, right = vec.size() - 1;

    while(left != right) {
        if(vec[left] + vec[right] < target) { 
            ++left;
        } else if(vec[left] + vec[right] > target) {
            --right;
        } else return std::make_pair(left, right);
    }
    return std::make_pair(-1, -1);
}

template <typename T>
bool is_sorted(const std::vector<T>& vec) {
    if(vec.size() == 0) return true;
    T cur_max_val = vec[0];

    for(const auto& element : vec) {
        if(cur_max_val > element) {
            return false;
        } 
        cur_max_val = element;
    }
    return true;
}

template <typename T>
void reading_data(std::vector<T>& data, std::size_t size) {
    for(int k = 0; k < size; ++k) std::cin >> data[k];
}

} // <-- namespace details

int main() {
    int size, target;
    std::cin >> size >> target;
    std::vector<int> vec(size);
    std::pair<int,int> pair;
    details::reading_data(vec, size);

    if(details::is_sorted(vec)) {
        pair = details::two_sum(vec, target);
    } else {
        std::cout << "Array is not sorted" << std::endl;
        return 0;
    }

    if(pair.first == -1) {
        std::cout << "There are no such numbers" << std::endl;
    } else std::cout << pair.first << " " << pair.second << std::endl;
}