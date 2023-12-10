#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
  {
    std::ifstream infile("input");
    std::regex const symbols(R"((\+|\*|-|=|@|\/|%|\$|\#|\&))");
    std::regex const numbers("([0-9]+)");

    std::vector<std::vector<int>> symbols_positions;

    auto n = 0;
    for (std::string line; getline(infile, line); ++n) {
      std::vector<int> symbols_line;
      for (std::sregex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), symbols);
           i != std::sregex_iterator(); ++i) {
        auto pos = i->position();
        symbols_line.push_back(pos);
      }

      symbols_positions.push_back(symbols_line);
    }
    n = 0;
    auto sum = 0;
    infile.clear();
    infile.seekg(0);
    for (std::string line; getline(infile, line); ++n) {
      for (std::sregex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), numbers);
           i != std::sregex_iterator(); ++i) {
        auto pos = i->position();
        auto length = i->length();
        for (auto e : symbols_positions[n]) {
          if (e == pos - 1 || e == pos + length) {
            sum += std::stoi(i->str());
            goto lol;
          }
        }
        if (n > 0) {
          for (auto e : symbols_positions[n - 1]) {
            if (e >= pos - 1 && e <= pos + length) {
              sum += std::stoi(i->str());
              goto lol;
            }
          }
        }
        if (n < symbols_positions.size() - 1) {
          for (auto e : symbols_positions[n + 1]) {
            if (e >= pos - 1 && e <= pos + length) {
              sum += std::stoi(i->str());
              goto lol;
            }
          }
        }
      lol:
        continue;
      }
    }

    std::cout << sum << std::endl;

    infile.close();
  }

  {
    std::regex const numbers("([0-9]+)");
    std::ifstream infile("input");

    std::vector<std::vector<std::pair<std::string, int>>> number_pos;
    for (std::string line; getline(infile, line);) {
      std::vector<std::pair<std::string, int>> n_p;
      for (std::sregex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), numbers);
           i != std::sregex_iterator(); ++i) {
        n_p.emplace_back(i->str(), i->position());
      }

      number_pos.push_back(n_p);
    }

    infile.clear();
    infile.seekg(0);
    auto sum = 0;
    auto n = 0;
    for (std::string line; getline(infile, line); ++n) {
      for (auto pos = 0; pos < line.size(); ++pos) {
        if (line[pos] == '*') {
          auto sum_star = 1;
          auto n_star = 0;
          if (n > 0) {
            for (const auto &e : number_pos[n - 1]) {
              if (e.second + e.first.size() >= pos && e.second <= pos + 1) {
                ++n_star;
                sum_star *= std::stoi(e.first);
              }
            }
          }
          if (n < number_pos.size() - 1) {
            for (const auto &e : number_pos[n + 1]) {
              if (e.second + e.first.size() >= pos && e.second <= pos + 1) {
                ++n_star;
                sum_star *= std::stoi(e.first);
              }
            }
          }
          for (const auto &e : number_pos[n]) {
            if (pos == e.second + e.first.size() || pos == e.second - 1) {
              ++n_star;
              sum_star *= std::stoi(e.first);
            }
          }
          if (n_star == 2) {
            sum += sum_star;
          }
          if (n_star > 2) {
            sum += sum_star;
          }
        }
      }
    }

    std::cout << sum << std::endl;

    infile.close();
  }

  return 0;
}