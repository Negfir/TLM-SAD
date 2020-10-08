#include "systemc.h"
#include "memory_if.h"
#include <fstream>
#define MEM_SIZE 500
// this class implements the virtual functions
// in the interfaces
class memory: public sc_module, public simple_mem_if
{
  private:
    unsigned int memData[MEM_SIZE]={};

  public:
  // constructor
    memory(sc_module_name nm, char* file) : sc_module(nm)
    {
      ifstream initFile("mem.txt");
      int cnt= 0;
      int x;
       while (initFile >> x){
        // arr[cnt++] = x;
        this->Write(cnt++, x);
      }

    }
    bool memory::Write(unsigned int addr, unsigned int data)
    {
      if (addr < MEM_SIZE)
      {
        this->memData[addr]=data;
        return true;
      }
      return false;
      }

    bool memory::Read(unsigned int addr, unsigned int& data)
    {
      if (addr < MEM_SIZE)
      {
        data=this->memData[addr];
        return true;
      }
      return false;
      }


    // void memory::register_port(sc_port_base& port_, const char* if_typename_)
    // {
    //   cout << "binding " << port_.name() << " to " << "interface: " << if_typename_ << endl;
    // }
  };










  // class mem : public sc_module, public simple_mem_if { public:      
  //   SC_HAS_PROCESS(mem);
  //   SC_THREAD(oscillator);