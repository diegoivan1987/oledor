#ifndef UDP_H
#define UDP_H

#include <iostream>
#include <vector>

using namespace std;

class UDP
{
private:
    int source_port;
    string source_port_service;
    int destination_port;
    string destination_port_service;
    int length;
    int checksum;
    size_t bitAcumulador;
public:
    UDP(size_t bit);
    ~UDP();
    string toBinary(const vector<unsigned char>& bytes);
    int binaryToDecimal(const string& number);
    void setUDPHeader(const string& data);
    void setSourcePortService(int port_value);
    void setDestinationPortService(int port_value);
    void showUDPHeader();
    string getSourcePort();
    string getDestinationPort();
};

#endif // UDP_H