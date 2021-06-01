#include"tools.h"


using namespace std;

string datasets;
THREAD_PROPERTY thread_vecs[NUMBER_OF_THREADS];
vector<DataFrame> dataframes(NUMBER_OF_THREADS);
DataFrame weights;
long true_predicts;
vector<float> min_vec;
vector<float> max_vec;



int main(int argc, char **argv){

  pthread_t thread[NUMBER_OF_THREADS];
  int return_code;
  void* status;
  datasets = "";
  if (argc == 2){
      datasets = argv[1];
  }
  weights = read_csv(datasets+"weights.csv");

  for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
		pthread_create(&thread[tid], NULL,read_csv_thread, (void*)tid);

  for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
		return_code = pthread_join(thread[tid], &status);
  

  set_max_min_vec();


  for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
		return_code = pthread_create(&thread[tid], NULL,classification, (void*)tid); 
	
  for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(thread[i], &status);

  cout<<"Accuracy: "<<true_predicts * 100.00/long(2000) <<"%"<<endl;


	pthread_exit(NULL);
}