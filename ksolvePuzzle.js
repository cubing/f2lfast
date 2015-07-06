"use strict";

var def = {};
def["222"] = "Name 2x2\n\n# def-file by Kåre Krig\n# CORNERS: UBL UBR UFR UFL DBR DFR DFL\n# DBL is fixed. No B,Loc,D moves.\n\nSet CORNERS 7 3\n\nSolved\nCORNERS\n1 2 3 4 5 6 7\nEnd\n\nMove U\nCORNERS\n4 1 2 3 5 6 7\nEnd\n\nMove R\nCORNERS\n1 3 6 4 2 5 7\n0 2 1 0 1 2 0\nEnd\n\nMove F\nCORNERS\n1 2 4 7 5 3 6\n0 0 2 1 0 1 2\nEnd";
def["333"] = "Name 3x3x3\n\n# Kirjava\n# CORNERS URF, ULF, ULB, URB, DRF, DLF, DLB, DRB\n# EDGES UF UL UB UR FR FL BL BR DF DL DB DR\n\nSet CORNERS 8 3\nSet EDGES 12 2\n\nSolved\nCORNERS\n1 2 3 4 5 6 7 8\nEDGES\n1 2 3 4 5 6 7 8 9 10 11 12\nEnd\n\nMove U\nCORNERS\n4 1 2 3 5 6 7 8\nEDGES\n4 1 2 3 5 6 7 8 9 10 11 12\nEnd\n\nMove R\nCORNERS\n5 2 3 1 8 6 7 4\n1 0 0 2 2 0 0 1\nEDGES\n1 2 3 5 12 6 7 4 9 10 11 8\n0 0 0 1 1 0 0 1 0 0 0 1\nEnd\n\nMove F\nCORNERS\n2 6 3 4 1 5 7 8\n2 1 0 0 1 2 0 0\nEDGES\n6 2 3 4 1 9 7 8 5 10 11 12\nEnd\n\nMove D\nCORNERS\n1 2 3 4 6 7 8 5\nEDGES\n1 2 3 4 5 6 7 8 10 11 12 9\nEnd\n\nMove L\nCORNERS\n1 3 7 4 5 2 6 8\n0 2 1 0 0 1 2 0\nEDGES\n1 7 3 4 5 2 10 8 9 6 11 12\n0 1 0 0 0 1 1 0 0 1 0 0\nEnd\n\nMove B\nCORNERS\n1 2 4 8 5 6 3 7\n0 0 2 1 0 0 1 2\nEDGES\n1 2 8 4 5 6 3 11 9 10 7 12\nEnd";

// By convention, methods and variables ending in underscores are private.
// Be very wary of using them for anything but debugging.
var kSolvePuzzle = function(definition) {
  this.parser_ = ksolve_def_parser.parse(definition);
  this.state_ = this.newSolvedState_();
  this.stateSwap_ = this.newSolvedState_(); // Avoid allocations.
};

kSolvePuzzle.prototype = {
  newSolvedState_: function() {
    var state = {};
    for (var set in this.parser_.sets) {
      state[set] = {
        permutation: [],
        orientation: []
      };
      for (var i = 0; i < this.parser_.sets[set].num; i++) {
        state[set].permutation.push(this.parser_.solved[set].permutation[i] - 1);
      }
      for (var i = 0; i < this.parser_.sets[set].num; i++) {
        state[set].orientation.push(0);
      }
    }
    return state;
  },

  getState: function() {
    return this.state_;
  },

  setSVGElement: function(svgElement) {
    this.svgElement_ = svgElement;
    this.originalColors_ = {};

    for (var set in this.parser_.sets) {
      var num_pieces = this.parser_.sets[set].num;
      var num_orientations = this.parser_.sets[set].orientations;

      for (var loc = 0; loc < num_pieces; loc++) {
        for (var orientations = 0; orientations < num_orientations; orientations++) {
          var id = set + "-l" + loc + "-o" + orientations;
          this.originalColors_[id] = this.svgElement_.getElementById(id).style.fill;
        }
      }
    }
  },

  draw: function() {
    for (var set in this.parser_.sets) {
      for (var loc = 0; loc < this.parser_.sets[set].num; loc++) {
        for (var orientations = 0; orientations < this.parser_.sets[set].orientations; orientations++) {
          var id = set + "-l" + loc + "-o" + orientations;
          var from = set + "-l" + this.state_[set].permutation[loc] + "-o" + ((this.parser_.sets[set].orientations - this.state_[set].orientation[loc] + orientations) % this.parser_.sets[set].orientations);
          this.svgElement_.getElementById(id).style.fill = this.originalColors_[from];
        }
      }
    }
  },

  applyMove: function(moveString) {
    var move = this.parser_.moves[moveString];

    for (var set in this.parser_.sets) {

      for (var loc = 0; loc < this.parser_.sets[set].num; loc++) {
        var prevLoc = move[set].permutation[loc] - 1;

        this.stateSwap_[set].permutation[loc] = this.state_[set].permutation[prevLoc];

        var orientationChange = (typeof move[set].orientation === "undefined") ? 0 : move[set].orientation[loc];
        this.stateSwap_[set].orientation[loc] = (this.state_[set].orientation[prevLoc] + orientationChange) % this.parser_.sets[set].orientations
      }
    }

    var oldState = this.state_;
    this.state_ = this.stateSwap_;
    this.stateSwap_ = oldState;
  },

  applyAlg: function(moves) {
    for (var i in moves) {
      this.applyMove(moves[i]);
    }
  }
}