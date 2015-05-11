#include <my_global.h>
#include <mysql.h>
#include <errmsg.h>
#include <mysqld_error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
* 1. ������� �������� ��� ����������� � MySQL (������� ��� �, � ������ ����� ��� Win32)
* 2. ������� ���� � include
* 3. ������� ���� � lib (� lib ����� ������� ���������� mysqlclient.lib �� ����� VS12 (��� ������,
  � ����������� �� ������ Visual Studio), � �������� �� ������� ����)
* 4. ������� ���������� ���������� libmysql.lib � mysqlclient.lib
* 5. �������� dll, ����� ��� ����� ����� ��������� 
* 
* 6. ��������� ��� �������� ������ mysql (mysqld.exe)
* 7. ��������� ��� �������� ��
*/
int main()
{
	char *user=NULL;
	char *param="some data";
	char *content=NULL;
	char strinQuery[100];
	

	printf("Connecting: ");
	MYSQL conn; // ���������� ����������
	mysql_init(&conn); // �������� ���������� ����������

	// ������������� ���������� � ����� ������
	mysql_real_connect(&conn, 
					   "localhost", // URL ������� 
					   "root", // ��� ��������� ��
					   "", // ������
					   "testdb", // ��� ��
					   3306, // ����
					   NULL, 
					   0);
	printf("Connected\n");
	
	// ������ ���������� 
	mysql_query(&conn, "START TRANSACTION");
	sprintf_s(strinQuery,"INSERT INTO `test_table1` VALUES (NULL,'%s')",param);
	mysql_query(&conn, strinQuery);
	fprintf(stdout, "Insert into test_table1: %s;\r\n", param);

	MYSQL_RES *res; // ���������� �������������� �������
	MYSQL_ROW row;  // ���������� ������

	// ������� ���� ������ � ������� test_table2
	mysql_query(&conn, "SELECT * FROM `test_table2` ORDER BY `ID` limit 1");
	// �������� ���������� �������������� �������
	res = mysql_store_result(&conn);

	// ���� ������� ���� �� ���� ������ - �������
	// ������ ���������
	if(mysql_num_rows(res) > 0)
	{
		// � ����� ���������� ��� ������
		// �������������� �������
		while((row = mysql_fetch_row(res)) != NULL)
		{
			// ������� ��������� � ����������� �����
			fprintf(stdout, "Read from test_table2: %s;\r\n", row[1]);
		}

		// ������ ������� �� ��������
		//mysql_query(&conn, "DELETE FROM `test_table2` ORDER BY `ID` LIMIT 1");
	}

	// ����������� ������, ������� �������������� ��������
	mysql_free_result(res);

	// ��������� ���������� 
	mysql_query(&conn, "COMMIT");
	mysql_close(&conn);
	

	fflush(stdin);
	getchar();
	return 0;
};


