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
#ifndef UTILS_FILES_H_
#define UTILS_FILES_H_

#include <vector>
#include <string>
#include <iostream>

/**
 * @class   Utils_Files utils_files.h Code\utils\utils_files.h
 *
 * @brief   The utilities files.
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 */
class Utils_Files
{
	public:
    /**
     * @fn  static std::vector<std::string> Utils_Files::ListAllFiles(const std::string &file_path);
     *
     * @brief   给出路径 , 列出路径下面的所有文件, 如果路径为空,或者无内容 则返回 空
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   file_path   Full pathname of the file
     *
     * @return  A std::vector&lt;std::string&gt;
     */
    static std::vector<std::string> ListAllFiles(const std::string &file_path);
    /**
     * @fn  static void Utils_Files::ListAllFiles(const std::string &file_path, std::vector<std::string> &filelist);
     *
     * @brief   List all files
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param           file_path   Full pathname of the file
     * @param [in,out]  filelist    The filelist
     */
    static void ListAllFiles(const std::string &file_path, std::vector<std::string> &filelist);

    /**
     * @fn  static std::string Utils_Files::GetFileName(const std::string &file);
     *
     * @brief   从路径中 剥离出来文件名
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   file    The file
     *
     * @return  The file name
     */
    static std::string GetFileName(const std::string &file);



    /**
     * @fn  static bool Utils_Files::SplitFileName(std::string &file_name, std::string &file_path, const std::string &filename);
     *
     * @brief   将文件路径拆分为 文件路径和文件名称 删除拓展名
     *
     * @author  IRIS_Chen
     * @date    2019/10/25
     *
     * @param [in,out]  file_name   Filename of the file.
     * @param [in,out]  file_path   Full pathname of the file.
     * @param           filename    Filename of the file.
     *
     * @return  True if it succeeds, false if it fails.
     */
    static bool SplitFileName(std::string &file_name, std::string &file_path, const std::string &filename);

    /**
     * @fn  static bool Utils_Files::IsDirExist(const std::string & path, bool create_ = true);
     *
     * @brief   判断文件夹是否存在, 如果不存在 则新建 文件夹 // 不确定能否递归建立
     *
     * @author  IRIS_Chen
     * @date    2019/10/29
     *
     * @param   path    Full pathname of the file.
     * @param   create_ (Optional) True to create.
     *
     * @return  True if dir exist, false if not.
     */
    static bool IsDirExist(const std::string & path, bool create_ = true);

    /**
     * @fn  static bool Utils_Files::IsFileExist(const std::string & file, bool create_ = false);
     *
     * @brief   判断指定的文件是否存在 // 给定flg 如果不存在则建立文件
     *
     * @author  IRIS_Chen
     * @date    2019/10/29
     *
     * @param   file    The file.
     * @param   create_ (Optional) True to creat.
     *
     * @return  True if file exist, false if not.
     */
    static bool IsFileExist(const std::string & file, bool create_ = false);

    /**
     * @fn  std::vector<std::string> Utils_Files::LowwerString(const std::string &src_filelist);
     *
     * @brief   将输入的字符串全部变成小写
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   src_filelist    Source filelist
     *
     * @return  A std::vector&lt;std::string&gt;
     */
    std::vector<std::string> LowwerString(const std::string &src_filelist);

    /**
     * @fn  bool Utils_Files::RenameFileList(const std::string &src_filelist, const std::string &dst_filelist);
     *
     * @brief   将文件列表的所有文件名对应重命名
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   src_filelist    Source filelist
     * @param   dst_filelist    Destination filelist
     *
     * @return  True if it succeeds, false if it fails
     */
    bool RenameFileList(const std::string &src_filelist, const std::string &dst_filelist);

    /**
     * @fn  template<typename T> static bool Utils_Files::WriteData(std::fstream *pfile, T &num)
     *
     * @brief   Writes a data  写入基本数据类型
     *
     * @author  IRIS_Chen
     * @date    2019/11/29
     *
     * @tparam  T   Generic type parameter.
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  num     Number of
     *
     * @return  True if it succeeds, false if it fails
     */
    template<typename T>
    /**
     * @fn  static bool Utils_Files::WriteData(std::fstream *pfile, T &num)
     *
     * @brief   Writes a data
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  num     Number of
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool WriteData(std::fstream *pfile, T &num)
    {
        pfile->write((char*)&num, sizeof(T));
        return true;
    }

    /**
     * @fn  template<typename T> static bool Utils_Files::ReadData(std::fstream *pfile, T &num)
     *
     * @brief   读取基本数据类型
     *
     * @author  IRIS_Chen
     * @date    2019/11/29
     *
     * @tparam  T   Generic type parameter.
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  num     Number of
     *
     * @return  True if it succeeds, false if it fails
     */
    template<typename T>
    /**
     * @fn  static bool Utils_Files::ReadData(std::fstream *pfile, T &num)
     *
     * @brief   Reads a data
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  num     Number of
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ReadData(std::fstream *pfile, T &num)
    {
        pfile->read((char*)&num, sizeof(T));
        return true;
    }


    /**
     * @fn  static bool Utils_Files::WriteStringBinary(std::fstream *pfile, const std::string &str, int len);
     *
     * @brief   在二进制流中写入一段 字符串
     *
     * @author  IRIS_Chen
     * @date    2019/12/16
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param           str     The string
     * @param           len     The length
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool WriteStringBinary(std::fstream *pfile, const std::string &str, int len);

    /**
     * @fn  static bool Utils_Files::ReadStringBinary(std::fstream *pfile, std::string &str, int len);
     *
     * @brief   从二进制流 读取字符串
     *
     * @author  IRIS_Chen
     * @date    2019/12/16
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  str     The string
     * @param           len     The length
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ReadStringBinary(std::fstream *pfile, std::string &str, int len);

    /**
     * @fn  static bool Utils_Files::WriteStringTxt(std::fstream *pfile, const std::string &str);
     *
     * @brief   将文件写入txt 文档中 每次写入一行
     *
     * @author  IRIS_Chen
     * @date    2019/12/16
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param           str     The string
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool WriteStringTxt(std::fstream *pfile, const std::string &str);

    /**
     * @fn  static bool Utils_Files::ReadStringTxt(std::fstream *pfile, std::string &str);
     *
     * @brief   每次读取一行  放入字符串中
     *
     * @author  IRIS_Chen
     * @date    2019/12/16
     *
     * @param [in,out]  pfile   If non-null, the pfile
     * @param [in,out]  str     The string
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool ReadStringTxt(std::fstream *pfile, std::string &str);

};



#endif  // UTILS_FILES_H_

