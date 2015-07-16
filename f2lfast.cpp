#include "cube_solver/cubepos.h"

#include <iostream>
#include <vector>

using namespace std;

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
      : name_(seq_string.c_str()),
        cost_(cost) {
    pos = alg2pos(seq_string.c_str());
  }
  const char* name_;
  cubepos pos;
  const int cost_;
};

vector<Alg> AUFs;

// Triggers are grouped by slot.
// This makes it easy to avoid applying triggers for a slot that is already solved;
vector<Alg> triggers[4];
const unsigned char SLOT_H_FL = 0;
const unsigned char SLOT_I_BL = 1;
const unsigned char SLOT_J_BR = 2;
const unsigned char SLOT_K_FR = 3;

void init_algs() {

  AUFs.push_back(Alg(""  , 0));
  AUFs.push_back(Alg("U+", 0));
  AUFs.push_back(Alg("U2", 0));
  AUFs.push_back(Alg("U-", 0));

  const int RL_BOOST = 1;
  const int SLEDGE_BOOST = 1;

  triggers[SLOT_H_FL].push_back(Alg("L- U- L+", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("L- U2 L+", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("L- U  L+", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("F+ U  F-", 3));
  triggers[SLOT_H_FL].push_back(Alg("F+ U2 F-", 3));
  triggers[SLOT_H_FL].push_back(Alg("F+ U- F-", 3));

  triggers[SLOT_I_BL].push_back(Alg("L+ U  L-", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("L+ U2 L-", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("L+ U- L-", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("B- U- B+", 3));
  triggers[SLOT_I_BL].push_back(Alg("B- U2 B+", 3));
  triggers[SLOT_I_BL].push_back(Alg("B- U  B+", 3));

  triggers[SLOT_J_BR].push_back(Alg("R- U- R+", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("R- U2 R+", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("R- U  R+", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("B+ U  B-", 3));
  triggers[SLOT_J_BR].push_back(Alg("B+ U2 B-", 3));
  triggers[SLOT_J_BR].push_back(Alg("B+ U- B-", 3));

  triggers[SLOT_K_FR].push_back(Alg("R+ U  R-", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("R+ U2 R-", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("R+ U- R-", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("F- U- F+", 3));
  triggers[SLOT_K_FR].push_back(Alg("F- U2 F+", 3));
  triggers[SLOT_K_FR].push_back(Alg("F- U  F+", 3));
  triggers[SLOT_K_FR].push_back(Alg("R- F+ R+ F-", 4 - SLEDGE_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("F+ R- F- R+", 4 - SLEDGE_BOOST));
}

int main(int argc, char *argv[]) {
  cubepos cp1 = alg2pos("R2 U+ R+ U+ R- U- R- U- R- U+ R-");
  cubepos cp2 = alg2pos("R2 U2 R2 U2 R2 U2");
  cubepos combo;
  cubepos::mul(cp1, cp2, combo);
  cout << combo.Singmaster_string() << endl;

  init_algs();
  cout << triggers[SLOT_H_FL][0].pos.Singmaster_string() << endl;
  cout << triggers[SLOT_H_FL][0].pos.Singmaster_string() << endl;
}