#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
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


int main() {

    int variant;
    std::cout << "input from\n1 file\n2 handmade\nanything else random\n";
    std::cin >> variant;
    std::cout << "size of matrix\n";
    size_t n;
    std::cin >> n;
    double eps;
    std::cout << "epslilon\n";
    std::cin >> eps;
    vector<vector<double>> matrix(n, vector<double>(n));
    vector<double> y_vector(n);

    if(variant == 1) {
        std::cout << "filename\n";
        string file_name;
        std::cin >> file_name;
        ifstream file;
        file.open(file_name);

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

        

    }else if(variant == 2) {
        for (size_t i = 0; i != n; ++i) {
            for (size_t j = 0; j != n + 1; ++j) {
                if (j != n) {
                    cout << "matrix["<<  i << "][" << j << "]=";
                    cin >> matrix[i][j];
                } else {
                    cout << "y_matrix["<< i << "]=";
                    cin >> y_vector[i];            
                }
        }

        }       
    }else {
        srand(time(NULL));
        for(size_t i = 0; i != n ; ++i){
            for(size_t j = 0; j != n; ++ j) {
                if(i==j) {
                    continue;
                }
                matrix[i][j] = static_cast<double>(rand() % 59);
            }
        }
        for(size_t i = 0; i != n ; ++i){
            matrix[i][i] = 0;
            for(size_t j = 0; j != n; ++j) {
                if(i==j) {
                    continue;
                }
                matrix[i][i] += matrix[i][j] + 2;

            }
        }
        for(size_t i = 0; i !=n; ++i) {
            y_vector[i] = static_cast<double>(rand()%59);
        }
    }
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

    cout << "result\n\n";

    for (size_t i = 0; i != n; ++i) {
        cout << result[i] << "\t";
    }
    cout << endl;

    return 0;
}
