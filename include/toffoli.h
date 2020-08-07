#ifndef TOFFOLI_H
#define TOFFOLI_H

#include "quantum.h"
#include "functions.h"

/// Toffoli matrix implementation
static const quantum::op toffoli {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0}
};

/// Perform Toffoli operation on a System state
quantum::state toffoli_gate(const quantum::state &s)
{
    return toffoli * s;
}

#endif // TOFFOLI_H
