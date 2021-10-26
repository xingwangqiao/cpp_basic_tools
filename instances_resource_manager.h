/**
 * @brief manage resources of instance just like pointer
 */
#include "any.h"

#include <vector>
#include <map>

// tmp define
#define InstanceResources int
#define InstanceID int
// end tmp define

namespace basic {
class InstancesResourceManager {
public:
    InstancesResourceManager() = default;
    ~InstancesResourceManager() = default;

    InstanceID createStorage();
    void destroyStorage(InstanceID);

    std::shared_ptr<InstanceResources> getResources(InstanceID id);
    // stored resource that no instanceID
    std::shared_ptr<InstanceResources> getAnyResources();

    std::vector<InstanceID> getInstanceIDOfAllResource(std::string key, void* value);
    InstanceID getInstanceIDOfFirstResource(std::string key, void* value);
};
}
/**
 * map<InstanceID, InstanceResources> resources;
 */