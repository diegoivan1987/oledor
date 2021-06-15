#ifndef ICMPv6_H
#define ICMPv6_H

#include <iostream>
#include <vector>

using namespace std;

class ICMPv6
{
private:
    int type;
    int code;
    int checksum;

public:
    ICMPv6();
    ~ICMPv6();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    void setICMPv6Header(string data);
    void errorType(int type, int code);
    void showICMPv6Header();
};

#endif // ICMPv6_H
