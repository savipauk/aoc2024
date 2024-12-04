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
      if (input[i][j] != 'X') {
        continue;
      }

      // E, NE, SE
      if (j + 3 < (int)input.size()) {
        // E
        if (input[i][j + 1] == 'M' && input[i][j + 2] == 'A' &&
            input[i][j + 3] == 'S') {
          total++;
        }

        if (i + 3 < (int)input.size()) {
          // SE
          if (input[i + 1][j + 1] == 'M' && input[i + 2][j + 2] == 'A' &&
              input[i + 3][j + 3] == 'S') {
            total++;
          }
        }

        if (i - 3 >= 0) {
          // NE
          if (input[i - 1][j + 1] == 'M' && input[i - 2][j + 2] == 'A' &&
              input[i - 3][j + 3] == 'S') {
            total++;
          }
        }
      }

      // W, NW, SW
      if (j - 3 >= 0) {
        // W
        if (input[i][j - 1] == 'M' && input[i][j - 2] == 'A' &&
            input[i][j - 3] == 'S') {
          total++;
        }

        if (i + 3 < (int)input.size()) {
          // SW
          if (input[i + 1][j - 1] == 'M' && input[i + 2][j - 2] == 'A' &&
              input[i + 3][j - 3] == 'S') {
            total++;
          }
        }

        if (i - 3 >= 0) {
          // NW
          if (input[i - 1][j - 1] == 'M' && input[i - 2][j - 2] == 'A' &&
              input[i - 3][j - 3] == 'S') {
            total++;
          }
        }
      }

      if (i + 3 < (int)input.size()) {
        // S
        if (input[i + 1][j] == 'M' && input[i + 2][j] == 'A' &&
            input[i + 3][j] == 'S') {
          total++;
        }
      }

      if (i - 3 >= 0) {
        // N
        if (input[i - 1][j] == 'M' && input[i - 2][j] == 'A' &&
            input[i - 3][j] == 'S') {
          total++;
        }
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
