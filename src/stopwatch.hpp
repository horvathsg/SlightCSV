#ifndef _UTILS_STOPWATCH_HPP
#define _UTILS_STOPWATCH_HPP

#include <chrono>

namespace utils {

    typedef enum {STARTED, STOPPED} stopwatch_status;

    class StopWatch {

        public:
            StopWatch(void);
            void start(void);
            void stop(void);

        private:
            void verifyStatus(stopwatch_status t_status);
            std::chrono::time_point<std::chrono::system_clock> m_start;
            utils::stopwatch_status m_status;

    };

}

#endif // _UTILS_STOPWATCH_HPP