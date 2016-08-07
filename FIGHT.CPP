#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<process.h>
#include<dir.h>
#include<stdio.h>

void main_menu();
void startup();
void startgame();
void umove();
float getran();
void checkstats();
void stopgame();
void help();
void about();
void sel(int, char);

struct uplayer
{
	char name[12];
	int lvl;
	int uindx;
};

class player
{
  public:
	int hp, iscpu, defend;
	  player(int x)
	{
		iscpu = x;
		hp = 100;
		defend = 0;
	}
	void attack(char g)
	{
		sel(iscpu, g);
		checkstats();
	}
};

player user(0);
player cpu(1);
struct uplayer userd;
FILE *f;
int cnt=0;

void sel(int k, char n)
{
	if ((k == 0 && cpu.defend != 1) || (k == 1 && user.defend != 1))
	{
	  switch(n)
	  {
		case '1':		// hpunch
			if (k == 0)
				cpu.hp -= 10 * userd.lvl;
			else
				user.hp -= 10 * userd.lvl;
		    break;
		case '2':		// lpunch
			if (k == 0)
			{
				cpu.hp -= 2 * userd.lvl;
				user.defend = 1;
			}
			else
			{
				user.hp -= 2 * userd.lvl;
				cpu.defend = 1;
			}
		    break;
		case '3':		// hkick
			if (k == 0)
				cpu.hp -= 15 * userd.lvl;
			else
				user.hp -= 15 * userd.lvl;
		    break;
		case '4':		// lkick
			if (k == 0)
			{
				cpu.hp -= 5 * userd.lvl;
				user.defend = 1;
			}
			else
			{
				user.hp -= 5 * userd.lvl;
				cpu.defend = 1;
			}
		    break;
		case '5':		// defend
			if (k == 0)
				user.defend = 1;
			else
				cpu.defend = 1;
		    break;
		case '0':
			cout << "\nYou Quit...\n";
			stopgame();
			break;
		default:
			cout<<"Invalid input. Please try again. Hit enter...";
			getch();
			cout<<"\n\n";
			umove();
	  }
	}
	else
	{
		if (k == 0)
			cpu.defend = 0;
		if (k == 1)
			user.defend = 0;
	}
}


int gameover = 0;

void main()
{
	clrscr();
	srand((unsigned)time(NULL));
	mkdir("User files");
	main_menu();
	getch();
}

void main_menu()
{
	clrscr();
	char c;
	cout << "************************************\n";
	cout << "*****    FIGHT NIGHT  v1.0b    *****\n";
	cout << "************************************\n";
	cout << "By: Hrishi Hiraskar\n";
	cout << "\n1. New Player\n2. Load Player\n3. Delete Player\n0. Exit\nEnter choice...";
	cin >> c;
	cout << endl;
	f=fopen("User files/count.hri","r");
	fread(&cnt,1,sizeof(cnt),f);
	fclose(f);
	cout<<cnt;
	getch();
	switch(c)
	{
		case '1':
			cout<<"Enter Player name:\t";
			cin>>userd.name;
			userd.lvl=1;
			userd.uindx=cnt;
			f=fopen("User files/players.hri","a");
			fwrite(&userd,1,sizeof(userd),f);
			fclose(f);
			cnt++;
			f=fopen("User files/count.hri","w");
			fwrite(&cnt,1,sizeof(cnt),f);
			fclose(f);
			startup();
			break;
		case '2':
			struct uplayer users[10];
			int p;
			f=fopen("User files/players.hri","r");
			fread(&users,cnt,sizeof(users),f);
			fclose(f);
			cout<<"\n\nSr.No.\tPlayer\tLevel\n";
			for(int r=0;r<cnt;r++)
			{
				cout<<(r+1)<<".\t"<<users[r].name<<"\t"<<users[r].lvl<<endl;
			}
			cout<<"\nEnter choice...";
			if(cin>>p)
			{
			  if(p>0 && p<=cnt)
			  {
				p--;
				strcpy(userd.name,users[p].name);
				userd.lvl=users[p].lvl;
				//userd.lvl=5;
				userd.uindx=users[p].uindx;
				startup();
			  }
			  else
			  {
				goto elss;
			  }
			}
			else
			{
				cin.clear();
				cin.ignore();
				elss:
				cout<<"\nInvalid input. Please try again. Hit enter...";
				getch();
				main_menu();
			}
			break;
		case '3':
			struct uplayer users1[10];
			int q;
			f=fopen("User files/players.hri","r");
			fread(&users1,cnt,sizeof(users1),f);
			fclose(f);
			cout<<"\n\nSr.No.\tPlayer\tLevel\n";
			for(int t=0;t<cnt;t++)
			{
				cout<<(t+1)<<".\t"<<users1[t].name<<"\t"<<users1[t].lvl<<endl;
			}
			cout<<"\nEnter player number to be deleted...";
			if(cin>>q)
			{
			if(q>0 && q<=cnt)
			{
			q--;
			for(int l=q;l<cnt-1;l++)
			{
				strcpy(users1[l].name,users1[l+1].name);
				users[l].lvl=users[l+1].lvl;
				users[l].uindx=users[l+1].uindx;
			}
			cnt--;
			f=fopen("User files/count.hri","w");
			fwrite(&cnt,1,sizeof(cnt),f);
			fclose(f);
			f=fopen("User files/players.hri","w");
			fwrite(&users1[0],cnt,sizeof(users1[0]),f);
			fclose(f);
			cout<<"Deleted successfully...";
			getch();
			main_menu();
			}
			else
			  {
				goto elsd;
		   	  }
			}
			else
			{
				cin.clear();
				cin.ignore();
				elsd:
				cout<<"\nInvalid input. Please try again. Hit enter...";
				getch();
				main_menu();
			}
			break;
		case '0':
			exit(0);
		default:
			cout<<"\nInvalid input. Please try again. Hit enter...";
			getch();
			main_menu();
			break;
	}
}

void startup()
{
	clrscr();
	char a;
	cout << "************************************\n";
	cout << "*****    FIGHT NIGHT  v1.0b    *****\n";
	cout << "************************************\n";
	cout << "By: Hrishi Hiraskar\n";
	cout << "\nPlayer: "<<userd.name<<". Level: "<<userd.lvl;
	cout <<
		"\n\n1. Start New Game.\n2. Help.\n3. About Dev.\n4. Save progress\n5. Load/New Player\n0. Exit.\nEnter choice...";
	cin >> a;
	switch (a)
	{
	case '1':
		startgame();
	case '2':
		help();
	case '3':
		about();
	case '4':
		f=fopen("User files/count.hri","r");
		fread(&cnt,1,sizeof(cnt),f);
		fclose(f);
		struct uplayer users[10];
		f=fopen("User files/players.hri","r");
		fread(&users,cnt,sizeof(users),f);
		fclose(f);
		users[userd.uindx].lvl=userd.lvl;
		f=fopen("User files/players.hri","w");
		fwrite(&users[0],cnt,sizeof(users[0]),f);
		fclose(f);
		cout<<"\nSaved succesfully";
		getch();
		startup();
		break;
	case '5':
		main_menu();
		break;
	case '0':
		exit(0);
	default:
		cout<<"\nInvalid input. Pleaae try again. Hit enter...";
		getch();
		startup();
	}
	getch();
}

void umove()
{
	char b;
	cout << "Your HP: " << user.hp << "\tEnemy\'s HP: " << cpu.hp;
	cout <<
		"\n\n1. High Punch.\n2. Low Punch.\n3. High Kick.\n4. Low Kick.\n5. Defend.\n0. Stop Game.\nEnter choice...";
	cin >> b;
	cout<<"\n\n";
	user.attack(b);
}

float getran()
{
	float r = rand(), max = RAND_MAX;
	return (r / max);
}

void startgame()
{
	clrscr();
	user.hp=(cpu.hp=100*userd.lvl);
	char f[5]={'1','2','3','4','5'};
	while (gameover == 0)
	{
		umove();
		int m = (int)(getran() * 5);
		cpu.attack(f[m]);
	}
	getch();
}

void checkstats()
{
	int j;
	if (user.hp > 0 && cpu.hp <= 0)
	{
		gameover = 1;
		cout << "\nEnemy killed! You WIN!!!\nYou have "<<user.hp<<" HP left.\n";
	}
	else if (user.hp <= 0 && cpu.hp > 0)
	{
		gameover = 1;
		cout << "\nYou got killed! Sorry, You LOSE!!!\nEnemy has "<<cpu.hp<<" HP left.\n";
	}
	else if (user.hp <= 0 && cpu.hp <= 0)
	{
		gameover = 1;
		cout << "\nDRAW!!!\n";
	}
	if (gameover == 1)
		stopgame();
}

void stopgame()
{
	gameover = 0;
	user.hp=100;
	cpu.hp=100;
	user.defend=0;
	cpu.defend=0;
	char j;
	cout << "\n1. Next Round.\n2. Main Menu.\n0. Exit.\nEnter choice...";
	cin >> j;
	if (j == '1')
		startgame();
	else if (j == '2')
		startup();
	else if (j == '0')
		exit(0);
	else
	{
		cout<<"Invalid input. Please try again. Hit enter...\n";
		getch();
		stopgame();
	}
	getch();
}	
	
void help()
{
	cout <<
		"\nFIGHT NIGHT is a text based fighting game in which player fights against CPU.\nEach player starts with 100 HP and first to reach 0 HP loses.\nThere are various choices of attacks and defences.\nAttacks are punches and kicks, each divided into high power and low power. High power attacks do a great deal of damage but lack in any defence. Low power attacks have low damage but defend us. Defending blocks any enemy attack keeping your HP safe.\nSo, c'mon get'em down and be the King of FIGHT NIGHT...\nHit enter to continue...";
	getch();
	startup();
}

void about()
{
	cout <<
		"\nFIGHT NIGHT v1.0beta\nBy: Hrishi Hiraskar\n\nContact:-\nEmail: hrishihiraskar@gmail.com\nFacebook: http://www.facebook.com/hrishi.hiraskar7/\nHit enter to continue...";
	getch();
	startup();
}
