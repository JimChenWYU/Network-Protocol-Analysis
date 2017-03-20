#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define  IP_PROTO    0X0800
#define  ARP_PROTO   0X0806

/*��������̫��Э���ʽ*/
struct ether_header
{
	unsigned char  ether_dhost[6];  //Ŀ��Mac��ַ
	unsigned char  ether_shost[6];  //ԴMac��ַ
	unsigned short ether_type;     //Э������
};

/*������ARPЭ���ʽ�Ķ���*/
struct arp_header
{unsigned short arp_hardware_type;          /*Ӳ������*/
 unsigned short arp_protocol_type;           /*Э������*/
 unsigned char arp_hardware_length;        /*Ӳ����ַ����*/
 unsigned char arp_protocol_length;        /*Э���ַ����*/
 unsigned short arp_operation_code;         /*������*/
 unsigned char arp_source_ethernet_address[6];  /*Դ��̫����ַ*/
 unsigned char arp_source_ip_address[4];      /*ԴIP��ַ*/
 unsigned char arp_destination_ethernet_address[6]; /*Ŀ����̫����ַ*/
 unsigned char arp_destination_ip_address[4];          /*Ŀ��IP��ַ*/
};

// Ŀ��Mac��ַ��ȡ
string Ether_Dhost(char *prodat)
{
	string ether_dhost;
	ether_dhost.resize(13);
	for(int i = 0; i < 12; i++) {
		ether_dhost[i] = prodat[i];
	}
	ether_dhost[12] = '\0';
	return ether_dhost;
}

//ԴMac��ַ��ȡ 
string Ether_Shost(char *prodat)
{

	string ether_shost;
	ether_shost.resize(13);
	for(int i = 12; i < 24; i++) {
		ether_shost[i - 12] = prodat[i];
	}
	ether_shost[12] = '\0';
	return ether_shost;
}

short *Ether_Type(char *prodat)
{
	short *ether_type = new short[5];
	for (int i = 24; i < 28; i++) {
		ether_type[i - 24] = prodat[i];
	}
	ether_type[4] = '\0';
	return ether_type;
}

// ת��
int convert(char c)
{
	int result;
	if (c > 'a') {
		result = c - 'a' + 10;
	} else {
		result = c - 0;
	}
	return result;	
}

char combineTwoChar(char c1, char c2)
{
	return ((convert(c1) << 4) | convert(c2));
}
