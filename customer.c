 #include<stdio.h>
 #include<conio.h>
 #include<stdlib.h>

 void input();
 void writefile();
 void search();
 void output();

 struct date{
	   int month;
	   int day;
	   int year;
	   };

  struct account {
	int number;
	char name[100];
	int acct_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
  }cust;
  int tl,sl,ts;
 int main()
	{
	  int i,n;
	  char ch;
	  clrscr();

	  _setcursortype(_NOCURSOR);
	  printf("   cust BILLING SYSTEM:\n\n");
	  printf("===============================\n");
	  printf("\n1:    to add account on list\n");
	  printf("2:    to search cust account\n");
	  printf("3:    exit\n");
	  printf("\n================================\n");
	  do{
	       printf("\nselect what do you want to do?");
	       ch=getche();
	  }while(ch<='0' || ch>'3');
	  switch(ch){
		case '1':
			clrscr();
			printf("\nhow many cust accounts?");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				input();
				if(cust.payment>0)
					cust.acct_type=(cust.payment<0.1*cust.oldbalance)? 'O': 'D';
				else
					cust.acct_type=(cust.oldbalance>0)?'D' : 'C';
				cust.newbalance=cust.oldbalance - cust.payment;
				writefile();
			}
			main();
		case '2':
			clrscr();
			printf("search by what?\n");
			printf("\n1 --- search by cust number\n");
			printf("2 --- search by cust name\n");
			search();
			ch=getche();
			main();
		case '3':
			clrscr();
			delay(700);
			textcolor(RED);
			gotoxy(25,25);
			cprintf("\nA PROJECT BY BIDUR & SUJAN");
			delay(1500);
			exit(1);
	  }
 }


   void input()
	{
	  FILE *fp=fopen("bidur.dat","rb");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(cust);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&cust,sizeof(cust),1,fp);
	  printf("\ncust no:%d\n",++cust.number);
	  fclose(fp);
	  printf("         Account number:");
	  scanf("%d",&cust.acct_no);
	  printf("\n       Name:");
	  scanf("%s",cust.name);
	  printf("\n       mobile no:");
	  scanf("%f",&cust.mobile_no);
	  printf("         Street:");
	  scanf("%s",cust.street);
	  printf("         City:");
	  scanf("%s",cust.city);
	  printf("         Previous balance:");
	  scanf("%f",&cust.oldbalance);
	  printf("         Current payment:");
	  scanf("%f",&cust.payment);
	  printf("         Payment date(mm/dd/yyyy):");
	  scanf("%d/%d/%d",&cust.lastpayment.month,&cust.lastpayment.day,&cust.lastpayment.year);
	  return;
   }

   void writefile()
   {
	  FILE *fp;
	  fp=fopen("bidur.dat","ab");
	  fwrite(&cust,sizeof(cust),1,fp);
	  fclose(fp);
	  return;
   }

   void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("bidur.dat","rb");
	 do{
		printf("\nenter your choice:");
		ch=getche();
	 }while(ch!='1' && ch!='2');
	 switch(ch){
	      case '1':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(cust);
		    ts=tl/sl;
		    do{
			printf("\nchoose cust number:");
			scanf("%d",&n);
			if(n<=0 || n>ts)
			printf("\nenter correct\n");
			else{
			    fseek(fp,(n-1)*sl,SEEK_SET);
			    fread(&cust,sl,1,fp);
			    output();
			}
			printf("\n\nagain?(y/n)");
			ch=getche();
		    }while(ch=='y');
		    fclose(fp);
		    break;
	      case '2':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(cust);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&cust,sizeof(cust),1,fp);
		    n=cust.number;

		    do{
			printf("\nenter the name:");
			scanf("%s",nam);
			fseek(fp,0,SEEK_SET);
			for(i=1;i<=n;i++)
			{
			     fread(&cust,sizeof(cust),1,fp);
			     if(strcmp(cust.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			printf("\n\ndoesn't exist\n");
			printf("\nanother?(y/n)");
			ch=getche();
		    }while(ch=='y');
		    fclose(fp);
	      }
	      return;
	 }



   void output()
	 {
	   printf("\n\n    cust no    :%d\n",cust.number);
	   printf("    Name 	   :%s\n",cust.name);
	   printf("    Mobile no      :%.f\n",cust.mobile_no);
	   printf("    Account number :%d\n",cust.acct_no);
	   printf("    Street         :%s\n",cust.street);
	   printf("    City           :%s\n",cust.city);
	   printf("    Old balance    :%.2f\n",cust.oldbalance);
	   printf("    Current payment:%.2f\n",cust.payment);
	   printf("    New balance    :%.2f\n",cust.newbalance);
	   printf("    Payment date   :%d/%d/%d\n\n",cust.lastpayment.month,cust.lastpayment.day,cust.lastpayment.year);
	   printf("    Account status :");
	   textcolor(128+RED);
	   switch(cust.acct_type)
	      {
	      case 'C':
		 cprintf("CURRENT\n\n");
		 break;
	      case 'O':
		 cprintf("OVERDUE\n\n");
		 break;
	      case 'D':
		 cprintf("DELINQUENT\n\n");
		 break;
	      default:
		 cprintf("ERROR\\n\n");
	      }
	      textcolor(WHITE);
	      return;
	   }














