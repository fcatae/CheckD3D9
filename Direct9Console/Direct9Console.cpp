// Direct9Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef LPDIRECT3D9(WINAPI* PD3DCALL)(UINT);

void Log(char* msg)
{
	printf(" - %s\n", msg);
}

void* GetDirect3DCreateFunc()
{
	Log("LoadModule D3D9.DLL");
	HMODULE d3mod = LoadLibrary(L"D3D9.DLL");

	if (d3mod == NULL)
		return NULL;

	Log("Load Function Direct3DCreate9");
	return GetProcAddress(d3mod, "Direct3DCreate9");
}

BOOL CheckDirectX()
{
	LPDIRECT3D9 g_pD3D;
	D3DCAPS9 caps;
	PD3DCALL Direct3DCreate9 = (PD3DCALL)GetDirect3DCreateFunc();

	if (Direct3DCreate9 == NULL)
		return FALSE;

	Log("Call Direct3DCreate9()");
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
		return FALSE;

	Log("Call GetDeviceCaps()");
	HRESULT hr = g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	return SUCCEEDED(hr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Direct9Console\n");

	char *result = CheckDirectX() ? "OK" : "FAILED";

	printf("Result = %s\n", result);

	return 0;
}

