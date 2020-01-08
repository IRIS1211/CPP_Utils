
// 单元测试
#include "./utils.h"
#include "./utils_string.h"


TEST_CASE("Test utils_string Func Str2Vec")
{
#if 1
    std::string str("Windows,Linux,,MacOS,");
    std::vector<std::string> res;
    res = Utils_String::Str2Vec(str, res,',', true);
    CHECK(res.size() == 3);
    res.clear();

    res = Utils_String::Str2Vec(str, res, ',', false);
    CHECK(res.size() == 4);
    
#endif
    // Utils_String::CoutVector(res);
}

TEST_CASE("Test utils_string Func Str2Vector")
{
#if 1
    std::string str("Windows,Linux||,'',MacOS All");
    std::vector<std::string> res;
    res = Utils_String::Str2Vector(str,res, ",| ",true);
    // Utils_String::CoutVector(res);
#endif
}

TEST_CASE("Test utils_string Func StrVersionToInt")
{
#if 1
    CHECK(Utils_String::StringVersionToInt("1.1") == 101);
    CHECK(Utils_String::StringVersionToInt("10.0") == 1000);
    CHECK(Utils_String::StringVersionToInt("10.0") == 1000);
#endif
}

TEST_CASE("Test Num 2 String")
{
    CHECK(Utils_String::NumToString(3.1415926f, 2) == "3.14");
    CHECK(Utils_String::NumToString(3, 3) == "003");
    CHECK(Utils_String::NumToString(314, 3) == "314");
    CHECK(Utils_String::NumToString(314, 2) == "314");
}

TEST_CASE("Test Num 2 String base")
{
#if 1
    CHECK(Utils_String::NumToString(314, 3) == "314");
    CHECK(Utils_String::NumToString(314, 4,8) == "0472");
    CHECK(Utils_String::NumToString(314, 6,16) == "00013A");
    CHECK(Utils_String::NumToString(314, 4, 2) == "100111010");
    CHECK(Utils_String::NumToString(15, 4, 2) == "1111");
#endif
}

TEST_CASE("Test String 2 Num")
{
    CHECK(Utils_String::String2Num("123", 10) == 123);
    CHECK(Utils_String::String2Num("F", 16) == 15);
    CHECK(Utils_String::String2Num("1111", 2) == 7);
    CHECK(Utils_String::String2Num("777", 10) == 511);
}

TEST_CASE("Hex 2 Num")  ///< The test case
{
#if 1
    CHECK(Utils_String::Hex2Num('F') == 15);
    CHECK(Utils_String::Hex2Num('A') == 10);
    CHECK(Utils_String::Hex2Num('0') == 0);
    CHECK(Utils_String::Hex2Num('f') == 15);
    CHECK(Utils_String::Hex2Num('a') == 10);

    CHECK(Utils_String::Hex2Num("FF") == 255);
    CHECK(Utils_String::Hex2Num("Ff") == 255);
    CHECK(Utils_String::Hex2Num("aA") == 170);
    CHECK(Utils_String::Hex2Num("00") == 0);
#endif
}


TEST_CASE("Hex 2 uchar")
{
#if 1
    CHECK(Utils_String::Hex2Num("00") == 0);
    CHECK(Utils_String::Hex2Num("0D") == 13);
    CHECK(Utils_String::Hex2Num("FF") == 255);
    CHECK(Utils_String::Hex2Num("D0") == 208);
#endif
}


TEST_CASE("Hex 2 uchar")
{
#if 1
    CHECK(Utils_String::Num2Hex(15) == 'F');
    CHECK(Utils_String::Num2Hex(15, false) == 'f');
    CHECK(Utils_String::Num2Hex(0, false) == '0');
    CHECK(Utils_String::Num2Hex(0) == '0');
    CHECK(Utils_String::Num2Hex((uchar)255) == "FF");
    CHECK(Utils_String::Num2Hex((uchar)0) == "00");
    CHECK(Utils_String::Num2Hex((uchar)15) == "0F");

    // 测试 函数别名定义
    CHECK(Utils_String::UChar2Hex((uchar)15) == "0F");
    CHECK(Utils_String::UChar2Hex(15, false) == 'f');
#endif
}


TEST_CASE("char arr to String")
{
#if 0
    std::string hex_str = "68 13 00 85 11 12 21 22 31 32 00 00 01 00 00 02 00 00 03 88 FF 01 02 03 04 05 0F";

    // 字符串 处理  \0 存在问题
    uchar * buffer; 
    Utils_String::Hex2CharArr(buffer, hex_str,true);

    std::string char_str = Utils_String::CharArr2String((char*)buffer,27);

    std::string str = Utils_String::Char2String((char*)buffer);


    std::string test_str = "12345678";
    // LDebug("test_str:{}", test_str);
    test_str[1] = 0;

    // LDebug("test_str:{}", test_str);
    char *buf = Utils_String::String2Char(test_str);
    test_str = Utils_String::Char2String(buf);
    // LInfo("str:{}", str);
#endif
}

TEST_CASE("CharArr2String")
{
    char buffer[] = { 5,4,3,2,1,0,2,4,6,0,8 };
    std::string test_str1 = "", test_str2 = "";

    test_str1 = Utils_String::CharArr2String(buffer, -1);   // 不给参数
    test_str2 = Utils_String::CharArr2String(buffer, 11);   // 真实长度
    // test_str2 = Utils_String::CharArr2String(buffer, 15);   // 越界   
    // LDebug("test_str1:{} \t test_str2:{}", test_str1,test_str2);


    std::string str2;
    Utils_String::CharArr2String(&str2,buffer, 11);
    // LDebug("str2:{}", str2);
}


