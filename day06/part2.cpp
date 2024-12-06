#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

enum Direction { UP, RIGHT, DOWN, LEFT };

struct Vector2 {
  int y;
  int x;

  bool operator==(const Vector2& other) { return x == other.x && y == other.y; }
};

struct VisitedPlace {
  Vector2 position;
  bool up = false, right = false, down = false, left = false;
};

struct Hit {
  Vector2 position;
  Direction direction;
};

void visit_place(VisitedPlace* place, Direction direction) {
  switch (direction) {
    case UP:
      place->up = true;
      break;
    case RIGHT:
      place->right = true;
      break;
    case DOWN:
      place->down = true;
      break;
    case LEFT:
      place->left = true;
      break;
  }
}

VisitedPlace visit_place(Vector2 position, Direction direction) {
  VisitedPlace place;
  place.position = position;
  switch (direction) {
    case UP:
      place.up = true;
      break;
    case RIGHT:
      place.right = true;
      break;
    case DOWN:
      place.down = true;
      break;
    case LEFT:
      place.left = true;
      break;
  }
  return place;
}

bool out_of_bounds(Vector2 position, Vector2 size) {
  if (position.x < 0 || position.y < 0 || position.x >= size.x ||
      position.y >= size.y) {
    return true;
  }

  return false;
}

void parse_input(std::vector<std::string>& lines) {
  Direction direction = DOWN;
  Direction initial_direction = DOWN;
  Vector2 position = {0, 0};
  Vector2 initial_position = {0, 0};
  std::vector<VisitedPlace> visited = {};
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
        VisitedPlace place = visit_place(position, direction);
        visited.emplace_back(place);
        break;
      }
    }
    if (found) {
      break;
    }
  }

  initial_position = position;
  initial_direction = direction;
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
    } else {
      bool already_visited = false;
      for (size_t i = 0; i < visited.size(); i++) {
        if (visited[i].position == position) {
          already_visited = true;
          visit_place(&visited[i], direction);
          break;
        }
      }

      if (!already_visited) {
        VisitedPlace place = visit_place(position, direction);
        visited.emplace_back(place);
        lines[position.y][position.x] = 'X';
      }
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

  std::vector<Hit> hits = {};
  for (size_t i = 0; i < visited.size(); i++) {
    Vector2 obstruction = visited[i].position;
    if (obstruction == initial_position) {
      continue;
    }

    lines[obstruction.y][obstruction.x] = '#';
    position = initial_position;
    direction = initial_direction;
    old_position = position;
    hits = {};
    while (!out_of_bounds(position, size)) {
      char c = lines[position.y][position.x];
      if (c == '#') {
        bool already_hit = false;
        for (Hit hit : hits) {
          if (hit.position == position && hit.direction == direction) {
            already_hit = true;
            total++;
            break;
          }
        }
        if (already_hit) {
          break;
        }
        Hit hit = {position, direction};
        hits.emplace_back(hit);
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

    lines[obstruction.y][obstruction.x] = 'X';
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
