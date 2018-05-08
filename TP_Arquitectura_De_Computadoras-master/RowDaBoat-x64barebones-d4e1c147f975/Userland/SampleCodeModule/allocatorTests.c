#include <shell.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t _int80(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

void testOne()
{
	printf("Testeo doble creacion: ");
	uint64_t firstAddress = _int80(14, 1000, 0, 0, 0, 0);
	uint64_t secondAddress = _int80(14, 1000, 0, 0, 0, 0);
	if((int)firstAddress == (int)secondAddress)
	{
		printf("Mismos lugares. Mala alocacion\n");
	}
	else
	{
		printf("Distintos lugares. Correcta alocacion\n");
	}
}

void testTwo()
{
	printf("Testeo free: ");
	uint64_t firstAddress = _int80(14, 1000, 0, 0, 0, 0);
	_int80(15, firstAddress, 0, 0, 0, 0);
	uint64_t secondAddress = _int80(14, 1000, 0, 0, 0, 0);
	if((int)firstAddress == (int)secondAddress)
	{
		printf("Mismos lugares. Buen free\n");
	}
	else
	{
		printf("Distintos lugares. Mal free\n");
	}
}