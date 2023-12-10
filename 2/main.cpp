#include <fstream>
#include <iostream>
#include <regex>
#include <limits>

int main() {
  {
    std::ifstream infile("input");
    auto sum = 0;
    std::regex const games("([0-9]+) red|([0-9]+) green|([0-9]+) blue");
    auto id = 1;
    for (std::string line; getline(infile, line); ++id) {
      auto current = id;
      for (std::sregex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), games);
           i != std::sregex_iterator(); ++i) {
        std::smatch matches = *i;
        if (matches[1].length() && std::stoi(matches[1].str()) > 12) {
          current = 0;
          break;
        }

        if (matches[2].length() && std::stoi(matches[2].str()) > 13) {
          current = 0;
          break;
        }

        if (matches[3].length() && std::stoi(matches[3].str()) > 14) {
          current = 0;
          break;
        }
      }
      sum += current;
    }
    std::cout << sum << std::endl;
  }

  {
    std::ifstream infile("input");
    auto sum = 0;
    std::regex const games("([0-9]+) red|([0-9]+) green|([0-9]+) blue");
    for (std::string line; getline(infile, line);) {
      int max_red = 0, max_green = 0, max_blue = 0;
      for (std::sregex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), games);
           i != std::sregex_iterator(); ++i) {
        std::smatch matches = *i;
        if (matches[1].length()) {
          auto m = std::stoi(matches[1].str());
          if (m > max_red)
            max_red = m;
        }
        if (matches[2].length()) {
          auto m = std::stoi(matches[2].str());
          if (m > max_green)
            max_green = m;
        }
        if (matches[3].length()) {
          auto m = std::stoi(matches[3].str());
          if (m > max_blue)
            max_blue = m;
        }
      }
      sum += max_red * max_green * max_blue;
    }
    std::cout << sum << std::endl;
  }
}