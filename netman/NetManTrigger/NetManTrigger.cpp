#include <iostream>
#include <Windows.h>
#include <comdef.h>
#include <netcon.h>

typedef void(WINAPI* _NcFreeNetconProperties)(NETCON_PROPERTIES* pProps);

int wmain(int argc, wchar_t* argv[])
{
    HMODULE hNetShell;
    _NcFreeNetconProperties impNcFreeNetconProperties;
    HRESULT hr = S_OK;
    INetConnectionManager* pConnectionManager = NULL;
    IEnumNetConnection* pEnumConnection = NULL;
    INetConnection* pConnection = NULL;
    ULONG count;
    NETCON_PROPERTIES* pConnectionProperties = NULL;

    if (!(hNetShell = LoadLibrary(L"netshell.dll")))
        goto cleanup;

    if (!(impNcFreeNetconProperties = (_NcFreeNetconProperties)GetProcAddress(hNetShell, "NcFreeNetconProperties")))
        goto cleanup;

    if (FAILED(hr = CoInitializeEx(0, COINIT_MULTITHREADED)))
        goto cleanup;

    if (FAILED(hr = CoCreateInstance(CLSID_ConnectionManager, 0, CLSCTX_ALL, __uuidof(INetConnectionManager), (void**)&pConnectionManager)))
        goto cleanup;

    if (FAILED(hr = pConnectionManager->EnumConnections(NCME_DEFAULT, &pEnumConnection)))
        goto cleanup;

    while (pEnumConnection->Next(1, &pConnection, &count) == S_OK)
    {
        if (SUCCEEDED(hr = pConnection->GetProperties(&pConnectionProperties)))
        {
            wprintf(L"Interface: %ls\r\n", pConnectionProperties->pszwName);
            impNcFreeNetconProperties(pConnectionProperties);
        }

        pConnection->Release();
    }

cleanup:
    if (pEnumConnection)
        pEnumConnection->Release();
    if (pConnectionManager)
        pConnectionManager->Release();
    if (FAILED(hr))
        wprintf(L"[-] COM error: 0x%08x\r\n", hr);

    return 0;
}