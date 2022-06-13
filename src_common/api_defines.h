#pragma once
#include <stdint.h>
#include "windows.h"
#include "wininet.h"
#include "common.h"
BOOL __cdecl _RevertToSelf ();
HMODULE __cdecl _LoadLibraryA (LPCSTR);
BOOL __cdecl _VirtualProtect (LPVOID, SIZE_T, DWORD, PDWORD);
INT __cdecl _printf (LPCSTR, ...);
typedef BOOL(WINAPI* tRevertToSelf)();
typedef HMODULE(WINAPI* tLoadLibraryA)(LPCSTR);
typedef BOOL(WINAPI* tVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
typedef INT(WINAPI* tprintf)(LPCSTR, ...);
typedef struct {
	D_API( _RevertToSelf );
	D_API( _LoadLibraryA );
	D_API( _VirtualProtect );
	D_API( _printf );
} API ;
