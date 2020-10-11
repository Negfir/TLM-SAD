#include "systemc.h"
#include "interface.h"
#include "memory_rtl.h"
#include "oscillator.h"
#include <fstream>
#define MEM_SIZE 70000

#ifndef __MEMORY_H__
#define __MEMORY_H__

class memory : public sc_module, public simple_mem_if
{
  private:
    // Module declarations


    // Local signal declarations
    sc_signal<unsigned int> addr_sig;
    sc_signal<unsigned int> dataIn_sig;
    sc_signal<unsigned int> dataOut_sig;
    sc_signal<sc_logic> ren_sig;
    sc_signal<sc_logic> wen_sig;
    sc_signal<sc_logic> ack_sig;
    sc_signal<sc_logic> clk_sig;

  public:
    MEMORY_RTL mem_rtl;
    oscillator osc;

    bool Read(unsigned int addr, unsigned int& data)
    {
      // Waiting for memory bus to be free
      while (ack_sig.read() != sc_logic_Z)
      {
        wait(10, SC_NS);
      }

      ren_sig.write(sc_logic_1);
      wen_sig.write(sc_logic_0);
      addr_sig.write(addr);

      // Waiting for acknowledge
      while (ack_sig.read() == sc_logic_Z)
      {
        wait(10, SC_NS);
      }

      data = dataOut_sig.read();
      //std::cout << "Memory wrapper got data " << data << std::endl;
      bool ack = ack_sig.read() == sc_logic_1;
      ren_sig.write(sc_logic_0);

      return ack;
    }

    bool Write(unsigned int addr, unsigned int data)
    {
      // Waiting for memory bus to be free
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

      return ack;
    }

    // void clockOscillator()
    // {
    //   while(true)
    //   {
    //      clk_sig.write(sc_logic_0);
    //      wait(5, SC_NS);
    //      clk_sig.write(sc_logic_1);
    //      wait(5, SC_NS);
    //   }
    // }

    // constructor
    memory(sc_module_name nm, char* filename) : sc_module(nm), osc("oscillator")
    {
      //SC_THREAD(clockOscillator);
      // Module instance signal connections
      mem_rtl = new MEMORY_RTL("mem_rtl", filename);
      //oscillator =new oscillator("oscillator");

      // RTL memory
      mem_rtl->clk(clk_sig);

      mem_rtl->Addr(addr_sig);
      mem_rtl->DataIn(dataIn_sig);
      mem_rtl->DataOut(dataOut_sig);
      mem_rtl->Ren(ren_sig);
      mem_rtl->Wen(wen_sig);
      mem_rtl->Ack(ack_sig);

      // Initialize signals
      ren_sig.write(sc_logic_0);
      wen_sig.write(sc_logic_0);
      ack_sig.write(sc_logic_Z);

      // Oscillator
      osc->clk(clk_sig);
      
    }
      

};


// class memory: public sc_module, public simple_mem_if
// {
//   private:
//     unsigned int memData[MEM_SIZE]={0};

//   public:
//   // constructor
//     memory(sc_module_name nm, char* file) : sc_module(nm)
//     {
//       ifstream init_file(file);
//       int cnt= 0;
//       int x;
//        while (init_file >> x){
//         memData[cnt++] = x;
//         //this->Write(cnt++, x);
//         //cnt++;


//       }
//       //cout << "=======Memory size is"<< cnt <<' ';

//     }
//     bool Write(unsigned int addr, unsigned int data)
//     {
//       if (addr < MEM_SIZE)
//       {
//         memData[addr]=data;
//         //cout << "Writing " << data << endl;
//         return true;
//       }
//       return false;
//       }

//     bool Read(unsigned int addr, unsigned int& data)
//     {
//       if (addr < MEM_SIZE)
//       {
//         data=memData[addr];
//         //cout << "Reading " << data <<endl;
//         return true;
//       }
//       return false;
//       }


//     // void memory::register_port(sc_port_base& port_, const char* if_typename_)
//     // {
//     //   cout << "binding " << port_.name() << " to " << "interface: " << if_typename_ << endl;
//     // }
//   };

#endif //__MEMORY_H__











  // class mem : public sc_module, public simple_mem_if { public:      
  //   SC_HAS_PROCESS(mem);
  //   SC_THREAD(oscillator);