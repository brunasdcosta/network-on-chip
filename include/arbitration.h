#ifndef ARBITRATION_H
#define ARBITRATION_H

#include "systemc.h"

SC_MODULE(Arbitration) {

    // Sinais que identificam quais canais de entrada estão solicitando sair pelo canal do árbitro.
    // Lembrando que uma mensagem não deve entrar e sair pelo mesmo canal. Assim, no máximo quatro desses sinais podem estar ativos ao mesmo tempo.
    sc_in<bool> local_channel, north_channel, south_channel, east_channel, west_channel;

    // Sinal que identifica que o árbitro escolheu um canal e quer enviar a mensagem.
    sc_out<bool> request_shipping;

    /**
     * Indica qual canal o árbitro escolheu.
     * 000 (0) - Canal local.
     * 001 (1) - Canal norte.
     * 010 (2) - Canal sul.
     * 011 (3) - Canal leste.
     * 100 (4) - Canal oeste.  
     */
    sc_out<sc_uint<3>> chosen_channel;

    void rules(){

        if(local_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(0);

            //TODO: acho que aqui tem que fazer alguma verificação com o fluxo de entrada e saída, só não tenho certeza como.
            //Fazer a mesma coisa para as outras verificações.

        }
        else if(north_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(1);

        }
        else if(south_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(2);

        }
        else if(east_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(3);

        }
        else if(west_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(4);

        }

        request_shipping.write(false);

    }

    SC_CTOR(Arbitration) {
        SC_METHOD(rules);
        sensitive << local_channel << north_channel << south_channel << east_channel << west_channel;
    }

};

#endif