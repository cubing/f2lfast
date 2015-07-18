bool anyTestFailure = false;

void testCondition(bool expected, bool actual, string expectGood, string expectBad) {
  string output = string(expected == actual ? "OK" : "FAIL") + ": " + string(expected ? expectGood : expectBad);
  if (expected == actual) {
    cout << output << endl;
  } else {
    cerr << output << endl;
    anyTestFailure = true;
  }
}

void testPos(
    cubepos pos,
    bool expectF2LSolved,
    bool expectOLLSolved,
    bool expectSolvedUpToAUF) {
  testCondition(expectF2LSolved, isF2LSolved(pos), "F2L should be solved", "F2L should NOT be solved");
  testCondition(expectOLLSolved, isOLLSolved(pos), "OLL should be solved", "OLL should NOT be solved");
  testCondition(expectSolvedUpToAUF, isSolvedUpToAUF(pos), "Should be entirely solved (up to AUF)" , "Should NOT be entirely solved (up to AUF)");
}

void testAlg(
    const char* alg,
    bool expectF2LSolved,
    bool expectOLLSolved,
    bool expectSolvedUpToAUF) {
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

  cout << "----------------" << endl;
  if (anyTestFailure) {
    cerr << "All test passed: NO";
  } else {
    cout << "All test passed: YES";
  }
}
