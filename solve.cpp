
string indentation[4] = {"    ", "   ", "  ", " "};

// Returns null if no solution is found.
string solveF2LWithSkip(cubepos scramble, int depthRemaining) {
  if (isSolvedUpToAUF(scramble)) {
    return "!";
  }
  else if (depthRemaining == 0) {
    return string();
  }
  for (Alg auf : AUFs) {
    cubepos pos1;
    cubepos::mul(scramble, auf.pos, pos1);
    for (int slot = 0; slot < NUM_SLOTS; slot++) {
      for (Alg trigger : triggers[slot]) {
        cubepos pos2;
        cubepos::mul(pos1, trigger.pos, pos2);

        // cout << indentation[depthRemaining] << auf.name_ + string(" ") + trigger.name_  << " (" << depthRemaining << ")" << endl;
        string solution = solveF2LWithSkip(pos2, depthRemaining - 1);
        if (solution.length() > 0) {
          return auf.name_ + string(" ") + trigger.name_ + string(" / ") + solution;
        }
      }
    }
  }
  return string();
}

string solve(cubepos scramble) {
  // Assume cross is solved for now.
  return solveF2LWithSkip(scramble, 2);
}