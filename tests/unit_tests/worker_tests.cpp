#include <gtest/gtest.h>
#include <worker.h>
#include <memory>

class WorkerUnitTests : public testing::Test {
protected:
    void SetUp() {
        runner = std::make_shared<Worker>(0);
    }

    std::shared_ptr<Worker> runner;
};

TEST_F(WorkerUnitTests, has_empty_task_count_by_default) {
    EXPECT_EQ(runner->getBufferedTaskCount(), 0);
}

TEST_F(WorkerUnitTests, is_active_by_default) {
    EXPECT_EQ(runner->getStatus(), WorkerStatus::ACTIVE);
}

TEST_F(WorkerUnitTests, can_pause_worker) {
    runner->setStatus(WorkerStatus::PAUSED);
    EXPECT_EQ(runner->getStatus(), WorkerStatus::PAUSED);
}

TEST_F(WorkerUnitTests, can_stop_worker) {
    runner->setStatus(WorkerStatus::STOPPED);
    EXPECT_EQ(runner->getStatus(), WorkerStatus::STOPPED);
}

TEST_F(WorkerUnitTests, can_assign_task_when_paused) {
    runner->setStatus(WorkerStatus::PAUSED);

    auto assignmentFlag = runner->assignTask([](){});

    EXPECT_EQ(assignmentFlag, WorkerAssignmentFlag::SUCCESS);
    EXPECT_EQ(runner->getBufferedTaskCount(), 1);
}

TEST_F(WorkerUnitTests, cannot_assign_task_when_stopped) {
    runner->setStatus(WorkerStatus::STOPPED);

    auto assignmentFlag = runner->assignTask([](){});

    EXPECT_EQ(assignmentFlag, WorkerAssignmentFlag::FAILIURE);
    EXPECT_EQ(runner->getBufferedTaskCount(), 0);
}
