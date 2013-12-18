#include <Logger.h>
#include "Kernel.h"

int main()
{
	Kernel* kernel = new Kernel();

	kernel->run();

	system("pause");
	return 0;
}