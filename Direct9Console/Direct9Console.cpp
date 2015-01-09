// Direct9Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef LPDIRECT3D9(WINAPI* PD3DCALL)(UINT);

void* GetDirect3DCreateFunc()
{
	HMODULE d3mod = LoadLibrary(L"D3D9.DLL");

	if (d3mod == NULL)
		return NULL;

	return GetProcAddress(d3mod, "Direct3DCreate9");
}

BOOL CheckDirectX()
{
	LPDIRECT3D9 g_pD3D;
	D3DCAPS9 caps;
	PD3DCALL Direct3DCreate9 = (PD3DCALL)GetDirect3DCreateFunc();

	if (Direct3DCreate9 == NULL)
		return FALSE;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
		return FALSE;

	if (FAILED(g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		return FALSE;

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Direct9Console");
	char ch; scanf_s("%c", &ch);
	char *result = CheckDirectX() ? "OK" : "FAILED";

	printf(" - CheckDirectX: %s", result);

	return 0;
}

