#include"tools.h"



void* read_csv_thread(void* tid){

    long thread_id;
    thread_id = (long)tid;

    string str = datasets + "train_" + to_string(thread_id) + ".csv";
    DataFrame df = read_csv(str);

    dataframes[thread_id] = df;

    thread_vecs[thread_id].max_vector = get_max_vec(dataframes[thread_id]);
    thread_vecs[thread_id].min_vector = get_min_vec(dataframes[thread_id]);
    pthread_exit((void*)thread_id);
}

void set_max_min_vec(){

    for(int j = 0; j <ATTRIBUTES;j++){
        float max_temp = std::numeric_limits<float>::min();
        float min_temp = std::numeric_limits<float>::max();
        for(int i=0; i < NUMBER_OF_THREADS; i++){
            min_temp = min(thread_vecs[i].min_vector[j],min_temp);
            max_temp = max(thread_vecs[i].max_vector[j],max_temp);
        }
        max_vec.push_back(max_temp);
        min_vec.push_back(min_temp);
    }
}


void* classification(void* tid){
    long thread_id;
    thread_id = (long)tid;
    dataframes[thread_id] = normalize_dataframe(dataframes[thread_id]);
    vector<int> predictions = determine_class(dataframes[thread_id],weights);

    vector<int> true_column = get_true_column(dataframes[thread_id]);

    true_predicts += accuracy(predictions,true_column);

    pthread_exit((void*)thread_id);

}

DataFrame read_csv(string filename){
    DataFrame df;
    fstream myFile; 
    myFile.open(filename, ios::in); 
    std::string line;
    getline(myFile, line);
    while(getline(myFile, line)){
        stringstream ss(line);
        vector<float> row = parse_row(line);
        df.push_back(row);
    }
    myFile.close();
    
    return df;
}

float normalize(float x, float max, float min){
    return (x-min)/(max-min);
}
vector<float> parse_row(string row){
    vector<float> result;
    string token;
    stringstream r(row); 
    while(getline(r, token, ','))
        result.push_back(stof(token));
    return result;
}

float get_max(DataFrame df,int col){
    float temp = std::numeric_limits<int>::min();
    for(int i = 0; i < df.size(); i++){
        temp = max(temp,df[i][col]);
    }
    return temp;
}
float get_min(DataFrame df,int col){
    float temp = std::numeric_limits<int>::max();
    for(int i = 0; i < df.size(); i++){
        temp = min(temp,df[i][col]);
    }
    return temp;  
}
vector<float> get_max_vec(DataFrame df){
    vector<float> vec;
    for(int j = 0; j < ATTRIBUTES; j++){
        vec.push_back(get_max(df,j));
    }
    return vec;
}
vector<float> get_min_vec(DataFrame df){
    vector<float> vec;
    for(int j = 0; j < ATTRIBUTES; j++){
        vec.push_back(get_min(df,j));
    }
    return vec;
}
DataFrame normalize_dataframe(DataFrame df){
    for(int i = 0; i < df.size(); i++){
        for(int j = 0; j < df[i].size()-1; j++){
            df[i][j] = normalize(df[i][j],max_vec[j],min_vec[j]);
        }
    }
    return df;
}
float dot_product(vector<float> train, vector<float> weights){
    float sum = 0;
    for(int i = 0; i < ATTRIBUTES; i++){
        sum += train[i] * weights[i];
    }
    return sum;
}

int return_max(vector<float> vec){
    float price = std::numeric_limits<int>::min();
    int max_idx;
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] > price){
            price = vec[i];
            max_idx = i;
        }
    }
    return max_idx;
}
vector<int> determine_class(DataFrame train_df, DataFrame weights){
    vector<int> predicts;
    for(int i = 0; i < train_df.size(); i++){
        vector<float> classes;
        for(int j = 0; j < weights.size(); j++){
            classes.push_back(dot_product(train_df[i],weights[j])+weights[j][ATTRIBUTES]); 
        }
        
        predicts.push_back(return_max(classes));
    }   
    return predicts;
}

long accuracy(vector<int> pred, vector<int> real){
    long true_preds = 0;
    for(int i = 0; i < real.size();i++){
        if(pred[i] == real[i])
            true_preds+= 1;

    }
    return true_preds;

}

vector<int> get_true_column(DataFrame train){
    vector<int> true_col;
    for(int i = 0; i < train.size();i++){
        vector<float> temp = train[i];
        true_col.push_back(int(temp[temp.size() - 1]));
        
    }
    return true_col;
}