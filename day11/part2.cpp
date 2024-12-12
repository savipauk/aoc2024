#include <math.h>

#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <vector>

int number_of_digits(long n) {
  int n_of_digits = 0;

  do {
    n /= 10;
    n_of_digits++;
  } while (n > 0);

  return n_of_digits;
}

std::map<long, long> blink(std::map<long, long>& stones) {
  std::map<long, long> new_stones;

  for (const auto& [stone, value] : stones) {
    if (stone == 0) {
      new_stones[1] += value;
      continue;
    }

    int n_of_digits = number_of_digits(stone);
    if (n_of_digits % 2 == 0) {
      long right_num = (stone % (long)(std::pow(10, n_of_digits / 2)));
      long left_num =
          (stone - right_num) / (long)(std::pow(10, n_of_digits / 2));
      new_stones[left_num] += value;
      new_stones[right_num] += value;
      continue;
    }

    long new_stone = stone * 2024L;
    new_stones[new_stone] += value;
  }

  return new_stones;
}

void parse_input(std::vector<std::string>& lines) {
  std::list<long> stones;
  std::map<long, long> stone_map;
  for (std::string& line : lines) {
    size_t pos;
    do {
      pos = line.find(' ');
      std::string sub = line.substr(0, pos);
      long n = std::stol(sub);
      stones.emplace_back(n);
      line = line.substr(pos + 1);
    } while (pos != std::string::npos);
  }

  for (long initial_stone : stones) {
    stone_map[initial_stone] = 1;
  }

  for (int i = 0; i < 75; i++) {
    stone_map = blink(stone_map);
  }

  unsigned long long total = 0;
  for (const auto& [key, value] : stone_map) {
    total += value;
  }

  std::cout << "Total: " << total << "\n";
}

int main() {
  std::string line;
  std::vector<std::string> input;

  while (getline(std::cin, line)) {
    input.emplace_back(line);
  }

  parse_input(input);

  return 0;
}
