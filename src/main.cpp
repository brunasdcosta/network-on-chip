#include "systemc.h"

#include "../include/buffer.h"
#include "../include/routing.h"
#include "../include/arbitration.h"
#include "../include/flux-control-in.h"
#include "../include/flux-control-out.h"
#include "../include/router.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<2>> local_x_in, local_y_in; // Valores X e Y de entrada.
    sc_signal<bool> local_x_sign_in, local_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> local_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> local_x_out, local_y_out; // Valores X e Y de saída.
    sc_signal<bool> local_x_sign_out, local_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> local_message_out; // Mensagem de saída.

    // // Canal norte.
    sc_signal<sc_uint<2>> north_x_in, north_y_in; // Valores X e Y de entrada.
    sc_signal<bool> north_x_sign_in, north_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> north_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> north_x_out, north_y_out; // Valores X e Y de saída.
    sc_signal<bool> north_x_sign_out, north_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> north_message_out; // Mensagem de saída.

    // // Canal sul.
    sc_signal<sc_uint<2>> south_x_in, south_y_in; // Valores X e Y de entrada.
    sc_signal<bool> south_x_sign_in, south_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> south_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> south_x_out, south_y_out; // Valores X e Y de saída.
    sc_signal<bool> south_x_sign_out, south_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> south_message_out; // Mensagem de saída.

    // // Canal leste.
    sc_signal<sc_uint<2>> east_x_in, east_y_in; // Valores X e Y de entrada.
    sc_signal<bool> east_x_sign_in, east_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> east_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> east_x_out, east_y_out; // Valores X e Y de saída.
    sc_signal<bool> east_x_sign_out, east_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> east_message_out; // Mensagem de saída.

    // // Canal oeste.
    sc_signal<sc_uint<2>> west_x_in, west_y_in; // Valores X e Y de entrada.
    sc_signal<bool> west_x_sign_in, west_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> west_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> west_x_out, west_y_out; // Valores X e Y de saída.
    sc_signal<bool> west_x_sign_out, west_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> west_message_out; // Mensagem de saída.

    // // Sinais de controle para dizer se o buffer pode ler da entrada ou escrever na saída.
    // sc_signal<bool> local_buffer_read, north_buffer_read, south_buffer_read, east_buffer_read, west_buffer_read;
    sc_signal<bool> local_buffer_write, north_buffer_write, south_buffer_write, east_buffer_write, west_buffer_write;

    std::cout << "Iniciando...\n";

    Router router("Router");
    router.local_x_in(local_x_in);
    router.local_y_in(local_y_in);
    router.local_x_sign_in(local_x_sign_in);
    router.local_y_sign_in(local_y_sign_in);
    router.local_message_in(local_message_in);
    router.local_x_out(local_x_out);
    router.local_y_out(local_y_out);
    router.local_x_sign_out(local_x_sign_out);
    router.local_y_sign_out(local_y_sign_out);
    router.local_message_out(local_message_out);
    
    router.north_x_in(north_x_in);
    router.north_y_in(north_y_in);
    router.north_x_sign_in(north_x_sign_in);
    router.north_y_sign_in(north_y_sign_in);
    router.north_message_in(north_message_in);
    router.north_x_out(north_x_out);
    router.north_y_out(north_y_out);
    router.north_x_sign_out(north_x_sign_out);
    router.north_y_sign_out(north_y_sign_out);
    router.north_message_out(north_message_out);

    router.south_x_in(south_x_in);
    router.south_y_in(south_y_in);
    router.south_x_sign_in(south_x_sign_in);
    router.south_y_sign_in(south_y_sign_in);
    router.south_message_in(south_message_in);
    router.south_x_out(south_x_out);
    router.south_y_out(south_y_out);
    router.south_x_sign_out(south_x_sign_out);
    router.south_y_sign_out(south_y_sign_out);
    router.south_message_out(south_message_out);

    router.east_x_in(east_x_in);
    router.east_y_in(east_y_in);
    router.east_x_sign_in(east_x_sign_in);
    router.east_y_sign_in(east_y_sign_in);
    router.east_message_in(east_message_in);
    router.east_x_out(east_x_out);
    router.east_y_out(east_y_out);
    router.east_x_sign_out(east_x_sign_out);
    router.east_y_sign_out(east_y_sign_out);
    router.east_message_out(east_message_out);

    router.west_x_in(west_x_in);
    router.west_y_in(west_y_in);
    router.west_x_sign_in(west_x_sign_in);
    router.west_y_sign_in(west_y_sign_in);
    router.west_message_in(west_message_in);
    router.west_x_out(west_x_out);
    router.west_y_out(west_y_out);
    router.west_x_sign_out(west_x_sign_out);
    router.west_y_sign_out(west_y_sign_out);
    router.west_message_out(west_message_out);

    router.local_buffer_write(local_buffer_write);
    router.north_buffer_write(north_buffer_write);
    router.south_buffer_write(south_buffer_write);
    router.east_buffer_write(east_buffer_write);
    router.west_buffer_write(west_buffer_write);

    // router.initilize();
    // router.run();
    sc_start();

    std::cout << "Finalizado!\n";

    return 0;
}