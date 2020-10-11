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
    sc_in<unsigned int> Addr;
    sc_in<unsigned int> DataIn;
    sc_out<unsigned int> DataOut;
    sc_out<sc_logic> Ack;

    SC_HAS_PROCESS(MEMORY_RTL);


    void rtl()
    {
      if (Ren.read() == sc_logic_0 && Wen.read() == sc_logic_0)
      {
        Ack.write(sc_logic_Z);
        return;
      }
      unsigned int addr_val = Addr.read();
      if (addr_val < MEM_SIZE)
      {
        if(Ren.read() == sc_logic_1)
        {
          //std::cout << "Reading from Memory : addr " << addr_val << ", value " << mem[(unsigned int) addr_val] << std::endl;
          DataOut.write(memData[addr_val]);
        }
        // Write mode
        else if (Wen.read() == sc_logic_1)
        {
          //std::cout << "Writing to Memory : addr " << addr_val << ", value " << mem[(unsigned int) dataIn.read()] << std::endl;
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