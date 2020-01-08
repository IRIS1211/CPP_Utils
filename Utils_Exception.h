/**********************************************************************************************//**
 * @file    include\Utils_Exception.h.
 *
 * @brief   声明自己处理过程中遇到的异常, 在遇到异常的时候直接返回处异常位置, 便于后续处理
 * @changelog   2018/11/28    SChen Created.
 *************************************************************************************************/
#pragma once
#include <string>
// #include "utils_logger.h"
/**
 * @enum    ErrorCode
 *
 * @brief   定义错误代码 表示不同功能, 从小到达依次定义
 *          可以参考错误代码表    
        1. 配置文件
        2. 相机硬件部分
        3. 图像处理部分
        4. 串口及其他硬件部分
        5. 文件系统操作错误部分
        6. 视频流读写部分
        7. 界面显示及操作部分
        8. 其他部分
        9. 保留
        0. 调试部分异常
 */



enum ErrorCode
{
    // ConfigError = 101,

    Error_YML_FileNotExist = 1000,     // yml 文件不存在
    Error_YML_FileNode_NoExist      = 1001,     // 文件节点不存在 runpara

    Error_IDOI_FileNotExist         =   5000,   //  自定义文件不存在
    Error_IDOI_FileWritePointerNull =   5001,   //    写入文件指针为空
    Error_IDOI_FileVerifyError      =   5002,   // 读取文件头校验失败
    Error_IDOI_File_Write = 5003,    // IDOI 写文件指针错误

    Error_Image_Resize_Crash =  3001,   // 图片缩放错误
    Error_Image_Resize_Crash_OnLabel = 3002,  // 在显示过程中的缩放出错

    Error_Serial_Timeout_Over_Set_Time = 4002,  // 串口超时无数据
    Error_Serial_Compass_TypeError = 4003,      // 串口处理 罗盘类型错误 未记录
    Error_Serial_PortName_Invalid = 4004,       // 串口端口 无效

    Error_Project_Dir_Create_Error = 5000,     // 工作路径文件夹创建错误
    Error_Work_Dir_Pic_Create_Error = 5001,     // 工作路径下图片文件夹创建错误
    Error_Work_Dir_Video_Create_Error = 5002,     // 工作路径下视频文件夹创建错误

    Error_Video_Writer_Null = 6001,     // 视频流指针为空

};

/**********************************************************************************************//**
 * @class   Utils_Exception Utils_Exception.h include\Utils_Exception.h
 *
 * @brief   直接从 异常基类继承 , 可以考虑分别使用不同的基类继承出来不同的类
 *
 * @author  SChen
 * @date    2018/11/28
 *************************************************************************************************/

/**
 * @class   Utils_Exception myException.h Code\inc\myException.h
 *
 * @brief   Exception for signalling my errors.
 *
 * @author  IRIS_Chen
 * @date    2019/11/7
 */

class Utils_Exception : public std::exception
{
    public:

    // 错误信息返回
    int mi_ErrorCode_; ///< 错误代码
    std::string ms_ErrorMsg_;  ///< 错误消息

    /**
     * @fn  Utils_Exception::Utils_Exception(int num = 100, std::string str = "Unknown exception")
     *
     * @brief   初始对象生成 默认会出现  位置错误 对于错误异常 直接处理结果
     *
     * @author  IRIS_Chen
     * @date    2019/11/7
     *
     * @param   num (Optional) Number of
     * @param   str (Optional) The string
     */
    Utils_Exception(int num = 100, std::string str = "Unknown exception")
    {
        // LOG(INFO) << "错误代码:" << err_num << ":" << err_str;
        mi_ErrorCode_ = num;
        ms_ErrorMsg_ = str;
        // log出异常
        LError("Exception occur:\t Code:{}\tMess:{}", mi_ErrorCode_, ms_ErrorMsg_);
    }
};
