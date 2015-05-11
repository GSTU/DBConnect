#include <my_global.h>
#include <mysql.h>
#include <errmsg.h>
#include <mysqld_error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
* 1. Скачать драйвера для подключения к MySQL (качайте для С, и скорее всего для Win32)
* 2. Указать путь к include
* 3. Указать путь к lib (в lib нужно достать библиотеку mysqlclient.lib из папки VS12 (или другой,
  в зависимости от версии Visual Studio), и положить на уровень шыше)
* 4. указать линковщику библиотеки libmysql.lib и mysqlclient.lib
* 5. Положить dll, чтобы его могла найти программа 
* 
* 6. Проверьте или запущена служба mysql (mysqld.exe)
* 7. Проверьте или создайте БД
*/
int main()
{
	char *user=NULL;
	char *param="some data";
	char *content=NULL;
	char strinQuery[100];
	

	printf("Connecting: ");
	MYSQL conn; // Дескриптор соединения
	mysql_init(&conn); // Получаем дескриптор соединения

	// Устанавливаем соединение с базой данных
	mysql_real_connect(&conn, 
					   "localhost", // URL сервера 
					   "root", // Имя владельца БД
					   "", // Пароль
					   "testdb", // Имя БД
					   3306, // Порт
					   NULL, 
					   0);
	printf("Connected\n");
	
	// Начало транзакции 
	mysql_query(&conn, "START TRANSACTION");
	sprintf_s(strinQuery,"INSERT INTO `test_table1` VALUES (NULL,'%s')",param);
	mysql_query(&conn, strinQuery);
	fprintf(stdout, "Insert into test_table1: %s;\r\n", param);

	MYSQL_RES *res; // Дескриптор результирующей таблицы
	MYSQL_ROW row;  // Дескриптор строки

	// Выбрать одно строку с таблицы test_table2
	mysql_query(&conn, "SELECT * FROM `test_table2` ORDER BY `ID` limit 1");
	// Получаем дескриптор результирующей таблицы
	res = mysql_store_result(&conn);

	// Если имеется хотя бы одна запись - выводим
	// список каталогов
	if(mysql_num_rows(res) > 0)
	{
		// В цикле перебираем все записи
		// результирующей таблицы
		while((row = mysql_fetch_row(res)) != NULL)
		{
			// Выводим результат в стандартный поток
			fprintf(stdout, "Read from test_table2: %s;\r\n", row[1]);
		}

		// Пример запроса на удаление
		//mysql_query(&conn, "DELETE FROM `test_table2` ORDER BY `ID` LIMIT 1");
	}

	// Освобождаем память, занятую результирующей таблицей
	mysql_free_result(res);

	// Завершить транзакцию 
	mysql_query(&conn, "COMMIT");
	mysql_close(&conn);
	

	fflush(stdin);
	getchar();
	return 0;
};


