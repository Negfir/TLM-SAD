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
        //cout << res <<' ' << "======";
        wait(10,SC_NS);
      }
      MEM->Write(SAD_OUTPUT_ADDR + block, res);
      cout << sc_time_stamp() << " | block : " << block << " | sad : " << res << std::endl;
      wait(10,SC_NS);
    }
    
    sc_stop();
  }

  SC_CTOR(sad)       {
    SC_THREAD(sadFunction);   
  }
};



SC_MODULE (hello_world) {
  SC_CTOR (hello_world) {
    // Nothing in constructor 
  }
  void say_hello() {
    //Print "Hello World" to the console.
    cout << "Hello World.\n";
  }
};

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
  sad Sad1("SAD1");
  char* file = (char *)"mem_init.txt";
  memory Mem_Simple("MEM_SMPL", (char *)file);

      // Link memory
  Sad1.MEM(Mem_Simple);

  sc_start();
  
  //Sad1.sadFunction();

  // int arr[500];
  // ifstream is("mem.txt");
  // int cnt= 0;
  // int x;
  // // check that array is not already full
  // while (cnt<500){
  //   if (is >> x){
  //     arr[cnt++] = x;
  //   }
  //   else {
  //     arr[cnt++] = 0;
  //   }
  // } 
  // print the integers stored in the array
  // cout<<"The integers are:"<<"\n";
  // for (int i = 0; i < cnt; i++) {
  //   cout << arr[i] <<' ';
  // }
  // cout << "=====" << arr[0]*2 <<endl;

  // hello_world hello("HELLO");
  // // Print the hello world
  // hello.say_hello();
  return(0);
}

