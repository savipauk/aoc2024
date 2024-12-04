#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

void parse_input(std::vector<std::string>& lines) {
  std::vector<std::vector<char>> input;
  int total = 0;

  for (std::string& line : lines) {
    std::vector<char> inbetween;
    for (char c : line) {
      inbetween.emplace_back(c);
    }
    input.emplace_back(inbetween);
  }

  for (int i = 0; i < (int)input.size(); i++) {
    for (int j = 0; j < (int)input[i].size(); j++) {
      if (input[i][j] != 'A') {
        continue;
      }
      
      if (i - 1 < 0 || i + 1 >= (int)input.size()) {
        continue;
      }

      if (j - 1 < 0 || j + 1 >= (int)input.size()) {
        continue;
      }
      
      bool cond1 = false, cond2 = false;

      // MAS from NW to SE
      if (input[i - 1][j - 1] == 'M' && input[i + 1][j + 1] == 'S') {
        cond1 = true;
      }

      // SAM from NW to SE
      if (input[i - 1][j - 1] == 'S' && input[i + 1][j + 1] == 'M') {
        cond1 = true;
      }
      
      // MAS from NE to SW
      if (input[i - 1][j + 1] == 'M' && input[i + 1][j - 1] == 'S') {
        cond2 = true;
      }

      // SAM from NE to SW
      if (input[i - 1][j + 1] == 'S' && input[i + 1][j - 1] == 'M') {
        cond2 = true;
      }
    
      if (cond1 && cond2) {
        total++;
      }
    }
  }

  std::cout << "total = " << total << "\n";
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
