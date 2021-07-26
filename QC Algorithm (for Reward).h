#ifndef _PHONE_PROCESS_NEW_H
#define _PHONE_PROCESS_NEW_H

/*************************************************************************************
 * Defines....
 *************************************************************************************/

#define MAX_WEATHER_STATUS			16

#define GRID_TIME					900
#define GRID_X						0.05
#define GRID_Y						0.05
#define GRID_X_EXTRA				0.1
#define GRID_Y_EXTRA				0.1

#define WEATHER_STATUS_1ST			'1'
#define WEATHER_STATUS_2ND			'2'
#define WEATHER_STATUS_2ND_EXTRA	'B'


#define PARSE_DATA(V, T, P)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " Setting Error!\n"); \
								return (-1); \
							} \
							else \
							{ \
								pdata->V = P(token); \
							}

#define PARSE_STRING(V, T)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " Setting Error!\n"); \
								return (-1); \
							} \
							else \
							{ \
								strcpy(pdata->V, token); \
								str_trim(pdata->V, TRIM_ALL); \
							}

#define PARSE_CHAR(V, T)	if ( (ptr = get_next_token(buff, ptr, token, ';')) <= 0 || (strlen(token) < 1) ) \
							{ \
								Log("ParseMWSData: " T " Setting Error!\n"); \
								return (-1); \
							} \
							else \
							{ \
								pdata->V = token[0]; \
							}
							
typedef struct
{
	int			data_date;			/* DATE */
	int			data_time;			/* TIME */
	int			user_num;			/* User unique number */
	char		ip[16];				/* Observation IP */
	double		lng;				/* Longitude */
	double		lat;				/* Latitude */
	double		PRE;				/* Pressure */
	char		w_status;			/* Report */
	char		w_group;			/* Report Group */
	
	int			QC_PRE;
	char		QC_PRE_ERR[256];
	
	int			QC_W;
	char		QC_W_ERR[256];
	
	int			QC_NOW;
	char		QC_NOW_ERR[256];
	
	char		f_QC_W;
	int			date_idx;
} PHONE_DATA;

typedef struct
{
	char		status;
	int			count;
} FDATA;

/*************************************************************************************
 * Global Variable Definitions
 *************************************************************************************/
 
char				program_name[64];
int 				process_id;

sql_context			ctx;
char				raw_file_name[256];

/*************************************************************************************
 * Function Definition
 *************************************************************************************/

int		ParsePhoneData(char* buff, PHONE_DATA* pdata);
int		ProcessWeatherStatus2nd(time_t ftime);

int		QC_WeatherStatus(char step, PHONE_DATA* pdata);
int		QC_WeatherStatusNOW(char step, PHONE_DATA* pdata);
int		_qsort_wstatus( const void *a, const void *b );

int		InsertPhoneData(PHONE_DATA* pdata);
int		UpdatePhoneData(PHONE_DATA* pdata);
int		InsertQCError(int data_date, int date_idx, char qc_type, char* msg);
int		UpdatePhoneCount(PHONE_DATA* pdata);

void	InitServer();
void	interrupt(int sig);

#endif
