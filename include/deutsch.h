#ifndef DEUTSCH_H
#define DEUTSCH_H

#include "quantum.h"
#include "functions.h"
#include <cmath>
#include <iostream>

/// Hadamard Matrix implementation
static const quantum::op hadamard {
    {1.0/sqrt(2.0), 1.0/sqrt(2.0)},
    {1.0/sqrt(2.0), -1.0/sqrt(2.0)}
};

/// Identity Matrix implementation
static const quantum::op ident {
    {1.0, 0.0},
    {0.0, 1.0}
};

///Perform Deutsch Algorithm on a System state
quantum::state deutsch(const quantum::state &s, bool f0, bool f1)
{
    state t = tensor(hadamard, hadamard) * s;
    /*  The gate Uf maps (|00> - |01> + |10> - |11>) to (|0f(0)> - |0!f(0)> + |1f(1)> - |1!f(1)>),
        which swaps the first two components of the state if f(0) = 1 and swaps the last two if
        f(1) = 1
    */
    if (f0) {
        auto x = t[0];
        t[0] = t[1];
        t[1] = x;
    }
    if (f1) {
        auto x = t[2];
        t[2] = t[3];
        t[3] = x;
    }
    return tensor(hadamard, ident) * t;
}

#endif // DEUTSCH_H
