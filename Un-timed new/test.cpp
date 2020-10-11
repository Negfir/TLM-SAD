// All systemc modules should include systemc.h header file
#include "systemc.h"
#include "interface.h"
#include "memory.h"
#include <fstream>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768




int sc_main(int argc, char* argv[]) {


  int arr[70000]={0};
  ifstream is("mem_init.txt");
  int cnt= 0;
  int x;

  while (is >> x){
    arr[cnt++] = x;
  } 

  
  int i, v;
  unsigned int block;
  unsigned int sad;
  unsigned int a, b;

  for (block=0; block<NUM_BLOCKS; block++) 
  {
      sad = 0;
      for (i=0; i<BLOCK_SIZE; i++) 
      {
          a=arr[INPUT1_ADDR+(block*BLOCK_SIZE)+i];
          b=arr[INPUT2_ADDR+(block*BLOCK_SIZE)+i];
          //cout  << " | A : " << a << " | B : " << b << endl;

          v = a - b;
         
          if (v < 0) v = -v;
          sad += v;
      }
      arr[SAD_OUTPUT_ADDR+block] = sad;
      cout << "@"<<sc_time_stamp() << " block #" << block << " | SAD : " << sad <<endl;
  }


  return(0);
}

