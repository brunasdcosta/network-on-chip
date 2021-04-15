#include "systemc.h"

SC_MODULE(Testbench) {

    sc_in<bool> clk;
    sc_out<sc_uint<2>> x, y;
    sc_out<bool> x_signal, y_signal, read_, write_;
    sc_out<sc_uint<32>> message;

    void do_tb() {

        // O algoritmo abaixo foi utilizado para testar o buffer.

        x.write(2);
        x_signal.write(1);
        y.write(0);
        y_signal.write(0);
        message.write(16);

        write_.write(0);
        read_.write(1);

        wait();

        read_.write(0);
        write_.write(1);

        wait();

        x.write(1);
        x_signal.write(1);
        y.write(0);
        y_signal.write(0);
        message.write(12);

        write_.write(0);
        read_.write(1);

        wait();

        read_.write(0);
        write_.write(1);

        wait();

        x.write(0);
        x_signal.write(0);
        y.write(0);
        y_signal.write(0);
        message.write(8);

        write_.write(0);
        read_.write(1);

        wait();

        sc_stop();

    }

    SC_CTOR(Testbench) {
        SC_THREAD(do_tb);
        sensitive << clk.pos();
    }

};