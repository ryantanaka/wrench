//
// Created by ryan on 1/15/18.
//

#ifndef WRENCH_HELLOWORLD_H
#define WRENCH_HELLOWORLD_H

#include "wrench/services/Service.h"

namespace wrench{

    class HelloWorld: public Service {

    public:
        ~HelloWorld();

        HelloWorld(std::string hostname);

//        void start();

    private:
        friend class Simulation;

        int main();
    };
}

#endif //WRENCH_HELLOWORLD_H
