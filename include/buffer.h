#ifndef BUFFER_H
#define BUFFER_H

// #include <stdio.h>
#include "systemc.h"

SC_MODULE(Buffer) {

    sc_in<sc_uint<2>> x_in, y_in; // Valores X e Y de entrada.
    sc_in<bool> x_sign_in, y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> message_in; // Mensagem de entrada.

    // Sinais de controle do buffer.
    sc_in<bool> read_; // Sinaliza para o buffer ler da entrada.
    sc_in<bool> write_; // Sinaliza para o buffer escrever na saída.
    sc_out<bool> is_full; // Sinaliza se o buffer está cheio.
    sc_logic buffer_is_full = SC_LOGIC_0; // Sinal de controle interno.

    sc_uint<2> x_stored, y_stored; // Valores X e Y armazenados no buffer.
    sc_logic x_sign_stored, y_sign_stored; // Sinais de X e Y armazenados no buffer. 0 - negativo; 1 - positivo.
    sc_uint<32> message_stored; // Mensagem armazenada no buffer.

    sc_out<sc_uint<2>> x_out, y_out; // Valores X e Y de saída.
    sc_out<bool> x_sign_out, y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> message_out; // Mensagem de saída.

    void rules(){

        if(buffer_is_full == SC_LOGIC_0 && read_.read() == 1) { // Se o buffer não está cheio e foi mandado que ele armazene os valores.

            // std::cout << "\n---O buffer vai ler os valores---\n";

            // std::cout << "\nValores que chegaram:\nx=" << x_in.read() << "\nx_sign=" << x_sign_in.read() << "\ny=" << y_in.read() << "\ny_sign=" << y_sign_in.read() << "\nmessage=" << message_in.read() << "\n";

            x_stored = x_in;
            if(x_sign_in.read() == false)
                x_sign_stored = SC_LOGIC_0;
            else
                x_sign_stored = SC_LOGIC_1;

            y_stored = y_in;
            
            if(y_sign_in.read() == false)
                y_sign_stored = SC_LOGIC_0;
            else
                y_sign_stored = SC_LOGIC_1;

            message_stored = message_in;

            is_full.write(true);
            buffer_is_full = SC_LOGIC_1;

            // std::cout << "\nValores armazenados:\nx=" << x_stored << "\nx_sign=" << x_sign_stored << "\ny=" << y_stored << "\ny_sign=" << y_sign_stored << "\nmessage=" << message_stored << "\n";

        }

        if(buffer_is_full == SC_LOGIC_1 && write_.read() == 1) { // Se o buffer está cheio e foi mandado que ele envie os valores.

            // std::cout << "\n---O buffer vai escrever na saída---\n";

            // std::cout << "\nValores armazenados:\nx=" << x_stored << "\nx_sign=" << x_sign_stored << "\ny=" << y_stored << "\ny_sign=" << y_sign_stored << "\nmessage=" << message_stored << "\n";

            x_out.write(x_stored);
            if(x_sign_stored == SC_LOGIC_0)
                x_sign_out.write(false);
            else
                x_sign_out.write(true);

            y_out.write(y_stored);

            if(y_sign_stored == SC_LOGIC_0)
                y_sign_out.write(false);
            else
                y_sign_out.write(true);

            message_out.write(message_stored);

            is_full.write(0);
            buffer_is_full = SC_LOGIC_0;

        }

    }

    SC_CTOR(Buffer) {
        SC_METHOD(rules);
        sensitive << read_ << write_;
    }

};

#endif