#include <stdio.h>

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

char* Ether_Dhost(char* prodat)
{
	char ether_dhost[13];
	for(int i = 0; i < 12; i++) {
		ether_dhost[i] = prodat[i];
	}
	ether_dhost[12] = '\0';
	return ether_dhost;
}


char* Ether_Shost(char* prodat)
{
	char ether_shost[13];
	for(int i = 12; i < 24; i++) {
		ether_shost[i - 12] = prodat[i];
	}
	ether_shost[12] = '\0';
	printf("%s\n", ether_shost);
	return ether_shost;
}