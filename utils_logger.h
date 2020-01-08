/**
 * @file    Code\utils\SpdLogger.h.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief  实现一个简单的 spdlogger 封装, 编译之后使用
 *          spdLog 封装 文件输出和 控制台输出  自定义loggger
 *          https://blog.csdn.net/et_endeavoring/article/details/86109121
 * @changelog   2019/10/17    IRIS_Chen  Created.
 */

#pragma once


//  static function check dir
// Check only one layer
#ifndef CHECK_DIR_
#define CHECK_DIR_

#ifdef WIN32
#include <io.h>
#include <direct.h>
#endif
#ifdef linux
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

/**
 * @fn  static bool check_dir(const char* dir)
 *
 * @brief   Check dir检查文件夹是否存在 不存在则新建 logs
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 *
 * @param   dir The dir
 *
 * @return  True if it succeeds, false if it fails
 */
static bool check_dir(const char *dir)
{
    int res = 0;
    if (_access(dir, 0) == -1)
    {
#ifdef WIN32
        res = _mkdir(dir);
#endif
#ifdef linux
        res = mkdir(dir.c_str(), 0777);
#endif
        return (res == 0);
    }
    return true;
};
#endif

//*****************************************************
// 注意：
// 文件名 __FILE__ ,函数名 __func__ ，行号__LINE__ 是编译器实现的
// 并非C++头文件中定义的
// 前两个变量是string类型，且__LINE__是整形，所以需要转为string类型
//******************************************************

// 整数类型文件行号 ->转换为string类型  std::to_string 处理
#ifdef _WIN32

/**
 * @def FILENAME_
 *
 * @brief   A macro that defines filename
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 */

#define FILENAME_ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)
#else

/**
 * @def FILENAME_
 *
 * @brief   A macro that defines filename
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 */

#define FILENAME_ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#endif

// 定义一个在日志后添加 文件名 函数名 行号 的宏定义
#ifndef suffix_
/**
 * @def suffix_(msg)
 *
 * @brief   A macro that defines suffix
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 *
 * @param   msg The message
 */

#define suffix_(msg) std::string(msg)\
                .append("  <")\
                .append(FILENAME_)\
                .append(":")\
                .append(std::to_string(__LINE__))\
                .append("> <")\
                .append(__func__)\
                .append(">").c_str()

#if 0
#define suffix_(msg) std::string()\
                .append(" File:")\
                .append(FILENAME_)\
                .append("\", Func:\"")
                .append(__func__)\
                .append("()\", Line:\"")\
                .append(std::to_string(__LINE__))\
                .append("\"")\
                .append(msg).c_str()
#endif
#endif

// 在 spdlog.h 之前定义，才有效
#ifndef SPDLOG_TRACE_ON
#define SPDLOG_TRACE_ON
#endif

#ifndef SPDLOG_DEBUG_ON
#define SPDLOG_DEBUG_ON
#endif

#ifndef SPDLOGGER_H_
#define SPDLOGGER_H_

/**
 * @brief   定义 LOGFILE 这样才会log 到相应文件
 */

#define LOG2FILE_ 1
#include <ctime>  // 引入时间 便于生成文件
#include <vector>
#include <string>
#include <memory>

// spd log 参数
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/details/registry.h"

/**
 * @class   SpdLogger SpdLogger.h Code\inc\SpdLogger.h
 *
 * @brief   A speed logger.
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 */
class SpdLogger
{
    public:
        /**
         * @fn  static SpdLogger& SpdLogger::GetInstance()
         *
         * @brief   Gets the instance
         *
         * @author  IRIS_Chen
         * @date    2019/10/17
         *
         * @return  The instance
         */

        static SpdLogger &GetInstance()
        {
            static SpdLogger m_instance;
            return m_instance;
        }

        /**
         * @fn  auto SpdLogger::GetLogger()
         *
         * @brief   Gets the logger
         *
         * @author  IRIS_Chen
         * @date    2019/10/17
         *
         * @return  The logger
         */
        std::shared_ptr<spdlog::logger> GetLogger()
        {
            return nml_logger;
        }

private:
    /**
     * @fn  SpdLogger::SpdLogger()
     *
     * @brief   Initializes a new instance of the SpdLogger class
     *
     * @author  IRIS_Chen
     * @date    2019/10/17
     */

    SpdLogger()
    {
        // 检查文件夹是否存在
        check_dir("./logs");

        // combined_logger = std::make_shared<spdlog::logger>(file_name, begin(sinks), end(sinks));
        // 打印格式设置 https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        // 设置打印格式  年月日 时分秒.毫秒, 线程ID,日志等级,内容 );
        // combined_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");
        // combined_logger->set_level(spdlog::level::trace);

        // 设置为异步日志
        // spdlog::set_async_mode(32768);  // 必须为 2 的幂

        std::vector<spdlog::sink_ptr> sinkList;

        // #FIXME (schen00) 此处修复每次打开console 的问题
        // 命令行窗口输出 会打开console
        #ifdef _CONSOLE
        #ifdef _DEBUG
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_level(spdlog::level::trace);
            // consoleSink->set_pattern("[multi_sink_example] [%^%l%$] %v");
            consoleSink->set_pattern("[%H:%M:%S][%t][%^%L%$] %v");
            sinkList.push_back(consoleSink);
        #endif
        #endif

        // VS 调试窗口 输出 debug 窗口输出内容
        #ifdef _DEBUG
            auto debuggerSink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
            debuggerSink->set_level(spdlog::level::trace);
            debuggerSink->set_pattern("[%m-%d %H:%M:%S.%e] [%t] [%L] %v");
            sinkList.push_back(debuggerSink);
        #endif

#if LOG2FILE_
        // 使用 当前时间创建 log文件
        // 获取当前时间字符串
        time_t t = time(nullptr);
        struct tm ltm;
        localtime_s(&ltm, &t);
        std::string str;

        std::string format_ = "%04d%02d%02d-%02d%02d";
        char *buf = new char[20];
        sprintf(buf, format_.c_str(), \
                ltm.tm_year + 1900,
                ltm.tm_mon + 1,
                ltm.tm_mday,
                ltm.tm_hour,
                ltm.tm_min);

        str = std::string(buf);

        // 日志文件 每次运行新建文件 按照时间格式明明
        std::string log_file_name = "logs/Bhole-Log-" + str + ".txt";

        // 文件输入 日志全部记录
        auto basicSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file_name);
        basicSink->set_level(spdlog::level::debug);
        basicSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");
        sinkList.push_back(basicSink);
#endif
        // 设置异步模式
        nml_logger = std::make_shared<spdlog::logger>("both", \
                                                    sinkList.begin(), \
                                                    sinkList.end());
        // register it if you need to access it globally
        spdlog::register_logger(nml_logger);

        // 设置日志记录级别
#ifdef _DEBUG
        nml_logger->set_level(spdlog::level::trace);
#else
        nml_logger->set_level(spdlog::level::info);
#endif
        // 设置 logger 格式[%^%L%$]
        // nml_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%5l]  %v");
        // nml_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%5l%$]  %v");
        // 设置当出发 err 或更严重的错误时立刻刷新日志到  disk
        nml_logger->flush_on(spdlog::level::err);

        // 每3秒刷新 将数据 刷新到文件 避免日志崩溃未保存
        spdlog::flush_every(std::chrono::seconds(3));

        nml_logger->info("======== Init SPDLOG ========");
    }

    /**
     * @fn  SpdLogger::~SpdLogger()
     *
     * @brief   Finalizes an instance of the SpdLogger class
     *
     * @author  IRIS_Chen
     * @date    2019/10/17
     */

    ~SpdLogger()
    {
        spdlog::drop_all();
    }

    /**
     * @fn  SpdLogger::SpdLogger(const SpdLogger&) = delete;
     *
     * @brief   Initializes a new instance of the SpdLogger class
     *
     * @author  IRIS_Chen
     * @date    2019/10/17
     *
     * @param   parameter1  The first parameter
     */

    SpdLogger(const SpdLogger &) = delete;

    /**
     * @fn  SpdLogger& SpdLogger::operator=(const SpdLogger&) = delete;
     *
     * @brief   Assignment operator
     *
     * @author  IRIS_Chen
     * @date    2019/10/17
     *
     * @param   parameter1  The first parameter
     *
     * @return  A shallow copy of this object
     */

    SpdLogger &operator=(const SpdLogger &) = delete;

private:
    std::shared_ptr<spdlog::logger> nml_logger;  ///< The nml logger
};

// Logger& operator<<(Logger& log, const char* s);
// Logger& operator<<(Logger& log, const std::string& s);

// TODO(SChen): 完成log  blog 参数
// 设置相应的层级  不同的层级 log 出现信息
// T: 记录部分信息 参数以及其他 不常用-- 不用
// D: 记录调试的 常用变量        // 一般都记录这一层, release 模式不输出
// I: 记录需要记录的信息 + 位置
// W: 记录 可能造成错误的警告信息 + 位置
// E: 记录 错误信息 必须排查 + 位置
// C F: 致命错误, 程序直接终止

// #define LTrace(msg,...) SpdLogger::GetInstance().GetLogger()->trace(suffix_(msg), __VA_ARGS__)
#define LTrace(...) SpdLogger::GetInstance().GetLogger()->trace(__VA_ARGS__)
// #define LDebug(msg,...) SpdLogger::GetInstance().GetLogger()->debug(suffix_(msg), __VA_ARGS__)
#define LDebug(...) SpdLogger::GetInstance().GetLogger()->debug(__VA_ARGS__)
// #define LInfo(msg, ...) SpdLogger::GetInstance().GetLogger()->info(suffix_(msg), __VA_ARGS__)
#define LInfo(...)      SpdLogger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LWarn(msg, ...) SpdLogger::GetInstance().GetLogger()->warn(suffix_(msg), __VA_ARGS__)
// #define LWarn(...)      SpdLogger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LError(msg, ...) SpdLogger::GetInstance().GetLogger()->error(suffix_(msg), __VA_ARGS__)
// #define LError(...) SpdLogger::GetInstance().GetLogger()->error(__VA_ARGS__)
#define LCritical(...) SpdLogger::GetInstance().GetLogger()->critical(__VA_ARGS__)
#define LFatal(msg, ...) SpdLogger::GetInstance().GetLogger()->critical(suffix_(msg), __VA_ARGS__)

/**
 * @def criticalif(b, ...)
 *
 * @brief   A macro that defines criticalif
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 *
 * @param   b   A void to process
 * @param   ... Variable arguments providing additional information
 */
#define criticalif(b, ...)                                               \
    do                                                                   \
    {                                                                    \
        if ((b))                                                         \
        {                                                                \
            SpdLogger::GetInstance().GetLogger()->critical(__VA_ARGS__); \
        }                                                                \
    } while (0)

#endif  // SPDLOGGER_H_
