
cubepos alg2pos(const char* seq_string) {
  moveseq alg = cubepos::parse_moveseq(seq_string);
  cubepos cp;
  for (int mov : alg) {
    cp.move(mov);
  }
  return cp;
}

class Alg {
public:
  Alg(string seq_string, int cost)
      : name_(seq_string),
        cost_(cost) {
    pos = alg2pos(seq_string.c_str());
  }
  string name_;
  cubepos pos;
  const int cost_;
};

void printCubies(const cubepos& pos) {
  for (int i = 0; i < NUM_EDGES; i++) {
    cout << "Edge #" << i << ": " << int(pos.e[i]) << endl;
  }
  for (int i = 0; i < NUM_CORNERS; i++) {
    cout << "Corner #" << i << ": " << int(pos.c[i]) << endl;
  }
}
