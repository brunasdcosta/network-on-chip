#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"
#include "buffer.h"
#include "routing.h"
#include "flux-control-in.h"
#include "flux-control-out.h"
#include "arbitration.h"
#include "testbench.h"

SC_MODULE(Router) {

    int id; // Identificador do roteador.
    sc_signal<sc_uint<3>> direction;
    sc_signal<sc_uint<2>> x_in, y_in, x_out, y_out;
    sc_signal<bool> x_sign_in, y_sign_in, read_, write_, is_full, x_sign_out, y_sign_out;
    sc_signal<sc_uint<32>> message_in, message_out;
    sc_signal<bool> channel1, channel2, channel3, channel4;
    sc_signal<bool> can_receive, request_to_receive, buffer_is_full, request_to_shipping, can_ship, request_shipping;

    void initilize(){
        Buffer buffer("Buffer");
        buffer.x_in(x_in);
        buffer.y_in(y_in);
        buffer.x_out(x_out);
        buffer.y_out(y_out);
        buffer.x_sign_in(x_sign_in);
        buffer.y_sign_in(y_sign_in);
        buffer.x_sign_out(x_sign_out);
        buffer.y_sign_out(y_sign_out);
        buffer.is_full(is_full);
        buffer.read_(read_);
        buffer.write_(write_);
        buffer.message_in(message_in);
        buffer.message_out(message_out);


        Arbitration arbitration("arbitration");
        arbitration.channel1(channel1);
        arbitration.channel2(channel2);
        arbitration.channel3(channel3);
        arbitration.channel4(channel4);
        arbitration.request_shipping(request_shipping);


        HandshakeIN handshakein("handshakein");
        handshakein.request_to_receive(request_to_receive);
        handshakein.buffer_is_full(buffer_is_full);
        handshakein.can_receive(can_receive);

        HandshakeOUT handshakeout("handshakeout");
        handshakeout.can_ship(can_ship);
        handshakeout.request_to_shipping(request_to_shipping);
        handshakeout.shipping_request(request_shipping);

        RoutingXY routingXY("RoutingXY");
        routingXY.x_in(x_in);
        routingXY.y_in(y_in);
        routingXY.x_sign_in(x_sign_in);
        routingXY.y_sign_in(y_sign_in);
        routingXY.direction(direction);

        Testbench testbench("Testbench");

        testbench.x(x_in);
        testbench.y(y_in);
        testbench.x_signal(x_sign_in);
        testbench.y_signal(y_sign_in);
        testbench.read_(read_);
        testbench.write_(write_);
        testbench.message(message_in);

    }

    void run(){
        std::cout << "ENTROU!\n";
    }


    SC_CTOR(Router) {
        initilize();
        SC_THREAD(run);
        sensitive << x_in << y_in << x_sign_in << y_sign_in << read_ << write_ << message_in << channel1 << channel2 << channel3 << channel4 << request_to_receive << buffer_is_full << request_to_shipping << can_ship;
    }

};

#endif