#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

namespace details {

template <typename T>
void reading_data(std::vector<T>& data) {
    int size = data.size();
    for(int k = 0; k < size; ++k) std::cin >> data[k];
}

// return integer part of sqrt(N) 
int sqrt_by_int(long long N) {
    if (N < 0) throw std::invalid_argument("sqrt_by_int: Negative number");

    long long low = 0, middle = 0;
    long long high = (N < 25) ? N : N/2 + 1;
    while(low <= high) {
        middle = (low + high) / 2;
        if(middle * middle > N) {
            high = middle - 1;
            continue;
        }
        if(middle * middle < N) {
            low = middle + 1;
            continue;
        }
        return middle;
    }
    return high;
}

// return nearest integer of sqrt(N)
int sqrt_by_double(long int N) {
    if (N < 0) throw std::invalid_argument("sqrt_by_double: Negative number");

    long double low = 0, middle = 0;
    long double high = (N < 25) ? N : N/2 + 1;
    while(std::abs(low - high) > 0.5) {
        middle = (low + high) / 2;
        if(middle*middle < N) {
            low = middle;
        } else {
            high = middle;
        }
    }

    if(std::round(high) != std::round(low)) {
        long int r_high = std::round(high), r_low = std::round(low);

        if(std::abs(r_high * r_high - N) < std::abs(r_low * r_low - N))
            return r_high;
        return r_low;
    }
    return std::round(high);
}

int doc_copy(long int N, long int x, long int y) {
    if (N < 0) throw std::invalid_argument("doc_copy: Negative number");
    if(!N) return 0;

    long int Time = std::min(x, y);
    Time += x*y*((N - 1) / (x + y));
    long int rem = (N - 1) % (x + y);
    if(!rem) return Time;

    int low = 0, high = std::max(x, y) * rem;
    long int middle = 0;
    while(low + 1 < high) {
        middle = (low + high) / 2;
        if(middle / x + middle / y < rem) {
            low = middle;
        } else {
            high = middle;
        }
    }

    return Time + high;
}

int animal_feeding(std::vector<int>& needs, std::vector<int>& possibl) {
    std::sort(needs.begin(), needs.end());
    std::sort(possibl.begin(), possibl.end());

    int count = 0;
    int i = 0, j = 0;

    while (i < needs.size() && j < possibl.size()) {
        if (needs[i] <= possibl[j]) 
            ++count, ++i;
        j++;
    
    }
    return count;
}

// size(str1) >= size(str2)
char string_difference(const std::string& str1, const std::string& str2) {
    if(str1.size() < str2.size()) throw std::invalid_argument("string difference: wrong data");
    std::unordered_map<char, int> map;
    std::unordered_map<char, int>::iterator map_it;
    int size = str1.size();
    
    for(int i = 0; i < size; ++i) {
        map_it = map.find(str1[i]);
        if(map_it != map.end()) {
            ++(map_it->second);
        } else {
            map.insert({str1[i], 1});
        }
    }

    size = str2.size();
    for(int i = 0; i < size; ++i) {
        map_it = map.find(str2[i]);
        if(map_it == map.end()) 
            throw std::invalid_argument("string difference: wrong data");

        if(map_it->second == 1) {
            map.erase(map_it);
        } else {
            --(map_it -> second);
        }
    }

    map_it = map.begin();
    if(map_it != map.end()) 
        return map_it->first;
    return '=';
}

//return indexes of array 
std::pair<int, int> sum_of_two(const std::vector<int>& arr, const int target) {
    std::unordered_map<int, std::pair<int, int>> arr_map;
    std::unordered_map<int, std::pair<int, int>>::iterator map_it;
    int arr_size = arr.size();

    for(int i = 0; i < arr_size; ++i) {
        map_it = arr_map.find(arr[i]);

        if(map_it == arr_map.end()) {
            arr_map.insert({arr[i], {i, -1}});
        } else if(map_it->second.second == -1) {
            map_it->second.second = i;
        } else continue;
    }

    for(const int elem: arr) {
        map_it = arr_map.find(target - elem);

        if(elem * 2 == target) { 
            if(map_it->second.second > -1) {
                return {map_it->second.first, map_it->second.second};
            } else continue;
        }

        if(map_it != arr_map.end()) {
            std::unordered_map<int, std::pair<int, int>>::iterator temp_it = arr_map.find(elem);
            return {temp_it->second.first, map_it->second.first};
        }
    }

    return {-1, -1};
}

using AnagramList = std::list<std::pair<std::string, std::list<std::string>>>;

AnagramList anogram_combine(const std::vector<std::string>& anogrm) {
    using node_list = std::list<std::string>;
    using node = std::pair<std::string, node_list>;
    using un_map = std::unordered_map<std::string, std::list<node>::iterator>;
    AnagramList List;
    un_map Map;

    std::string sort_str;
    int size = anogrm.size();
    un_map::iterator map_it;
    std::list<node>::iterator list_it;
    for(int i = 0; i < size; ++i) {
        sort_str = anogrm[i];
        std::sort(sort_str.begin(), sort_str.end());
        map_it = Map.find(sort_str);

        if(map_it != Map.end()) {
            map_it->second->second.push_back(anogrm[i]);
        } else {
            node new_node{sort_str, {anogrm[i]}};
            List.push_back(std::move(new_node));
            list_it = std::prev(List.end());
            Map.insert({sort_str, list_it});
        }
    }

    return List;
}

void print_anagram(const AnagramList& list) {
    for (const auto& big_elem: list) {
        std::cout << "[ ";
        for (const auto& small_elem: big_elem.second) {
            std::cout << small_elem << " ";
        }
        std::cout << "]" << std::endl;
    }
}

} // namespace details

int main() {

    std::cout << "task1(by int): square root" << std::endl;
    std::cout << "enter number ";
    long int P = 0;
    std::cin >> P;
    std::cout << "sqrt of number: " << details::sqrt_by_int(P) << std::endl << std::endl;

    std::cout << "task1(by double): square root" << std::endl;
    std::cout << "enter number ";
    long int Q = 0;
    std::cin >> Q;
    std::cout << "sqrt of number: " << details::sqrt_by_double(Q) << std::endl << std::endl;

    std::cout << "task2: printing copies" << std::endl;
    std::cout << "enter number of copies, speed of the first printer and the second ";
    long int N, x, y;
    std::cin >> N >> x >> y;
    std::cout << "Neccessery time: " << details::doc_copy(N, x, y) << std::endl << std::endl;

    std::cout << "task3: animal feeding" << std::endl;
    std::cout << "enter number of animal, the amount of neccessery food for them in portions" << std::endl;
    int num_of_animal;
    std::cin >> num_of_animal;
    std::vector<int> vec1(num_of_animal);
    details::reading_data(vec1);
    std::cout << "enter number of food sets delivered, the amount of food for them in portions" << std::endl;
    int num_of_sets;
    std::cin >> num_of_sets;
    std::vector<int> vec2(num_of_sets);
    details::reading_data(vec2);
    std::cout << "Number of animals fed: " << details::animal_feeding(vec1, vec2) << std::endl << std::endl;

    std::cout << "task4: string difference" << std::endl;
    std::string str1, str2;
    std::cin.ignore();
    std::cout << "Enter first string" << std::endl;
    std::getline(std::cin, str1);
    std::cout << "Enter second string" << std::endl;
    std::getline(std::cin, str2);
    char res = details::string_difference(str1, str2);
    std::cout << "string difference: ";
    if(res == '=') {
        std::cout << "the strings match";
    } else {
        std::cout << res;
    }
    std::cout << std::endl << std::endl;

    std::cout << "task5: sum of two: " << std::endl;
    std::cout << "Enter size of array, target and the array itself" << std::endl;
    int size, target;
    std::cin >> size >> target;
    std::vector<int> s_vec(size);
    details::reading_data(s_vec);
    std::pair<int, int> sum_res = details::sum_of_two(s_vec, target);
    std::cout << "matches number: ";
    if(sum_res.first == -1) {
        std::cout << "are missing";
    } else {
        std::cout << "first number: " << s_vec[sum_res.first] << ", second number: " << s_vec[sum_res.second];
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "task6: anogram combine: " << std::endl;
    std::cout << "Enter number of string and strings" << std::endl;
    int arr_sz;
    std::cin >> arr_sz;
    std::vector<std::string> vec(arr_sz);
    details::reading_data(vec);
    details::AnagramList List = details::anogram_combine(vec);
    details::print_anagram(List);
    std::cout << std::endl << std::endl;
}
