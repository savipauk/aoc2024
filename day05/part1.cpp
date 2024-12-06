#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

void parse_input(std::vector<std::string>& lines) {
  int section = 0;
  int total = 0;
  int rules[99][99] = {};
  std::vector<std::vector<int>> updates;

  for (std::string& line : lines) {
    if (section == 0 && line == "") {
      section = 1;
      continue;
    }
    
    if (section == 0) {
      std::string first_number = line.substr(0, 2);  
      std::string second_number = line.substr(3, 2);  
      int num1 = std::stoi(first_number);
      int num2 = std::stoi(second_number);
      rules[num1 - 1][num2 - 1] = 1;
      continue;
    }

    size_t pos = 0;
    int current;
    std::vector<int> local_update;
    
    do {
      pos = line.find_first_of(',');
      std::string number = line.substr(0, pos);
      line = line.substr(pos + 1);
      current = std::stoi(number);
      local_update.emplace_back(current); 
    } while (pos != std::string::npos);

    updates.emplace_back(local_update);
    local_update = {};
  }

  for (std::vector<int>& local_update : updates) {
    bool works = true;
    for (size_t i = 0; i < local_update.size(); i++) {
      for (size_t j = i+1; j < local_update.size(); j++) {
        if (rules[local_update[i] - 1][local_update[j] - 1] == 0) {
          works = false;
          break;
        }
      }
      if (!works) {
        break;
      }
    }
    if (works) {
      int middle = local_update.size() / 2;
      total += local_update[middle];
    }
  }

  std::cout << "Total = " << total << "\n";
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
