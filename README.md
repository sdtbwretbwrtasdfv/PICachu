# PICachu     (╯°□°）╯︵ ┻━┻

## _Easy to use position independent code compile_
PICachu is a framework for writing x86/x64 position independent code for Windows.

Basic usage:
- Add needed WinAPI to "winapis.txt" using following format - *dllname.dll->func_name<-func_type<<(func_arg1, func_arg2, etc)*
- Add whatever ya whant to "src_mainpic/main.h"
- Use only headers and include them to main.h
- ./compile.sh

All functions that we specified in "winapis.txt" will be available in Api struct with underline prefix (call example: Api._printf(msg); ).
If you wanna make them also available outside "Mmain" just pass Api member to func.

Actually with this you can only resolv functions from:
- kernel32.dll
- advapi32.dll
- msvcrt.dll
- ntdll.dll
- user32.dll
- winhttp.dll
- wininet.dll
- ws2_32.dll

If you need some additional library, add it to "src_common/api_resolve.c" in the "loadDll" method in the following format:
```sh
#ifdef H_LIB_LIBNAMEWITHOUTDOTDLL
    if (dll_hash == H_LIB_LIBNAMEWITHOUTDOTDLL) {
	    char dll_name[] = {'l','i','b','n','a','m','e','w','i','t','h','o','u','t','d','o','t','d','l','l','.','d','l','l', 0x00};
	    ptr_loaded_dll = (uint64_t)((tLoadLibraryA)fptr_loadLibary)(dll_name);
    }
#endif
```
## Size Matters
Sinse we don't use stdlib and all other usefull stuff, resulting PE will be small :)
If needed... Check "src_loader/stdlib" or dyn resolve from msvcrt.dll.
```sh
#node_1㉿#Usaaar)-> cat helloworld.c 
#include <stdio.h>
int main(){
	printf("Hello World!");
}    
(#node_1㉿#Usaaar)-> x86_64-w64-mingw32-gcc helloworld.c                                                                                                      
(#node_1㉿#Usaaar)-> ls -lh a.exe | awk '{print  $5}'   
285K
(#node_1㉿#Usaaar)-> echo "msvcrt.dll->printf<-INT<<(LPCSTR, ...)" >> winapis.txt 
(#node_1㉿#Usaaar)-> python3 scripts/str2chars.py 'Hello world!'
char msg[] = {'H','e','l','l','o',' ','w','o','r','l','d','!', 0x00};
(#node_1㉿#Usaaar)-> cat src_mainpic/main.h 
int Mmain(API Api, LPCWSTR PasswdFromExecute){
    char msg[] = {'H','e','l','l','o',' ','w','o','r','l','d','!', 0x00};
    Api._printf(msg);
    return 0;
}
(#node_1㉿#Usaaar)-> ./compile.sh 
	[*]Cleanning...
	[*]Building API hashes file
	[*]Build adjust-stack
	[*]Build ApiResolve x64
	[*]Build ApiResolve x86
	[*]Build PIC for arch: x64
	[*]Build mainpic object
	[*]Build PIC for arch: x86
	[*]Build mainpic object
	[*]Compiling loader object arch: x64
	[*]Compiling loader object arch: x86
(#node_1㉿#Usaaar)-> ls -lh build/loader_x64.exe | awk '{print  $5}'    
	4.0K
```

```sh
PS C:\Users\User\Desktop\tests> .\a.exe
	Hello World!
PS C:\Users\User\Desktop\tests> .\loader_x64.exe
	Hello world!
PS C:\Users\User\Desktop\tests> .\loader_x86.exe
	Hello world!
PS C:\Users\User\Desktop\tests> .\pic_x64.exe
	Hello world!
PS C:\Users\User\Desktop\tests> .\pic_x86.exe
	Hello world!
PS C:\Users\User\Desktop\tests> dir
    Directory: C:\Users\User\Desktop\tests
	Mode                 LastWriteTime         Length Name
	----                 -------------         ------ ----
	-a----         6/13/2022   5:02 PM         291000 a.exe
	-a----         6/13/2022   5:06 PM           4096 loader_x64.exe
	-a----         6/13/2022   5:06 PM           4608 loader_x86.exe
	-a----         6/13/2022   5:06 PM           2560 pic_x64.exe
	-a----         6/13/2022   5:06 PM           2560 pic_x86.exe
```
## Why? For what?
Only for study. So the result may not be stable :)
PICachu automatically creates hashes for all used APIs, and also automatically creates the structure and rewrites Entry.c so that the APIs can be accessed in the future.

## Limitations
We cannot use strings since these will not be included in the .text section of our executable, we need to write them as byte arrays to ensure that they are dynamically constructed on the stack.
Helper - scripts/str2chars.py
```sh
(#node_1㉿#Usaaar)-> python3 scripts/str2chars.py test
char msg[] = {'t','e','s','t', 0x00};
```
Another way - use macro, for cast vars or funcs in a specific region of memory.
Something like:
```sh
#define D_SEC( x )	__attribute__(( section( ".text$" #x ) ))
D_SEC( SomeSectionThatShouldBeCreatingWhileLinking ) char * my_var = "hehehe";
```
But if you do so, then you will have to change the logic of the linker, by custom script.
## How to inline this after compile?
After compile just use scripts/bin2sc.sh to create PIC hex blob. Like this:
```sh
(#node_1㉿#Usaaar)-> cripts/bin2sc.sh -exe build/loader_x64.exe 
(#node_1㉿#Usaaar)-> cat build/loader_x64.bin.h
char shellcode [] = "\x56\x48\x89\xe6\x48";
```
After that allocated blob inside the .text. Cast the array containing our blob into a function pointer and invoke it.
Example for Visual Studio:
```sh
#pragma section(".text")
__declspec(allocate(".text")) char our_blob[] =
"\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc\xfc";

int main() {
    (*(void(*)())(&our_blob))();
}
```
## Warranty
DO NOT USE THIS FOR ILLEGAL PURPOSES.THE AUTHOR DOES NOT KEEP RESPONSIBILITY FOR ANY ILLEGAL ACTION YOU DO.
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. 
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU

