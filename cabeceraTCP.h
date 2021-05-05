#ifndef TCP_H
#define TCP_H

#include <iostream>
#include <vector>

using namespace std;

class TCP
{
private:
    int source_port;
    string source_port_service;
    int destination_port;
    string destination_port_service;
    int sequence_number;
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
    void setTCPHeader(string data);
    void setSourcePortService(int port_value);
    void showTCPHeader();
};

#endif // TCP_H