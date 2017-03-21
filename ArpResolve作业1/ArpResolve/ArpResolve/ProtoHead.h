#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define  IP_PROTO    0X0800
#define  ARP_PROTO   0X0806
#define  HARD_PROTO  0X0001

/*��������̫��Э���ʽ*/
struct ether_header
{
	unsigned char  ether_dhost[6];  //Ŀ��Mac��ַ
	unsigned char  ether_shost[6];  //ԴMac��ַ
	unsigned short ether_type;     //Э������
};

/*������ARPЭ���ʽ�Ķ���*/
struct arp_header
{
	unsigned short arp_hardware_type;          /*Ӳ������*/
	unsigned short arp_protocol_type;           /*Э������*/
	unsigned char arp_hardware_length;        /*Ӳ����ַ����*/
	unsigned char arp_protocol_length;        /*Э���ַ����*/
	unsigned short arp_operation_code;         /*������*/
	unsigned char arp_source_ethernet_address[6];  /*Դ��̫����ַ*/
	unsigned char arp_source_ip_address[4];      /*ԴIP��ַ*/
	unsigned char arp_destination_ethernet_address[6]; /*Ŀ����̫����ַ*/
	unsigned char arp_destination_ip_address[4];          /*Ŀ��IP��ַ*/
};
