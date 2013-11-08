#include <stdio.h>

void calculo_paquetes(void);
void paquete_a_binario(void);
void print_byte(int);
void usage(void);

char paquete_recv[9];

typedef struct {
  int src;
  int dst;
  int type;
  int pos;
  int vel;
  int gotoexit;
  int flags;
  int ack;
  int nack;
} sac_datagram;

sac_datagram input_datagram;

void main(int argc, char **argv)
{
	int opt=0;
	int sw=0;
	int i;
	char *r_string;

	if (argc > 1) opt=atoi(argv[1]);
	if (argc >= 3) strcpy(paquete_recv, argv[2]);

	switch (opt)
	{
		case 1:
			paquete_a_binario();
			break;
		case 2:
			calculo_paquetes();
			break;
		default:
			usage();
			break;
	}
}

void usage()
{
	printf("Uso:\n");
	printf("./decodifica {1 <paquete HEX> | 2}");
	printf(" 1.- Conversión de un paquete a binario\n");
	printf(" 2.- Cálculo de paquetes en función de parámetros\n");
}

/***********************************************************************************
* HSSSDDDP HHTppppP HHVVGGGP PPPPPPPPP
*
* H=Header  D=Destination  T=Type      V=Speed
* S=Source  P=Parity       p=Position  G=Goto Exit
***********************************************************************************/

void calculo_paquetes()
{
	int datagram[]={0,0,0,0};
	int temp;
	int i,j;

	printf ("Introduce parámetros\n");
	printf ("Source: ");
	scanf("%x", &input_datagram.src);
	printf ("Dest  : ");
	scanf("%x", &input_datagram.dst);
	printf ("Type  : ");
	scanf("%x", &input_datagram.type);
	printf ("Pos   : ");
	scanf("%x", &input_datagram.pos);
	printf ("Speed : ");
	scanf("%x", &input_datagram.vel);
	printf ("Goto  : ");
	scanf("%x", &input_datagram.gotoexit);

	//Generación del primer byte
	datagram[0]|=(input_datagram.src & 0x07) << 4;
	datagram[0]|=(input_datagram.dst & 0x07) << 1;
	datagram[0]|=calcula_paridad_byte(datagram[0]);
	
	//Generación del segundo byte
	datagram[1]=0x80; //Header
	datagram[1]|=(input_datagram.type & 0x01) << 5;
	datagram[1]|=(input_datagram.pos & 0x0F) << 1;
	datagram[1]|=calcula_paridad_byte(datagram[1]);
	
	//Generación del tercer byte
	datagram[2]=0xC0; //Header
	datagram[2]|=(input_datagram.vel & 0x03) << 4;
	datagram[2]|=(input_datagram.gotoexit & 0x07) << 1;
	datagram[2]|=calcula_paridad_byte(datagram[2]);
	
	//Generación del cuarto byte
	for (i=0; i<8; i++)
	{
		temp=0;
		for (j=0; j<3; j++)
			if(datagram[j]&(0x01 << i)) temp++;

		if (temp & 0x01) datagram[3]|= (0x01 <<i);
	}

	//Imprimiendo resultado
	for (i=0; i<4; i++)
		print_byte(datagram[i]);
	
	for (i=0; i<4; i++)
		printf("%X", datagram[i]);

	printf("\n");
}

int calcula_paridad_byte(int mybyte)
{
	int i;
	int count=0;
	
	for (i=1; i<8; i++)
		if (mybyte & (0x01 << i)) count++;

	return (count&0x01);
}

void paquete_a_binario()
{
	int i,j;
	int paquete[4];
	int temp;
	int par_byte=0;
	unsigned long int x;

	x = strtoll(paquete_recv, NULL, 16);

	paquete[3]=x & 0xff;
	paquete[2]=(x & 0xff00) >> 8;
	paquete[1]=(x & 0xff0000) >> 16;
	paquete[0]=(x & 0x7f000000) >> 24;

	printf("Imprimiendo paquete:\n");
	for (i=0; i<4; i++)
	{
		printf("\t%X -> ",paquete[i]);
		print_byte(paquete[i]);
		printf("\n");
	}

	printf("Analizando paquete:\n");
	
	/* PRIMER BYTE ***********************************************/
	printf("\tPrimer byte:\n");
	(paquete[0] & 0x80) ? printf ("\t\tHeader: NO OK\n") : printf("\t\tHeader: OK\n");
	temp=(paquete[0]&0x70) >> 4;
	printf ("\t\tSource: %X\n", temp);
	temp=(paquete[0]&0x0E) >> 1;
	printf ("\t\tDest  : %X\n", temp);
	(calcula_paridad_byte(paquete[0]) == (paquete[0]&0x01)) ? printf ("\t\tParity: OK\n") : printf ("\t\tParity: NO OK\n");

	/* SEGUNDO BYTE ***********************************************/
	printf("\tSegundo byte:\n");
	((paquete[1] & 0x80) && !(paquete[1] & 0x40)) ?	printf ("\t\tHeader: OK\n") :printf("\t\tHeader: NO OK\n");
	temp=(paquete[1]&0x20) >> 5;
	printf ("\t\tTipo  : %X\n", temp);
	temp=(paquete[1]&0x1E) >> 1;
	printf ("\t\tPos   : %X\n", temp);
	(calcula_paridad_byte(paquete[1]) == (paquete[1]&0x01)) ? printf ("\t\tParity: OK\n") : printf ("\t\tParity: NO OK\n");
	
	/* TERCER BYTE ***********************************************/
	printf("\tTercer byte:\n");
	((paquete[2] & 0x80) && (paquete[2] & 0x40)) ? printf ("\t\tHeader: OK\n") : printf("\t\tHeader: NO OK\n");
	temp=(paquete[2]&0x30) >> 4;
	printf ("\t\tSpeed : %X\n", temp);
	temp=(paquete[2]&0x0E) >> 1;
	printf ("\t\tGoto  : %X\n", temp);
	(calcula_paridad_byte(paquete[2]) == (paquete[2]&0x01)) ? printf ("\t\tParity: OK\n") : printf ("\t\tParity: NO OK\n");

	/* CUARTO BYTE ***********************************************/
	printf("\tParity byte:\n");
	for (i=0; i<8; i++)
	{
		temp=0;
		for (j=0; j<3; j++)
			if(paquete[j]&(0x01 << i)) temp++;
		if (temp & 0x01) par_byte |= (0x01 <<i);
	}
	(par_byte == paquete[3]) ? printf ("\t\tParity: OK\n") : printf ("\t\tParity: NO OK (%X)\n", par_byte);	
}


void print_byte(int mybyte)
{
	int i;

	for (i=7; i>=0; i--)
	{
		(mybyte& (0x01 << i)) ? printf ("1") : printf ("0");
		if (i==4) printf (" ");
	}
	printf("\n");
}


