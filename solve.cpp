
string indentation[4] = {"    ", "   ", "  ", " "};

// The i-th position from the right is set iff slot #i is solved.
typedef unsigned char F2LSlotMask;

F2LSlotMask slotMask(const cubepos& pos) {
  F2LSlotMask mask = 0;
  for (size_t slot = 0; slot < NUM_SLOTS; slot++) {
    if (isSlotSolved(F2LSlot(slot), pos)) {
      mask |= 1 << slot;
    }
  }
  return mask;
}

bool slotInMaskIsSolved(F2LSlot slot, const F2LSlotMask mask) {
  return (mask & (1 << slot)) != 0;
}

// Returns a copy of `original` with all bits from `remove set to 0.
F2LSlotMask slotSubtract(F2LSlotMask original, F2LSlotMask remove) {
  return (original & (~remove));
}

bool secondMaskIsSubsetOfFirst(F2LSlotMask first, F2LSlotMask second) {
  return slotSubtract(first, second) != 0;
}

string slotMaskToString(F2LSlotMask mask) {
  string output = "";
  if (slotInMaskIsSolved(SLOT_H_FL, mask)) { output += "FL "; };
  if (slotInMaskIsSolved(SLOT_I_BL, mask)) { output += "BL "; };
  if (slotInMaskIsSolved(SLOT_J_BR, mask)) { output += "BR "; };
  if (slotInMaskIsSolved(SLOT_K_FR, mask)) { output += "FR "; };
  return output;
}

const int MAX_DEPTH_PER_SLOT = 3;

// Returns null if no solution is found.
string solveF2LWithSkip(const cubepos& scramble, int depthRemaining, F2LSlotMask mask) {
  if (isSolvedUpToAUF(scramble)) {
    return ".";
  }
  else if (depthRemaining == 0) {
    return string();
  }
  for (Alg auf : AUFs) {
    cubepos pos1;
    cubepos::mul(scramble, auf.pos, pos1);
    for (int slot = 0; slot < NUM_SLOTS; slot++) {
      if (slotInMaskIsSolved(F2LSlot(slot), mask)) {
        continue;
      }
      for (Alg trigger : triggers[slot]) {
        cubepos pos2;
        cubepos::mul(pos1, trigger.pos, pos2);

        string newlySlovedSlots = "";

        F2LSlotMask newMask = slotMask(pos2);
        int nextDepth = depthRemaining - 1;
        if (secondMaskIsSubsetOfFirst(newMask, mask)) {
          nextDepth = MAX_DEPTH_PER_SLOT;
          // cout << indentation[depthRemaining] << auf.name_ + string(" ") + trigger.name_  << " (" << depthRemaining << ")" << endl;
        }

        string solution = solveF2LWithSkip(pos2, nextDepth, newMask);
        if (solution.length() > 0) {
          string newlySlovedSlots = slotMaskToString(slotSubtract(newMask, mask));
          string slotComment = "";
          if (newlySlovedSlots != "") {
            slotComment = "/* " + newlySlovedSlots + "*/\n";
          }
          return auf.name_ + string(" ") + trigger.name_ + " " + slotComment + solution;
        }
      }
    }
  }
  return string();
}

string solve(const cubepos& scramble) {
  // Assume cross is solved for now.
  string solution;
  solution = solveF2LWithSkip(scramble, 1, slotMask(scramble));
  if (solution.length() > 0) { return solution; }
  solution = solveF2LWithSkip(scramble, 2, slotMask(scramble));
  if (solution.length() > 0) { return solution; }
  solution = solveF2LWithSkip(scramble, 4, slotMask(scramble));
  if (solution.length() > 0) { return solution; }
  return "Solution not found.";
}