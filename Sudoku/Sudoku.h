/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ABOUT                            1       /* callback function: quitAboutFunction */
#define  ABOUT_ID                         2       /* control type: textMsg, callback function: (none) */
#define  ABOUT_NAME                       3       /* control type: textMsg, callback function: (none) */
#define  ABOUT_WRITEN                     4       /* control type: textMsg, callback function: (none) */
#define  ABOUT_PICTURE                    5       /* control type: picture, callback function: (none) */

#define  ACH                              2       /* callback function: outFunction */
#define  ACH_TABLE                        2       /* control type: table, callback function: (none) */
#define  ACH_CHAMPION                     3       /* control type: picture, callback function: (none) */
#define  ACH_DIFFSTRING                   4       /* control type: string, callback function: (none) */
#define  ACH_MEDAL                        5       /* control type: picture, callback function: (none) */

#define  GAME                             3       /* callback function: goBackFunction */
#define  GAME_SUDOKUTABLE                 2       /* control type: table, callback function: sudokuFunction */
#define  GAME_MISTAKESNUMERIC             3       /* control type: numeric, callback function: (none) */
#define  GAME_DIFFICULTYSTRING            4       /* control type: string, callback function: (none) */
#define  GAME_INSTRUCTIONBUTTON           5       /* control type: command, callback function: instructionsFunction */
#define  GAME_EXITTABLEBUTTON             6       /* control type: command, callback function: exitTableFunction */
#define  GAME_CHECKTIMER                  7       /* control type: timer, callback function: functionCheckTimer */
#define  GAME_NUMERIC_HOUR                8       /* control type: numeric, callback function: (none) */
#define  GAME_NUMERIC_SEC                 9       /* control type: numeric, callback function: (none) */
#define  GAME_NUMERIC_MIN                 10      /* control type: numeric, callback function: (none) */

#define  MAIN                             4       /* callback function: quitFunction */
#define  MAIN_NEWGAMEBUTTON               2       /* control type: command, callback function: newGameFunction */
#define  MAIN_SETTINGSBUTTON              3       /* control type: command, callback function: settingsFunction */
#define  MAIN_CONTINUEBUTTON              4       /* control type: command, callback function: continueFunction */
#define  MAIN_TEXTMSG_1                   5       /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_2                   6       /* control type: textMsg, callback function: (none) */
#define  MAIN_SUDOKUPICTURE               7       /* control type: picture, callback function: (none) */
#define  MAIN_DEMOBUTTON                  8       /* control type: command, callback function: demoFunction */

#define  SETTINGS                         5       /* callback function: cancelFunction */
#define  SETTINGS_STRIKESSLIDE            2       /* control type: scale, callback function: (none) */
#define  SETTINGS_DIFF_RING               3       /* control type: ring, callback function: diffFunction */
#define  SETTINGS_OBS_RING                4       /* control type: ring, callback function: obsFunction */
#define  SETTINGS_NAMESTRING              5       /* control type: string, callback function: (none) */
#define  SETTINGS_PICTURE_2               6       /* control type: picture, callback function: (none) */
#define  SETTINGS_SAVEBUTTON              7       /* control type: command, callback function: saveFunction */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_HELP                     2       /* callback function: helpBar */
#define  MENUBAR_AD                       3       /* callback function: adBar */
#define  MENUBAR_ABOUT                    4       /* callback function: aboutBar */


     /* Callback Prototypes: */

void CVICALLBACK aboutBar(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK adBar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK cancelFunction(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK continueFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK demoFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK diffFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitTableFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK functionCheckTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK goBackFunction(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK helpBar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK instructionsFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK newGameFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK obsFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK outFunction(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitAboutFunction(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitFunction(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK saveFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK settingsFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK sudokuFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
