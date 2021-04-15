#ifndef ROUTING_H
#define ROUTING_H

#include "systemc.h"

SC_MODULE(RoutingXY) {

    sc_in<sc_uint<2>> x_in, y_in; // Valores X e Y.
    sc_in<bool> x_sign_in, y_sign_in; // Sinais dos valores X e Y. 0 - negativo; 1 - positivo.

    /**
     * Indica qual direção a mensagem deve seguir.
     * 000 (0) - A mensagem chegou ao destino.
     * 001 (1) - A mensagem deve ir para o norte.
     * 010 (2) - A mensagem deve ir para o sul.
     * 011 (3) - A mensagem deve ir para o leste.
     * 100 (4) - A mensagem deve ir para o oeste.  
     */
    sc_out<sc_uint<3>> direction;

    void rules(){

        int x = x_in.read();
        int x_sign = x_sign_in.read();

        int y = y_in.read();
        int y_sign = y_sign_in.read();

        if(x==0){
            if(y==0){
                direction.write(0); // x=0 e y=0: A mensagem chegou ao destino.
            }
            else if(y_sign==1) {
                direction.write(1); // x=0 e y>0: A mensagem deve ir para o norte.
            }
            else if(y_sign==0) {
                direction.write(2); // x=0 e y<0: A mensagem deve ir para o sul.
            }
        }
        else if(x_sign==1){
            direction.write(3); // x>0: A mensagem deve ir para o leste.
        }
        else if(x_sign==0){
            direction.write(4);  // x<0: A mensagem deve ir para o oeste.
        }

    }

    SC_CTOR(RoutingXY) {
        SC_METHOD(rules);
        sensitive << x_in << y_in << x_sign_in << y_sign_in;
    }

};

#endif