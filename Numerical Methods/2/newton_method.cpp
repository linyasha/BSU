#include "NTN.h"
#include "SLE.h"

const int max_iterations = 100;


bool solve_snle(const vector<function<double(vector<double>)>>& fu, vector<double> approximation , double eps, vector<double>& result, int& counter) {
    for(int i = 0; i < max_iterations; i++) {
        counter++; 
        vector<vector<double>> derivatives (approximation.size(), vector<double>(approximation.size(), 0)); 
        for(int g = 0; g < derivatives.size(); g++) {
            for(int r = 0; r < derivatives.size(); r++) {
                derivatives[g][r] = derivative(fu[g], approximation, r, eps);
            }
        }
        vector<double> free_odds(fu.size());
        for (int h = 0; h < free_odds.size(); h++) {
            free_odds[h] = fu[h](approximation);
        }
        for(int j = 0; j < derivatives.size(); j++) {
            derivatives[j].push_back(free_odds[j]);
        }
        vector<double> resultX(approximation.size());
        if(!slu_gaus(derivatives, resultX)) return false;
        for(int v = 0; v < resultX.size(); v++) {
            approximation[v] -= resultX[v];
        }
        if (!check_free(free_odds, eps) && !step_check(approximation, resultX, eps)) {
			result = approximation;
			return true;
		} 
    }
    return false;
}


double derivative(function<double(vector<double>)> f, vector<double> x, int coordinate, double eps) {
    double x_needed = x[coordinate];
    double function_plusdelta, function_minusdelta = 0;

    if (x_needed > 1) {
        x[coordinate] += x_needed * eps;
        function_plusdelta = f(x);
        x[coordinate] -= x_needed * (2 * eps);
        function_minusdelta = f(x);
        return (function_plusdelta - function_minusdelta) / (x_needed * (2 * eps));
    }
    else {
        x[coordinate] += eps;
        function_plusdelta = f(x);
        x[coordinate] -= 2 * eps;
        function_minusdelta = f(x);
        return (function_plusdelta - function_minusdelta) / (2 * eps);
    }

}

bool check_free(vector<double> free_odds, double eps) {
    double max = 0;
    for (int i = 0; i < free_odds.size(); i++) {
        if (fabs(free_odds[i]) > max) max = fabs(free_odds[i]);
    }
    if (max > eps) return true;
    return false;
}

bool step_check(vector<double> x, vector<double> resultX, double eps) {
    vector<double> normal_vector(x.size(), 0);
    for (int i = 0; i < x.size(); i++) {
        if (fabs(x[i]) > 1) normal_vector[i] = fabs(resultX[i] / x[i]);
        else normal_vector[i] = fabs(resultX[i]);
    }
    double max = 0;
    for (int g = 0; g < x.size(); g++) {
        if (normal_vector[g] > max) max = fabs(normal_vector[g]);
    }
    if (max > eps) return true;
    return false;
}




