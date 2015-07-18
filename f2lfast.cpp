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
#include "test.cpp"
#include "solve.cpp"

int main(int argc, char *argv[]) {
  init_algs();
  if (argc > 1) {
    if (strcmp(argv[1], "--test") == 0) {
      test();
      return 0;
    } else {
      cout << "Usage: " << argv[0] << " [--test]";
      return 1;
    }
  }

  // cubepos pos = alg2pos("R U' R' U R2 U2 R' L' B' R B L U2 R2");
  // cubepos scramble = alg2pos("F' R' U2 R F");
  cubepos scramble = alg2pos("U' R U R' U L' U' L");
  // cubepos scramble = alg2pos("R U' R' U R U2 R' U' R U R' L' U' L");
  string solution = solve(scramble);
  cout << "Solution: " << solution << endl;
}