#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include "Decrypt.h"


char convertBase58toDecimal(char x)
{
    // base 58 array
    const std::string base58array = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    int index = base58array.find(x);

    std::cout << index;

    // error handling 
    if (index == std::string::npos)
    {
        std::cout << "Invalid Base58 Character" << std::endl;
        return -1;
    }
    return index;
};

int convertHextoDecimal(char x)
{
    // hex array
    const std::string hexarray = "0123456789ABCDEF";
    int index1 = hexarray.find(x);

    return index1;
}


long long decimalToBase58(long long x)
{
    long long base10{ 0 };
    std::string decimalStr = std::to_string(x);

    for (size_t index = 0; index < decimalStr.length(); ++index)
    {
        char y = decimalStr[index];
        int base58value = convertBase58toDecimal(y);
        long long newsumand = base58value * pow(58, decimalStr.length() - index - 1);
        base10 = base10 + newsumand;
    }
    return base10;
}

long long hexToBase58(char x)
{
    long long base10{ 0 };
    std::string decimalStr = std::to_string(x);

    for (size_t index = 0; index < decimalStr.length(); ++index)
    {
        char y = decimalStr[index];
        int base58value = convertBase58toDecimal(y);
        long long newsumand = base58value * pow(58, decimalStr.length() - index - 1);
        base10 = base10 + newsumand;
    }
    return base10;
}

int mmi(char x, char p) // Modular Multiplicative Inverse
{
    return 0;
}

int main()
{
    // bitcoin wallet 
    std::string public_key{ "1E1eZNRxbNHQNPEraaCZw1YvuXhDCbtEid "};
    std::string private_key{"L5buqNXpTnu7eAUusKnHdW74gyjczV6B77hmTE1DUqnpkVv61ste"};

    // convert bae 58 to decimal
    char base58char = '3';
    int decimalValue = convertBase58toDecimal(base58char);
    if (decimalValue != -1) {
        std::cout << "Decimal value of '" << base58char << "' in Base58: " << decimalValue << std::endl;
    }
    return 0;
}

// Bitcoin ecc protocol
