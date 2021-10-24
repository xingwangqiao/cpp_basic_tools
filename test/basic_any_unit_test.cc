#include<gtest/gtest.h>
#include "any.h"

#include <memory>

namespace Test {
class BasicAnyUnitTest : public testing::Test {
public:
    BasicAnyUnitTest() = default;
    ~BasicAnyUnitTest() = default;

    void SetUp() override {

    }
    void TearDown() override {

    }
private:
    int conut;
};

TEST_F(BasicAnyUnitTest, ConstructionByDefault) {
    basic::Any any;
    EXPECT_EQ(nullptr, any.get<void>());
}

TEST_F(BasicAnyUnitTest, ConstructionByPointer) {
    // create pointer of int;
    int* int_ptr = new int(0);
    basic::Any any(int_ptr);
    EXPECT_EQ(int_ptr, any.get<int>().get());
}

TEST_F(BasicAnyUnitTest, ConstructionBySharedPointer) {
    std::shared_ptr<int> int_ptr = std::make_shared<int>(0);
    basic::Any any(int_ptr);
    EXPECT_EQ(int_ptr, any.get<int>());
}
}