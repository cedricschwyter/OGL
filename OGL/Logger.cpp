/**
    Implements the Logger namespace

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Logger.cpp
    @brief        Implementation of the Logger namespace
*/
#include <fstream>
#include <time.h>
#include <iostream>
#include <string>

#include "Logger.hpp"
#if defined WIN_64 || defined WIN_32
    #include <direct.h>
    #include "ConsoleColor.hpp"
#elif defined LINUX
    #include <sys/stat.h>
#endif

namespace logger {

    const char* LOG_DIR = "logs";

    const std::string        ERROR_LOG_PATH = "logs/error.log";
    const std::string        START_LOG_PATH = "logs/start.log";
    const std::string        EVENT_LOG_PATH = "logs/event.log";
    std::ofstream            error;
    std::ofstream            start;
    std::ofstream            event;

    std::mutex               streamBusy;

    LOGGER_STATUS_CODE init() {
#ifndef OGL_NO_LOG
#if defined WIN_64 || defined WIN_32
        if (_mkdir(LOG_DIR) >= 0) return LOGGER_SC_DIRECTORY_CREATION_ERROR;
#elif defined LINUX
        struct stat st;
        if(stat("/tmp",&st) != 0) {

            if (mkdir(LOG_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {

                logger::log(ERROR_LOG, "Failed to create log directory at " + std::string(LOG_DIR));
                return LOGGER_SC_DIRECTORY_CREATION_ERROR;

            }

        }
#endif
        error.open(ERROR_LOG_PATH, std::ios::trunc);
        start.open(START_LOG_PATH, std::ios::app);
        event.open(EVENT_LOG_PATH, std::ios::trunc);
        logger::log(EVENT_LOG, "Successfully initialized Logger");
#endif
        return LOGGER_SC_SUCCESS;

    }

    LOGGER_STATUS_CODE log(LOG_TYPE log_, const char* msg_) {
#ifndef OGL_NO_LOG
        streamBusy.lock();
        static int countEvent = 0;
        static int countError = 0;
        std::ofstream stream;

        time_t current_time;
        struct tm local_time;

        time(&current_time);
#if defined WIN_64 || defined WIN_32
        localtime_s(&local_time, &current_time);
#elif defined LINUX
        localtime_r(&current_time, &local_time);
#endif

        int Year        = local_time.tm_year + 1900;
        int Month       = local_time.tm_mon + 1;
        int Day         = local_time.tm_mday;

        int Hour        = local_time.tm_hour;
        int Min         = local_time.tm_min;
        int Sec         = local_time.tm_sec;

        std::thread::id thisThread = std::this_thread::get_id();

        switch (log_) {
        case ERROR_LOG:
            if (countError == 0) {

                countError++;

                error << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << "CRITICAL: "
                    << msg_ << std::endl;

#if (defined OGL_DEVELOPMENT || defined OGL_RELEASE_CONSOLE) && (defined WIN_64 || WIN_32)
                std::cerr << green << Day << white << ":"
                    << green << Month << white << ":"
                    << green << Year << white << "   "
                    << green << Hour << white << ":"
                    << green << Min << white << ":"
                    << green << Sec << yellow << " in thread "
                    << thisThread << "        ===        "
                    << red << "CRITICAL: "
                    << blue << msg_ << white << std::endl;
#else
                std::cerr << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << "CRITICAL: "
                    << msg_ << std::endl;
#endif
            }
            else {

                error << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << "CRITICAL: "
                    << msg_ << std::endl;

#if (defined OGL_DEVELOPMENT || defined OGL_RELEASE_CONSOLE) && (defined WIN_64 || WIN_32)
                std::cerr << green << Day << white << ":"
                    << green << Month << white << ":"
                    << green << Year << white << "   "
                    << green << Hour << white << ":"
                    << green << Min << white << ":"
                    << green << Sec << yellow << " in thread "
                    << thisThread << "        ===        "
                    << red << "CRITICAL: "
                    << blue << msg_ << white << std::endl;
#else
                std::cerr << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << "CRITICAL: "
                    << msg_ << std::endl;
#endif
            }

        case START_LOG:

            start << Day << ":"
                << Month << ":"
                << Year << "   "
                << Hour << ":"
                << Min << ":"
                << Sec << " in thread "
                << thisThread << "        ===        "
                << msg_ << std::endl;

        case EVENT_LOG:
            if (countEvent == 0) {

                countEvent++;

                event << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << msg_ << std::endl;

#if (defined OGL_DEVELOPMENT || defined OGL_RELEASE_CONSOLE) && (defined WIN_64 || WIN_32)
                std::cout << green << Day << white << ":"
                    << green << Month << white << ":"
                    << green << Year << white << "   "
                    << green << Hour << white << ":"
                    << green << Min << white << ":"
                    << green << Sec << yellow << " in thread "
                    << thisThread << white << "        ===        "
                    << blue << msg_ << white << std::endl;
#else
                std::cout << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << msg_ << std::endl;
#endif
            }
            else {

                event << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << msg_ << std::endl;

#if (defined OGL_DEVELOPMENT || defined OGL_RELEASE_CONSOLE) && (defined WIN_64 || WIN_32)
                std::cout << green << Day << white << ":"
                    << green << Month << white << ":"
                    << green << Year << white << "   "
                    << green << Hour << white << ":"
                    << green << Min << white << ":"
                    << green << Sec << yellow << " in thread "
                    << thisThread << white << "        ===        "
                    << blue << msg_ << white << std::endl;
#else
                std::cout << Day << ":"
                    << Month << ":"
                    << Year << "   "
                    << Hour << ":"
                    << Min << ":"
                    << Sec << " in thread "
                    << thisThread << "        ===        "
                    << msg_ << std::endl;
#endif
            }

            break;

        default:
            break;

        }
#endif
        if (log_ == ERROR_LOG) {
#if defined OGL_DEVELOPMENT && (defined WIN_64 || defined WIN_32)
            __debugbreak();
#else
            throw std::runtime_error(msg_);
#endif
        }

        streamBusy.unlock();

        return LOGGER_SC_SUCCESS;

    }

    LOGGER_STATUS_CODE log(LOG_TYPE log_, std::string msg_) {

        return logger::log(log_, msg_.c_str());

    }

}