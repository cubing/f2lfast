try {
  var fs = require("fs");
  var vm = require("vm");

  function include(path) {
      var code = fs.readFileSync(path, 'utf-8');
      vm.runInThisContext(code, path);
  }

  include("ksolve_def_parser.js");
  include("ksolvePuzzle.js");
  include("puzzles/puzzles.js");
  include("lib/alg_jison.js");
  include("lib/alg.js");
} catch (e) {
  console.log("I hope this is not running in node.");
}

/*****************/

var def = puzzles["333"].def;

var cloneState = function(state) {
  return {
    CORNERS: {
      permutation: state.CORNERS.permutation.slice(0),
      orientation: state.CORNERS.orientation.slice(0)
    },
    EDGES: {
      permutation: state.EDGES.permutation.slice(0),
      orientation: state.EDGES.orientation.slice(0)
    }
  };
}

function toMove(algString) {
  var k = new ksolvePuzzle(def);
  k.applyAlg(algString)
  return cloneState(k.getState());
}



var AUFs = {
  "." : toMove(""  ),
  "U" : toMove("U" ),
  "U2": toMove("U2"),
  "U'": toMove("U'")
};

var triggers = {
  "H": {
    "L' U' L ": toMove("L' U' L "),
    "L' U2 L ": toMove("L' U2 L "),
    "L' U  L ": toMove("L' U  L "),
    "F  U  F'": toMove("F  U  F'"),
    "F  U2 F'": toMove("F  U2 F'"),
    "F  U' F'": toMove("F  U' F'")
  },
  "I": {
    "L  U  L'": toMove("L  U  L'"),
    "L  U2 L'": toMove("L  U2 L'"),
    "L  U' L'": toMove("L  U' L'"),
    "B' U' B ": toMove("B' U' B "),
    "B' U2 B ": toMove("B' U2 B "),
    "B' U  B ": toMove("B' U  B ")
  },
  "J": {
    "R' U' R ": toMove("R' U' R "),
    "R' U2 R ": toMove("R' U2 R "),
    "R' U  R ": toMove("R' U  R "),
    "B  U  B'": toMove("B  U  B'"),
    "B  U2 B'": toMove("B  U2 B'"),
    "B  U' B'": toMove("B  U' B'")
  },
  "K": {
    "R  U  R'": toMove("R  U  R'"),
    "R  U2 R'": toMove("R  U2 R'"),
    "R  U' R'": toMove("R  U' R'"),
    "R' F R F'": toMove("R' F R F'"),
    "F R' F' R": toMove("F R' F' R"),
    "F' U' F ": toMove("F' U' F "),
    "F' U2 F ": toMove("F' U2 F "),
    "F' U  F ": toMove("F' U  F ")
  },
};

// console.log(JSON.stringify(triggers));

// var kPuzzle = new ksolvePuzzle(def);
// kPuzzle.applyMove(triggers.K.K]);
// kPuzzle.applyMove("U");
// kPuzzle.applyMove(triggers.K.K2]);
// kPuzzle.applyAlg("U'");
// kPuzzle.applyMove(triggers.J.J]);
// kPuzzle.applyAlg("U'");
// kPuzzle.applyMove(triggers.J.J2]);
// kPuzzle.applyMove("U");
// kPuzzle.printState();

var c = {
  URF: 0,
  ULF: 1,
  ULB: 2,
  URB: 3,
  DRF: 4,
  DLF: 5,
  DLB: 6,
  DRB: 7
};

var e = {
  UF: 0,
  UL: 1,
  UB: 2,
  UR: 3,
  FR: 4,
  FL: 5,
  BL: 6,
  BR: 7,
  DF: 8,
  DL: 9,
  DB: 10,
  DR: 11
}

var k = new ksolvePuzzle(def);
// console.log(k.state_);

function unsolvedF2LPairs(state) {
  var cp = state.CORNERS.permutation;
  var co = state.CORNERS.orientation;
  var ep = state.EDGES.permutation;
  var eo = state.EDGES.orientation;

  var pairs = [];
  if (!(cp[c.DLF] == c.DLF && co[c.DLF] == 0 && ep[e.FL] == e.FL && eo[e.FL] == 0)) { pairs.push("H"); };
  if (!(cp[c.DLB] == c.DLB && co[c.DLB] == 0 && ep[e.BL] == e.BL && eo[e.BL] == 0)) { pairs.push("I"); };
  if (!(cp[c.DRB] == c.DRB && co[c.DRB] == 0 && ep[e.BR] == e.BR && eo[e.BR] == 0)) { pairs.push("J"); };
  if (!(cp[c.DRF] == c.DRF && co[c.DRF] == 0 && ep[e.FR] == e.FR && eo[e.FR] == 0)) { pairs.push("K"); };
  return pairs;
}

function isOLLSolved(state) {
  var cp = state.CORNERS.permutation;
  var co = state.CORNERS.orientation;
  var ep = state.EDGES.permutation;
  var eo = state.EDGES.orientation;
  if (unsolvedF2LPairs(state).length > 0) { return false; }
  if (co[c.URF] !== 0) { return false; }
  if (co[c.ULF] !== 0) { return false; }
  if (co[c.ULB] !== 0) { return false; }
  if (co[c.URB] !== 0) { return false; }
  if (eo[e.UF] !== 0) { return false; }
  if (eo[e.UL] !== 0) { return false; }
  if (eo[e.UB] !== 0) { return false; }
  if (eo[e.UR] !== 0) { return false; }

  return true;
}

function isLLSolved(state) {
  var cp = state.CORNERS.permutation;
  var co = state.CORNERS.orientation;
  var ep = state.EDGES.permutation;
  var eo = state.EDGES.orientation;
  if (unsolvedF2LPairs(state).length > 0) { return false; }
  if (cp[c.URF] !== c.URF) { return false; }
  if (cp[c.ULF] !== c.ULF) { return false; }
  if (cp[c.ULB] !== c.ULB) { return false; }
  if (cp[c.URB] !== c.URB) { return false; }
  if (co[c.URF] !== 0) { return false; }
  if (co[c.ULF] !== 0) { return false; }
  if (co[c.ULB] !== 0) { return false; }
  if (co[c.URB] !== 0) { return false; }
  if (ep[e.UF] !== e.UF) { return false; }
  if (ep[e.UL] !== e.UL) { return false; }
  if (ep[e.UB] !== e.UB) { return false; }
  if (ep[e.UR] !== e.UR) { return false; }
  if (eo[e.UF] !== 0) { return false; }
  if (eo[e.UL] !== 0) { return false; }
  if (eo[e.UB] !== 0) { return false; }
  if (eo[e.UR] !== 0) { return false; }

  return true;
}

function isLLSolvedIgnoringAUF(state) {
  k.state_ = state;
  if (isLLSolved(k.state_)) { return true; }
  k.applyMove("U");
  if (isLLSolved(k.state_)) { return true; }
  k.applyMove("U");
  if (isLLSolved(k.state_)) { return true; }
  k.applyMove("U");
  if (isLLSolved(k.state_)) { return true; }
  return false;
}

// k.applyMove(triggers.I["I2"]);
// k.applyMove(triggers.I["i" ]);
// k.applyMove(triggers.I["I'"]);
// k.applyMove(triggers.I["i2"]);
// console.log(solvedF2LPairs(k.state_));


var depthPerPair = 2;

var ks = new ksolvePuzzle(def);

DEBUG = false;
var KEEP_GOING = true;
var numCandidates = 0;

var llSkipCallback = function(algo) {
  console.log("LL SKIP:", algo);
};

var ollSkipCallback = function(algo) {
  console.log("Candidate #" + numCandidates + ":", algo);
};

// depth == depth left at this stage.
// triggers
function solveF2L(state, depth, previousPairs, algo) {
  if (DEBUG) { console.log(algo); };
  // console.log(state);
  var pairs = unsolvedF2LPairs(state);
  // console.log("Pairs", pairs.length, previousPairs.length)
  if (pairs.length < previousPairs.length) { // Doesn't check that all previously pairs stayed solved, but progress is progress.
    if (pairs.length === 0) {
      numCandidates += 1;
      if (isOLLSolved(state)) {
        ollSkipCallback(algo);
        // console.log(state);
      }
      if (isLLSolvedIgnoringAUF(cloneState(state))){
        llSkipCallback(algo);
        if (KEEP_GOING) {
          return null;
        } else {
          return algo;
        }
      } else {
        return null;
      }
    } else {
      a = solveF2L(state, 1, pairs, algo + " /* " + pairs + " */");
      if (a && !KEEP_GOING) { return a; };
      a = solveF2L(state, 2, pairs, algo + " /* " + pairs + " */");
      if (a) { return a; };
      // a = solveF2L(state, 3, pairs, algo);
      // if (a) { return a; };
    }
  }
  if (depth === 0) {
    return null;
  }
  for (var i in AUFs) {
    // console.log("i: " + i);
    for (var j in pairs) {
      // console.log("j: " + pairs[j]);
      for (var k in triggers[pairs[j]]) {
        // console.log("k: " + k);
        ks.state_ = cloneState(state);
        // console.log("AUF (" + i + "), trigger (" + k + ")");
        // console.log(AUFs[i]);
        ks.applyMove(AUFs[i]);
        ks.applyMove(triggers[pairs[j]][k]);
        var s = solveF2L(ks.state_, depth - 1, pairs, algo + " " + i + " " + k);
        if (s) {
          return s;
        }
      }
    }
  }
}

// k.applyAlg("F' R F' R' F R'");
// k.applyAlg("R F' R F R' F");
// k.applyAlg("U2 L B L B2 D L2 F' R' B2 R2 U2 F' L2 F D2 B2 R2 D2       B' F' L' B' U' F2 R2");
// k.applyAlg("L' U R' F' U L2 U2 L' U' L U2 D R' D' F2 R2 U'          U D F R' D'");
// k.applyAlg("L' U R' F' U L2 U2 L' U' L U2 D R' D' F2 R2 U'          U2 L F' U L2");
// k.applyAlg("R U R' B U B'");


function solveF2LWrapper(state) {
  // TODO: verify / solve cross
  console.log("solveF2LWrapper");
  a = solveF2L(state, 1, unsolvedF2LPairs(state), "");
  if (a && !KEEP_GOING) { return a; };
  a = solveF2L(state, 2, unsolvedF2LPairs(state), "");
  if (a && !KEEP_GOING) { return a; };
  a = solveF2L(state, 3, unsolvedF2LPairs(state), "");
  if (a && !KEEP_GOING) { return a; };
}
// console.log("Found: ", solveF2LWrapper(k.state_));
// console.log("Done");

function solve(algo) {
  console.log("Solving alg:", algo);
  var k = new ksolvePuzzle(def);
  k.applyAlg(algo);
  solveF2LWrapper(k.state_);
  console.log("Done solving alg:", algo);
}

// solve("L' U R' F' U L2 U2 L' U' L U2 D R' D' F2 R2 U'          U2 L F' U L2");

// kPuzzle.printState();
// kPuzzle.applyMove(st);
// kPuzzle.printState();
// kPuzzle.applyMove(st);
// kPuzzle.printState();
// kPuzzle.applyMove(st);
// kPuzzle.printState();