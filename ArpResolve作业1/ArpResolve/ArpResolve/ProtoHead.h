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


// ת��
int convert(char c)
{
	int result = 0;
	if (c > 'a') {
		result = c - 'a' + 10;
	} else {
		result = c - '0';
	}
	return result;	
}

// �ϲ�
char combineTwoChar(char c1, char c2)
{
	return (convert(c1)<<4)|convert(c2);
}

//���MAC��ʽ
void print_mac(unsigned char* cs) 
{
	for(int i = 0; i < 6; i++) 
	{
		if (i == 5) {
			printf("%02X", cs[i]);
		} else {
			printf("%02X--", cs[i]);
		}
	}
	printf("\n");
}

void print_type(unsigned short cs)
{
	printf("%04X", cs);
	printf("\n");
}