#ifndef QUANTUM_H
#define QUANTUM_H

#include <complex>
#include <cstddef>
#include <vector>
using namespace std;

namespace quantum
{
    typedef pair<complex<double>, complex<double>> qubit;

    typedef vector<complex<double>> state;

    typedef vector<vector<complex<double>>> op;
}

#endif