#include "systemc.h"
#include "memory_if.h"
#define MEM_SIZE 500
// this class implements the virtual functions
// in the interfaces
class memory: public sc_module, public simple_mem_if
{
  private:
    char data[20];

  public:
  // constructor
    memory(sc_module_name nm) : sc_module(nm)
    {
    }
    bool memory::nb_write(char c)
    {
      if (top < 20)
      {
        data[top++] = c;
        return true;
      }
      return false;
      }

    bool memory::nb_read(char& c)
    {
    if (top > 0)
    {
      c = data[--top];
      return true;
    }
    return false;
    }
    void memory::register_port(sc_port_base& port_, const char* if_typename_)
    {
      cout << "binding " << port_.name() << " to " << "interface: " << if_typename_ << endl;
    }
  };










  // class mem : public sc_module, public simple_mem_if { public:      
  //   SC_HAS_PROCESS(mem);
  //   SC_THREAD(oscillator);