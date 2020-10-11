#include "systemc.h"
#include "interface.h"
#include <fstream>
#define MEM_SIZE 70000


class memory: public sc_module, public simple_mem_if
{
  private:
    unsigned int memData[MEM_SIZE]={0};

  public:

    memory(sc_module_name nm, char* file) : sc_module(nm)
    {
      ifstream init_file(file);
      int cnt= 0;
      int x;
       while (init_file >> x){
        memData[cnt++] = x;


      }


    }
    bool Write(unsigned int addr, unsigned int data)
    {
      if (addr < MEM_SIZE)
      {
        memData[addr]=data;
        //cout << "Writing " << data << endl;
        return true;
      }
      return false;
      }

    bool Read(unsigned int addr, unsigned int& data)
    {
      if (addr < MEM_SIZE)
      {
        data=memData[addr];
        //cout << "Reading " << data <<endl;
        return true;
      }
      return false;
      }


  };
