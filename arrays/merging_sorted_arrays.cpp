#include <iostream>
#include <vector>

namespace details {

template <typename T>
std::vector<T> merging(const std::vector<T>& vec1, const std::vector<T>& vec2) {
    std::vector<T> result_vec(vec1.size() + vec2.size());
    int left1 = 0, left2 = 0, used = 0;
    while((left1 < vec1.size()) && (left2 < vec2.size())) {
        if(vec1[left1] > vec2[left2]) {
            result_vec[used] = vec2[left2];
            ++left2, ++used;
        } else {
            result_vec[used] = vec1[left1];
            ++left1, ++used;
        }
    } 

    while(left2 < vec2.size()) {
        result_vec[used] = vec2[left2];
        ++left2, ++used;
    }

    while(left1 < vec1.size()) {
        result_vec[used] = vec1[left1];
        ++left1, ++used;
    }
    
    return result_vec;
}

template <typename T>
void reading_data(std::vector<T>& data, int size) {
    for(int k = 0; k < size; ++k) std::cin >> data[k];
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
void print_vector(const std::vector<T>& vec) {
    for(const auto& element : vec) std::cout << element << " ";
    std::cout << std::endl;
}

} // <-- namespace details

int main() {

    int size1, size2;
    std::cin >> size1 >> size2;
    std::vector<int> vec1(size1), vec2(size2);
    details::reading_data(vec1, size1);
    details::reading_data(vec2, size2);

    if(details::is_sorted(vec1) && details::is_sorted(vec2)) {
        std::vector<int> result_vec = details::merging(vec1, vec2);
        details::print_vector(result_vec);
    } else {
        std::cout << "arrays unsorted" << std::endl;
    }
}