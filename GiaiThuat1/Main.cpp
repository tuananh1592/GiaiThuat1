#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>
#include"Function.h"
using namespace std;

bool isPrime(int n)
{
    //loop from 2 to n/2 to check for factors
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0 || n!=0 )     //found a factor that isn't 1 or n, therefore not prime
            return false;
    }

    return true;
}
//given a number n, find the next closest prime number above n
int findNextPrime(int n)
{
    int Prime = n;
    bool found = false;

    int APrime = 0, BPrime = 0;
    //loop continuously until isPrime returns true for a number above n
    while (!found)
    {
        Prime++;
        if (isPrime(Prime)) {
            found = true;
            APrime = Prime;
        }
    }
    
    found = false;
    Prime = n;
    while (!found)
    {
        Prime--;
        if (isPrime(Prime)) {
            found = true;
            BPrime = Prime;
        }
    }
    int APrimeN = 0, BPrimeN = 0;
    APrimeN = APrime - n;
    BPrimeN = n - BPrime;
    int ans;
    if (APrimeN > BPrimeN) return BPrime;
    if (APrimeN < BPrimeN) return APrime;
    else return APrime;
}



int main() {
    
   return 0;
}
