#ifndef IPV6_H
#define IPV6_H

#include <iostream>
#include <vector>

using namespace std;

class IPv6
{
private:
    int version;
    string traffic_class;
    int flow_label;
    unsigned int payload_length;
    int next_header;
    unsigned int hop_limit;
    int source_address[16];
    int destination_address[16];
    int size;
public:
    IPv6();
    ~IPv6();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    string trafficClassPriority(string bits);
    void trafficClassFeatures(string bits);
    string nextHeader(int next);
    void setIPv6Header(string data);
    void showIPv6Header();
    int getBitSize();
};

#endif // IPV6_H