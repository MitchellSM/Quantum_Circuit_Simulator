#include "deutsch.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "Deutsch's Algorithm\n-------------------\n";
    bool f0, f1;
    cout << "Enter f(0): ";
    cin >> f0;
    cout << "Enter f(1): ";
    cin >> f1;

    vector<quantum::qubit> q;
    q.emplace_back(1, 0); // |0>
    q.emplace_back(0, 1); // |1>

    quantum::state s = get_state(q);
    quantum::state result = deutsch(s, f0, f1);

    cout << endl << "Final state: [ ";
    for (auto x: result) cout << x << ' ';
    cout << "]" << endl << endl;

    cout << "Probability of measuring |0>: " 
         << measurement_prob(result, 2, 0, 0) << endl;
    cout << "Probability of measuring |1>: " 
         << measurement_prob(result, 2, 0, 1) << endl << endl;
}