#include <base64/base64.hpp>

#include <gtest/gtest.h>

#include <ctime> 
#include <algorithm>
#include <cstring>


TEST(test_base64, test_array)
{
    std::array<uint8_t, 4096> data;
    std::generate(data.begin(), data.end(), rand);

    auto encoded = base64::encode(data);
    
    auto decoded = base64::decode(encoded);

    EXPECT_EQ(data.size(), decoded.size());
    
    std::array<uint8_t, data.size()> out_data;
    std::memcpy(out_data.data(), decoded.data(), decoded.size());
    EXPECT_EQ(data.size(), out_data.size());
    EXPECT_EQ(data, out_data);        
}

TEST(test_base64, test_vector)
{
    std::vector<uint8_t> data(4096);
    std::generate(data.begin(), data.end(), rand);

    auto encoded = base64::encode(data);
    
    auto decoded = base64::decode(encoded);

    EXPECT_EQ(data.size(), decoded.size());
    
    std::vector<uint8_t> out_data(data.size());
    std::memcpy(out_data.data(), decoded.data(), decoded.size());
    EXPECT_EQ(data.size(), out_data.size());
    EXPECT_EQ(data, out_data);        
}

TEST(test_base64, test_string)
{
    std::string data = "testkjadlskjflkasjfwe08u185u12w3oqew,dmf.smxa";    
    auto encoded = base64::encode(data);
    
    auto decoded = base64::decode(encoded);

    EXPECT_EQ(data.size(), decoded.size());
    EXPECT_EQ(data, decoded);        
}

    
int main(int argc, char** argv)
{
    // Seed random number generator
    srand(static_cast<uint32_t>(time(0)));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   
}
