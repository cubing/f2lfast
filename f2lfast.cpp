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
      : name_(seq_string),
        cost_(cost) {
    pos = alg2pos(seq_string.c_str());
  }
  string name_;
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
  AUFs[0].name_ = ".";
  AUFs.push_back(Alg("U", 0));
  AUFs.push_back(Alg("U2", 0));
  AUFs.push_back(Alg("U'", 0));

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


// function solveF2L(state, depth, previousPairs, algo) {
//   if (DEBUG) { console.log(algo); };
//   // console.log(state);
//   var pairs = unsolvedF2LPairs(state);
//   // console.log("Pairs", pairs.length, previousPairs.length)
//   if (pairs.length < previousPairs.length) { // Doesn't check that all previously pairs stayed solved, but progress is progress.
//     if (pairs.length === 0) {
//       numCandidates += 1;
//       if (isOLLSolved(state)) {
//         ollSkipCallback(algo);
//         // console.log(state);
//       }
//       if (isLLSolvedIgnoringAUF(cloneState(state))){
//         llSkipCallback(algo);
//         if (KEEP_GOING) {
//           return null;
//         } else {
//           return algo;
//         }
//       } else {
//         return null;
//       }
//     } else {
//       a = solveF2L(state, 1, pairs, algo + " /* " + pairs + " */");
//       if (a && !KEEP_GOING) { return a; };
//       a = solveF2L(state, 2, pairs, algo + " /* " + pairs + " */");
//       if (a) { return a; };
//       // a = solveF2L(state, 3, pairs, algo);
//       // if (a) { return a; };
//     }
//   }
//   if (depth === 0) {
//     return null;
//   }
//   for (var i in AUFs) {
//     // console.log("i: " + i);
//     for (var j in pairs) {
//       // console.log("j: " + pairs[j]);
//       for (var k in triggers[pairs[j]]) {
//         // console.log("k: " + k);
//         ks.state_ = cloneState(state);
//         // console.log("AUF (" + i + "), trigger (" + k + ")");
//         // console.log(AUFs[i]);
//         ks.applyMove(AUFs[i]);
//         ks.applyMove(triggers[pairs[j]][k]);
//         var s = solveF2L(ks.state_, depth - 1, pairs, algo + " " + i + " " + k);
//         if (s) {
//           return s;
//         }
//       }
//     }
//   }
// }

// // k.applyAlg("F' R F' R' F R'");
// // k.applyAlg("R F' R F R' F");
// // k.applyAlg("U2 L B L B2 D L2 F' R' B2 R2 U2 F' L2 F D2 B2 R2 D2       B' F' L' B' U' F2 R2");
// // k.applyAlg("L' U R' F' U L2 U2 L' U' L U2 D R' D' F2 R2 U'          U D F R' D'");
// // k.applyAlg("L' U R' F' U L2 U2 L' U' L U2 D R' D' F2 R2 U'          U2 L F' U L2");
// // k.applyAlg("R U R' B U B'");


// function solveF2LWrapper(state) {
//   // TODO: verify / solve cross
//   console.log("solveF2LWrapper");
//   a = solveF2L(state, 1, unsolvedF2LPairs(state), "");
//   if (a && !KEEP_GOING) { return a; };
//   a = solveF2L(state, 2, unsolvedF2LPairs(state), "");
//   if (a && !KEEP_GOING) { return a; };
//   a = solveF2L(state, 3, unsolvedF2LPairs(state), "");
//   if (a && !KEEP_GOING) { return a; };
// }

bool isEqual(cubepos a, cubepos b) {
  for (int i = 0; i < 12; i++) {
    if (a.e[i] != b.e[i]) {
      return false;
    }
  }
  for (int i = 0; i < 8; i++) {
    if (a.c[i] != b.c[i]) {
      return false;
    }
  }
  return true;
}

const char* u_turn_str = "U";
const int U_TURN = cubepos::parse_move(u_turn_str);

bool isSolvedUpToAUF(cubepos pos) {
  cubepos check(pos);
  if (isEqual(pos, identity_cube)) { return true; };
  pos.move(U_TURN);
  if (isEqual(pos, identity_cube)) { return true; };
  pos.move(U_TURN);
  if (isEqual(pos, identity_cube)) { return true; };
  pos.move(U_TURN);
  if (isEqual(pos, identity_cube)) { return true; };
  return false;
}

// Returns null if no solution is found.
string solveF2LWithSkip(cubepos scramble, int depthRemaining) {
  if (depthRemaining == 0) {
    return string();
  }
  if (isSolvedUpToAUF(scramble)) {
    return "!";
  }
  for (Alg auf : AUFs) {
    cubepos pos1;
    cubepos::mul(scramble, auf.pos, pos1);
    for (int slot = 0; slot < 4; slot++) {
      for (Alg trigger : triggers[slot]) {
        cubepos pos2;
        cubepos::mul(pos1, trigger.pos, pos2);

        string indentation[4] = {"    ", "   ", "  ", " "};
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
  return solveF2LWithSkip(scramble, 3);
}

int main(int argc, char *argv[]) {
  init_algs();

  // cubepos scramble = alg2pos("F' R' U2 R F");
  // cubepos scramble = alg2pos("U' R U R' U L' U' L");
  cubepos scramble = alg2pos("R U' R' U R U2 R' U' R U R'");
  string solution = solve(scramble);
  cout << "Solution: " << solution << endl;
}