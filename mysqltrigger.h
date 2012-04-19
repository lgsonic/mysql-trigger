#include <mysql.h>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MYSQL_TRIGGER_INI_FILE						"/usr/local/mysqltrigger/mysqltrigger.ini"
#define MYSQL_TRIGGER_INI_KEY_LOG					"logdir"

#define MYSQL_TRIGGER_UPDATE_LOG_DIR				"/usr/local/mysqltrigger/"
#define MYSQL_TRIGGER_UPDATE_LOG_PREFIX				"mysqltriggerlog_"

#define MYSQL_TRIGGER_INSERT_CMD					"insert"
#define MYSQL_TRIGGER_UPDATE_CMD					"update"
#define MYSQL_TRIGGER_DELETE_CMD					"delete"

#define MYSQL_TRIGGER_API 

extern "C"{

MYSQL_TRIGGER_API my_bool trigger_config_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
MYSQL_TRIGGER_API void trigger_config_deinit(UDF_INIT *initid);
MYSQL_TRIGGER_API long long trigger_config(UDF_INIT *initid, UDF_ARGS *args);

MYSQL_TRIGGER_API my_bool trigger_add_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
MYSQL_TRIGGER_API void trigger_add_deinit(UDF_INIT *initid);
MYSQL_TRIGGER_API long long trigger_add(UDF_INIT *initid, UDF_ARGS *args);

MYSQL_TRIGGER_API my_bool trigger_set_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
MYSQL_TRIGGER_API void trigger_set_deinit(UDF_INIT *initid);
MYSQL_TRIGGER_API long long trigger_set(UDF_INIT *initid, UDF_ARGS *args);

MYSQL_TRIGGER_API my_bool trigger_delete_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
MYSQL_TRIGGER_API void trigger_delete_deinit(UDF_INIT *initid);
MYSQL_TRIGGER_API long long trigger_delete(UDF_INIT *initid, UDF_ARGS *args);

}
