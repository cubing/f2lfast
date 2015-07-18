
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
