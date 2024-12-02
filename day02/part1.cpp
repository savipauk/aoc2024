#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>
#include <math.h>

void parse_input(std::vector<std::string>& input) {
  int total = 0;
  for (std::string& line : input) {
    int increase = 0, last = 0, curr = 0;
    size_t pos;
    do {
      pos = line.find(' ');
      std::string sub = line.substr(0, pos);
      line = line.substr(pos + 1);

      curr = std::stoi(sub);

      if (increase == 0) {
        increase = 2;
        last = curr;
        continue;
      }

      if (std::abs(curr - last) > 3 || std::abs(curr - last) < 1) {
        increase = 3;
        break;
      }

      if (increase == 2) {
        if (curr > last) {
          increase = 1;
        } else if (curr < last) {
          increase = -1;
        }

        last = curr;
        continue;
      }

      if (increase == 1) {
        if (curr > last) {
          last = curr;
          continue;
        } else {
          increase = 3;
          break;
        }
      }

      if (increase == -1) {
        if (curr < last) {
          last = curr;
          continue;
        } else {
          increase = 3;
          break;
        }
      }
    } while (pos != std::string::npos);

    if (increase == 1 || increase == -1) {
      total++;
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
