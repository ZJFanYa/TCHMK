#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

void PrintStart()
{
	printf("Program TCHMK.\n");
	printf("Enter the input parameters:\n");
	printf("\n<name of program> <filename A> <operation>\n<filename B> <result filename C> [b] [filename with module]\n\n");
	printf("Parametr: \n");
	printf("\"-b\" - binfile\n");
	printf("Operations: \n");
	printf("\"+\" - addition\n");
	printf("\"-\" - subtraction\n");
	printf("\"*\" - multiplication\n");
	printf("\"/\" - division\n");
	printf("\"|\" - taking the remainder\n");		 //% не отображается
	printf("\"^\" - involution (pow)\n");
}
//Проверка
bool checkParam(int argc, char* argv[])
{
	if (argc < 2)
		return false;

	if (argc > 8)
	{
		printf("\nToo many parameters.\n");
		PrintStart();
		return false;
	}

	if ((argc > 1) && (argc < 6))
	{
		printf("\nIntroduced not all parameters.\n");
		PrintStart();
		return false;
	}

	if (strlen(argv[2]) > 1)
	{
		printf("Invalid input operation.\n");
		PrintStart();
		return false;
	}

	return true;
}

int* MinMax(int* a,int* b,char type)
{
    if (a[0] > b[0])
    {
        if(type == 'm') return b;
        if(type == 'M') return a;
    }
    else if (a[0] < b[0])
    {
        if(type == 'm') return a;
        if(type == 'M') return b;
    }
    else
    {
        for(int i = a[0];i>0;i--)
        {
            if(a[i] > b[i])
            {
                if(type == 'm') return b;
                if(type == 'M') return a;
            }
            else  if(a[i] < b[i])
            {
                if(type == 'm') return a;
                if(type == 'M') return b;
            }
        }
    }
    return a;
}
int* DeleteNull(int* c)
 {
    for(int i = c[0]; i>1; i--)
	{
		if(c[i] == 0) c[0]--;
		else break;
	}
	return c;
 }
int* fileRead(int *mas ,char* fileName,int base)
{
    char* flag;
    if(base == 10) flag = "r";
    else flag = "rb";
    FILE *fp = fopen(fileName, flag);
    if(NULL == fp) exit(1);
    fseek(fp,0,SEEK_END);
	int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
	mas = (int*) malloc((size+2)*sizeof(int));
	if(base == 10) for(int i = size; i>0; i--) mas[i] = fgetc(fp) - 48;
    else for (int i=1;i<=size;i++) mas[i] = getc(fp);
	mas[0] = size;
    fclose(fp);
    return mas;
}
void fileWrite(int *mas,char res, char *fileName,int base)
{
    char* flag;
    if(base == 10) flag = "w";
    else flag = "wb+";
	FILE *fp = fopen(fileName, flag);
	if(base == 10)
    {
        if(res == '-') fprintf(fp,"%c",res);
        for(int i=mas[0]; i>0; i--) fprintf(fp,"%d",mas[i]);
    }
    else for (int i=1;i<mas[0]+1;i++) putc(mas[i], fp);
	fclose(fp);
}
char ResultSign(char oper, char sa,char sb,int* a,int* b)
{
	if('+' == oper)
    {
        if(sa == '-') return '-';
        else return '+';
    }
    else if('-' == oper) {
        if('+' == sa) {
            if(a == MinMax(a,b,'M')) return '+';
            else return '-';
        }
        else {
            if(b == MinMax(a,b,'m')) return '-';
            else return '+';
        }
    }
    else if('*' == oper || '/' == oper) {
        if(sa != sb) return '-';
        else return '+';
    }
    return sa;
}
int* CopyArray(int* arr, int* source, bool Memory)
{
    if (!Memory)
        arr = (int*) malloc((source[0]+2)*sizeof(int));
    for(int i = 0;i<=source[0];i++)
        arr[i] = source[i];
    return arr;
}
int* DigitToArray(int d,int base)
{
    int size = 1;
    while(d>=pow((double)base,size)) size++;
    int* arr = (int*) malloc((size+2)*sizeof(int));
    arr[0] = size;
    for(int i = 0;i<size;i++)
    {
        arr[i+1] = d % base;
        d /= base;
    }
    return arr;
}
int* Addition(int *a, int *b,int *c,int base)
{
    int* min = MinMax(a,b,'m');
    int* max = MinMax(a,b,'M');
    c = (int*) malloc((max[0]+2)*sizeof(int));
    c[0] = max[0] + 1;
    for(int i =1;i<c[0]+1;i++) c[i] = 0;

    for (int i = 1; i < c[0]; i++)
    {
        if(i < min[0]+1)
            c[i] += min[i] + max[i];
        else
            c[i] += max[i];
            c[i + 1] += (c[i] / base);
            c[i] %= base;
    }
    return DeleteNull(c);
}
int* Subtraction(int *a,int *b,int *c,int base)
{
    int buf = 0, borrow = 0;
    int* min = MinMax(a,b,'m');
    int* max= MinMax(a,b,'M');
    c = (int*) malloc((max[0]+2)*sizeof(int));
    c[0] = max[0] + 1;
    for(int i =1;i<c[0]+1;i++) c[i] = 0;
   	for(int i=1;i<c[0];i++)
	{
        if(i < min[0]+1) buf = max[i] - min[i] - borrow;
		else buf = max[i] - borrow;
		if(buf>=0) {
			c[i] = buf;
			borrow = 0;
		}
		else {
			c[i] = base + buf;
			borrow = 1;
		}
	}
	return DeleteNull(c);
}
int* Multiplication(int *a,int *b,int *c,int base)
{
    c = (int*) malloc((a[0]+b[0]+2)*sizeof(int));
    c[0] = a[0]+b[0]+1;
    for(int i =1;i<c[0]+1;i++) c[i] = 0;
	for (int i = 1; i<= a[0]; i++)
		for (int j = 1; j <= b[0]; j++)
			c[i + j - 1] += a[i] * b[j];
	for (int i = 1; i < c[0]; i++)
	{
		c[i + 1] +=  c[i] / base;
		c[i] %= base;
	}
		c = DeleteNull(c);
    return c;
}

int* DivideOnDigit(int* mas, int digit, int* answer,bool retR,int base)
{
    if(digit == 0)
    {
        printf("Error! Dividing on zero value\n");
        return mas;
    }
    int ms = mas[0];
    answer = (int*) malloc((mas[0]+2)*sizeof(int));
    answer[0] = 0;
    int r = 0;
    int j = mas[0];
    while(j>0)
    {
        int cur = r * base + mas[j];
        answer[j] = (int)(cur/digit);
        r = (int)(cur % digit);
        j--;
        answer[0] ++;
    }
    answer[answer[0]+1]=r;
    if(retR)
    {
        int* r2 = DigitToArray(r,base);
        CopyArray(answer,r2,true);
        free(r2);
        return answer;
    }
    else return answer;
}
int* Dividing(int* u,int* v,int* q,bool retR,int base)
{
    int* f = NULL;
    int* tempV = NULL;
    if(v[0] == 1)
    {
        f = DivideOnDigit(u,v[1],f,retR,base);
        u = CopyArray(u,f,true);
        free(f);
        return u;
    }
    int n = v[0];
    int m = u[0] - v[0];
    q = (int*) malloc((u[0]+2)*sizeof(int));
    int* u2 = (int*) malloc((u[0]+2)*sizeof(int));
    q[0] = m+1;
    int* comp = (int*) malloc((n+2)*sizeof(int));
    int d = (base / (v[n] + 1));
    f = Multiplication(u,DigitToArray(d,base),f,base);
    if(f[0] == n+m)
    {
        f[f[0]+1] = 0;
        f[0]++;
    }
    u = CopyArray(u,f,true);
    free(f);
    f = Multiplication(v,DigitToArray(d,base),f,base);
    v = CopyArray(v,f,true);
    free(f);
    for(int j=m;j>=0;j--)
    {
        int cur = (u[j + n+1]) * base + u[j + n];
        int tempq = (int)(cur / v[n]);
        int tempr = (int)(cur % v[n]);
        do
        {
            if (tempq == base || (tempq * v[n - 2+1] > base * tempr + u[j+n-2+1]))
            {
                tempq--;
                tempr += v[n];
            }
            else break;
        }
        while(tempr < base);
        tempV = Multiplication(v,DigitToArray(tempq,base),tempV,base);
        int it = 1;
        for(int i=j+1;i<=n+j+1;i++)
        {
            int ag = u[i];
            u2[it] = u[i];
            u[i] = 0;
            it++;
        }
        u2[0] = n+1;
        bool signFlag = false;
        int saveNules = 0;
        for( int i=u2[0];i>1;i--)
        {
            if(u2[i] == 0)
            {
                u2[0]--;
                saveNules++;
            }
            else break;
        }
        if(u2 == MinMax(u2,tempV,'m') && u2 != MinMax(u2,tempV,'M')) signFlag = true;
        u2[0] = u2[0] + saveNules;
        int* f2 = Subtraction(u2,tempV,f2,base);
        u2 = CopyArray(u2,f2,true);
        free(f2);
        if(signFlag)
        {
            for (int i = 1; i <= n; i++) comp[i] = 0;
            comp[n+1] = 1;
            comp[0] = n+1;
            f = Subtraction(comp,u2,f,base);
            u2 = CopyArray(u2,f,true);
            free(f);
        }
        q[j+1] = tempq;
        if (signFlag)
        {
            q[j+1]--;
            int *f3 = Addition(u2,v,f3,base);
            u2 = CopyArray(u2,f3,true);
            u2[0]--;
            free(f3);
        }
        for(int i=1;i<=u2[0];i++) u[j+i] = u2[i];
    }
    q = DeleteNull(q);
    while(u[0]>n)
        u[0]--;
    int* r = NULL;
    r = DivideOnDigit(u,d,r,false,base);
    r = DeleteNull(r);
    free(tempV);
    free(comp);
    free(u2);
    if(retR)
    {
        free(q);
        return r;
    }
    else
    {
        free(r);
        return q;
    }
}
 int* Pow(int* a,int* b,int* c,int base)
 {
    int* f;
    c = DigitToArray(1,base);
    int* one = DigitToArray(1,base);
    while(!(b[0]==1 && b[1] ==0))
    {
         int* temp = DivideOnDigit(b,2,temp,true,base);
         int* q = DivideOnDigit(b,2,temp,false,base);
         if(temp[1] == 0 && temp[0] == 1)
         {
             free(b);
             b = q;
             f = Multiplication(a,a,f,base);
             a = CopyArray(a,f,true);
             free(f);
         }
         else{
            free(q);
            f = Subtraction(b,one,f,base);
            b = CopyArray(b,f,true);
            free(f);
            f = Multiplication(c,a,f,base);
            free(c);
            c = CopyArray(c,f,false);
            free(f);
         }
     }
     return c;
 }
 int* Mod(int* a,int* b,int base)
 {
    int* m = Dividing(a,b,m,true,base);
    return m;
 }
void Solve(char* file1, char* file2, char oper,char* resFile,int base, char* modFile,bool ModBool)
{
    int *a = NULL;
    a = fileRead(a,file1,base);
    int *b = NULL;
    b = fileRead(b,file2,base);
    char sa = '+',sb = '+';
    if(a[a[0]] == -3)
    {
         a[0]--;
         sa = '-';
    }
    if(b[b[0]] == -3)
    {
        b[0]--;
        sb = '-';
    }
    if(sa != sb)
    {
        if(oper == '+') oper = '-';
        else if(oper == '-')   oper = '+';
    }
    char res = ResultSign(oper,sa,sb,a,b);

    int* c = NULL;
    if(oper == '+') c = Addition(a,b,c,base);
    else if(oper == '-') c = Subtraction(a,b,c,base);
    else if(oper == '*') c = Multiplication(a,b,c,base);
    else if(oper == '/') c = Dividing(a,b,c,false,base);
    else if(oper == '^') c = Pow(a,b,c,base);
    else if(oper == '%') c = Mod(a,b,base);


    if(ModBool)
    {
        int* m = fileRead(m,modFile,base);
        int* t = Mod(c,m,base);
        free(c);
        c = t;
    }
    fileWrite(c,res,resFile,base);
    free(a);
    free(b);
    free(c);
}
int main(int argc, char* argv[])
{
    //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	PrintStart();

    if(!checkParam(argc,argv))
		return 0;

	char *fname_in1 = argv[1];
	char act = argv[2][0];
	char *fname_in2 =argv[3];
	char *fname_out = argv[4];
	char *bin = NULL;
	char *modFile = NULL;

	int base = 10;
	bool modBool = true;


    /*char string4parse[256], file1[32], file2[32], oper[2], res[32], binMark[32], modFile[32];
    int base = 10,spaces = 0;
   // bool ModBool = true;
    printf("Enter string in such way:\n");
    printf("[file1] [operator] [file2] [result file] [-b] [mod file]\n");
    gets(string4parse);
    sscanf(string4parse,"%s %s %s %s %s %s",&file1,&oper,&file2,&res,&binMark,&modFile);
    for(int i =0;i<strlen(string4parse)-1;i++) if(string4parse[i] == ' ') spaces++;*/

    if(argc == 5)
    {
        modBool = false;
    }

    else if(argc == 6)
    {
        modBool = false;
        bin = argv[5];
        if(!strcmp(bin, "-b"))
        {
            base = 256;
        }
    }

    else
    {
        bin = argv[5];
        if(!strcmp(bin, "-b"))
        {
            base = 256;
        }

        modFile = argv[6];
    }
    Solve(fname_in1, fname_in2, act, fname_out, base, modFile, modBool);
    return 0;
}
