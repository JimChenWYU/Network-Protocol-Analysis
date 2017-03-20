#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define  IP_PROTO    0X0800
#define  ARP_PROTO   0X0806

/*以下是以太网协议格式*/
struct ether_header
{
	unsigned char  ether_dhost[6];  //目的Mac地址
	unsigned char  ether_shost[6];  //源Mac地址
	unsigned short ether_type;     //协议类型
};

/*下面是ARP协议格式的定义*/
struct arp_header
{unsigned short arp_hardware_type;          /*硬件类型*/
 unsigned short arp_protocol_type;           /*协议类型*/
 unsigned char arp_hardware_length;        /*硬件地址长度*/
 unsigned char arp_protocol_length;        /*协议地址长度*/
 unsigned short arp_operation_code;         /*操作码*/
 unsigned char arp_source_ethernet_address[6];  /*源以太网地址*/
 unsigned char arp_source_ip_address[4];      /*源IP地址*/
 unsigned char arp_destination_ethernet_address[6]; /*目的以太网地址*/
 unsigned char arp_destination_ip_address[4];          /*目的IP地址*/
};

// 目的Mac地址获取
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

//源Mac地址获取 
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

// 转换
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
