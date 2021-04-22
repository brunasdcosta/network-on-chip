#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"
#include "buffer.h"
#include "routing.h"
#include "flux-control-in.h"
#include "flux-control-out.h"
#include "arbitration.h"
#include <string>

SC_MODULE(Router) {

    int id; // Identificador do roteador.

    sc_in<sc_uint<2>> x_in, y_in;
    sc_in<bool> x_sign_in, y_sign_in, write_, request_to_receive, can_ship;
    sc_in<sc_uint<32>> message_in;

    sc_out<sc_uint<2>> x_out, y_out;
    sc_out<bool> x_sign_out, y_sign_out;
    sc_out<sc_uint<32>> message_out;

    void rules(){
        std::cout << "TESTE\n";
        while(true){
            wait();
            x_out.write(0);
            y_out.write(0);
            x_sign_out.write(0);
            y_sign_out.write(0);

            sc_stop();
        }
    }

    SC_CTOR(Router) {
        SC_THREAD(rules);
        sensitive << x_in << y_in << x_sign_in << y_sign_in << write_ << request_to_receive << can_ship << message_in;
    }

};

#endif