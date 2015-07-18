
bool isEqual(cubepos a, cubepos b) {
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

// The first few edges/corners are on U.
const int START_F2L_EDGE_INDEX = 4;
const int START_F2L_CORNER_INDEX = 4;

bool isF2LSolved(cubepos pos) {
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

bool isOLLSolved(cubepos pos) {
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

bool isSolvedUpToAUF(cubepos pos) {
  cubepos check(pos);
  for (int i = 0; i < NUM_AUFs; i++) {
    if (isEqual(pos, solvedUpToAUFs[i])) {
      return true;
    };
  }
  return false;
}
