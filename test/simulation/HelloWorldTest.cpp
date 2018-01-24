/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */


#include <gtest/gtest.h>
#include <wrench-dev.h>

#include "NoopScheduler.h"

#include "TestWithFork.h"


class HelloWorldTest : public ::testing::Test {

public:
    wrench::WorkflowTask *task;

    void do_Simple_test();

protected:
    HelloWorldTest() {

      // Create an empty workflow
      workflow = new wrench::Workflow();

      // Create a one-host platform file
      std::string xml = "<?xml version='1.0'?>"
              "<!DOCTYPE platform SYSTEM \"http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd\">"
              "<platform version=\"4.1\"> "
              "   <AS id=\"AS0\" routing=\"Full\"> "
              "       <host id=\"SingleHost\" speed=\"1f\"/> "
              "   </AS> "
              "</platform>";
      FILE *platform_file = fopen(platform_file_path.c_str(), "w");
      fprintf(platform_file, "%s", xml.c_str());
      fclose(platform_file);

    }

    std::string platform_file_path = "/tmp/platform.xml";
    wrench::Workflow *workflow;

};




/**********************************************************************/
/**  SIMPLE SIMULATION TEST                                          **/
/**********************************************************************/

class SimpleTestWMS : public wrench::WMS {

public:
    SimpleTestWMS(HelloWorldTest *test,
                  wrench::Workflow *workflow,
                  std::unique_ptr<wrench::Scheduler> scheduler,
                  std::string hostname) :
            wrench::WMS(workflow, std::move(scheduler), hostname, "test") {
      this->test = test;
    }


private:

    HelloWorldTest *test;

    int main() {



      this->simulation->shutdownAllComputeServices();
      this->simulation->shutdownAllStorageServices();

      return 0;
    }
};

TEST_F(HelloWorldTest, Simple) {
  DO_TEST_WITH_FORK(do_Simple_test);
}

void HelloWorldTest::do_Simple_test() {


  // Create and initialize a simulation
  wrench::Simulation *simulation = new wrench::Simulation();
  int argc = 1;
  char **argv = (char **) calloc(1, sizeof(char *));
  argv[0] = strdup("one_task_test");

  simulation->init(&argc, argv);

  // Setting up the platform
  EXPECT_NO_THROW(simulation->instantiatePlatform(platform_file_path));

  // Get a hostname
  std::string hostname = simulation->getHostnameList()[0];

  // Create a WMS
  EXPECT_NO_THROW(wrench::WMS *wms = simulation->setWMS(
          std::unique_ptr<wrench::WMS>(new SimpleTestWMS(this, workflow,
                                                         std::unique_ptr<wrench::Scheduler>(
                                                                 new NoopScheduler()),
                          hostname))));

  // Create a Compute Service
  EXPECT_NO_THROW(simulation->add(
          std::unique_ptr<wrench::MultihostMulticoreComputeService>(
                  new wrench::MultihostMulticoreComputeService(hostname, true, true,
                                                               {std::make_pair(hostname, 0)},
                                                               nullptr,
                                                               {}))));

  // Create a Storage Service
  EXPECT_NO_THROW(simulation->add(
          std::unique_ptr<wrench::SimpleStorageService>(
                  new wrench::SimpleStorageService(hostname, 10000000000000.0))));

  // Create a HelloWorld Service
  EXPECT_THROW(simulation->setHelloWorldService(std::unique_ptr<wrench::HelloWorld>(
          new wrench::HelloWorld(hostname))), std::runtime_error);


  // Running the simulation
  EXPECT_NO_THROW(simulation->launch());

  delete simulation;

  free(argv[0]);
  free(argv);
}

