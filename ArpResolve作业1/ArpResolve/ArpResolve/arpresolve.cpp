  #include "string.h"
  #include "memory.h"
  #include "ProtoHead.h"
  #include "stdio.h"
  #include "stdlib.h"
  
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
  
  }








