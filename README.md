# Overview

## About The Project

Helper library for external windows game hacking.

Collaborative work provided by the <a href="https://discord.gg/CRMQq4F" target="_blank">CasualCommunity</a>

## Installation

 1. Download current release ("CasualLibrary0.2.rar") from <a href="https://github.com/CasualCoder91/CasualLibrary/releases/" target="_blank">the release section</a>
 2. Extract *.h and *.lib file(s) at appropriate location in your project directory.
 3. Include them into your project.

## Documentation

The main set of documentation can be found <a href="https://casualcoder91.github.io/CasualLibrary/html/index.html" target="_blank">here</a>

## Usage

### bare-bones setup

#### external

```cpp
#include <iostream>
#include "Memory.h"

int main(){
    External::Memory memory = External::Memory("target.exe");
    External::Memory memoryDebug = External::Memory("target.exe", true); //use for debug messages
}
```

#### internal

<details>
  <summary>Sample dll including the library</summary>

  ```cpp
  #include <Windows.h>
  #include <iostream>

  #include <Memory.h>

  HMODULE myhModule;

  DWORD __stdcall EjectThread(LPVOID lpParameter) {
      Sleep(100);
      FreeLibraryAndExitThread(myhModule, 0);
  }

  DWORD WINAPI Menue() {
      AllocConsole();
      FILE* fp;
      freopen_s(&fp, "CONOUT$", "w", stdout); // output only
      std::cout << "Running tests ...\n\n";

      //add Code here

      while (1) {
          Sleep(100);
          if (GetAsyncKeyState(VK_NUMPAD0))
              break;
      }
      fclose(fp);
      FreeConsole();
      CreateThread(0, 0, EjectThread, 0, 0, 0);
      return 0;
  }


  BOOL APIENTRY DllMain(HMODULE hModule,
      DWORD  ul_reason_for_call,
      LPVOID lpReserved
      )
  {
      switch (ul_reason_for_call)
      {
      case DLL_PROCESS_ATTACH:
          myhModule = hModule;
          CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Menue, NULL, 0, NULL);
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
          break;
      }
      return TRUE;
  }
  ```

</details>

### read/write memory

#### external

```cpp
//works for all types including uintptr_t, int, double etc. as well as custom structs and classes.
//does NOT work for arrays/vectors
Address address = Address(0x2240001C);
// read integer stored at address
int test = memory.read<int>(address);
// read one word
std::string word = memory.readString(address);
//read 200 chars
std::string text = memory.readString(address, 200);
//write value 5 starting at given address
memory.write<int>(address, 5);
```

#### internal

```cpp
//works for all types including uintptr_t, int, double etc. as well as custom structs and classes.
//does NOT work for arrays/vectors
Address address = Address(0x2240001C);
// read integer stored at address
int test = Internal::Memory::read<int>(address);
//write value 5 starting at given address
Internal::Memory::write<int>(address, 5);
```

### get module base address

#### external

```cpp
Address clientAddr = memory.getModule("client.dll");
```

#### internal

```cpp
Address clientAddr = Internal::Memory::getModule("client.dll");
```

### get address from static pointer + offsets

![Static Pointer in CE](docs/img/getAddress.png)

#### external

```cpp
Address baseAddr = memory.getModule("ZW64.exe");
Address healthAddr = memory.getAddress(baseAddr+0x00003648, { 0x40,0xE4 });
```

#### internal

```cpp
Address baseAddr = Internal::Memory::getModule("ZW64.exe");
Address healthAddr = Internal::Memory::getAddress(baseAddr+0x00003648, { 0x40,0xE4 });
```

### AOB Scanner

#### external

```cpp
Address address = memory.findSignature(0x7FF702CB5D00, "? 39 05 F0 A2 F6 FF" , 10000);
```

#### internal

```cpp
Address address = Internal::Memory::findSignature(0x7FF702CB5D00, "? 39 05 F0 A2 F6 FF" , 10000);
```
