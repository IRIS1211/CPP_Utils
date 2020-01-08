/**
 * @file    Code\utils\utils_files.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities files class
 * @changelog   2019/12/27    IRIS_Chen Created.
 */

#include "./utils_string.h"
#include "./utils_files.h"

#include  <io.h>
#include <string.h>
#include <direct.h>

/**
 * @fn  bool Utils_Files::WriteStringBinary(std::fstream * pfile, const std::string & str, int len)
 *
 * @brief    将一个字符串写入到二进制文件流中
 *
 * @author  IRIS_Chen
 * @date    2019/11/29
 *
 * @param [in,out]  pfile   If non-null, the pfile
 * @param           str     The string
 * @param           len     The length
 *
 * @return  True if it succeeds, false if it fails
 */

std::vector<std::string> Utils_Files::ListAllFiles(const std::string & file_path)
{
    std::vector<std::string> res;
    ListAllFiles(file_path, res);
    return res;
}

// 递归列出文件
void Utils_Files::ListAllFiles(const std::string &file_path, std::vector<std::string> &filelist)
{
    // 在目录后面加上"\\*.*"进行第一次搜索
    std::string file_path_new = file_path + "\\*.*";
    intptr_t handle;
    _finddata_t findData;
    handle = _findfirst(file_path_new.c_str (), &findData);
    if (handle == -1)        // 检查是否成功
    {
        return ;
    }
    do
    {
        // 如果是 目录 则递归 否则不处理
        if (findData.attrib & _A_SUBDIR)
        {
            // 如果找到的是 当前目录 .  或者上层目录 ..  继续
            if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
            {
                continue;
            }
            // 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
            file_path_new = file_path + "\\" + std::string(findData.name);
            ListAllFiles(file_path_new, filelist);
        }
        else
        {
            file_path_new = file_path + "\\" + std::string(findData.name);
            filelist.push_back(file_path_new);
        }
    }
    while (_findnext(handle, &findData) == 0);
    _findclose(handle);  // 关闭搜索句柄
}

// 从 字符路径中 获取文件名
std::string Utils_Files::GetFileName(const std::string & file)
{
    size_t pos_backlash = file.find_last_of('\\');
    size_t pos_dot = file.find_last_of('.'); // 从后面找到.  避免出错

    // 找不到斜线则 首位, 找不到点 则最后一位
    pos_backlash = (pos_backlash == std::string::npos) ? -1 : pos_backlash;
    pos_dot = (pos_dot == std::string::npos) ? file.size() : pos_dot;

    return file.substr(pos_backlash + 1, pos_dot - pos_backlash - 1);
}


// 二进制文件写入
bool Utils_Files::WriteStringBinary(std::fstream * pfile, const std::string & str, int len)
{
    char *tmp = new char[len];
    tmp = Utils_String::String2Char(str);
    pfile->write(tmp, len);
    delete []tmp;
    return true;
}

/**
 * @fn  bool Utils_Files::ReadStringBinary(std::fstream * pfile, std::string & str, int len)
 *
 * @brief   从文件流中读取一个 字符串
 *
 * @author  IRIS_Chen
 * @date    2019/11/29
 *
 * @param [in,out]  pfile   If non-null, the pfile
 * @param [in,out]  str     The string
 * @param           len     The length
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_Files::ReadStringBinary(std::fstream * pfile, std::string & str, int len)
{
    char *tmp = new char[len];
    pfile->read(tmp, len);
    str = Utils_String::Char2String(tmp);
    delete []tmp;
    return true;
}

/**
 * @fn  bool Utils_Files::WriteStringTxt(std::fstream *pfile, const std::string &str)
 *
 * @brief   Writes a string text
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param [in,out]  pfile   If non-null, the pfile
 * @param           str     The string
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_Files::WriteStringTxt(std::fstream *pfile, const std::string &str)
{
    if (pfile==nullptr && !pfile->is_open ())
    {
        return false;
    }

    pfile->write(str.c_str(),str.size());

    pfile->write("\n", 1);
    pfile->flush();
    return true;
}


/**
 * @fn  bool Utils_Files::SplitFileName(std::string &file_name, std::string &file_path, const std::string &filename)
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
bool Utils_Files::SplitFileName(std::string &file_name, std::string &file_path, const std::string &filename)
{
    // 根据 filename 更新 file_name_, 和 file_path_  找到最后一个 "/" 如果找不到 pos = -1
    size_t pos = filename.find_last_of("/");
    // 如果 找不到前置 /  表示当层目录, 对应的是 "" "/" "./" 
    if (pos < 2)
        file_path = "./";
    else
        file_path = filename.substr(0, pos + 1);    // 将 /  包含到 path 中

                                                    // 从找到的pos 后一位开始就可
    file_name = filename.substr(pos + 1); // 从/ 开始到最后的结尾
    pos = file_name.find_last_of(".");     // 计算最后一个 ". "  去除 拓展名

                                           // 表示找到了字符串
    if (pos > 0)
        file_name = file_name.substr(0, pos);

    return true;
}

/**
 * @fn  bool Utils_Files::IsDirExist(const std::string & path, bool create_)
 *
 * @brief   判断文件夹是否存在, 如果不存在 则新建 文件夹 // 不能否递归建立
 *
 * @author  IRIS_Chen
 * @date    2019/10/29
 *
 * @param   path    Full pathname of the file.
 * @param   create_ True to create.
 *
 * @return  True if dir exist, false if not.
 */
bool Utils_Files::IsDirExist(const std::string & path, bool create_)
{
    if (_access(path.c_str(), 0) == -1)
    {
        if (create_)
        {
#ifdef WIN32  
            int flag = _mkdir(path.c_str());
#endif  
#ifdef linux   
            int flag = mkdir(dir.c_str(), 0777);
#endif  
            return (flag == 0);
        }
        else
            return false;
    }
    return true;
}

/**
 * @fn  bool Utils_Files::IsFileExist(const std::string & file, bool create_)
 *
 * @brief   判断指定的文件是否存在 // 给定flg 如果不存在则建立文件 当path为文件时，_access函数判断文件是否存在，并判断文件是否可以用mode值指定的模式进行访问。
 *          
 *          当path为目录时，_access只判断指定的目录是否存在， 00--只检查文件是否存在 02--写权限  04--读权限 06--读写权限
 *          
 *          如果文件具有指定的访问权限，则函数返回0；如果文件不存在或者不能访问指定的权限，则返回-1。
 *
 * @author  IRIS_Chen
 * @date    2019/10/29
 *
 * @param   file    The file.
 * @param   create_ True to creat.
 *
 * @return  True if file exist, false if not.
 */
bool Utils_Files::IsFileExist(const std::string & file, bool create_)
{
    if ((_access(file.c_str(), 0)) == -1)
    {
        if (create_)
        {
            // 创建文件
            std::string name_, path_;
            SplitFileName(name_, path_, file);

            if (IsDirExist(path_, create_))
            {
                if ((_access(file.c_str(), 0)) != -1)
                    return true;
            }
            return false;
        }
        else
            return false;
    }
    return true;
}