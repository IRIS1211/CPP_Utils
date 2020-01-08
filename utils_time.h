/**
 * @file    Code\utils\utils_files.h.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Declares the utilities files class
 * * 有关文件操作的通用组件, 便于迁移和复用  
 * * 使用C++ 通用组件, 暂时不考虑跨平台操作
 * @changelog   2019/12/16    IRIS_Chen Created.
 */


#pragma once
#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

#include <vector>
#include <string>
#include <iostream>

class Utils_Time
{
    public:

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
    static float CalcPeriodMs(int flg = 0, std::string str = "funcPeroidMS");

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
    static float CalcPeriodFps(int flg = 0, std::string str = "funcPeroidFPS");
    
    /**
    * @fn  static std::string Utils_Time::GetTime(char c = '_', bool rand_flg = false);
    *
    * @brief   Gets time string 按照YYYYYmmDD-HHMM 的形式输出 默认字符为连符号
    *          *        可以修改为 - _ ~ / \
    *
    * @author  IRIS_Chen
    * @date    2019/6/15
    *
    * @param   c           (Optional) The character
    * @param   rand_flg    (Optional) True to random flg
    *
    * @return  The time string
    */
    static std::string GetTime(char c = '_', bool rand_flg = false);

    /**
    * @fn  static std::string Utils_String::GetDate(char c = '_');
    *
    * @brief   Gets date string  返回 8位 日期值
    *
    * @author  IRIS_Chen
    * @date    2019/11/17
    *
    * @param   c   (Optional) The character
    *
    * @return  The date string
    */
    static std::string GetDate(void);
};

#endif  //UTILS_TIME_H_

