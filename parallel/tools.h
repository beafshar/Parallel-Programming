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
#include <pthread.h>
#include<dirent.h>
#include <algorithm>


#define NUMBER_OF_THREADS 4
#define TRAIN_SIZE 2000
#define WEIGHTS_SIZE 5
#define ATTRIBUTES 20

using namespace std;

typedef vector<string> stringvec;
typedef vector<vector<float>> DataFrame;
typedef struct{
  vector<float> min_vector;
  vector<float> max_vector;
}THREAD_PROPERTY;

extern string datasets;
extern vector<float> min_vec;
extern vector<float> max_vec;
extern THREAD_PROPERTY thread_vecs[NUMBER_OF_THREADS];
extern vector<DataFrame> dataframes;
extern DataFrame weights;
extern long true_predicts;



void* read_csv_thread(void* tid);
DataFrame read_csv(string filename);
vector<float> parse_row(string row);
vector<float> get_max_vec(DataFrame df);
vector<float> get_min_vec(DataFrame df);
float get_max(DataFrame df,int col);
float get_min(DataFrame df,int col);
void* classification(void* tid);
long accuracy(vector<int> pred, vector<int> real);
void set_max_min_vec();

float dot_product(vector<float> train_row, vector<float> train_weight);
int return_max(vector<float> vec);
vector<int> determine_class(DataFrame train_df, DataFrame weights_df);

vector<int> get_true_column(DataFrame train);
float normalize(float x, float max, float min);
DataFrame normalize_dataframe(DataFrame df);


#endif