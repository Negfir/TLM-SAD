#include "systemc.h"
#include "interface.h"
#include "memory.h"
#include <fstream>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
//#define INPUT2_ADDR 106384
#define SAD_OUTPUT_ADDR 32768
//#define SAD_OUTPUT_ADDR 302768

SC_MODULE(sad) {


  sc_port<simple_mem_if> MEM;

  sc_in<sc_logic> clk;

  void sadFunction() {
    int i, v;
    unsigned int block;
    unsigned int res;
    unsigned int a, b;
    bool ack1,ack2,ack3;

    for (block=0; block<NUM_BLOCKS; block++)
    {
      wait(10,SC_NS); //comparison (block<NUM_BLOCKS)
      res = 0;
      for (i=0; i<BLOCK_SIZE; i++)
      {
        wait(10,SC_NS); //comparison (i<BLOCK_SIZE)
        ack1=MEM->Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, a);
        ack2=MEM->Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, b);


        v = a - b;
        wait(10,SC_NS); // subtraction (a - b)
        if( v < 0 ) v = -v;
        wait(10,SC_NS); //comparison (v<0)

        res += v;
        wait(10,SC_NS); //sum (res + v)
        
        wait(10,SC_NS); //increment (i++)
      }
      ack3=MEM->Write(SAD_OUTPUT_ADDR + block, res);
      //cout << "Write Ack is ==== " << ack3 <<endl;
      cout << "@"<<sc_time_stamp() << " block #" << block << " | SAD : " << res <<endl;
      wait(10,SC_NS); //increment (block++)
    }
    
    sc_stop();
  }

  SC_CTOR(sad)       {
    SC_THREAD(sadFunction);
    sensitive << clk.pos();  

  }
};




int sc_main(int argc, char* argv[]) {
  sad sadModule("sadModule");
  char* file = (char *)"mem_init.txt";
  memory mem("mem", (char *)file);

  sadModule.MEM(mem);
  sadModule.clk(mem.clk_sig);


  sc_trace_file *wf = sc_create_vcd_trace_file("WaveForm");
 
  sc_trace(wf, mem.addr_sig , "addr" );
  sc_trace(wf, mem.dataIn_sig , "dataIn" );
  sc_trace(wf, mem.dataOut_sig , "dataOut" );
  sc_trace(wf, mem.ren_sig, "ren");
  sc_trace(wf, mem.wen_sig, "wen");
  sc_trace(wf, mem.ack_sig, "ack");
  sc_trace(wf, mem.clk_sig, "clk");
  //sc_trace(wf, sadModule.MEM, "Bus");
  sc_start();

  sc_close_vcd_trace_file(wf);


  return(0);
}

