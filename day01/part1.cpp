#include <math.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

void parse_input(std::vector<std::string>& input) {
  std::vector<int> lefties;
  std::vector<int> righties;

  int i = 0;
  for (std::string& line : input) {
    int pos = line.find_first_of(' ');
    std::string left = line.substr(0, pos);
    int lefty = std::stoi(left);
    lefties.emplace_back(lefty);

    pos = line.find_last_of(' ');
    std::string right = line.substr(pos + 1, line.length() - pos);
    int righty = std::stoi(right);
    righties.emplace_back(righty);

    i++;
  }

  std::sort(lefties.begin(), lefties.end());
  std::sort(righties.begin(), righties.end());

  int sum = 0;
  for (size_t i = 0; i < lefties.size(); i++) {
    int midsum = std::abs(lefties[i] - righties[i]);
    sum += midsum;
  }

  std::cout << "sum " << sum << "\n";
}

int main() {
  std::string line;
  std::vector<std::string> input;

  // Read lines
  while (getline(std::cin, line)) {
    input.emplace_back(line);
  }

  parse_input(input);

  return 0;
}
