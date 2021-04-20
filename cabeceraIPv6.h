#ifndef IPV6_H
#define IPV6_H

#include <iostream>
#include <vector>

using namespace std;

class IPv6
{
private:
    int version;
    int traffic_class;
    int flow_label;
    int payload_length;
    int next_header;
    int hop_limit;
    int source_address[16];
    int destination_address[16];
public:
    IPv6();
    ~IPv6();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    void setIPv6Header(string data);
    void showIPv6Header();
};

#endif // IPV6_H