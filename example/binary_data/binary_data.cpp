#include <base64/base64.hpp>

#include <algorithm>

#include <ctime>

#include <cassert>

std::vector<uint8_t> generate_data(const size_t& size)
{
    std::vector<uint8_t> data(size);
    std::generate(data.begin(), data.end(), rand);
    return data; 
}

int main(void)
{
    /// Seed the random number generator
    srand(static_cast<uint32_t>(time(0)));

    auto data = generate_data(4096);

    /// Create the base64 encoded string 
    auto encoded = base64::encode(data);


    /// Decode the string as a string
    auto decoded = base64::decode(encoded);

    // check that encoded and decoded is not the same
    assert(encoded != decoded);
    
    /// Create the vector
    std::vector<uint8_t> out_data(decoded.begin(), decoded.end()); 

    /// Validate that data is the same 
    assert(data == out_data); 

    return 0; 
}
