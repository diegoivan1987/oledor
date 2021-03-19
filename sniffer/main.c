#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {

    setlocale(LC_CTYPE, "spanish");

    FILE *f1;   //Archivo que se va a leer
    unsigned char numero; //Variable que almacenará los valores a imprimir en pantalla
    int i = 1; //Contador para separar los campos del frame
    unsigned char tipo[2]; //Este array contiene el tipo de frame7
    unsigned char fragmento[13]; //Array para la posicion de fragmento
    int total_length = 0; //Acumulador para la longitud total
    int identifier = 0; //Acumulador para el identificador
    unsigned char aux; //Caracter auxiliar

    //Abrimos el archivo para lectura y checamos si se abrió correctamente.
    //Se debe colocar la ruta completa del archivo
    if ((f1 = fopen("ethernet_ipv4_udp_dns.bin", "rb")) == NULL)
    {
        printf("Error al abrir el archivo. \n");
    }
    else
    {
        //Se leen los datos hasta el final del archivo
        while (!feof(f1))
        {
            numero = fgetc(f1);
            if (i == 1) //Primer byte
            {
                printf("Direccion MAC de destino: ");
                printf("%02X:", numero);
            }

            if (i > 1 && i < 6) //Bytes 2 a 5
            {
                printf("%02X:", numero);
            }

            if (i == 6) //Byte 6. Hasta aquí es la dirección MAC de destino.
            {
                printf("%02X", numero);
            }

            if (i == 7) //Byte 7
            {
                printf("\nDireccion MAC de origen:  ");
                printf("%02X:", numero);
            }

            if (i > 7 && i < 12) //Bytes 8 a 11
            {
                printf("%02X:", numero);
            }

            if (i == 12) //Byte 12 Hasta aquí es la dirección MAC de origen.
            {
                printf("%02X", numero);
            }

            if (i == 13) //Byte 13
            {
                printf("\nTipo de frame:            ");
                printf("%02X", numero);
                tipo[0] = numero;
            }

            if (i == 14) //Byte 14 Hasta aquí es el tipo de frame.
            {
                printf("%02X", numero);
                tipo[1] = numero;

                //Se checa que tipo de frame es
                if (tipo[0] == 8 && tipo[1] == 6)
                {
                    printf(" - ARP\n");
                }

                if (tipo[0] == 8 && tipo[1] == 0)
                {
                    printf(" - IPv4\n");
                }

                if (tipo[0] == 128 && tipo[1] == 53) //Se utilizan valores decimales para hacer la comparación
                {
                    printf(" - RARP\n");
                }

                if (tipo[0] == 134 && tipo[1] == 221)
                {
                    printf(" - IPv6\n");
                }

            }

//           Analisis de paquete IPv4
//------------------------------------------------------------------------

            if (i == 15 && (tipo[0] == 8 && tipo[1] == 0)) //Si el frame esde tipo IPv4
            {
                //Se menciona la version del protocolo
                // Se convuerte el byte 15 a un array de bits
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                if (buffer[0] == '0' && buffer[1] == '1' && buffer[2] == '0' && buffer[3] == '0') // Se checa si es IPv4
                {
                    printf("\nVersion del protocolo:   Version 4 (IPv4)\n");
                }

                //Se menciona el tamaño de la cabecera
                int header_size[4];

                //Se copian los contenidos del buffer a otros array para hacer la conversión a decimal
                for (int a = 0; a < 4; a++)
                {
                    header_size[a] = buffer[a+4] - '0';
                }

                //Se convierte de binario a decimal
                int cabecera = 0, potencia = 1;

                for (int a = 0; a < 4; a++)
                {
                    cabecera += header_size[3-a]*potencia;
                    potencia *= 2;
                }

                printf("Longitud de la cabecera: %d\n", cabecera);

            }

            if (i == 16) // Tipo de servicio
            {
                //Se convierte el caracter a binario
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                printf("Tipo de urgencia:        ");

                //Tipo de urgencia
                if (buffer[0] == '0' && buffer[1] == '0' && buffer[2] == '0')
                {
                    printf("De rutina\n");
                }

                if (buffer[0] == '0' && buffer[1] == '0' && buffer[2] == '1')
                {
                    printf("Prioritario\n");
                }

                if (buffer[0] == '0' && buffer[1] == '1' && buffer[2] == '0')
                {
                    printf("Inmediato\n");
                }

                if (buffer[0] == '0' && buffer[1] == '1' && buffer[2] == '1')
                {
                    printf("Relampago\n");
                }

                if (buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '0')
                {
                    printf("Invalidacion relampago\n");
                }

                if (buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '1')
                {
                    printf("Procesando llamada critica y de emergencia\n");
                }

                if (buffer[0] == '1' && buffer[1] == '1' && buffer[2] == '0')
                {
                    printf("Control de trabajo de internet\n");
                }

                if (buffer[0] == '1' && buffer[1] == '1' && buffer[2] == '1')
                {
                    printf("Control de la red\n");
                }

                printf("\nCaracteristicas del servicio\n");

                //Características del servicio

                if (buffer[3] == '0')
                {
                    printf("Retardo:     Normal\n");
                }

                if (buffer[3] == '1')
                {
                    printf("Retardo:     Alto\n");
                }

                if (buffer[4] == '0')
                {
                    printf("Rendimiento: Normal\n");
                }

                if (buffer[4] == '1')
                {
                    printf("Rendimiento: Alto\n");
                }

                if (buffer[5] == '0')
                {
                    printf("Fiabilidad:  Normal\n");
                }

                if (buffer[5] == '1')
                {
                    printf("Fiabilidad:  Alta\n");
                }

            }

            if (i == 17) // Longitud Total
            {
                aux = numero;
            }

            if (i == 18) //Continuación de longitud totañ
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (aux & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                unsigned char buffer_2[8];
                len = 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer_2[len++] = (numero & mask) ? '1' : '0';
                }
                buffer_2[len++] = '\0';

                unsigned char final_buffer[16];
                int index = 0;

                for (int a = 0; a < 8; a++)
                {
                    final_buffer[index] = buffer[a];
                    index++;
                }

                for (int a = 0; a < 8; a++)
                {
                    final_buffer[index] = buffer_2[a];
                    index++;
                }

                final_buffer[0] = '1';

                int length[16];

                for (int a = 0; a < 16; a++)
                {
                    length[a] = final_buffer[a] - '0';
                }

                //Se convierte de binario a decimal
                int potencia = 1;

                for (int a = 0; a < 16; a++)
                {
                    total_length += length[15-a]*potencia;
                    potencia *= 2;
                }

                printf("\nLongitud total: %d\n", total_length);
            }

            if (i == 19) // Indentificador
            {
                aux = numero;
            }

            if (i == 20)
            {
                unsigned char buffer[8], len= 0;
                unsigned char buffer_2[8];
                unsigned char final_buffer[16];

                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (aux & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                len = 0;

                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer_2[len++] = (numero & mask) ? '1' : '0';
                }
                buffer_2[len++] = '\0';

                int index = 0;

                for (int a = 0; a < 8; a++)
                {
                    final_buffer[index] = buffer[a];
                    index++;
                }

                for (int a = 0; a < 8; a++)
                {
                    final_buffer[index] = buffer_2[a];
                    index++;
                }

                int length[16];
                final_buffer[0] = '0';

                for (int a = 0; a < 16; a++)
                {
                    length[a] = final_buffer[a] - '0';
                }

                //Se convierte de binario a decimal
                int potencia = 1;

                for (int a = 0; a < 16; a++)
                {
                    identifier += length[15-a]*potencia;
                    potencia *= 2;
                }

                printf("Identificador:  %d\n", identifier);
            }

            if (i == 21) // Banderas
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                printf("\nBanderas:\n");

                if (buffer[1] == '0')
                {
                    printf("Fragmento divisible\n");
                }

                if (buffer[1] == '1')
                {
                    printf("Fragmento no divisible\n");
                }

                if (buffer[2] == '0')
                {
                    printf("Ultimo fragmento\n");
                }

                if (buffer[2] == '1')
                {
                    printf("Fragmento intermedio\n");
                }

                for (int a = 3; a < 8; a++)
                {
                    fragmento[a-3] = buffer[a];
                }

            }

            if (i == 22) //Posicion del fragmento
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                for (int a = 5; a < 13; a++)
                {
                    fragmento[a] = buffer[a-5];
                }

                int final_fragment[13];

                for (int a = 0; a < 13; a++)
                {
                    final_fragment[a] = fragmento[a] - '0';
                }

                int fragment_size = 0, potencia = 1;

                for (int a = 0; a < 13; a++)
                {
                    fragment_size += final_fragment[12-a]*potencia;
                    potencia *= 2;
                }

                printf("\nPosicion del fragmento:     %d\n", fragment_size);
            }

            if (i == 23) //Tiempo de vida
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int life_span_array[8];

                for (int a = 0; a < 8; a++)
                {
                    life_span_array[a] = buffer[a] - '0';
                }

                int life_span = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    life_span += life_span_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("Tiempo de vida:             %d\n", life_span);
            }

            if (i == 24) //Protocolo de capas superiores
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int upper_protocol_array[8];

                for (int a = 0; a < 8; a++)
                {
                    upper_protocol_array[a] = buffer[a] - '0';
                }

                int upper_protocol = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    upper_protocol += upper_protocol_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("Protocolo de capa superior: ");

                switch (upper_protocol)
                {
                case 1:
                    printf("ICMPv4\n");
                    break;

                case 6:
                    printf("TCP\n");
                    break;

                case 17:
                    printf("UDP\n");
                    break;

                case 58:
                    printf("ICMPv6\n");
                    break;

                case 118:
                    printf("STP\n");
                    break;

                case 121:
                    printf("SMP\n");
                    break;

                default:
                    break;
                }
            }

            if (i == 25) //Checksum
            {
                printf("\nSuma de control de cabecera: %02X", numero);
            }

            if (i == 26)
            {
                printf("%02X\n", numero);
            }

            if (i == 27) //Direccion de origen
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int source_array[8];

                for (int a = 0; a < 8; a++)
                {
                    source_array[a] = buffer[a] - '0';
                }

                int source_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    source_address += source_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("Direccion IP de origen:      %d.", source_address);
            }

            if (i > 27 && i < 30)
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int source_array[8];

                for (int a = 0; a < 8; a++)
                {
                    source_array[a] = buffer[a] - '0';
                }

                int source_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    source_address += source_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("%d.", source_address);
            }

            if (i == 30)
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int source_array[8];

                for (int a = 0; a < 8; a++)
                {
                    source_array[a] = buffer[a] - '0';
                }

                int source_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    source_address += source_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("%d\n", source_address);
            }

            if (i == 31) //Direccion de destino
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int destination_array[8];

                for (int a = 0; a < 8; a++)
                {
                    destination_array[a] = buffer[a] - '0';
                }

                int destination_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    destination_address += destination_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("Direccion IP de destino:     %d.", destination_address);
            }

            if (i > 31 && i < 34)
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int destination_array[8];

                for (int a = 0; a < 8; a++)
                {
                    destination_array[a] = buffer[a] - '0';
                }

                int destination_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    destination_address += destination_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("%d.", destination_address);
            }

            if (i == 34)
            {
                unsigned char buffer[8], len= 0;
                for (long mask = 0x80; mask > 0; mask >>= 1)
                {
                    buffer[len++] = (numero & mask) ? '1' : '0';
                }
                buffer[len++] = '\0';

                int destination_array[8];

                for (int a = 0; a < 8; a++)
                {
                    destination_array[a] = buffer[a] - '0';
                }

                int destination_address = 0, potencia = 1;

                for (int a = 0; a < 8; a++)
                {
                    destination_address += destination_array[7-a]*potencia;
                    potencia *= 2;
                }

                printf("%d\n", destination_address);
            }

            i++;

        }

        fclose(f1);
        system("pause");
    }

    return 0;
}
