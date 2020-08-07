#include "quantum.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include "cnot.h"
using namespace std;
namespace q = quantum;

void print_prob(const state &s)
{
    cout << "\t\t|0>\t|1>" << endl << setprecision(4) << fixed
         << "Qubit 1\t\t" << measurement_prob(s, 2, 0, 0) << "\t"
         << measurement_prob(s, 2, 0, 1) << endl
         << "Qubit 2\t\t" << measurement_prob(s, 2, 1, 0) << "\t"
         << measurement_prob(s, 2, 1, 1) << endl;
}

void cnot_test()
{
    cout << "C-NOT Test:" << endl;
    q::qubit zero(1, 0);
    q::qubit one(0, 1);
    q::state s;

    vector<q::qubit> input(2);

    bool qubitOne, qubitTwo;

    cout << "Please enter the first qubit by typing (\'0\' or \'1\'): ";
    cin >> qubitOne;

    cout << "Please enter the second qubit by typing (\'0\' or \'1\'): ";
    cin >> qubitTwo;
    cout << endl;

    input[0] = (qubitOne) ? q::qubit(0,1) : q::qubit(1,0);
    input[1] = (qubitTwo) ? q::qubit(0,1) : q::qubit(1,0);


    s = get_state(input);
    s = controlled_not(s);
    cout << "-------------------------------" << endl;
    cout << "Input: |" << qubitOne << qubitTwo << ">\tProbability" << endl;
    print_prob(s);


}

int main()
{
    cnot_test();
    return 0;
}
