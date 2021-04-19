#include "systemc.h"

#include "../include/buffer.h"
#include "../include/routing.h"
#include "../include/arbitration.h"
#include "../include/flux-control-in.h"
#include "../include/flux-control-out.h"
#include "../include/router.h"

int sc_main(int argc, char* argv[]) {


    std::cout << "Iniciando...\n";

    Router router("Router");
    router.run();

    std::cout << "Finalizado!\n";

    return 0;
}