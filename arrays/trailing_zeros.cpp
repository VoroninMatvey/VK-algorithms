#include <iostream>
#include <vector>

namespace details {

//moving zeros to the end without preserving the order of non-zeros
template <typename T>
void end_move_zeros_extra(std::vector<T>& vec) {
    int reverse_it = vec.size() - 1, it = 0;

    while(it < reverse_it) {
        if(vec[it] == 0) {
            std::swap(vec[it], vec[reverse_it]);
            --reverse_it;
        } else {
            ++it;
        }
    }
}

//moving zeros to the end while preserving the order of non-zeros
// [0: non_zero_pl -1] - non zero number
// [non_zero_pl: it - 1] - zero
// [it: size - 1] - research area
template <typename T>
void end_move_zeros(std::vector<T>& vec) {
    int non_zero_pl = 0, it = 0;

    while(it < vec.size()) {
        if(vec[it] != 0) {
            std::swap(vec[non_zero_pl], vec[it]);
            ++it; ++non_zero_pl;
        } else {
            ++it;
        }
    }
}

template <typename T>
void print_vector(const std::vector<T>& vec) {
    for(const auto& element : vec) std::cout << element << " ";
    std::cout << std::endl;
}

template <typename T>
void reading_data(std::vector<T>& data) {
    int size = data.size();
    for(int k = 0; k < size; ++k) std::cin >> data[k];
}

} // <-- namespace details

int main() {

    int size;
    std::cin >> size;
    std::vector<int> vec(size);
    details::reading_data(vec);
    std::vector<int> vec_copy = vec;

    std::cout << "the resulting array with unordered non-zero numbers" << std::endl;
    details::end_move_zeros_extra(vec);
    details::print_vector(vec);

    std::cout << "the resulting array with ordered non-zero numbers" << std::endl;
    details::end_move_zeros(vec_copy);
    details::print_vector(vec_copy);
}