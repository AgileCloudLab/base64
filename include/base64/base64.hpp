#pragma once

#include <string>
#include <cstdint>

#include <vector>
#include <array>

#include <type_traits>

#include <stdexcept>

namespace base64
{
    static const std::array<char, 64> b64chars =
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U','V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
        '8' ,'9', '+', '/'
    };
    
    static const std::array<int, 256> b64index =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 62, 63, 62, 62, 63, 52, 53,
        54, 55, 56, 57, 58, 59, 60, 61, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 2, 3, 4,
        5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 0, 0, 0, 0, 63, 0, 26, 27,
        28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51
    };
  
  
    template<typename T> bool valid_container_type(const T& container)
    {
        (void) container; 
        if constexpr (std::is_same<T, std::vector<uint8_t>>::value)
        {
            return true; 
        }
        else if constexpr (std::is_same<T, std::vector<char>>::value)
        {
            return true; 
        }
        //Find a way to add check for array
        // else if constexpr (std::is_same<T, std::array<uint8_t, container.size()>>::value)
        // {
        //     return true; 
        // }
        // else if constexpr (std::is_same<T, std::array<uint8_t, container.size()>>::value)
        // {
        //     return true; 
        // }                
        else if constexpr (std::is_same<T, std::string>::value)
        {
            return true;
        }     
        return false; 
    }

    template<typename T> const std::string encode(const T& str)
    {

        // if (!valid_container_type(str))
        // {
        //     throw std::invalid_argument("str must be of type std::vector<uint8_t>, std::vector<char>, std::array<uint8_t, size>, std::array<char, size>, or std::string"); 
        // }        
        std::string result(((str.size() + 2) / 3) * 4, '=');

        size_t pad = str.size() % 3;
        size_t j = 0; 

        const size_t last = str.size() - pad;

        for (size_t i = 0; i < last; i = i + 3)
        {
            int n = (int(str.at(i))) << 16 | int(str.at(i + 1) << 8) | str.at(i + 2); 

            result.at(j++) = b64chars.at(n >> 18);
            result.at(j++) = b64chars.at(n >> 12 & 0x3F);
            result.at(j++) = b64chars.at(n >> 6 & 0x3F);
            result.at(j++) = b64chars.at(n & 0x3F);
        }

        if (pad)
        {
            int n = --pad ? int(str.at(last)) << 8 | str.at(last + 1) : str.at(last);
            result.at(j++) = b64chars.at(pad ? n >> 10 & 0x3F : n >> 2);
            result.at(j++) = b64chars.at(pad ? n >> 4 & 0x03F : n << 4 & 0x3F);
            result.at(j++) = pad ? b64chars.at(n << 2 & 0x3F) : '=';
        }
        
        return result; 
    }

    template <typename T> const std::string decode(const T& str)
    {
        // if (!valid_container_type(str))
        // {
        //     throw std::invalid_argument("str must be of type std::vector<uint8_t>, std::vector<char>, std::array<uint8_t, size>, std::array<char, size>, or std::string"); 
        // }
        
        if (str.empty())
        {
            return str; 
        }

        size_t j = 0;
        size_t pad1 = str.size() % 4 || str.at(str.size() - 1) == '=';
        
        size_t pad2 = pad1 && (str.size()  % 4 >> 2 || str.at(str.size() - 2) != '=');

        const size_t last = (str.size() - pad1) / 4 << 2;

        std::string result(last / 4 * 3 + pad1 + pad2, '\0');

        for (size_t i = 0; i < last; i = i + 4)
        {
            int n = b64index.at(str.at(i)) << 18 | b64index.at(str.at(i + 1)) << 12 | b64index.at(str.at(i + 2)) << 6 | b64index.at(str.at(i + 3));
            result.at(j++) = n >> 16;
            result.at(j++) = n >> 8 & 0xFF;
            result.at(j++) = n & 0xFF;             
        }

        if (pad1)
        {
            int n = b64index.at(str.at(last)) << 18 | b64index.at(str.at(last + 1)) << 12;
            result.at(j++) = n >> 16;

            if ( pad2)
            {
                n |= b64index.at(str.at(last + 2)) << 6;
                result.at(j++) = n >> 8 & 0xFF; // Check if j++ is needed (should not be)
            }
        }
        
        return result; 
    }    
  
  
}
