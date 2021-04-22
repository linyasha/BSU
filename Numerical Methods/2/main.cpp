#include "SLE.h"
#include "NTN.h"


#define x vars[0]
#define y vars[1]

typedef function<double(vector<double>)> equation;


#define x vars[0]
#define y vars[1]
#define z vars[2]

typedef std::function<double(vector<double>)> equation;



static double f1(vector<double> vars) {
    return x * x + 1;
}

static double f2(vector<double> vars) {
    return y * y + 1;
}


#undef x
#undef y

vector<equation> nonlinear_system() {
    return { f1, f2 };
}

vector<double> get_initial_approximation() {
    return { -4, 2 };
}
int main() {
    
    vector<equation> fuuu = nonlinear_system();
    vector<double> approximation = get_initial_approximation(); 
    vector<double> result; 
    int counter = 0; 
    if (solve_snle(fuuu, approximation, eps, result, counter)) {
        for (int i = 0; i < result.size(); i++) {
            cout << ' ' << result[i];
        }
    }
    else cout << "=<";
}