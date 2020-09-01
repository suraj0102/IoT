#include <lpc214x.h>		 //21007BB4B15F         18008D991A16
#include <stdio.h>
#include <string.h>

#include "lcd.h"
#include "serial.h"
//#include "gsm.h"
#include "gpio.h"

#define ON  '1'//0x31
#define OFF '0' //0x30

#define  dt1    P0_3
#define  dt2    P0_4
#define  dt3    P0_5
#define  dt4    P0_6


#define  m1a    P1_24
#define  m1b    P1_25
#define  m2a    P1_26
#define  m2b    P1_27


#define  m3a    P0_20
#define  m3b    P0_21

#define  m4a    P0_22
#define  m4b    P0_23

#define  relay  P0_10


unsigned int memsx=0,memsy=0;
void serial0_RxISR(void) __irq; 

unsigned long int as1()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000002;
 delay(500);
  while(!(AD0DR1&0X80000000));
 return ((AD0DR1 >> 6) & 0x03FF);
}
unsigned long int as2()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000004;
 //delay(500);
 while(!(AD0DR2&0X80000000));
 return((AD0DR2 >> 6) & 0x03FF);
}
unsigned long int as3()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000008;
 //delay(500);
 while(!(AD0DR3&0X80000000));
 return((AD0DR3 >> 6) & 0x03FF);
}


void pin()
{
 PINSEL0=0X00050005;//SELECTING PIN OPERATION
 PINSEL1=0X15000000;
 PINSEL2=0X00000000;
 IODIR0=0xffffffff;
//IODIR0=0X00000000|sensor1|sensor2;// as output	and 2 pins as input
 IODIR0 &= ~(dt1|dt2|dt3|dt4);
 IODIR1=0XFFFFFFFF;//PORT1 AS OUTPUT
 IOCLR1=0XFFFFFFFF;
 AD0CR=0X00210600;// ADC CONTROL REGISTER
//IOPIN0|=0X0000001C;
 //IOSET0=sensor1|sensor2;
}
/*char inp0(char _bit)
{
 unsigned long c; 
 c = 1<<_bit; // Calculate digit to configuration for input port
 IODIR0 &= ~c; // Set input port from parameter _bit
 return((IOPIN0 & c)>>_bit); // Read and return data bit
}*/

int inp0(int pinNumber)
{
  // Read the current state of all pins in GPIO block 0
  int pinBlockState = IOPIN0;

  // Read the value of 'pinNumber'
  int pinState = (pinBlockState & (/*1 <<*/ pinNumber)) ? 1 : 0;

  // Return the value of pinState
  return pinState;
}
void InitSerial0Int(unsigned isrPtr)
{
  U0IER = 0x01;
  VICVectCntl0 	= 0x00000026;  						//select a priority slot for a given interrupt  
  VICVectAddr0 	= (unsigned long)isrPtr;		//pass the address of the IRQ into the VIC slot 
  VICIntEnable 	|= 0x00000040;						//enable interrupt2
}



unsigned char chkok()
{
  unsigned char rt;
 
 do{
    rt = receive_0();
	if(rt == 'E')
	  {
	   	 rt='E';
		 break;
	  }
   }while(rt != 'K');

   return rt;
}
	  /*
void gprs()
{
   unsigned char rt;   
   do{
      delay(800);
	  string_0("AT\r\n");
       rt = chkok();
   	 }while(rt != 'K');clcd(1);stringlcd(0x80,"AT");
 		 delay(600);

	/*
	do{
       delay(800);
	   string_0("AT+CSQ\r\n");
		 rt = chkok();
	  }while(rt != 'K');clcd(1);stringlcd(0x80,"AT+CSQ");
 		 delay(400);  */

 /*
	do{
	    delay(600);
        string_0("AT+CSTT=\"AIRTELGPRS.COM\",\",\"\r\n");   //rcomnet
 //  tx("AT+CSTT=\"RCOMNET\",\",\"\r\n");
        rt = chkok();
	  }while(rt != 'K');clcd(1);stringlcd(0x80,"Airtelgprs.com");  delay(600);


	 do{
	    delay(600);
        string_0("AT+CGATT=1\r\n");
	     rt = chkok();
	   }while(rt != 'K');clcd(1);stringlcd(0x80,"AT+CGATT=1");delay(650);	 


     
	 do{
	    delay(600);
        string_0("AT+CIICR\r\n");
	     rt = chkok();
	   }while(rt != 'K');clcd(1);stringlcd(0x80,"AT+CIICR=1");delay(650);
	   
	   	   
//delay(150);
       string_0("AT+CIFSR\r\n");
       delay(1500);
	   delay(1000);
	   clcd(1);  
	   stringlcd(0x80,"AT+CIFSR*");
}


void gprsstop()
 {
  unsigned char rx;
  string_0("AT+CIPCLOSE\r\n");
         do{
             rx=receive_0();
           }while(rx != 'K');clcd(1);stringlcd(0x80,"AT+CIPCLOSE");
		   delay(600);
  string_0("AT+CIPSHUT\r\n");
         do{
             rx=receive_0();
           }while(rx != 'K');clcd(1);stringlcd(0x80,"AT+CIPSHUT");
 }

void gprsstart()
 {
 unsigned char rx;

   // do
	//{
lp:	 delay(600);
	 string_0("AT+CIPSTART=\"TCP\",\"www.gprsserver.in\",\"80\"\r\n");  
	  do{
             rx=receive_0();
           }while(rx != 'K');
	       
		   	do{
               rx=receive_0();
			    if(rx == 'F')
			       {
				     gprsstop();goto lp;
				   }
              }while(rx != 'K');	   

     delay(600);

		    string_0("AT+CIPSEND\r\n");
      	    do{
			   rx=receive_0();
			  }while(rx != '>');
 }
  */

  
void okcheck()
{
 unsigned char rr;
 do{
     rr = receive_0();
   }while(rr != 'K');
}

void gprs()
{
//   unsigned char rt;  


	  string_0("AT\r\n");
       okcheck(); clcd(1); stringlcd(0x80,"AT");
   	 
 		 delay(400);

	/*
	do{
       delay(800);
	   string_0("AT+CSQ\r\n");
		 rt = chkok();
	  }while(rt != 'K');clcd(1);stringlcd(0x80,"AT+CSQ");
 		 delay(400);  */

        string_0("AT+CSTT=\"AIRTELGPRS.COM\",\",\"\r\n");   //rcomnet
        okcheck(); clcd(1);	 stringlcd(0x80,"airtelgprs.com");
 //  tx("AT+CSTT=\"RCOMNET\",\",\"\r\n");
        
        string_0("AT+CGATT=1\r\n");
		okcheck(); clcd(1);	 stringlcd(0x80,"AT+CGATT=1");
	    delay(650);	 


        string_0("AT+CIICR\r\n");
		okcheck();clcd(1);	 stringlcd(0x80,"AT+CIICR");
		  
		  delay(500);
	   	   
//delay(150);
       string_0("AT+CIFSR\r\n");
       delay(1500);
	   delay(1000);
	   clcd(1);  
	   stringlcd(0x80,"AT+CIFSR*");
}


void gprsstop()
 {
  unsigned char rx;
  string_0("AT+CIPCLOSE\r\n");
         do{
             rx=receive_0();
           }while(rx != 'K');clcd(1);stringlcd(0x80,"AT+CIPCLOSE");
		   delay(600);
  string_0("AT+CIPSHUT\r\n");
         do{
             rx=receive_0();
           }while(rx != 'K');clcd(1);stringlcd(0x80,"AT+CIPSHUT");
 }

void gprsstart()
 {
 unsigned char rx;

   // do
	//{
lp:	 delay(600);
	 string_0("AT+CIPSTART=\"TCP\",\"www.gprsserver.in\",\"80\"\r\n");  
	  do{
             rx=receive_0();
           }while(rx != 'K');
	       
		   	do{
               rx=receive_0();
			    if(rx == 'F')
			       {
				     gprsstop();goto lp;
				   }
              }while(rx != 'K');	   

     delay(600);

		    string_0("AT+CIPSEND\r\n");
      	    do{
			   rx=receive_0();
			  }while(rx != '>');
 }




 
void gprs_vts_send(unsigned char *lat,unsigned char *lon,unsigned char *di1,unsigned char *di2,unsigned int ai1,unsigned int ai2,unsigned char *dev_name)
{
 unsigned char tbuf[10];
 unsigned char buf[4]={0x0d,0x0a,0x1a,0x00};
 
 string_0("GET /portvts.php?");

  
 string_0("a=");  string_0(lat);
 string_0("&b="); string_0(lon);

 string_0("&c="); string_0(dev_name);
 string_0("&d="); string_0("vts");
 

 string_0("&e="); string_0(di1);
  
 string_0("&f="); string_0(di2);
  

  sprintf(tbuf,"%u",ai1);
    string_0("&g="); string_0(tbuf);

  sprintf(tbuf,"%u",ai2);
    string_0("&h="); string_0(tbuf);

    string_0("&i="); string_0("- HTTP/1.1\r\n");

   string_0("Host: www.gprsserver.in\r\n");
   string_0(buf);
//  tx1(0x1A);
}  

void gprs_logger_send(unsigned char *s1,unsigned int si1,unsigned char *s2,unsigned int si2,unsigned char *s3,unsigned int si3,unsigned char *s4,unsigned int si4,unsigned char *s5,unsigned int si5,unsigned char *dev_name)
{
  unsigned char tbuf[10];
  unsigned char buf[4]={0x0d,0x0a,0x1a,0x00}; 
 
 string_0("GET /portlogger.php?");

 string_0("a=");string_0(s1);
 sprintf(tbuf,"%u",si1);
 string_0("&b=");string_0(tbuf);

 string_0("&c=");string_0(s2);
 sprintf(tbuf,"%u",si2);
 string_0("&d=");string_0(tbuf);

 string_0("&e=");string_0(s3);
 sprintf(tbuf,"%u",si3);
 string_0("&f=");string_0(tbuf);

 string_0("&g=");string_0(s4);
 sprintf(tbuf,"%u",si4);
 string_0("&h=");string_0(tbuf);

 string_0("&i=");string_0(s5);
 sprintf(tbuf,"%u",si5);
 string_0("&j=");string_0(tbuf);


 string_0("&k=");string_0(dev_name);
 string_0("&l=");string_0("logger");

 string_0(" HTTP/1.1 \r\n");

 string_0("Host: www.gprsserver.in\r\n");
 string_0(buf);

}

 


 
unsigned char count=0,gps_location[26];
void gps()
{
	while(receive_1()!='C');
		for(count=0;count<14;count++)
		{
		receive_1();
		}
		for(count=0;count<24;count++)
		{
		gps_location[count]=receive_1();
		}
}


void lcdbasic()
{
     clcd(1);
	stringlcd(0x80,"HB:");//0x83,4,5
	stringlcd(0x88,"T:"); //0x8A,9,a
	stringlcd(0xc0,"M:"); //0xc2,3,4
	stringlcd(0xc6,"L:"); //0xc8,9,a  
	stringlcd(0xcb,"H:"); //0xcd,e,f

}



unsigned char mob1[11];//="9030059841\0";
unsigned char mob2[15]="7730867385\0";
unsigned int card=0,set1=0,set2=0,set3=0,hb=0,cnt=0,ht=0,loop=0;
unsigned char rfid_t[15],rfid_0[13]="140071C70FAD\0",rfid_1[13]="140071DCA61F\0",rfid_2[13]="840081160E1D\0",rfid_3[13]="FE006E2F5BE4\0";
unsigned char msg1[10],msg2[10];


void main()		   //gsm modem is connected to serial0 and system is connected to serial1
{
 unsigned char rec='X',rec1='x',p;
 unsigned long int cnt=0,hc=0,ht=0;
 unsigned int temp=0,hb;
 for(p=0;p<14;p++){rfid_t[p]=0;}
 pin();

 			  IOCLR1=m1a;IOCLR1=m1b;
			  IOCLR1=m2a;IOCLR1=m2b;

			  IOCLR0=m3a;IOCLR0=m3b;
			  IOCLR0=m4a;IOCLR0=m4b;

			  IOCLR0=relay;

	ser_init_0(0x61,0x00);
	ser_init_1(0x61,0x00); //serial initilization 

	initlcd();

	stringlcd(0x80,"Agriculture Robot"); //initial message
	

	delay(1000); delay(1000);delay(1000);
  //  InitSerial0Int((unsigned int)serial0_RxISR);
   
					 clcd(1);
 while(1)
 {
   if(inp0(dt1) == 1 && inp0(dt2) == 0 && inp0(dt3) == 0 && inp0(dt4) == 0)	
     {
	  IOSET1=m1a;IOCLR1=m1b;
	  IOSET1=m2a;IOCLR1=m2b;  stringlcd(0x80,"F");
	 }
   if(inp0(dt1) == 0 && inp0(dt2) == 1 && inp0(dt3) == 0 && inp0(dt4) == 0)	
     {
	  IOCLR1=m1a;IOSET1=m1b;
	  IOCLR1=m2a;IOSET1=m2b;  stringlcd(0x80,"B");
	 } 
   if(inp0(dt1) == 1 && inp0(dt2) == 1 && inp0(dt3) == 0 && inp0(dt4) == 0)	
     {
	  IOSET1=m1a;IOCLR1=m1b;
	  IOCLR1=m2a;IOSET1=m2b;  stringlcd(0x80,"L");
	 } 
   if(inp0(dt1) == 0 && inp0(dt2) == 0 && inp0(dt3) == 1 && inp0(dt4) == 0)	
     {
	  IOCLR1=m1a;IOSET1=m1b;
	  IOSET1=m2a;IOCLR1=m2b; stringlcd(0x80,"R");
	 } 
   if(inp0(dt1) == 1 && inp0(dt2) == 0 && inp0(dt3) == 1 && inp0(dt4) == 0)	
     {
	  IOCLR1=m1a;IOCLR1=m1b;
	  IOCLR1=m2a;IOCLR1=m2b; stringlcd(0x80,"S");
	 }
	 
	 
   if(inp0(dt1) == 0 && inp0(dt2) == 1 && inp0(dt3) == 1 && inp0(dt4) == 0)	
     {
	  IOCLR0=m3a;IOSET0=m3b;  stringlcd(0x80,"1");
	 } 	  
   if(inp0(dt1) == 1 && inp0(dt2) == 1 && inp0(dt3) == 1 && inp0(dt4) == 0)	
     {
	  IOSET0=m3a;IOCLR0=m3b; stringlcd(0x80,"2");
	 }
   if(inp0(dt1) == 0 && inp0(dt2) == 0 && inp0(dt3) == 0 && inp0(dt4) == 1)	
     {
	  IOCLR0=m3a;IOCLR0=m3b; stringlcd(0x80,"3");
	 } 	  	  	  	  	  


   
   if(inp0(dt1) == 1 && inp0(dt2) == 0 && inp0(dt3) == 0 && inp0(dt4) == 1)	
     {
	  IOCLR0=m4a;IOSET0=m4b; stringlcd(0x80,"4");
	 } 	  
   if(inp0(dt1) == 0 && inp0(dt2) == 1 && inp0(dt3) == 0 && inp0(dt4) == 1)	
     {
	  IOSET0=m4a;IOCLR0=m4b; stringlcd(0x80,"5");
	 }
   if(inp0(dt1) == 1 && inp0(dt2) == 1 && inp0(dt3) == 0 && inp0(dt4) == 1)	
     {
	  IOCLR0=m4a;IOCLR0=m4b; stringlcd(0x80,"6");
	 } 	  	  	  	  	  


   
   if(inp0(dt1) == 0 && inp0(dt2) == 0 && inp0(dt3) == 1 && inp0(dt4) == 1)	
     {
	  IOSET0=relay;			stringlcd(0x80,"7");
	 }
   if(inp0(dt1) == 1 && inp0(dt2) == 0 && inp0(dt3) == 1 && inp0(dt4) == 1)	
     {
	  IOCLR0=relay;		   stringlcd(0x80,"8");
	 } 	  	  	  	  	  
 }//end of while


 }
 
 /*	
 void serial0_RxISR(void) __irq 
{
  unsigned char ch;
  for(ch=0;ch<12;ch++){rfid_t[ch]=receive_0();}
  IOCLR0=relay;
  if(strcmp(rfid_t,rfid_0)==0){card = 1;set3=1;}
  if(strcmp(rfid_t,rfid_1)==0){card = 2;set3=1;}
  if(strcmp(rfid_t,rfid_2)==0){card = 3;set3=1;}
  
  VICVectAddr 	= 0x00000000;						//Dummy write to signal end of interrupt
}  */
																                  