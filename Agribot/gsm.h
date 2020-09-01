 void gsminit()
 {
 unsigned char rec=0;
	//	 while(1)
	//	{
		 string_0("AT\r\n");	
	//	 rec=receive_0();
	//	 if((rec=='O')||(rec=='K'))
	//	 break;
	//	}

		string_0("AT+CREG?\r\n");//network registration command
		delay(1000);
		string_0("AT+CMGF=1\r\n"); //flash message to read message
		delay(1000);
		string_0("AT+CNMI=1,2,0,0\r\n");	//flash message to read message
		delay(1000);
		
	//	stringlcd(0x80,"Modem Intilized..");
 }
 void sendmsg(unsigned char *num,unsigned char *chrm)
{
int i=0;
string_0("AT+CMGS=\"");
string_0(num);
string_0("\"\r\n");
delay(1000);
string_0(chrm);	
send_0(0x1a);  //control+z()1a)
delay(2500);
}