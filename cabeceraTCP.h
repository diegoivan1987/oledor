#ifndef TCP_H
#define TCP_H

#include <iostream>
#include <vector>

using namespace std;

class TCP
{
private:
    long long source_port;
    string source_port_service;
    long long destination_port;
    string destination_port_service;
    long long sequence_number;
    int acknowledgment_number;
    int offset;
    int reserved;
    int NS_flag;
    int CWR_flag;
    int ECE_flag;
    int URG_flag;
    int ACK_flag;
    int PSH_flag;
    int RST_flag;
    int SYN_flag;
    int FIN_flag;
    int window_size;
    int checksum;
    int urgent_pointer;

public:
    TCP();
    ~TCP();
    string toBinary(vector<unsigned char> bytes);
    int binaryToDecimal(string number);
    long long binaryToLong(string number);
    void setTCPHeader(string data);
    void setSourcePortService(int port_value);
    void setDestinationPortService(int port_value);
    void showTCPHeader();
};

#endif // TCP_H