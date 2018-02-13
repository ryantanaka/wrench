/**
 * Copyright (c) 2017-2018. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WRENCH_TERMINATOR_H
#define WRENCH_TERMINATOR_H

#include <map>
#include <set>
#include "wrench/services/compute/ComputeService.h"
#include "wrench/services/storage/StorageService.h"
#include "wrench/services/file_registry/FileRegistryService.h"
#include "wrench/services/network_proximity/NetworkProximityService.h"

namespace wrench {

    /***********************/
    /** \cond DEVELOPER    */
    /***********************/

    /**
     * @brief A helper daemon (co-located with the Simulation) to handle service termination
     */
    class Terminator {

    public:

        /***********************/
        /** \cond INTERNAL     */
        /***********************/

        void registerComputeService(std::set<ComputeService *> compute_services);

        void registerComputeService(ComputeService *compute_service);

        void shutdownComputeService(std::set<ComputeService *> compute_services);

        void shutdownComputeService(ComputeService *compute_service);

        void registerStorageService(StorageService *storage_service);

        void shutdownStorageService(StorageService *storage_service);

        void registerFileRegistryService(FileRegistryService *file_registry_service);

        void shutdownFileRegistryService(FileRegistryService *file_registry_service);

        void registerNetworkProximityService(NetworkProximityService *network_proximity_service);

        void shutdownNetworkProximityService(NetworkProximityService *network_proximity_service);

    private:

        std::map<ComputeService *, int> compute_services;
        std::map<StorageService *, int> storage_services;
        std::map<FileRegistryService *, int> file_registry_services;
        std::map<NetworkProximityService *, int> network_proximity_services;

        /**
         * Register a reference to a Service
         */
        template<class T>
        void registerService(std::map<T, int> &services_map, T service) {
          if (not service) {
            return;
          }
          services_map.find(service) == services_map.end() ? services_map[service]++ : services_map[service] = 0;
        }

        /**
         * @brief Shutdown a Service. If the FileRegistryService has only one reference it will be stopped,
         * otherwise the counter is decreased
         */
        template<class T>
        bool shutdownService(std::map<T, int> &services_map, T service) {

          if (not service) {
            return false;
          }
          if (services_map.find(service) == services_map.end()) {
            throw std::runtime_error(
                    "Terminator::shutdownService(): Service not registered: " + service->getName());
          }
          if (not service->isUp()) {
            throw std::runtime_error(
                    "Terminator::shutdownService(): Service is not running: " + service->getName());
          }

          // if the service has only one reference it will be stopped, otherwise the counter is decreased
          if (services_map[service] <= 1) {
            service->stop();
            services_map.erase(service);
            return true;
          }
          services_map[service]--;
          return false;
        }

        /***********************/
        /** \endcond           */
        /***********************/
    };

    /***********************/
    /** \endcond            */
    /***********************/

}

#endif //WRENCH_TERMINATOR_H