
#include "quantum.h"
#include <complex>
#include <numeric>
#include <utility>
using namespace std;
using namespace quantum;

/// Resize a given operator matrix to dimensions n*m
void resize(op &A, int n, int m)
{
    A.resize(n);
    for (auto &r: A) {
        r.resize(m);
        r.assign(m, 0);
    }
}

/// Perform a transpose operation on a given operator matrix
op transpose(const op &A)
{
    op result;
    int n = A.size();
    int m = A[0].size();
    resize(result, n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}

/// Overridden operator to multiply an operator matrix and an operator matrix
op operator*(const op &lhs, const op &rhs)
{
    op result;
    op rhs_cols = transpose(rhs);

    for (auto r: lhs) {
        vector<complex<double>> row;

        for (auto c: rhs_cols) {
            row.push_back(std::inner_product(r.begin(), r.end(), c.begin(),
            std::complex<double>(0,0)));
        }
        result.push_back(row);
    }

    return result;
}

///Takes two Qubits and computes their tensor product
state tensor(qubit a, qubit b){
    state s;
    s.resize(4);
    s[0] = get<0>(a) * get<0>(b);
    s[1] = get<0>(a) * get<1>(b);
    s[2] = get<1>(a) * get<0>(b);
    s[3] = get<1>(a) * get<1>(b);
    return s;
}

///Computes the tensor product of a 1xN system state and one Qubit
state tensor(state a, qubit  b){
    int ctr = 0; //System state iterator
    state s; //New System state
    s.resize(a.size()*2);
    for(unsigned int i = 0; i < a.size(); i++)
    {
        s[ctr] = a[i] * b.first;
        s[ctr+1] = a[i] * b.second;
        ctr+=2;
    }
    return s;
}

/// Computes the tensor product of two Hermitian operators
op tensor(op a, op b){
    op o; // New operator to store tensor product
    resize(o, a.size()*b.size(), a.size()*b.size());
    for(unsigned int i = 0; i < a.size(); i++)
    {
        for(unsigned int j = 0; j < a.size(); j++)
        {
            for(unsigned k = 0; k < b.size(); k++)
            {
                for(unsigned l = 0; l < b.size(); l++)
                {
                    o[k+i*b.size()][j*b.size() + l] = a[i][j]*b[k][l];
                }
            }
        }
    }
    return o;
}

/// Overridden operator to multiply an operator matrix and a system state
state operator*(const op &lhs, const state &rhs)
{
    state result;
    for (auto row: lhs) {
        result.push_back(
            std::inner_product(row.begin(), row.end(), rhs.begin(), std::complex<double>(0, 0))
        );
    }
    return result;
}

///Computes the tensor product of a vector of Qubits
state get_state(vector<qubit> q)
{
    //Compute initial state
    state s = tensor(q.at(0), q.at(1));

    //Compute whole state
    for(unsigned int i = 2; i < q.size(); i++)
    {
        s = tensor(s, q.at(i));
    }
    return s;
}

/// Compute the probability of a qubit in a specific basis
// eg. [c1 c2] in [1 0]
double measurement_prob(const qubit &q, bool basis_state)
{
    // c++ norm is |a|^2
    return norm(basis_state ? q.second : q.first);
}

/// Compute the probability of a qubit in a specific basis
// eg. [c1 c2 c3 c4] in [1 0 0 1]
double measurement_prob(const state &s, int n_qubits, int q_measure, bool basis_state)
{
    double p = 0;
    // Sum the probability of each system state
    for (int i = 0; i < s.size(); i++) {
        if (((i >> (n_qubits - 1 - q_measure)) & 1) == (int)basis_state) {
            p += std::norm(s[i]);
        }
    }
    return p;
}
