#ifndef DNS_H
#define DNS_H

#include <iostream>
#include <vector>

using namespace std;

class DNS
{
private:
    size_t bitAcumulador;
    int id;
    int QR;
    int op_code;
    int AA;
    int TC;
    int RD;
    int RA;
    int Z;
    int rCode;
    unsigned int QDCount;
    unsigned int ANCount;
    unsigned int NSCount;
    unsigned int ARCount;
    int Qtype;
public:
    DNS(size_t bit);
    ~DNS();
    string toBinary(const vector<unsigned char>& bytes);
    int binaryToDecimal(const string& number);
    void setDNSHeader(const string& data, const vector<unsigned char>& domain_name);
    void showDNSHeader(const vector<unsigned char>& domain_name);
};

#endif // DNS_H