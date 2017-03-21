/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *  @brief WRENCH::SimulationMessage and derived classes to encapsulate
 *  control/data messages exchanged by simulated processes
 */

#include "SimulationMessage.h"

namespace wrench {

		/** Base Simgrid Message **/
		SimulationMessage::SimulationMessage(Type  t, double s) {
			type = t;
			size = s;
		}

		/** STOP_DAEMON MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		StopDaemonMessage::StopDaemonMessage(): SimulationMessage(STOP_DAEMON, 1024.00) {
		}

		/** RUN_JOB MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		RunJobMessage::RunJobMessage(WorkflowJob *job): SimulationMessage(RUN_STANDARD_JOB, 1024.0) {
			this->job = job;
		}

		/** JOB_DONE MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		JobDoneMessage::JobDoneMessage(WorkflowJob *job, ComputeService *cs): SimulationMessage(STANDARD_JOB_DONE, 1024.0) {
			this->job = job;
			this->compute_service = cs;
		}

		/** JOB_FAILED MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		JobFailedMessage::JobFailedMessage(WorkflowJob *job, ComputeService *cs): SimulationMessage(STANDARD_JOB_FAILED, 1024.0) {
			this->job = job;
			this->compute_service = cs;
		}

		/** RUN_TASK MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		RunTaskMessage::RunTaskMessage(WorkflowTask *task): SimulationMessage(RUN_TASK, 1024.0) {
			this->task = task;
		}

		/** TASK_DONE MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		TaskDoneMessage::TaskDoneMessage(WorkflowTask *task, SequentialTaskExecutor *executor): SimulationMessage(TASK_DONE, 1024.0) {
			this->task = task;
			this->task_executor = executor;
		}

		/** NUM_IDLE_CORES_REQUEST MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		NumIdleCoresRequestMessage::NumIdleCoresRequestMessage() : SimulationMessage(NUM_IDLE_CORES_REQUEST, 1024.0) {
		}

		/** NUM_IDLE_CORES_ANSWER MESSAGE **/
		// TODO: MAke the "1024" below configurable somehow
		NumIdleCoresAnswerMessage::NumIdleCoresAnswerMessage(unsigned long num) : SimulationMessage(NUM_IDLE_CORES_ANSWER, 1024.0) {
			this->num_idle_cores = num;
		}


};