(function(f) {if (typeof MagicWorker !== "undefined") {
    MagicWorker.register("worker.js", f);
} else {f()}})(function() {

  var that = this;
  that.postMessage("Starting worker.");


  importScripts("lib/alg_jison.js", "lib/alg.js");
  importScripts("ksolve_def_parser.js", "puzzles/puzzles.js");
  importScripts("ksolvePuzzle.js");
  importScripts("f2lfast.js");


  this.addEventListener('message', function(e) {

    ollSkipCallback = function(alg) {
      this.postMessage('Candidate: ' + alg);
    }
    llSkipCallback = function(alg) {
      this.postMessage('LL Skip: ' + alg);
    }

    // that.postMessage("Worker received data:\n" + JSON.stringify(e.data, null, "  "));
    var kPuzzle = new ksolvePuzzle(puzzles[e.data.puzzle].def);
    // kPuzzle.state_ = [e.data.state];
    solveF2LWrapper(e.data.state);

  }, false);

});
