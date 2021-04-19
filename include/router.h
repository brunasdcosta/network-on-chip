#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"
#include "buffer.h"

SC_MODULE(Router) {

    int id; // Identificador do roteador.
    sc_signal<sc_uint<2>> x_in, y_in, x_out, y_out;
    sc_signal<bool> x_sign_in, y_sign_in, read_, write_;
    sc_signal<sc_uint<32>> message_in, message_out;
    sc_signal<bool> channel1, channel2, channel3, channel4;
    sc_signal<bool> request_to_receive, buffer_is_full, request_to_shipping, can_ship;

    void run(){
        Buffer buffer("buffer");
        buffer.x_in(x_in);
        buffer.y_in(y_in);
        buffer.x_out(x_out);
        buffer.y_out(y_out);
        buffer.x_sign_in(x_sign_in);
        buffer.y_sign_in(x_sign_in);
        buffer.read_(read_);
        buffer.write_(write_);
        buffer.message_in(message_in);
        buffer.message_out(message_out);

        Arbitration arbitration("arbitration");
        arbitration.channel1(channel1);
        arbitration.channel2(channel2);
        arbitration.channel3(channel3);
        arbitration.channel4(channel4);

        HandshakeIN handshakein("handshakein");
        handshakein.request_to_receive(request_to_receive);
        handshakein.buffer_is_full(buffer_is_full);

        HandshakeOUT handshakeout("handshakeout");
        handshakeout.can_ship(can_ship);
        handshakeout.request_to_shipping(request_to_shipping);

        RoutingXY routingXY("RoutingXY");
        routingXY.x_in(x_in);
        routingXY.y_in(y_in);
        routingXY.x_sign_in(x_sign_in);
        routingXY.y_sign_in(y_sign_in);


        std::cout << "ENTROUU!\n";
        

        x_in.write(1);
        y_in.write(0);
        x_sign_in.write(1);
        y_sign_in.write(1);
        message_in.write(22);

        write_.write(1);
        read_.write(0);


        std::cout << "Mensagem saída: " <<  message_out.read() << std::endl;

        sc_stop();




    }


    SC_CTOR(Router) {
        SC_THREAD(run);
        sensitive << x_in << y_in << x_sign_in << y_sign_in << read_ << write_ << message_in << channel1 << channel2 << channel3 << channel4 << request_to_receive << buffer_is_full << request_to_shipping << can_ship;
    }

};

#endif