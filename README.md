# `f2lfast`

An LL skip solver.

Takes a cube position that has cross solved, and finds an LL skip using standard triggers.

## C++

    git clone https://github.com/cubing/f2lfast ; cd f2lfast
    cd cpp
    make f2lfast
    ./f2lfast --scramble "F' R' U2 R F"


## JS

Needs to be run from a web server (due to web workers).

    git clone https://github.com/cubing/f2lfast ; cd f2lfast
    cd js
    open "http://localhost:8001" ; python -m SimpleHTTPServer 8001