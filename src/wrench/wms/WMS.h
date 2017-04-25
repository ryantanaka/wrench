/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WRENCH_WMS_H
#define WRENCH_WMS_H

#include "simgrid_S4U_util/S4U_DaemonWithMailbox.h"
#include "wms/scheduler/Scheduler.h"
#include "wms/optimizations/static/StaticOptimization.h"
#include "workflow/Workflow.h"

namespace wrench {

    class Simulation; // forward ref

    /**
     * @brief Abstract implementation of a Workflow Management System
     */
    class WMS : public S4U_DaemonWithMailbox {

    public:
        void add_static_optimization(std::unique_ptr<StaticOptimization>);

    protected:
        WMS(Simulation *, Workflow *, std::unique_ptr<Scheduler>, std::string, std::string);

        Simulation *simulation;
        Workflow *workflow;
        std::unique_ptr<Scheduler> scheduler;
        std::vector<std::unique_ptr<StaticOptimization>> static_optimizations;

    private:
        virtual int main() = 0;
    };
};


#endif //WRENCH_WMS_H
