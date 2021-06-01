#ifndef PCAP_CLASS_H
#define PCAP_CLASS_H
#ifdef _MSC_VER
/*
 * we do not want the warnings about the old deprecated and unsecure CRT functions
 * since these examples can be compiled under *nix as well
 */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <pcap.h>
#include <vector>

#define LINE_LEN 16
#define NUM_PACKAGES 20

using namespace std;

class PCAP_CLASS
{
    private:
        vector<vector<unsigned char>> reading;
    public:
        PCAP_CLASS();
        int workPCAP(int argc, char **argv);
        vector<vector<unsigned char>> getReading();
};

#endif // PCAP_CLASS_H
