// Tchml_Lab1.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
//#include <conio.h>
#include <string.h>
#include <math.h>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

bool checkParam(int argc, char* argv[]);
bool Solve(char* fName_In1, char operation, char* fName_In2, char* fNameRes, int base, char* modulFile, bool isModul);

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

bool fileRead(int** bigNumArr, char* fileName, int base, int& arrSize, char& numberSign)
{
	const char* flag;
	if(base == 1000000000)
	{
		flag = "r";
	}
	else if(base == 256)
	{
		flag = "rb";
	}

	FILE* fp = fopen(fileName, flag);
	if(!fp)
	{
		printf("Can't open the file with a big number. Error!\n");
		return false;
	}

	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	int curPos = 0;
	
	fseek(fp, 0, SEEK_SET);
	if(fgetc(fp) == '-')
	{
		numberSign = '-';
		curPos = fileSize;
		fileSize -= 1;
	}
	else
	{
		numberSign = '+';
		curPos = fileSize;
	} 

	if(base == 1000000000)
	{
		if(!(fileSize % 9))
		{
			arrSize = fileSize / 9;
		}
		else
		{
			arrSize = fileSize / 9 + 1;
		}
	}
	else if(base == 256)
	{
		arrSize = fileSize;
	}

	(*bigNumArr) = new int[arrSize];
	for(int i = 0; i < (arrSize); i++)
	{
		(*bigNumArr)[i] = 0;
	}

	if(base == 1000000000)
	{
		
		for(int i = arrSize; i > 0; i--)
		{	
			if((curPos - 9) >= 0)
			{
				curPos -= 9;
				fseek(fp, curPos, SEEK_SET);
				for(int j = 0; j < 9; j++)
				{
					(*bigNumArr)[i - 1] += (fgetc(fp) - 48)*(int)(pow((double)10, (9 - j - 1)));
				}	
			}
			else
			{
				fseek(fp, 0, SEEK_SET);
				if(fgetc(fp) == '-')
				{
					fseek(fp, 1, SEEK_SET);
					for(int j = 1; j < curPos; j++)
					{
						(*bigNumArr)[i - 1] += (fgetc(fp) - 48)*(int)(pow((double)10, (curPos - j - 1)));
					}
				}
				else
				{
					fseek(fp, 0, SEEK_SET);
					for(int j = 0; j < curPos; j++)
					{
						(*bigNumArr)[i - 1] += (fgetc(fp) - 48)*(int)(pow((double)10, (curPos - j - 1)));
					}
				}
			}			
		}
	}
	else if(base == 256)
	{
		fseek(fp, 0, SEEK_SET);
		for(int i = arrSize; i > 0; i--)
		{
			(*bigNumArr)[i - 1] = getc(fp);
		}
	}

	fclose(fp);
	printf("The big number is successfully read from file.\n");
	return true;
}

bool fileWrite(int* bigNumArr, char numSign, int bigNumArrSize, char* fileResultName, int base)
{
	const char* flag = NULL;
	if(base == 1000000000)
	{
		flag = "w";
	}
	else if(base == 256)
	{
		flag = "wb+";
	}

	FILE* fp = fopen(fileResultName, flag);

	if(!fp)
	{
		return false;
	}
	
	if(base == 1000000000)
	{
		if(numSign == '-')
		{
			fprintf(fp, "%c", numSign);
		}
		for(int i = 0; i < bigNumArrSize; i++)
		{
			if(i)
			{
				for(int j = 0; j < 9; j++)
				{
					if(bigNumArr[i] < (int)pow((double)10, j))
					{
						fprintf(fp, "%d", 0);
					}
				}
			}
			fprintf(fp, "%d", bigNumArr[i]);
		}
	}

	else if(base == 256)
	{
		for(int i = bigNumArrSize; i > 0; i--)
		{
			putc(bigNumArr[i - 1], fp);
		}
	}

	fclose(fp);
	printf("The big number is successfully written to file.\n");
	return true;
}

char resultSign(char operation, char firstNumSign, char secNumSign, int* firstNumArr, int* secNumArr, int firstNumArrSize, int secNumArrSize)
{
	if(operation == '+')
	{
		if(firstNumArrSize > secNumArrSize)
		{
			return firstNumSign;
		}
		else if(firstNumArrSize < secNumArrSize)
		{
			return secNumSign;
		}

		else
		{
			for(int i = 0; i < firstNumArrSize; i++)
			{
				if(firstNumArr[i] > secNumArr[i])
				{
					return firstNumSign;
				}

				else if(firstNumArr[i] < secNumArr[i])
				{
					return secNumSign;
				}
			}
		}

		return '=';
	}

	if(operation == '*' || operation == '/')
	{
		if(firstNumSign != secNumSign)
		{
			return '-';
		}
		else
		{
			return '+';
		}
	}

	return firstNumSign;
}

void findMaxMin(int* firstNumArr, int* secNumArr, int firstNumArrSize, int secNumArrSize, int** maxNumArr, int** minNumArr, int& maxNumArrSize, int& minNumArrSize)
{
	if(firstNumArrSize > secNumArrSize)
	{
		maxNumArrSize = firstNumArrSize;
		*maxNumArr = new int[maxNumArrSize];
		for(int i = 0; i < maxNumArrSize; i++)
		{
			(*maxNumArr)[i] = firstNumArr[i];
		}
		minNumArrSize = secNumArrSize;
		*minNumArr = new int[minNumArrSize];
		for(int i = 0; i < minNumArrSize; i++)
		{
			(*minNumArr)[i] = secNumArr[i];
		}
	}
		
	else if(firstNumArrSize < secNumArrSize)
	{
		maxNumArrSize = secNumArrSize;
		*maxNumArr = new int[maxNumArrSize];
		for(int i = 0; i < maxNumArrSize; i++)
		{
			(*maxNumArr)[i] = secNumArr[i];
		}
		minNumArrSize = firstNumArrSize;
		(*minNumArr) = new int[minNumArrSize];
		for(int i = 0; i < minNumArrSize; i++)
		{
			(*minNumArr)[i] = firstNumArr[i];
		}
	}

	else
	{
		for(int i = 0; i < firstNumArrSize; i++)
		{
			if(firstNumArr[i] > secNumArr[i])
			{
				maxNumArrSize = firstNumArrSize;
				*maxNumArr = new int[maxNumArrSize];
				for(int i = 0; i < maxNumArrSize; i++)
				{
					(*maxNumArr)[i] = firstNumArr[i];
				}
				minNumArrSize = secNumArrSize;
				*minNumArr = new int[minNumArrSize];
				for(int i = 0; i < minNumArrSize; i++)
				{
					(*minNumArr)[i] = secNumArr[i];
				}
				break;
			}

			else if(firstNumArr[i] < secNumArr[i])
			{
				maxNumArrSize = secNumArrSize;
				*maxNumArr = new int[maxNumArrSize];
				for(int i = 0; i < maxNumArrSize; i++)
				{
					(*maxNumArr)[i] = secNumArr[i];
				}
				minNumArrSize = firstNumArrSize;
				*minNumArr = new int[minNumArrSize];
				for(int i = 0; i < minNumArrSize; i++)
				{
					(*minNumArr)[i] = firstNumArr[i];
				}
				break;
			}
		}
	}
}

int* withoutNulls(int* arrWithNulls, int& arrSize)
{
	int nullValues = 0;
	int* arrWithoutNulls = NULL;

	for(int i = 0; i < arrSize; i++)
	{
		if(arrWithNulls[i] == 0)
		{
			nullValues++;
		}
		else
		{
			break;
		}
	}

	arrSize -= nullValues;
	if(!arrSize)
	{
		arrSize = 1;
		arrWithoutNulls = new int[arrSize];
		arrWithoutNulls[0] = 0;		
	}

	else
	{
		arrWithoutNulls = new int[arrSize];
		for(int i = 0; i < arrSize; i++)
		{
			arrWithoutNulls[i] = arrWithNulls[i + nullValues];
		}
	}

	delete [] arrWithNulls;
	return arrWithoutNulls;
}

int* longToInt(long long int ArrElem, int* longToIntArr, int& longToIntArrSize, int base)
{
	longToIntArrSize = 2;
	longToIntArr = new int[longToIntArrSize];
	for(int i = 0; i < longToIntArrSize; i++)
	{
		longToIntArr[i] = 0;
	}

	longToIntArr[0] = (int)(ArrElem / (long long int)base);
	longToIntArr[1] = (int)(ArrElem % (long long int)base);

	return withoutNulls(longToIntArr, longToIntArrSize);
}

int* copyArr(int* newArr, int* oldArr, int& newArrSize, int oldArrSize)
{
	delete [] newArr;
	newArrSize = oldArrSize;
	newArr = new int[newArrSize];
	for(int i = 0; i < newArrSize; i++)
	{
		newArr[i] = oldArr[i];
	}

	return withoutNulls(newArr, newArrSize);
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

	if(!Solve(fileName_In1, operation, fileName_In2, fileResult, base, modFile, modBool))
	{
		printf("There is error in processing. \n");
	}

	return 0;
}

int* addition(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, int base)
{
	int* moreNumArr = NULL;
	int* lessNumArr = NULL;
	int moreNumArrSize = 0;
	int lessNumArrSize = 0;

	findMaxMin(firstNumArr, secondNumArr, firstNumArrSize, secNumArrSize, &moreNumArr, &lessNumArr, moreNumArrSize, lessNumArrSize);
	resNumArrSize = moreNumArrSize + 1;
	resNumArr = new int[resNumArrSize];

	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArr[i] = 0;
	}

	for(int i = resNumArrSize; i > 1; i--)
	{
		if((resNumArrSize - i) < lessNumArrSize)
		{
			resNumArr[i - 1] += (moreNumArr[moreNumArrSize - (resNumArrSize - i) - 1] + lessNumArr[lessNumArrSize - (resNumArrSize - i) - 1]);
		}

		else
		{
			resNumArr[i - 1] += moreNumArr[moreNumArrSize - (resNumArrSize - i) - 1];
		}

		resNumArr[i - 2] += resNumArr[i - 1] / base;
		resNumArr[i - 1] %= base;
	}

	delete [] moreNumArr;
	delete [] lessNumArr;
	return withoutNulls(resNumArr, resNumArrSize);
}

int* substraction(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, int base)
{
	int* moreNumArr = NULL;
	int* lessNumArr = NULL;
	int moreNumArrSize = 0;
	int lessNumArrSize = 0;
	int credit = 0;
	int newSub = 0;

	findMaxMin(firstNumArr, secondNumArr, firstNumArrSize, secNumArrSize, &moreNumArr, &lessNumArr, moreNumArrSize, lessNumArrSize);
	resNumArrSize = moreNumArrSize;

	resNumArr = new int[resNumArrSize];

	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArr[i] = 0;
	}

	for(int i = resNumArrSize; i > 0; i--)
	{
		if((resNumArrSize - i) < lessNumArrSize)
		{
			newSub = moreNumArr[moreNumArrSize - (resNumArrSize - i) - 1] - lessNumArr[lessNumArrSize - (resNumArrSize - i) - 1] - credit;
		}

		else
		{
			newSub = moreNumArr[moreNumArrSize - (resNumArrSize - i) - 1] - credit;
		}
		
		if(newSub < 0)
		{
			resNumArr[i - 1] = newSub + base;
			credit = 1;
		}
		else
		{
			resNumArr[i - 1] = newSub;
			credit = 0;
		}

	}

	delete [] moreNumArr;
	delete [] lessNumArr;
	return withoutNulls(resNumArr, resNumArrSize);
}

int* multiplication(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, int base)
{
	long long int* resNumArrLong = NULL;
 	resNumArrSize = firstNumArrSize + secNumArrSize + 1;
	resNumArr = new int[resNumArrSize];
	resNumArrLong = new long long int[resNumArrSize];

	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArrLong[i] = 0;
		resNumArr[i] = 0;
	}

	for(int i = firstNumArrSize; i > 0; i--)
	{
		for(int j = secNumArrSize; j > 0; j--)
		{
			resNumArrLong[i + j] += (long long int)(firstNumArr[i - 1]) * (long long int)(secondNumArr[j - 1]);
		}
	}

	for(int i = resNumArrSize; i > 1; i--)
	{
		resNumArrLong[i - 2] += resNumArrLong[i - 1] / base;
		resNumArrLong[i - 1] %= base;
	}

	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArr[i] = (int)resNumArrLong[i];
	}

	delete [] resNumArrLong;

	return withoutNulls(resNumArr, resNumArrSize);
}

int* divOnDigit(int* firstNumArr, int digit, int* resNumArr, int firstNumArrSize, int& resNumArrSize, int& tail, bool isRem, int base)
{
	if(!digit)
	{
		printf("Dividing to the zero. Error!\n");
		return firstNumArr;
	}

	resNumArrSize = firstNumArrSize;
	resNumArr = new int[resNumArrSize];
	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArr[i] = 0;
	}

	int remain = 0;
	long long int curDiver = 0;
	for(int i = 0; i < firstNumArrSize; i++)
	{
		curDiver = (long long int)remain * (long long int)base + (long long int)firstNumArr[i];
		resNumArr[i] = (int)(curDiver / (long long int)digit);
		remain = (int)(curDiver % (long long int)digit);
	}

	tail = remain;
	return withoutNulls(resNumArr, resNumArrSize);
}

int* dividing(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, bool isRem, int base)
{
	int remain = 0;
	if(secNumArrSize == 1)
	{
		resNumArr = divOnDigit(firstNumArr, secondNumArr[0], resNumArr, firstNumArrSize, resNumArrSize, remain, isRem, base);
		if(isRem)
		{
			delete [] resNumArr;
			resNumArr = new int[1];
			resNumArr[0] = remain;
			return resNumArr;
		}
		else
		{
			return resNumArr;
		}
	}
	
	if(firstNumArrSize == 1)
	{
		resNumArrSize = 1;
		resNumArr = new int[resNumArrSize];

		if(secNumArrSize == 1)
		{
			if(secondNumArr[0])
			{
				resNumArr[0] = firstNumArr[0] / secondNumArr[0];
				return resNumArr;
			}
			else
			{
				printf("Dividing to the zero. Error!\n");
				return firstNumArr;
			}
		}
		else
		{
			resNumArr[0] = 0;
			return resNumArr;
		}
	}

	resNumArrSize = firstNumArrSize - secNumArrSize + 1;
	resNumArr = new int[resNumArrSize];
	for(int i = 0; i < resNumArrSize; i++)
	{
		resNumArr[i] = 0;
	}

	int* remainder = NULL;
	int* deduction = NULL;
	int* submit = NULL;
	int* difference = NULL;
	long long int* modifyRem = NULL;
	long long int* modifySecNumArr = NULL;
	int remainderSize = 0;
	int deductionSize = 0;
	int difSize = 0;
	remainderSize = firstNumArrSize + 1;
	remainder = new int[remainderSize];
	submit = new int[remainderSize];
	modifyRem = new long long int[remainderSize];
	modifySecNumArr = new long long int[secNumArrSize];
	for(int i = 0; i < remainderSize; i++)
	{
		remainder[i] = 0;
		modifyRem[i] = 0;
		submit[i] = 0;
	}

	for(int i = 0; i < secNumArrSize; i++)
	{
		modifySecNumArr[i] = 0;
	}

	int helpValue = 0;
	if(!((base / 2) % secondNumArr[0]))
	{
		helpValue = ((base / 2) / secondNumArr[0]);
	}

	else
	{
		helpValue = ((base / 2) / secondNumArr[0]) + 1;
	}

	for(int i = 1; i < remainderSize; i++)
	{
		remainder[i] = firstNumArr[i - 1];
	}

	for(int i = 0; i < secNumArrSize; i++)
	{
		modifySecNumArr[i] = (long long int)secondNumArr[i] * (long long int)helpValue;
	}

	int* newQuot = NULL;
	newQuot = new int[1];
	int* modifyRemInt = NULL;
	int* modifySecNumArrInt = NULL;
	int* multiArr = NULL;
	int* secMultiArr = NULL;
	int* thirMultiArr = NULL;
	int* sumArr = NULL;
	int* baseArr = NULL;
	int* relation = NULL;
	baseArr = new int[1];
	baseArr[0] = base;
	int multiArrSize = 0;
	int secMultiArrSize = 0;
	int thirMultiArrSize = 0;
	int sumArrSize = 0;
	int modifyRemIntSize = 0;
	int modifySecNumArrIntSize = 0;
	int relationSize = 0;

	for(int i = 0; i < resNumArrSize; i++)
	{
		for(int j = 0; j < remainderSize; j++)
		{
			modifyRem[j] = (long long int)remainder[j] * (long long int)helpValue;
		}

		modifyRemInt = longToInt(modifyRem[i], modifyRemInt, modifyRemIntSize, base);
		multiArr = multiplication(modifyRemInt, baseArr, multiArr, modifyRemIntSize, 1, multiArrSize, base);
		delete [] modifyRemInt;
		modifyRemInt = longToInt(modifyRem[i + 1], modifyRemInt, modifyRemIntSize, base);
		sumArr = addition(multiArr, modifyRemInt, sumArr, multiArrSize, modifyRemIntSize, sumArrSize, base);
		delete [] modifyRemInt;
		relation = divOnDigit(sumArr, (int)modifySecNumArr[0], relation, sumArrSize, relationSize, remain, false, base);

		if(relationSize > 1)
		{
			newQuot[0] = (base - 1);
		}
		else
		{
			newQuot[0] = relation[0];
		}

		delete [] relation;

		do
		{
			delete [] multiArr;
			delete [] sumArr;

			modifySecNumArrInt = longToInt(modifySecNumArr[1], modifySecNumArrInt, modifySecNumArrIntSize, base);
			multiArr = multiplication(modifySecNumArrInt, newQuot, multiArr, modifySecNumArrIntSize, 1, multiArrSize, base);
			delete [] modifySecNumArrInt;

			modifyRemInt = longToInt(modifyRem[i], modifyRemInt, modifyRemIntSize, base);
			secMultiArr = multiplication(modifyRemInt, baseArr, secMultiArr, modifyRemIntSize, 1, secMultiArrSize, base);
			delete [] modifyRemInt;
			modifyRemInt = longToInt(modifyRem[i + 1], modifyRemInt, modifyRemIntSize, base);
			sumArr = addition(secMultiArr, modifyRemInt, sumArr, secMultiArrSize, modifyRemIntSize, sumArrSize, base);
			delete [] modifyRemInt;
			delete [] secMultiArr;
			modifySecNumArrInt = longToInt(modifySecNumArr[0], modifySecNumArrInt, modifySecNumArrIntSize, base);
			secMultiArr = multiplication(modifySecNumArrInt, newQuot, secMultiArr, modifySecNumArrIntSize, 1, secMultiArrSize, base);
			delete [] modifySecNumArrInt;
			thirMultiArr = substraction(sumArr, secMultiArr, thirMultiArr, sumArrSize, secMultiArrSize, thirMultiArrSize, base);
			delete [] sumArr;
			delete [] secMultiArr;
			secMultiArr = multiplication(thirMultiArr, baseArr, secMultiArr, thirMultiArrSize, 1, secMultiArrSize, base);
			delete [] thirMultiArr;
			modifyRemInt = longToInt(modifyRem[i + 2], modifyRemInt, modifyRemIntSize, base);
			sumArr = addition(secMultiArr, modifyRemInt, sumArr, secMultiArrSize, modifyRemIntSize, sumArrSize, base);
			delete [] secMultiArr;
			delete [] modifyRemInt;

			if(resultSign('+', '+', '-', multiArr, sumArr, multiArrSize, sumArrSize) == '+')
			{
				newQuot[0]--;
			}
		}while(resultSign('+', '+', '-', multiArr, sumArr, multiArrSize, sumArrSize) == '+');

		delete [] multiArr;
		delete [] sumArr;
		deduction = multiplication(secondNumArr, newQuot, deduction, secNumArrSize, 1, deductionSize, base);
		for(int j = 0; j < (i + 1 - (deductionSize - secNumArrSize)); j++)
		{
			submit[j] = 0;
		}
		for(int j = (i + 1 - (deductionSize - secNumArrSize)); j < (secNumArrSize + 1 + i); j++)
		{
			submit[j] = deduction[j - i - 1 + (deductionSize - secNumArrSize)];
		}
		for(int j = (secNumArrSize + 1 + i); j < remainderSize; j++)
		{
			submit[j] = 0;
		}
		
		if(resultSign('+', '+', '-', remainder, submit, remainderSize, remainderSize) == '-')
		{
			newQuot[0]--;

			delete [] deduction;

			deduction = multiplication(secondNumArr, newQuot, deduction, secNumArrSize, 1, deductionSize, base);
			for(int j = 0; j < (i + 1 - (deductionSize - secNumArrSize)); j++)
			{
				submit[j] = 0;
			}
			for(int j = (i + 1 - (deductionSize - secNumArrSize)); j < (secNumArrSize + 1 + i); j++)
			{
				submit[j] = deduction[j - i - 1 + (deductionSize - secNumArrSize)];
			}
			for(int j = (secNumArrSize + 1 + i); j < remainderSize; j++)
			{
				submit[j] = 0;
			}
		}
		
		difference = substraction(remainder, submit, difference, remainderSize, remainderSize, difSize, base);
		resNumArr[i] = newQuot[0];
		for(int i = remainderSize; i > (remainderSize - difSize); i--)
		{
			remainder[i - 1] = difference[difSize - (remainderSize - i) - 1];
		}
		for(int i = (remainderSize - difSize); i > 0; i--)
		{
			remainder[i - 1] = 0;
		}
		delete [] difference;
		delete [] deduction;
	}

	delete [] submit;
	delete [] modifyRem;
	delete [] modifySecNumArr;
	delete [] newQuot;
	delete [] baseArr;

	if(isRem)
	{
		delete [] resNumArr;
		resNumArr = withoutNulls(remainder, remainderSize);
		resNumArrSize = remainderSize;
		return resNumArr;
	}
	else
	{
		delete [] remainder;
		return withoutNulls(resNumArr, resNumArrSize);
	}
}

int* involution(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, int base)
{
	resNumArr = new int[1];
	resNumArr[0] = 1;
	resNumArrSize = 1;
	int* oneArr = NULL;
	oneArr = new int[1];
	oneArr[0] = 1;
	int* tempQuotArr = NULL;
	int tempQuotArrSize = 0;
	int* tempMultiArr = NULL;
	int tempMultiArrSize = 0;
	int* tempSubArr = NULL;
	int tempSubArrSize = 0;
	int* tempFirstArr = NULL;
	int tempFirstArrSize = 0;
	int* tempSecArr = NULL;
	int tempSecArrSize = 0;
	int remain = 0;

	tempFirstArr = copyArr(tempFirstArr, firstNumArr, tempFirstArrSize, firstNumArrSize);
	tempSecArr = copyArr(tempSecArr, secondNumArr, tempSecArrSize, secNumArrSize);

	while(!((tempSecArrSize == 1) && (tempSecArr[0] == 1)))
	{
		tempQuotArr = divOnDigit(tempSecArr, 2, tempQuotArr, tempSecArrSize, tempQuotArrSize, remain, false, base);
		if(!remain)
		{
			tempSecArr = copyArr(tempSecArr, tempQuotArr, tempSecArrSize, tempQuotArrSize);
			delete [] tempQuotArr;
			tempMultiArr = multiplication(tempFirstArr, tempFirstArr, tempMultiArr, tempFirstArrSize, tempFirstArrSize, tempMultiArrSize, base);
			tempFirstArr = copyArr(tempFirstArr, tempMultiArr, tempFirstArrSize, tempMultiArrSize);
			delete tempMultiArr;
		}
		else
		{
			tempSubArr = substraction(tempSecArr, oneArr, tempSubArr, tempSecArrSize, 1, tempSubArrSize, base);
			tempSecArr = copyArr(tempSecArr, tempSubArr, tempSecArrSize, tempSubArrSize);
			delete [] tempSubArr;
			tempMultiArr = multiplication(tempFirstArr, resNumArr, tempMultiArr, tempFirstArrSize, resNumArrSize, tempMultiArrSize, base);
			resNumArr = copyArr(resNumArr, tempMultiArr, resNumArrSize, tempMultiArrSize);
			delete [] tempMultiArr;
		}
	}

	tempMultiArr = multiplication(tempFirstArr, resNumArr, tempMultiArr, tempFirstArrSize, resNumArrSize, tempMultiArrSize, base);
	resNumArr = copyArr(resNumArr, tempMultiArr, resNumArrSize, tempMultiArrSize);
	delete [] tempMultiArr;

	delete [] oneArr;
	delete [] tempSecArr;
	delete [] tempFirstArr;
	return resNumArr;
}

int* remainder(int* firstNumArr, int* secondNumArr, int* resNumArr, int firstNumArrSize, int secNumArrSize, int& resNumArrSize, int base)
{
	resNumArr = dividing(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, true, base);
	return resNumArr;
}

bool Solve(char* fName_In1, char operation, char* fName_In2, char* fNameRes, int base, char* modulFile, bool isModul)
{
	int* firstNumArr = NULL;
	int* secondNumArr = NULL;
	int* resNumArr = NULL;
	int firstNumArrSize = 0;
	int secNumArrSize = 0;
	int resNumArrSize = 0;
	char firstNumSign = '\0';
	char secNumSign = '\0';
	char resNumSign = '\0';
	
	if(!fileRead(&firstNumArr, fName_In1, base, firstNumArrSize, firstNumSign))
	{
		printf("Can't read the first big number from file!\n");
		return false;
	}

	if(!fileRead(&secondNumArr, fName_In2, base, secNumArrSize, secNumSign))
	{
		printf("Can't read the second big number from file!\n");
		return false;
	}
	
	char tempOper = '\0';

	if(operation == '-')
	{
		tempOper = '-';
		operation = '+';
		if(secNumSign == '-')
		{
			secNumSign = '+';
		}
		else
		{
			secNumSign = '-';
		}
	}

	resNumSign = resultSign(operation, firstNumSign, secNumSign, firstNumArr, secondNumArr, firstNumArrSize, secNumArrSize);

	if(tempOper != '\0')
	{
		operation = tempOper;
		if(secNumSign == '-')
		{
			secNumSign = '+';
		}
		else
		{
			secNumSign = '-';
		}
	}
	
	if(firstNumSign != secNumSign)
	{
		if(operation == '+')
		{
			operation = '-';
		}
		else if(operation == '-')
		{
			operation = '+';
		}
	}
	
	switch(operation)
	{
		case '+':
			resNumArr = addition(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, base);
			break;
		case '-':
			resNumArr = substraction(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, base);
			break;
		case '*':
			resNumArr = multiplication(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, base);
			break;
		case '/':
			resNumArr = dividing(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, false, base);
			break;
		case '^':
			resNumArr = involution(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, base);
			break;
		case '|':
			resNumArr = remainder(firstNumArr, secondNumArr, resNumArr, firstNumArrSize, secNumArrSize, resNumArrSize, base);
			break;
		default:
			printf("Wrong operation. Error.\n");
			return false;
			break;
	}
	
	if(isModul)
	{
		int* modNumArr = NULL;
		int* resNumModArr = NULL;
		int modNumArrSize = 0;
		int resNumModArrSize = 0;
		char modNumSign = '\0';
		char resNumModSign = '\0';

		if(!fileRead(&modNumArr, modulFile, base, modNumArrSize, modNumSign))
		{
			printf("Can't read the bid number from file with a modul!\n");
			return false;
		}

		resNumModArr = remainder(resNumArr, modNumArr, resNumModArr, resNumArrSize, modNumArrSize, resNumModArrSize, base);

		delete [] resNumArr;
		resNumArrSize = resNumModArrSize;
		resNumArr = new int[resNumArrSize];
		for(int i = 0; i < resNumArrSize; i++)
		{
			resNumArr[i] = resNumModArr[i];
		}
		delete [] modNumArr;
		delete [] resNumModArr;
	}

	if(!fileWrite(resNumArr, resNumSign, resNumArrSize, fNameRes, base))
	{
		printf("Can't write big number to the file. Error!\n");
	}

	delete [] firstNumArr;
	delete [] secondNumArr;
	delete [] resNumArr;

	return true;
}