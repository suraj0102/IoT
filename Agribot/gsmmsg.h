unsigned char recm=0,mob[20],k=0;

void storenumber()
{
for(k=0;k<20;k++){mob[k]=0;}
 do{
    	 recm=receive_0();
       }while(recm != '+'); 

	   for(k=0;k<9;k++)
	      {
		   recm=receive_0();
		  }

	  for(k=0;k<10;k++)
	      {
		   mob[k]=receive_0();
		  }
}