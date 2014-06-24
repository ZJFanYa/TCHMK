// Tchmk_Lab2.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <string.h>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
#include <math.h>
#include "bigNumDLL.h"

void PrintStart()
{
	printf("Realization of arithmetic operations with big numbers:\n");
	printf("addition, substraction, multiplication, dividing, involution, taking the remainder.\n");
	printf("Main string should be in a such way: \n");
	printf("[fileName1_in] [operation] [fileName2_in] [resFileName] [key] [modFileName]");
	printf("	fileName1_in - file with the first big number\n");
	printf("	operation:\n");
	printf("		""+"" - addition\n");
	printf("		""-"" - substraction\n");
	printf("		""*"" - multiplication\n");
	printf("		""/"" - dividing\n");
	printf("		""^"" - involution\n");
	printf("		""|"" - taking the remainder\n");
	printf("	fileName2_in - file with the second big number\n");
	printf("	resFileName - file with the big number-result\n");
	printf("	-b - binary processing\n");
	printf("	else - text processing\n");
	printf("	modFileName - file with a big number - modul\n");
}

bool checkParam(int argc, char* argv[])
{
	if(argc < 5)
	{
		printf("There is lake of parameters. Main string was entered wrongly.\n");
		return false;
	}

	if(argc > 7)
	{
		printf("Too many parameters. Main string was entered wrongly.\n");
		return false;
	}

	if(strlen(argv[2]) > 1)
	{
		printf("Wrong operation.\n");
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	PrintStart();

	if(!checkParam(argc, argv))
	{
		return 0;
	}

	char* fileName_In1 = argv[1];
	char operation = argv[2][0];
	char* fileName_In2 = argv[3];
	char* fileResult = argv[4];
	char* bin = NULL;
	char* modFile = NULL;

	int base = 0;
	bool modBool = false;

	if(argc == 5)
	{
		base = 1000000000;
	}

	if(argc == 6)
	{
		if(!strcmp(argv[5], "-b"))
		{
			bin = argv[5];
			base = 256;
		}
		else
		{
			base = 1000000000;
			modFile = argv[5];
			modBool = true;
		}
	}

	if(argc == 7)
	{
		if(!strcmp(argv[5], "-b"))
		{
			bin = argv[5];
			base = 256;
			modFile = argv[6];
			modBool = true;
		}
		else
		{
			printf("Too many parameters. Error!\n");
			return 0;
		}
	}
	
	bigNum firstBigNum;
	bigNum secBigNum;
	
	bigNum resBigNum;

	if(!firstBigNum.Read(fileName_In1, base))
	{
		printf("Error of first big number reading.\n");
		return 0;
	}
	if(!secBigNum.Read(fileName_In2, base))
	{
		printf("Error of second big number reading.\n");
		return 0;
	}
	
	switch(operation)
	{
		case '+':
			resBigNum = firstBigNum + secBigNum;
			break;
		case '-':
			resBigNum = firstBigNum - secBigNum;
			break;
		case '*':
			resBigNum = firstBigNum * secBigNum;
			break;
		case '/':
			resBigNum = firstBigNum / secBigNum;
			break;
		case '^':
			resBigNum = firstBigNum ^ secBigNum;
			break;
		case '|':
			resBigNum = firstBigNum % secBigNum;
			break;
		default:
			printf("Wrong operation. Error.\n");
			return false;
			break;
	}

	if(modBool)
	{
		bigNum modBigNum;
		bigNum resModBigNum;
		if(!modBigNum.Read(modFile, base))
		{
			printf("Error of modul big number reading.\n");
			return 0;
		}
		resModBigNum = resBigNum % modBigNum;
		resModBigNum.Write(fileResult);
		return 0;
	}

	resBigNum.Write(fileResult);

	return 0;
}

