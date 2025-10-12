#include <iostream>
#include <vector>

namespace details {

template <typename T>
void reverse(std::vector<T>& vec, int beg, int fin) { //reverse part of array, including fin
    if(beg < 0 || fin >= vec.size() || beg > fin) 
        throw std::out_of_range("Invalid indices in reverse function");

    int size = fin - beg + 1;
    for(int i = 0; i < size/2; ++i) {
        std::swap(vec[beg + i], vec[fin - i]);
    }
}

template <typename T>
void right_shift(std::vector<T>& vec, int k) { // shift array with preservation
    if(k < 0) 
        throw std::runtime_error("shift must be right");
    if(vec.empty() || k == 0) return;
    k = k % vec.size();

    reverse(vec, 0, vec.size() - 1);
    reverse(vec, 0, k - 1);
    reverse(vec, k, vec.size() - 1);
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
    
    #ifdef SHIFT
        int shift;
        std::cin >> shift;
        details::reading_data(vec);
        details::right_shift(vec, shift);
        details::print_vector(vec);
    #else   
        details::reading_data(vec);
        details::reverse(vec, 0, vec.size() - 1);
        details::print_vector(vec);
    #endif

}