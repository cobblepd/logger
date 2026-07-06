#include <gtest/gtest.h>

#include "logger.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class LoggerTest : public ::testing::Test {
protected:
    fs::path logDir = fs::current_path() / "test_logs";

    void SetUp() override {
        Logger::getInstance().shutdown();
    }
};

TEST_F(LoggerTest, ShutdownBeforeConfigureDoesNotThrow) {
    EXPECT_NO_THROW(Logger::getInstance().shutdown());
}