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

TEST_F(InstanceResourcesTest, acess2InstanceResources) {
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
    EXPECT_FALSE(invalid_any);
}
}