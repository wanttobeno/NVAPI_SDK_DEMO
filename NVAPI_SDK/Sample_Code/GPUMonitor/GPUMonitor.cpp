/*
	https://www.codenong.com/cs106902684/
*/

#include "GPUMonitorEx.h"

#ifdef _M_IX86
#pragma comment(lib,"../../x86/nvapi.lib")
#else
#pragma comment(lib,"../../amd64/nvapi64.lib")
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	GPUMonitorEx obj;
	obj.GPUInit();

	obj.getGPUInfo();

}