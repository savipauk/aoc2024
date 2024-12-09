#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

struct Vector2 {
  int x;
  int y;
};

struct Antenna {
  Vector2 position;
  char c;
};

bool add_if_unique_and_in_bounds(Vector2& vec, std::vector<Vector2>* list,
                                 Vector2 size) {
  if (vec.x < 0 || vec.y < 0 || vec.x >= size.x || vec.y >= size.y) {
    return false;
  }

  for (Vector2 node : *list) {
    if (vec.x == node.x && vec.y == node.y) {
      return false;
    }
  }

  list->emplace_back(vec);

  return true;
}

void parse_input(std::vector<std::string>& lines) {
  int total = 0;
  std::vector<std::vector<Antenna>> antennas;
  Vector2 size = {(int)lines[0].size(), (int)lines.size()};

  for (size_t i = 0; i < lines.size(); i++) {
    std::vector<char> row;
    std::string& line = lines[i];
    for (size_t j = 0; j < line.size(); j++) {
      char c = line[j];
      row.emplace_back(c);
      if (c == '.') {
        continue;
      }
      bool exists = false;
      Antenna ant;
      ant.position = {(int)j, (int)i};
      ant.c = c;
      for (std::vector<Antenna>& ant_group : antennas) {
        if (ant_group[0].c == c) {
          exists = true;
          ant_group.emplace_back(ant);
          break;
        }
      }
      if (!exists) {
        std::vector<Antenna> new_ant_group = {ant};
        antennas.emplace_back(new_ant_group);
      }
    }
  }

  std::vector<Vector2> antinodes;
  for (std::vector<Antenna>& ant_group : antennas) {
    for (size_t i = 0; i < ant_group.size(); i++) {
      Antenna ant = ant_group[i];
      for (size_t j = i + 1; j < ant_group.size(); j++) {
        if (i == j) {
          continue;
        }
        Antenna other = ant_group[j];

        Vector2 me = ant.position;
        Vector2 you = other.position;

        int initial_x_diff = std::abs(me.x - you.x);
        int initial_y_diff = std::abs(me.y - you.y);
        int x_diff = initial_x_diff;
        int y_diff = initial_y_diff;

        int max_scale = std::min(size.x / initial_x_diff, size.y / initial_y_diff);

        for (int scale = 0; scale <= max_scale; scale++) {
          x_diff = initial_x_diff * scale;   
          y_diff = initial_y_diff * scale;   

          int x1 = me.x, x2 = me.x, y1 = me.y, y2 = me.y;

          if (me.x > you.x) {
            x1 = me.x + x_diff;
            x2 = you.x - x_diff;
            if (me.y < you.y) {
              y1 = me.y - y_diff;
              y2 = you.y + y_diff;
            }
            if (me.y > you.y) {
              y1 = me.y + y_diff;
              y2 = you.y - y_diff;
            }
          } else if (me.x < you.x) {
            x1 = me.x - x_diff;
            x2 = you.x + x_diff;
            if (me.y < you.y) {
              y1 = me.y - y_diff;
              y2 = you.y + y_diff;
            }
            if (me.y > you.y) {
              y1 = me.y - y_diff;
              y2 = you.y + y_diff;
            }
          }

          Vector2 an1 = {x1, y1};
          Vector2 an2 = {x2, y2};

          if (add_if_unique_and_in_bounds(an1, &antinodes, size)) {
            total++;
          }

          if (add_if_unique_and_in_bounds(an2, &antinodes, size)) {
            total++;
          }
        }
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
