/**
 * @file    .
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   有关Qt的 通用组件
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#pragma once
// #include "utils.h"
#ifndef UTILS_QT_H__
#define UTILS_QT_H__

#include <QString>
#include <Qdir>
#include <QSerialPort>
#include <QSerialPortInfo>

/**
 * @class   Utils_QT utils_qt.h Code\utils\utils_qt.h
 *
 * @brief   The utilities qt.
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 */
class Utils_QT
{
    public:

    /**
     * @fn  static std::string Utils_QT::DirBack(const std::string & str);
     *
     * @brief   获取上一层级的文件夹 字符串
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   str The string
     *
     * @return  A std::string
     */
    static std::string DirBack(const std::string & str);

    /**
     * @fn  static bool Utils_QT::CheckDir(const std::string &path, bool create_ = true);
     *
     * @brief   判断文件夹是否存在如果存在  根据情况判断是否创建
     *
     * @author  IRIS_Chen
     * @date    2019/11/17
     *
     * @param   path    Full pathname of the file
     * @param   create_ (Optional) True to flg
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool CheckDir(const std::string &path, bool create_ = true);

    /**
     * @fn  static bool Utils_QT::CheckFile(const std::string &path, bool create_ = true);
     *
     * @brief   Query if 'file' is file exist 判断文件是否存在后 根据 flg 新建
     *
     * @author  IRIS_Chen
     * @date    2019/11/17
     *
     * @param   path    The file
     * @param   create_ (Optional) True to flg
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool CheckFile(const std::string &path, bool create_ = true);

    /**
     * @def Utils_QT::DEFAULT_DISK
     *
     * @brief   Gets disk occupy 获取磁盘占用 默认D盘
     *
     * @author  IRIS_Chen
     * @date    2019/11/17
     *
     * ### param    disk    (Optional) The disk
     * ### return   The disk occupy
     */
    #define DEFAULT_DISK "D"
    /**
     * @fn  static void Utils_QT::ListAllDisk(void);
     *
     * @brief   List all disk
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     */
    static void ListAllDisk(void);
    /**
     * @fn  static int Utils_QT::GetDiskOccupy(const std::string disk = DEFAULT_DISK);
     *
     * @brief   Gets disk occupy
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   disk    (Optional) The disk
     *
     * @return  The disk occupy
     */
    static int GetDiskOccupy(const std::string disk = DEFAULT_DISK);
    /**
     * @fn  static double Utils_QT::GetDiskAll(const std::string disk = DEFAULT_DISK);
     *
     * @brief   Gets disk all
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   disk    (Optional) The disk
     *
     * @return  The disk all
     */
    static double GetDiskAll(const std::string disk = DEFAULT_DISK);
    /**
     * @fn  static double Utils_QT::GetDiskFree(const std::string disk = DEFAULT_DISK);
     *
     * @brief   Gets disk free
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   disk    (Optional) The disk
     *
     * @return  The disk free
     */
    static double GetDiskFree(const std::string disk = DEFAULT_DISK);
    /**
     * @fn  static double Utils_QT::GetDiskUsed(const std::string disk = DEFAULT_DISK);
     *
     * @brief   Gets disk used
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   disk    (Optional) The disk
     *
     * @return  The disk used
     */
    static double GetDiskUsed(const std::string disk = DEFAULT_DISK);


    /**
     * @fn  static QByteArray Utils_QT::Str2QByteArray(const std::string &str, int flg_space = 1);
     *
     * @brief   将字符串 转换成 QByteArray 字符串默认有空格
     *          *        A B C --- 65 66 67 --- 41 42 43
     *          * *      字母      十进制        16进制
     *
     * @author  IRIS_Chen
     * @date    2019/11/2
     *
     * @param   str         The string.
     * @param   flg_space   (Optional) The flg space.
     *
     * @return  A QByteArray.
     */
    static QByteArray Str2QByteArray(const std::string &str, int flg_space = 1);


    /**
     * @fn  static bool Utils_QT::ReleaseThread(QThread *qthread);
     *
     * @brief   停止进程并同时 删除对象
     *
     * @author  IRIS_Chen
     * @date    2019/6/15
     *
     * @param [in,out]  qthread If non-null, the qthread
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ReleaseThread(QThread *qthread);

    /**
     * @fn  static bool Utils_QT::ShowImageOnLable(const cv::Mat &srcImg, QLabel *lb_label, int width, int height);
     *
     * @brief   在相应的label 上显示图片
     *
     * @author  IRIS_Chen
     * @date    2019/7/20
     *
     * @param           srcImg      Source image.
     * @param [in,out]  lb_label    If non-null, the pound label.
     * @param           width       The width.
     * @param           height      The height.
     *
     * @return  True if it succeeds, false if it fails.
     */
    static bool ShowImageOnLable(const cv::Mat &srcImg, QLabel *lb_label, int width, int height);

    /**
     * @fn  static void Utils_QT::RenderNumberOnLabel(QLabel *label, float num);
     *
     * @brief   实现信息格式化显示  默认 float 显示一位数据
     *
     * @author  IRIS_Chen
     * @date    2019/11/7
     *
     * @param [in,out]  label   If non-null, the label
     * @param           num     Number of
     */
    static void RenderNumberOnLabel(QLabel *label, float num);

    /**
     * @fn  static void Utils_QT::RenderNumberOnLabel(QLabel *label, int num);
     *
     * @brief   Renders the number on label
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param           num     
     */
    static void RenderNumberOnLabel(QLabel *label, int num);


    /**
     * @fn  QSerialPort Utils_QT::*GetSerialByPortNo(int port_no = -1);
     *
     * @brief   Gets serial by port no
     *
     * @author  IRIS_Chen
     * @date    2019/11/7
     *
     * @param   port_no (Optional) The port no
     *
     * @return  Null if it fails, else the serial by port no
     */
    static QSerialPort *GetSerialByPortNo(int port_no = -1);


    /**
     * @fn  static std::vector<std::string> Utils_QT::GetAllSerialPort();
     *
     * @brief   获取所有 的可用串口 COM5 的形式
     *
     * @author  IRIS_Chen
     * @date    2020/1/7
     *
     * @return  all port number
     */
    static std::vector<std::string> GetAllSerialPort();


    // QT UI 操作
    // 设置相关按钮不可用 如Label、QFrame、QSlider、QPushButton等
    template<typename T>
    static bool UI_ToggleEnable(T *btn)
    {
        if (btn == nullptr)
            return false;
        btn->setDisabled(btn->isEnabled());
        return true;
    }
    // 设置组件 切换显示状态
    template<typename T>
    static bool UI_ToggleVisible(T *btn)
    {
        if (btn == nullptr)
            return false;
        btn->setVisible(!btn->isVisible());
        return true;
    }


};

#endif  //UTILS_QT_H__