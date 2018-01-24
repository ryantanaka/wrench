/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <wrench/logging/TerminalOutput.h>
#include "wrench/services/network_proximity/NetworkProximityService.h"

#include <simulation/SimulationMessage.h>


XBT_LOG_NEW_DEFAULT_CATEGORY(network_proximity_service, "Log category for Network Proximity Service");

namespace wrench {


    /**
     * @brief Destructor
     */

    NetworkProximityService::~NetworkProximityService() {
        this->default_property_values.clear();
    }

    /**
     * @brief Constructor
     * @param hostname: the hostname on which to start the service
     * @param hosts_in_network: the hosts running in the network
     * @param message_size: the message size (in bytes) exchanged by monitoring daemon
     * @param measurement_period: the time (in seconds) between measurements at a daemon
     * @param noise: a random noise added to the measurement period to avoid weird synchronicity behaviors
     * @param plist: a property list ({} means "use all defaults")
     */
    NetworkProximityService::NetworkProximityService(std::string hostname,
                                                     std::vector<std::string> hosts_in_network,
                                                     int message_size, double measurement_period, int noise,
                                                     std::map<std::string, std::string> plist):
    NetworkProximityService(std::move(hostname), std::move(hosts_in_network), message_size, measurement_period, noise, std::move(plist),"") {

    }

    /**
     * @brief Constructor
     * @param hostname: the hostname on which to start the service
     * @param hosts_in_network: the hosts running in the network
     * @param message_size: the message size (in bytes) exchanged by monitoring daemon
     * @param measurement_period: the time (in seconds) between measurements at a daemon
     * @param noise: a random noise added to the measurement period to avoid weird synchronicity behaviors
     * @param plist: a property list ({} means "use all defaults")
     * @param suffix: suffix to append to the service name and mailbox
     */
    NetworkProximityService::NetworkProximityService(
            std::string hostname,
            std::vector<std::string> hosts_in_network,
            int message_size, double measurement_period, int noise,
            std::map<std::string, std::string> plist,
            std::string suffix) :
            Service(hostname, "network_proximity" + suffix, "network_proximity" + suffix) {

        this->hosts_in_network = std::move(hosts_in_network);

        // Set default properties
        for (auto p : this->default_property_values) {
            this->setProperty(p.first, p.second);
        }

        // Set specified properties
        for (auto p : plist) {
            this->setProperty(p.first, p.second);
        }

        // Create the network daemons
        std::vector<std::string>::iterator it;
        for (it=this->hosts_in_network.begin();it!=this->hosts_in_network.end();it++){
            this->network_daemons.push_back(std::unique_ptr<NetworkProximityDaemon>(new NetworkProximityDaemon(*it,this->mailbox_name, message_size,measurement_period,noise)));
        }
    }

    /**
     * @brief Starts the network proximity service sets of daemons and the
     *        proximity service itself
     *
     * @throw std::runtime_error
     */
    void NetworkProximityService::start() {
      try {
        // Start the network daemons
        for (auto it = this->network_daemons.begin(); it != this->network_daemons.end(); it++) {
          (*it)->start();
        }
        this->start_daemon(this->hostname, false);
      } catch (std::runtime_error &e) {
        throw;
      }
    }
}