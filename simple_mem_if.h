// All systemc modules should include systemc.h header file
#include "systemc.h"
#include <fstream>

#define WIDTH  32

SC_MODULE(adder) {
  sc_in<sc_int<WIDTH> > a, b;  
  sc_out<sc_int<WIDTH> > sum;

  void do_add() {
    sum.write(a.read() + b.read());
    cout<<"@" << "sum is" <<sum.read()<<endl;
  }

  SC_CTOR(adder)       {
    SC_METHOD(do_add);   
    sensitive << a << b; 
  }
};


SC_MODULE (hello_world) {
  SC_CTOR (hello_world) {
    // Nothing in constructor 
  }
  void say_hello(int arr[500]) {
    //Print "Hello World" to the console.
    cout << "Hello World.\n" << arr[3];
  }
};





// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {

  // sc_signal<sc_int<WIDTH> >   a ;
  // sc_signal<sc_int<WIDTH> >   b ;
  // sc_signal<sc_int<WIDTH> >   s;
  // a=5;
  // b=6; 
  // adder myadder("adding");
  // myadder.a(a);
  // myadder.b(b);
  // myadder.sum(s);
  // myadder.do_add();

  int arr[500];
  ifstream is("mem.txt");
  int cnt= 0;
  int x;
  // check that array is not already full
  while (cnt<500){
    if (is >> x){
      arr[cnt++] = x;
    }
    else {
      arr[cnt++] = 0;
    }
  } 
  // print the integers stored in the array
  cout<<"The integers are:"<<"\n";
  for (int i = 0; i < cnt; i++) {
    cout << arr[i] <<' ';
  }
  cout << "=====" << arr[0]*2 <<endl;

  hello_world hello("HELLO");
  hello.say_hello(arr);

  return(0);
}
