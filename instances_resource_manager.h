/**
 * @brief manage resources of instance just like pointer
 */
#pragma once
#include "any.h"
#include "instance_resources.h"

#include <vector>
#include <map>

namespace basic {
class InstancesResourceManager {
public:
    InstancesResourceManager() = default;
    ~InstancesResourceManager() = default;

    static InstanceID createStorage();
    static void destroyStorage(InstanceID);

    static std::shared_ptr<InstanceResources> getResources(InstanceID id);
    // stored resource that no instanceID
    static std::shared_ptr<InstanceResources> getAnyResources();

    static std::vector<InstanceID> getInstanceIDOfAllResource(std::string key, void* value);
    static InstanceID getInstanceIDOfFirstResource(std::string key, void* value);
};
}
/**
 * map<InstanceID, InstanceResources> resources;
 */