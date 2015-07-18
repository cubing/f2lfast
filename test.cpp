
void printCubies(cubepos pos) {
  for (int i = 0; i < NUM_EDGES; i++) {
    cout << "Edge #" << i << ": " << int(pos.e[i]) << endl;
  }
  for (int i = 0; i < NUM_CORNERS; i++) {
    cout << "Corner #" << i << ": " << int(pos.c[i]) << endl;
  }
}

void testPos(
    cubepos pos,
    int expectF2LSolved,
    int expectOLLSolved,
    int expectSolvedUpToAUF) {
  cout <<
  ((isF2LSolved(pos) == expectF2LSolved) ? "OK" : "FAIL") << ": " <<
    (expectF2LSolved ? "F2L should be solved" : "F2L should NOT be solved") << endl;
  cout <<
  ((isOLLSolved(pos) == expectOLLSolved) ? "OK" : "FAIL") << ": " <<
    (expectOLLSolved ? "OLL should be solved" : "OLL should NOT be solved") << endl;
  cout <<
  ((isSolvedUpToAUF(pos) == expectSolvedUpToAUF) ? "OK" : "FAIL") << ": " <<
    (expectSolvedUpToAUF ? "Should be entirely solved (up to AUF)" : "Should NOT be entirely solved (up to AUF)") << endl;
}

void testAlg(
    const char* alg,
    int expectF2LSolved,
    int expectOLLSolved,
    int expectSolvedUpToAUF) {
  cout << "----------------" << endl;
  cout << "Test case: " << alg << endl;
  cubepos pos = alg2pos(alg);
  cout << pos.Singmaster_string() << endl;
  // printCubies(pos);
  testPos(pos, expectF2LSolved, expectOLLSolved, expectSolvedUpToAUF);
}

void test() {
  testAlg("U",
    true, true, true);
  // U-perm
  testAlg("R2 U R U R' U' R' U' R' U R'",
    true, true, false);
  // R-perm
  testAlg("R' U2 R U2 R' F R U R' U' R' F' R2 U'",
    true, true, false);
  // Sune
  testAlg("R U R' U R U2 R'",
    true, false, false);
  testAlg("R",
    false, false, false);
}
