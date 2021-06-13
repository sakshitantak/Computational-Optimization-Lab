#include <bits/stdc++.h>
using namespace std;

#define PAD(a) left << setw(a)
#define MAX(vec) max_element(vec.begin(), vec.end()) - vec.begin()

class VogelsApproximation {
    int row, col;
    vector<vector<int>> mat, feasSoln;
    vector<int> supply, demand;
    int cost, allocations;

   public:
    VogelsApproximation();
    void solve();
    void display();
};

VogelsApproximation::VogelsApproximation() {
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
    cout << "Supply for each row: ";
    for (int i = 0; i < row; i++) {
        cout << "S" << i + 1 << ": ";
        cin >> supply[i];
    }

    demand.resize(col);
    cout << "Demand for each column: ";
    for (int i = 0; i < col; i++) {
        cout << "D" << i + 1 << ": ";
        cin >> demand[i];
    }

    cout << "Given matrix: \n";
    cout << PAD(10) << " ";
    for (int i = 0; i < col; i++) {
        cout << PAD(10) << "D" + to_string(i + 1);
    }
    cout << "Supply\n";
    for (int i = 0; i < row; i++) {
        cout << PAD(10) << "S" + to_string(i + 1);
        for (int j = 0; j < col; j++) {
            cout << PAD(10) << mat[i][j];
        }
        cout << supply[i] << "\n";
    }
    cout << PAD(10) << "Demand";
    for (int i = 0; i < col; i++) {
        cout << PAD(10) << demand[i];
    }
    cout << "\n";
}

void VogelsApproximation::solve() {
    vector<int> rowDiff(row), colDiff(col);
    vector<bool> rowDone(row, false), colDone(col, false);
    int minR1, minR2, minC1, minC2, count = 0;
    feasSoln.resize(row, vector<int>(col));
    cost = allocations = 0;

    while (count != row + col) {
        minR1 = minR2 = minC1 = minC2 = INT32_MAX;

        for (int i = 0; i < row; i++) {
            rowDiff[i] = -1;
            if (rowDone[i]) continue;
            for (int j = 0; j < col; j++) {
                if (colDone[j]) continue;
                if (minR1 > mat[i][j]) {
                    minR2 = minR1;
                    minR1 = mat[i][j];
                }
            }
            rowDiff[i] = minR2 - minR1;
            if (minR2 == INT32_MAX) rowDiff[i] = minR1;
        }
        for (int j = 0; j < col; j++) {
            colDiff[j] = -1;
            if (colDone[j]) continue;
            for (int i = 0; i < row; i++) {
                if (rowDone[i]) continue;
                if (minC1 > mat[i][j]) {
                    minC2 = minC1;
                    minC1 = mat[i][j];
                }
            }
            colDiff[j] = minC2 - minC1;
            if (minC2 == INT32_MAX) colDiff[j] = minC1;
        }

        int rmx = MAX(rowDiff), cmx = MAX(colDiff);
        if (rowDiff[rmx] > colDiff[cmx]) {
            int cmn, val = INT32_MAX;
            for (int i = col - 1; i >= 0; i--) {
                if (!colDone[i] && mat[rmx][i] <= val) {
                    cmn = i;
                    val = mat[rmx][i];
                }
            }
            val = min(supply[rmx], demand[cmn]);

            feasSoln[rmx][cmn] = val;
            cost += val * mat[rmx][cmn];
            supply[rmx] -= val;
            if (!supply[rmx]) {
                rowDone[rmx] = true;
                count++;
            }
            demand[cmn] -= val;
            if (!demand[cmn]) {
                colDone[cmn] = true;
                count++;
            }
        } else {
            int rmn, val = INT32_MAX;
            for (int i = row - 1; i >= 0; i--) {
                if (!rowDone[i] && mat[i][cmx] <= val) {
                    rmn = i;
                    val = mat[i][cmx];
                }
            }
            val = min(supply[rmn], demand[cmx]);

            feasSoln[rmn][cmx] = val;
            cost += val * mat[rmn][cmx];
            supply[rmn] -= val;
            if (!supply[rmn]) {
                rowDone[rmn] = true;
                count++;
            }
            demand[cmx] -= val;
            if (!demand[cmx]) {
                colDone[cmx] = true;
                count++;
            }
        }
        allocations++;
    }
}

void VogelsApproximation::display() {
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
    VogelsApproximation va;

    va.solve();
    va.display();

    return 0;
}