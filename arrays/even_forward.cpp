#include <iostream>
#include <vector>

namespace details {

template <typename T>
void print_vector(const std::vector<T>& vec) {
    for(const auto& element : vec) std::cout << element << " ";
    std::cout << std::endl;
}

template <typename T>
void sorted(std::vector<T>& vec) {
    int even_place = 0, it = 0;

    while(it < vec.size()) {
        if(vec[it] % 2 == 1) {
            ++it;
        } else {
            std::swap(vec[it], vec[even_place]);
            ++it; ++even_place;
        }
    }
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
    details::sorted(vec);
    details::print_vector(vec);
}