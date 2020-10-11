#include "systemc.h"
#include "interface.h"
#include "memory_rtl.h"
#include "oscillator.h"
#include <fstream>
#define MEM_SIZE 70000

class memory: public sc_module, public simple_mem_if
{
  private:
  

    sc_signal<int> addr_sig;
    sc_signal<int> dataIn_sig;
    sc_signal<int> dataOut_sig;
    sc_signal<sc_logic> ren_sig;
    sc_signal<sc_logic> wen_sig;
    sc_signal<sc_logic> ack_sig;
    sc_signal<sc_logic> clk_sig;

  public:
    MEMORY_RTL mem_rtl;
    oscillator osc;
    memory(sc_module_name nm, char* file) : sc_module(nm), osc("oscillator"), mem_rtl("MEMORY_RTL",(char *)"mem_init.txt")
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
      ack_sig.write(sc_logic_Z);

      osc.clk(clk_sig);

    }
    bool Write(unsigned int addr, unsigned int data)
    {
      while (ack_sig.read() != sc_logic_Z)
      {
        wait(10, SC_NS);
      }
      wen_sig.write(sc_logic_1);
      ren_sig.write(sc_logic_0);
      addr_sig.write(addr);
      dataIn_sig.write(data);

      while (ack_sig.read() == sc_logic_Z)
      {
        wait(10, SC_NS);
      }

      bool ack = ack_sig.read() == sc_logic_1;
      wen_sig.write(sc_logic_0);



      }

    bool Read(unsigned int addr, unsigned int& data)
    {
      while (ack_sig.read() != sc_logic_Z)
      {
        wait(10, SC_NS);
      }
      ren_sig.write(sc_logic_1);
      wen_sig.write(sc_logic_0);
      addr_sig.write(addr);

     while (ack_sig.read() == sc_logic_Z)
      {
        wait(10, SC_NS);
      }

      data = dataOut_sig.read();
      bool ack = ack_sig.read() == sc_logic_1;
      ren_sig.write(sc_logic_0);

      return ack;


      }


    // void memory::register_port(sc_port_base& port_, const char* if_typename_)
    // {
    //   cout << "binding " << port_.name() << " to " << "interface: " << if_typename_ << endl;
    // }
  };










  // class mem : public sc_module, public simple_mem_if { public:      
  //   SC_HAS_PROCESS(mem);
  //   SC_THREAD(oscillator);