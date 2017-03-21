#include "string.h"
#include "memory.h"
#include "ProtoHead.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>	  
#include <string>

using namespace std;

// ת��ʮ������
int convert(char c);
// �ϲ�
char combineTwoChar(char c1, char c2);
//���MAC��ʽ
void print_mac(char* title, unsigned char* cs);
// ���ip��ַ��ʽ
void print_ip(char* title, unsigned char* cs);
// ���Э������
void print_type(char* title, unsigned short cs);
// ���������
void print_code(char* title, unsigned short cs);
// ���Э�鳤��
void print_length(char* title, unsigned short cs);
// �����̫��ͷ��
void print_ether_header(ether_header eheader);
// ���Arpͷ��
void print_arp_header(arp_header arphead);
// ����ip��ַ
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
  
	//todo:���eheader��arphead���ֶ�,Ȼ�����¸�ʽ�������
	//��̫��ͷ��
	//Ŀ��Mac��ַ��FF--FF--FF--FF--FF--FF
	//ԴMac��ַ��  00--E0--4C--4F--10--90
	//Э�����ͣ�   0x0806(ARPЭ��)

	//ARPͷ��
	//Ӳ�����ͣ�   0001����̫����
	//......
	//Ŀ��IP:      C0A80002(192.168.0.2)

	int current_index = 0;

	for(int i = 0; i < 6; i++) {
		eheader.ether_dhost[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}
   
	for(int i = 0; i < 6; i++) {
		eheader.ether_shost[i] = combineTwoChar(prodat[current_index], prodat[current_index+1]);
		current_index += 2;
	}

	// ��̫��Э������
	eheader.ether_type = combineTwoChar(prodat[current_index], prodat[current_index+1])<<8;
	//printf("%04X \n", convert(prodat[current_index]));
	//printf("%04X \n", convert(prodat[current_index+1]));
	current_index += 2;

	eheader.ether_type = eheader.ether_type | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	// ARPͷӲ������
	arphead.arp_hardware_type = combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	arphead.arp_hardware_type = arphead.arp_hardware_type | combineTwoChar(prodat[current_index], prodat[current_index+1]);

	current_index += 2;

	// ARPͷЭ������
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

// ת��ʮ������
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

// �ϲ�
char combineTwoChar(char c1, char c2)
{
	return (convert(c1)<<4)|convert(c2);
}

//���MAC��ʽ
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

// ���ip��ַ��ʽ
void print_ip(char* title, unsigned char* cs)
{
	printf("  %s", title);
	for (int i = 0; i < 4; i++) {
		printf("%02X", cs[i]);
	}
	printf("%s", tran_to_ip(cs));
	printf("\n");
}

// ���Э������
void print_type(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%04X", cs);
	if (cs == ARP_PROTO) {
		printf("(ARPЭ��)");
	} else if (cs == IP_PROTO) {
		printf("(IP)");
	} else if (cs == HARD_PROTO) {
		printf("(��̫��)");
	}
	printf("\n");
}

// ���������
void print_code(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%04X", cs);
	printf("(ARP����)");
	printf("\n");
}

// ���Э�鳤��
void print_length(char* title, unsigned short cs)
{
	printf("  %s", title);
	printf("%02X", cs);
	printf("\n");
}

// �����̫��ͷ��
void print_ether_header(ether_header eheader)
{
	printf("��̫��ͷ����\n");
	print_mac("Ŀ��MAC��ַ�� ", eheader.ether_dhost);
	print_mac("ԴMAC��ַ��   ", eheader.ether_shost);
	print_type("Э�����ͣ�    ", eheader.ether_type);
}

// ���Arpͷ��
void print_arp_header(arp_header arphead)
{
	printf("Arpͷ����\n");
	print_type("Ӳ�����ͣ�    ", arphead.arp_hardware_type);
	print_type("Э�����ͣ�    ", arphead.arp_protocol_type);
	print_length("Ӳ����ַ���ȣ�", arphead.arp_hardware_length);
	print_length("Э���ַ���ȣ�", arphead.arp_protocol_length);
	print_code("�����룺      ", arphead.arp_operation_code);
	print_mac("ԴMAC��ַ��   ", arphead.arp_source_ethernet_address);
	print_ip("ԴIP��ַ��    ", arphead.arp_source_ip_address);
	print_mac("Ŀ��MAC��ַ�� ", arphead.arp_destination_ethernet_address);
	print_ip("Ŀ��IP��ַ��  ", arphead.arp_destination_ip_address);
}

// ����ip��ַ
char* tran_to_ip(unsigned char* cs)
{
	char* ip = new char[18];
	sprintf(ip, "(%d.%d.%d.%d)", cs[0], cs[1], cs[2], cs[3]);
	return ip;
}


