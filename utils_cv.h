/**
 * @file    .
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   有关opencv 的相关函数组件
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#pragma once
// #include "utils.h"
#ifndef UTILS_CV_H__
#define UTILS_CV_H__
#include <QImage>
#include <vector>
#include "opencv2/core.hpp"

class Utils_CV 
{
    public:

    /**
     * @fn  static cv::Rect Str2Rect(const std::string &str, const std::string delim = ", ");
     *
     * @brief   将字符串按照分割字符分割之后 生成矩形
     *
     * @author  IRIS_Chen
     * @date    2019/11/26
     *
     * @param   str     The string
     * @param   delim   (Optional) The delimiter
     *
     * @return  A cv::Rect
     */
    static cv::Rect Str2Rect(const std::string &str, const std::string delim = ",| ");
     

    /**
     * @fn  static bool Utils_CV::ImageSplit(const cv::Mat &src_img, const std::vector<int> &lines, std::vector<cv::Mat> &splitImgVec, bool horizon = true, const int wealth = 5);
     *
     * @brief   将一副图片按照给出的线划分 成为 几列图像  // 给出一定的裕量 相应的图片会比较大 // 默认横向分割
     *
     * @author  IRIS_Chen
     * @date    2019/12/6
     *
     * @param           src_img     Source image
     * @param           lines       The lines
     * @param [in,out]  splitImgVec The split image vector
     * @param           horizon     (Optional) True to horizon
     * @param           wealth      (Optional) The wealth
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ImageSplit(const cv::Mat &src_img,
                           const std::vector<int> &lines,
                           std::vector<cv::Mat> &splitImgVec,
                           bool horizon = true,
                           const int wealth = 5);

    /**
     * @fn  static bool Utils_CV::ImageMerge(cv::Mat &dst_img, const std::vector<cv::Mat> &splitImgVec, const vector<int> &lines, bool horizon = true, const int wealth = 5);
     *
     * @brief   将给出的图片数组 根据给出的分割线 和 裕量 合并成一副 图像
     *
     * @author  IRIS_Chen
     * @date    2019/12/7
     *
     * @param [in,out]  dst_img     目标生成的目录
     * @param           splitImgVec 分割开的图像
     * @param           lines       分割线     // 可以不给出
     * @param           horizon     (Optional) 水平分割
     * @param           wealth      (Optional) 分割 裕量
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ImageMerge(cv::Mat &dst_img,
                           const std::vector<cv::Mat> &splitImgVec,
                           const std::vector<int> &lines,
                           bool horizon = true,
                           const int wealth = 5);
    /**
     * @fn  static bool Utils_CV::ImageMerge(cv::Mat &dst_img, const std::vector<cv::Mat> &splitImgVec, bool horizon = true, const int wealth = 5);
     *
     * @brief   将给出的图片数组 根据给出的分割线 和 裕量 合并成一副 图像
     *
     * @author  IRIS_Chen
     * @date    2019/12/7
     *
     * @param [in,out]  dst_img     目标生成的目录
     * @param           splitImgVec 分割开的图像
     * @param           horizon     (Optional) 水平分割
     * @param           wealth      (Optional) 分割 裕量
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ImageMerge(cv::Mat &dst_img,
                           const std::vector<cv::Mat> &splitImgVec,
                           bool horizon = true,
                           const int wealth = 5);
    
    /**
     * @fn  static cv::Rect Utils_CV::GetSquareRect(const cv::Mat &img);
     *
     * @brief   根据 图像尺寸 生成  一个包含中间区域的 矩形框
     *
     * @author  IRIS_Chen
     * @date    2019/11/5
     *
     * @param   img The image
     *
     * @return  The sqr rectangle
     */
    static cv::Rect GetSquareRect(const cv::Mat &img);

    /**
     * @fn  static cv::Rect Utils_CV::GetRect(const cv::Mat &img);
     *
     * @brief   返回图像的矩形区域
     *
     * @author  IRIS_Chen
     * @date    2019/11/5
     *
     * @param   img The image
     *
     * @return  The image rectangle
     */
    static cv::Rect GetRect(const cv::Mat &img);

    /**
     * @fn  static cv::Rect Utils_CV::GetCenterRect(const cv::Rect img_r, int width = -1, int height = -1);
     *
     * @brief   获取图像中心区域 的值
     *
     * @author  IRIS_Chen
     * @date    2019/11/5
     *
     * @param   img_r   The image r
     * @param   width   (Optional) The width
     * @param   height  (Optional) The height
     *
     * @return  The cen rectangle
     */
    static cv::Rect GetCenterRect(const cv::Rect img_r, int width = -1, int height = -1);
    
    /**
     * @fn  static cv::Rect Utils_CV::MarginRect(const cv::Rect &cur_r, int t = 5, int l = -1, int b = -1, int r = -1);
     *
     * @brief   矩形外扩一定范围
     *
     * @author  IRIS_Chen
     * @date    2019/11/5
     *
     * @param   cur_r   The current r
     * @param   t       (Optional) An int to process
     * @param   l       (Optional) An int to process
     * @param   b       (Optional) An int to process
     * @param   r       (Optional) An int to process
     *
     * @return  A cv::Rect
     */
    static cv::Rect MarginRect(const cv::Rect &cur_r, int t = 5, int l = -1, int b = -1, int r = -1);

    /**
     * @fn  static cv::Rect Utils_CV::GetOffsetRect(const cv::Rect &cur_r, const cv::Point &offset);
     *
     * @brief   根据当前区域相对于上次区域的偏移值定位出来 上次矩形框的外扩范围
     *
     * @author  IRIS_Chen
     * @date    2019/7/16
     *
     * @param   cur_r   The current r
     * @param   offset  The offset
     *
     * @return  The offset rectangle
     */
    static cv::Rect GetOffsetRect(const cv::Rect &cur_r, const cv::Point &offset);


    /**
     * @fn  void Utils_CV::CreatMapMat(cv::Mat & map_x, cv::Mat & map_y, int cen_x, int cen_y, int min_r, int max_r, int Width = -1, int Height = -1);
     *
     * @brief   创建 映射map 图像
     *
     * @author  IRIS_Chen
     * @date    2019/7/20
     *
     * @param [in,out]  map_x   The map x coordinate.
     * @param [in,out]  map_y   The map y coordinate.
     * @param           cen_x   The cen x coordinate.
     * @param           cen_y   The cen y coordinate.
     * @param           min_r   The minimum r.
     * @param           max_r   The maximum r.
     * @param           Width   (Optional) The width.
     * @param           Height  (Optional) The height.
     */
    static void CreatMapMat(cv::Mat & map_x, \
                            cv::Mat & map_y, \
                            int cen_x, \
                            int cen_y, \
                            int min_r, \
                            int max_r, \
                            int Width = -1, \
                            int Height = -1);

    // #TEST(SChen) 完成图像 格式相互转换 test 
    
    /**
     * @fn  static QImage Utils_CV::CvMat2QImage(const cv::Mat * mat);
     *
     * @brief   将opencv mat 转换成 QT image
     *
     * @author  IRIS_Chen
     * @date    2019/12/19
     *
     * @param   mat The matrix
     *
     * @return  A QImage
     */
    static QImage CvMat2QImage(const cv::Mat * mat);


    /**
     * @fn  static cv::Mat Utils_CV::QImage2CvMat(const QImage *image);
     *
     * @brief   QT Image 转换成 cv Mat 结构
     *
     * @author  IRIS_Chen
     * @date    2019/12/19
     *
     * @param   image   The image
     *
     * @return  A cv::Mat
     */
    static cv::Mat QImage2CvMat(const QImage *image);

};

#endif  //UTILS_CV_H__