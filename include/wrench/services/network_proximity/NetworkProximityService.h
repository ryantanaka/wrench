#ifndef WRENCH_NETWORKPROXIMITYSERVICE_H
#define WRENCH_NETWORKPROXIMITYSERVICE_H

#include "wrench/services/Service.h"
#include "wrench/services/network_proximity/NetworkProximityServiceProperty.h"
#include "wrench/services/network_proximity/NetworkProximityDaemon.h"

namespace wrench {

  class NetworkProximityService: public Service {

    protected:
      std::map<std::string, std::string> default_property_values =
      {{NetworkProximityServiceProperty::STOP_DAEMON_MESSAGE_PAYLOAD, "1024"},
       {NetworkProximityServiceProperty::DAEMON_STOPPED_MESSAGE_PAYLOAD , "1024"},
       {NetworkProximityServiceProperty::NETWORK_DB_LOOKUP_MESSAGE_PAYLOAD , "1024"},
       {NetworkProximityServiceProperty::NETWORK_DAEMON_CONTACT_ANSWER_PAYLOAD , "1024"},
       {NetworkProximityServiceProperty::NETWORK_PROXIMITY_TRANSFER_MESSAGE_PAYLOAD, "1024"},
       {NetworkProximityServiceProperty::LOOKUP_OVERHEAD , "0.0"},
      };

      NetworkProximityService(std::string hostname,
                              std::vector<std::string> hosts_in_network,
                              double measurement_period, int noise,
                              std::map<std::string, std::string> plist,
                              std::string suffix = "");

      std::vector<std::unique_ptr<NetworkProximityDaemon>> network_daemons;
      std::vector<std::string> hosts_in_network;

    public:
      ~NetworkProximityService();

//      NetworkProximityService(std::string hostname,
//                              std::vector<std::string> hosts_in_network,
//                              int message_size, double measurement_period, int noise,
//                              std::map<std::string, std::string> = {});

//      virtual void start() = 0;

      virtual double query(std::pair<std::string, std::string> hosts) = 0;

    private:
      friend class Simulation;

//      virtual int main() = 0;

      virtual bool processNextMessage() = 0;
  };

}

#endif
