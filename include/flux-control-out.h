#ifndef FLUX_CONTROL_OUT_H
#define FLUX_CONTROL_OUT_H

#include "systemc.h"

SC_MODULE(HandshakeOUT) {

    sc_in<bool> request_to_shipping; // Sinal que identifica que quer enviar uma mensagem.
    sc_in<bool> can_ship; // Sinal que identifica se pode enviar a mensagem;
    sc_out<bool> shipping_request; // Sinal que identifica se pode receber a mensagem ou não.

    void rules(){

        bool request = request_to_shipping.read();
        if(request){
            shipping_request.write(true);
        }
        else{
            shipping_request.write(false);
        }

        //TODO: acho que ta faltando alguma coisa aqui, que no caso seria se o fluxo de entrada mandasse um sinal positivo ou negativo através do can_ship.

    }

    SC_CTOR(HandshakeOUT) {
        SC_METHOD(rules);
        sensitive << request_to_shipping << can_ship;
    }

};

#endif