#ifndef ARP_H
#define ARP_H

#include <iostream>
#include <vector>

using namespace std;

class ARP
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
    ARP();
    ~ARP();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    string hardwareType(int type);
    string protocolType(int type);
    void setARPHeader(string data);
    void showARPHeader();
};

#endif // ARP_H