#include "utils.h"

#include <random>

TEST_CASE("Test LeastSqure")
{
#if 0
    // y= 0.5x+0.5
    std::vector<int> data_x;
    std::vector<float> data_y;
    float a = 0.5f, b = 0.5f;

    for (int i = 0; i < 10; i++)
    {
        data_x.emplace_back(i);
        data_y.emplace_back(a*i + b);
    }

    float res_a, res_b;

    Utils_Data::LeastSquare(data_x, data_y, res_a, res_b);
    CHECK(res_a == a);
    CHECK(res_b == b);
#endif
}

TEST_CASE("Test Blur")
{
#if 0
    std::vector<float> data;
    for (int i = 0; i < 20; i++)
    {
        data.push_back(rand()%100);
    }

    // Utils_String::CoutVector(data, false);
    std::vector<float> media_res = Utils_Data::MediaBlur(data, 3);
    // Utils_String::CoutVector(media_res,false);
    std::vector<float> mean_res = Utils_Data::MeanBlur(data, 3);
    // Utils_String::CoutVector(mean_res, false);
#endif
}