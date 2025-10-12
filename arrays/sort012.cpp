#include <iostream>
#include <vector>

namespace details {

// [0 : low-1] - zeroes
// [low : mid - 1] - ones
// [mid : high] - study area
// [high + 1 : n - 1] - twos

template <typename T>
void sortedDutchFlag(std::vector<T>& vec) {
    int low = 0, mid = 0; 
    int high = vec.size() -1;

    while(mid <= high) {
        if(vec[mid] == 2) {
            std::swap(vec[mid], vec[high]);
            --high;
        } else if(vec[mid] == 0) {
            std::swap(vec[mid], vec[low]);
            ++low; ++mid;
        } else ++mid;
    }

}

template <typename T>
void reading_data(std::vector<T>& data) {
    int size = data.size();
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
    details::reading_data(vec);
    details::sortedDutchFlag(vec);
    details::print_vector(vec);
}