
vector<Alg> AUFs;

// Triggers are grouped by slot.
// This makes it easy to avoid applying triggers for a slot that is already solved;
const size_t NUM_SLOTS = 4;

vector<Alg> triggers[NUM_SLOTS];
enum F2LSlot {
  SLOT_H_FL = 0,
  SLOT_I_BL = 1,
  SLOT_J_BR = 2,
  SLOT_K_FR = 3
};

void init_algs() {

  AUFs.push_back(Alg(""  , 0));
  AUFs[0].name_ = ".";
  AUFs.push_back(Alg("U", 1));
  AUFs.push_back(Alg("U2", 1));
  AUFs.push_back(Alg("U'", 1));

  const int RL_BOOST = 1;
  const int SLEDGE_BOOST = 1;

  triggers[SLOT_H_FL].push_back(Alg("L' U' L", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("L' U2 L", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("L' U  L", 3 - RL_BOOST));
  triggers[SLOT_H_FL].push_back(Alg("F  U  F'", 3));
  triggers[SLOT_H_FL].push_back(Alg("F  U2 F'", 3));
  triggers[SLOT_H_FL].push_back(Alg("F  U' F'", 3));

  triggers[SLOT_I_BL].push_back(Alg("L  U  L'", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("L  U2 L'", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("L  U' L'", 3 - RL_BOOST));
  triggers[SLOT_I_BL].push_back(Alg("B' U' B", 3));
  triggers[SLOT_I_BL].push_back(Alg("B' U2 B", 3));
  triggers[SLOT_I_BL].push_back(Alg("B' U  B", 3));

  triggers[SLOT_J_BR].push_back(Alg("R' U' R", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("R' U2 R", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("R' U  R", 3 - RL_BOOST));
  triggers[SLOT_J_BR].push_back(Alg("B  U  B'", 3));
  triggers[SLOT_J_BR].push_back(Alg("B  U2 B'", 3));
  triggers[SLOT_J_BR].push_back(Alg("B  U' B'", 3));

  triggers[SLOT_K_FR].push_back(Alg("R  U  R'", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("R  U2 R'", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("R  U' R'", 3 - RL_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("F' U' F", 3));
  triggers[SLOT_K_FR].push_back(Alg("F' U2 F", 3));
  triggers[SLOT_K_FR].push_back(Alg("F' U  F", 3));
  triggers[SLOT_K_FR].push_back(Alg("R' F  R  F'", 4 - SLEDGE_BOOST));
  triggers[SLOT_K_FR].push_back(Alg("F  R' F' R", 4 - SLEDGE_BOOST));
}
