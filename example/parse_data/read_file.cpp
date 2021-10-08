#include <base64/base64.hpp>

#include <string>

#include <fstream>
#include <filesystem>

#include <cassert>
int main(void)
{
    const std::string path = "./example/parse_data/ruby_data.bin";

    std::string data = "testkjadlskjflkasjfwe08u185u12w3oqew,dmf.smxa";

    std::ifstream in(path, std::ios::binary);
    size_t size = std::filesystem::file_size(path);

    std::string encoded(size, '0');
    in.read(encoded.data(), size);

    auto decoded = base64::decode(encoded);
  
    assert(data == decoded);
}

