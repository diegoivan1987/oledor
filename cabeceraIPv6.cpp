#include "cabeceraIPv6.h"

//Constructor y destructor
IPv6::IPv6() { }

IPv6::~IPv6() { }

//Conversiones
string IPv6::toBinary(vector<unsigned char> bytes)
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

int IPv6::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

//Funeciones switch para los distintos atributos
string IPv6::trafficClassPriority(string bits)
{
    if (bits == "000")
    {
        return "De Rutina";
    }

    if (bits == "001")
    {
        return "Prioritario";
    }

    if (bits == "010")
    {
        return "Inmediato";
    }
    
    if (bits == "011")
    {
        return "Relampago";
    }
    
    if (bits == "100")
    {
        return "Invalidacion Relampago";
    }
    
    if (bits == "101")
    {
        return "Procesando llamada critica o de emergencia";
    } 
    
    if (bits == "110")
    {
        return "Control de trabajo de internet";
    }
    
    if (bits == "111")
    {
        return "Control de red";
    }
    else
    {
        return "Prioridad desconocida";
    }
}

void IPv6::trafficClassFeatures(string bits)
{
    if(bits[0] == '0')
    {
        cout << "   -Retardo: Normal" << endl;
    }
    
    if(bits[0] == '1')
    {
        cout <<  "  -Retardo: Bajo" << endl;
    }
    
    if(bits[1] == '0')
    {
        cout << "   -Rendimiento: Normal" << endl;
    }
    
    if(bits[1] == '1')
    {
        cout << "   -Rendimiento: Alto" << endl;
    }

    if(bits[2] == '0')
    {
        cout << "   -Fiabilidad: Normal" << endl;
    }
    
    if(bits[2] == '1')
    {
        cout << "   -Fiabilidad: Alta" << endl;
    }
}

//Procedimiento
void IPv6::setIPv6Header(string data)
{
    //Despues de la cabecera ethernet se queda en el bit 112
    int bit = 112;

    //Version - 4 bits - Decimal
    string ipv6_version;

    for (size_t i = bit; i <= 115; i++)
    {
        ipv6_version += data[i];
        bit++;
    }

    version = binaryToDecimal(ipv6_version);

    //Clase de trafico - 8 bits - Binario
    for (size_t i = bit; i <= 123; i++)
    {
        traffic_class += data[i];
        bit++;
    }
}

void IPv6::showIPv6Header()
{
    cout << "       Cabecera IPv6" << endl;
    cout << "Version: " << version << endl;

    string priority, features;
    for (size_t i = 0; i < traffic_class.size(); i++)
    {
        if (i <= 2)
        {
            priority += traffic_class[i];
        }
        else
        {
            features += traffic_class[i];
        }
    }
    
    cout << "Prioridad: " <<  priority << " - "  << trafficClassPriority(priority) << endl;
    cout << "Caracteristicas del servicio: " << endl;
    trafficClassFeatures(features);
}