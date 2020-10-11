
#include "systemc.h"
#include "interface.h"
#include "memory.h"
#include <fstream>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768

SC_MODULE(sad) {
  sc_port<simple_mem_if> MEM;

  void sadFunction() {
    int i, v;
    unsigned int block;
    unsigned int res;
    unsigned int a, b;

    for (block=0; block<NUM_BLOCKS; block++)
    {
      res = 0;
      for (i=0; i<BLOCK_SIZE; i++)
      {
        MEM->Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, a);
        MEM->Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, b);
        //cout  << " A : " << a << " B : " << b << endl;
        v = a - b;
        if( v < 0 ) v = -v;
        res += v;
        //cout << "======"<< res <<endl ;
      }
      MEM->Write(SAD_OUTPUT_ADDR + block, res);
      cout << "@"<<sc_time_stamp() << " block #" << block << " | SAD : " << res <<endl;
    }
  }


  SC_CTOR(sad)       {
    SC_METHOD(sadFunction);   
  }


};



int sc_main(int argc, char* argv[]) {
  sad sadModule("sadModule");
  char* file = (char *)"mem_init.txt";
  memory mem("mem", (char *)file);

  sadModule.MEM(mem);
  sadModule.sadFunction();

  return(0);
}

