#include"tools.h"


using namespace std;

int main(int argc, char **argv){
    string datasets;
    datasets = "";
    if (argc == 2){
        datasets = argv[1];
    }
    DataFrame train_df = read_csv(datasets+"train.csv");;
    DataFrame weights = read_csv(datasets+"weights.csv");
    
    train_df = normalize_dataframe(train_df);
    vector<int> predictions = determine_class(train_df,weights);

    vector<int> true_column = get_true_column(train_df);
    accuracy(predictions,true_column);

    return 0;
} 