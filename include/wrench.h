/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WRENCH_WRENCH_H
#define WRENCH_WRENCH_H

#include "simulation/Simulation.h"
#include "simulation/SimulationTimestamp.h"
#include "workflow/Workflow.h"

// WMS Implementations
#include "wms/WMS.h"
#include "wms/engine/SimpleWMS.h"

// Schedulers
#include "wms/scheduler/Scheduler.h"
#include "wms/scheduler/RandomScheduler.h"
#include "wms/scheduler/MinMinScheduler.h"
#include "wms/scheduler/MaxMinScheduler.h"

// Static Optimizations
#include "wms/optimizations/static/StaticOptimization.h"
#include "wms/optimizations/static/SimplePipelineClustering.h"

#endif //WRENCH_WRENCH_H
