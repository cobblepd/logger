#include <chrono>
#include <thread>
#include "logger.h"

int main()
{
    auto& logger = Logger::getInstance();

    logger.configure("test/logger.txt", 15, 42);

    for (int i = 0; i < 120; ++i) {
        logger.info("test {}", i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    logger.shutdown();
}