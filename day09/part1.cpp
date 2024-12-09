#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

void parse_input(std::string& input) {
  int id = 0;
  long total = 0;
  std::vector<int> disk;
  for (size_t i = 0; i < input.size(); i++) {
    char c = input[i];
    int to_put_in = -1;
    if (i % 2 == 0) {
      to_put_in = id;
      id++;
    }
    int repeat = c - '0';
    for (int j = 0; j < repeat; j++) {
      disk.push_back(to_put_in);
    }
  }

  int end = (int)disk.size() - 1;
  int i = 0;
  while (i < end) {
    if (disk[i] == -1) {
      while (disk[end] == -1) {
        end--;
      }
      disk[i] = disk[end];
      disk[end] = -1;
    }
    i++;
  }

  i = 0;
  for (int num : disk) {
    if (num == -1) {
      continue;
    }
    total += num * i;
    i++;
  }

  std::cout << "Total: " << total << "\n";
}

int main() {
  std::string line;
  getline(std::cin, line);
  parse_input(line);

  return 0;
}
