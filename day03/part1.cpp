#include <math.h>

#include <cstring>
#include <iostream>
#include <vector>

std::string input;
int pos = 0;
bool finished = false;
int total_sum = 0;
std::string first_number = "";
std::string second_number = "";

bool check(char to_check);
bool checknum(std::string* number);

bool parse_input();
bool parse_m();
bool parse_u();
bool parse_l();
bool parse_num();
bool parse_leftp();
bool parse_fstnum();
bool parse_comma();
bool parse_sndnum();
bool parse_rightp();

bool checknum(std::string* number) {
  if (check('0') || check('1') || check('2') || check('3') || check('4') ||
      check('5') || check('6') || check('7') || check('8') || check('9')) {
    char num = input[pos - 1];
    number->push_back(num);
    return true;
  }

  return false;
}

bool check(char to_check) {
  if (pos > (int)input.length()) {
    finished = true;
    return false;
  }

  if (input[pos] == to_check) {
    pos++;
    return true;
  }

  return false;
}

bool parse_input() {
  if (finished) {
    return false;
  }

  if (check('m')) {
    return parse_m();
  }

  pos++;
  return parse_input();
}

bool parse_m() {
  if (check('u')) {
    return parse_u();
  }

  pos++;
  return parse_input();
}

bool parse_u() {
  if (check('l')) {
    return parse_l();
  }

  pos++;
  return parse_input();
}

bool parse_l() {
  if (check('(')) {
    return parse_leftp();
  }

  pos++;
  return parse_input();
}

bool parse_leftp() {
  first_number = "";
  if (checknum(&first_number)) {
    return parse_fstnum();
  }

  pos++;
  return parse_input();
}

bool parse_fstnum() {

  if (checknum(&first_number)) {
    return parse_fstnum();
  }

  if (check(',')) {
    return parse_comma();
  }

  pos++;
  return parse_input();
}

bool parse_comma() {
  second_number = "";
  if (checknum(&second_number)) {
    return parse_sndnum();
  }

  pos++;
  return parse_input();
}

bool parse_sndnum() {
  if (checknum(&second_number)) {
    return parse_sndnum();
  }

  if (check(')')) {
    return parse_rightp();
  }

  pos++;
  return parse_input();
}

bool parse_rightp() {
  int n1 = std::stoi(first_number);
  int n2 = std::stoi(second_number);

  total_sum += n1 * n2;

  return parse_input();
}

int main() {
  first_number.resize(3);
  second_number.resize(3);
  while (getline(std::cin, input)) {
    pos = 0;
    finished = false;
    parse_input();
  }

  std::cout << "total sum of valid muls = " << total_sum << "\n";

  return 0;
}
