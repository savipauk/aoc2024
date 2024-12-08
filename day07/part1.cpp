#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

struct Equation {
  long result;
  std::vector<long> nums;
};

void calculate(size_t i, size_t total_size, std::vector<long>& nums,
               long local_result, std::vector<long>& results) {
  if (i == total_size) {
    results.emplace_back(local_result);
    return;
  }

  long mul_result = local_result;
  local_result = local_result + nums[i];
  calculate(i + 1, total_size, nums, local_result, results);

  if (i == 0) {
    mul_result = nums[i];
    calculate(i + 1, total_size, nums, mul_result, results);
  } else {
    mul_result = mul_result * nums[i];
    calculate(i + 1, total_size, nums, mul_result, results);
  }
}

void permutate(size_t i, size_t total_size, std::vector<char>& chars,
               std::vector<std::vector<char>>& storage) {
  if (i == total_size) {
    storage.emplace_back(chars);
    return;
  }

  std::vector<char> new_chars = chars;

  char s = '+';
  chars.emplace_back(s);
  permutate(i + 1, total_size, chars, storage);

  char m = '*';
  new_chars.emplace_back(m);
  permutate(i + 1, total_size, new_chars, storage);
}

void parse_input(std::vector<std::string>& lines) {
  long total = 0;
  long total2 = 0;
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

    // Approach 1
    std::vector<std::vector<char>> storage;
    std::vector<char> local_storage;
    permutate(0, e.nums.size() - 1, local_storage, storage);
    for (std::vector<char> operands : storage) {
      long res = e.nums[0];
      for (size_t j = 0; j < operands.size(); j++) {
        char o = operands[j];
        if (o == '+') {
          res += e.nums[j+1];
        } else {
          res *= e.nums[j+1];
        }
      }
      if (res == e.result) {
        total += res;
        break;
      }
    }

    // Approach 2
    std::vector<long> results;
    calculate(0, e.nums.size(), e.nums, 0, results);
    for (long r : results) {
      if (r == e.result) {
        total2 += r;
        break;
      }
    }
  }

  std::cout << "Total: " << total << "\n";
  std::cout << "Total2: " << total2 << "\n";
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
