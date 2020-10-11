#include "systemc.h"
#include "interface.h"
#include <fstream>
#define MEM_SIZE 70000



class MEMORY_RTL: public sc_module
{
  private:
    sc_uint<32> memData[MEM_SIZE];

  public:
    sc_in<sc_logic> clk;
    sc_in<sc_logic> Ren, Wen;
    sc_in<int> Addr;
    sc_in<int> DataIn;
    sc_out<int> DataOut;
    sc_out<sc_logic> Ack;

    SC_HAS_PROCESS(MEMORY_RTL);


    void rtl()
    {
      if (Ren.read() == sc_logic_0 && Wen.read() == sc_logic_0)
      {
        Ack.write(sc_logic_Z);
        return;
      }
      int addr_val = Addr.read();
      if (addr_val < MEM_SIZE)
      {
        if(Ren.read() == sc_logic_1)
        {
         
          DataOut.write(memData[addr_val]);
        }
        else if (Wen.read() == sc_logic_1)
        {
          memData[addr_val] = DataIn.read();
        }

        Ack.write(sc_logic_1);
      }

      else
      {
        Ack.write(sc_logic_0);
      }
    }



    MEMORY_RTL(sc_module_name nm, char* file) : sc_module(nm)
    {
      ifstream init_file(file);
      int cnt= 0;
      int x;
       while (init_file >> x){
        memData[cnt++] = x;}

      SC_METHOD(rtl);
      sensitive << clk.pos();
    }


};