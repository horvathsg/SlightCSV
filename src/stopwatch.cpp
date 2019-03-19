#include "stopwatch.hpp"

#include <iostream>

utils::StopWatch::StopWatch(void) {
    m_status = STOPPED;
}

void utils::StopWatch::start(void) {
    verifyStatus(STOPPED);
    m_start = std::chrono::system_clock::now();
    m_status = STARTED;
}

void utils::StopWatch::stop(void) {
    verifyStatus(STARTED);
    std::chrono::time_point<std::chrono::system_clock> stop = std::chrono::system_clock::now();
    std::chrono::duration<float> duration = stop - m_start;
    std::cout << "Execution took " << duration.count() << " sec." << std::endl;
}

void utils::StopWatch::verifyStatus(stopwatch_status t_status) {
    if (m_status != t_status) {
        throw "stopwatch status mismatch.";
    }
}