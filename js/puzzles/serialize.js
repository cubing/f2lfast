var fs = require("fs");

var OUTFILE = (__dirname + "/" + "puzzles.js");

var puzzleNames = ["222", "333", "pyram"];
var puzzles = {};

for (var i in puzzleNames) {
  console.log("Serializing " + puzzleNames[i]);
  puzzles[puzzleNames[i]] = {};

  puzzles[puzzleNames[i]].def = fs.readFileSync(__dirname + "/" + puzzleNames[i] + ".def", 'utf8');
  puzzles[puzzleNames[i]].svg = fs.readFileSync(__dirname + "/" + puzzleNames[i] + ".svg", 'utf8');
}

fs.writeFileSync(OUTFILE, "var puzzles = " + JSON.stringify(puzzles, null, "  "));
console.log("Done serializing to " + OUTFILE)