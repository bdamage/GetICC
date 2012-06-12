// GetICC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <simmgr.h>
#pragma comment(lib, "cellcore.lib")

char szICC[22];


int WriteRegistry(HKEY hKey, WCHAR *szPath, WCHAR *szValueName, DWORD dwType,LPBYTE lpData,DWORD cbData)
{
	HKEY phkResult;
	DWORD dwDisposition=0;
	if(RegCreateKeyEx(hKey, szPath,0,NULL, 0, 0,NULL, &phkResult, &dwDisposition )==ERROR_SUCCESS)
	{		
		RegSetValueEx(phkResult, szValueName, 0, dwType, lpData, cbData); 
		RegFlushKey(hKey);
		RegCloseKey( phkResult );
		
	}
	return 0;
}
//Report back to MSP that this is running
void WriteICC()
{
	TCHAR wPath[] = _T("Software\\MSP\\Attributes");
	TCHAR wszBuf[256];

	wsprintf(wszBuf,_T("%S"),szICC);
	int length = _tcslen(wszBuf);
	WriteRegistry(HKEY_LOCAL_MACHINE,wPath,_T("ICC"),REG_SZ,(LPBYTE)wszBuf,length*sizeof(TCHAR));
}

void GetICC()
{

	HSIM hSim=NULL;
	DWORD dwAddress=0x2FE2;
	DWORD dwRecordType=1;
	DWORD dwIndex=0;
	BYTE byData[ 10];
	DWORD dwBytesRead=0L;
	HRESULT hr;
	
	
	ZeroMemory(szICC,sizeof(szICC));

	hr = SimInitialize(SIM_INIT_NONE, NULL, 0, &hSim) ;
	hr = SimReadRecord (hSim, dwAddress ,  SIM_RECORDTYPE_TRANSPARENT,  
		dwIndex,  byData, sizeof(byData),  &dwBytesRead );
	
	if(hr==S_OK)
	{
		int n = 0;
		for(int i=0; i<10; i++)
		{
			szICC[n] = (char)(byData[i] & 0x0F)+48;
			szICC[n+1] = (char)(byData[i] >> 4)+48;
			n+=2;

		}
		WriteICC();
	}
	if(hSim!=NULL)
		hr = SimDeinitialize( hSim );

}

int _tmain(int argc, _TCHAR* argv[])
{
	GetICC();
	return 0;
}

