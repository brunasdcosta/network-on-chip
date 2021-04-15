#ifndef ARBITRATION_H
#define ARBITRATION_H

#include "systemc.h"

SC_MODULE(Arbitration) {

    // Sinais que identificam quais canais de entrada estão solicitando sair pelo canal do árbitro.
    sc_in<bool> channel1, channel2, channel3, channel4;

    // Sinal que identifica que o árbitro escolheu um canal e quer enviar a mensagem.
    sc_out<bool> request_shipping;

    void rules(){

        if(channel1.read()){

            request_shipping.write(true);

            //TODO: acho que aqui tem que fazer alguma verificação com o fluxo de entrada e saída, só não tenho certeza como.
            //Fazer a mesma coisa para as outras verificações.

        }
        else if(channel2.read()){

            request_shipping.write(true);

            // TODO

        }
        else if(channel3.read()){

            request_shipping.write(true);

            // TODO

        }
        else if(channel2.read()){

            request_shipping.write(true);

            // TODO

        }

        request_shipping.write(false);

    }

    SC_CTOR(Arbitration) {
        SC_METHOD(rules);
        sensitive << channel1 << channel2 << channel3 << channel4;
    }

};

#endif