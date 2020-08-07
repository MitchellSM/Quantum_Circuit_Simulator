#include "quantum.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace q = quantum;

void print_prob(const state &s)
{
    cout << "\t\t|0>\t|1>" << endl << setprecision(4) << fixed
         << "Qubit 1\t\t" << measurement_prob(s, 0, 0) << "\t" 
         << measurement_prob(s, 0, 1) << endl
         << "Qubit 2\t\t" << measurement_prob(s, 1, 0) << "\t" 
         << measurement_prob(s, 1, 1) << endl;
}

void cnot_test()
{
    cout << "C-NOT Test:" << endl;
    q::qubit zero(1, 0);
    q::qubit one(0, 1);
    q::state s;

    vector<q::qubit> input(2);
    
    input[0] = zero;
    input[1] = zero;
    s = get_state(input);
    cout << "-------------------------------" << endl;
    cout << "Input: |00>\tProbability" << endl;
    print_prob(s);

    input[0] = zero;
    input[1] = one;
    s = get_state(input);
    cout << "-------------------------------" << endl;
    cout << "Input: |01>\tProbability" << endl;
    print_prob(s);

    input[0] = one;
    input[1] = zero;
    s = get_state(input);
    cout << "-------------------------------" << endl;
    cout << "Input: |10>\tProbability" << endl;
    print_prob(s);

    input[0] = one;
    input[1] = one;

    s = get_state(input);
    cout << "-------------------------------" << endl;
    cout << "Input: |11>\tProbability" << endl;
    print_prob(s);
    cout << "-------------------------------" << endl;
}

int main()
{
    cnot_test();
}