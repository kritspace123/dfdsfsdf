//#include "Matrix.h"
#include <fstream>
#include <iostream>

using namespace std;

class Column {
public:
    int **m_colmn;
    int m_size;
    int flag = -1;

    Column(int n);

    void setColumn(int i, int *p);

    void getColumn();

    Column(const Column &colmn);

    Column& operator[](int a);

    ~Column();

    Column& operator=(int a);

};
Column& Column::operator=( int a) {
    m_colmn[flag][0] = a;
    return *this;
}
Column::Column(int n) {
    m_size = n;
    m_colmn = new int *[n];
}

void Column::setColumn(int i, int *p) {
    m_colmn[i] = p;
}

void Column::getColumn() {
    for (int i = 0; i < m_size; i++) {
        cout << m_colmn[i] << " ";
    }
    cout << endl;
}

Column& Column::operator[](int a) {
    flag = a;
    return *this;
}

Column::~Column() {
    delete[] m_colmn;
}

Column::Column(const Column &colmn) {
    m_size = colmn.m_size;
    m_colmn = new int *[m_size];
    for (int i = 0; i < m_size; i++) {
        m_colmn[i] = colmn.m_colmn[i];
    }
}

class Matrix {
public:
    friend class Column;

    friend istream &operator>>(istream &input, Matrix &matr);

    friend ostream &operator<<(ostream &output, const Matrix &matr);

    Matrix(int n, int arr[]);

    Matrix(int n);

    Matrix();

    ~Matrix();

    Matrix(const Matrix &matr);

    void getMatrix();

    Matrix operator+(const Matrix &matr) const;

    Matrix operator-(const Matrix &matr) const;

    Matrix operator*(const Matrix &matr) const;

    bool operator==(const Matrix &matr) const;

    Matrix operator!();

    Matrix operator()(int a, int b);

    int *operator[](int a);

    Column operator()(int a);

private:
    int **m_A;
    int m_size;
};

Matrix::Matrix(int n, int arr[]) {
    m_size = n;
    m_A = new int *[n];
    for (int i = 0; i < m_size; i++) {
        m_A[i] = new int[n];
        for (int j = 0; j < m_size; j++) {
            if (i == j) {
                m_A[i][j] = arr[i];
            } else {
                m_A[i][j] = 0;
            }
        }
    }
}
Matrix::Matrix(int n) {
    m_size = n;
    m_A = new int *[n];
    for (int i = 0; i < n; i++) {
        m_A[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                m_A[i][j] = 1;
            } else {
                m_A[i][j] = 0;
            }
        }
    }

}
Matrix::Matrix() {
    m_size = 0;
    m_A = NULL;
}
Matrix::~Matrix() {
    for (int i = 0; i < m_size; i++) {
        delete[] m_A[i];
    }
    delete[] m_A;
}
Matrix::Matrix(const Matrix &matr) {
    m_size = matr.m_size;
    m_A = new int *[m_size];
    for (int i = 0; i < m_size; i++) {
        m_A[i] = new int[m_size];
        for (int j = 0; j < m_size; j++) {
            m_A[i][j] = matr.m_A[i][j];
        }
    }

}
void Matrix::getMatrix() {
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            cout << m_A[i][j] << " ";
        }
        cout << "\n";
    }
}
Matrix Matrix::operator+(const Matrix &matr) const {
    if (m_size != matr.m_size) {
        exit(5);
    }
    Matrix test(m_size);
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            test.m_A[i][j] = m_A[i][j] + matr.m_A[i][j];
        }
    }
    return test;
}
Matrix Matrix::operator-(const Matrix &matr) const {
    if (m_size != matr.m_size) {
        exit(5);
    }
    Matrix test(m_size);
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            test.m_A[i][j] = m_A[i][j] - matr.m_A[i][j];
        }
    }
    return test;
}
Matrix Matrix::operator*(const Matrix &matr) const {
    if (m_size != matr.m_size) {
        exit(6);
    }
    Matrix test(m_size);
    for (int col = 0; col < m_size; col++) {
        for (int row = 0; row < m_size; row++) {
            int sum = 0;
            for (int k = 0; k < m_size; k++) {
                sum += m_A[row][k] * matr.m_A[k][col];
            }
            test.m_A[row][col] = sum;
        }
    }
    return test;

}
bool Matrix::operator==(const Matrix &matr) const {
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            if (m_A[i][j] != matr.m_A[i][j]) {
                return false;
            }
        }
    }
    return true;
}
Matrix Matrix::operator!() {
    Matrix test(m_size);
    for (int row = 0; row < m_size; row++) {
        for (int col = 0; col < m_size; col++) {
            test.m_A[row][col] = m_A[col][row];
        }
    }
    return test;
}
Matrix Matrix::operator()(int a, int b) {
    Matrix ans(m_size - 1);
    a -= 1;
    b -= 1;
    int *start = ans.m_A[0];
    for (int row = 0; row < m_size; row++) {
        for (int col = 0; col < m_size; col++) {
            if (row == a || col == b) {
                continue;
            } else {
                *start = m_A[row][col];
                start += 1;
            }
        }
    }
    return ans;
}
int *Matrix::operator[](int a) {
    if (a >= m_size) {
        cerr << "erorr size off" << endl;
    }
    return m_A[a];
}

Column Matrix::operator()(int a) {
    int **prom;
    prom = new int *[m_size];
    for (int i = 0; i < m_size; i++) {
        prom[i] = &(m_A[i][a]);
    }

    Column m(m_size);
    for (int k = 0; k < m_size; k++) {
        m.setColumn(k, prom[k]);
    }
    delete[] prom;
    return m;
}

istream &operator>>(istream &input, Matrix &matr) {
    matr.m_A = new int *[matr.m_size];
    for (int i = 0; i < matr.m_size; i++) {
        matr.m_A[i] = new int[matr.m_size];
        for (int j = 0; j < matr.m_size; j++) {
            input >> matr.m_A[i][j];
        }
    }
    return input;


}

ostream &operator<<(ostream &output, const Matrix &matr) {
    for (int i = 0; i < matr.m_size; i++) {
        for (int j = 0; j < matr.m_size; j++) {
            output << matr.m_A[i][j] << " ";
        }
        output << endl;
    }
    return output;
}


int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    int N, k;
    input >> N;

    input >> k;
    Matrix A(N), B(N), C(N), D(N);
    int *example = new int[N];
    for (int i = 0; i < N; i++) {
        example[i] = k;
    }
    Matrix K(N, example);
    input >> A >> B >> C >> D;
    Matrix T = (A + B * !C + K) * !D;

    A.getMatrix();
    cout << "\n";
    A[1][0] = 7777;
    A(1)[0] = 8888;
    A.getMatrix();

    output.close();
    input.close();

}