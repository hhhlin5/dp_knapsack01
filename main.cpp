/**
 * This file contains a dynamic programming solutions to the Knapsack problem of OPT(i,w,k)
 * Define OPT(i,w,k) to be the maximum value of any subset of the first i items of size exactly k whose total weight is exactly w.
 *--------------------------------------------------------------------------------------------------------------------------------
 * Consider the following recursive equation:
 * When i < k, OPT(i,w,k) = −∞
 * When w > 0 and k = 0, OPT(i,w,k) = −∞
 * When w = 0 and k > 0, OPT(i,w,k) = −∞
 * When w = 0 and k = 0, OPT(i,w,k) = 0
 * When wi > w, OPT(i,w,k) = OPT(i-1,w,k)
 * Otherwise, OPT(i,w,k) = max{OPT(i-1,w,k), vi + OPT(i-1,w-wi,k-1)}
 * --------------------------------------------------------------------------------------------------------------------------------
 * TODO:
 * [x] 1. Initialize a three-dimensional matrix to store solutions to subproblems.
 * [x] 2. Build the matrix using bottom-up dynamic programming algorithm with the above recursive equation.
 * [x] 3. If no solution exists, print out something.
 * [x] 4. Otherwise, implement a traceback function that traverses the matrix to find a solution to the problem.
 * --------------------------------------------------------------------------------------------------------------------------------
 * input: all the items with the format (value, weight)
 * output: a subset of items that satisfy the given constraints.
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Function to find the maximum value subset of the first i items with exactly l items and total weight W
void KnapsackSubset(int n, int W, int l, vector<int>& weights, vector<int>& values){
    // n --- total number of the items
    // W --- exact total weight
    // l --- number of subset meets the expected weight W

    /**  1. Initialize a 3D matrix to store solutions to subproblems **/
    vector<vector<vector<int>>> opt(n + 1, vector<vector<int>>(W + 1, vector<int>(l + 1, 0)));
    // vector<vector<vector<int>>>  --- This declares a 3D vector - opt[i][w][k]
    // opt(n + 1,..                 --- the size of the first dimension (i), indicating items from index 0 to n
    // vector<vector<int>>(W + 1,.. --- the size of the second dimension (w), indicating weight from 0 to W
    // vector<int>(l + 1, ..        --- the size of the third dimension (k), indicating weight from 0 to l
    // Note: when we enter the weight and the value, they should correspond one to the other


    /** 2. Build the matrix using bottom-up dynamic programming algorithm **/
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            for (int k = 1; k <= l; ++k) {

                // implement the recursive equation in the following cases:

                // When i < k, OPT(i,w,k) = −∞
                if (i < k) {
                    opt[i][w][k] = numeric_limits<int>::min();
                }

                    // When w > 0 and k = 0, OPT(i,w,k) = −∞
                else if (w > 0 && k == 0) {
                    opt[i][w][k] = numeric_limits<int>::min();
                }

                    // When w = 0 and k > 0, OPT(i,w,k) = −∞
                else if (w == 0 && k > 0){
                    opt[i][w][k] = numeric_limits<int>::min();
                }

                    // When w = 0 and k = 0, OPT(i,w,k) = 0
                else if (w == 0 && k == 0){
                    opt[i][w][k] = 0;
                }

                    // When wi > w, OPT(i,w,k) = OPT(i-1,w,k)
                else if (weights[i - 1] > w) {
                    opt[i][w][k] = opt[i - 1][w][k];
                }

                    // Other cases: OPT(i,w,k) = max{OPT(i-1,w,k), vi + OPT(i-1,w-wi,k-1)}
                else {
                    // Choose the maximum value between including or excluding the current item
                    opt[i][w][k] = max(opt[i - 1][w][k], values[i - 1] + opt[i - 1][w - weights[i - 1]][k - 1]);
                }
            }
        }
    }

    /** 3. If no subset exists, print a message and return **/
    if (opt[n][W][l] == 0 ||  opt[n][W][l] == numeric_limits<int>::min()) {
        cout << "No subset exists." << endl;
        return;
    }


    /** 4. If there is subsets: Implement a traceback function that traverses the matrix to find a solution to the problem. **/
    int i = n, w = W, k = l;
    vector<int> subset;
    while (i > 0 && w > 0 && k > 0) {
        if (opt[i][w][k] != opt[i - 1][w][k]) {
            subset.push_back(i);
            w -= weights[i - 1];
            --k;
        }
        --i;
    }

    // Print the result of the subset with its value and weight using the format: ith item: (value: XX, weight: XX)
    cout << "Subset with maximum value: \n";
    for (int i = subset.size() - 1; i >= 0; --i) {
        cout  << subset[i] << ": (value:" << values[subset[i] - 1] << ", " << "weight: " << weights[subset[i] - 1] << ")" << endl;
    }
    cout << endl;

}


int main() {
    int n, W, k;
    cout << "Enter the total number of items (n): ";
    cin >> n;

    vector<int> weights(n);
    vector<int> values(n);

    cout << "Enter the weights of the items: \n";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: \n";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    cout << "Enter the total weight (W): ";
    cin >> W;

    cout << "Enter the number of items in the subset (k): ";
    cin >> k;

    KnapsackSubset(n, W, k, weights, values);

    return 0;
}
