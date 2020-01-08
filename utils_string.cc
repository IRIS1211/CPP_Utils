/**
 * @file    Code\utils\utils_string.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities string class
 * @changelog   2019/12/16    IRIS_Chen Created.
 */

// 通用字符串操作类 
#include "./utils_string.h"
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <time.h>

/**
 * @fn  std::vector<std::string> Utils_String::Str2Vec(const std::string & str, const char separator, bool skip_empty)
 *
 * @brief   字符串 分割成数组
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   str         The string
 * @param   separator   The separator
 * @param   skip_empty  True to skip empty
 *
 * @return  A std::vector&lt;std::string&gt;
 */
std::vector<std::string> Utils_String::Str2Vec(const std::string & str, const char separator, bool skip_empty)
{
    std::vector<std::string> res;
    std::istringstream iss(str);
    for (std::string item; getline(iss, item, separator);)
    {
        if (skip_empty && item.empty())
            continue;
        else
            res.push_back(item);
    }
    return res;
}


/**
 * @fn  std::vector<std::string> Utils_String::Str2Vector(const std::string & str, const std::string & delimiters, bool skip_empty)
 *
 * @brief   完成字符串分割
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   str         The string
 * @param   delimiters  The delimiters
 * @param   skip_empty  True to skip empty
 *
 * @return  A std::vector&lt;std::string&gt;
 */
std::vector<std::string> Utils_String::Str2Vector(const std::string & str, const std::string & delimiters, bool skip_empty)
{
    std::vector<std::string> res;
    std::string::size_type pos, prev = 0;
    while ((pos = str.find_first_of(delimiters, prev)) != std::string::npos)
    {
        if (pos > prev)
        {
            if (skip_empty && 1 == pos - prev)
                break;
            res.emplace_back(str, prev, pos - prev);
        }
        prev = pos + 1;
    }
    if (prev < str.size())
        res.emplace_back(str, prev, str.size() - prev);
    return res;
}

/**
 * @fn  const char* Utils_String::String2ConstChar(const std::string &str)
 *
 * @brief   String 2 character 直接返回数据字符串
 *          *        c_str 与 data 的区别 见
 *          https://www.cnblogs.com/devilmaycry812839668/p/6353807.html
 *
 * @author  IRIS_Chen
 * @date    2019/11/26
 *
 * @param   str The string
 *
 * @return  Null if it fails, else a pointer to a char
 */

const char* Utils_String::String2ConstChar(const std::string &str)
{
    return str.c_str();
}


/**
 * @fn  char * Utils_String::String2Char(const std::string & str)
 *
 * @brief   String 2 character
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   str The string
 *
 * @return  Null if it fails, else a pointer to a char
 */
char * Utils_String::String2Char(const std::string & str)
{
    char *ch = new char[str.size() + 1];
    strcpy(ch, str.c_str());

    return ch;

}

/**
 * @fn  const uchar * Utils_String::String2Uchar(const std::string & str)
 *
 * @brief   String 2 uchar
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   str The string
 *
 * @return  Null if it fails, else a pointer to a const uchar
 */
const uchar * Utils_String::String2Uchar(const std::string & str)
{
    return (uchar*)str.c_str();
}

/**
 * @fn  std::string Utils_String::ConstChar2String(const char *buffer)
 *
 * @brief   char 类型与 string的相互转换
 *
 * @author  IRIS_Chen
 * @date    2019/11/26
 *
 * @param   buffer  The buffer
 *
 * @return  A std::string
 */

std::string Utils_String::ConstChar2String(const char *buffer)
{
    return std::string(buffer);
}

/**
 * @fn  std::string Utils_String::Char2String(char * buffer)
 *
 * @brief   Character 2 string
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param [in,out]  buffer  If non-null, the buffer
 *
 * @return  A std::string
 */
std::string Utils_String::Char2String(char * buffer)
{
    return std::string(buffer);
}

std::string Utils_String::CharArr2String(char * buffer, int len)
{
    std::string str = "";
    CharArr2String(&str, buffer, len);
    return str;
}

bool Utils_String::CharArr2String(std::string * str, char * buffer, int len)
{
    if (len == -1)
    {
        while (*buffer != '\0')
        {
            *str += *buffer;
            buffer++;
        }
    }
    else
    {
        while (len--)
        {
            *str += *buffer;
            buffer++;
        }
    }
    return true;
}

std::string Utils_String::ShowCharArr(uchar * buffer, int len)
{
    std::string res = "";
    if (len == -1)
    {
        while (*buffer != '\0')
        {
            res += UChar2Hex(*buffer++);
            res += " ";
        }
    }
    else
    {
        while (len--)
        {
            res += UChar2Hex(*buffer++) + " ";
        }
    }
    return res;
}

std::string Utils_String::ShowCharArr(const std::string * str)
{
    std::string res = "";
    for (const auto &s : *str)
    {
        res += UChar2Hex(s) + " ";
    }
    return res;
}

/**
 * @fn  std::string Utils_String::Hex2String(const std::string & str, bool flg_space)
 *
 * @brief   将 hex 字符串转换成 string 字符串  
 *  *       // #PERF(SChen00) string 只能是 char 型
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 *
 * @param   str         The string
 * @param   flg_space   True to flg space
 *
 * @return  A std::string
 */
std::string Utils_String::Hex2String(const std::string & str, bool flg_space)
{
    // 出错 只有两个值 默认不符合 操作
    if (str.size() < 3)    return nullptr;
    // 默认够长 判断是否存在空格
    if (str[2] == ' ')   flg_space = true;
    int step = flg_space ? 3 : 2;

    int res_size = (flg_space?(str.size() + 1): str.size()) / step;
    std::string res;
    res.resize(res_size);

    for (int i = 0; i < res_size;i++)
    {
        uchar ch = Hex2Uchar(str.substr(static_cast<size_t>(i*step), 2));
        // 根据是否有空格选择 移动
        res[i] = (char)ch;
    }
    return res;
}

/**
 * @fn  std::string Utils_String::UChar2String(const uchar * buffer)
 *
 * @brief   Uchar 2 string
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   buffer  The buffer
 *
 * @return  A std::string
 */
std::string Utils_String::UChar2String(const uchar * buffer)
{   
    std::string str = (char*)buffer;
    return str;
}

std::string Utils_String::UChar2String(uchar *buffer)
{
    std::string str = (char*)buffer;
    return str;
}

/**
 * @fn  char * Utils_String::ConstChar2Char(const char* buffer)
 *
 * @brief   Constant character 2 character
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   buffer  The buffer
 *
 * @return  Null if it fails, else a pointer to a char
 */
char * Utils_String::ConstChar2Char(const char* buffer)
{
    char* res = new char[100];  // 足够的长度避免溢出
    strcpy(res, buffer);
    return res;
}

/**
 * @fn  const char * Utils_String::Char2ConstChar(char * buffer)
 *
 * @brief   Character 2 constant character
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param [in,out]  buffer  If non-null, the buffer
 *
 * @return  Null if it fails, else a pointer to a const char
 */
const char * Utils_String::Char2ConstChar(char * buffer)
{
    return buffer;
}

// uchar 数据转换 char  >127   c1-256
char Utils_String::UChar2Char(uchar c1)
{
    return static_cast<char>(c1 > 127 ? c1 - 256 : c1);
}

// char 类型转换 uchar  <0 -- c1 +256
uchar Utils_String::Char2UChar(char c1)
{
    return static_cast<uchar>((c1 < 0 ? 256 + c1 : c1));
}


/**
 * @fn  std::string Utils_String::AddQuoteString(std::string str, const std::string q)
 *
 * @brief   在字符串前后 添加 引号 双引号  用于YML 写入
 *
 * @author  IRIS_Chen
 * @date    2019/11/28
 *
 * @param   str The string
 * @param   q   A std::string to process
 *
 * @return  A std::string
 */

std::string Utils_String::AddQuoteString(std::string str, const std::string q)
{
    return (q + str + q);
}

/**
 * @fn  int Utils_String::StringVersionToInt(const std::string & str)
 *
 * @brief   将 1.1 这种转换成 int 版本号  1.1 == 101   10.11 == 1011
 *
 * @author  IRIS_Chen
 * @date    2019/11/28
 *
 * @param   str The string
 *
 * @return  An int
 */
int Utils_String::StringVersionToInt(const std::string & str)
{
    std::vector<std::string> tmp_str = Str2Vec(str, '.');
    assert(tmp_str.size() == 2);
    int res = 0;
    for (const auto& s : tmp_str)
    {
        int tmp = std::stoi(s);
        if (tmp < 0)
            tmp = -tmp;
        res = res * 100 + tmp;
    }
    return res;
}


/**
 * @fn  std::string Utils_String::NumToString(int num, int width, int base)
 *
 * @brief   Number to string 整型数据 前补 0 占位符显示 进制 为 8 10 16  \
 *  *       如果超过给出的宽度 原始宽度显示  16进制 大写输出
 * * 
 *
 * @author  IRIS_Chen
 * @date    2019/12/3
 *
 * @param   num     Number of
 * @param   width   The width
 * @param   base    The base
 *
 * @return  The total number of to string
 */
std::string Utils_String::NumToString(int num, int width, int base)
{

#if 0
    // 保证 存在进制 只考虑 2 8 , 10 16 进制
    static std::map<int, char> t_base = {
        { 2,'0' },
        { 8,'o' },
        { 10,'d' },
        { 16,'x' } };
    if (!t_base.count(base))
        return "";
    // 二进制 特殊处理
    if (base == 2)
    {
        std::string str_8 = NumToString(num, width, 8);
        //  设置8进制 转2进制码表, 转换之后 去除前缀0 即可
        static const std::vector<std::string> table = { "000","001","010","011","100","101","110","111" };

        std::string str_2 = "";
        for (auto s : str_8)
        {
            if(s =='0')
                continue;
            str_2 += table[s - '0'];
        }
        // 去掉前面所有的 0值 从1 开始
        int pos = static_cast<int>(str_2.find_first_of('1'));

        // #TODO(Schen00) 处理, 得到的长度小于width 的情况
        return pos == std::string::npos ?"":str_2.substr (pos);
    }

    std::string format = "%0" + std::to_string(width) + t_base.find(base)->second;

    char *buf = new char[20];
    sprintf(buf, format.c_str(), num);
    return std::string(buf);
#else

    // 不限制进制, 暴力处理
    std::string res = "";
    while (num)
    {
        res = (base == 16 ? Num2Hex(num % base) : (char)(num % base + '0')) + res;
        num /= base;
    }
    // 不足位 补0  足位 不删除
    int cnt = width - res.size();
    while (cnt-- > 0)
    {
        res = "0" + res;
    }
    return res;

#endif
}




/**
 * @fn  std::string Utils_String::NumToString(const float &num, int precision)
 *
 * @brief   float 控制精度显示
 *
 * @author  IRIS_Chen
 * @date    2019/12/3
 *
 * @param   num         Number of
 * @param   precision   The precision
 *
 * @return  The total number of to string
 */
std::string Utils_String::NumToString(const float &num, int precision)
{
    char *buf = new char[20];
    std::string format_ = "%." + std::to_string(precision) + "f";
    sprintf(buf, format_.c_str(), num);
    return std::string(buf);
}

// 将字符串转换成数字 根据进制  "123" ==> 123  
int Utils_String::String2Num(const std::string & str, int base)
{
    int res = 0;

    for (const char &s : str)
    {
        res = res*base + (base == 16 ? Hex2Num(s) : s - '0');
    }
    return res;
}




/**
 * @fn  uchar Utils_String::Hex2Uchar(const std::string & str)
 *
 * @brief   Hexadecimal 2 uchar 将两个 hex 字符 转换成 0-256
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param   str The string 默认初始两位字符  FF == 255   00 = 0  0D = 14
 *
 * @return  An uchar
 */
uchar Utils_String::Hex2Uchar(const std::string & str)
{
    uchar res = 0;
    for (const auto &s:str)
    {
        res = (res << 4) + Hex2Num(s);
    }
    return res;
}

/**
 * @fn  int Utils_String::Hex2Num(const char ch)
 *
 * @brief   根据 各种情况 转换字母  一位字母 大于 48 的 +9  然后取后4位的值
 * *        将 0-F 转换成 0-15
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   ch  The ch
 *
 * @return  An int
 */
int Utils_String::Hex2Num(const char ch)
{
    //int res = (ch & '@' ? ch + 9 : ch) & 0x0F;
    //LInfo("ch:{},res:{}", ch, res);
    return (ch & '@' ? ch + 9 : ch) & 0x0F;
}



/**
 * @fn  char Utils_String::Num2Hex(int num, bool Up )
 *
 * @brief   将 0-15 转换成 0-F
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param   num Number of
 * @param   Up  True to up
 *
 * @return  The total number of 2 hexadecimal
 */
char Utils_String::Num2Hex(int num, bool Up /* = true */)
{
    char res;
    if (num >= 10 && num <= 15)
    {
        res = num - 10 + (Up ? 'A' : 'a');
    }
    else
        res = num + '0';
    return res;
}

/**
 * @fn  std::string Utils_String::Num2Hex(uchar num, bool Up)
 *
 * @brief   Number 2 hexadecimal  得到的结果只有 小写
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param   num Number of
 * @param   Up  True to up
 *
 * @return  The total number of 2 hexadecimal
 */
std::string Utils_String::Num2Hex(uchar num, bool Up)
{
    std::string res= NumToString((int)num, 2, 16);
    return Up ? StringUpper(res) : StringLowwer (res);
}

/**
 * @fn  int Utils_String::Hex2Num(const std::string & str)
 *
 * @brief   连续的 16 进制字符 转换成数字 // 空格滤除
 *
 * @author  IRIS_Chen
 * @date    2019/12/16
 *
 * @param   str The string
 *
 * @return  An int
 */
int Utils_String::Hex2Num(const std::string & str)
{
    int res = 0;
    for (const auto &s : str)
        if(s != ' ' )
            res = (res << 4) + Hex2Num(s);
    return res;
}





/**
 * @fn  uchar * Utils_String::Hex2CharArr(uchar *&buffer, const std::string & str, bool flg_space)
 *
 * @brief   Hexadecimal 2 character array hex 字符串 转换成 数组
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param [in,out]  buffer      [in,out] If non-null, the buffer
 * @param           str         The string
 * @param           flg_space   True to flg space
 *
 * @return  Null if it fails, else a pointer to an uchar
 */
uchar * Utils_String::Hex2CharArr(uchar *&buffer, const std::string & str, bool flg_space)
{
    // 出错 只有两个值 默认不符合 操作
    if (str.size() < 3)    return nullptr;
    // 默认够长 判断是否存在空格
    if (str[2] == ' ')   flg_space = true;

    int step = flg_space ? 3 : 2;

    // 拓展空间 保证有足够的空间存储数组
    buffer = new uchar[(str.size() + 1) / step + 1];

    // std::string str2 = "";

    for (int i = 0; i < static_cast<int>(str.size());i += step)
    {
        uchar ch = Hex2Uchar(str.substr(static_cast<size_t>(i), 2));
        // 根据是否有空格选择 移动
        *(buffer + i / step) = ch;

        // str2 += std::to_string((int)ch) + "-";
    }
    // LInfo("charArr:{}", str2);

    return buffer;

}

#if 0
uchar * Utils_String::Hex2CharArr(uchar *buffer, const std::string & str, bool flg_space)
{
    // 出错 只有两个值 默认不符合 操作
    if (str.size() < 3)    return nullptr;
    // 默认够长 判断是否存在空格
    if (str[2] == ' ')   flg_space = true;

    int step = flg_space ? 3 : 2;

    // 拓展空间 保证有足够的空间存储数组
    buffer = new uchar[(str.size() + 1) / step + 1];

    std::string str2 = "";

    for (int i = 0; i < static_cast<int>(str.size());)
    {
        uchar ch = Hex2Uchar(str.substr(static_cast<size_t>(i), 2));
        // 根据是否有空格选择 移动
        *(buffer + i / step) = ch;
        i += step;

        str2 += std::to_string((int)ch) + "-";
    }
    // LInfo("charArr:{}", str2);

    return buffer;
}
#endif

/**
 * @fn  std::string Utils_String::CharArr2Hex(uchar * buffer, int length, int flg_space)
 *
 * @brief   Character array 2 hexadecimal  数组 转换成 hex 字符
 *          * 将UCHAR 字符串依次转换成 string 字符串
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param [in,out]  buffer      If non-null, the buffer
 * @param           length      The length
 * @param           flg_space   The flg space
 *
 * @return  A std::string
 */
std::string Utils_String::CharArr2Hex(uchar * buffer, int length, int flg_space)
{
    std::string str = "";
    // 读取数组中所有字符
    for (int i = 0; i < length; i++)
    {
        str += Num2Hex(*buffer++);
        // 如果开启空格的话  每两个字符 之间加入一个空格 最后一个不加
        if (flg_space && i != length - 1)
            str += " ";
    }
    return str;
}



/**
 * @fn  std::string Utils_String::StringUpper(const std::string & str)
 *
 * @brief   将字符串全部转换成大写
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param   str The string
 *
 * @return  A std::string
 */
std::string Utils_String::StringUpper(const std::string & str)
{
    std::string res = "";
    for (const auto &s : str)
    {
        if (s >= 'a' &&s <= 'z')
            res += s - 32;
        else
            res += s;
    }
    return res;
}

/**
 * @fn  std::string Utils_String::StringLowwer(const std::string & str)
 *
 * @brief   将字符串全部转换成小写
 *
 * @author  IRIS_Chen
 * @date    2019/12/18
 *
 * @param   str The string
 *
 * @return  A std::string
 */
std::string Utils_String::StringLowwer(const std::string & str)
{
    std::string res = "";
    for (const auto &s : str)
    {
        if (s >= 'A' &&s <= 'Z')
            res += s + 32;
        else
            res += s;
    }
    return res;
}

/**
 * @fn  uchar Utils_String::Commu_CheckXOR(const uchar * buffer, int len)
 *
 * @brief   异或校验 8位  避免出现 0 数据造成的 截至
 *
 * @author  IRIS_Chen
 * @date    2019/12/24
 *
 * @param   buffer  The buffer  字符串指针
 * @param   len     The length
 *
 * @return  uchar  字符
 */
uchar Utils_String::Commu_CheckXOR(const uchar * buffer, int len)
{
    if (buffer == nullptr || len < 1)
        return 0;
    uchar res = 0;
    for (int i = 0; i < len; i++)
    {
        res = res ^ (*(buffer + i));
    }
    return res;
}

uchar Utils_String::Commu_CheckSum(const std::string & str)
{
    uchar res = 0;
    // #NormTypes(SChen00) 可能存在 类型转换的错误
    for (const auto &s : str)
    {
        res += s;
    }
    return res;
}

uchar Utils_String::Commu_CheckSum(uchar * dat, int len)
{
    if (dat == nullptr || len < 1)
    {
        return 0;
    }
    // #Note(Schen00) len 必须满足一定范围, 超过之后可能会出现异常
    uchar res = 0;

    try
    {
        for (int i = 0; i < len; i++)
        {
            res += *(dat + i);
        }
    }
    catch (...)
    {
        LError("dat has not enough length, data over");
        throw("dat has not enough length, data over");
    }
    return res;
}

/**
 * @fn  uchar Utils_String::Commu_CheckXOR(const std::string & str)
 *
 * @brief   异或校验 8位
 *
 * @author  IRIS_Chen
 * @date    2019/12/24
 *
 * @param   str The buffer  字符串指针
 *
 * @return  uchar  字符
 */
uchar Utils_String::Commu_CheckXOR(const std::string & str)
{
    uchar res = 0;

    // for (const char &s : str)
    for(char s : str)
    {
        res ^= s;

#if 0
        LInfo("res:{},\t str:{}, \t s:{},{}", \
              Utils_String::NumToString(res, 8, 2), \
              str.size(), \
              s, \
              Utils_String::NumToString(s, 8, 2));
#endif
    }
    return res;
}




