#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <complex>
#include "deutsch.h"
#include "cnot.h"
#include "toffoli.h"

TEST_CASE("Tensor product of qubits", "[qubitxqubit]") 
{
    quantum::qubit z(1, 0);
    quantum::qubit o(0, 1);
    quantum::qubit p(1, 1);
    quantum::qubit m(1, -1);

    quantum::state zz = {1, 0, 0, 0};
    quantum::state zo = {0, 1, 0, 0};
    quantum::state oz = {0, 0, 1, 0};
    quantum::state oo = {0, 0, 0, 1};

    quantum::state mz = {1, 0, -1, 0};
    quantum::state mo = {0, 1, 0, -1};
    quantum::state zm = {1, -1, 0, 0};
    quantum::state om = {0, 0, 1, -1};
    quantum::state pz = {1, 0, 1, 0};
    quantum::state po = {0, 1, 0, 1};
    quantum::state zp = {1, 1, 0, 0};
    quantum::state op = {0, 0, 1, 1};
    quantum::state pm = {1, -1, 1, -1};
    quantum::state mp = {1, 1, -1, -1};

    REQUIRE(tensor(z, z) == zz);
    REQUIRE(tensor(z, o) == zo);
    REQUIRE(tensor(o, z) == oz);
    REQUIRE(tensor(o, o) == oo);
    REQUIRE(tensor(m, z) == mz);
    REQUIRE(tensor(m, o) == mo);
    REQUIRE(tensor(z, m) == zm);
    REQUIRE(tensor(o, m) == om);
    REQUIRE(tensor(p, z) == pz);
    REQUIRE(tensor(p, o) == po);
    REQUIRE(tensor(z, p) == zp);
    REQUIRE(tensor(o, p) == op);
    REQUIRE(tensor(p, m) == pm);
    REQUIRE(tensor(m, p) == mp);
}

TEST_CASE("Tensor products of qubit and state", "[qubitxstate]")
{
    quantum::qubit z(1, 0);
    quantum::qubit o(0, 1);

    quantum::state zp = {1, 1, 0, 0};
    quantum::state op = {0, 0, 1, 1};
    quantum::state pm = {1, -1, 1, -1};
    quantum::state mp = {1, 1, -1, -1};

    quantum::state zpz = {1, 0, 1, 0, 0, 0, 0, 0};
    quantum::state opz = {0, 0, 0, 0, 1, 0, 1, 0};
    quantum::state pmz = {1, 0, -1, 0, 1, 0, -1, 0};
    quantum::state mpz = {1, 0, 1, 0, -1, 0, -1, 0};
    quantum::state zpo = {0, 1, 0, 1, 0, 0, 0, 0};
    quantum::state opo = {0, 0, 0, 0, 0, 1, 0, 1};
    quantum::state pmo = {0, 1, 0, -1, 0, 1, 0, -1};
    quantum::state mpo = {0, 1, 0, 1, 0, -1, 0, -1};

    REQUIRE(tensor(zp, z) == zpz);
    REQUIRE(tensor(op, z) == opz);
    REQUIRE(tensor(pm, z) == pmz);
    REQUIRE(tensor(mp, z) == mpz);
    REQUIRE(tensor(zp, o) == zpo);
    REQUIRE(tensor(op, o) == opo);
    REQUIRE(tensor(pm, o) == pmo);
    REQUIRE(tensor(mp, o) == mpo);
}

TEST_CASE("Tensor product of two operators", "[opxop]")
{
    quantum::op op1 = {{1, -1},
                       {1,  0}};
    quantum::op op2 = {{0,   0},
                       {-1, -1}};
    quantum::op op1op2 = {{ 0,  0, 0, 0},
                          {-1, -1, 1, 1},
                          { 0,  0, 0, 0},
                          {-1, -1, 0, 0}};
    quantum::op op2op1 = {{ 0, 0,  0, 0},
                          { 0, 0,  0, 0},
                          {-1, 1, -1, 1},
                          {-1, 0, -1, 0}};
    REQUIRE(tensor(op1, op2) == op1op2);
    REQUIRE(tensor(op2, op1) == op2op1);
}

TEST_CASE("Get state from list of qubits" "[get_state]")
{
    quantum::qubit o(0, 1);
    quantum::qubit z(1, 0);
    quantum::qubit m(1, -1);

    quantum::state ozm = {0, 0, 0, 0, 1, -1, 0, 0};
    quantum::state omz = {0, 0, 0, 0, 1, 0, -1, 0};
    quantum::state zmo = {0, 1, 0, -1, 0, 0, 0, 0};
    quantum::state zom = {0, 0, 1, -1, 0, 0, 0, 0};
    quantum::state moz = {0, 0, 1, 0, 0, 0, -1, 0};
    quantum::state mzo = {0, 1, 0, 0, 0, -1, 0, 0};

    REQUIRE(get_state(std::vector<qubit>{o, z, m}) == ozm);
    REQUIRE(get_state(std::vector<qubit>{o, m, z}) == omz);
    REQUIRE(get_state(std::vector<qubit>{z, m, o}) == zmo);
    REQUIRE(get_state(std::vector<qubit>{z, o, m}) == zom);
    REQUIRE(get_state(std::vector<qubit>{m, o, z}) == moz);
    REQUIRE(get_state(std::vector<qubit>{m, z, o}) == mzo);
}

TEST_CASE("Qubit measurement probabilities", "[qubit_prob]")
{
    quantum::qubit z(1, 0);
    quantum::qubit o(0, 1);
    quantum::qubit p(1.0/sqrt(2.0), 1.0/sqrt(2.0));
    quantum::qubit m(1.0/sqrt(2.0), -1.0/sqrt(2.0));

    REQUIRE((measurement_prob(z, 0) - 1) < 1e-10);
    REQUIRE((measurement_prob(z, 1) - 0) < 1e-10);
    REQUIRE((measurement_prob(o, 1) - 1) < 1e-10);
    REQUIRE((measurement_prob(o, 0) - 0) < 1e-10);
    REQUIRE((measurement_prob(p, 0) - 0.5) < 1e-10);
    REQUIRE((measurement_prob(p, 1) - 0.5) < 1e-10);
    REQUIRE((measurement_prob(m, 1) == 0.5) < 1e-10);
    REQUIRE((measurement_prob(m, 0) == 0.5) < 1e-10);
}


TEST_CASE("State measurement probabilities", "[state_prob]")
{
    double n = 1.0 / sqrt(5.0);
    quantum::state s = {1.0*n, 0, -1.0*n, -1.0*n, 0, 0, 1.0*n, -1.0*n};
    n *= n;
    REQUIRE((measurement_prob(s, 3, 0, 0) - 3.0/n) < 1e-10);
    REQUIRE((measurement_prob(s, 3, 0, 1) - 2.0/n) < 1e-10);
    REQUIRE((measurement_prob(s, 3, 1, 0) - 1.0/n) < 1e-10);
    REQUIRE((measurement_prob(s, 3, 1, 1) - 4.0/n) < 1e-10);
    REQUIRE((measurement_prob(s, 3, 2, 0) - 3.0/n) < 1e-10);
    REQUIRE((measurement_prob(s, 3, 2, 1) - 2.0/n) < 1e-10);
}

TEST_CASE("Multiplication of operators", "[op*op]")
{
    quantum::op A = {{1, 0, 0, 1},
                     {0, -1, -1, 0},
                     {-1, 1, 0, 0},
                     {0, 0, 0, 1}};
    quantum::op B = {{0, 1, 0, 0},
                     {1, -1, -1, -1},
                     {0, 1, 1, 1},
                     {1, 0, 1, -1}};
    quantum::op AB = {{1, 1, 1, -1},
                      {-1, 0, 0, 0},
                      {1, -2, -1, -1},
                      {1, 0, 1, -1}};
    quantum::op BA = {{0, -1, -1, 0},
                      {2, 0, 1, 0},
                      {-1, 0, -1, 1},
                      {0, 1, 0, 0}};
    REQUIRE(A*B == AB);
    REQUIRE(B*A == BA);
}

TEST_CASE("Multiplication of operator and state", "[op*state]")
{
    quantum::op A = {{1, 0, 0, 1},
                     {0, -1, -1, 0},
                     {-1, 1, 0, 0},
                     {0, 0, 0, 1}};
    quantum::state zero = {1, 0, 0, 0};
    quantum::state one = {0, 1, 0, 0};
    quantum::state two = {0, 0, 1, 0};
    quantum::state three = {0, 0, 0, 1};
    REQUIRE(A*zero == quantum::state{1, 0, -1, 0});
    REQUIRE(A*one == quantum::state{0, -1, 1, 0});
    REQUIRE(A*two == quantum::state{0, -1, 0, 0});
    REQUIRE(A*three == quantum::state{1, 0, 0, 1});
}