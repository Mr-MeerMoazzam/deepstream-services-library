/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _DSL_LOG4CXX_H
#define _DSL_LOG4CXX_H

#include <log4cxx/logger.h>

/**
 * returns a pointer to a log4cxx logger, specific to the calling function.
 * Each function will create a new logger on first use.
 * The logger instance will be reused on each subsequent call to the same function.
 * Note: used by the logging macros below, not to be called directly.
 *
 * @param[in] message the message string to log.
 */
#define LOG4CXX_LOGGER LogMgr::Ptr()->Log4cxxLogger(__METHOD_NAME__)

/**
 * Logs the Entry and Exit of a Function with the DEBUG level.
 * Add macro as the first statement to each function of interest.
 * Consider the intrussion/penalty of this call when adding.
 */
#define LOG_FUNC() LogFunc lf(__METHOD_NAME__)

#define LOG_DEBUG(message) LOG4CXX_DEBUG(LOG4CXX_LOGGER, message)

#define LOG_INFO(message) LOG4CXX_INFO(LOG4CXX_LOGGER, message)

#define LOG_WARN(message) LOG4CXX_WARN(LOG4CXX_LOGGER, message)

#define LOG_ERROR(message) LOG4CXX_ERROR(LOG4CXX_LOGGER, message)

#define LOG_FATAL(message) LOG4CXX_FATAL(LOG4CXX_LOGGER, message)

 
namespace DSL
{

    /**
     * @class LogMgr
     * @file  DssLog4cxx.h
     * @brief Implements a singlton instance to manage initialization and
     * configuration of log4cxx on first call to any of the logging macros. 
     */
    class LogMgr
    {
    public:
    
        /** Returns a pointer to this singleton
         * 
         * @return instance pointer
         */
         
        static LogMgr* Ptr();
        
        /**
         * @brief Returns a pointer to a log4cxx logger unique to each unique name
         * Subsequent calls using the same name will return the same instance
         * 
         * @param[in] name name of the looger to get
         * @return pointer to the logger identified by name
         */
        log4cxx::LoggerPtr Log4cxxLogger(const std::string& name);
    
    private:
        /**
         * @brief private constructor for this singleton class
         */
        LogMgr(){};
        
        static LogMgr* m_pInstatnce;
    };  
    
    /**
     * @class LogFunc
     * @file  DssLog4cxx.h
     * @brief Used to log entry and exit of a function.
     */
    class LogFunc
    {
    public:
        LogFunc(const std::string& name);
        ~LogFunc();
    private:
        std::string m_name; 
    };

} // namespace 


#endif // _DSL_LOG4CXX_H