#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Vector2 {
  int y;
  int x;
};

bool out_of_bounds(Vector2 position, Vector2 size) {
  if (position.x < 0 || position.y < 0 || position.x >= size.x ||
      position.y >= size.y) {
    return true;
  }

  return false;
}

void parse_input(std::vector<std::string>& lines) {
  Direction direction = DOWN;
  Vector2 position = {0, 0};
  int total = 0;

  for (int i = 0; i < (int)lines.size(); i++) {
    std::string& line = lines[i];
    bool found = false;
    for (int j = 0; j < (int)line.size(); j++) {
      char c = line[j];
      switch (c) {
        case '^':
          found = true;
          direction = UP;
          break;
        case '>':
          found = true;
          direction = RIGHT;
          break;
        case 'v':
          found = true;
          direction = DOWN;
          break;
        case '<':
          found = true;
          direction = LEFT;
          break;
      }
      if (found) {
        position = {i, j};
        lines[i][j] = 'X';
        total++;
        break;
      }
    }
    if (found) {
      break;
    }
  }

  Vector2 size = {(int)lines[0].size(), (int)lines.size()};
  Vector2 old_position = position;
  while (!out_of_bounds(position, size)) {
    char c = lines[position.y][position.x];
    if (c == '#') {
      position = old_position;
      switch (direction) {
        case UP:
          direction = RIGHT;
          break;
        case RIGHT:
          direction = DOWN;
          break;
        case DOWN:
          direction = LEFT;
          break;
        case LEFT:
          direction = UP;
          break;
      }
    } else if (c == '.') {
      lines[position.y][position.x] = 'X';
      total++;
    }

    old_position = position;

    switch (direction) {
      case UP:
        position.y--;
        break;
      case RIGHT:
        position.x++;
        break;
      case DOWN:
        position.y++;
        break;
      case LEFT:
        position.x--;
        break;
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
