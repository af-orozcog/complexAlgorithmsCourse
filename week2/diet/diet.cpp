#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const double EPS = 1e-5;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
            a(a),
            b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
            column(column),
            row(row)
    {}
    Position():column(0),row(0){}
    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(a, b);
}

pair<bool,Position> SelectPivotElement(
        const Matrix &a,
        std::vector <bool> &used_rows,
        std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while(used_columns[pivot_element.column])
        ++pivot_element.column;
    double biggest = 0;
    for(int i = 0; i < used_rows.size();++i){
        if(used_rows[i])continue;
        if(fabs(a[i][pivot_element.column]) > biggest)
            biggest = fabs(a[i][pivot_element.column]), pivot_element.row = i;
    }
    pivot_element.column = 0;
    pair<bool,Position> ans;
    ans.second = pivot_element;
    ans.first = 1;
    if(biggest == 0) ans.first = 0;
    return ans;
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}


void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    double divide = a[pivot_element.row][pivot_element.column];
    for(int i = pivot_element.column; i < (int)a[0].size();++i)
        a[pivot_element.row][i] /= divide;
    b[pivot_element.row] /= divide;
    for(int i = 0;i < (int)a.size();++i){
        if(i == pivot_element.row) continue;
        double mul = -a[i][pivot_element.column];
        for(int j = pivot_element.column; j < (int)a[0].size(); ++j)
            a[i][j] += a[pivot_element.row][j]*mul;
        b[i] += b[pivot_element.row]*mul;
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

pair<bool,Column> SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    bool ans = 1;
    for (int step = 0; step < size; ++step) {
        pair<bool,Position> pivot_element = SelectPivotElement(a, used_rows, used_columns);
        pivot_element.second.column = step;
        if(!pivot_element.first) break;
        SwapLines(a, b, used_rows, pivot_element.second);
        ProcessPivotElement(a, b, pivot_element.second);
        MarkPivotElementUsed(pivot_element.second, used_rows, used_columns);
    }
    pair<bool,Column> anss;
    anss.first = ans;
    anss.second = b;
    return anss;
}

pair<int, vector<double>> solve_diet_problem(
        int n,
        int m,
        Matrix &A,
        Column &b,
        vector<double> c) {
    Matrix solve(m,std::vector <double> (m, 0.0));
    Column sendB(m);
    pair<int,vector<double>> ans;
    ans.second.resize(m,0.0);
    ans.first = -1;
    double ma = -1000000000.0;
    for(int i = 0; i < (1<<(n+m+1));++i){
        int j = 0;
        int coun = 0;
        int co = i;
        while(co && coun < m){
            if(co&1 && coun < m)solve[coun] = A[j],sendB[coun] = b[j],++coun;
            ++j;
            co >>= 1;
        }
        if(coun > m || coun < m) continue;
        /*cout << "which matrix picked?" << "\n";
        for(int k = 0; k < solve.size();++k){
            for(int q = 0; q < solve[0].size();++q)
                cout << solve[k][q] << " ";
            cout << "\n";
        }*/
        Equation eq = Equation(solve,sendB);
        pair<bool,Column> col = SolveEquation(eq);
        if(!col.first) continue;
        bool valid = 1;
        /**cout << "possible answer\n";
        for(int k = 0; k < col.second.size();++k)
            cout << col.second[k] << " ";
        cout << "\nsums ";**/
        for(int k = 0; k < A.size() && valid;++k){
            double sum = 0;
            for(int q = 0; q < A[0].size() && valid;++q)
                sum += A[k][q]*col.second[q];
          //  cout << b[k] - sum << " " << "\n";
            if(b[k] - sum >= EPS) valid = 0;
        }
        if(!valid) continue;
        //cout << "it is valid!!!" << "\n";
        double temp = 0.0;
        for(int k = 0; k < col.second.size();++k)
            temp += c[k]*col.second[k];
        if(temp-ma >= EPS){
            if(fabs(sendB.back()+(double)1000000000.0)<=EPS) ans.first = 1;
            else ans.first = 0;
            for(int k = 0; k < col.second.size();++k)
                ans.second[k] = col.second[k];
            ma = temp;
        }
        //cout << "temp is "<<temp << "\n";
    }
    return ans;
}

int main(){
    int n, m;
    cin >> n >> m;
    Matrix A(n+m+1, std::vector <double> (m, 0.0));
    Column b(n+m+1, 0.0);
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < m; ++column){
            cin >> A[row][column];
            A[row][column] *= -1.0;
        }
    }
    for(int i = 0; i < n;++i){
        cin >> b[i];
        b[i] *= -1.0;
    }
    b.back() = -1000000000.0;
    vector<double> c(m);
    for(int i = 0; i < m;++i)
        cin >> c[i];
    for(int i = n,j = 0; j < m;++i,++j)
        A[i][j] = 1.0;
    for(int i = 0; i < m;++i)
        A.back()[i] = -1.0;
    pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

    switch (ans.first) {
        case -1:
            printf("No solution\n");
            break;
        case 0:
            printf("Bounded solution\n");
            for (int i = 0; i < m; i++) {
                printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
            }
            break;
        case 1:
            printf("Infinity\n");
            break;
    }
    return 0;
}
