//Przemysław Myśliwiec, 302885

#include <iostream>
#include "tsp.hpp"
#include <functional>
#include <utility>
#define INF (NAN)

TSP_cost_matrix::TSP_cost_matrix(std::vector<ivec> m) {
    iv=std::move(m);
    LB=0;
}

void TSP_cost_matrix::print() const {
    for(auto & i : iv){
        std::cout << "[";
        for(std::size_t j=0; j < i.size(); j++){
            std::cout.width(5);
            std::cout << i[j];
            if(i.size()!=j+1 ) {std::cout << " ";}
        }
        std::cout << "]";
        std::cout << "\n";
    }
}

void TSP_cost_matrix::find_best_path() {
    save_coordinates();
    std::size_t size = iv.size();
    for (std::size_t i = 0; i < size ; i++) {
        if (iv.size() == 2) {
            if (is_reduce_necessery()) {
                reduce_all_rows();
                reduce_all_cols();
            }
            last_matrix();
            break;
        }
        if (iv.size() > 2) {
            if (is_reduce_necessery()) {
                reduce_all_rows();
                reduce_all_cols();
            }
            find_next_path();
            for (std::size_t k = 0; k < x.size(); k++) {
                if (x[k] == solution[i].second[0]) {
                    reduce_row(k);
                    x.erase(x.begin() + k);
                }
            }
            for (std::size_t l = 0; l < y.size(); l++) {
                if (y[l] == solution[i].second[1]) {
                    reduce_col(l);
                    y.erase(y.begin() + l);
                }
            }
            for (std::size_t m = 0; m < x.size(); m++) {
                if (x[m] == solution[i].second[1]) {
                    for (std::size_t n = 0; n < y.size(); n++) {
                        if (y[n] == solution[i].second[0]) {
                            iv[m][n] = INF;
                            break;
                        }
                    }
                }
            }
        }
    }
}


void TSP_cost_matrix::reduce_row(const int& row) {
    iv.erase(iv.begin()+row);
}

void TSP_cost_matrix::reduce_all_rows() {
    for(auto & i : iv){
        double min;
        if(std::isnan(i[0])){
            min = i[1];
        }
        else{
            min=i[0];
        }
        for(auto j : i) {
            if (j < min) {
                min = j;
            }
        }
        for(double & k : i){
            if(k!=NAN) {
                k = k - min;
            }
        }
        LB=LB+min;
    }
}

void TSP_cost_matrix::reduce_col(const int& col) {
    for(auto & i : iv){
        i.erase(i.begin()+col);
    }
}

void TSP_cost_matrix::reduce_all_cols() {
    for(std::size_t i=0; i < iv[0].size(); i++){
        double min;
        if(std::isnan(iv[0][i])){
            min = iv[1][i];
        }
        else{
            min=iv[0][i];
        }
        for(auto & j : iv) {
            if (j[i] < min) {
                min = j[i];
            }
        }
        for(auto & k : iv){
            if(k[i]!=NAN) {
                k[i] = k[i] - min;
            }
        }
        LB=LB+min;
    }
}

void TSP_cost_matrix::find_next_path() {
    for (std::size_t i = 0; i < iv.size(); i++) {
        for (std::size_t j = 0; j < iv[i].size(); j++) {
            if (iv[i][j] == 0) {
                summits.push_back(x[i]);
                summits.push_back(y[j]);
                candidates.emplace_back(get_path_cost(i, j), summits);
                summits.clear();
            }
        }
    }
    solution.emplace_back(candidates[0].first, candidates[0].second);
    for (auto & candidate : candidates) {
        if (solution.back().first < candidate.first) {
            solution.back().first = candidate.first;
            solution.back().second = candidate.second;
        }
    }
    candidates.clear();
}

double TSP_cost_matrix::get_path_cost(const int& row_num,const int& col_num){
    double min_row = first_minrow(row_num,col_num);
    double min_col = first_mincol(row_num,col_num);

    for(std::size_t m=0; m < iv[row_num].size(); m++){
        if(min_row > iv[row_num][m] && m!=col_num) {
            min_row = iv[row_num][m];
        }
        else{
            continue;
        }
    }

    for(std::size_t p=0; p < iv.size(); p++) {
        if(min_col > iv[p][col_num] && p!=row_num) {
            min_col = iv[p][col_num];
        }
        else{
            continue;
        }
    }
    double cost_path = min_row + min_col;
    return cost_path;
}


double TSP_cost_matrix::first_minrow(const int& row_num,const int& col_num) {
    for(std::size_t i=0; i<iv[row_num].size(); i++){
        if(std::isnan(iv[row_num][i]) || i == col_num ){
            continue;
        }
        else{
            return iv[row_num][i];
        }
    }
    return 0;
}

double TSP_cost_matrix::first_mincol(const int& row_num,const int& col_num) {
    for(std::size_t i=0; i<iv.size(); i++){
        if(std::isnan(iv[i][col_num]) || i==row_num ){
            continue;
        }
        else{
            return iv[i][col_num];
        }
    }
    return 0;
}

bool TSP_cost_matrix::is_reduce_necessery() const {
    bool inrow;
    bool incol;
    for(auto & i : iv){
        inrow=true;
        for(std::size_t j=0; j<iv[0].size(); j++) {
            if (i[j] == 0) {
                inrow = false;
            }
        }
        if(inrow){
            return true;
        }
    }
    for(std::size_t i=0; i<iv[0].size(); i++){
        incol=true;
        for(auto & j : iv) {
            if (j[i] == 0) {
                incol = false;
            }
        }
        if(incol){
            return true;
        }
    }
    return false;
}

void TSP_cost_matrix::save_coordinates() {
    for(std::size_t i=1; i <= iv.size(); i++){
        x.push_back(i);
        y.push_back(i);
    }
}

void TSP_cost_matrix::last_matrix() {
    std::vector<double> helper;
    for(std::size_t i=0; i<iv.size(); i++){
        for(std::size_t j=0; j<iv[i].size(); j++){
            if(std::isnan(iv[i][j])){
                if(i==j){
                    helper.push_back(x[0]);
                    helper.push_back(y[1]);
                    solution.emplace_back(0, helper);
                    helper.clear();
                    helper.push_back(x[1]);
                    helper.push_back(y[0]);
                    solution.emplace_back(0, helper);
                    helper.clear();
                }
                else{
                    helper.push_back(x[0]);
                    helper.push_back(y[0]);
                    solution.emplace_back(0, helper);
                    helper.clear();
                    helper.push_back(x[1]);
                    helper.push_back(y[1]);
                    solution.emplace_back(0, helper);
                    helper.clear();
                }
            }
        }
    }
}

void TSP_cost_matrix::segregate_solutions() {
    int start = 0;
    int end = 0;
    std::size_t curr_size=solution.size()-1;
    for(auto & i : solution){
        if(i.second[0]==1){
            start=i.second[0];
            end=i.second[1];
            FINISH_PATH.push_back(start);
            FINISH_PATH.push_back(end);

        }
    }
    int j=0;
    while(curr_size>0){
        if(solution[j].second[0]==end){
            FINISH_PATH.push_back(solution[j].second[1]);
            end=solution[j].second[1];
            curr_size=curr_size-1;
            j=0;
            if(FINISH_PATH.size()==solution.size()){
                curr_size=0;
            }
        }
        else {j++;}
    }
    FINISH_PATH.push_back(start);
}



std::vector<int> tsp(std::vector<ivec> matrix) {
    TSP_cost_matrix v(std::move(matrix));
    v.find_best_path();
    v.segregate_solutions();

    return v.FINISH_PATH;
}

double get_forbidden_cost(){
    return NAN;
}