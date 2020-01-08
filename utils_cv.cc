/**
 * @file    Code\utils\utils.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities class 通用组件的实现
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#include <map>

#include "./utils_cv.h"
#include "./utils.h"


#include "opencv2/core.hpp"


/**
 * @fn  cv::Rect Utils_CV::Str2Rect(const std::string &str, const std::string delim )
 *
 * @brief   将字符串按照分割字符分割之后 生成矩形
 *
 * @author  IRIS_Chen
 * @date    2019/11/26
 *
 * @param   str     The string
 * @param   delim   The delimiter
 *
 * @return  A cv::Rect
 */
cv::Rect Utils_CV::Str2Rect(const std::string &str, const std::string delim /*= ", "*/)
{
    // 分割字符串
    std::vector<std::string> tmp_str;

    Utils_String::Str2Vec(str, tmp_str, ',', true);
    
    cv::Rect r;

    // 依次 转换成数字
    std::vector<int> tmp_int;
    for (const auto& s : tmp_str)
        tmp_int.push_back(std::stoi(s));

    assert(4 == tmp_int.size());
    // 创建 cv Rect 区域
    r = cv::Rect(tmp_int[0], 
                 tmp_int[1], 
                 tmp_int[2], 
                 tmp_int[3]);
    return r;
}

/**
* @fn  static bool Utils_CV::ImageSplit(const cv::Mat &src_img, const std::vector<int> &lines, std::vector<cv::Mat> &splitImgVec, bool horizon = true, const int wealth = 5);
*
* @brief   将一副图片按照给出的线划分 成为 几列图像  
*          给出一定的裕量 相应的图片会比较大 // 默认横向分割
*
* @author  IRIS_Chen
* @date    2019/12/6
*
* @param           src_img     Source image
* @param           lines       The lines
* @param [in,out]  splitImgVec The split image vector
* @param           horizon     (Optional) True to horizon 横向分割为 几列图像
* @param           wealth      (Optional) 每次分割的裕量 多切割出来的部分
*
* @return  True if it succeeds, false if it fails
*/
bool Utils_CV::ImageSplit(const cv::Mat &src_img, const std::vector<int> &lines, std::vector<cv::Mat> &splitImgVec, bool horizon /*= true*/, const int wealth /*= 5*/)
{
    if (!splitImgVec.empty())
        return false;

    // 根据边线分割 // 在原有边线上增加 两个量 便于后续执行循环切割
    int left_px = wealth, right_px = src_img.cols - wealth - 1;

    cv::Rect rect;
    std::vector<int> new_lines;
    new_lines.push_back(left_px);
    
    // 如果小于过于左侧的分割或者右侧的分割线, 得到的结果可能导致异常
    for (int l : lines)
    {
        // 最好避免出现这种情况 可以报错
        if (l < left_px)    l = left_px;
        if (l > right_px)   l = right_px;
            
        new_lines.push_back(l);
    }

    new_lines.push_back(right_px+1);

    // 循环处理区域切割  // 左右均留出裕量
    cv::Mat tmp_img;
    try
    {
        for (int i = 1; i < new_lines.size(); i++)
        {
            // 根据 方向 区分是竖直切割 还是 水平切割
            if (horizon)
            {
                rect = cv::Rect(new_lines[i - 1] - wealth,
                                0,
                                new_lines[i] - new_lines[i - 1] + wealth * 2,
                                src_img.rows);
            }
            else
            {
                rect = cv::Rect(0,
                                new_lines[i - 1] - wealth,
                                src_img.cols,
                                new_lines[i] - new_lines[i - 1] + wealth * 2);
            }
            tmp_img = src_img(rect);
            splitImgVec.emplace_back(tmp_img);
        }
    }
    catch (...)
    {
        LError("Rect Image Error");
        return false;
    }

    return true;
}

/**
* @fn  static bool Utils_CV::ImageMerge(cv::Mat &dst_img, const std::vector<cv::Mat> &splitImgVec, const vector<int> &lines, bool horizon = true, const int wealth = 5);
*
* @brief   将给出的图片数组 根据给出的分割线 和 裕量 合并成一副 图像
*
* @author  IRIS_Chen
* @date    2019/12/7
*
* @param [in,out]  dst_img     Destination image
* @param           splitImgVec The split image vector
* @param           lines       The lines
* @param           horizon     (Optional) True to horizon
* @param           wealth      (Optional) The wealth
*
* @return  True if it succeeds, false if it fails
*/
bool Utils_CV::ImageMerge(cv::Mat & dst_img, \
                          const std::vector<cv::Mat>& splitImgVec, \
                          const std::vector<int>& lines, \
                          bool horizon, \
                          const int wealth)
{
    UNREFERENCED_PARAMETER(lines);
    return ImageMerge(dst_img, splitImgVec, horizon, wealth);
}

/**
* @fn  static bool Utils_CV::ImageMerge(cv::Mat &dst_img, const std::vector<cv::Mat> &splitImgVec, bool horizon = true, const int wealth = 5);
*
* @brief   将给出的图片数组 根裕量 合并成一副 图像
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
bool Utils_CV::ImageMerge(cv::Mat & dst_img, \
                          const std::vector<cv::Mat>& splitImgVec, \
                          bool horizon, \
                          const int wealth)
{
    if (splitImgVec.empty())
        return false;
    
    // 创建大图 用于处理图像
    cv::Mat finalImg;

    
    // 赋值有一个裕量出来 然后循环处理, 最后将最后的裕量添加上
    cv::Rect rect_src,rect_dst;
    if (horizon)
    {
        // 获取最终图像的宽度或者高度
        int sum_ = 0;
        for (const auto &img : splitImgVec)
            sum_ += img.cols - 2 * wealth;
        sum_ += 2 * wealth;
        finalImg = cv::Mat::zeros(sum_, splitImgVec[0].rows, splitImgVec[0].type());

        // 由于每个区域边界的不可脱离, 智能按照严格的标准处理拼接
        rect_src = cv::Rect(0, 0, wealth, splitImgVec[0].rows);
        rect_dst = cv::Rect(0, 0, wealth, splitImgVec[0].rows);
        splitImgVec[0](rect_src).copyTo(finalImg(rect_dst));

        int start_cols = wealth;
        for (const auto & img : splitImgVec)
        {
            rect_src = cv::Rect(wealth, 0, img.cols - 2 * wealth, img.rows);
            rect_dst = cv::Rect(start_cols, 0, img.cols - 2 * wealth, img.rows);
            img(rect_src).copyTo(finalImg(rect_dst));
            start_cols += rect_src.size ().width;      // 记录上一次拼接之后的位置
        }

        // 最后的裕量拼接
        const cv::Mat &img = splitImgVec.back();
        rect_src = cv::Rect(img.cols-wealth,0,wealth,img.rows);
        rect_dst = cv::Rect(start_cols, 0, wealth, img.rows);

        img(rect_src).copyTo(finalImg(rect_dst));
    }
    else
    {
        // 获取最终图像的宽度或者高度
        int sum_ = 0;
        for (const auto &img : splitImgVec)
            sum_ += img.rows - 2 * wealth;
        sum_ += 2 * wealth;
        finalImg = cv::Mat::zeros(splitImgVec[0].cols,sum_, splitImgVec[0].channels());

        // 由于每个区域边界的不可脱离, 智能按照严格的标准处理拼接
        rect_src = cv::Rect(0, 0, splitImgVec[0].cols, wealth);
        rect_dst = cv::Rect(0, 0, splitImgVec[0].cols, wealth);
        splitImgVec[0](rect_src).copyTo(finalImg(rect_dst));

        int start_rows = wealth;
        for (const auto & img : splitImgVec)
        {
            rect_src = cv::Rect(0, wealth,img.cols, img.rows - 2 * wealth);
            rect_dst = cv::Rect(0,start_rows, img.cols, img.rows - 2 * wealth);
            img(rect_src).copyTo(finalImg(rect_dst));
            start_rows += rect_src.size().height;      // 记录上一次拼接之后的位置
        }

        // 最后的裕量拼接
        const cv::Mat &img = splitImgVec.back();
        rect_src = cv::Rect(0, img.rows - wealth, img.cols,wealth);
        rect_dst = cv::Rect(0,start_rows, img.cols, wealth);

        img(rect_src).copyTo(finalImg(rect_dst));
    }

    dst_img = finalImg;
    return true;
}

/**
 * @fn  cv::Rect Utils_CV::GetSquareRect(const cv::Mat &img)
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
cv::Rect Utils_CV::GetSquareRect(const cv::Mat &img)
{
    int len = std::min(img.cols, img.rows);
    int LT_x = (img.cols - len) / 2;
    int LT_y = (img.rows - len) / 2;

    // 保证图像为原始图像中间区域的一个方形 同时保证区域不会超出设定边界
    cv::Rect r = cv::Rect(LT_x, LT_y, len, len);

    return r;
}

/**
 * @fn  cv::Rect Utils_CV::GetRect(const cv::Mat &img)
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
cv::Rect Utils_CV::GetRect(const cv::Mat &img)
{
    return cv::Rect(0,
                    0,
                    img.cols,
                    img.rows);
}

/**
 * @fn  cv::Rect Utils_CV::GetCenterRect(const cv::Rect img_r, int width , int height )
 *
 * @brief   获取图像中心区域 的值
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param   img_r   原始图像
 * @param   width   宽度
 * @param   height  高度
 *
 * @return  The cen rectangle
 */
cv::Rect Utils_CV::GetCenterRect(const cv::Rect img_r, int width /*= -1*/, int height /*= -1*/)
{
    // 如果 没给或者 只给了宽度
    if (height == -1)
    {
        // 计算一个 图像的 边的最小值
        int tmp_w = std::min(img_r.width, img_r.height);
        width = tmp_w;
        height = tmp_w;
    }
    // 否则 按照设定的尺寸获取即可

    // 返回计算出来的居中值 和原始图像的交集 避免出现 溢出
    return cv::Rect((img_r.width - width) / 2,
                    (img_r.height - height) / 2,
                    width,
                    height) & img_r;
}

/**
 * @fn  cv::Rect Utils_CV::MarginRect(const cv::Rect &cur_r, int t , int l , int b , int r )
 *
 * @brief   矩形外扩一定范围
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param   cur_r   The current r
 * @param   t       向上 
 * @param   l       向左
 * @param   b       向下
 * @param   r       向右
 *
 * @return  A cv::Rect
 */
cv::Rect Utils_CV::MarginRect(const cv::Rect &cur_r, int t /*= 5*/, int l /*= -1*/, int b /*= -1*/, int r /*= -1*/)
{
    // 根据值判断相应的值
    // 一个参数  四周一致 
    // 二个参数 上下 左右
    if (l == -1) // 只给了一个参数
    {
        l = t;
        b = t;
        r = l;
    }
    else if (b == -1)
    {
        // 给了两个参数
        b = t;
        r = l;
    }
    else if (r == -1)
    {
        // 给了三个参数
        r = l;
    }
    //其他 给了四个参数

    // 返回外扩矩形
    return cv::Rect(cur_r.tl().x - l,
                    cur_r.tl().y - t,
                    cur_r.width + l + r,
                    cur_r.height + t + b) | cur_r;
}

/**
 * @fn  cv::Rect Utils_CV::GetOffsetRect(const cv::Rect &cur_r, const cv::Point &offset)
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
cv::Rect Utils_CV::GetOffsetRect(const cv::Rect &cur_r, const cv::Point &offset)
{
    return MarginRect(cur_r - offset) | cur_r;
}

/**
 * @fn  void Utils_CV::CreatMapMat(cv::Mat & map_x, cv::Mat & map_y, int cen_x, int cen_y, int min_r, int max_r, int Width , int Height )
 *
 * @brief   为 展开图像创建 map  后续执行起来很快 展开思路 参考
 *          https://blog.csdn.net/guduruyu/article/details/65436931 见附件 pdf 公式推导 展开图像角度 从标准座标系
 *          270开始的 顺时针展开
 *          #TODO(SChen): 解决缩放 插值的问题
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
 * @param           Width   The width.
 * @param           Height  The height.
 */
void Utils_CV::CreatMapMat(cv::Mat & map_x,
                cv::Mat & map_y,
                int cen_x,
                int cen_y,
                int min_r,
                int max_r,
                int Width /*= -1 */,
                int Height /*= -1 */)
{
    //  避免赋值出错 进行数值交换
    if (min_r > max_r)
    {
        LDebug("MinR:{0} is larger than MaxR:{1}", min_r, max_r);
        std::swap(min_r, max_r);  //交换一下
    }

    // 需要判断是否 超过范围 避免 溢出值
    // 求算出来 中心点到四个边缘 的最小值, 
    int maxR_h = std::min(std::min(cen_x, cen_y),
                        std::min(gConfig->mRunPara.Image.Polar.nImgWidth - cen_x,
                                gConfig->mRunPara.Image.Polar.nImgHeight - cen_y));
    // 计算出来 设定值与给出值的最小值
    max_r = std::min(max_r, maxR_h);

    //  避免赋值出错 进行数值交换
    if (min_r > max_r)
    {
        LDebug("MinR:{0} is larger than MaxR:{1}", min_r, max_r);
        std::swap(min_r, max_r);  //交换一下
    }

    // 对于 圆形的图像 按照给出的直径范围  生成对应的值的映射, 相应位置的值 为对应的座标 值

    // 按照给出的 展开圆的区域 生成空的数组
    // 如果给出的尺寸是默认尺寸  -1  则使用 中间圆周长和 内外圆差值做宽高
    int map_width = 0, map_height = 0;
    // 如果 参数未赋值 使用默认方法 赋值
    map_width = ((-1 == Width) ? ((int)(max_r + min_r)*CV_PI) : Width);
    map_height = ((-1 == Height) ? (max_r - min_r) : Height);

    // 创建空的尺寸图 用于存放变换座标序列 默认使用 32F值
    map_x = cv::Mat::zeros(map_height, map_width, CV_32FC1);
    map_y = cv::Mat::zeros(map_height, map_width, CV_32FC1);

    // 计算两个尺寸的缩放因子
    float delta_r = 1.0;  // (float)(map_height)/(max_r - min_r); // 此值 需要进行计算 单纵向没有拉伸, 可以不进行处理
    float delta_theta = -2.0f * static_cast<float>(CV_PI / map_width);

    // 填充两个 图的座标值
    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {
            // 计算出来 对应的C 图上的座标值
            float xc = cen_x + delta_r*(min_r + map_height - y)*Utils_Data::FastSin(delta_theta*x);
            float yc = cen_y + delta_r*(min_r + map_height - y)*Utils_Data::FastCos(delta_theta*x);
            map_x.at<float>(y, x) = xc;
            map_y.at<float>(y, x) = yc;
        }
    }

}


/**
 * @fn  QImage Utils_CV::CvMat2QImage(const cv::Mat * mat)
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
QImage Utils_CV::CvMat2QImage(const cv::Mat * mat)
{
    // 图像的通道 一定是给定的值

    assert(mat->type() == 1 || mat->type() == 3 || mat->type() == 4);
    // 设立一个表 直接查询 其中 0 2 是无效值 1 3 4 对应的转换值
    const std::map<int, QImage::Format> img_cvt_map {
        { 1, QImage::Format_Grayscale8 },
        { 3, QImage::Format_RGB888 },
        { 4, QImage::Format_ARGB32 }
    };

    if (mat == nullptr || !img_cvt_map.count(mat->type()))
    {
        LError("Mat type is not in table , cannot convert  :{}", mat->type());
        return QImage();
    }


    return QImage(mat->data, \
                 mat->cols, \
                 mat->rows, \
                 static_cast<int>(mat->step), \
                 img_cvt_map.at(mat->type()));

}

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
cv::Mat Utils_CV::QImage2CvMat(const QImage * image)
{
    cv::Mat mat;
    const std::map<QImage::Format, int> img_cvt_map{
        { QImage::Format_Grayscale8, 1 },
        { QImage::Format_RGB888, 3 },
        { QImage::Format_ARGB32, 4}
    };

    if (image == nullptr || !img_cvt_map.count(image->format()))
    {
        LError("image format is not in table , cannot convert :{}", image->format());
        return cv::Mat();
    }

    return cv::Mat(image->height(), \
                  image->width(), \
                  img_cvt_map.at(image->format()));
}
