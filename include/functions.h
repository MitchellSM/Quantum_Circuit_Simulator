#include "quantum.h"
using namespace quantum;

op operator*(const op &lhs, const op &rhs);

state operator*(const op &lhs, const state &rhs);

void resize(op &A, int n, int m);

op transpose(const op &A);

state tensor(qubit a, qubit b);

op tensor(op a, op b);

state tensor(state a, qubit  b);

state get_state(vector<qubit>);

// Get the probability of measuring qubit q_measure in basis_state 0 or 1 
double measurement_prob(const state &s, int n_qubits, int q_measure, bool basis_state);
double measurement_prob(const qubit &q, bool basis_state);