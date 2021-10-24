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

TEST_F(BasicAnyUnitTest, ConstructionByNullptr) {
    basic::Any any(nullptr);
    EXPECT_EQ(nullptr, any.get<int>().get());
}

TEST_F(BasicAnyUnitTest, ConstructionByPointer) {
    // create pointer of int;
    int* int_ptr = new int(0);
    basic::Any any(int_ptr);
    EXPECT_EQ(int_ptr, any.get<int>().get());

    const int* c_int_ptr = new int(0);
    basic::Any c_any(c_int_ptr);
    EXPECT_EQ(c_int_ptr, c_any.get<int>().get());
}

TEST_F(BasicAnyUnitTest, ConstructionBySharedPointer) {
    std::shared_ptr<int> int_ptr = std::make_shared<int>(0);
    basic::Any any(int_ptr);
    EXPECT_EQ(int_ptr, any.get<int>());
}

TEST_F(BasicAnyUnitTest, Compare) {
    basic::Any any;
    EXPECT_TRUE(any == nullptr);

    basic::Any any_null(nullptr);
    EXPECT_TRUE(any_null == nullptr);

    int* ptr = new int(0);
    basic::Any any_ptr(ptr);
    EXPECT_TRUE(any_ptr == ptr);

    std::shared_ptr<int> s_ptr = std::make_shared<int>(0);
    basic::Any any_shared_ptr(s_ptr);
    EXPECT_TRUE(any_shared_ptr == s_ptr);
}

TEST_F(BasicAnyUnitTest, Assignment) {
    basic::Any any;

    any = nullptr;
    EXPECT_TRUE(any == nullptr);

    int* ptr = new int(0);
    any = ptr;
    EXPECT_TRUE(any == ptr);

    std::shared_ptr<int> s_ptr = std::make_shared<int>(0);
    any = s_ptr;
    EXPECT_TRUE(any == s_ptr);
}

}