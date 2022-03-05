#include <gtest/gtest.h>

#include "instance_resources.h"

namespace Test {
class InstanceResourcesTest : public testing::Test {
public:
    InstanceResourcesTest() = default;
    ~InstanceResourcesTest() = default;

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(InstanceResourcesTest, access2InstanceResources) {
    // create a storage of Instance
    basic::InstanceID ins_id = 1;
    basic::InstanceResources storage(ins_id);
    EXPECT_TRUE(ins_id = storage.getInstanceID());

    // set item
    int* testValue = new int(12345678);
    storage.setItem("testkey", testValue);

    // get valid key-value
    EXPECT_TRUE(storage.hasValue("testkey"));
    basic::Any test_any = storage.getValue("testkey");
    EXPECT_TRUE(*testValue == *test_any.get<int>());

    // get invalid key-value
    EXPECT_FALSE(storage.hasValue("invalidkey"));
    basic::Any invalid_any = storage.getValue("invalidkey");
    EXPECT_FALSE(invalid_any);

    // remove item
    storage.removeItem("testkey");
    EXPECT_FALSE(storage.hasValue("testkey"));
    basic::Any removed_any = storage.getValue("testkey");
    EXPECT_FALSE(removed_any);

    // clear storage
    storage.setItem("key", new int(0));
    EXPECT_FALSE(storage.empty());
    storage.clear();
    EXPECT_TRUE(storage.empty());
    EXPECT_FALSE(storage.hasValue("key"));
}

TEST_F(InstanceResourcesTest, manageResourceWhenResourceIsItself) {
    // create a storage of Instance
    basic::InstanceID ins_id = 1;
    basic::InstanceResources* storage = new basic::InstanceResources(ins_id);
    EXPECT_TRUE(ins_id = storage->getInstanceID());

    // stored itself
    storage->setItem("this_storage", storage);

    // get valid key-value
    EXPECT_TRUE(storage->hasValue("this_storage"));
    basic::Any storage_any = storage->getValue("this_storage");
    EXPECT_TRUE(storage_any == storage);

    // remove itself
    storage->removeItem("this_storage");
    EXPECT_FALSE(storage->hasValue("this_storage"));
    basic::Any removed_any = storage->getValue("this_storage");
    EXPECT_FALSE(removed_any);
}
}