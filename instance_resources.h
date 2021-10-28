#pragma once
#include "any.h"

#include <map>
#include <mutex>

namespace basic {
// define instanceID type
using InstanceID = intptr_t;
class InstanceResources {
public:
    using ResourceTarget = std::string;
public:
    InstanceResources() = delete;
    InstanceResources(InstanceID id) : instance_id_(id) { }
    ~InstanceResources() = default;

    // Prohibit copy construction/move construction
    InstanceResources(const InstanceResources& rhs) = delete;
    InstanceResources(InstanceResources&& rhs) = delete;

    // Prohibit copy assignment/move assignment
    InstanceResources& operator= (const InstanceResources& rhs) = delete;
    InstanceResources& operator= (InstanceResources&& rhs) = delete;

    void clear();

    void setItem(ResourceTarget key, basic::Any any);
    void removeItem(ResourceTarget key);

    bool hasValue(ResourceTarget key);
    Any getValue(ResourceTarget key);

    InstanceID getInstanceID() const;

private:
    std::mutex m_mutex_;
    InstanceID instance_id_;
    std::map<ResourceTarget, basic::Any> storage_;
};
}