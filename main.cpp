
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void iter(vector<vector<double>>& matrix,  vector<double>& y_vector, size_t n, vector<double>& result, double eps) {



    for (size_t i = 0; i != n; ++i) {
        result[i] = y_vector[i] / matrix[i][i];
    }

    vector<double> Xn(n);

    do {
        for (size_t i = 0; i != n; ++i) {
            Xn[i] = y_vector[i] / matrix[i][i];
            for (size_t j = 0; j != n; ++j) {
                if (i == j)
                    continue;
                else {
                    Xn[i] -= matrix[i][j] / matrix[i][i] * result[j];
                }
            }
        }

        bool flag = true;
        for (size_t i = 0; i != n - 1; ++i) {
            if (abs(Xn[i] - result[i]) > eps) {
                flag = false;
                break;
            }
        }

        for (size_t i = 0; i != n; ++i) {
            result[i] = Xn[i];
        }

        if (flag)
            break;
    } while (true);


}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "problem with args";
        return 1;
    }
    string file_name = argv[1];
    double eps = stod(string(argv[2]));

    ifstream file;
    file.open(file_name);

    size_t n;
    file >> n;
    vector<vector<double>> matrix(n, vector<double>(n));
    vector<double> y_vector(n);


    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n + 1; ++j) {
            if (j != n) {
                file >> matrix[i][j];
            } else {
                file >> y_vector[i];
            }
        }
    }
    file.close();

    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n + 1; ++j) {
            if (j != n) {
                cout << matrix[i][j] << "\t";
            } else {
                cout << y_vector[i] << "\t";
            }
        }
        cout << endl;
    }

    vector<double> result(n);
    iter(matrix, y_vector, n, result, eps);

    for (size_t i = 0; i != n; ++i) {
        cout << result[i] << "\t";
    }
    cout << endl;

    return 0;
}
