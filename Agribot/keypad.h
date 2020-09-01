
#include <lpc214x.h>
//#define DEBUG

//#ifdef DEBUG 							   // #if 1	 FOR PORT 0
								   // #if 0	 FOR PORT 1
#define  sw1     P0_16   						
#define  sw2     P0_17 
#define  sw3     P0_18 
#define  sw4     P0_19    						
#define  sw5     P0_20    						
#define  sw6     P0_21   						
#define  sw7     P0_22    
#define  sw8     P0_23 
#define  sw9     P0_24    						
#define  swl0    P0_25    						
#define  swl1    P0_26   						
#define  swl2    P0_27 	
					

unsigned char keypad(void );



unsigned char keypad(void)
{
 	pwd=0,kp;

 while(1)
 //for(kp=0;kp<4;kp++) 
	{
	 	if(inp0(sw1) == 0)
		  {while(inp0(sw1) == 0);
			password[pwd];
			dlcd('1'); 
			pwd++;
		  }

		if(inp0(sw2) == 0)
		  {while(inp0(sw2) == 0);
			password[pwd];
			dlcd('2'); 
			pwd++;
		  }

		if(inp0(sw3) == 0)
		  {while(inp0(sw3) == 0);
			password[pwd];
			dlcd('3'); 
			pwd++;
		  }

		if(inp0(sw4) == 0)
		  {while(inp0(sw4) == 0);
			password[pwd];
			dlcd('4'); 
			pwd++;
		  }



		if(inp0(sw5) == 0)
		  {while(inp0(sw5) == 0);
			password[pwd];
			dlcd('5'); 
			pwd++;
		  }

		if(inp0(sw6) == 0)
		  {while(inp0(sw6) == 0);
			password[pwd];
			dlcd('6'); 
			pwd++;
		  }

		if(inp0(sw7) == 0)
		  {while(inp0(sw7) == 0);
			password[pwd];
			dlcd('7'); 
			pwd++;
		  }

		if(inp0(sw8) == 0)
		  {while(inp0(sw8) == 0);
			password[pwd];
			dlcd('8'); 
			pwd++;
		  }



	   	if(inp0(sw9) == 0)
		  {while(inp0(sw9) == 0);
			password[pwd];
			dlcd('9'); 
			pwd++;
		  }

		if(inp0(sw10) == 0)
		  {while(inp0(sw10) == 0);
			password[pwd];
			dlcd('0'); 
			pwd++;
		  }

		if(inp0(sw11) == 0)
		  {while(inp0(sw11) == 0);
			password[pwd];
			dlcd('*'); 
			pwd++;
		  }

		if(inp0(sw12) == 0)
		  {while(inp0(sw12) == 0);
			password[pwd];
			dlcd('E'); 
			pwd++;
		  }

		
	}
}
