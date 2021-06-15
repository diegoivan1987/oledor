#include "ICMPv4.h"

ICMPv4::ICMPv4()
{

}

void ICMPv4::setICMPv4(string bin)
{
    size_t bit = 272;
    CabeceraIPv4 convertir;
    //Despues de la cabecera IPv4 se queda en el bit 272
     string tipoS, codigoS, checksumS;

    //Tipo 8 bits, decimal
    for(size_t i = bit; i <= 279; i++){
        tipoS += bin[i];
        bit++;
    }
    tipo = convertir.binToDecimal(tipoS);
    //Codigo 8 bits, decimal
    for(size_t i = bit; i <= 287; i++){
        codigoS += bin[i];
        bit++;
    }
    codigo = convertir.binToDecimal(codigoS);
    //Checksum 16 bits, decimal
    for(size_t i = bit; i <= 303; i++){
        checksumS += bin[i];
        bit++;
    }
    checksum = convertir.binToDecimal(checksumS);
}

void ICMPv4::mostrarICMPv4()
{
    cout << endl <<         "***ICMPv4***" << endl;
    cout << "       Mensaje Informativo: ";
    setMensajeInformativo(tipo);
    cout << "       Mensaje de error: ";
    setMensajeError(codigo);
    printf("        Checksum: %02X", checksum);
}

void ICMPv4::setMensajeInformativo(int tipo)
{
    switch(tipo){
        case 0: cout << "       Echo Reply (Respuesta de eco)" << endl; break;
        case 3: cout << "       Destination Unreacheable (destino inaccesible)" << endl; break;
        case 4: cout << "       Source Quench (disminuci�n del tr�fico desde el origen)" << endl; break;
        case 5: cout << "       Redirect (redireccionar - cambio de ruta)" << endl; break;
        case 8: cout << "       Echo (solicitud de eco)" << endl; break;
        case 11: cout << "      Time Exceeded (tiempo excedido para un datagrama)" << endl; break;
        case 12: cout << "      Parameter Problem (problema de par�metros)" << endl; break;
        case 13: cout << "      Timestamp (solicitud de marca de tiempo)" << endl; break;
        case 14: cout << "      Timestamp Reply (respuesta de marca de tiempo)" << endl; break;
        case 15: cout << "      Information Request (solicitud de informaci�n) - obsoleto-" << endl; break;
        case 16: cout << "      Information Reply (respuesta de informaci�n) - obsoleto-" << endl; break;
        case 17: cout << "      Addressmask (solicitud de m�scara de direcci�n)" << endl; break;
        case 18: cout << "      Addressmask Reply (respuesta de m�scara de direcci�n)" << endl; break;
        default : cout << "     Numero erroneo." << endl;
    }
}

void ICMPv4::setMensajeError(int codigo)
{
    switch(codigo){
        case 0: cout << "       no se puede llegar a la red" << endl; break;
        case 1: cout << "       no se puede llegar al host o aplicaci�n de destino" << endl; break;
        case 2: cout << "       el destino no dispone del protocolo solicitado" << endl; break;
        case 3: cout << "       no se puede llegar al puerto destino o la aplicaci�n destino no est� libre" << endl; break;
        case 4: cout << "       se necesita aplicar fragmentaci�n, pero el flag correspondiente indica lo contrario" << endl; break;
        case 5: cout << "       la ruta de origen no es correcta" << endl; break;
        case 6: cout << "       no se conoce la red destino" << endl; break;
        case 7: cout << "       no se conoce el host destino" << endl; break;
        case 8: cout << "       el host origen est� aislado" << endl; break;
        case 9: cout << "       la comunicaci�n con la red destino est� prohibida por razones administrativas" << endl; break;
        case 10: cout << "      la comunicaci�n con el host destino est� prohibida por razones administrativas" << endl; break;
        case 11: cout << "      no se puede llegar a la red destino debido al Tipo de servicio" << endl; break;
        case 12: cout << "      no se puede llegar al host destino debido al Tipo de servicio" << endl; break;
        default: cout << "      Numero erroneo." << endl;
    }
}



