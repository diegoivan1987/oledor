#ifndef CABECERAICMPV4_H
#define CABECERAICMPV4_H

#include <iostream>
#include <vector>

using namespace std;

class CabeceraICMPv4
{
private:
    int type;
    int code;
    int checksum;

public:
    CabeceraICMPv4();
    ~CabeceraICMPv4();

    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    void setICMPv4Header(string data);
    string messageType(int type);
    void showICMPv4Header();
};

#endif // CABECERAICMPV4_H