// All systemc modules should include systemc.h header file
#include <iostream>

#include <fstream>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768

using namespace std;

int main(int argc, char* argv[]) {


  int arr[70000]={0};
  ifstream is("mem_init.txt");
  int cnt= 0;
  int x;
  // check that array is not already full
  while (is >> x){
  
    arr[cnt++] = x;
  
  } 

  // cout<<"The integers are:"<<"\n";
  // for (int i = 0; i < cnt; i++) {
  //   cout << arr[i] <<' ';
  // }
  
  int i, v;
  unsigned int block;
  unsigned int sad;

  for (block=0; block<NUM_BLOCKS; block++) 
  {
      sad = 0;
      for (i=0; i<BLOCK_SIZE; i++) 
      {
          v = arr[INPUT1_ADDR+(block*BLOCK_SIZE)+i] - 
              arr[INPUT2_ADDR+(block*BLOCK_SIZE)+i];
          if (v < 0) v = -v;
          sad += v;
      }
      arr[SAD_OUTPUT_ADDR+block] = sad;
      cout <<" block #" << block << " | SAD: " << sad <<endl;
  }


  return(0);
}

