#ifndef CNOT_H
#define CNOT_H

#include <cassert>
#include "quantum.h"
#include "functions.h"

/// Controlled-Not matrix implementation
static const quantum::op cnot {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0}
};

/// Perform C-NOT operation on a System state
quantum::state controlled_not(quantum::state &s)
{
    return cnot * s;
};

#endif // CNOT_H
