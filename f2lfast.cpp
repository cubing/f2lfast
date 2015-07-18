#include "cube_solver/cubepos.h"

#include <iostream>
#include <vector>

using namespace std;

const size_t NUM_EDGES = 12;
const size_t NUM_CORNERS = 8;

// Use raw source file includes for rudimentary decomposition.
// Include order still matters.
#include "alg.cpp"
#include "triggers.cpp"
#include "comparison.cpp"
#include "solve.cpp"
#include "test.cpp"

int main(int argc, char *argv[]) {
  init_algs();
  if (argc == 2 && strcmp(argv[1], "--test") == 0) {
    test();
    return 0;
  } else if (argc == 3 && strcmp(argv[1], "--scramble") == 0) {
    cubepos scramble = alg2pos(argv[2]);
    string solution = solve(scramble);
    cout << "Solution: " << solution << endl;
    return 0;
  } else {
    cout << "Usage: " << argv[0] << " [--test | --scramble <scramble>]";
    return 1;
  }
}