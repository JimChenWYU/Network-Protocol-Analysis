#include "string.h"
#include "memory.h"
#include "ProtoHead.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>	  
#include <string>

using namespace std;

// 转换十六进制
int convert(char c);
// 合并
char combineTwoChar(char c1, char c2);
//输出MAC格式
void print_mac(char* title, unsigned char* cs);
// 输出ip地址格式
void print_ip(char* title, unsigned char* cs);
// 输出协议类型
void print_type(char* title, unsigned short cs);
// 输出操作码
void print_code(char* title, unsigned short cs);
// 输出协议长度
void print_length(char* title, unsigned short cs);
// 输出以太网头部
void print_ether_header(ether_header eheader);
// 输出Arp头部
void print_arp_header(arp_header arphead);
// 返回ip地址
char* tran_to_ip(unsigned char* cs);


void main()
{
	char prodat[1600];
	strcpy(prodat,"ffffff");
	strcat(prodat,"ffffff");
  
	strcat(prodat,"00e04c4f1090");
	strcat(prodat,"0806");
	strcat(prodat,"000108000604");
	strcat(prodat,"0001");
	strcat(prodat,"00e04c4f1090c0a80014");
	strcat(prodat,"000000000000c0a80002");
	strcat(prodat,"000000000000");
	strcat(prodat,"000000000000");
	strcat(prodat,"000000000000");
  
	ether_header eheader;
	arp_header   arphead;
  
	//todo:填充eheader和arphead各字段,然后按以下格式依次输出
	//以太网头：
	//目的Mac地址：FF--FF--FF--FF--FF--FF
	//源Mac地址：  00--E0--4C--4F--10--90
	//协议类型：   0x0806(ARP协议)

	//ARP头：
	//硬件类型：   0001（以太网）
	//......
	//目的IP:      C0A80002(192.168.0.2)

	int current_index = 0;

	for(int i = 0; i < 6; i++) {
		eheader.ether_dhost[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}
   
	for(int i = 0; i < 6; i++) {
		eheader.ether_shost[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	// 以太网协议类型
	eheader.ether_type = combineTwoChar(prodat[current_index], prodat[current_index+1])<<8;
	//printf("%04X \n", convert(prodat[current_index]));
	//printf("%04X \n", convert(prodat[current_index+1]));
	current_index += 2;

	eheader.ether_type = eheader.ether_type | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	// ARP头硬件类型
	arphead.arp_hardware_type = combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_hardware_type = arphead.arp_hardware_type | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	// ARP头协议类型
	arphead.arp_protocol_type = combineTwoChar(prodat[current_index], prodat[current_index+1])<<8;

	current_index += 2;

	arphead.arp_protocol_type = arphead.arp_protocol_type | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_hardware_length = combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_protocol_length = combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_operation_code = combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_operation_code = arphead.arp_operation_code | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	for(int i = 0; i < 6; i++) {
		arphead.arp_source_ethernet_address[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	for(int i = 0; i < 4; i++) {
		arphead.arp_source_ip_address[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	for(int i = 0; i < 6; i++) {
		arphead.arp_destination_ethernet_address[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	for(int i = 0; i < 4; i++) {
		arphead.arp_destination_ip_address[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	print_ether_header(eheader);
	printf("\n");
	print_arp_header(arphead);
	printf("\n");

	system("pause");
}

// 转换十六进制
int convert(char c)
{
	int result = 0;
	if (c >= 'a') {
		result = c - 'a' + 10;
	} else {
		result = c - '0';
	}
	return result;	
}

// 合并
char combineTwoChar(char c1, char c2)
{
	return (convert(c1)<<4)|convert(c2);
}

//输出MAC格式
void print_mac(char* title, unsigned char* cs) 
{
	printf("  %s", title);
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

// 输出ip地址格式
void print_ip(char* title, unsigned char* cs)
{
	printf("  %s", title);
	for (int i = 0; i < 4; i++) {
		printf("%02X", cs[i]);
	}
	printf("%s", tran_to_ip(cs));
	printf("\n");
}

// 输出协议类型
void print_type(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%04X", cs);
	if (cs == ARP_PROTO) {
		printf("(ARP协议)");
	} else if (cs == IP_PROTO) {
		printf("(IP)");
	} else if (cs == HARD_PROTO) {
		printf("(以太网)");
	}
	printf("\n");
}

// 输出操作码
void print_code(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%04X", cs);
	printf("(ARP请求)");
	printf("\n");
}

// 输出协议长度
void print_length(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%02X", cs);
	printf("\n");
}

// 输出以太网头部
void print_ether_header(ether_header eheader)
{
	printf("以太网头部：\n");
	print_mac("目的MAC地址： ", eheader.ether_dhost);
	print_mac("源MAC地址：   ", eheader.ether_shost);
	print_type("协议类型：    ", eheader.ether_type);
}

// 输出Arp头部
void print_arp_header(arp_header arphead)
{
	printf("Arp头部：\n");
	print_type("硬件类型：    ", arphead.arp_hardware_type);
	print_type("协议类型：    ", arphead.arp_protocol_type);
	print_length("硬件地址长度：", arphead.arp_hardware_length);
	print_length("协议地址长度：", arphead.arp_protocol_length);
	print_code("操作码：      ", arphead.arp_operation_code);
	print_mac("源MAC地址：   ", arphead.arp_source_ethernet_address);
	print_ip("源IP地址：    ", arphead.arp_source_ip_address);
	print_mac("目的MAC地址： ", arphead.arp_destination_ethernet_address);
	print_ip("目的IP地址：  ", arphead.arp_destination_ip_address);
}

// 返回ip地址
char* tran_to_ip(unsigned char* cs)
{
	char* ip = new char[18];
	sprintf(ip, "(%d.%d.%d.%d)", cs[0], cs[1], cs[2], cs[3]);
	return ip;
}


