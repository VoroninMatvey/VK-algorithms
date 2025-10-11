#include <iostream>
#include <vector>

namespace details {

template <typename T>
void sorted(std::vector<T>& vec) {
    int left = 0, right = vec.size() -1;

    while(left < right) {
        if(vec[left] == 0) {
            ++left;
        } else {
            std::swap(vec[left], vec[right]);
            --right;
        }
    }
}
template <typename T>
void reading_data(std::vector<T>& data, int size) {
    for(int k = 0; k < size; ++k) std::cin >> data[k];
}

template <typename T>
void print_vector(const std::vector<T>& vec) {
    for(const auto& element : vec) std::cout << element << " ";
    std::cout << std::endl;
}

} // <-- namespace details

int main() {

    int size;
    std::cin >> size;
    std::vector<int> vec(size);
    details::reading_data(vec, size);
    details::sorted(vec);
    details::print_vector(vec);
}