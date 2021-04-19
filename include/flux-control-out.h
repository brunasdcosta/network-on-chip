#ifndef FLUX_CONTROL_OUT_H
#define FLUX_CONTROL_OUT_H

#include "systemc.h"

SC_MODULE(HandshakeOUT) {

    sc_in<bool> request_to_shipping; // Sinal que identifica que quer enviar uma mensagem.
    sc_in<bool> can_ship; // Sinal que identifica se pode enviar a mensagem;
    sc_out<bool> shipping_request; // Sinal que identifica se pode receber a mensagem ou não.

    void rules(){

        // Apenas permite enviar o sinal se, e somente se, ele quer enviar e se pode enviar
        bool cs = can_ship.read();
        bool request = request_to_shipping.read();

        if(request && cs){
            shipping_request.write(true);
        }
        else{
            shipping_request.write(false);
        }

    }

    SC_CTOR(HandshakeOUT) {
        SC_METHOD(rules);
        sensitive << request_to_shipping << can_ship;
    }

};

#endif