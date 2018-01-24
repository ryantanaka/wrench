#ifndef WRENCH_ALLTOALL_H
#define WRENCH_ALLTOALL_H

#include "wrench/services/network_proximity/NetworkProximityService.h"
#include "wrench/services/network_proximity/NetworkProximityDaemon.h"

namespace wrench {
  
  class AllToAll: public NetworkProximityService {
  
  public:
    ~AllToAll();

    AllToAll(std::string hostname,
             std::vector<std::string> hosts_in_network,
             double measurement_period, int noise,
             std::map<std::string, std::string> = {}); 

    void start();

    double query(std::pair<std::string, std::string> hosts);

  private:
    friend class Simulation;

    int main();

    bool processNextMessage();

    void addEntryToDatabase(std::pair<std::string, std::string> pair_hosts, double proximity_value);

    std::map<std::pair<std::string, std::string>,double> entries;
    
  };
}

#endif
