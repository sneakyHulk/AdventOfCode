#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include <numeric>

template <typename T> class dynamic_vector : public std::vector<T> {
  T const &value;

public:
  explicit dynamic_vector(T const &value) : value(value) {}

  T &operator[](std::vector<T>::size_type const index) noexcept {
    if (auto old_size = std::vector<T>::size(); index >= old_size) {
      std::vector<T>::insert(std::vector<T>::cend(), index - old_size + 1,
                             value);
    }
    return std::vector<T>::operator[](index);
  }
};

int main() {
  {
    std::ifstream infile("input");
    int sum = 0;

    std::regex const cards(
        "Card  ? ?([0-9]+):  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+) \\|  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)");
    for (std::string line; getline(infile, line);) {
      std::smatch matches;

      if (std::regex_search(line, matches, cards)) {
        int sub_sum = 1;
        for (auto i = 2; i <= 11; ++i) {
          for (auto j = 12; j <= 36; ++j) {
            auto str_i = matches[i].str(), str_j = matches[j].str();
            if (str_i == str_j) {
              sub_sum *= 2;
              break;
            }
          }
        }
        sum += sub_sum / 2;
      } else {
        std::cout << "HELP" << std::endl;
      }
    }

    std::cout << sum << std::endl;
    infile.close();
  }

  {
    std::ifstream infile("input");
    int sum = 0;

    std::regex const cards(
        "Card  ? ?([0-9]+):  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+) \\|  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  ?([0-9]+)  "
        "?([0-9]+)");

    dynamic_vector<int> n_cards(1);
    auto n = 0;
    for (std::string line; getline(infile, line); ++n) {
      std::smatch matches;
      auto nn = n;
      if (std::regex_search(line, matches, cards)) {
        for (auto i = 2; i <= 11; ++i) {
          for (auto j = 12; j <= 36; ++j) {
            auto str_i = matches[i].str(), str_j = matches[j].str();
            if (str_i == str_j) {
              n_cards[++nn] += n_cards[n];
              break;
            }
          }
        }
      } else {
        std::cout << "HELP" << std::endl;
      }
    }

    std::cout << std::accumulate(n_cards.begin(), n_cards.end(), 0) << std::endl;
    infile.close();
  }

  return 0;
}