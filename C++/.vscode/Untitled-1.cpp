#include<iostream>
#include<vector>
#include<fstream>
#include<string>


void matrix_creat(std::ifstream& matrix_file, std::vector<std::vector<double>>& matrix, int& order_matrix);

void matrix_set(std::ifstream& matrix_file, std::vector<std::vector<double>>& matrix);

double max_value(std::vector<std::vector<double>>& matrix);

double max_value(std::vector<std::vector<double>>& matrix, const int x_cord, const int y_cord, double eps);

void set_eps(double& eps, std::vector<std::vector<double>>& matrix);

bool gauss_method(std::vector<std::vector<double>>& matrix, double eps);

bool complability(std::vector<std::vector<double>>& matrix, double eps);

void creat_solution_vector(std::vector<std::vector<double>>& matrix, std::vector<double>& solution_vector);

void out_vector(std::vector<double>& solution_vector);



int main()
{
    double eps(0);
    std::vector<std::vector<double>> matrix;
    int order_matrix(0);
    std::ifstream matrix_file;
    matrix_file.open("Test.txt");
    matrix_creat(matrix_file, matrix, order_matrix);
    matrix_set(matrix_file, matrix);
    gauss_method(matrix, eps);
}

void set_eps(double& eps, std::vector<std::vector<double>>& matrix)
{
    eps = max_value(matrix) * 10E-6;
}

double max_value(std::vector<std::vector<double>>& matrix, const int x_cord, const int y_cord, double eps)
{
    double max(matrix[y_cord][x_cord]);
    int y_max_cord(0);
    for (int i = y_cord; i < matrix.size(); i++)
    {
        if (matrix[i][x_cord] > max)
        {
            max = matrix[i][x_cord];
            y_max_cord = i;
        }
    }
    if (abs(max) <= eps)
        throw 1;
    else {
        if(y_max_cord!=0)
        matrix[y_max_cord].swap(matrix[y_cord]);
    }
}

double max_value(std::vector<std::vector<double>>& matrix)
{
    double max(0.);
    for (int i(0); i < matrix.size(); i++)
    {
        for (int g(0); g < matrix[0].size(); g++)
        {
            if (matrix[i][g] > max)
            {
                max = matrix[i][g];
            }
        }

    }
    return max;
}

void matrix_set(std::ifstream& matrix_file, std::vector<std::vector<double>>& matrix)
{
    for (int i(0); i < matrix.size(); i++)
    {
        for (int g(0); g < matrix[0].size(); g++)
        {
            matrix_file >> matrix[i][g];
        }

    }
}

void matrix_creat(std::ifstream& matrix_file, std::vector<std::vector<double>>& matrix, int& order_matrix)
{
   matrix_file>> order_matrix;
    std::vector<std::vector<double>> timly_matrix(order_matrix, std::vector<double>(order_matrix + 1, 0));
    matrix = timly_matrix;
}

bool gauss_method(std::vector<std::vector<double>>& matrix, double eps)
{
    for (int i(0); i < matrix.size(); i++)
    {

        max_value(matrix, i, i, eps);
        double multiplier(1 / matrix[i][i]);
        for (int g(0); g < matrix[0].size(); g++)
        {
            matrix[i][g] *= multiplier;
        }
        std::vector<double> liding_line(matrix[0].size());
        liding_line = matrix[i];
        for (int g(0); g < matrix.size(); g++)
        {
            if (g == i && g != matrix.size() - 1)
                g++;
            else
            {
                if (g == i && g == matrix.size() - 1)
                {
                    break;
                }

            }
            multiplier = (-matrix[g][i]);
            for (int c(0); c < matrix[0].size(); c++)
            {

                matrix[g][c] += (liding_line[c]*multiplier);
            }

        }

    }
    if (complability(matrix, eps) == 1)
    {
        return 1;
    }
    std::vector<double> solution_vector(matrix.size());
    creat_solution_vector(matrix,solution_vector);
    out_vector(solution_vector);
}

bool complability(std::vector<std::vector<double>>& matrix, double eps)
{
    for (int i(0); i < matrix.size(); i++)
    {
        bool is_null(0);
        for (int g(0); g < matrix.size(); g++)
        {
            if (matrix[i][g] >= eps)
                is_null = 1;
        }
        if (is_null == 0)
        {
            std::cout << "the sistem is incompatible!!" << std::endl;
            return 1;
        }

    }

}

void creat_solution_vector(std::vector<std::vector<double>>& matrix,std::vector<double>& solution_vector)
{
    for (int i(0); i<matrix.size(); i++)
    {
        solution_vector[i] = matrix[i][matrix.size()];
    }
}

void out_vector(std::vector<double>& solution_vector)
{
    std::ofstream result_file;
    result_file.open("Result.txt");
    for (int i(0); i < solution_vector.size(); i++)
    {
        result_file << solution_vector[i] << std::endl;
    }

}