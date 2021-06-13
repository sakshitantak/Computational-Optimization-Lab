#include <bits/stdc++.h>
using namespace std;

#define PAD(a) left << setw(a)

class LeastCostMethod {
    int row, col;
    vector<vector<int>> mat, feasSoln;
    vector<int> supply, demand;
    int cost, allocations;

   public:
    LeastCostMethod();
    void solve();
    void display();
};

LeastCostMethod::LeastCostMethod() {
    cout << "No. of rows: ";
    cin >> row;
    cout << "No. of columns: ";
    cin >> col;

    mat.resize(row);
    cout << "Matrix values: \n";
    for (int i = 0; i < row; i++) {
        cout << "Row " << i + 1 << ": ";
        mat[i].resize(col);
        for (int j = 0; j < col; j++) {
            cin >> mat[i][j];
        }
    }

    supply.resize(row);
    cout << "Supply for each row: \n";
    for (int i = 0; i < row; i++) {
        cout << "S" << i + 1 << ": ";
        cin >> supply[i];
    }

    demand.resize(col);
    cout << "Demand for each column: \n";
    for (int i = 0; i < col; i++) {
        cout << "D" << i + 1 << ": ";
        cin >> demand[i];
    }

    cout << "\nInput matrix: \n";
    cout << PAD(10) << " ";
    for (int i = 0; i < col; i++) {
        cout << PAD(6) << "D" + to_string(i + 1);
    }
    cout << "Supply\n";
    for (int i = 0; i < row; i++) {
        cout << PAD(10) << "S" + to_string(i + 1);
        for (int j = 0; j < col; j++) {
            cout << PAD(6) << mat[i][j];
        }
        cout << supply[i] << "\n";
    }
    cout << PAD(10) << "Demand";
    for (int i = 0; i < col; i++) {
        cout << PAD(6) << demand[i];
    }
    cout << "\n";
}

void LeastCostMethod::solve() {
    vector<bool> rowDone(row, false), colDone(col, false);
    int mxRow, mxCol, val, count = 0, minCost;
    feasSoln.resize(row, vector<int>(col));
    cost = allocations = 0;

    while (count != row + col) {
        val = INT32_MAX;
        for (int i = 0; i < row; i++) {
            if (rowDone[i]) continue;
            for (int j = 0; j < col; j++) {
                if (colDone[j]) continue;
                if (mat[i][j] < val) {
                    val = mat[i][j];
                    mxRow = i, mxCol = j;
                }
            }
        }

        minCost = min(supply[mxRow], demand[mxCol]);
        cost += minCost * val;
        allocations++;
        supply[mxRow] -= minCost;
        if (!supply[mxRow]) {
            rowDone[mxRow] = true;
            count++;
        }
        demand[mxCol] -= minCost;
        if (!demand[mxCol]) {
            colDone[mxCol] = true;
            count++;
        }
        feasSoln[mxRow][mxCol] = minCost;
    }
}

void LeastCostMethod::display() {
    cout << "\nBasic feasible solution: \n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (feasSoln[i][j]) {
                cout << PAD(8) << to_string(mat[i][j]) + "*" + to_string(feasSoln[i][j]);
            } else {
                cout << PAD(8) << mat[i][j];
            }
        }
        cout << "\n";
    }
    cout << "\nFinal cost: " << cost << "\n";
    cout << "Allocated cells: " << allocations;
    if (allocations == row + col - 1) {
        cout << " = " << row << "+" << col << "-1\n";
        cout << "Non-degenerate solution\n";
    } else {
        cout << " != " << row << "+" << col << "-1\n";
        cout << "Degenerate solution\n";
    }
}

int main() {
    LeastCostMethod lcm;

    lcm.solve();
    lcm.display();

    return 0;
}