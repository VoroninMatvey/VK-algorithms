#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

namespace details {

bool is_subsequence_by_queue(const std::string &a, const std::string &b) {
  std::queue<char> a_word, b_word;

  for (char elem : a) {
    a_word.push(elem);
  }

  for (char elem : b) {
    b_word.push(elem);
  }

  while (!b_word.empty() && !a_word.empty()) {
    if (a_word.front() == b_word.front()) {
      a_word.pop();
    }
    b_word.pop();
  }
  return a_word.empty();
}

bool is_subsequence_by_string(const std::string &a, const std::string &b) {
  std::size_t a_it = 0, b_it = 0;
  while (a_it < a.size() && b_it < b.size()) {
    if (a[a_it] == b[b_it]) {
      ++a_it;
    }
    ++b_it;
  }
  return a.size() == a_it;
}

bool is_palindrom_by_stack(const std::string &str) {
  std::stack<char> word;
  for (char elem : str) {
    word.push(elem);
  }

  auto it = str.cbegin();
  while (!word.empty()) {
    if (*it != word.top())
      return false;
    ++it;
    word.pop();
  }
  return true;
}

bool is_palindrom_by_deque(const std::string &str) {
  std::deque<char> word;
  for (char elem : str) {
    word.push_back(elem);
  }

  while (word.size() > 1) {
    if (word.front() != word.back())
      return false;
    word.pop_back();
    word.pop_front();
  }
  return true;
}

bool is_palindrom_by_string(const std::string &str) {
  int size = str.size();
  for (int i = 0; i < size / 2; ++i) {
    if (str[i] != str[size - i - 1])
      return false;
  }
  return true;
}

} // namespace details

int main() {
  std::string str1, str2;

  std::cout << "checking on substring" << std::endl;
  std::cout << "Enter first string" << std::endl;
  std::getline(std::cin, str1);

  std::cout << "Enter second string" << std::endl;
  std::getline(std::cin, str2);
  std::cout << std::endl;

  std::cout << "function: is_subsequence_by_queue" << std::endl;
  std::cout << "first string is original substring for second: "
            << std::boolalpha << details::is_subsequence_by_queue(str1, str2);
  std::cout << std::endl << std::endl;

  std::cout << "function: is_subsequence_by_string" << std::endl;
  std::cout << "first string is original substring for second: "
            << std::boolalpha << details::is_subsequence_by_string(str1, str2);
  std::cout << std::endl << std::endl;

  std::string str3;
  std::cout << "Enter string for checking on palindrom" << std::endl;
  std::getline(std::cin, str3);
  std::cout << std::endl;

  std::cout << "function: is_palindrom_by_stack" << std::endl;
  std::cout << "string is palindrom: " << std::boolalpha
            << details::is_palindrom_by_stack(str3);
  std::cout << std::endl << std::endl;

  std::cout << "function: is_palindrom_by_deque" << std::endl;
  std::cout << "string is palindrom: " << std::boolalpha
            << details::is_palindrom_by_deque(str3);
  std::cout << std::endl << std::endl;

  std::cout << "function: is_palindrom_by_string" << std::endl;
  std::cout << "string is palindrom: " << std::boolalpha
            << details::is_palindrom_by_string(str3);
  std::cout << std::endl << std::endl;
}