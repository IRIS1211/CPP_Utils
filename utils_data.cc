/**
 * @file    Code\utils\utils_data.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities data class
 * @changelog   2019/12/26    IRIS_Chen Created.
 */

#include "./utils_data.h"
/**
 * @fn  float Utils_Data::FastSin(float x)
 *
 * @brief   Utilities data class
 *
 * @author  IRIS_Chen
 * @date    2019/12/26
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 *
 */
float Utils_Data::FastSin(float x)
{
    // 判断范围  - PI 到 PI
    while (x < -FLOAT_PI)
    {
        x += static_cast<float>(2 * FLOAT_PI);
    }
    while (x > FLOAT_PI)
    {
        x -= static_cast<float>(2 * FLOAT_PI);
    }

    const float B = 1.2732f; // 4 / CV_PI;
    const float C = -0.4053f; // -4 / (CV_PI*CV_PI);
    float y = B * x + C * x * abs(x);

    // 是否开启更高精度的拟合
#if 0 
    // const float Q = 0.775; 
    const float P = 0.225f;
    y = P * (y * abs(y) - y) + y;
#endif 
    return y;
}

/**
 * @fn  float Utils_Data::FastCos(float x)
 *
 * @brief   Fast cosine
 *
 * @author  IRIS_Chen
 * @date    2019/12/26
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 */
float Utils_Data::FastCos(float x)
{
    return FastSin(x + FLOAT_PI/2.0f);
}

/**
 * @fn  int Utils_Data::Calc(uchar *dat, int len)
 *
 * @brief   通用计算函数 计算从 指针开始的指定位数的 计算结果
 *
 * @author  IRIS_Chen
 * @date    2019/12/26
 *
 * @param [in,out]  dat If non-null, the dat
 * @param           len The length
 *
 * @return  An int
 */
int Utils_Data::Calc(uchar *dat, int len)
{
    // int res = (*dat) & 0x7F;  // 获取第一个字节后 7 位的数据
    int res = (*dat);  // 获取第一个字节后 7 位的数据

    for (int i = 1; i < len; i++)
    {
        res = (res << 8) + *(dat + i);
    }
    return res;
}