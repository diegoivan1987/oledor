#include "cabeceraTCP.h"

//constructor y destructor
TCP::TCP() { }

TCP::~TCP() { }

//Conversiones
string TCP::toBinary(vector<unsigned char> bytes)
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

int TCP::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

long long TCP::binaryToLong(string number)
{
    long long total;
    total = stoull(number, 0, 2); 
    return total;
}

//Valores de los puertos
void TCP::setSourcePortService(int port_value)
{
    if (port_value >= 0 && port_value <= 1023)
    {
        cout << "Puerto bien conocido" << " - " << endl;

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

void TCP::setDestinationPortService(int port_value)
{
    if (port_value >= 0 && port_value <= 1023)
    {
        cout << "Puerto bien conocido" << " - " << endl;

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
void TCP::setTCPHeader(string data)
{
    //La cabecera comienza en el bit 272
    int bit = 272;
    string aux;

    //Puerto de origen - 16 bits - Decimal
    for (size_t i = bit; i <= 287; i++)
    {
        aux += data[i];
        bit++;
    }

    source_port = binaryToLong(aux);
    aux.clear();

    //Puerto de destino - 16 bits - Decimal
    for (size_t i = bit; i <= 303; i++)
    {
        aux += data[i];
        bit++;
    }
    
    destination_port = binaryToLong(aux);
    aux.clear();

    //Numero de secuencia - 32 bita - Decimal
    for (size_t i = bit; i <= 335; i++)
    {
        aux += data[i];
        bit++;
    }

    sequence_number = binaryToLong(aux);
    aux.clear();

    //Numero de acuse de recibo - 32 bits - Decimal
    for (size_t i = bit; i <= 367; i++)
    {
        aux += data[i];
        bit++;
    }

    acknowledgment_number = binaryToLong(aux);
    aux.clear();
}

void TCP::showTCPHeader()
{
    cout << "       Cabecera TCP" << endl;
    cout << "Puerto de origen: " << source_port << " - ";
    setSourcePortService(source_port);
    cout << "Puerto de destino: " << destination_port << " - ";
    setDestinationPortService(destination_port);
    cout << "Numero de secuencia: " << sequence_number << endl;
    cout << "Numero de acuse de recibo: " << acknowledgment_number << endl;
}