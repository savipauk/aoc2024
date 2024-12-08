#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

struct Equation {
  long result;
  std::vector<long> nums;
};

void permutate(size_t i, size_t total_size, std::vector<char>& chars,
               std::vector<std::vector<char>>& storage) {
  if (i == total_size) {
    storage.emplace_back(chars);
    return;
  }

  std::vector<char> new_chars = chars;
  std::vector<char> perm_chars = chars;

  char s = '+';
  chars.emplace_back(s);
  permutate(i + 1, total_size, chars, storage);

  char m = '*';
  new_chars.emplace_back(m);
  permutate(i + 1, total_size, new_chars, storage);

  char p = '|';
  perm_chars.emplace_back(p);
  permutate(i + 1, total_size, perm_chars, storage);
}

long concat(long fst, long snd) {
  long pow = 10;
  while (snd >= pow) {
    pow *= 10;
  }
  long res = fst * pow + snd;
  return res;
}

void parse_input(std::vector<std::string>& lines) {
  long total = 0;
  std::vector<Equation> equations = {};
  for (std::string& line : lines) {
    Equation e;
    size_t pos = line.find(':');
    std::string result_string = line.substr(0, pos);
    // + 1 because there's a whitespace after the colon
    line = line.substr(pos + 1 + 1);
    e.result = std::stol(result_string);
    long new_num;
    do {
      pos = line.find(' ');
      std::string sub = line.substr(0, pos);
      line = line.substr(pos + 1);
      new_num = std::stol(sub);
      e.nums.emplace_back(new_num);
    } while (pos != std::string::npos);
    equations.emplace_back(e);
  }

  for (Equation e : equations) {
    std::vector<int> operands = {};
    for (size_t i = 0; i < e.nums.size() - 1; i++) {
    }
  }

  for (size_t i = 0; i < equations.size(); i++) {
    Equation e = equations[i];

    std::vector<std::vector<char>> storage;
    std::vector<char> local_storage;
    permutate(0, e.nums.size() - 1, local_storage, storage);

    for (std::vector<char> operands : storage) {
      long result = e.nums[0];
      for (size_t j = 0; j < operands.size(); j++) {
        char o = operands[j];
        if (o == '+') {
          result += e.nums[j + 1];
        } else if (o == '*') {
          result *= e.nums[j + 1];
        } else {
          long next = e.nums[j + 1];
          result = concat(result, next);
        }
      }
      if (result == e.result) {
        total += e.result;
        break;
      }
    }
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
