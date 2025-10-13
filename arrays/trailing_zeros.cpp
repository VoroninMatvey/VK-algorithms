#include <iostream>
#include <vector>

namespace details {

template <typename T>
void end_move_zeros(std::vector<T>& vec) {
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
    details::end_move_zeros(vec);
    details::print_vector(vec);
}