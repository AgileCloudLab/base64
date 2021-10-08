#include <base64/base64.hpp>

#include <string>

#include <fstream>

#include <cassert>

int main(void)
{

    std::string data = "testkjadlskjflkasjfwe08u185u12w3oqew,dmf.smxa";
    auto encoded = base64::encode(data);
    
    std::ofstream out("./example/cpp_data.bin"); 
    out << encoded;
    out.close(); 
    
    auto decoded = base64::decode(encoded);
    assert(data == decoded);
}

