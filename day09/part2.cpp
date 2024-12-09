#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

struct Block {
  int id;
  int start;
  int size;
};

void parse_input(std::string& input) {
  int id = 0;
  long total = 0;
  std::vector<Block> files;
  std::vector<Block> free_spaces;
  int max_size = 0;
  int relative_position = 0;
  for (size_t i = 0; i < input.size(); i++) {
    char c = input[i];
    int repeat = c - '0';
    Block block;
    if (i % 2 == 0) {
      block = {id, relative_position, repeat};
      files.emplace_back(block);
      id++;
    } else {
      block = {-1, relative_position, repeat};
      free_spaces.emplace_back(block);
    }
    relative_position += repeat;
    max_size += repeat;
  }

  for (int end = (int)files.size() - 1; end >= 0; end--) {
    int needs_space = files[end].size;
    Block* swap = nullptr;
    int leftmost_swap_space = max_size;
    for (int i = 0; i < (int)free_spaces.size(); i++) {
      Block* free = &free_spaces[i];
      if (free->start > files[end].start) {
        continue;
      }
      if (free->size >= needs_space && leftmost_swap_space > free->start) {
        swap = free;
        leftmost_swap_space = free->start; 
      }
    }
    if (swap != nullptr) {
      int new_free_space_pos = files[end].start;
      files[end].start = swap->start;
      swap->start = new_free_space_pos;
      int extra_space = swap->size - needs_space;
      if (extra_space != 0) {
        Block add = {-1, files[end].start + needs_space, extra_space}; 
        free_spaces.emplace_back(add);
      }
    }
  }

  for (Block& block : files) {
    for (int i = 0; i < block.size; i++) {
      total += block.id * (block.start + i);
    }
  }

  std::cout << "Total: " << total << "\n";
}

int main() {
  std::string line;
  getline(std::cin, line);
  parse_input(line);

  return 0;
}
