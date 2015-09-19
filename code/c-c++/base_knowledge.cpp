//
// time		: create @ 2014/09/20
// description	: some base knowledge about c++
// 
#include <iostream>
#include <math.h>

using namespace std;
//////////////////////////////////////////////////////////////
// 1. Construct Function about class
class CA{
public:
	CA(int a, int b)
	{
		cout << "CA construct ... " << endl;
		m_a = a;
		m_b = b;
	}
	void print_number(){
		cout << m_a << ", " << m_b << endl;
	}
	
private:
	int m_a;
	int m_b;
};

class CB : public CA
{
public:
	CB(int a, int b)
	:CA(b, a)	//if delete this row, it will be error. You can test yourself!	
	{
		cout << "CB construct ... " << endl;
	}
};
///////////////////////////////////////////////////////////
//2. random
#define IM 139968 
#define IA 3877
#define IC 29573

static unsigned int s_nRandomSeed = -10;

//
unsigned int g_Random(unsigned int nMax)
{
	if (nMax)
	{
		s_nRandomSeed = s_nRandomSeed * IA + IC;
		printf("nRandomSeed = %u, %u\n", s_nRandomSeed, s_nRandomSeed % nMax);
		return s_nRandomSeed % nMax;
	}
	else
	{
		return 0;
	}
}

///////////////////////////////////////////////////////////
//3. strtoul
//#define strtoul_   simple_strtoul
#define TOLOWER(x) ((x) | 0x20)

static unsigned int simple_guess_base(const char *cp)
{
	if (cp[0] == '0') {
		if (TOLOWER(cp[1]) == 'x' && isxdigit(cp[2]))
			return 16;
		else
			return 8;
	} else {
		return 10;
	}
}

unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base)
{
	unsigned long result = 0;

	if (!base)
		base = simple_guess_base(cp);

	if (base == 16 && cp[0] == '0' && TOLOWER(cp[1]) == 'x')
		cp += 2;

	while (isxdigit(*cp)) {
		unsigned int value;

		value = isdigit(*cp) ? *cp - '0' : TOLOWER(*cp) - 'a' + 10;
		if (value >= base)
			break;
		result = result * base + value;
		cp++;
	}

	if (endp)
		*endp = (char *)cp;
	return result;
}

void testStrtoul()
{
	double a;
	//char pNum[] = "0xffffffff";
	char pNum[] = "0x100000000";
	//long long lb = 0x100000000;
	//double b = 1.0; // * lb;
	unsigned long ula = strtoul(pNum, 0, 16);
	unsigned long uls = simple_strtoul(pNum, 0, 16);
	//printf("%f, %d, %u\n", a, sizeof(double), ula);
	//a += 1;
	unsigned long c = (unsigned long)pow(2,32);// + 1;
	printf("%f, %x, %x, %x, %u\n", pow(2,32),  c, ula, uls, ULONG_MAX);
	/*
	 (1)pow is double, so +1 is also double
	 (2)double --> unsigned long, the result is 0xffffffff
	*/
	//double cc = pow(2, 32) * 4.0;
	//double cc = pow(2, 32) + 1.0;
	double cc = (double)4294967295.0 + 2.0;
	//double cc = 4294967295 * 2.0;
	//double cc = 1.0 << 32;
	printf("cc = %f, c = %d, %u\n", cc, c, c);
	c = cc;//(2^32)
	printf("cc = %f, c = %d, %u\n", cc, c, c);
	c = 0;
	char cNum[] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
	double dTemp = 0;
	for (int i = 0; i < sizeof(cNum)/sizeof(char); i++)
		dTemp = dTemp* 16.0 + cNum[i];
	c = dTemp;
	unsigned int n = dTemp;
	printf("%f, %u, %f, %u\n", a, c, dTemp, n);
	//
	double i = 4294967296.123;
	unsigned int e1 = (unsigned int)i;
	unsigned long e2 = (unsigned long)i;
	int e3 = (int)i;
	int e4 = (long)i;
	printf("e = %lu %ld, %d, %ld\n", e1, e2, e3, e4);
}

///////////////////////////////////////////////////////////
int main()
{
	//CB *b = new CB(1, 3);
	//b->print_number();
	//2. test
	/*const unsigned int MAX_NUM = 100;
	const unsigned int MAX_CIRCLE = 5;
	int nCounter[MAX_NUM] = {0};
	for ( int i = 0; i < MAX_CIRCLE; i++){
		unsigned int nRand = g_Random(MAX_NUM);
		nCounter[nRand] += 1;
	}
	int nCount = 0;
	for (int i = 0; i < MAX_NUM; i++){
		if (nCounter[i] == 0){
			printf("%d, %d\n", i, nCounter[i]);
			nCount = nCount + 1;
		}
	}
	printf("nCount = %d\n", nCount);*/
	//3.
	testStrtoul();
	return 0;
}