#include "systemc.h"
#include "interface.h"
#include "memory_rtl.h"
#include "oscillator.h"
#include <fstream>
#define MEM_SIZE 70000

class memory: public sc_module, public simple_mem_if
{

  
  public:
    sc_signal<sc_logic> clk_sig;
    sc_signal<sc_logic>ren_sig, wen_sig, ack_sig;
    sc_signal<int> addr_sig;
    sc_signal<int> dataIn_sig;
    sc_signal<int> dataOut_sig;

  
    MEMORY_RTL mem_rtl;
    oscillator osc;

    memory(sc_module_name nm, char* file) : sc_module(nm), osc("oscillator"), mem_rtl("MEMORY_RTL",(char *)file)
    {


      mem_rtl.clk(clk_sig);

      mem_rtl.Addr(addr_sig);
      mem_rtl.DataIn(dataIn_sig);
      mem_rtl.DataOut(dataOut_sig);
      mem_rtl.Ren(ren_sig);
      mem_rtl.Wen(wen_sig);
      mem_rtl.Ack(ack_sig);

      ren_sig.write(sc_logic_0);
      wen_sig.write(sc_logic_0);
      ack_sig.write(sc_logic_0);

      osc.clk(clk_sig);

    }



    // void oscillator() {
    //   while(true)
    //   {
    //      clk_sig.write(sc_logic_0);
    //      wait(5, SC_NS);
    //      clk_sig.write(sc_logic_1);
    //      wait(5, SC_NS);
    //   }
    // }


    bool Write(unsigned int addr, unsigned int data)
    {
      // while (ack_sig.read() != sc_logic_0)
      // {
      //   wait(10, SC_NS);
      // }
      
      
      addr_sig.write(addr);
      dataIn_sig.write(data);

      wait(10, SC_NS);

      wen_sig.write(sc_logic_1);

      wait(10, SC_NS);

      wen_sig.write(sc_logic_0);

      bool ack = ack_sig.read() == sc_logic_1;
      //cout << "Writing " << dataIn_sig<< " on address:" << addr_sig << " ack is:" << ack <<endl;
      return ack;

      }

    bool Read(unsigned int addr, unsigned int& data)
    {

      //wait(10, SC_NS);
      ren_sig.write(sc_logic_1);
    
      addr_sig.write(addr);

      data = dataOut_sig.read();

      wait(10, SC_NS);


      ren_sig.write(sc_logic_0);
      wait(10, SC_NS);

      bool ack = ack_sig.read() == sc_logic_1;

      return ack;


      }

  };
