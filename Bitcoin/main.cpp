#include <iostream>
#include <math.h>
#include <tuple>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/**
 *  Perform modular exponentiation
 */
int mod_pow(int x, int y, int p){
    int result = 1;
    x = x % p;

    while(y > 0){
        if(y & 1){
            result = (result * x) % p;
        }

        y = x >> 1;
        x = (x * x) % p;
    }
    return result;
}

/**
 * Find the modular inverse of a under modulo p, p must be a prime number
 * 
 */
int mod_inv(int a,int p){
    return mod_pow(a, p - 2, p);
}

/**
 * Add two points on an elliptic curve
 */
tuple<int, int> elliptic_curve_add(tuple<int, int> p1, tuple<int, int> p2, int a, int p){
    
    int x1, y1, x2, y2;
    tie(x1, y1) = p1;
    tie(x2, y2) = p2;

    // If a point is (0, 0)
    if (x1 == 0 && y1 == 0) return p2;
    if (x2 == 0 && y2 == 0) return p1;

    int m = 0;
    if (x1 == x2 && y1 == y2) {
        // Use tangent formula 
        m = (3 * x1 * x1 + a) * mod_inv(2 * y1, p) % p;
    } else {
        // Use the line formula for point addition
        m = (y2 - y1) * mod_inv(x2 - x1, p) % p;
    }

    int x3 = (m * m - x1 - x2) % p;
    int y3 = (m * (x1 - x3) - y1) % p;

    if (x3 < 0) x3 += p;
    if (y3 < 0) y3 += p;

    return make_tuple(x3, y3);
}

/**
 * Multiply a point by a scalar on an elliptic curve
 */
tuple<int, int> scalar_multiply(int k, tuple<int, int> point, int a, int p) {
    tuple<int, int> result = make_tuple(0, 0);
    tuple<int, int> addend = point;

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
    cout << ss.str() << '\n'; 

    string private_key = static_cast<int>("%064x" % random_number);

    string G_x = "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F817";
    string G_y = "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17D448A68554199C47D08F4E7D3";
    auto G = (G_x, G_y);
    string p = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F";
    int a = 0;
    int b = 7; 

    string public_key = scalar_multiply(private_key, G, a, p);

    cout << "Your Public Key is " << public_key << '\n';
    cout << "Your Private Key is " << private_key << '\n';
    
    return 0;
}