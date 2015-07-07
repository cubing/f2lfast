"use strict";

// By convention, methods and variables ending in underscores are private.
// Be very wary of using them for anything but debugging.
var ksolvePuzzle = function(definition) {
  this.parser_ = ksolve_def_parser.parse(definition);
  this.state_ = this.newSolvedState_();
  this.stateSwap_ = this.newSolvedState_(); // Avoid allocations.
};

ksolvePuzzle.prototype = {
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

  applyMove: function(move) {
    var wasString = false;
    if (typeof move === "string") {
      move = this.parser_.moves[move];
      wasString = true;
    }
    if (typeof move === "undefined") {
      throw new Error("Undefined move for puzzle (" + this.parser_.name + "): " + moveString);
    }

    for (var set in this.parser_.sets) {

      for (var loc = 0; loc < this.parser_.sets[set].num; loc++) {
        var prevLoc = move[set].permutation[loc] - (wasString ? 1 : 0);

        this.stateSwap_[set].permutation[loc] = this.state_[set].permutation[prevLoc];

        var orientationChange = (typeof move[set].orientation === "undefined") ? 0 : move[set].orientation[loc];
        this.stateSwap_[set].orientation[loc] = (this.state_[set].orientation[prevLoc] + orientationChange) % this.parser_.sets[set].orientations
      }
    }

    var oldState = this.state_;
    this.state_ = this.stateSwap_;
    this.stateSwap_ = oldState;
  },

  // invertState: {},

  serializeStateToKsolve: function() {
    var output = ""
    for (var set in this.parser_.sets) {
      output += set + "\n";
      // output += this.state_[set].permutation.map(function(x) {return x + 1;}).join(" ") + "\n";
      output += this.state_[set].permutation.join(" ") + "\n";
      output += this.state_[set].orientation.join(" ") + "\n";
    }
    output = output.slice(0, output.length - 1); // Trim last newline.
    return output;
  },

  printState: function() {
    console.log(this.serializeStateToKsolve());
  },

  applyAlg: function(algString) {
    var a = alg.cube.fromString(algString);
    for (var i in a) {
      var amount = (a[i].amount + 4) % 4;
      for (var j = 0; j < amount; j++) {
        this.applyMove(a[i].base);
      }
    }
  }
}