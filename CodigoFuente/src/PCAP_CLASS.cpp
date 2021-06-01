#include "PCAP_CLASS.h"

PCAP_CLASS::PCAP_CLASS()
{
    //ctor
}


int PCAP_CLASS::workPCAP(int argc, char **argv)
{
    pcap_if_t *alldevs, *d;
	pcap_t *fp;
	u_int inum, i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	printf("pktdump_ex: prints the packets of the network using WinPcap.\n");
	printf("   Usage: pktdump_ex [-s source]\n\n"
		"   Examples:\n"
		"      pktdump_ex -s file.acp\n"
		"      pktdump_ex -s \\Device\\NPF_{C8736017-F3C3-4373-94AC-9A34B7DAD998}\n\n");

	if(argc < 3)
	{
		printf("\nNo adapter selected: printing the device list:\n");
		/* The user didn't provide a packet source: Retrieve the local device list */
		if(pcap_findalldevs(&alldevs, errbuf) == -1)
		{
			fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
			exit(1);
		}

		/* Print the list */
		for(d=alldevs; d; d=d->next)
		{
			printf("%d. %s\n    ", ++i, d->name);

			if (d->description){
				printf(" (%s)\n", d->description);
			}else{
				printf(" (No description available)\n");
			}
		}

		if (i==0)
		{
			printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
			return -1;
		}

		printf("Enter the interface number (1-%d):",i);
		scanf("%d", &inum);

		if (inum < 1 || inum > i)
		{
			printf("\nInterface number out of range.\n");

			/* Free the device list */
			pcap_freealldevs(alldevs);
			return -1;
		}

		/* Jump to the selected adapter */
		for (d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

		/* Open the adapter */
		if ((fp = pcap_open_live(d->name,	// name of the device
			65536,							// portion of the packet to capture.
											// 65536 grants that the whole packet will be captured on all the MACs.
			1,								// promiscuous mode (nonzero means promiscuous)
			1000,							// read timeout
			errbuf							// error buffer
			)) == NULL)
		{
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	}
	else
	{
		/* Do not check for the switch type ('-s') */
		if ((fp = pcap_open_live(argv[2],	// name of the device
			65536,							// portion of the packet to capture.
											// 65536 grants that the whole packet will be captured on all the MACs.
			1,								// promiscuous mode (nonzero means promiscuous)
			1000,							// read timeout
			errbuf							// error buffer
			)) == NULL)
		{
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	}

	/* Read the packets */
	int cont = 0;
	cout << endl << "Leyendo Paquetes..." << endl;
	/***Comente las impresiones de los datos, tienen 5 astediscos -> *****/
	while((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0 && cont != NUM_PACKAGES)
	{

		if(res == 0)
			/* Timeout elapsed */
			continue;

		/* print pkt timestamp and pkt len */
		//*****printf("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len);

		//Agrego un vector al vector de vectores para ingresar los elementos/caracteres
		vector <unsigned char> aux;
        reading.push_back(aux);
		/* Print the packet */
		for (i=1; (i < header->caplen + 1 ) ; i++)
		{
			//******printf("%.2x ", pkt_data[i-1]);
			//Agrego los caracteres al vector que esta dentro del vector, son los campos hexadecimales
			reading.at(cont).push_back(pkt_data[i-1]);

			//*****if ( (i % LINE_LEN) == 0) printf("\n");
		}

		//*****printf("\n\n");
		cont++;
	}

	if(res == -1)
	{
		printf("Error reading the packets: %s\n", pcap_geterr(fp));
		return -1;
	}

	pcap_close(fp);
	return 0;
}

vector<vector<unsigned char>> PCAP_CLASS::getReading()
{
    return reading;
}
