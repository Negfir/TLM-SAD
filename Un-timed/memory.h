#include "systemc.h"
#include "interface.h"
#include <fstream>
#define MEM_SIZE 70000
// this class implements the virtual functions
// in the interfaces
class memory: public sc_module, public simple_mem_if
{
  private:
    unsigned int memData[MEM_SIZE]={0};

  public:
  // constructor
    memory(sc_module_name nm, char* file) : sc_module(nm)
    {
      ifstream init_file(file);
      int cnt= 0;
      int x;
       while (init_file >> x){
        // arr[cnt++] = x;
        this->Write(cnt++, x);
        cnt++;


      }
      //cout << "=======Memory size is"<< cnt <<' ';

    }
    bool Write(unsigned int addr, unsigned int data)
    {
      if (addr < MEM_SIZE)
      {
        this->memData[addr]=data;
        return true;
      }
      return false;
      }

    bool Read(unsigned int addr, unsigned int& data)
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