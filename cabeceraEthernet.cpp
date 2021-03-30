#include "CabeceraEthernet.h"

void CabeceraEthernet::setCabecera(vector<unsigned char> bytes)
{
    size_t i;

    for(i = 0; i < 6; i++)
    {
        dirDestino.push_back(bytes.at(i));
    }
    for(i = i; i < 12; i++)
    {
        dirOrigen.push_back(bytes.at(i));
    }
    for(i = i; i < 14; i++)
    {
        tipo_long.push_back(bytes.at(i));
    }
}

void CabeceraEthernet::mostrarCampo(vector<unsigned char> campo)
{
    if (campo.size() == 6) //Para mostrar las direcciones en Ethernet
    {
        for(size_t i = 0; i < campo.size(); i++)
        {
            if (i == 5)
            {
                printf("%02X", campo.at(i));
            }
            else
            {
                printf("%02X:", campo.at(i));
            }
        }
        printf("\n");
    }
    else
    {
        for (size_t i = 0; i < campo.size(); i++)
        {
            printf("%02X", campo.at(i));
        }
    }
}

void CabeceraEthernet::setTipo(vector<unsigned char> campo)
{
    if(campo.at(0) == 8)
    {
        if(campo.at(1) == 0)
        {
            tipo = "IPv4";
        }
        else if(campo.at(1) == 6)
        {
            tipo = "ARP";
        }
    }
    else if(campo.at(0) == 128)
    {
        tipo = "RARP";
    }
    else if(campo.at(0) == 134)
    {
        tipo = "IPv6";
    }
}

vector<unsigned char> CabeceraEthernet::getDirDestino()
{
    return dirDestino;
}

vector<unsigned char> CabeceraEthernet::getDirOrigen()
{
    return dirOrigen;
}

vector<unsigned char> CabeceraEthernet::getTipo_Long()
{
    return tipo_long;
}

string CabeceraEthernet::getTipo()
{
    return tipo;
}

