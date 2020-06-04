//Przemysław Myśliwiec, 302885

#ifndef KOMIWOJAZER_TSP_HPP
#define KOMIWOJAZER_TSP_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#define INF (NAN)

using ulong = unsigned long;
using ivec = std::vector<double>;

std::vector<int> tsp(std::vector<ivec> matrix);
double get_forbidden_cost();

class TSP_cost_matrix{
public:
    explicit TSP_cost_matrix(std::vector<ivec> m);
    void save_coordinates();
    void print() const;
    void find_best_path();
    void reduce_row(const int& row);
    void reduce_all_rows();
    double first_minrow(const int& row_num,const int& col_num);
    double first_mincol(const int& row_num,const int& col_num);
    bool is_reduce_necessery() const;
    void reduce_col(const int& col);
    void reduce_all_cols();
    void find_next_path();
    double get_path_cost(const int& row_num,const int& col_num);
    void last_matrix();
    void segregate_solutions();
    std::vector<std::pair<double, ivec>> solution;
    std::vector<std::pair<double, ivec>> candidates;
    std::vector<ivec> iv;
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> FINISH_PATH;
    ivec summits;
    double LB;
};





#endif //KOMIWOJAZER_TSP_HPP
