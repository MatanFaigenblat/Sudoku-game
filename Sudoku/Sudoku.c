#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "Sudoku.h"

static int panelGame, panelSettings, panelMain, panelAch, panelAbout;
FILE *fp;
int diff,obs,temp_val;
int sec=0,min=0,hour=0;
int mistake=0;
int rowlength=0,columnlength=0;
int cube_start_row=0,cube_end_row=0,cube_start_column=0,cube_end_column=0;
char name[20][20],playerName[20];
char line [30],headline[30];
int sec_arr[1000],min_arr[1000],hour_arr[1000];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelGame = LoadPanel (0, "Sudoku.uir", GAME)) < 0)
		return -1;
	if ((panelSettings = LoadPanel (0, "Sudoku.uir", SETTINGS)) < 0)
		return -1;
	if ((panelAch = LoadPanel (0, "Sudoku.uir", ACH)) < 0)
		return -1;
	if ((panelAbout = LoadPanel (0, "Sudoku.uir", ABOUT)) < 0)
		return -1;
	if ((panelMain = LoadPanel (0, "Sudoku.uir", MAIN)) < 0)
		return -1;


	DisplayPanel (panelMain);
	RunUserInterface ();
	DiscardPanel (panelGame);
	DiscardPanel (panelSettings);
	DiscardPanel (panelAch);
	DiscardPanel (panelAbout);
	DiscardPanel (panelMain);
	return 0;
}

int CVICALLBACK goBackFunction (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			SetCtrlAttribute (panelMain, MAIN_CONTINUEBUTTON, ATTR_DIMMED, 0);
			HidePanel (panelGame);

			break;
	}
	return 0;
}

int CVICALLBACK cancelFunction (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			HidePanel (panelSettings);

			break;
	}
	return 0;
}

int CVICALLBACK outFunction (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			HidePanel (panelAch);

			break;
	}
	return 0;
}

int CVICALLBACK quitAboutFunction (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			
			HidePanel (panelAbout);
			
			break;
	}
	return 0;
}


int CVICALLBACK quitFunction (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			
			QuitUserInterface (0);
			
			break;
	}
	return 0;
}



int CVICALLBACK continueFunction (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DisplayPanel (panelGame);

			break;
	}
	return 0;
}

int CVICALLBACK settingsFunction (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DisplayPanel (panelSettings);
			SetCtrlVal (panelSettings, SETTINGS_DIFF_RING, -1);
			SetCtrlVal (panelSettings, SETTINGS_OBS_RING, -1);
			SetCtrlAttribute (panelSettings, SETTINGS_SAVEBUTTON, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelSettings, SETTINGS_OBS_RING, ATTR_DIMMED, 1);

			break;
	}
	return 0;
}

int CVICALLBACK newGameFunction (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int num_rand,r,c,cell,value;
	int counter_obs=0;
	int x=0,y=0;
	int flag;

	switch (event)
	{
		case EVENT_COMMIT:


			sec=0;
			min=0;
			hour=0;
			mistake=0;
			SetCtrlVal (panelGame, GAME_MISTAKESNUMERIC, mistake);

			GetNumTableRows (panelGame, GAME_SUDOKUTABLE, &r);
			GetNumTableColumns (panelGame, GAME_SUDOKUTABLE, &c);

			for(int i=1; i<=r; i++)
			{
				for (int j=1; j<=c; j++)
				{
					SetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (i, j), 0);
					SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (i, j), ATTR_CELL_DIMMED, 0);
					SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (i, j), ATTR_TEXT_COLOR, VAL_BLACK);
				}
			}


			while(counter_obs<r-1-obs)
			{
				flag=0;
				x=rand()%r+1;
				y=rand()%c+1;

				GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint(x, y), &cell);

				if(cell==0)
				{
					num_rand=rand()%r+1;

					for(int i=1; i<=c; i++)
					{
						GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint(x, i), &value);
						if(value==num_rand)
						{
							flag++;
							break;
						}
					}

					if(flag==0)
					{
						for(int i=1; i<=r; i++)
						{
							GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint(i, y), &value);
							if(value==num_rand)
							{
								flag++;
								break;
							}
						}

						if(flag==0)
						{

							//checks row
							if(y>=1 && y<=3)
							{
								cube_start_row=1;
								cube_end_row=3;
							}
							else if(y>=4 && y<=6)
							{
								cube_start_row=4;
								cube_end_row=6;
							}
							else if(y>=7 && y<=9)
							{
								cube_start_row=7;
								cube_end_row=9;
							}

							//checks column
							if(x>=1 && x<=3)
							{
								cube_start_column=1;
								cube_end_column=3;
							}
							else if(x>=4 && x<=6)
							{
								cube_start_column=4;
								cube_end_column=6;
							}
							else if(x>=7 && x<=9)
							{
								cube_start_column=7;
								cube_end_column=9;
							}


							for(int i=cube_start_row; i<=cube_end_row; i++)
							{
								for(int j=cube_start_column; j<=cube_end_column; j++)
								{
									GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint(j, i), &value);
									if(value==num_rand)
									{
										flag++;
										break;
									}
								}
							}

							if(flag==0)
							{
								SetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (x, y), num_rand);
								SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (x, y), ATTR_CELL_DIMMED, 1);
								counter_obs++;
							}
						}

					}
				}


			}

			SetCtrlAttribute (panelGame, GAME_EXITTABLEBUTTON, ATTR_VISIBLE, 0);
			SetCtrlAttribute (panelGame, GAME_CHECKTIMER, ATTR_ENABLED, 1);
			DisplayPanel (panelGame);
			break;


	}


	return 0;
}

int CVICALLBACK diffFunction (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal (panelSettings, SETTINGS_DIFF_RING, &diff);
			
			if(diff==-1)
			{
				MessagePopup ("Error", "Pick an option from the list");
				break;
			}

			DeleteTableRows (panelGame, GAME_SUDOKUTABLE, 1, -1);
			DeleteTableColumns (panelGame, GAME_SUDOKUTABLE, 1, -1);


			if(diff==0)
			{


				SetCtrlVal (panelGame, GAME_DIFFICULTYSTRING, "Novice");
				SetCtrlVal (panelAch, ACH_DIFFSTRING, "Novice 3x3");
				
				InsertTableRows (panelGame, GAME_SUDOKUTABLE, 1, 3, VAL_CELL_NUMERIC);
				InsertTableColumns (panelGame, GAME_SUDOKUTABLE, 1, 3, VAL_CELL_NUMERIC);

			}

			else if(diff==1)
			{
				SetCtrlVal (panelGame, GAME_DIFFICULTYSTRING, "Expert");
				SetCtrlVal (panelAch, ACH_DIFFSTRING, "Expert 6x6"); 

				InsertTableRows (panelGame, GAME_SUDOKUTABLE, 1, 6, VAL_CELL_NUMERIC);
				InsertTableColumns (panelGame, GAME_SUDOKUTABLE, 1, 6, VAL_CELL_NUMERIC);
			}

			else if(diff==2)
			{
				SetCtrlVal (panelGame, GAME_DIFFICULTYSTRING, "Master");
				SetCtrlVal (panelAch, ACH_DIFFSTRING, "Master 9x9");

				InsertTableRows (panelGame, GAME_SUDOKUTABLE, 1, 9, VAL_CELL_NUMERIC);
				InsertTableColumns (panelGame, GAME_SUDOKUTABLE, 1, 9, VAL_CELL_NUMERIC);

				SetCtrlAttribute (panelSettings, SETTINGS_OBS_RING, ATTR_DIMMED, 0);
			}


			SetCtrlVal (panelSettings, SETTINGS_OBS_RING, -1);
			SetCtrlAttribute (panelSettings, SETTINGS_SAVEBUTTON, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelSettings, SETTINGS_OBS_RING, ATTR_DIMMED, 0);

			break;
	}
	return 0;
}

int CVICALLBACK obsFunction (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal (panelSettings, SETTINGS_OBS_RING, &obs);

			if(obs==-1)
			{
				MessagePopup ("Error", "Pick an option from the list");
				break;
			}

			SetCtrlAttribute (panelSettings, SETTINGS_SAVEBUTTON, ATTR_DIMMED, 0);

			break;
	}
	return 0;
}

int CVICALLBACK saveFunction (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			SetCtrlAttribute (panelMain, MAIN_NEWGAMEBUTTON, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelMain, MAIN_CONTINUEBUTTON, ATTR_DIMMED, 1);
			GetCtrlVal (panelSettings, SETTINGS_NAMESTRING,playerName);
			break;
	}
	return 0;
}

int CVICALLBACK sudokuFunction (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int cell_val,strikes;
	int nflag=0, mistakeflag=0;
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			//EventData1 = Row Postion
			//EventData2 = Column Postion
		{
			GetCtrlVal (panelSettings, SETTINGS_STRIKESSLIDE, &strikes);
			GetNumTableRows (panelGame, GAME_SUDOKUTABLE, &rowlength);
			GetNumTableColumns (panelGame, GAME_SUDOKUTABLE, &columnlength);


			if(strikes>mistake || strikes==0)
			{
				GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint(eventData2,eventData1), &cell_val);

				SetTableCellRangeAttribute (panelGame, GAME_SUDOKUTABLE, MakeRect (1, 1, rowlength, columnlength), ATTR_MAX_VALUE, rowlength);

				SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2, eventData1), ATTR_TEXT_COLOR, VAL_BLACK);

				//checks table
				nflag=0;

				for(int i=1; i<=rowlength; i++)
				{
					GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2,i), &temp_val);

					if(cell_val==temp_val  && eventData1 != i)
					{
						mistake++;
						SetCtrlVal (panelGame, GAME_MISTAKESNUMERIC, mistake);
						SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2, eventData1), ATTR_TEXT_COLOR, VAL_RED);

						mistakeflag++;
						nflag++;
						break;
					}
				}

				if(nflag==0)
				{
					for(int i=1; i<=rowlength; i++)
					{
						GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (i,eventData1), &temp_val);

						if(cell_val==temp_val && eventData2 != i)
						{
							mistake++;
							SetCtrlVal (panelGame, GAME_MISTAKESNUMERIC, mistake);
							SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2, eventData1), ATTR_TEXT_COLOR, VAL_RED);

							mistakeflag++;
							break;
						}


					}
				}

				//checks cube
				if(diff==2)
				{
					//checks row
					if(eventData1>=1 && eventData1<=3)
					{
						cube_start_row=1;
						cube_end_row=3;
					}
					else if(eventData1>=4 && eventData1<=6)
					{
						cube_start_row=4;
						cube_end_row=6;
					}
					else if(eventData1>=7 && eventData1<=9)
					{
						cube_start_row=7;
						cube_end_row=9;
					}

					//checks column
					if(eventData2>=1 && eventData2<=3)
					{
						cube_start_column=1;
						cube_end_column=3;
					}
					else if(eventData2>=4 && eventData2<=6)
					{
						cube_start_column=4;
						cube_end_column=6;
					}
					else if(eventData2>=7 && eventData2<=9)
					{
						cube_start_column=7;
						cube_end_column=9;
					}

					nflag=0;

					for(int i=cube_start_row; i<=cube_end_row; i++)
					{
						for(int j=cube_start_column; j<=cube_end_column; j++)
						{
							GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (j,i), &temp_val);

							if(cell_val==temp_val  && eventData1 != i && mistakeflag==0)
							{
								mistake++;
								SetCtrlVal (panelGame, GAME_MISTAKESNUMERIC, mistake);
								SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2, eventData1), ATTR_TEXT_COLOR, VAL_RED);

								nflag++;
								break;
							}
							if(nflag>0)
							{
								nflag=0;
								break;
							}
						}
					}
				}
				mistakeflag=0;

				if(strikes==mistake && strikes!=0)
				{
					MessagePopup ("Game Over", "You lost!!!");
					SetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (eventData2, eventData1), ATTR_TEXT_COLOR, VAL_RED);
					SetCtrlAttribute (panelGame, GAME_CHECKTIMER, ATTR_ENABLED, 0);
					SetCtrlAttribute (panelGame, GAME_EXITTABLEBUTTON, ATTR_VISIBLE, 1);
					SetTableCellRangeAttribute (panelGame, GAME_SUDOKUTABLE, MakeRect (1, 1, columnlength, rowlength), ATTR_CELL_DIMMED, 1);
				}
			}

		}
	}
	return 0;
}

int CVICALLBACK functionCheckTimer (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	int color_val;
	int count=0,csv_count=0;
	int timeofplayer=0,timeofwinner=0,timeofwinner2=0;
	int sec_tmp,min_tmp,hour_tmp;
	char name_tmp[20];
	char filename[20]="Achievement ";
	char number[10];
	
	sprintf(number, "%d", diff);
	
	strcat(filename,number);
	strcat(filename,".csv");
	
	switch (event)
	{
		case EVENT_TIMER_TICK:

			SetCtrlVal (panelGame, GAME_NUMERIC_SEC, sec);
			if(sec==60)
			{
				min++;
				sec=0;
				SetCtrlVal (panelGame, GAME_NUMERIC_MIN, min);
				if(min==60)
				{
					hour++;
					min=0;
					SetCtrlVal (panelGame, GAME_NUMERIC_MIN, hour);
				}
			}

			for(int i=1; i<=rowlength; i++)
			{
				for(int j=1; j<=columnlength; j++)
				{
					GetTableCellVal (panelGame, GAME_SUDOKUTABLE, MakePoint (j,i), &temp_val);
					GetTableCellAttribute (panelGame, GAME_SUDOKUTABLE, MakePoint (j,i), ATTR_TEXT_COLOR, &color_val);

					if(temp_val!=0 && color_val== VAL_BLACK)
					{
						count++;
					}
				}
			}

			if(count>0 && count==rowlength*columnlength)
			{
				MessagePopup ("Congratulation", "Good Job!\n\nYou made it!!!");
				SetCtrlAttribute (panelGame, GAME_CHECKTIMER, ATTR_ENABLED, 0);
				SetCtrlAttribute (panelGame, GAME_EXITTABLEBUTTON, ATTR_VISIBLE, 1);
				SetTableCellRangeAttribute (panelGame, GAME_SUDOKUTABLE, MakeRect (1, 1, columnlength, rowlength), ATTR_CELL_DIMMED, 1);
				
				fp=fopen(filename,"r");

				fgets (headline, 29, fp);
				fgets (headline, 29, fp);

				while(fgets(line,29,fp)!=0)
				{
					sscanf(line,"%d,%d,%d,%s",&sec_arr[csv_count],&min_arr[csv_count],&hour_arr[csv_count],name[csv_count]);
					csv_count++;
				}
				fclose(fp);

				timeofplayer = hour*3600+min*60+sec;

				//order the winners by time (secs)
				for(int i=0; i<3; i++)
				{

					timeofwinner = hour_arr[i]*3600+min_arr[i]*60+sec_arr[i];

					for(int j=i+1; j<3; j++)
					{
						timeofwinner2 = hour_arr[j]*3600+min_arr[j]*60+sec_arr[j];
						if(timeofwinner2<timeofwinner)
						{
							sec_tmp=sec_arr[i];
							min_tmp=min_arr[i];
							hour_tmp=hour_arr[i];
							strcpy(name_tmp,name[i]);

							sec_arr[i]=sec_arr[j];
							min_arr[i]=min_arr[j];
							hour_arr[i]=hour_arr[j];
							strcpy(name[i],name[j]);

							sec_arr[j]=sec_tmp;
							min_arr[j]=min_tmp;
							hour_arr[j]=hour_tmp;
							strcpy(name[j],name_tmp);

						}

					}

				}

				for(int i=3; i>0; i--)
				{
					timeofwinner = hour_arr[i]*3600+min_arr[i]*60+sec_arr[i];

					if(timeofplayer<timeofwinner)
					{
					
						sec_arr[i]=sec;
						min_arr[i]=min;
						hour_arr[i]=hour;
						strcpy(name[i],playerName);
						break;
					}
				}
				
				//second order after adding the player time
				for(int i=0; i<3; i++)
				{

					timeofwinner = hour_arr[i]*3600+min_arr[i]*60+sec_arr[i];

					for(int j=i+1; j<3; j++)
					{
						timeofwinner2 = hour_arr[j]*3600+min_arr[j]*60+sec_arr[j];
						if(timeofwinner2<timeofwinner)
						{
							sec_tmp=sec_arr[i];
							min_tmp=min_arr[i];
							hour_tmp=hour_arr[i];
							strcpy(name_tmp,name[i]);

							sec_arr[i]=sec_arr[j];
							min_arr[i]=min_arr[j];
							hour_arr[i]=hour_arr[j];
							strcpy(name[i],name[j]);

							sec_arr[j]=sec_tmp;
							min_arr[j]=min_tmp;
							hour_arr[j]=hour_tmp;
							strcpy(name[j],name_tmp);

						}

					}

				}

				fp=fopen(filename,"w");
				fprintf(fp,"%s,%s,%s,%s\n","Seconds:","Minutes:","Hours:","Name:");

				for(int i=0; i<csv_count; i++)
					fprintf(fp,"%d,%d,%d,%s\n",sec_arr[i],min_arr[i],hour_arr[i],name[i]);
				fclose(fp);


				for(int i=0; i<3; i++)
				{
					SetTableCellVal (panelAch, ACH_TABLE, MakePoint(1,i+1), name[i]);
					SetTableCellVal (panelAch, ACH_TABLE, MakePoint(2,i+1), hour_arr[i]);
					SetTableCellVal (panelAch, ACH_TABLE, MakePoint(3,i+1), min_arr[i]);
					SetTableCellVal (panelAch, ACH_TABLE, MakePoint(4,i+1), sec_arr[i]);
				}

				DisplayPanel (panelAch);
			}

			sec++;

			break;
	}
	return 0;
}

int CVICALLBACK exitTableFunction (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			HidePanel (panelGame);
			rowlength=0;
			columnlength=0;
			
			break;
	}
	return 0;
}

void CVICALLBACK helpBar (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	MessagePopup ("Help", "To play this game, you have to follow the instructions:\n\n\n  1. Enter the settings menu.\n  2. Choose from the following options:\n\n    a) Difficulty - the higher the difficulty, the bigger the table.\n    b) Obstacles - the higher the level u pick, the fewer obstacles u will have.\n    c) Strikes - how many mistakes can be made. 0 means not limition.\n\n  3. Prese save & start a new game.\n  4. Have Fun!!!!");
}

void CVICALLBACK adBar (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
	OpenDocumentInDefaultViewer ("Accompanying Document.docx", VAL_MAXIMIZE);
}

void CVICALLBACK aboutBar (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	DisplayPanel (panelAbout);
}

int CVICALLBACK instructionsFunction (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			if(diff==0)
			{
				MessagePopup ("instructions", "Each row & column in the table needs to be filled out with the the number 1-3, without repeating any numbers within the row and column.");
			}

			else if(diff==1)
			{
				MessagePopup ("instructions", "Each row & column in the table needs to be filled out with the the number 1-6, without repeating any numbers within the row and column.");
			}
				
			else
			{
				MessagePopup ("instructions", "Each row & column in the table needs to be filled out with the the number 1-9, without repeating any numbers within the row, column or square.");
			}


			break;
	}
	return 0;
}

int CVICALLBACK demoFunction (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			OpenDocumentInDefaultViewer ("Demo.mp4", VAL_MAXIMIZE);

			break;
	}
	return 0;
}
