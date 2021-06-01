#include "cabeceraUDP.h"

//Constructor y destructor
UDP::UDP(size_t bit)
{
    this->bitAcumulador = bit;
}

UDP::~UDP() { }

//Conversiones
string UDP::toBinary(const vector<unsigned char>& bytes)
{
    string binary;
    for(size_t i = 0; i < bytes.size(); i++)
    {
        for(int j = 7; j >= 0; j--)
        {
            binary += ((bytes.at(i) & (1 << j)) ? '1' : '0');
        }
    }
    return binary;
}

int UDP::binaryToDecimal(const string& number)
{
    int total;
    total = stoull(number, 0, 2);
    return total;
}

//Valores de los puertos
void UDP::setSourcePortService(int port_value)
{
    if (port_value >= 0 && port_value <= 1023)
    {
        cout << "Puerto bien conocido" << " - ";

        if (port_value == 20)
        {
            source_port_service = "FTP";
            cout << source_port_service << endl;
        }

        if (port_value == 21)
        {
            source_port_service = "FTP";
            cout << source_port_service << endl;
        }

        if (port_value == 22)
        {
            source_port_service = "SSH";
            cout << source_port_service << endl;
        }

        if (port_value == 23)
        {
            source_port_service = "TELNET";
            cout << source_port_service << endl;
        }

        if (port_value == 25)
        {
            source_port_service = "SMTP";
            cout << source_port_service << endl;
        }

        if (port_value == 53)
        {
            source_port_service = "DNS";
            cout << source_port_service << endl;
        }

        if (port_value == 67)
        {
            source_port_service = "DHCP";
            cout << source_port_service << endl;
        }

        if (port_value == 68)
        {
            source_port_service = "DHCP";
            cout << source_port_service << endl;
        }

        if (port_value == 69)
        {
            source_port_service = "TFTP";
            cout << source_port_service << endl;
        }

        if (port_value == 80)
        {
            source_port_service = "HTTP";
            cout << source_port_service << endl;
        }

        if (port_value == 110)
        {
            source_port_service = "POP3";
            cout << source_port_service << endl;
        }

        if (port_value == 143)
        {
            source_port_service = "IMAP";
            cout << source_port_service << endl;
        }

        if (port_value == 443)
        {
            source_port_service = "HTTPS";
            cout << source_port_service << endl;
        }

        if (port_value == 993)
        {
            source_port_service = "IMAP SSL";
            cout << source_port_service << endl;
        }

        if (port_value == 995)
        {
            source_port_service = "POP SSL";
            cout << source_port_service << endl;
        }
    }

    if (port_value >= 1024 && port_value <= 49151)
    {
        cout << "Puerto registrado" << endl;
    }

    if (port_value >= 49152 && port_value <= 65535)
    {
        cout << "Puerto dinamico o privado" << endl;
    }
}

void UDP::setDestinationPortService(int port_value)
{
    if (port_value >= 0 && port_value <= 1023)
    {
        cout << "Puerto bien conocido" << " - ";

        if (port_value == 20)
        {
            destination_port_service = "FTP";
            cout << destination_port_service << endl;
        }

        if (port_value == 21)
        {
            destination_port_service = "FTP";
            cout << destination_port_service << endl;
        }

        if (port_value == 22)
        {
            destination_port_service = "SSH";
            cout << destination_port_service << endl;
        }

        if (port_value == 23)
        {
            destination_port_service = "TELNET";
            cout << destination_port_service << endl;
        }

        if (port_value == 25)
        {
            destination_port_service = "SMTP";
            cout << destination_port_service << endl;
        }

        if (port_value == 53)
        {
            destination_port_service = "DNS";
            cout << destination_port_service << endl;
        }

        if (port_value == 67)
        {
            destination_port_service = "DHCP";
            cout << destination_port_service << endl;
        }

        if (port_value == 68)
        {
            destination_port_service = "DHCP";
            cout << destination_port_service << endl;
        }

        if (port_value == 69)
        {
            destination_port_service = "TFTP";
            cout << destination_port_service << endl;
        }

        if (port_value == 80)
        {
            destination_port_service = "HTTP";
            cout << destination_port_service << endl;
        }

        if (port_value == 110)
        {
            destination_port_service = "POP3";
            cout << destination_port_service << endl;
        }

        if (port_value == 143)
        {
            destination_port_service = "IMAP";
            cout << destination_port_service << endl;
        }

        if (port_value == 443)
        {
            destination_port_service = "HTTPS";
            cout << destination_port_service << endl;
        }

        if (port_value == 993)
        {
            destination_port_service = "IMAP SSL";
            cout << destination_port_service << endl;
        }

        if (port_value == 995)
        {
            destination_port_service = "POP SSL";
            cout << destination_port_service << endl;
        }
    }

    if (port_value >= 1024 && port_value <= 49151)
    {
        cout << "Puerto registrado" << endl;
    }

    if (port_value >= 49152 && port_value <= 65535)
    {
        cout << "Puerto dinamico o privado" << endl;
    }
}

//Procedimiento
void UDP::setUDPHeader(const string& data)
{
    int bit = bitAcumulador;
    bitAcumulador = bitAcumulador-1;
    string aux;

    //Puerto de origen - 16 bits - Decimal
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    source_port = binaryToDecimal(aux);
    aux.clear();

    //Puerto de destino - 16 bits - Decimal
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    destination_port = binaryToDecimal(aux);
    aux.clear();

    //Longitud total - 16 bits - Decimal
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }
    
    length = binaryToDecimal(aux);
    aux.clear();

    //Suma de comprobacion - 16 bits - Hexadecimal
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    checksum = binaryToDecimal(aux);
}

void UDP::showUDPHeader()
{
    cout << "\n ***Cabecera UDP***" << endl;
    cout << "Puerto de origen: " << source_port << " - ";
    setSourcePortService(source_port);
    cout << "Puerto de destino: " << destination_port << " - ";
    setDestinationPortService(destination_port);
    cout << "Longitud total: " << length << " bytes" << endl;
    printf("Suma de verificacion: %02X\n", checksum);
}

string UDP::getDestinationPort()
{
    return destination_port_service;
}

string UDP::getSourcePort()
{
    return source_port_service;
}