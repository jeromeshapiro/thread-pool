#include <gtest/gtest.h>
#include <runner.h>
#include <memory>

class RunnerTests : public testing::Test {
protected:
    void SetUp() {
        runner = std::make_shared<Runner>(0);
    }

    std::shared_ptr<Runner> runner;
};

TEST_F(RunnerTests, is_active_by_default) {
    EXPECT_EQ(runner->isActive(), true);
}
