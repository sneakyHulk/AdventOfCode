#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <limits>

int main() {
  {
    auto file = std::fopen("input", "r");
    if (std::fscanf(file, "seeds:") > 0)
      return -1;

    std::vector<unsigned int> seeds;
    for (unsigned int n; std::fscanf(file, "%d", &n);)
      seeds.push_back(n);

    std::array<std::vector<std::tuple<int, int, int>>, 7> converter;
    if (std::fscanf(file, "seed-to-soil map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[0].emplace_back(a, b, c);
    if (std::fscanf(file, "soil-to-fertilizer map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[1].emplace_back(a, b, c);
    if (std::fscanf(file, "fertilizer-to-water map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[2].emplace_back(a, b, c);
    if (std::fscanf(file, "water-to-light map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[3].emplace_back(a, b, c);
    if (std::fscanf(file, "light-to-temperature map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[4].emplace_back(a, b, c);
    if (std::fscanf(file, "temperature-to-humidity map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c);)
      converter[5].emplace_back(a, b, c);
    if (std::fscanf(file, "humidity-to-location map:") > 0)
      return -1;
    for (unsigned int a, b, c; std::fscanf(file, "%d %d %d", &a, &b, &c) > 0;)
      converter[6].emplace_back(a, b, c);
    std::fclose(file);

    unsigned int low = std::numeric_limits<unsigned int>::max();
    for (auto seed : seeds) {
      for (auto const &convert : converter) {
        for (auto mapped : convert) {
          if (seed >= std::get<1>(mapped) &&
              seed < std::get<1>(mapped) + std::get<2>(mapped)) {
            seed = std::get<0>(mapped) + seed - std::get<1>(mapped);
            if (seed < low) {
              low = seed;
            }
            break;
          }
        }
      }
    }
    std::cout << low << std::endl;
  }

  return 0;
}