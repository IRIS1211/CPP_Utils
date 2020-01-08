/**
 * @file    Code\utils\utils_string.h.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   通用字符串操作类 继承使用, 方便使用
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#ifndef UTILS_STRING_H__
#define UTILS_STRING_H__

#include <vector>
#include <string>
#include <iostream>

/**
 * @class   Utils_String utils_string.h Code\utils\utils_string.h
 *
 * @brief   The utilities string.
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 */
class Utils_String
{
    public:

    // 将vector 里面的内容转换成 字符串字符流输出
    template<typename T>
    /**
     * @fn  static void Utils_String::CoutVectorIdx(T & vec,bool new_line = true)
     *
     * @brief   Cout vector index
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param [in,out]  vec         The vector
     * @param           new_line    (Optional) True to new line
     */
    static void CoutVectorIdx(T & vec,bool new_line = true)
    {
        std::ostringstream buffer;
        size_t n = vec.size();
        std::string new_line_char = new_line ? "\n" : "";
        if (n == 0)
        {
            buffer << "Vector is Null";
        }
        else
        {
            for (int i = 0; i < n; i++)
                buffer << "\tidx:" << i << "\t:" << vec[i] << new_line_char;
        }
        std::cout << buffer.str() << endl;
    }

    template<typename T>
    /**
     * @fn  static void Utils_String::CoutVector(T & vec, bool new_line = true)
     *
     * @brief   Cout vector
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param [in,out]  vec         The vector
     * @param           new_line    (Optional) True to new line
     */
    static void CoutVector(T & vec, bool new_line = true)
    {
        std::ostringstream buffer;
        size_t n = vec.size();
        std::string new_line_char = new_line ? "\n" : " ";
        if (n == 0)
        {
            buffer << "Vector is Null";
        }
        else
        {
            for (int i = 0; i < n; i++)
                buffer << vec[i] << new_line_char;
        }
        std::cout << buffer.str() << endl;
    }


    /**
    * @fn  template<typename T> std::vector<T> Str2Vec(const std::string &str, std::vector<T> &elem, const char separator , bool skip_empty = true)
    *
    * @brief   将字符串根据分割符号分割的数字 数组 转换成 int输出 这样我们不仅可以用别的字符来做分隔，还可以选择跳过空白字符串
    *          https://segmentfault.com/a/1190000002483483
    *
    * @author  IRIS_Chen
    * @date    2019/11/25
    *
    * @tparam  T   Generic type parameter.
    * @param           str         The string  原始字符串
    * @param [in,out]  elem        The element  输入输出结果
    * @param           separator   The separator 分割符号 默认,
    * @param           skip_empty  (Optional) True to skip empty 跳过空白, 否则 添加一个空元素
    *
    * @return  vector 输出分割结果值
    */

    template<typename T>
    static std::vector<T> Str2Vec(const std::string &str,
                           std::vector<T> &elem,
                           const char separator,
                           bool skip_empty = true)  ///< True to skip empty
    {
        std::istringstream iss(str);
        for (std::string item; getline(iss, item, separator);)
        {
            if (skip_empty && item.empty())
                continue;
            else
                elem.push_back(item);
        }
        return elem;
    }
    
    /**
     * @fn  static std::vector<std::string> Utils_String::Str2Vec(const std::string &str, const char separator, bool skip_empty = true);
     *
     * @brief   2 vector
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str         The string
     * @param   separator   The separator
     * @param   skip_empty  (Optional) True to skip empty
     *
     * @return  A std::vector&lt;std::string&gt;
     */
    static std::vector<std::string> Str2Vec(const std::string &str,
                                            const char separator,
                                            bool skip_empty = true);
    /**
     * @fn  template<typename T> static std::vector<T> Utils_String::Str2Vector(const std::string &str, std::vector<T> &elem, const std::string &delimiters, bool skip_empty = true)
     *
     * @brief   返回字符串分割符号分割的数字数组  允许使用不同的字符来区分字符 https://segmentfault.com/a/1190000002483483
     *
     * @author  IRIS_Chen
     * @date    2019/11/25
     *
     * @tparam  T   Generic type parameter.
     * @param           str         The string  原始字符串
     * @param [in,out]  elem        The element     输入输出结果数组
     * @param           delimiters  The delimiters  分割符号字符串 多种
     * @param           skip_empty  (Optional) True to skip empty   是否跳过空格
     *
     * @return  返回结果值
     *
     * ### tparam   T   Generic type parameter.
     */
    template<typename T>
    static std::vector<T> Str2Vector(const std::string &str,
                              std::vector<T> &elem,
                              const std::string &delimiters,
                              bool skip_empty = true)   ///< True to skip empty
    {
        std::string::size_type pos, prev = 0;
        while ((pos = str.find_first_of(delimiters, prev)) != std::string::npos)
        {
            if (pos > prev)
            {
                if (skip_empty && 1 == pos - prev)
                    break;
                elem.emplace_back(str, prev, pos - prev);
            }
            prev = pos + 1;
        }
        if (prev < str.size())
            elem.emplace_back(str, prev, str.size() - prev);
        return elem;
    }

    /**
     * @fn  static std::vector<std::string> Utils_String::Str2Vector(const std::string &str, const std::string &delimiters, bool skip_empty = true);
     *
     * @brief   2 vector
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str         The string
     * @param   delimiters  The delimiters
     * @param   skip_empty  (Optional) True to skip empty
     *
     * @return  A std::vector&lt;std::string&gt;
     */
    static std::vector<std::string> Str2Vector(const std::string &str,
                                               const std::string &delimiters,
                                               bool skip_empty = true);

    /**
     * @fn  static const char* Utils_String::String2ConstChar(const std::string &str);
     *
     * @brief   将字符串转换成 char * 数组
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str The string
     *
     * @return  Null if it fails, else a pointer to a const char
     */
    static const char* String2ConstChar(const std::string &str);
    /**
     * @fn  static char* Utils_String::String2Char(const std::string &str);
     *
     * @brief   String 2 character
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str The string
     *
     * @return  Null if it fails, else a pointer to a char
     */
    static char* String2Char(const std::string &str);
    /**
     * @fn  static const uchar* Utils_String::String2Uchar(const std::string &str);
     *
     * @brief   String 2 uchar
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str The string
     *
     * @return  Null if it fails, else a pointer to a const uchar
     */
    static const uchar* String2Uchar(const std::string &str);
    /**
     * @fn  static std::string Utils_String::ConstChar2String(const char *buffer);
     *
     * @brief   char * 数组指针 转换成 string
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   buffer  The buffer
     *
     * @return  A std::string
     */
    static std::string ConstChar2String(const char *buffer);
    /**
     * @fn  static std::string Utils_String::Char2String(char* buffer);
     *
     * @brief   Character 2 string  存在 \0 截断问题
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param [in,out]  buffer  If non-null, the buffer
     *
     * @return  A std::string
     */
    static std::string Char2String(char* buffer);

    /**
     * @fn  static std::string Utils_String::CharArr2String(char* buffer, int len = -1);
     *
     * @brief   如果不给定长度, 一直向后直到得到 \0 可能中途截断
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  buffer  If non-null, the buffer
     * @param           len     (Optional) The length
     *
     * @return  A std::string
     */
    static std::string CharArr2String(char* buffer, int len = -1);
    // static char* String2Char(const std::string &str);
    /**
     * @fn  static bool Utils_String::CharArr2String(std::string *str, char *buffer, int len = -1);
     *
     * @brief   Character array 2 string
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  str     If non-null, the string
     * @param [in,out]  buffer  If non-null, the buffer
     * @param           len     (Optional) The length
     *
     * @return  True if it succeeds, false if it fails
     */
    static bool CharArr2String(std::string *str, char *buffer, int len = -1);

    // 将 char arr 输出出来 显示
    static std::string ShowCharArr(uchar* buffer, int len = -1);
    static std::string ShowCharArr(const std::string *str);


    /**
     * @fn  static std::string Utils_String::Hex2String(const std::string &str, bool flg_space = true);
     *
     * @brief   将 hex 字符串转换成 string 字符串
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   str         The string
     * @param   flg_space   (Optional) True to flg space
     *
     * @return  A std::string
     */
    static std::string Hex2String(const std::string &str, bool flg_space = true);

    /**
     * @fn  static std::string Utils_String::UChar2String(const uchar * buffer);
     *
     * @brief   Uchar 2 string
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   buffer  The buffer
     *
     * @return  A std::string
     */
    static std::string UChar2String(const uchar * buffer);
    /**
     * @fn  static std::string Utils_String::UChar2String(uchar *buffer);
     *
     * @brief   Uchar 2 string
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param [in,out]  buffer  If non-null, the buffer
     *
     * @return  A std::string
     */
    static std::string UChar2String(uchar *buffer);

    /**
     * @fn  static char Utils_String::*ConstChar2Char(const char* buffer);
     *
     * @brief   Constant character 2 character
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   buffer  The buffer
     *
     * @return  Null if it fails, else a pointer to a char
     */
    static char *ConstChar2Char(const char* buffer);

    


    /**
     * @fn  static const char * Utils_String::Char2ConstChar(char *buffer);
     *
     * @brief   Character 2 constant character
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param [in,out]  buffer  If non-null, the buffer
     *
     * @return  Null if it fails, else a pointer to a const char
     */
    static const char * Char2ConstChar(char *buffer);

    /**
     * @fn  static char Utils_String::UChar2Char(uchar c1);
     *
     * @brief   Uchar 2 char 的相互转换
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   c1  The first uchar
     *
     * @return  A char
     */
    static char UChar2Char(uchar c1);
    /**
     * @fn  static uchar Utils_String::Char2UChar(char c1);
     *
     * @brief   Character 2 u character
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     *
     * @param   c1  The first char
     *
     * @return  An uchar
     */
    static uchar Char2UChar(char c1);

    /**
     * @fn  static std::string Utils_String::AddQuoteString(std::string str,const std::string q = " "");
     *
     * @brief   在字符串前后 添加 引号 双引号
     *
     * @author  IRIS_Chen
     * @date    2019/12/3
     *
     * @param   str The string
     * @param   q   (Optional) A std::string to process
     *
     * @return  A std::string
     */
    static std::string AddQuoteString(std::string str,const std::string q = "\"");

    /**
     * @fn  static int Utils_String::StringVersionToInt(const std::string &str);
     *
     * @brief   string 1.1 版本 生成 版本号 数字
     *
     * @author  IRIS_Chen
     * @date    2019/12/3
     *
     * @param   str The string
     *
     * @return  An int
     */
    static int StringVersionToInt(const std::string &str);

    /**
     * @fn  static std::string Utils_String::NumToString(int num, int width = 3,int base=10);
     *
     * @brief   num 转换成 字符串 前 补零
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   num     Number of
     * @param   width   (Optional) The width
     * @param   base    (Optional) The base
     *
     * @return  The total number of to string
     */
    static std::string NumToString(int num, int width = 3,int base=10);

    /**
     * @fn  static std::string Utils_String::NumToString(const float &num, int precision);
     *
     * @brief   float 精度输出  precision 表示 小数点后位数
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   num         Number of
     * @param   precision   The precision
     *
     * @return  The total number of to string
     */
    static std::string NumToString(const float &num, int precision);

    // 默认10字符串转换成数字
    static int String2Num(const std::string &str, int base = 10);

    /**
     * @def Utils_String::Num2Str
     *
     * @brief   同名引用
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     */
    #define Num2Str NumToString

    /**
     * @fn  static uchar Utils_String::Hex2Uchar(const std::string &str);
     *
     * @brief   将两位 hex 值计算得到 int 值
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   str The string
     *
     * @return  An uchar
     */
    static uchar Hex2Uchar(const std::string &str);

    /**
     * @fn  static int Utils_String::Hex2Num(const char ch);
     *
     * @brief   将一位hex 16进制值 转化为 数字
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   ch  The ch
     *
     * @return  An int
     */
    static int Hex2Num(const char ch);
    #define Char2Num Hex2Num        // 针对一位的数据

    /**
     * @fn  static char Utils_String::Num2Hex(int num,bool Up = true);
     *
     * @brief   将数字转换成 hex 值 0-15 转换成 '0' - 'F'
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   num Number of
     * @param   Up  (Optional) True to up
     *
     * @return  The total number of 2 hexadecimal
     */
    static char Num2Hex(int num,bool Up = true);
    
    /**
     * @fn  static std::string Utils_String::Num2Hex(uchar num, bool Up = true);
     *
     * @brief   将 0-255 转换成 "00"- "FF"
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   num Number of
     * @param   Up  (Optional) True to up
     *
     * @return  The total number of 2 hexadecimal
     */
    static std::string Num2Hex(uchar num, bool Up = true);

    /**
     * @def Utils_String::UChar2Hex
     *
     * @brief   定义函数别名
     *
     * @author  IRIS_Chen
     * @date    2019/12/25
     */
    #define  UChar2Hex Num2Hex

    /**
     * @fn  static int Utils_String::Hex2Num(const std::string &str);
     *
     * @brief   将字符串按照16进制转换成数字
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param   str The string
     *
     * @return  An int
     */
    static int Hex2Num(const std::string &str);

    /**
     * @fn  static uchar * Utils_String::Hex2CharArr(uchar *&buffer, const std::string &str, bool flg_space = true);
     *
     * @brief   将 hex 字符串 转换成 uchar 数组  判断是否有空格字符
     *
     * @author  IRIS_Chen
     * @date    2019/12/18
     *
     * @param [in,out]  buffer      [in,out] If non-null, the buffer
     * @param           str         The string
     * @param           flg_space   (Optional) True to flg space
     *
     * @return  Null if it fails, else a pointer to an uchar
     */
    static uchar * Hex2CharArr(uchar *&buffer, const std::string &str, bool flg_space = true);
    // static uchar * Hex2CharArr(uchar *buffer, const std::string &str, bool flg_space = true);
    /**
     * @fn  static std::string Utils_String::CharArr2Hex(uchar *buffer, int length = 16, int flg_space = 1);
     *
     * @brief   将 UCHAR 数组 转换成  string 字符串
     *
     * @author  IRIS_Chen
     * @date    2019/10/14
     *
     * @param [in,out]  buffer      If non-null, the buffer.
     * @param           length      (Optional) The length.
     * @param           flg_space   (Optional) The flg space.
     *
     * @return  A std::string.
     */
    static std::string CharArr2Hex(uchar *buffer, int length = 16, int flg_space = 1);

/**
 * @def Utils_String::CharArr2String
 *
 * @brief   定义 字符串转换成 uchar 数组的函数
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 */
// #define CharArr2String UChar2String
/**
 * @def Utils_String::UCharArr2String
 *
 * @brief   A macro that defines Character Array 2 string
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 */
#define UCharArr2String UChar2String
/**
 * @def Utils_String::String2CharArr
 *
 * @brief   A macro that defines string 2 Character Array
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 */
#define String2CharArr String2Uchar
/**
 * @def Utils_String::String2UCharArr
 *
 * @brief   A macro that defines string 2 u Character Array
 *
 * @author  IRIS_Chen
 * @date    2019/12/25
 */
#define String2UCharArr String2Uchar

    /**
     * @fn  static std::string Utils_String::StringUpper(const std::string &str);
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
    static std::string StringUpper(const std::string &str);

    /**
     * @fn  static std::string Utils_String::StringLowwer(const std::string &str);
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
    static std::string StringLowwer(const std::string &str);


    /**
     * @fn  static uchar Utils_String::Commu_CheckXOR(const uchar* buffer, int len);
     *
     * @brief   异或校验 8位
     *
     * @author  IRIS_Chen
     * @date    2019/12/24
     *
     * @param   buffer  The buffer  字符串指针
     * @param   len     The length  字符串的长度
     *
     * @return  uchar  字符
     */
    static uchar Commu_CheckXOR(const uchar* buffer, int len);

    /**
     * @fn  static uchar Utils_String::Commu_CheckXOR(const std::string &str);
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
    static uchar Commu_CheckXOR(const std::string &str);
    /**
     * @fn  static uchar Utils_String::Commu_CheckXOR(uchar *dat, int len=-1);
     *
     * @brief   计算从指针开始的len 字符
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  dat If non-null, the dat
     * @param           len (Optional) The length
     *
     * @return  An uchar
     */
    static uchar Commu_CheckXOR(uchar *dat, int len=-1);
    
    /**
     * @fn  static uchar Utils_String::Commu_CheckSum(const std::string &str);
     *
     * @brief   计算 校验和
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param   str The string
     *
     * @return  An uchar
     */
    static uchar Commu_CheckSum(const std::string &str);

    /**
     * @fn  static uchar Utils_String::Commu_CheckSum(uchar *dat, int len = -1);
     *
     * @brief   计算len 长度的校验和
     *
     * @author  IRIS_Chen
     * @date    2019/12/27
     *
     * @param [in,out]  dat If non-null, the dat
     * @param           len (Optional) The length
     *
     * @return  An uchar
     */
    static uchar Commu_CheckSum(uchar *dat, int len = -1);

};

#endif  //UTILS_STRING_H__