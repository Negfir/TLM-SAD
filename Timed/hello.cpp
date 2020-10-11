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
      wait(10,SC_NS);
      res = 0;
      for (i=0; i<BLOCK_SIZE; i++)
      {
        wait(10,SC_NS);
        MEM->Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, a);
        MEM->Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, b);

        v = a - b;
        wait(10,SC_NS);
        if( v < 0 ) v = -v;
        wait(10,SC_NS);
        wait(10,SC_NS);
        res += v;
        wait(10,SC_NS);
        //cout << "======"<< res <<endl ;
        wait(10,SC_NS);
      }
      MEM->Write(SAD_OUTPUT_ADDR + block, res);
      cout << "@"<<sc_time_stamp() << " block #" << block << " | SAD : " << res <<endl;
      wait(10,SC_NS);
    }
    
    sc_stop();
  }

  SC_CTOR(sad)       {
    SC_THREAD(sadFunction);  

  }
};




int sc_main(int argc, char* argv[]) {
  sad sadModule("sadModule");
  char* file = (char *)"mem_init.txt";
  memory mem("mem", (char *)file);

  sadModule.MEM(mem);
  


  sc_trace_file *wf = sc_create_vcd_trace_file("WaveForm");
 
  sc_trace(wf, mem.addr_sig , "addr" );
  sc_trace(wf, mem.dataIn_sig , "dataIn" );
  sc_trace(wf, mem.dataOut_sig , "dataOut" );
  sc_trace(wf, mem.ren_sig, "ren");
  sc_trace(wf, mem.wen_sig, "wen");
  sc_trace(wf, mem.ack_sig, "ack");
  sc_trace(wf, mem.clk_sig, "clk");

  sc_start();

  sc_close_vcd_trace_file(wf);


  return(0);
}

