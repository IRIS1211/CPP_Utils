/**
 * @file    Code\utils\utils_time.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities time class 关于时间的组件
 * @changelog   2019/12/20    IRIS_Chen Created.
 */

#include <string.h>
#include <direct.h>
#include <time.h>
#include "./utils.h"
#include "./utils_time.h"


/**
* @fn  static float Utils_Time::CalcPeriodMs(int flg = 0, std::string str = "funcPeroid");
*
* @brief   计算经过的 时间 ms 单位
*
* @author  IRIS_Chen
* @date    2019/6/17
*
* @param   flg (Optional) The flg
* @param   str (Optional) The string
*
* @return  The time milliseconds
*/
float Utils_Time::CalcPeriodMs(int flg, std::string str)
{
    static  clock_t gTime_tmp = 0;
    float time_ms = -1;
    if (!flg)
    {
        gTime_tmp = clock();
    }
    else
    {
        // 计算得到的ms 值  生成 字符串输出
        time_ms = static_cast<float>(clock() - gTime_tmp)*1000.0f / CLOCKS_PER_SEC;
        str = "Funciton [ " + str + " ] in " \
            + __FILE__ + " - " + std::to_string(__LINE__) \
            + ":  " + std::to_string(time_ms) + "ms";
        LDebug(str);
    }
    return time_ms;
}

/**
* @fn  static float Utils_Time::CalcPeriodMs(int flg = 0, std::string str = "funcPeroid");
*
* @brief   计算经过的 时间 ms 单位
*
* @author  IRIS_Chen
* @date    2019/6/17
*
* @param   flg (Optional) The flg
* @param   str (Optional) The string
*
* @return  The time milliseconds
*/
float Utils_Time::CalcPeriodFps(int flg /*= 0*/, std::string str /*= "funcPeroidFPS"*/)
{
    static  clock_t gFps_tmp = 0;
    float time_fps = -1;
    if (!flg)
    {
        gFps_tmp = clock();
    }
    else
    {
        // 计算得到的ms 值  生成 字符串输出
        time_fps = CLOCKS_PER_SEC / static_cast<float>(clock() - gFps_tmp);
        gFps_tmp = 0;
        str = "Processs [ " + str + " ] in" \
            + __FILE__ + std::to_string(__LINE__) \
            + ":  " + std::to_string(time_fps) + "fps";
        LDebug(str);
    }
    return time_fps;
}


/**
* @fn  std::string Utils_Time::GetTime(char c, bool rand_flg)
*
* @brief   Gets a time 获取时间字符串   YYYYMMDD_HHMM 默认字符为连符号
* *        可以修改为 - _ ~ / \
*
* @author  IRIS_Chen
* @date    2019/12/12
*
* @param   c           The character
* @param   rand_flg    True to random flg
*
* @return  The time
*/
std::string Utils_Time::GetTime(char c, bool rand_flg)
{
    time_t t = time(nullptr);
    struct tm ltm;
    localtime_s(&ltm, &t);

    std::string format_ = "%04d%02d%02d-%02d%02d";
    char *buf = new char[20];
    sprintf(buf, format_.c_str(), \
            ltm.tm_year + 1900,
            ltm.tm_mon + 1,
            ltm.tm_mday,
            ltm.tm_hour,
            ltm.tm_min);

    // 根据 buf 生成 字符串
    std::string str =  std::string(buf);

    // 如果随机 加入三位随机值
    if (rand_flg)
    {
        str += c + std::to_string(rand() % 100);
    }
    return str;
}


/**
* @fn  std::string Utils_String::GetDate(void)
*
* @brief   获取日期 字符串 YYYYMMDD
*
* @author  IRIS_Chen
* @date    2019/12/12
*
* @return  日期字符串  8位
*/
std::string Utils_Time::GetDate(void)
{
    time_t t = time(nullptr);
    struct tm ltm;
    localtime_s(&ltm, &t);
    std::string str = Utils_String::NumToString(1900 + ltm.tm_year, 4)
        + Utils_String::NumToString(1 + ltm.tm_mon, 2)   // 设置月份
        + Utils_String::NumToString(ltm.tm_mday, 2);

    std::string format_ = "%04d%02d%02d";
    char *buf = new char[20];
    sprintf(buf, format_.c_str(), \
            ltm.tm_year + 1900,
            ltm.tm_mon + 1,
            ltm.tm_mday);
    // 根据 buf 生成 字符串
    std::string str = std::string(buf);
    return str;
}

