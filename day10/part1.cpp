#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

struct Position {
  size_t i;
  size_t j;
};

struct Trailhead {
  Position position;
  std::vector<Position> already_hit;
};

std::vector<std::vector<int>> map;
std::vector<Trailhead> trailheads;

int calculate_trailhead_paths(int i, int j, int last_height,
                              Trailhead* trailhead) {
  if (i < 0 || j < 0 || i >= (int)map.size() || j >= (int)map[0].size()) {
    return 0;
  }

  if (map[i][j] != last_height + 1) {
    return 0;
  }

  if (last_height == 8 && map[i][j] == 9) {
    for (Position pos : trailhead->already_hit) {
      if (pos.i == (size_t)i && pos.j == (size_t)j) {
        return 0;
      }
    }
    Position new_top = {(size_t)i, (size_t)j};
    trailhead->already_hit.emplace_back(new_top);
    return 1;
  }

  int sum = 0;
  sum += calculate_trailhead_paths(i + 1, j, last_height + 1, trailhead);
  sum += calculate_trailhead_paths(i - 1, j, last_height + 1, trailhead);
  sum += calculate_trailhead_paths(i, j + 1, last_height + 1, trailhead);
  sum += calculate_trailhead_paths(i, j - 1, last_height + 1, trailhead);

  return sum;
}

void parse_input(std::vector<std::string>& lines) {
  int total = 0;

  for (std::string& line : lines) {
    std::vector<int> row;
    for (char c : line) {
      int num = c - '0';
      row.emplace_back(num);
    }
    map.emplace_back(row);
  }

  for (size_t i = 0; i < map.size(); i++) {
    std::vector<int> row = map[i];
    for (size_t j = 0; j < row.size(); j++) {
      if (row[j] == 0) {
        std::vector<Position> already_hit = {};
        Position position = {i, j};
        Trailhead trailhead = {position, already_hit};
        int trailhead_score = calculate_trailhead_paths(i, j, -1, &trailhead);
        total += trailhead_score;
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
