#include "systemc.h"

#include "../include/buffer.h"
#include "../include/routing.h"
#include "../include/arbitration.h"
#include "../include/flux-control-in.h"
#include "../include/flux-control-out.h"
#include "../include/router.h"

int sc_main(int argc, char* argv[]) {


    sc_signal

    std::cout << "Iniciando...\n";

    Router router("Router");
    // router.initilize();
    // router.run();
    sc_start();

    std::cout << "Finalizado!\n";

    return 0;
}