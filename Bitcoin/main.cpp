#include <iostream>
#include <tuple>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

using bigint = cpp_int;

/**
 *  Perform modular exponentiation
 */
bigint mod_pow(bigint x, bigint y, bigint p){
    bigint result = 1;
    x = x % p;

    while(y > 0){
        if(y & 1){
            result = (result * x) % p;
        }

        y >>= 1;
        x = (x * x) % p;
    }
    return result;
}

/**
 * Find the modular inverse of a under modulo p, p must be a prime number
 * 
 */
bigint mod_inv(bigint a, bigint p){
    return mod_pow(a, p - 2, p);
}

/**
 * Add two points on an elliptic curve
 */
tuple<bigint, bigint> elliptic_curve_add(tuple<bigint, bigint> p1, tuple<bigint, bigint> p2, bigint a, bigint p){
    
    bigint x1, y1, x2, y2;
    tie(x1, y1) = p1;
    tie(x2, y2) = p2;

    // If a point is (0, 0)
    if (x1 == 0 && y1 == 0) return p2;
    if (x2 == 0 && y2 == 0) return p1;

    bigint m = 0;
    if (x1 == x2 && y1 == y2) {
        // Use tangent formula 
        m = (3 * x1 * x1 + a) * mod_inv(2 * y1, p) % p;
    } else {
        // Use the line formula for point addition
        m = (y2 - y1) * mod_inv(x2 - x1, p) % p;
    }

    bigint x3 = (m * m - x1 - x2) % p;
    bigint y3 = (m * (x1 - x3) - y1) % p;

    if (x3 < 0) x3 += p;
    if (y3 < 0) y3 += p;

    return make_tuple(x3, y3);
}

/**
 * Multiply a point by a scalar on an elliptic curve
 */
tuple<bigint, bigint> scalar_multiply(bigint k, tuple<bigint, bigint> point, bigint a, bigint p) {
    tuple<bigint, bigint> result = make_tuple(0, 0);
    tuple<bigint, bigint> addend = point;

    while (k > 0) {
        if (k & 1) {
            result = elliptic_curve_add(result, addend, a, p);
        }
        addend = elliptic_curve_add(addend, addend, a, p);
        k >>= 1;
    }
    return result;
}

int main(){
    
    // Generate a random 64-bit hexadecimal string
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis;
    uint64_t random_number = dis(gen);

    stringstream ss;
    ss << hex << setw(16) << setfill('0') << random_number; 
    string private_key_str = ss.str(); 

    bigint private_key = bigint("0x" + private_key_str);

    bigint G_x("0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F817");
    bigint G_y("0x483ADA7726A3C4655DA4FBFC0E1108A8FD17D448A68554199C47D08F4E7D3");
    auto G = make_tuple(G_x, G_y);
    bigint p("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    bigint a = 0;
    bigint b = 7; 

    auto public_key = scalar_multiply(private_key, G, a, p);
    bigint x = get<0>(public_key);
    bigint y = get<1>(public_key);

    string prefix = (y % 2 == 0) ? "02" : "03";
    ss << hex << setw(64) << setfill('0') << x;
    string public_key_str = prefix + ss.str(); 

    cout << "Your Public Key is " << public_key_str << '\n';
    cout << "Your Private Key is " << private_key_str << '\n';
    
    return 0;
}