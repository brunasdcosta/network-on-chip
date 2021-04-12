#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"

SC_MODULE(Router) {

    int id;

    // Buffer.
    sc_signal buffer_p1, buffer_p2, buffer_p3, buffer_p4;

    // Canal de leitura e escrita local.
    sc_in local_channel_in;
    sc_out local_channel_out;

    // Canais de leitura de outros roteadores.
    sc_in north_channel_in;
    sc_in south_channel_in;
    sc_in east_channel_in;
    sc_in west_channel_in;

    // Canais de escrita em outros roteadores.
    sc_out north_channel_out;
    sc_out south_channel_out;
    sc_out east_channel_out;
    sc_out west_channel_out;

    // Sinais para indicar que o roteador quer escrever nos canais.
    bool write_north, write_south, write_east, write_weast;

    // Sinais para indicar que o roteador pode ler dos canais.
    bool can_read_north, can_read_south, can_read_east, can_read_weast;

    void rules(){
        // TODO
    }

    SC_CTOR(Router) {
        SC_METHOD(rules);
        sensitive << north_channel_in << south_channel_in << east_channel_in << west_channel_in;
    }

};

#endif