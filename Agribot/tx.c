#include<reg51.h> //speed control of DC motor
#include<string.h>

#define lcd_data P2


sbit  lcd_rs   =  P2^0;  // Here we are using LCD in four bit mode that's why LCD's Data pins and control 
sbit  lcd_en   =  P2^1;


sbit sw1 = P3^0;
sbit sw2 = P3^1;
sbit sw3 = P3^2;
sbit sw4 = P3^3;
sbit sw5 = P3^4;

sbit sw6 = P0^0;
sbit sw7 = P0^1;
sbit sw8 = P0^2;


sbit sw9 = P0^3;
sbit swa = P0^4;
sbit swb = P0^5;



sbit swc = P0^6;
sbit swd = P0^7;




void delay(unsigned int value)

 {
   unsigned int x,y;
   for(x=0;x<value;x++)
   for(y=0;y<200;y++);
 } 

void lcdcmd(unsigned char value)		   // LCD COMMAND
  {
      
//      lcd_data=value; //slcd_end msb 4 bits
//      lcd_rs=0;	  //select command register
//      lcd_en=1;	  //lcd_enable the lcd to execute command
//	  delay(10);
//	  lcd_en=0; 
//	  delay(10);
	
	 lcd_data=value&(0xf0); //slcd_end msb 4 bits
      lcd_rs=0;	  //select command register
      lcd_en=1;	  //lcd_enable the lcd to execute command
	  delay(3);
	  lcd_en=0;  
      lcd_data=((value<<4)&(0xf0));	 //slcd_end lsb 4 bits
      lcd_rs=0;	 //select command register
      lcd_en=1;	 //lcd_enable the lcd to execute command
	  delay(3);
	  lcd_en=0;  
      
  }  
	

void lcd_init(void)
{
 lcdcmd(0x02);	
 lcdcmd(0x02);
 lcdcmd(0x28);  //intialise the lcd in 4 bit mode*/
 lcdcmd(0x28);  //intialise the lcd in 4 bit mode*/
 
 lcdcmd(0x0e);	//culcd_rsor blinking
 lcdcmd(0x06);	//move the culcd_rsor to right side
 lcdcmd(0x01);	//clear the lcd		

//   lcdcmd(0x38);
//   lcdcmd(0x0e);
//   lcdcmd(0x06);
//   lcdcmd(0x01);
//   lcdcmd(0x80);

}
void lcddata(unsigned char value)

  {
       
      lcd_data=value&(0xf0); //send msb 4 bits
      lcd_rs=1;	  //select data register
      lcd_en=1;	  //enable the lcd to execute data
	  delay(3);
	  lcd_en=0;  
      lcd_data=((value<<4)&(0xf0));	 //send lsb 4 bits
      lcd_rs=1;	  //select data register
      lcd_en=1;	  //enable the lcd to execute data
	  delay(3);
	  lcd_en=0;  
      
     delay(3); 
  }  



void msgdisplay(unsigned char b[]) // send string to lcd
  {
unsigned char s,count=0;
for(s=0;b[s]!='\0';s++)
 {
  count++;	 
  if(s==16)
   lcdcmd(0xc0);
   if(s==32)
   {
   lcdcmd(1);
   count=0;
   }
  lcddata(b[s]);
 }
}	



void main()
{
 P2=0xff;
 P1=0xff;
 P3=0xff;
 P0=0xff;

		 lcd_init();
		 msgdisplay("Agriculture Robot");
		 delay(500);

 while(1)
   {
    if(sw1 == 0)
	   {
	    while(sw1 == 0);
	    P1=0xf1;  lcdcmd(1);msgdisplay("f");
	   }
	 if(sw2 == 0)
	   {
	    while(sw2 == 0);
	    P1=0xf2;  lcdcmd(1);msgdisplay("b");
	   }
	  if(sw3 == 0)
	   {
	    while(sw3 == 0);
	    P1=0xf3; lcdcmd(1);msgdisplay("l");
	   }
	   if(sw4 == 0)
	   {
	    while(sw4 == 0);
	    P1=0xf4;  lcdcmd(1);msgdisplay("r");
	   }
	   if(sw5 == 0)
	   {
	    while(sw5 == 0);
	    P1=0xf5;    lcdcmd(1);msgdisplay("s");
	   }

	  
	  if(sw6 == 0)
	   {
	    while(sw6 == 0);
	    P1=0xf6;	 lcdcmd(1);msgdisplay("1");
	   }
	   if(sw7 == 0)
	   {
	    while(sw7 == 0);
	    P1=0xf7;   lcdcmd(1);msgdisplay("2");
	   }			  	   
	   if(sw8 == 0)
	   {
	    while(sw8 == 0);
	    P1=0xf8;    lcdcmd(1);msgdisplay("3");
	   }


	    if(sw9 == 0)
	   {
	    while(sw9 == 0);
	    P1=0xf9;    lcdcmd(1);msgdisplay("4");
	   }
	   if(swa == 0)
	   {
	    while(swa == 0);
	    P1=0xfa;   lcdcmd(1);msgdisplay("5");
	   }
	    if(swb == 0)
	   {
	    while(swb == 0);
	    P1=0xfb;   lcdcmd(1);msgdisplay("6");
	   } 



	   
	   if(swc == 0)
	   {
	    while(swc == 0);
	    P1=0xfc;    lcdcmd(1);msgdisplay("7");
	   }
	    if(swd == 0)
	   {
	    while(swd == 0);
	    P1=0xfd;    lcdcmd(1);msgdisplay("8");
	   }

   }

}