/**
 * @file    Code\utils\utils_data.h.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   定义常用的数据处理 组件
 * @changelog   2019/12/3    IRIS_Chen  Created.
 */
#ifndef UTILS_DATA_H__
#define  UTILS_DATA_H__
#include <vector>

 // 定义 简单使用 的 FLOAT 类型的PI 参数
const float  FLOAT_PI = 3.141592f;

#pragma once
class Utils_Data
{
    public:

    /**
     * @fn  template<typename T1, typename T2> static void Utils_Data::LeastSquare(const std::vector<T1> &data_x, const std::vector<T2>& data_y, float &var_a, float &var_b)
     *
     * @brief   閫氳繃xy  寰楀埌 鏁版嵁鐨?鏈€灏忎簩涔樺弬鏁?
     *
     * @author  IRIS_Chen
     * @date    2019/12/3
     *
     * @tparam  T1  Generic type parameter.
     * @tparam  T2  Generic type parameter.
     * @param           data_x  The data x coordinate
     * @param           data_y  The data y coordinate
     * @param [in,out]  var_a   The variable a
     * @param [in,out]  var_b   The variable b
     */
    template<typename T1, typename T2>
    static void LeastSquare(const std::vector<T1> &data_x,
                            const std::vector<T2>& data_y,
                            float &var_a,
                            float &var_b)
    {
        float t1 = 0.0f, t2 = 0.0f, t3 = 0.0f, t4 = 0.0f;
        if (data_x.empty() || data_y.empty())
            return;
        size_t N = data_x.size();
        // 两个数组的长度一致
        assert(data_x.size() == data_y.size());
        T1 x;
        T2 y;
        var_a = 0.0f, var_b = 0.0f;

        for (int i = 0; i < data_x.size(); i++)
        {
            x = data_x[i];
            y = data_y[i];

            t1 += x*x;
            t2 += x;
            t3 += x*y;
            t4 += y;
        }
        // 计算 分子
        float down = (t1*N - t2*t2);
        if (abs(down) < 0.1f)    return;

        var_a = (t3*N - t2*t4) / down;  // 得到参数 a
        var_b = (t1*t4 - t2*t3) / down;        // 得到参数 b
    }

    template<typename T>
    static std::vector<T> MediaBlur(const std::vector<T> &src, int ksize)
    {
        std::vector<T> dst(src.size());
        size_t H = src.size();
        for (int i = ksize / 2; i < H - ksize / 2; i++)
        {
            std::vector<T> tmp_windows(ksize);
            // 定义窗口 滑动滤波
            for (int j = 0; j < ksize; j++)
            {
                tmp_windows[j] = src[i - ksize / 2 + j];
            }
            //   Order elements (only half of them)
            for (int j = 0; j < ksize / 2 + 1; ++j)
            {
                //   Find position of minimum element
                int min = j;
                for (int k = j + 1; k < ksize; ++k)
                    if (tmp_windows[k] < tmp_windows[min])
                        min = k;
                //   Put found minimum element in its place
                int temp = tmp_windows[j];
                tmp_windows[j] = tmp_windows[min];
                tmp_windows[min] = temp;
            }
            dst[i] = tmp_windows[ksize / 2];
        }
        return dst;
    }

    template<typename T>
    static std::vector<T> MeanBlur(const std::vector<T> &src, int ksize)
    {
        std::vector<T> dst(src.size());
        size_t H = src.size();
        for (int i = ksize / 2; i < H - ksize / 2; i++)
        {
            float avg = 0.0f;
            for (int j = 0; j < ksize; j++)
            {
                avg += (float)src[i - ksize / 2 + j] / ksize;
            }

            dst[i] = avg;
        }

        for (int i = 0; i < ksize / 2; i++)
        {
            dst[i] = (float)src[i];
            dst[H - 1 - i] = (float)src[H - 1 - i];
        }
        return dst;
    }

    /**
    * @fn  float FastSin(float x);
    *
    * @brief   快速 sin 变换 拟合得到 减少运算
    *          https://www.cnblogs.com/sun11086/archive/2009/03/20/1417944.html
    *
    * @author  IRIS_Chen
    * @date    2019/6/15
    *
    * @param   x   The x coordinate
    *
    * @return  A float
    */
    static float FastSin(float x);

    /**
    * @fn  float FastCos(float x);
    *
    * @brief   快速 cos 变换
    *
    * @author  IRIS_Chen
    * @date    2019/6/15
    *
    * @param   x   The x coordinate
    *
    * @return  A float
    */
    static float FastCos(float x);



    /**
     * @fn  static int Utils_Data::Calc(uchar *dat, int len);
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
    static int Calc(uchar *dat, int len);
};

#endif // UTILS_DATA_H__