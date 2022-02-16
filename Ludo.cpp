
#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#include<semaphore.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

bool dice_empty=true;
int selected_token=-1;
int getkeypress =1;
int dice_display=0;
int pl;

int dice_array[3]={0,0,0};
int win_array[4][4];
int check_thread[4]={0,0,0,0};

sem_t dice_1;
sem_t grid;
pthread_t master_thread;
pthread_t player[4];


void draw_turn(int player);


int which_player_turn() // finds which player turn using player turn order. As soon as it finds a one in player turn order array, it returns the player turn number.
{
	return pl;	
}

int token_array[4][4][2] = 
{
	{//RED COLOUR PATH
	{232,	138}, //inside home token holder #1
	{232,	238}, //inside home token holder #2
	{332,	138}, //inside home token holder #3
	{332,	238}  //inside home token holder #4
	},
	{//GREEN COLOUR PATH
	{232,	594}, //inside home token holder #1
	{232,	694}, //inside home token holder #2
	{332,	594}, //inside home token holder #3
	{332,	694}  //inside home token holder #4
	},
	{//YELLOW COLOUR PATH
	{688,	594}, //inside home token holder #1
	{688,	694}, //inside home token holder #2
	{788,	594}, //inside home token holder #3
	{788,	694} //inside home token holder #4
	},
	{// BLUE COLOUR PATH
	{688,	138}, //inside home token holder #1
	{688,	238}, //inside home token holder #2
	{788,	138}, //inside home token holder #3
	{788,	238}  //inside home token holder #4
	}
};

int current_pos[4][4][2];

int win_coordinates[4][2]=
{
	{509,	365	}, { 59	,	415	},{	509	,	465	},{	559	,	415	}
};


int coordinate_array[4][57][2] =  // contains all the coordinates for the tokens to placed and moved through out the ludo board.
{
{//RED COLOUR PATH
{	459	,	115	},{	459 ,	165	},{	459	,	215	},{	459	,	265	},{	459	,	315	},{	409	,	365	},{	359	,	365	},{	309	,	365	},{	259	,	365	},{	209	,	365	},{	159	,	365	},
{	159	,	415	},{	159	,	465	},{	209	,	465	},{	259	,	465	},{	309	,	465	},{	359	,	465	},{	409	,	465	},{	459	,	515	},{	459	,	565	},{	459	,	615	},{	459	,	665	},
{	459	,	715	},{	459	,	765	},{	509	,	765	},{	559	,	765	},{	559	,	715	},{	559	,	665	},{	559	,	615	},{	559	,	565	},{	559	,	515	},{	609	,	465	},{	659	,	465	},
{	709	,	465	},{	759	,	465	},{	809	,	465	},{	859	,	465	},{	859	,	415	},{	859	,	365	},{	809	,	365	},{	759	,	365	},{	709	,	365	},{	659	,	365	},{	609	,	365	},
{	559	,	315	},{	559	,	265	},{	559	,	215	},{	559	,	165	},{	559	,	115	},{	559	,	65	},{	509	,	65	},{	509	,	115	},{	509	,	165	},{	509	,	215	},{	509	,	265	},
{	509	,	315	},{	509	,	365	}
},
{ //GREEN COLOUR PATH
{	209	,	465	},{	259	,	465	},{	309	,	465	},{	359	,	465	},{	409	,	465	},{	459	,	515	},{	459	,	565	},{	459	,	615	},{	459	,	665	},{	459	,	715	},{	459	,	765	},
{	509	,	765	},{	559	,	765	},{	559	,	715	},{	559	,	665	},{	559	,	615	},{	559	,	565	},{	559	,	515	},{	609	,	465	},{	659	,	465	},{	709	,	465	},{	759	,	465	},
{	809	,	465	},{	859	,	465	},{	859	,	415	},{	859	,	365	},{	809	,	365	},{	759	,	365	},{	709	,	365	},{	659	,	365	},{	609	,	365	},{	559	,	315	},{	559	,	265	},
{	559	,	215	},{	559	,	165	},{	559	,	115	},{	559	,	65	},{	509	,	65	},{	459	,	65	},{	459	,	115	},{	459	,	165	},{	459	,	215	},{	459	,	265	},{	459	,	315	},
{	409	,	365	},{	359	,	365	},{	309	,	365	},{	259	,	365	},{	209	,	365	},{	159	,	365	},{	159	,	415	},{	209	,	415	},{	259	,	415	},{	309	,	415	},{	359	,	415	},
{	409	,	415	},{	459	,	415	}
},
{//YELLOW COLOUR PATH
{	559	,	715	},{	559	,	665	},{	559	,	615	},{	559	,	565	},{	559	,	515	},{	609	,	465	},{	659	,	465	},{	709	,	465	},{	759	,	465	},{	809	,	465	},{	859	,	465	},
{	859	,	415	},{	859	,	365	},{	809	,	365	},{	759	,	365	},{	709	,	365	},{	659	,	365	},{	609	,	365	},{	559	,	315	},{	559	,	265	},{	559	,	215	},{	559	,	165	},
{	559	,	115	},{	559	,	65	},{	509	,	65	},{	459	,	65	},{	459	,	115	},{	459	,	165	},{	459	,	215	},{	459	,	265	},{	459	,	315	},{	409	,	365	},{	359	,	365	},
{	309	,	365	},{	259	,	365	},{	209	,	365	},{	159	,	365	},{	159	,	415	},{	159 ,	465	},{	209	,	465	},{	259	,	465	},{	309	,	465	},{	359	,	465	},{	409	,	465	},
{	459	,	515	},{	459	,	565	},{	459	,	615	},{	459	,	665	},{	459	,	715	},{	459	,	765	},{	509	,	765	},{	509	,	715	},{	509	,	665	},{	509	,	615	},{	509	,	565	},
{	509	,	515	},{	509	,	465	}
},
{// BLUE COLOUR PATH
{	809	,	365	},{	759	,	365	},{	709	,	365	},{	659	,	365	},{	609	,	365	},{	559	,	315	},{	559	,	265	},{	559	,	215	},{	559	,	165	},{	559	,	115	},{	559	,	65	},
{	509	,	65	},{	459	,	65	},{	459	,	115	},{	459	,	165	},{	459	,	215	},{	459	,	265	},{	459	,	315	},{	409	,	365	},{	359	,	365	},{	309	,	365	},{	259	,	365	},
{	209	,	365	},{	159	,	365	},{	159	,	415	},{	159	,	465	},{	209	,	465	},{	259	,	465	},{	309	,	465	},{	359	,	465	},{	409	,	465	},{	459	,	515	},{	459	,	565	},
{	459	,	615	},{	459	,	665	},{	459	,	715	},{	459	,	765	},{	509	,	765	},{	559	,	765	},{	559	,	715	},{	559	,	665	},{	559	,	615	},{	559	,	565	},{	559	,	515	},
{	609	,	465	},{	659	,	465	},{	709	,	465	},{	759	,	465	},{	809	,	465	},{	859	,	465	},{	859	,	415	},{	809	,	415	},{	759	,	415	},{	709	,	415	},{	659 ,	415	},
{	609	,	415	},{	559	,	415	}
}
};

int savepoints[8][2] = 
{		//--------- RED BOXES------      ---------GREEN BOXES------      ------YELLOW BOXES---------   --------BLUE BOXES----------                           
	{	459	,	115	},{	259	,	365	},{	209	,	465	},{	459	,	665	},{	559	,	715	},{ 759	,	465 },{	809	,	365	},{	559	,	165	} 
};



void drawcentresquare(int x,int y,int size,float *colors)
{
   DrawSquare(x-size/2,y-size/2, size,colors);
}	





void draw_dice(int num) // Array to draw a dice on the screen using using graphic library
{

		// cout << "dice"<< num << endl;
		drawcentresquare(62,90,100,colors[NAVY]); 
		if(num==1) 
		{
			DrawCircle(62,90,7,colors[RED]);//center dot
		}
		if(num==2)
		{
			DrawCircle(62+14+14,90-28,7,colors[RED]);//bottom right dot
			DrawCircle(62-14-14,90+28,7,colors[RED]);//top left dot
		}
		if(num==3)
		{
			DrawCircle(62,90,7,colors[RED]);//center dot
			DrawCircle(62+14+14,90-28,7,colors[RED]);//bottom right dot
					DrawCircle(62-14-14,90+28,7,colors[RED]);//top left dot
		}
		if(num==4)
		{
			DrawCircle(62+14+14,90-28,7,colors[RED]);//bottom right dot
			DrawCircle(62-14-14,90-28,7,colors[RED]);//bottom left dot
			DrawCircle(62-14-14,90+28,7,colors[RED]);//top left dot
			DrawCircle(62+14+14,90+28,7,colors[RED]);//top right v
		}
		if(num==5)
		{
			DrawCircle(62,90,7,colors[RED]);//center dot
			DrawCircle(62+14+14,90-28,7,colors[RED]);//bottom right dot
			DrawCircle(62-14-14,90-28,7,colors[RED]);//bottom left dot
			DrawCircle(62-14-14,90+28,7,colors[RED]);//top left dot
			DrawCircle(62+14+14,90+28,7,colors[RED]);//top right dot
		}
		if(num==6)
		{
			DrawCircle(62+14+14,90-28,7,colors[RED]);//bottom right dot
			DrawCircle(62-14-14,90-28,7,colors[RED]);//bottom left dot
			DrawCircle(62-14-14,90+28,7,colors[RED]);//top left dot
			DrawCircle(62+14+14,90+28,7,colors[RED]);//top right dot
			DrawCircle(62-14-14,90,7,colors[RED]);//ceter left dot
			DrawCircle(62+14+14,90,7,colors[RED]);//ceneter right dot
		}
		if (num != 0)
			sleep(1);
}





void fill_dice() //function to fill the dice whenever the user enters a spacebar fill dice function fills dice array elements randomly.
{
	srand(time(0));             // seed the random numbers generator by current time...
	dice_array[0] = rand()%6+1; 

	if( dice_array[0] == 6) 
	{	
		dice_array[1] = rand()%6+1; 		//random numbers being stored between 1 to 6 inclusive.
		if( dice_array[1] == 6 )
		{
			dice_array[2] = rand()%6+1; 		//random numbers being stored between 1 to 6 inclusive.
			if( dice_array[2] == 6 )
			{
				for(int i = 0; i < 3; i++)
					dice_array[i] = 0;
			}
		} 
		else
		{
			dice_array[2]= 0; 		//random numbers being stored between 1 to 6 inclusive.
		}
	}
	else
	{
		dice_array[1]= 0;
		dice_array[2]= 0; 		//random numbers being stored between 1 to 6 inclusive.
	}	
}





void draw_greenhome()
{
	int colour=GREEN;
	int centx=282;
	int centy=648;
	drawcentresquare(centx,centy,304,colors[colour]);//bottom left big home.
	drawcentresquare(centx,centy,200,colors[WHITE]);//bottom left small square
	DrawCircle(centx+50,centy+50,22,colors[colour]);//token holders top right
	DrawCircle(centx-50,centy+50,22,colors[colour]);//token holder top left
	DrawCircle(centx-50,centy-50,22,colors[colour]);//token holder bottom left
	DrawCircle(centx+50,centy-50,22,colors[colour]);//token holder bottem right
	drawcentresquare(	259	,	369	,50,colors[GREEN]);//outside green
	drawcentresquare(	209	,	469	,50,colors[GREEN]);//outside green
	DrawTriangle(510,420,434,344,434,344+152,colors[GREEN]);//left inside triangle
	drawcentresquare(	209	,	419	,50,colors[GREEN]);//inside Green
	drawcentresquare(	259	,	419	,50,colors[GREEN]);//inside Green
	drawcentresquare(	309	,	419	,50,colors[GREEN]);//inside Green
	drawcentresquare(	359	,	419	,50,colors[GREEN]);//inside Green
	drawcentresquare(	409	,	419	,50,colors[GREEN]);//inside Green

}



void draw_yellowhome()
{
	int colour=ORANGE;
	int centx=738;
	int centy=648;
	drawcentresquare(centx,centy,304,colors[colour]);//bottom left big home.
	drawcentresquare(centx,centy,200,colors[WHITE]);//bottom left small square
	DrawCircle(centx+50,centy+50,22,colors[colour]);//token holders top right
	DrawCircle(centx-50,centy+50,22,colors[colour]);//token holder top left
	DrawCircle(centx-50,centy-50,22,colors[colour]);//token holder bottom left
	DrawCircle(centx+50,centy-50,22,colors[colour]);//token holder bottem right
	drawcentresquare(	459	,	669	,50,colors[ORANGE]);// outside yellow
	drawcentresquare(	559	,	719	,50,colors[ORANGE]);//outside yellow
	drawcentresquare(	509	,	719	,50,colors[ORANGE]);//inside ORANGE
	drawcentresquare(	509	,	669	,50,colors[ORANGE]);//inside ORANGE
	drawcentresquare(	509	,	619	,50,colors[ORANGE]);//inside ORANGE
	drawcentresquare(	509	,	569	,50,colors[ORANGE]);//inside ORANGE
	drawcentresquare(	509	,	519	,50,colors[ORANGE]);//inside ORANGE
	DrawTriangle(510,420,434,344+152,434+152,344+152,colors[ORANGE]);//top inside triangle

}



void draw_redhome()
{ 
	int colour=RED;
	int centx=282;
	int centy=192;
	drawcentresquare(centx,centy,304,colors[colour]);//bottom left big home.
	drawcentresquare(centx,centy,200,colors[WHITE]);//bottom left small square
	DrawCircle(centx+50,centy+50,22,colors[colour]);//token holders top right
	DrawCircle(centx-50,centy+50,22,colors[colour]);//token holder top left
	DrawCircle(centx-50,centy-50,22,colors[colour]);//token holder bottom left
	DrawCircle(centx+50,centy-50,22,colors[colour]);//token holder bottem right
	drawcentresquare(	509	,	119	,50,colors[colour]);//inside red
	drawcentresquare(	509	,	169	,50,colors[colour]);//inside red
	drawcentresquare(	509	,	219	,50,colors[colour]);//inside red
	drawcentresquare(	509	,	269	,50,colors[colour]);//inside red
	drawcentresquare(	509	,	319	,50,colors[colour]);//inside red
	drawcentresquare(	559	,	169	,50,colors[colour]);//outside red
	drawcentresquare(	459	,	119	,50,colors[colour]);//outside red
	DrawTriangle(510,420,434+152,344,434,344,colors[colour]);//bottom inside triangle

}



void draw_bluehome()
{ 	
	int colour=BLUE;
    int centx=738;
	int centy=192;
	
	DrawSquare( 586, 40,304,colors[colour]);//bottom right big home.
	drawcentresquare(738,192,200,colors[WHITE]);//bottom right small square
	drawcentresquare(	762	,	469	,50,colors[colour]);//outside blue
	drawcentresquare(	812	,	369	,50,colors[colour]);//outside blue
	drawcentresquare(	812	,	419	,50,colors[colour]);//inside blue
	drawcentresquare(	762	,	419	,50,colors[colour]);//inside blue
	drawcentresquare(	712	,	419	,50,colors[colour]);//inside blue
	drawcentresquare(	662	,	419	,50,colors[colour]);//inside blue
	drawcentresquare(	612	,	419	,50,colors[colour]);//inside blue
	DrawTriangle(510,420,434+152,344,434+152,344+152,colors[colour]);//right inside triangle
	DrawCircle(centx+50,centy+50,22,colors[colour]);//token holders top right
	DrawCircle(centx-50,centy+50,22,colors[colour]);//token holder top left
	DrawCircle(centx-50,centy-50,22,colors[colour]);//token holder bottom left
	DrawCircle(centx+50,centy-50,22,colors[colour]);//token holder bottem right

}






void draw_token(int x, int y ,int home)
{
	if (home==0)//red
	{
		home=1; //float color built in array index for red 
	}
	else if (home==1)//green
	{
		home=29; //float color built in array index for green
	}
	else if (home==2)//yellow
	{
		home=14; //float color built in array index for yellow
	}
	else if (home==3)//blue
	{
		home=65; //float color built in array index for blue.
	}
		DrawCircle(x,y+4,20,colors[home]);
}

bool save_check(int player, int token)
{
	for (int j = 0; j < 8 ; j++)
	{
		if( current_pos[player][token][0] == savepoints[j][0] && current_pos[player][token][1] == savepoints[j][1])
			return 1; 
	}
	return 0;
}

int get_token_position(int player, int selectedtoken)  //gets token postion from the coordinate array maybe
{
	//return boardarray[player][selectedtoken];
	for (int j = 0; j < 57; j++)
	{
		if(current_pos[player][selectedtoken][0] == coordinate_array[player][j][0] && current_pos[player][selectedtoken][1] == coordinate_array[player][j][1])
		{
			return j;
		}
	}
}


void collision_token(int player)
{
	bool b ;

	{
		for(int i = 0 ; i < 4; i++)
		{
			for(int j = 0 ; j < 4; j++)
			{
				if(j != player)
				{
					for(int k = 0 ; k < 4; k++)
					{
						if(current_pos[player][i][0] == current_pos[j][k][0] && current_pos[player][i][1] == current_pos[j][k][1])
						{
							b = save_check(player, i);
							if(b != 1)
							{
								current_pos[j][k][0] = token_array[j][k][0];
								current_pos[j][k][1] = token_array[j][k][1];
							}
						}
					}
				}	
			}	
		}
	}
}


void plot_tokens() //plots token on the board for all payers.
{
	for(int i = 0; i < 4; i++)// i is player 
	{ 
		for (int j = 0; j < 4; j++) // j is token foer each home.
		{ 
			int tokenpostion;
		  	int xxcor;
		  	int yycor;
	
			xxcor = current_pos[i][j][0];
			yycor = current_pos[i][j][1];
			draw_token(xxcor,yycor,i); // passes the coordinates to be drawn on the ludoboard.
			DrawString(xxcor-6,yycor-6,to_string(j+1),colors[WHITE]); //prints token numbers on each token.
		}	
	}
}

void move()
{
	srand(time(0));
	int val = 0;
	int count = 0;
	int b[4] = {-1,-1,-1,-1};
	if (dice_array[0] != 0 && dice_array[2] != 6)
	{
		cout << "dice "<<" :: ";
		for(int j = 0; j < 3; j++)
		{
			cout << dice_array[j] << " ";
			if(dice_array[j] == 6)
			{
				for(int i  = 0; i < 4; i++)
				{
					if (current_pos[pl][i][0] == token_array[pl][i][0] && current_pos[pl][i][1] == token_array[pl][i][1] )
					{
						current_pos[pl][i][0] = coordinate_array[pl][0][0];
						current_pos[pl][i][1] = coordinate_array[pl][0][1];
					//	b = 1;
						break;
					}
					if (i == 3)
					{
						int k;
						do
						{
							k = rand()%4;
						}while(win_array[pl][k] == 1);

						if (current_pos[pl][k][0] != token_array[pl][k][0] && current_pos[pl][k][1] != token_array[pl][k][1] )
						{
							int num = get_token_position(pl,k);
							current_pos[pl][k][0] = coordinate_array[pl][(num + 5)][0];
							current_pos[pl][k][1] = coordinate_array[pl][(num + 5)][1];
							break;
						}
					}
				}
			}
			else
			{
				
				if(dice_array[j] != 0)
				{
					int k ;
					for(int sa = 0; sa < 4; sa++)
					{
						if (current_pos[pl][sa][0] == token_array[pl][sa][0] && current_pos[pl][sa][1] == token_array[pl][sa][1])
						{
								b[sa] = 0;
								count++;
						}
						else
							b[sa] = 1;
					}
					k = rand()%4;
					if(count < 4)
					{
						if(b[k] == 0 )
						{
							for(; b[k] == 0 && win_array[pl][k] == 1;)
							{
								k = rand() % 4;
							}
						}
						if (current_pos[pl][k][0] != token_array[pl][k][0] && current_pos[pl][k][1] != token_array[pl][k][1] )
						{
							int num = get_token_position(pl,k);
							for(int c1 = 0; (num + dice_array[j]) > 56 ; c1++)
							{
								if(c1 > 3)
								{
										k = 10;
										break;
								}
								num = get_token_position(pl,c1);
								k = c1;
							}
							if(k != 10)
							{
								current_pos[pl][k][0] = coordinate_array[pl][(num + dice_array[j])][0];
								current_pos[pl][k][1] = coordinate_array[pl][(num + dice_array[j])][1];
								break;
							}
						}
					}
				}
			}
		}
		cout << endl;
	}
	//-------------------- CHECKNG WINNING --------------------------

	for (int i =0; i < 4; i++)
	{
		if(current_pos[pl][i][0] == win_coordinates[pl][0] && current_pos[pl][i][1] == win_coordinates[pl][1] )
		{
			win_array[pl][i] = 1;
		}
	}

}

void checking_thread(int player)
{
	int count_1 = 0;
	for(int i = 0; i < 4; i++ )
	{
		if(win_array[player][i] == 1 )
			count_1++;
	}
	if(count_1 == 4)
	{
		for(int i = 0; i < 4 ; i++ )
		{
			if (i == player)
				check_thread[i] = 1;
		}
	}
}


void draw_ludoboard()
{

//	sem_wait(&dice_1);

		DrawSquare( 126 , 36,768,colors[BLACK]);//ludoboard box outline
		DrawSquare( 434, 344,152,colors[WHITE]);// ludoboard white background.


		/////smal boxes

		drawcentresquare(	459	,	169	,50,colors[WHITE]);
		drawcentresquare(	459	,	219	,50,colors[WHITE]);
		drawcentresquare(	459	,	269	,50,colors[WHITE]);
		drawcentresquare(	459	,	319	,50,colors[WHITE]);
		drawcentresquare(	409	,	369	,50,colors[WHITE]);
		drawcentresquare(	359	,	369	,50,colors[WHITE]);
		drawcentresquare(	309	,	369	,50,colors[WHITE]);

		drawcentresquare(	209	,	369	,50,colors[WHITE]);
		drawcentresquare(	159	,	369	,50,colors[WHITE]);
		drawcentresquare(	159	,	419	,50,colors[WHITE]);
		drawcentresquare(	159	,	469	,50,colors[WHITE]);

		drawcentresquare(	259	,	469	,50,colors[WHITE]);
		drawcentresquare(	309	,	469	,50,colors[WHITE]);
		drawcentresquare(	359	,	469	,50,colors[WHITE]);
		drawcentresquare(	409	,	469	,50,colors[WHITE]);
		drawcentresquare(	459	,	519	,50,colors[WHITE]);
		drawcentresquare(	459	,	569	,50,colors[WHITE]);
		drawcentresquare(	459	,	619	,50,colors[WHITE]);

		drawcentresquare(	459	,	719	,50,colors[WHITE]);
		drawcentresquare(	459	,	769	,50,colors[WHITE]);
		drawcentresquare(	509	,	769	,50,colors[WHITE]);
		drawcentresquare(	559	,	769	,50,colors[WHITE]);

		drawcentresquare(	559	,	669	,50,colors[WHITE]);
		drawcentresquare(	559	,	619	,50,colors[WHITE]);
		drawcentresquare(	559	,	569	,50,colors[WHITE]);
		drawcentresquare(	559	,	519	,50,colors[WHITE]);
		drawcentresquare(	612 ,	469	,50,colors[WHITE]);
		drawcentresquare(	662	,	469	,50,colors[WHITE]);
		drawcentresquare(	712	,	469	,50,colors[WHITE]);

		drawcentresquare(	812	,	469	,50,colors[WHITE]);
		drawcentresquare(	862 ,	469	,50,colors[WHITE]);
		drawcentresquare(	862	,	419	,50,colors[WHITE]);
		drawcentresquare(	862	,	369	,50,colors[WHITE]);

		drawcentresquare(	762	,	369	,50,colors[WHITE]);
		drawcentresquare(	712	,	369	,50,colors[WHITE]);
		drawcentresquare(	662	,	369	,50,colors[WHITE]);
		drawcentresquare(	612	,	369	,50,colors[WHITE]);
		drawcentresquare(	559	,	319	,50,colors[WHITE]);
		drawcentresquare(	559	,	269	,50,colors[WHITE]);
		drawcentresquare(	559	,	219	,50,colors[WHITE]);

		drawcentresquare(	559	,	119	,50,colors[WHITE]);
		drawcentresquare(	559	,	69	,50,colors[WHITE]);
		drawcentresquare(	509	,	69	,50,colors[WHITE]);
		drawcentresquare(	459	,	69	,50,colors[WHITE]);
		///end small boxes

		draw_redhome(); //draws the red part of the ludoboard
		draw_bluehome(); //draws the blue part of the ludoboard
		draw_yellowhome(); //draws the yellow part of the ludoboard
		draw_greenhome(); //draws the green part of the ludoboard
		plot_tokens(); //draws tokens for all homes on the ludoboard
	
		sleep(1);


		draw_turn(pl);
		
		for (int i = 0; i < 3; i++)
		{	
			if (dice_array[i] != 0)
			{
				draw_dice(dice_array[i]);
				//sleep(1);
			}
		}
}


void draw_turn(int player)
{
	if(pl>-1)	
	{
		if (pl==0)
		{
			DrawString( 10, 810, "Turn : Red", colors[RED]);  //open GL functions used to display strings on the display board.
		}
		else if (pl==1)
		{
			DrawString( 10, 810, "Turn : Green", colors[29]);  //open GL functions used to display strings on the display board.
		}
		else if (pl==2)
		{
			DrawString( 10, 810, "Turn : Yellow", colors[14]);  //open GL functions used to display strings on the display board.
		}	
		else if (pl==3)
		{		
			DrawString( 10, 810, "Turn : Blue", colors[65]);  //open GL functions used to display strings on the display board.
		}
	}
}



int get_token_cordinates(char xy, int player, int selectedtoken) // gets exact token coordinates.
{
	if (xy == 'x')
	{
		return coordinate_array[player][get_token_position(player,selectedtoken)][0]; // stores the x coordinate
	}
	else if (xy == 'y')
	{
		return coordinate_array[player][get_token_position(player,selectedtoken)][1]; // stores the y coordinate
	}
	
}




/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void SetCanvasSize(int width, int height) 
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}



/*
 * Main Canvas drawing function.
 */
//Board *b;
void GameDisplay()/**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,2] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1.1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	
    draw_ludoboard();
	
	   
	glutSwapBuffers(); // do not modify this line..

}



/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {

	if (key == 27/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}

	if (key==32 && getkeypress==1) /* space key ASCII*/
	{
		
		//fill_dice(dice_array); // roll dice when space key is pressed.
		dice_empty=false; 
		getkeypress=0;
		
		
	}
	if (dice_display==0) // if dice is not being displayed then press escape to fill dice and display it.
	{
		if (key==32 )
		{
			dice_display=1;
		}
	}
	
	if ((dice_empty==false)&&(dice_display==1)) //only select token if dice is displayed and dice is not empty
	{
		if (key==49)//1 key
		{
			selected_token=0;
		}
		else if (key==50)//2 key
		{
			selected_token=1;
		}
		else if (key==51)//3 key
		{
			selected_token=2;
		}
		else if (key==52)//4 key
		{
			selected_token=3;
		}
	}
	glutPostRedisplay(); // contineous infinite loop so that board does not disappear.
}

void* player_function(void * arg)
{
	sem_wait(&dice_1);
		int p = *(int*)arg;
		pl = p;
		sleep(1);
		fill_dice();
	sem_post(&dice_1);
	
	sem_wait(&grid);
	move();
	collision_token(pl);
	sleep(1);
	sem_post(&grid);
	
	checking_thread(pl);

	pthread_exit(NULL);
}

void* master_function(void * arg)
{
	sem_init(&dice_1, 0, 1);
	sem_init(&grid,0,1);

	int Array[4]= {0,1,2,3};
	while(true)
	{
		for( int j = 0; j < 4; j++)
		{
			if(check_thread[j] != 1)
			{
				if(pthread_create(&player[j],NULL,&player_function,&Array[j])!=0)	
				cout<<"Hello World"<<endl;
			}
		}
		for(int i=0; i<4; i++ )
		{
			if(check_thread[i] != 1)
				pthread_join(player[i],NULL);
		}
		cout<<"\n Round completed\n\n";
		sleep(1);
	}

}



/*
 * This function is called after every 1000/60 /FPS milliseconds
 * (FPS is defined on in the beginning).
 * Ythis function is being used to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {


	// once again we tell the library to call Timer function after next 1000/FPS
	glutTimerFunc(110, Timer, 0);

	glutPostRedisplay();
}



/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) 
{
	y=840-y;
	
	printf("%d %d",x,y);
	puts("");
	
}
void MouseMoved(int x, int y) {

	
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		
				y = 840-y;
			
					printf("%d %d",x,y);
					puts("");
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
}



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {


	for (int a = 0; a < 4; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			for (int c = 0; c < 2; c++)
			{
				current_pos[a][b][c] = token_array[a][b][c];
			}
		}
	}
	for(int i = 0; i < 4 ; i++)
	{
		for(int j  = 0; j < 4; j++)
		{
			win_array[i][j] = 0;
		}
	}

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);

	glutInit(&argc, argv); // initialize the graphics library...
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OS Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	
	
	pthread_create(&master_thread,NULL,&master_function,NULL);
	pthread_detach(master_thread);



	// you are telling the library names of function to call for different tasks.
//	glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutTimerFunc(1000.0, Timer, 0); // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...


	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop(); // infinite background loop.

	//glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif 