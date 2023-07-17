#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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


