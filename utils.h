/**
 * @file    Code\utils\utils.h.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   通用 utils 组件
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#pragma once

#ifndef UTILS_H__
#define UTILS_H__

#include "./utils_logger.h"
#include "./Utils_Exception.h"
#include "./utils_string.h"
#include "./utils_files.h"
#include "./utils_cv.h"
#include "./utils_data.h"
#include "./utils_qt.h"
#include "./utils_time.h"


// 直接继承 可以使用 同一的类名 访问
class Utils :
    public Utils_String,
    public Utils_Files,
    public Utils_Data,
    public Utils_CV
{
    public:

    /**
    * @fn  template<typename T> void Limit(T &q,const T minV,const T maxV)
    *
    * @brief   定义 函数限定函数， 根据 输入的值现象参数的范围
    *
    * @author  IRIS_Chen
    * @date    2019/6/15
    *
    * @tparam  T   Generic type parameter.
    * @param [in,out]  q       A T to process
    * @param           minV    The minimum v
    * @param           maxV    The maximum v
    */
    template<typename T>
    static T Limit(T &q, const T minV, const T maxV)
    {
        // 将值限定在 设定区域内; 超过的值 都限定在 min max 中
        q = std::max(minV, std::min(maxV, q));
        return q;
    }

    /**
    * @fn  void ClearQueue(T &q)
    *
    * @brief   将队列清空 // 定义 清空队列函数  快速 清空队列
    *
    * @author  IRIS_Chen
    * @date    2019/6/15
    *
    * @param [in,out]  q   A T to process
    */
    template<typename T>
    static void ClearQueue(T &q)
    {
        T empty;
        swap(empty, q);
    }


};


#endif  //UTILS_H__