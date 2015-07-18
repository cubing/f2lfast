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

void testLLPos(
    cubepos pos,
    bool expectF2LSolved,
    bool expectOLLSolved,
    bool expectSolvedUpToAUF) {
  testCondition(expectF2LSolved, isF2LSolved(pos), "F2L should be solved", "F2L should NOT be solved");
  testCondition(expectOLLSolved, isOLLSolved(pos), "OLL should be solved", "OLL should NOT be solved");
  testCondition(expectSolvedUpToAUF, isSolvedUpToAUF(pos), "Should be entirely solved (up to AUF)" , "Should NOT be entirely solved (up to AUF)");
}

void testLLAlg(
    const char* alg,
    bool expectF2LSolved,
    bool expectOLLSolved,
    bool expectSolvedUpToAUF) {
  cout << "----------------" << endl;
  cout << "LL Test case: " << alg << endl;
  cubepos pos = alg2pos(alg);
  cout << pos.Singmaster_string() << endl;
  // printCubies(pos);
  testLLPos(pos, expectF2LSolved, expectOLLSolved, expectSolvedUpToAUF);
}

void testF2L(const char* alg, bool expectFL, bool expectBL, bool expectBR, bool expectFR) {
  cout << "----------------" << endl;
  cout << "F2L test case: " << alg << endl;
  cubepos pos = alg2pos(alg);
  testCondition(expectFL, isSlotSolved(SLOT_H_FL, pos), "FL should be solved", "FL should NOT be solved");
  testCondition(expectBL, isSlotSolved(SLOT_I_BL, pos), "BL should be solved", "BL should NOT be solved");
  testCondition(expectBR, isSlotSolved(SLOT_J_BR, pos), "BR should be solved", "BR should NOT be solved");
  testCondition(expectFR, isSlotSolved(SLOT_K_FR, pos), "FR should be solved", "FR should NOT be solved");
}

void test() {

  testLLAlg("U",
    true, true, true);
  // U-perm
  testLLAlg("R2 U R U R' U' R' U' R' U R'",
    true, true, false);
  // R-perm
  testLLAlg("R' U2 R U2 R' F R U R' U' R' F' R2 U'",
    true, true, false);
  // Sune
  testLLAlg("R U R' U R U2 R'",
    true, false, false);
  testLLAlg("R",
    false, false, false);

  testF2L("F U r U' R' F'", true, true, true, true);
  testF2L("L' U L", false, true, true, true);
  testF2L("L U L'", true, false, true, true);
  testF2L("R' U R", true, true, false, true);
  testF2L("R U R'", true, true, true, false);
  testF2L("F2", false, true, true, false);
  testF2L("L U' R U2 L' U R'", true, false, true, false);


  cout << "----------------" << endl;
  if (anyTestFailure) {
    cerr << "All test passed: NO";
  } else {
    cout << "All test passed: YES";
  }
}
