#include <math.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

struct Entry {
  int original_pos;
  int value;

  Entry(int _original_pos, int _value)
      : original_pos(_original_pos), value(_value) {}

  bool operator<(const Entry& other) const { 
    // if (value == other.value) {
    //   return original_pos < other.original_pos; 
    // }

    return value < other.value;
  }
};

void parse_input(std::vector<std::string>& input) {
  std::vector<Entry> lefties;
  std::vector<Entry> righties;

  int i = 0;
  for (std::string& line : input) {
    int pos = line.find_first_of(' ');
    std::string left = line.substr(0, pos);
    int lefty = std::stoi(left);
    lefties.emplace_back(i, lefty);

    pos = line.find_last_of(' ');
    std::string right = line.substr(pos + 1, line.length() - pos);
    int righty = std::stoi(right);
    righties.emplace_back(i, righty);

    i++;
  }

  // for (Entry& e : lefties) {
  //   std::cout << e.value << " " << e.original_pos << "\n";
  // }
  //
  // std::cout << "\n";
  // for (Entry& e : righties) {
  //   std::cout << e.value << " " << e.original_pos << "\n";
  // }
  
  std::sort(lefties.begin(), lefties.end());
  std::sort(righties.begin(), righties.end());

  // std::cout << "\n";
  // for (Entry& e : lefties) {
  //   std::cout << e.value << " " << e.original_pos << "\n";
  // }
  //
  // std::cout << "\n";
  // for (Entry& e : righties) {
  //   std::cout << e.value << " " << e.original_pos << "\n";
  // }
 
  int sum = 0;
  for (size_t i = 0; i < lefties.size(); i++) {
    int midsum = std::abs(lefties[i].value - righties[i].value);
    // std::cout << "|" << lefties[i].original_pos << " - "
    //           << righties[i].original_pos << "| = " << midsum << "\n";
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
