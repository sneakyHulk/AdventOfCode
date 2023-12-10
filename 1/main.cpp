#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int get_number(std::string const &str) {
  if (str.length() > 1) {
    if (str == "one") {
      return 1;
    } else if (str == "two") {
      return 2;
    } else if (str == "three") {
      return 3;
    } else if (str == "four") {
      return 4;
    } else if (str == "five") {
      return 5;
    } else if (str == "six") {
      return 6;
    } else if (str == "seven") {
      return 7;
    } else if (str == "eight") {
      return 8;
    } else if (str == "nine") {
      return 9;
    }
  } else {
    return str.front() - '0';
  }
}

int main() {
  {
    std::ifstream infile("input");
    auto sum = 0;
    for (std::string line; getline(infile, line);) {
      auto it = std::find_if(line.begin(), line.end(),
                             [](char const c) { return c >= '0' && c <= '9'; });
      auto rit = std::find_if(line.rbegin(), line.rend(), [](char const c) {
        return c >= '0' && c <= '9';
      });
      sum += 10 * (*it - '0') + (*rit - '0');
    }

    std::cout << sum << std::endl;

    infile.close();
  }

  {
    std::ifstream infile("input");
    auto sum = 0;
    std::regex const numbers(
        "([0-9]|one|two|three|four|five|six|seven|eight|nine).*([0-9]|one|two|"
        "three|four|five|six|seven|eight|nine)");
    std::regex const number(
        "([0-9]|one|two|three|four|five|six|seven|eight|nine)");

    for (std::string line; getline(infile, line);) {
      std::smatch matches;

      if (std::regex_search(line, matches, numbers)) {
        sum += 10 * get_number(matches[1].str()) + get_number(matches[2].str());
      } else if (std::regex_search(line, matches, number)) {
        sum += 11 * get_number(matches[0].str());
      }
    }

    std::cout << sum << std::endl;

    infile.close();
  }

  return 0;
}