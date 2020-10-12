#pragma warning(disable : 4996)
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <iomanip>
#include <algorithm>


using namespace std;

typedef long double ld;

const int N = 4;
const double GAMMA = 0.9;
const ld EPS = 1e-4;
const double SOR_EPS = 1e-2;
const double SOR_STEP = 1e-1;
const int IT_CNT = 10;
const long long INFINITE = 1e18;

struct Matrix;

void lu(Matrix a, Matrix& u, Matrix& l, Matrix& p);

Matrix buildInverted(Matrix& l, Matrix& u, Matrix& p);


// Структура матрица, здесь опишем операции, которые будем производить с матрицами
struct Matrix {
    // Деструктор
    ~Matrix() = default;
    
    // Конструкторы
    
    Matrix() {
        a.resize(N);
        for (int i = 0; i < N; i++)
            a[i].resize(N);
    }

    Matrix(const Matrix& m) {
        a.resize(m.size());
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < m.a[i].size(); j++)
                a[i].push_back(m.a[i][j]);
        }
    }
    Matrix(int n, int m) {
        a.resize(n);
        for (int i = 0; i < n; i++)
            a[i].resize(m, 0);
    }
    Matrix(vector<vector<ld> > matr) {
        a = matr;
    }

    // Возвращает произведение 2 матриц
    Matrix operator * (Matrix m) const {
        Matrix result(a.size(), m.a[0].size());
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)m.a[0].size(); ++j)
                for (int k = 0; k < (int)m.a.size(); ++k)
                    result(i, j) += a[i][k] * m(k, j);
        return result;
    }

    // Возвращает произведение матрицы на число
    Matrix operator * (ld k) const {
        Matrix ans(a);
        for (auto& row : ans.a)
            for (auto& element : row)
                element *= k;
        return ans;
    }

    // Возвращает разность 2 матриц
    Matrix operator - (Matrix m) const {
        Matrix result(size(), len());
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)len(); ++j)
                result(i, j) = a[i][j] - m.a[i][j];
        return result;
    }

    // Возвращает сумму 2 матриц
    Matrix operator + (Matrix m) const {
        Matrix result(size(), len());
        for (int i = 0; i < (int)a.size(); ++i)
            for (int j = 0; j < (int)len(); ++j)
                result(i, j) = a[i][j] + m.a[i][j];
        return result;
    }

    // Возвращает элемент матрицы с индексами (i, j)
    ld& operator () (const int i, const int j) {
        return a[i][j];
    }

    // Возвращает скалярное произведение векторов
    ld operator % (Matrix m) {
        ld ans = 0;
        for (int i = 0; i < size(); i++) {
            assert(a[i].size() == m.a[i].size() && a[i].size() == 1);
            ans += a[i][0] * m(i, 0);
        }
        return ans;
    }

    // Возвращает транспонированную матрицу
    Matrix transpose() {
        Matrix res(a[0].size(), size());
        for (int i = 0; i < (int)a.size(); i++)
            for (int j = 0; j < (int)a[i].size(); j++)
                res(j, i) = a[i][j];
        return res;
    }

    // Добавляет столбцы матрицы M к исходной матрице
    void append(Matrix m) {
        for (int i = 0; i < (int)a.size(); i++) {
            a[i].resize(a[i].size() + m.a[i].size());
            copy(m.a[i].begin(), m.a[i].end(), a[i].end() - m.a[i].size());
        }
    }

    // Заполняет матрицу значением val
    void fillVal(ld val) {
        for (int i = 0; i < (int)a.size(); i++)
            fill(a[i].begin(), a[i].end(), val);
    }

    // Возвращает высоту матрицы
    int size() const {
        return a.size();
    }

    // Возвращает ширину матрицы
    int len() const {
        return a[0].size();
    }

    // Выводит матрицу
    void print(bool flag = false) {
        cout << endl;
        for (auto line : a) {
            for (auto element : line)
                if (flag)
                    cout << scientific << element << " " << fixed;
                else
                    cout << setw(11) << fixed << setprecision(7) << element << " ";
            cout << endl;
        }
    }

    // Считывает матрицу
    void read(int n, int m) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].resize(m);
            for (int j = 0; j < m; j++)
                cin >> a[i][j];
        }
    }

    // Создает единичную матрицу
    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
            res(i, i) = 1;
        return res;
    }

    // Значения матрицы
    vector<vector<ld>> a;

    // Возвращает обратную матриц
    Matrix inverted() {
        Matrix u, l, p;
        lu(*this, u, l, p);
        return buildInverted(l, u, p);
    }
};


// Возвращает векторную Евклидову норму 
ld vectorNorm3(Matrix a) {
    ld ans = 0;

    for (int i = 0; i < a.size(); i++) {
        ans += (a(i, 0) * a(i, 0));
    }

    return sqrt(ans);
}


// Возвращает матричную Евклидову норму
ld matrixNorm3(Matrix* b)
{
    Matrix a = *b;

    auto aT = a.transpose();
    auto aTa = a * aT;
    a = aTa;

    int n = a.size();
    while (true)
    {
        ld sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                sum += a(i, j) * a(i, j);

        if (sqrt(sum) <= EPS)
            break;

        ld mx = -1;
        int ii = -1, jj = -1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (abs(a(i, j)) > mx)
                {
                    mx = abs(a(i, j));
                    ii = i, jj = j;
                }

        ld alpha = 0.5 * atan(2 * a(ii, jj) / (a(ii,ii) - a(jj, jj)));
        ld c = cos(alpha), s = sin(alpha);

        vector<vector<ld>> b(a.size(), vector<ld>(a.size()));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                b[i][j] = a(i, j);

        for (int m = 0; m < n; m++) {
            b[m][ii] = c * a(m, ii) + s * a(m, jj);
            b[m][jj] = -s * a(m, ii) + c * a(m, jj);
        }

        for (int m = 0; m < n; m++) {
            a(ii, m) = c * b[ii][m] + s * b[jj][m];
            a(jj, m) = -s * b[ii][m] + c * b[jj][m];
            a(m, ii) = c * b[ii][m] + s * b[jj][m];
            a(m, jj) = -s * b[ii][m] + c * b[jj][m];
        }

        a(ii, jj) = c * b[ii][jj] + s * b[jj][jj];
        a(jj, ii) = c * b[ii][jj] + s * b[jj][jj];
    }

   ld mx = -1;
    for (int i = 0; i < n; i++)
        mx = max(mx, abs(a(i, i)));

    return sqrt(mx);
}


//Перемещает строки с максимальным элементом в LU разложении
void shift(Matrix& a, Matrix& u, Matrix& p, int j) {
    int maxIndex = j;
    ld maxItem = u(maxIndex, j);
    for (int i = j + 1; i < u.size(); i++)
        if (abs(u(i, j)) > maxItem) {
            maxIndex = i;
            maxItem = abs(u(i, j));
        }
    swap(u.a[j], u.a[maxIndex]);
    swap(a.a[j], a.a[maxIndex]);
    swap(p.a[j], p.a[maxIndex]);
}


// Возвращает матрицу L, матрицу U и матрицу P LU - разложения матрицы A
void lu(Matrix a, Matrix& u, Matrix& l, Matrix& p) {
    u = a;
    p = Matrix::identity(u.size());
    for (int i = 0; i < N; i++) {
        shift(a, u, p, i);

        for (int j = N - 1; j >= i; j--)
            u(i, j) /= u(i, i);

        for (int k = i + 1; k < N; k++)
            for (int j = N - 1; j >= i; j--)
                u(k, j) -= u(i, j) * u(k, i);

        for (int j = 0; j <= i; j++) {
            l(i, j) = a(i, j);
            for (int k = 0; k < j; k++)
                l(i, j) -= l(i, k) * u(k, j);
            if (i == j && abs(l(i, j)) < EPS) {
                return;
            }
        }
    }
}


// Решение СЛАУ методом LU разложения
Matrix solve(Matrix& l, Matrix& u, Matrix& p, Matrix& b) {
    auto b1 = p * b;
    Matrix y((int)l.size(), 1);
    for (int i = 0; i < (int)l.size(); i++) {
        y(i, 0) = b1(i, 0);
        for (int j = 0; j < i; j++) {
            y(i, 0) -= y(j, 0) * l(i, j);
        }
        y(i, 0) /= l(i, i);
    }

    Matrix x((int)u.size(), 1);
    for (int i = (int)u.size() - 1; i >= 0; i--) {
        x(i, 0) = y(i, 0);
        for (int j = i + 1; j < (int)u.size(); j++) {
            x(i, 0) -= u(i, j) * x(j, 0);
        }
    }

    return x;
}


// Возвращает обратную матрицу по матрицам L U P. 
Matrix buildInverted(Matrix& l, Matrix& u, Matrix& p) {
    Matrix inverted(l.size(), 0);
    Matrix eColumn(l.size(), 1);
    for (int i = 0; i < (int)l.size(); i++) {
        eColumn.fillVal(0);
        eColumn(i, 0) = 1;
        inverted.append(solve(l, u, p, eColumn));
    }
    return inverted;
}


// Возвращает число обусловленностией матрицы A
ld cond(Matrix a) {
    auto a_1 = a.inverted();
    return matrixNorm3(&a) * matrixNorm3(&a_1);
}


// Вывод результатов
void printHead() {
    cout << setw(7) << "|" << setw(7) << "|" << setw(7) << "|" << setw(12) << "Residual |" <<
        setw(12) << "Error |" << endl;
    cout << setw(7) << "Itr |" << setw(7) << "tau |" << setw(7) << "q |" <<
        setw(12) << "norm |" << setw(12) << "estimate |" <<
        setw(9) << "x1" << setw(9) << "x2" << setw(9) << "x3" << setw(9) << "x4" << endl;
}

// Вывод результатов
void printRow(int it, ld tau, ld q, ld resNorm, ld erEt, Matrix x, ld alpha = INFINITE) {
    cout << setw(6) << it << "|";
    cout << setw(6) << fixed << setprecision(4) << tau << "|";
    cout << setw(6) << fixed << setprecision(3) << q << "|";
    cout << setw(11) << fixed << setprecision(7) << resNorm << "|";
    cout << setw(11) << fixed << setprecision(7) << erEt << "|";
    for (int i = 0; i < x.size(); i++) {
        cout << setw(9) << fixed << setprecision(5) << x(i, 0);
    }
    if (alpha != INFINITE)
        cout << "|" << setw(9) << fixed << setprecision(5) << alpha;
    cout << endl;
}


// Возвращает оценку погрешности приближенного решения
ld vectorError(Matrix a, Matrix x, Matrix b) {
    auto b1 = a * x;
    return cond(a) * vectorNorm3(b - b1) / vectorNorm3(b);
}


// Решение СЛАУ методом наискорейшего спуска
Matrix steepestDescent(Matrix a, Matrix b) {
    cout << "Method of steepest descent" << endl;

    vector <Matrix> x, r;
    x.push_back(b);
    r.push_back(a * x[0] - b);
    
    int it;
    int theoryIt = (-log10(EPS) * cond(a));
    int freq = ceil(1.0 * theoryIt / IT_CNT);

    printHead();

    ld q;

    for (it = 1; vectorNorm3(r.back()) > EPS; it++) {
        ld tau = (r.back() % r.back()) / ((a * r.back()) % r.back());
        x.push_back(x.back() - r.back() * tau);
        r.push_back(a * x[it] - b);

        if (it == 1)
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - Matrix(N, 1));
        else
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - x[it - 2]);

        if (it % freq == 0 || vectorNorm3(r.back()) <= EPS) {
            printRow(it, tau, q, vectorNorm3(r.back()), vectorError(a, x.back(), b), x.back());
        }
    }

    cout << scientific << vectorError(a, x.back(), b) << " " << fixed;
    cout << "Theoretic number of iterations: " << theoryIt << endl;
    return x.back();
}


//Решение СЛАУ методом сопряженных градиентов
Matrix conjugateGradientMethod(Matrix A, Matrix b) {
    cout << "Conjugate gradient method" << endl;
    vector <Matrix> x, r;
    vector <ld> a, t;
    int it;
    int theoryIt = (log(2 / EPS) / 2 * sqrt(cond(A)));
    //int freq = theoryIt / IT_CNT;
    x.push_back(Matrix(N, 1));
    r.push_back(A * x[0] - b);
    a = { 0, 1 };
    t = { 0, (r[0] % r[0]) / ((A * r[0]) % r[0]) };
    x.push_back(x[0] - r[0] * t[1]);
    r.push_back(A * x[1] - b);

    printHead();

    for (it = 1; vectorNorm3(r.back()) > EPS; it++) {
        t.push_back((r[it] % r[it]) / ((A * r[it]) % r[it]));
        a.push_back(1.0 / (1 - r[it] % r[it] * t[it + 1] / ((r[it - 1]) % r[it - 1] * t[it] * a[it])));
        x.push_back(x[it] * a[it + 1] + x[it - 1] * (1 - a[it + 1]) - r[it] * t[it + 1] * a[it + 1]);
        r.push_back(A * x[it + 1] - b);

        ld q = vectorNorm3(x.back() - x[x.size() - 2]) / vectorNorm3(x[x.size() - 2] - x[x.size() - 3]);
        printRow(it, t[it], q, vectorNorm3(r.back()), vectorError(A, x.back(), b), x.back(), a.back());
    }

    cout << scientific << vectorError(A, x.back(), b) << " " << fixed;

    cout << "Theoretic number of iterations: " << theoryIt << endl;
    return x.back();
}


// Решение СЛАУ методом простой итерации
Matrix simpleIteration(Matrix a, Matrix b) {
    cout << "Simple Iteration Method:" << endl;
    vector <Matrix> x, r;
    ld tau = GAMMA * 2 / matrixNorm3(&a);
    int it;
    int theoryIt = int(log(1 / EPS) / 2 * cond(a));
    int freq = ceil(1.0 * theoryIt / IT_CNT);
    x.push_back(b);
    r.push_back(a * x[0] - b);
    ld q;

    printHead();

    for (it = 1; vectorNorm3(r.back()) > EPS; it++) {
        x.push_back(x.back() - (a * x[it - 1] - b) * tau);
        r.push_back(a * x[it] - b);
        if (it == 1)
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - Matrix(N, 1));
        else
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - x[it - 2]);
        if (it % freq == 0 || vectorNorm3(r.back()) <= EPS)
            printRow(it, tau, q, vectorNorm3(r.back()), vectorError(a, x.back(), b), x.back());
    }
    cout << scientific << vectorError(a, x.back(), b) << " " << fixed;
    
    cout << "Theoretic number of iterations: " << theoryIt << endl;
    return x.back();
}


// Решение СЛАУ методом ПВР
Matrix SOR(Matrix a, Matrix b) {
    ld w, w_best = 0;
    int itr = 1e9;
    int theoryIt = int(log(1 / EPS) / 4 * sqrt(cond(a)));
    int freq = ceil(1.0 * theoryIt / IT_CNT);
    cout << "SOR - choosing the optimal w" << endl;
    for (w = SOR_STEP; w < 2; w += SOR_STEP)
    {
        vector <Matrix> x, r;
        x.push_back(Matrix(N, 1));
        r.push_back(a * x[0] - b);
        int it;
        for (it = 1; vectorNorm3(r.back()) > SOR_EPS; it++) {
            Matrix xNew = x.back();
            for (int i = 0; i < N; i++)
            {
                xNew(i, 0) = b(i, 0);
                for (int j = 0; j < N; j++)
                {
                    if (i != j)
                        xNew(i, 0) = xNew(i, 0) - a(i, j) * xNew(j, 0);
                }
                xNew(i, 0) /= a(i, i);
                xNew(i, 0) = w * xNew(i, 0) + (1 - w) * x.back()(i, 0);
            }
            x.push_back(xNew);
            r.push_back(a * x[it] - b);
        }
        cout << "w = " << w << "  Itr = " << it - 1 << endl;
        if ((it - 1) < itr)
        {
            w_best = w;
            itr = it - 1;
        }
    }
    cout << endl << "w* = " << w_best << "  ItrMin = " << itr << endl << endl;
    cout << "SOR:" << endl;
    vector <Matrix> x, r;
    ld q;
    x.push_back(b);
    r.push_back(a * x[0] - b);

    printHead();

    for (int it = 1; vectorNorm3(r.back()) > EPS; it++) {
        Matrix xNew = x.back();
        for (int i = 0; i < N; i++)
        {
            xNew(i, 0) = b(i, 0);
            for (int j = 0; j < N; j++)
            {
                if (i != j)
                    xNew(i, 0) -= a(i, j) * xNew(j, 0);
            }
            xNew(i, 0) /= a(i, i);
            xNew(i, 0) = w_best * xNew(i, 0) + (1 - w_best) * x.back()(i, 0);
        }
        x.push_back(xNew);
        r.push_back(a * x[it] - b);
        if (it == 1)
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - Matrix(N, 1));
        else
            q = vectorNorm3(x[it] - x[it - 1]) / vectorNorm3(x[it - 1] - x[it - 2]);
        if (it % freq == 0 || vectorNorm3(r.back()) <= EPS)
            printRow(it, w_best, q, vectorNorm3(r.back()), vectorError(a, x.back(), b), x.back());
    }
    cout << scientific << vectorError(a, x.back(), b) << " " << fixed;
    cout << "Theoretic number of iterations: " << theoryIt << endl;
    return x.back();
}


void printComparison(Matrix x, Matrix x1) {
    cout << endl << "Comparison with the direct method(x* - x):";
    (x1 - x).print(true);
}


int main() {
    freopen("input.txt", "r", stdin);
    //freopen("ouput.txt", "w", stdout);

    Matrix a, x, b, l, u, p;
    b = Matrix({ { 1.0 }, { 2.0 }, { 3.0 }, { 4.0 } });
    a.read(N, N);
    cout << "b:";
    b.print();
    cout << "a:";
    a.print();
    lu(a, u, l, p);
    x = solve(l, u, p, b);
    cout << "x:";
    x.print();
    cout << "Matrix norm : " << matrixNorm3(&a) << endl;
    auto solve1 = simpleIteration(a, b);
    printComparison(x, solve1);
    cout << endl;
    auto solve2 = steepestDescent(a, b);
    printComparison(x, solve2);
    cout << endl;
    auto solve3 = SOR(a, b);
    printComparison(x, solve3);
    cout << endl;
    auto solve4 = conjugateGradientMethod(a, b);
    printComparison(x, solve4);
    cout << endl;
}
