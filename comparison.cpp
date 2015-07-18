
bool isEqual(const cubepos& a, const cubepos& b) {
  for (int i = 0; i < NUM_EDGES; i++) {
    if (a.e[i] != b.e[i]) {
      return false;
    }
  }
  for (int i = 0; i < NUM_CORNERS; i++) {
    if (a.c[i] != b.c[i]) {
      return false;
    }
  }
  return true;
}

const char* u_turn_str = "U";
const int U_TURN = cubepos::parse_move(u_turn_str);

const size_t NUM_AUFs = 4;
const cubepos solvedUpToAUFs[NUM_AUFs] = {
  alg2pos(""),
  alg2pos("U"),
  alg2pos("U2"),
  alg2pos("U'"),
};

// Pair of {edge, corner} indices.
int slotIndices[NUM_SLOTS][2] {
  {6, 6}, // SLOT_H_FL
  {4, 4}, // SLOT_I_BL
  {5, 5}, // SLOT_J_BR
  {7, 7}  // SLOT_K_FR
};

bool isSlotSolved(F2LSlot slot, const cubepos& pos) {
  int edge_index = slotIndices[slot][0];
  if (pos.e[edge_index] != identity_cube.e[edge_index]) {
    return false;
  }
  int corner_index = slotIndices[slot][1];
  if (pos.c[corner_index] != identity_cube.c[corner_index]) {
    return false;
  }
  return true;
}

// The first few edges/corners are on U.
const int START_F2L_EDGE_INDEX = 4;
const int START_F2L_CORNER_INDEX = 4;

bool isF2LSolved(const cubepos& pos) {
  for (int i = START_F2L_EDGE_INDEX; i < NUM_EDGES; i++) {
    if (pos.e[i] != identity_cube.e[i]) {
      return false;
    }
  }
  for (int i = START_F2L_CORNER_INDEX; i < NUM_CORNERS; i++) {
    if (pos.c[i] != identity_cube.c[i]) {
      return false;
    }
  }
  return true; // TODO
}

bool isOLLSolved(const cubepos& pos) {
  if (!isF2LSolved(pos)) {
    return false;
  }
  for (int i = 0; i < START_F2L_EDGE_INDEX; i++) {
    if (pos.e[i] % 2 != 0) {
      return false;
    }
  }
  for (int i = 0; i < START_F2L_CORNER_INDEX; i++) {
    if (pos.c[i] >= START_F2L_CORNER_INDEX) {
      return false;
    }
  }
  return true;
}

bool isSolvedUpToAUF(const cubepos& pos) {
  for (int i = 0; i < NUM_AUFs; i++) {
    if (isEqual(pos, solvedUpToAUFs[i])) {
      return true;
    };
  }
  return false;
}
