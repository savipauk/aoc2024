#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

void blink(std::vector<long>* read_from, std::vector<long>* write_to) {
  *write_to = {};
  for (long stone : *read_from) {
    if (stone == 0) {
      write_to->emplace_back(1L);
      continue;
    }

    int n_of_digits = 0;
    long midstone = stone;
    do {
      midstone /= 10;
      n_of_digits++;
    } while (midstone > 0);

    if (n_of_digits % 2 == 0) {
      long left_num = 0, right_num = 0;
      for (int i = 0; i < n_of_digits / 2; i++) {
        right_num += (stone % 10) * std::pow(10, i);
        stone /= 10;
      }

      for (int i = 0; i < n_of_digits / 2; i++) {
        left_num += (stone % 10) * std::pow(10, i);
        stone /= 10;
      }

      write_to->emplace_back(left_num);
      write_to->emplace_back(right_num);
      continue;
    }

    long new_stone = stone * 2024L;
    write_to->emplace_back(new_stone);
  }
}

void parse_input(std::vector<std::string>& lines) {
  std::vector<long> stones;
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

  std::vector<long> stones_blink;
  for (int i = 0; i < 26; i++) {
    if (i % 2 == 0) {
      blink(&stones, &stones_blink);
      continue;
    }

    blink(&stones_blink, &stones);
  }

  std::cout << "Total: " << stones_blink.size() << "\n";
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
