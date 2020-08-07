#include "quantum.h"
#include "functions.h"
#include "toffoli.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
namespace q = quantum;

void print_prob(const state &s)
{
    cout << "\t\t|0>\t|1>" << endl << setprecision(4) << fixed
         << "Qubit 1\t\t" << measurement_prob(s, 3, 0, 0) << "\t"
         << measurement_prob(s, 3, 0, 1) << endl
         << "Qubit 2\t\t" << measurement_prob(s, 3, 1, 0) << "\t"
         << measurement_prob(s, 3, 1, 1) << endl
         << "Qubit 3\t\t" << measurement_prob(s, 3, 2, 0) << "\t"
         << measurement_prob(s, 3, 2, 1) << endl;
}

void toffoli_test()
{
    cout << "Toffoli Test:" << endl;
    q::state s;

    vector<q::qubit> input(3);

    bool qubitOne, qubitTwo, qubitThree;

    cout << "Please enter the first qubit by typing (\'0\' or \'1\'): ";
    cin >> qubitOne;

    cout << "Please enter the second qubit by typing (\'0\' or \'1\'): ";
    cin >> qubitTwo;

    cout << "Please enter the third qubit by typing (\'0\' or \'1\'): ";
    cin >> qubitThree;
    cout << endl;

    input[0] = (qubitOne) ? q::qubit(0,1) : q::qubit(1,0);
    input[1] = (qubitTwo) ? q::qubit(0,1) : q::qubit(1,0);
    input[2] = (qubitThree) ? q::qubit(0,1) : q::qubit(1,0);

    s = get_state(input);
    s = toffoli_gate(s);
    cout << "-------------------------------" << endl;
    cout << "Input: |"<< qubitOne << qubitTwo << qubitThree << ">\tProbability" << endl;
    print_prob(s);

}

int main()
{
    toffoli_test();
}
