#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<fstream.h>

struct player{
    char name[50];
    int score;
}p;

class Snake                                                     //The Class that runs the game
{
      int p1,p2,v1,v2,v3,e1,e2,prev,now,n,colr,dsp,cnt,dly,m;
      int stp,egGen;
      int xr,yr;
      void caught();
 	public:
        long scr;
        int strtX,strtY,endX,endY;
        int pos[100][2];
        void show();
        void init();
        void egg();
        void transpose();
        void gnrtCond();
        void gnrtUnCond();
        void check();
        void checkEgg();
        void move();
        void chngDir();
        void sndEt();
        void sndCgt();
        int test();
        void score();
        Snake();
        Snake(Snake*);
         ~Snake();
};
Snake::Snake(){}
Snake::~Snake(){}

char menu()
{
	char choice;
	clrscr();
	cout<<"\n\n\t\t\t    ========= Menu ========="<<endl<<endl;
	cout<<"\n\t\t\t\t1> New Game [N] "<<endl;
	cout<<"\n\t\t\t\t2> How to play [H] "<<endl;
	cout<<"\n\t\t\t\t3> Highscores[S]" << endl;
	cout<<"\n\t\t\t\t4> Exit Game [X] " <<endl<< endl;
	cout<<"\n\t\t  Input choice: ";
	cin>> choice;
	if(choice=='X')
		exit(0);

	return choice;
}

void Snake::checkEgg()                                          //Checks the snake's and the egg's position 
{
    if((e1 == p1) && (e2 == p2))
	{   
    	sndEt();
     	egg();
     	dly--;
     	score();
     	n++;
  	}
}

void Snake::sndEt()                                             //Sounds for GAME OVER
{
    nosound();
    sound(500);
    delay(5);
    nosound();
}

void Snake::sndCgt()                                            //Sound for Caught
{
    nosound();
    for(int x=2000;x>440;x--)
    {
		sound(x);
		delay(2);
    }
    nosound();
}

void Snake::score()                                             //Changes the score
{ 
    char *p;

    ltoa(scr,p,10);
    settextstyle(8,0,1);
    setcolor(0);
    outtextxy(585,40,p);
    if(egGen != 1)
    {
	    scr = scr + dly / 10;
    }
    ltoa(scr,p,10);
    setcolor(10);
    outtextxy(585,40,p);
}
void Snake::gnrtCond()                                          //Moves the snake within the screen
{    
    if(n < 367)
    {
        if(now == 8 && (prev != 8 && prev != 2))
        {
            pos[0][0] = p1;
            pos[0][1] = p2 - dsp;
            prev = now;
        }
        if(now == 4 && (prev != 4 && prev != 1))
        {
            pos[0][0] = p1 + dsp;
            pos[0][1] = p2;
            prev = now;
        }
        if(now == 2 && (prev != 8 && prev != 2))
        {
            pos[0][0] = p1;
            pos[0][1] = p2 + dsp;
            prev = now;
        }
        if(now == 1 && (prev != 1 && prev != 4))
        {      
            pos[0][0] = p1 - dsp;
            pos[0][1] = p2;
            prev = now;
     	}
    }
}
void Snake::gnrtUnCond()                                        //Moves the snake outside the screen
{
    if( prev == 8 )
    {
        pos[0][0] = p1;
        pos[0][1] = p2 - dsp;
    }
    if( prev == 4 )
    {
        pos[0][0] = p1 + dsp;
        pos[0][1] = p2;
    }
    if( prev == 2 )
    {
        pos[0][0] = p1;
        pos[0][1] = p2 + dsp;
    }
    if( prev == 1 )
    {
        pos[0][0] = p1 - dsp;
        pos[0][1] = p2;
    }
    p1 = pos[0][0];
    p2 = pos[0][1];
}
void Snake::check()                                             //Checks the "head" "eats" the egg or bites itself
{
    if(p1 > endX)
    	p1 = strtX;
    else if(p1 < strtX)
        p1 = endX;
    if(p2 > endY)
        p2 = strtY;
    else if(p2 < strtY)
        p2 = endY;
    pos[0][0] = p1;
    pos[0][1] = p2;
    for(int i = 1; i < n; i++)
    { 
        if(p1 == pos[i][0] && p2 == pos[i][1])
        {
            caught();
            break;
        }
    }
}
void Snake::show()
{
    int x = getcolor();
    if(egGen != 1)
    {
        setcolor(getbkcolor());
        setfillstyle(1,getbkcolor());
        fillellipse(v1,v2,yr,yr);
    }
    else
        egGen = 0;
    if(egGen == 2)
        egGen--;
    setcolor(colr);
    setfillstyle(1,9);
    if(now == 8 || now == 2)
        fillellipse(pos[0][0],pos[0][1],xr,yr);
    else if(now == 4 || now == 1)
        fillellipse(pos[0][0],pos[0][1],yr,xr);
    setcolor(x);
}
void Snake::transpose()
{   int i,j,x,y;
    p1 = pos[0][0];
    p2 = pos[0][1];
    if(!egGen)
    {
       v1 = pos[n-1][0];
       v2 = pos[n-1][1];
    }
    else
    	egGen = 0;
   for(i = n-1; i >= 1; i--)
   {
        pos[i][0] = pos[i-1][0];
        pos[i][1] = pos[i-1][1];
   }
}
void Snake::move()
{ 
    int st = 0;
    do
    {
        if(!kbhit())
        {
            checkEgg();
            if(!st)
                show();
            else
                st = 0;
            delay(dly/4);
            transpose();
            delay(dly/4);
            gnrtUnCond();
            delay(dly/4);
            check();
            delay(dly/4);
        }
        else if(stp)
        {
            chngDir();
            gnrtCond();
            check();
            show();
            st = 1;
        }
   }while(stp);
}
void Snake::init()
{
    time_t tm;
    srand(time(&tm));
    dsp = 20;
    n = 5;
    prev = 4;
    for(int i = 4;i >= 0;i--)
    {
        pos[i][0] = 201 + (n - i - 1) * dsp;
        pos[i][1] = 301;
    }
    strtX = 21;
    strtY = 21;
    endX = 481;
    endY = 361;
    colr = 14;
    now = prev;
    dsp = 20;
    stp = 111;
    cnt = -1;
    scr = 0;
    dly = 130;
    xr = 3;
    yr = 9;
    egg();
    egGen = 1;
    score();
    int x = getcolor();
    setlinestyle(0,1,3);
    setcolor(15);
    rectangle(strtX-15,strtY-15,endX+15,endY+15);
    rectangle(endX+25,strtY-15,getmaxx()-15,endY+15);
    rectangle(strtX-15,endY+25,getmaxx()-15,getmaxy()-5);
    line(endX+25,strtY+75,getmaxx()-15,strtY+75);
    line(endX+25,strtY+200,getmaxx()-15,strtY+200);
    line(endX+25,strtY+275,getmaxx()-15,strtY+275);
    setlinestyle(0,1,1);
    settextstyle(8,0,1);
    setcolor(11);
    outtextxy(514,40,"SCORE");
    setcolor(14);
    settextstyle(11,0,5);
    outtextxy(524,110," CONTROLS ");
    outtextxy(522,135,"p = PAUSE");
    outtextxy(522,155,"g = RESUME");
    outtextxy(522,175,"e = EXIT");
    outtextxy(513,195," ARROWS FOR");
    outtextxy(512,205," MOVEMENT");
    setcolor(14);
    settextstyle(3,0,9);
    outtextxy(getmaxx()-500,getmaxy()-110,"SNAKE 2");
    settextstyle(3,0,2);
    setcolor(x);
}
void Snake::caught()
{
    stp = 0;
    sndCgt();
    for(int i=0;i<=8;i++)
    {
        if(i%2)
        {
      	  	setcolor(CYAN);
        	outtextxy(512,250,"GAME OVER");
        	sound(500);
        	delay(500);
        	nosound();
        }
        else
        {
            setcolor(0);
            outtextxy(512,250,"GAME OVER");
            delay(500);
        }
    }
    sleep(1);
}
void Snake::chngDir()
{
    int clr;
    fillsettingstype *p;
    char x = getch();
    if(x == 72)
        now = 8;
    else if(x == 77)
        now = 4;
    else if(x == 80)
        now = 2;
    else if(x == 75)
        now = 1;
    else if(x == 'e')
    {     
        for(int q=1000;q>=0;q--)
        {
            sound(q);
            delay(3);
        }
        nosound();
        closegraph();
        restorecrtmode();
	   	menu();
    }
    else if(x == 'p')
    { 
        int twnkl = 1;
        settextstyle(11,0,9);
        while(1)
        {
            if(kbhit())
            {
                int c = getch();
                if(c == 'g')
                {
                    clr = getcolor();
                    setcolor(0);
                    rectangle(endX+40,endY-10,getmaxx()-35,getmaxy()-160);
                    outtextxy(endX+60,endY-29,"PAUSED");
                    break;
                }
            }
            else
            {
                if(twnkl%2)
                {
                    clr = getcolor();
                    setcolor(10);
                    rectangle(endX+40,endY-10,getmaxx()-35,getmaxy()-160);
                    outtextxy(endX+60,endY-29,"PAUSED");
                    setcolor(clr);
                    delay(1000);
                }
                else
                {
                    clr = getcolor();
                    setcolor(0);
                    rectangle(endX+40,endY-10,getmaxx()-35,getmaxy()-160);
                    outtextxy(endX+60,endY-29,"PAUSED");
                    delay(1000);
                }
            }
            twnkl++;
        }
    settextstyle(8,0,1);
    }
}
Snake::Snake(Snake *p)
{
    *p=NULL;
}
void Snake::egg()
{ 
    do{
        e1 = (rand() % 100) * dsp + strtX;
        e2 = (rand() % 100) * dsp + strtY;
    }while(test());
    int x = getcolor();
    setcolor(7);
    setfillstyle(1,random(15)+1);
    fillellipse(e1,e2,xr+2,xr+2);
    setcolor(x);
    egGen = 2;
}
int Snake::test()                                           
{ 	int i;
    for(i=0;i<n;i++)
    {
        if(e1 == pos[i][0] && e2 == pos[i][1])
            break;
        if(v1 == e1 && v2 == e2)
		    break;
        if((e1 >= endX+1) || (e2 >= endY+1))
            break;
   	}
   	if(i != n)
		return 1;
   	else
		return 0;
}

void addPlayer()
{
    cout<< "Enter your Name: ";
    cin >> p.name;
    cout<< "Enter your Score: ";
    cin >> p.score;
    cout<< endl << "Thanks for your entry!" << endl;
    cout<< "Press any key to continue...";
    
    ofstream playerInfo("playerInfo.dat", ios::app | ios::binary);
	playerInfo.write((char*)&p, sizeof(p));	
	getch();	  	
    playerInfo.close();
}

void showScores()                   
{
	clrscr();
	char *line;
    cout<< endl
	    << "\t\t\t#--------------------------------#" << endl
	    << "\t\t\t#-----******SCOREBOARD******-----#" << endl
	    << "\t\t\t#--------------------------------#" << endl << endl
	    << "\t\tPlayer Name\t\t\t\tScore"<<endl;
	    
		ifstream playerInfo("playerInfo.dat", ios::out | ios::binary);
		if(playerInfo)
		{
		    while (!playerInfo.eof())
		    {	
				playerInfo.read((char*)&p, sizeof(p));
				cout<<"\t"<< p.name <<"\t\t"<< p.score << endl << endl; 
            }
        }
        else 
			cout << "Unable to open file."; 
    cout<<"\nPress any key to continue...";
    getch();
	playerInfo.close();
}

void rules()
{
	clrscr();
	char choose;
	cout<<"\n\n\t\t\t   !!! Welcome to Snake !!!"<<endl<<endl;

	cout<<"\t\t\t    ---Basic Game Play---"<<endl<<endl<<endl;
	cout<<"\t1. Use W,A,S,D to move the snake."<<endl<<endl;
	cout<<"\t2. W -> Up  \n"<<
		  "\t   A -> Left\n"<<
		  "\t   S -> Down\n"<<
		  "\t   D -> Right" <<endl<<endl;
	cout<<"\t3. Survive for as long as possible. Achieve the highest score !!"<<endl;
	cout<<"\t4. The game ends when the Snake bites it's own body."<< endl << endl;;
	cout<<"\t5. Remember your score and make sure to plug it into the highscore tables."<<endl << endl;
	cout<<"\tPress Y to return to menu."<<endl;
	cin>> choose;

	if(choose=='Y'||choose=='y')
	{
		menu();
	}
	else
		cout<<"Invalid input."<<endl;
	return;
}

void highsc()
{	
	int menuChoice = 0;
	clrscr();
    do{
    	clrscr();
		cout << endl << "\n\n\t\t\t######--- HIGH-SCORE MENU ---######" << endl << endl;
		cout << endl << "\t\t\t1) Add a High-Score entry\n";
		cout << endl << "\t\t\t2) Display the High Score table\n";
		cout << endl << "\t\t\t3) Delete current High Scores\n";
		cout << endl << "\t\t\t4) Quit the program\n" << endl;
		cout << endl << "Please enter your choice (1-4): ";
		cin  >> menuChoice;
		cout << endl;
		if(menuChoice < 1 || menuChoice > 4)
	    {
			cout <<"\t\tPlease select an existing option!" << endl;
			cout <<"Press any key to continue...";
			getch();
			highsc();
	 	}
		switch(menuChoice)                                          
		{
			case 1:	addPlayer();
					break;
			case 2:	showScores();
					break;
			case 3:	ofstream SaveFile("playerInfo.dat", ios::trunc);
					SaveFile.close();
					cout <<"High Scores successfully deleted." << endl;
					cout <<"Press any key to continue...";
					getch();
					break;
			case 4: menu();
					break;
			default:cout<<"Enter a valid choice (1-4):";
		}
    }while(menuChoice >= 1 || menuChoice <= 4);
}
void main()
{
	char choice;
	choice = menu();
	switch(choice)
	{
		case 'N': 	Snake snk;
					int gd=DETECT,gm,i,j,k,x,y;
					clrscr();
					int gdriver = DETECT, gmode, errorcode;

					initgraph(&gdriver, &gmode, "");
					initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
					snk.init();
					snk.move();
   					
					closegraph();
					restorecrtmode();
					break;

		case 'H': 	rules();
					break;
		case 'S': 	highsc();
					break;
		case 'X': 	exit(1);
					break;
		default: 	cout<<"Invalid entry: Only capital letters allowed."<<endl;
					break;
	}
	cout<<endl;
}
