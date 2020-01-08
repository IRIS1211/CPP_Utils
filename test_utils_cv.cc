#include "./utils_cv.h"

TEST_CASE("Test Image Split And Merge")
{
#if 0

    // 创建 空白图像
    cv::Mat src_img = cv::Mat::zeros(1000, 1000, CV_8UC3);

    // 绘制 相应的线 便于查看 是否正确拼接
    cv::putText(src_img,
                "1234567890",
                cv::Point(0, 800),
                cv::FONT_HERSHEY_COMPLEX,
                5,
                cv::Scalar(0, 255, 0),
                3);

    cv::line(src_img,
             cv::Point(0, 0),
             cv::Point(1000, 1000),
             cv::Scalar(255, 0, 0),
             3);

    cv::circle(src_img,
               cv::Point(500, 500),
               480,
               cv::Scalar(0, 0, 255),
               3);

    std::vector<int> line_ = { 100, 300, 500, 800, 900 };


    std::vector<cv::Mat> splitVector;
    int wealth = 5;     // 裕量

    Utils_CV::ImageSplit(src_img, line_, splitVector, true, wealth);

    CHECK(splitVector.size() == (line_.size() + 1));
    CHECK(splitVector[0].cols == (line_[0] + wealth));
    // CHECK(splitVector[1].cols == (line_[1] + 2*wealth));

    cv::Mat dst_img;
    Utils_CV::ImageMerge(dst_img, splitVector, true, wealth);

    CHECK(dst_img.cols == src_img.cols);

    Utils_CV::ImageSplit(src_img, line_, splitVector, false, wealth);
    cv::Mat dst_img_v;
    Utils_CV::ImageMerge(dst_img_v, splitVector, true, wealth);

    CHECK(dst_img_v.rows == src_img.rows);
#endif
}


