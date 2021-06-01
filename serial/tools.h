#ifndef TOOLS_H
#define TOOLS_H
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include <fstream>
#include <sstream> 
#include<vector>
#include <utility> 
#include <limits> 

#define TRAIN_SIZE 2000
#define WEIGHTS_SIZE 5
#define ATTRIBUTES 20


using namespace std;
typedef vector<string> stringvec;
typedef vector<vector<float>> DataFrame;

DataFrame read_csv(string filename);
vector<float> parse_row(string row);
float dot_product(vector<float> train_row, vector<float> train_weight);
int return_max(vector<float> vec);
vector<int> determine_class(DataFrame train_df, DataFrame weights_df);
void accuracy(vector<int> pred, vector<int> real);

vector<int> get_true_column(DataFrame train);
float normalize(float x, float max, float min);
DataFrame normalize_dataframe(DataFrame df);

vector<float> get_max_or_min_vec(DataFrame df,bool max);
float get_max(DataFrame df,int col);
float get_min(DataFrame df,int col);
#endif