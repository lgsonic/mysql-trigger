#include "mysqltrigger.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define MAX_LINE_LEN 1024

static char g_szDir[MAX_PATH] = MYSQL_TRIGGER_UPDATE_LOG_DIR;
static char g_szLog[MAX_PATH];

static void GetCurLog()
{
	time_t now;
	time(&now);
	struct tm tmLocal;
	gmtime_r(&now, &tmLocal);
	snprintf(g_szLog, MAX_PATH, "%s%s%04d%02d%02d", 
		g_szDir, 
		MYSQL_TRIGGER_UPDATE_LOG_PREFIX,
		1900+tmLocal.tm_year,
		tmLocal.tm_mon+1,
		tmLocal.tm_mday);
}

static void trigger_process(UDF_ARGS *args, std::string & strData)
{
	for(unsigned int i = 0; i<args->arg_count; i++)
	{
		if(args->lengths[i] <= 0)
		{
			continue;
		}

		if(args->arg_type[i] == INT_RESULT)
		{
			long long llData = 0;
			int nData = 0;
			int nLength = args->lengths[i];
			if(nLength > sizeof(llData))
			{
				nLength = sizeof(llData);
			}

			if(nLength > sizeof(nData))
			{
				memcpy(&llData, args->args[i], nLength);
			}
			else
			{
				memcpy(&nData, args->args[i], nLength);
				llData = nData;
			}

			char szData[64];
			snprintf(szData, sizeof(szData), "%lld", llData);
			strData.insert(strData.end(), szData, szData+strlen(szData));
		}
		else if(args->arg_type[i] == STRING_RESULT)
		{
			strData.insert(strData.end(), args->args[i], args->args[i]+args->lengths[i]);
		}
		strData+=" ";
	}
	strData+="\r\n";

	GetCurLog();

	std::ofstream ofs(g_szLog, std::ios::app);
	if(ofs.good())
	{
		ofs.write(strData.c_str(), strData.size());
		ofs.close();
		chmod(g_szLog, 0664);
	}
	else{}
}


my_bool trigger_config_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	return 0;
}

void trigger_config_deinit(UDF_INIT *initid)
{
}

long long trigger_config(UDF_INIT *initid, UDF_ARGS *args)
{
	std::ifstream ifs(MYSQL_TRIGGER_INI_FILE, std::ios::in);
	if(ifs.good())
	{
		if(!ifs.eof())
		{
			char szLine[MAX_LINE_LEN];
			if(ifs.getline(szLine, MAX_LINE_LEN).good())
			{
				std::string strLine = szLine;
				int index = strLine.find("=");
				if(index != -1)
				{
					std::string strKey = strLine.substr(0, index);
					std::string strValue = strLine.substr(index+1);
					if((strKey==MYSQL_TRIGGER_INI_KEY_LOG) && !strValue.empty())
					{
						snprintf(g_szDir, MAX_PATH, "%s", strValue.c_str());
					}
				}
			}
			else{}
		}

		ifs.close();
	}
	else{}

	return 0;
}


my_bool trigger_add_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	return 0;
}

void trigger_add_deinit(UDF_INIT *initid)
{
}

long long trigger_add(UDF_INIT *initid, UDF_ARGS *args)
{
	std::string strData = (std::string)MYSQL_TRIGGER_INSERT_CMD + " ";
	trigger_process(args, strData);
	return 0;
}


my_bool trigger_set_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	return 0;
}

void trigger_set_deinit(UDF_INIT *initid)
{
}

long long trigger_set(UDF_INIT *initid, UDF_ARGS *args)
{
	std::string strData = (std::string)MYSQL_TRIGGER_UPDATE_CMD + " ";
	trigger_process(args, strData);
	return 0;
}


my_bool trigger_delete_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	return 0;
}

void trigger_delete_deinit(UDF_INIT *initid)
{
}

long long trigger_delete(UDF_INIT *initid, UDF_ARGS *args)
{
	std::string strData = (std::string)MYSQL_TRIGGER_DELETE_CMD + " ";
	trigger_process(args, strData);
	return 0;
}



