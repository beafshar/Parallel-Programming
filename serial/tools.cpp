#include"tools.h"

DataFrame read_csv(string filename){
    DataFrame df;
    stringvec result;
    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    std::string line;
    getline(myFile, line);
    while(getline(myFile, line)){
        stringstream ss(line);
        vector<float> row = parse_row(line);
        df.push_back(row);
        result.push_back(line);  
    }
    myFile.close();

    return df;
}

float normalize(float x, float max, float min){
    return (x-min)/(max-min);
}
vector<float> parse_row(string row){
    vector<float> result;
    string temp;
    temp = strtok(&row[0],",");
    result.push_back(stof(temp));
    for(int i = 0; i < ATTRIBUTES;i++){
        temp = strtok (NULL, ",");
        result.push_back(stof(temp));
    }
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
vector<float> get_max_or_min_vec(DataFrame df,bool max){
    vector<float> vec;
    for(int j = 0; j < ATTRIBUTES; j++){
            if(max == true){
                vec.push_back(get_max(df,j));
            }   
            else{
                vec.push_back(get_min(df,j));
            }
    }
    return vec;
}
DataFrame normalize_dataframe(DataFrame df){
    vector<float> max_vec = get_max_or_min_vec(df,true);
    vector<float> min_vec = get_max_or_min_vec(df,false);
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

void accuracy(vector<int> pred, vector<int> real){
    float true_preds = 0;
    for(int i = 0; i < real.size();i++){
        if(pred[i] == real[i])
            true_preds+= 1;

    }

    cout<<"Accuracy: "<<true_preds*100/pred.size() <<"%"<<endl;
}

vector<int> get_true_column(DataFrame train){
    vector<int> true_col;
    for(int i = 0; i < train.size();i++){
        vector<float> temp = train[i];
        true_col.push_back(int(temp[temp.size() - 1]));
        
    }
    return true_col;
}