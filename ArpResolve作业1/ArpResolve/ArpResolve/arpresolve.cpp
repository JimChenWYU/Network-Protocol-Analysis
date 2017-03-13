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
  
   //todo:填充eheader和arphead各字段,然后按以下格式依次输出
  //以太网头：
   //目的Mac地址：FF--FF--FF--FF--FF--FF
   //源Mac地址：  00--E0--4C--4F--10--90
   //协议类型：   0x0806(ARP协议)

   //ARP头：
   //硬件类型：   0001（以太网）
   //......
   //目的IP:      C0A80002(192.168.0.2)
  
  }








