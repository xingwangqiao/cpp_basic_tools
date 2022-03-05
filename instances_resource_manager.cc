#include "instances_resource_manager.h"

#include <mutex>
#include <map>

#define ANY_SRC_INSTANCE_ID 0
#define INVAILD_INSTANCE_ID (ANY_SRC_INSTANCE_ID - 1)
namespace basic {
class InstanceResourceManagerImpl {
public:
    std::mutex m_mutex_;
    InstanceID cur_alloc_instance_id_;
    std::map<InstanceID, std::shared_ptr<InstanceResources>> manage_storage_;
};

InstanceResourceManagerImpl* ManagerInstance() {
    static InstanceResourceManagerImpl* signal_ins = new InstanceResourceManagerImpl();
    return signal_ins;
}

InstanceID InstancesResourceManager::createStorage() {
    std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
    InstanceID id = ++ManagerInstance()->cur_alloc_instance_id_;
    std::shared_ptr<InstanceResources> clear_store= std::make_shared<InstanceResources>(id);
    ManagerInstance()->manage_storage_[id] = clear_store;
    return id;
}

void InstancesResourceManager::destroyStorage(InstanceID id) {
    std::shared_ptr<InstanceResources> resources = getResources(id);
    do {
        std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
        ManagerInstance()->manage_storage_.erase(id);
    } while(false);
    resources = nullptr;
}

std::shared_ptr<InstanceResources> InstancesResourceManager::getResources(InstanceID id) {
    std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
    auto ins_it = ManagerInstance()->manage_storage_.find(id);
    if(ins_it == ManagerInstance()->manage_storage_.end())
        return nullptr;
    return ins_it->second;
}

std::shared_ptr<InstanceResources> InstancesResourceManager::getAnyResources() {
    std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
    auto ins_it = ManagerInstance()->manage_storage_.find(ANY_SRC_INSTANCE_ID);
    if(ins_it == ManagerInstance()->manage_storage_.end()) {
        std::shared_ptr<InstanceResources> storage = std::make_shared<InstanceResources>(ANY_SRC_INSTANCE_ID);
        ManagerInstance()->manage_storage_[ANY_SRC_INSTANCE_ID] = storage;
        return storage;
    }
    return ins_it->second;
}

std::vector<InstanceID> InstancesResourceManager::getInstanceIDOfAllResource(std::string key, void* value) {
    std::vector<InstanceID> ids;
    std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
    for(const auto& it : ManagerInstance()->manage_storage_) {
        if(it.second->hasValue(key) && it.second->getValue(key) == value)
            ids.push_back(it.first);
    }
    return ids;
}

InstanceID InstancesResourceManager::getInstanceIDOfFirstResource(std::string key, void* value) {
    std::lock_guard<std::mutex> _(ManagerInstance()->m_mutex_);
    for(const auto& it : ManagerInstance()->manage_storage_) {
        if(it.second->hasValue(key) && it.second->getValue(key) == value)
            return it.first;
    }
    return INVAILD_INSTANCE_ID;
}
}