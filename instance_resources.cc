#include "instance_resources.h"

namespace basic {
void InstanceResources::clear() {
    std::lock_guard<std::mutex> _(m_mutex_);
    storage_.clear();
}

void InstanceResources::setItem(ResourceTarget key, basic::Any value) {
    auto old_value = this->getValue(key);
    do {
        std::lock_guard<std::mutex> _(m_mutex_);
        storage_[key] = value;
    } while(false);
    old_value.reset();
}

void InstanceResources::removeItem(ResourceTarget key) {
    auto old_value = this->getValue(key);
    do {
        std::lock_guard<std::mutex> _(m_mutex_);
        storage_.erase(key);
    } while(false);
    old_value.reset();
}

bool InstanceResources::hasValue(ResourceTarget key) {
    std::lock_guard<std::mutex> _(m_mutex_);
    return (storage_.find(key) != storage_.end());
}

Any InstanceResources::getValue(ResourceTarget key) {
    std::lock_guard<std::mutex> _(m_mutex_);
    auto it = storage_.find(key);
    if(it == storage_.end())
        return Any();

    return it->second;
}

InstanceID InstanceResources::getInstanceID() const {
    return instance_id_;
}

}