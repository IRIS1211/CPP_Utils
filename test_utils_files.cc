#include "./utils_files.h"
#include "./utils_string.h"

TEST_CASE("ListAllFiles")
{
#if 0
    std::vector<std::string> res;
    const std::string file_path = "D:\\Code\\Vision\\Camera\\Project\\CBoreHole\\Code\\utils";
    res = Utils_Files::ListAllFiles(file_path);

    CHECK(res.size() > 10);
    // Utils_String::CoutVector(res);
#endif
}

TEST_CASE("ListAllFiles")
{
#if 0
    std::vector<std::string> src;
    src.emplace_back("D:\\Code\\Vision\\Camera\\Project\\CBoreHole\\Code\\utils\\test_utils_files.cc");
    src.emplace_back("D:\\Code\\Vision\\Camera\\Project\\CBoreHole\\Code\\utils\\test_utils_files");
    src.emplace_back("test_utils_files");
    
    std::vector<std::string> res;
    for (const auto& s : src)
    {
        res.emplace_back(Utils_Files::GetFileName(s));
    }

    CHECK(res[0] == "test_utils_files");
    CHECK(res[1] == "test_utils_files");
    CHECK(res[2] == "test_utils_files");
#endif
}