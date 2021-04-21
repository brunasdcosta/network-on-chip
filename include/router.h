#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"
#include "buffer.h"
#include "routing.h"
#include "flux-control-in.h"
#include "flux-control-out.h"
#include "arbitration.h"

SC_MODULE(Router) {

    int id; // Identificador do roteador.

    // Canal local.
    sc_in<sc_uint<2>> local_x_in, local_y_in; // Valores X e Y de entrada.
    sc_in<bool> local_x_sign_in, local_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> local_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> local_x_out, local_y_out; // Valores X e Y de saída.
    sc_out<bool> local_x_sign_out, local_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> local_message_out; // Mensagem de saída.

    // Canal norte.
    sc_in<sc_uint<2>> north_x_in, north_y_in; // Valores X e Y de entrada.
    sc_in<bool> north_x_sign_in, north_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> north_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> north_x_out, north_y_out; // Valores X e Y de saída.
    sc_out<bool> north_x_sign_out, north_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> north_message_out; // Mensagem de saída.

    // Canal sul.
    sc_in<sc_uint<2>> south_x_in, south_y_in; // Valores X e Y de entrada.
    sc_in<bool> south_x_sign_in, south_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> south_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> south_x_out, south_y_out; // Valores X e Y de saída.
    sc_out<bool> south_x_sign_out, south_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> south_message_out; // Mensagem de saída.

    // Canal leste.
    sc_in<sc_uint<2>> east_x_in, east_y_in; // Valores X e Y de entrada.
    sc_in<bool> east_x_sign_in, east_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> east_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> east_x_out, east_y_out; // Valores X e Y de saída.
    sc_out<bool> east_x_sign_out, east_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> east_message_out; // Mensagem de saída.

    // Canal oeste.
    sc_in<sc_uint<2>> west_x_in, west_y_in; // Valores X e Y de entrada.
    sc_in<bool> west_x_sign_in, west_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> west_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> west_x_out, west_y_out; // Valores X e Y de saída.
    sc_out<bool> west_x_sign_out, west_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> west_message_out; // Mensagem de saída.

    // Sinais de controle para dizer se o buffer pode ler da entrada ou escrever na saída.
    sc_signal<bool> local_buffer_read, north_buffer_read, south_buffer_read, east_buffer_read, west_buffer_read;
    sc_signal<bool> local_buffer_write, north_buffer_write, south_buffer_write, east_buffer_write, west_buffer_write;

    // Sinais de controle para verificar se o buffer de cada canal está cheio.
    sc_signal<bool> local_buffer_full, north_buffer_full, south_buffer_full, east_buffer_full, west_buffer_full;

    // Sinais de controle para definição da rota.
    sc_signal<sc_uint<3>> local_direction, north_direction, south_direction, east_direction, west_direction;

    // Sinais de controle que indicam para onde cada canal quer enviar.
    sc_signal<bool> local_to_north, local_to_south, local_to_east, local_to_west;
    sc_signal<bool> north_to_local, north_to_south, north_to_east, north_to_west;
    sc_signal<bool> south_to_local, south_to_north, south_to_east, north_to_west;
    sc_signal<bool> east_to_local, east_to_north, east_to_south, north_to_west;
    sc_signal<bool> west_to_local, west_to_north, west_to_south, west_to_east;

    // Sinais de controle que indicam que cada árbitro escolheu um canal para enviar.
    sc_signal<bool> local_arbitration_ship, north_arbitration_ship, south_arbitration_ship, east_arbitration_ship, west_arbitration_ship;

    // Sinais de controle que indicam qual canal o árbitro escolheu.
    sc_signal<sc_uint<3>> local_arbitration_chosen, north_arbitration_chosen, south_arbitration_chosen, east_arbitration_chosen, west_arbitration_chosen;

    sc_sigan<bool> this_
    sc_signal<bool> local_can_receive, north_can_receive, south_can_receive, east_can_receive, west_can_receive;

    void initialize(){
        init_buffers();
        init_routings();
        init_arbitrations();
        init_flux_controls_out();
        init_flux_controls_in();
    }

    void init_buffers(){

        Buffer local_buffer("local_buffer");
        local_buffer.x_in(local_x_in);
        local_buffer.y_in(local_y_in);
        local_buffer.x_sign_in(local_x_sign_in);
        local_buffer.y_sign_in(local_y_sign_in);
        local_buffer.message_in(local_message_in);
        local_buffer.read_(local_buffer_read);
        local_buffer.write_(local_buffer_write);
        local_buffer.is_full(local_buffer_full);

        Buffer north_buffer("north_buffer");
        north_buffer.x_in(north_x_in);
        north_buffer.y_in(north_y_in);
        north_buffer.x_sign_in(north_x_sign_in);
        north_buffer.y_sign_in(north_y_sign_in);
        north_buffer.message_in(north_message_in);
        north_buffer.read_(north_buffer_read);
        north_buffer.write_(north_buffer_write);
        north_buffer.is_full(north_buffer_full);

        Buffer south_buffer("south_buffer");
        south_buffer.x_in(south_x_in);
        south_buffer.y_in(south_y_in);
        south_buffer.x_sign_in(south_x_sign_in);
        south_buffer.y_sign_in(south_y_sign_in);
        south_buffer.message_in(south_message_in);
        south_buffer.read_(south_buffer_read);
        south_buffer.write_(south_buffer_write);
        south_buffer.is_full(south_buffer_full);

        Buffer east_buffer("east_buffer");
        east_buffer.x_in(east_x_in);
        east_buffer.y_in(east_y_in);
        east_buffer.x_sign_in(east_x_sign_in);
        east_buffer.y_sign_in(east_y_sign_in);
        east_buffer.message_in(east_message_in);
        east_buffer.read_(east_buffer_read);
        east_buffer.write_(east_buffer_write);
        east_buffer.is_full(east_buffer_full);

        Buffer west_buffer("west_buffer");
        west_buffer.x_in(west_x_in);
        west_buffer.y_in(west_y_in);
        west_buffer.x_sign_in(west_x_sign_in);
        west_buffer.y_sign_in(west_y_sign_in);
        west_buffer.message_in(west_message_in);
        west_buffer.read_(west_buffer_read);
        west_buffer.write_(west_buffer_write);
        west_buffer.is_full(west_buffer_full);
    }

    void init_routings(){

        RoutingXY local_routing("local_routing");
        routingXY.x_in(local_x_in);
        routingXY.y_in(local_y_in);
        routingXY.x_sign_in(local_x_sign_in);
        routingXY.y_sign_in(local_y_sign_in);
        routingXY.direction(local_direction);

        RoutingXY north_routing("north_routing");
        routingXY.x_in(north_x_in);
        routingXY.y_in(north_y_in);
        routingXY.x_sign_in(north_x_sign_in);
        routingXY.y_sign_in(north_y_sign_in);
        routingXY.direction(north_direction);

        RoutingXY south_routing("south_routing");
        routingXY.x_in(south_x_in);
        routingXY.y_in(south_y_in);
        routingXY.x_sign_in(south_x_sign_in);
        routingXY.y_sign_in(south_y_sign_in);
        routingXY.direction(south_direction);

        RoutingXY east_routing("east_routing");
        routingXY.x_in(east_x_in);
        routingXY.y_in(east_y_in);
        routingXY.x_sign_in(east_x_sign_in);
        routingXY.y_sign_in(east_y_sign_in);
        routingXY.direction(east_direction);

        RoutingXY west_routing("west_routing");
        routingXY.x_in(west_x_in);
        routingXY.y_in(west_y_in);
        routingXY.x_sign_in(west_x_sign_in);
        routingXY.y_sign_in(west_y_sign_in);
        routingXY.direction(west_direction);
    }

    void init_arbitrations(){

        Arbitration local_arbitration("local_arbitration");
        local_arbitration.north_channel(north_to_local);
        local_arbitration.south_channel(south_to_local);
        local_arbitration.east_channel(east_to_local);
        local_arbitration.west_channel(west_to_local);
        local_arbitration.request_shipping(local_arbitration_ship);
        local_arbitration.chosen_channel(local_arbitration_chosen);

        Arbitration north_arbitration("north_arbitration");
        north_arbitration.local_channel(local_to_north);
        north_arbitration.south_channel(south_to_north);
        north_arbitration.east_channel(east_to_north);
        north_arbitration.west_channel(west_to_north);
        north_arbitration.request_shipping(north_arbitration_ship);
        north_arbitration.chosen_channel(north_arbitration_chosen);

        Arbitration south_arbitration("south_arbitration");
        south_arbitration.local_channel(local_to_south);
        south_arbitration.north_channel(north_to_south);
        south_arbitration.east_channel(east_to_south);
        south_arbitration.west_channel(west_to_south);
        south_arbitration.request_shipping(south_arbitration_ship);
        south_arbitration.chosen_channel(south_arbitration_chosen);

        Arbitration east_arbitration("east_arbitration");
        east_arbitration.local_channel(local_to_east);
        south_arbitration.north_channel(north_to_east);
        east_arbitration.south_channel(south_to_east);
        east_arbitration.west_channel(west_to_east);
        east_arbitration.request_shipping(east_arbitration_ship);
        east_arbitration.chosen_channel(east_arbitration_chosen);

        Arbitration west_arbitration("west_arbitration");
        west_arbitration.local_channel(local_to_west);
        south_arbitration.north_channel(north_to_west);
        east_arbitration.south_channel(south_to_west);
        west_arbitration.east_channel(east_to_west);
        west_arbitration.request_shipping(west_arbitration_ship);
        west_arbitration.chosen_channel(west_arbitration_chosen);
    }

    void init_flux_controls_out(){

        HandshakeOUT local_out("local_out");
        local_out.request_to_shipping(local_arbitration_ship);
        local_out.can_ship();
        local_out.shipping_request();
    }

    void init_flux_controls_in(){
        HandshakeIN handshakein("handshakein");
        handshakein.request_to_receive(request_to_receive);
        handshakein.buffer_is_full(buffer_is_full);
        handshakein.can_receive(can_receive);
    }

    void rules(){
        // TODO: fazer o restantes das ligações entre os sinais de controle.
    }

    SC_CTOR(Router) {
        initilize();
        SC_THREAD(rules);
        sensitive << local_x_in << local_y_in << local_x_sign_in << local_y_sign_in << local_message_in
                  << north_x_in << north_y_in << north_x_sign_in << north_y_sign_in << north_message_in
                  << south_x_in << south_y_in << south_x_sign_in << south_y_sign_in << south_message_in
                  << east_x_in << east_y_in << east_x_sign_in << east_y_sign_in << east_message_in
                  << west_x_in << west_y_in << west_x_sign_in << west_y_sign_in << west_message_in;
    }

};

#endif