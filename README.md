# Base64

Base64 is a header only C++ library that provides support base 64 encode and decode in C++ for `std::string`, `std::vector<uint8_t>`, `std::vector<char>`, `std::array<char, SIZE>`, and `std::array<uint8_t, SIZE>`


# Usage 

```C++
    #include <base64/base64.hpp>
    
    #include <algorithm>
    #include <ctime>
    
    #include <cassert>
    
    int main(void)
    {
        // Seed random
        srand(static_cast<uint32_t>(time(0)));
        
        std::vector<uint8_t> data(4096);
        std::generate(data.begin(), data.end(), rand); 
        
        auto encoded = base64::encode(data); 
        auto decoded = base64::decode(encoded); 
        
        std::vector<uint8_t> out_data(decoded.begin(), decoded.end()); 
        
        assert(data, out_data); 
    }
```
