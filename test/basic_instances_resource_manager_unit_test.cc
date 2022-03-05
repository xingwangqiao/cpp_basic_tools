#include<gtest/gtest.h>

#include "any.h"
#include "instances_resource_manager.h"

namespace Test {
class InstancesResourceManagerTest : public testing::Test {
public:
    InstancesResourceManagerTest() = default;
    ~InstancesResourceManagerTest() = default;

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(InstancesResourceManagerTest, createAndDestoryInstanceStorage) {
    basic::InstanceID ins_id = basic::InstancesResourceManager::createStorage();
    ASSERT_TRUE(ins_id);

    basic::InstancesResourceManager::destroyStorage(ins_id);
}
}