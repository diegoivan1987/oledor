#ifndef RARP_H
#define RARP_H

#include <iostream>
#include <vector>

using namespace std;

class RARP
{
private:
    int hardware_type;
    int protocol_type;
    int hardware_address_length;
    int protocol_address_length;
    int opcode;
    int mac_source[6];
    int mac_destination[6];
    int ip_source[4];
    int ip_destination[4];

public:
    RARP();
    ~RARP();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    string hardwareType(int type);
    string protocolType(int type);
    string opCode(int type);
    void setRARPHeader(string data);
    void showRARPHeader();
};

#endif // RARP_H
