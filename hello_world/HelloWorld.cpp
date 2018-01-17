//
// Created by ryan on 1/15/18.
//


#include "HelloWorld.h"
#include <iostream>

#include <wrench/logging/TerminalOutput.h>
#include <wrench/simgrid_S4U_util/S4U_Simulation.h>
#include <simulation/SimulationMessage.h>
#include <simgrid_S4U_util/S4U_Mailbox.h>
#include <services/ServiceMessage.h>

XBT_LOG_NEW_DEFAULT_CATEGORY(hw, "Log category for HelloWorld");


namespace wrench {
    HelloWorld::~HelloWorld() {

    }

    HelloWorld::HelloWorld(std::string hostname): Service(hostname, "HelloWorld", "HelloWorld") {

    }

    int HelloWorld::main() {
        TerminalOutput::setThisProcessLoggingColor(WRENCH_LOGGING_COLOR_MAGENTA);

        WRENCH_INFO("Hello World Service starting on host %s!", S4U_Simulation::getHostName().c_str());

        std::cerr << "PRINTING FROM HELLOWORLD" << std::endl;

        return 0;
    }

//    void HelloWorld::start() {
//        this->start_daemon(this->hostname, false);
//    }
}