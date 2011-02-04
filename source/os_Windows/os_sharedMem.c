

#include "os_api.h"
#include "os_error.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>


/* CONSTANTS *************************************************************************************/

/**@Beschreibung:
 * Diese Funktion erzeugt ein SharedMemory-Objekt. Das SharedMemory wird mit einem Namen 
 * Katalogisiert, mit dem Threads auf die Speicherbereich zugreifen können.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @pSmHandle Zeiger auf das SharedMemory-Handle.
 * @size Größe des Shared-Memory.
 * @pName Name des Shared-Memory.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
int os_createSharedMemory(OS_HandleSharedMemory* pSmHandle, uint size, char* pName)
{
	HANDLE hSharedMem;

	if ( (strlen(pName)) > 14 ){  // max. 15 chars includding the end.
			printf("os_createSharedMemory: ERROR: name too long.\n", strlen(pName) );
			return OS_INVALID_STRING;
		}
	
	hSharedMem = CreateFileMapping(
                 INVALID_HANDLE_VALUE,      /* use paging file */
                 NULL,                      /* default security */
                 PAGE_READWRITE,            /* read/write access */
                 0,                         /* max. object size */
                 size,                      /* buffer size */
                 pName);                    /* name of mapping object */
	if(hSharedMem == NULL){
		DWORD err = GetLastError();
		printf("os_createSharedMemory: ERROR: Failed to create file mapping, Win err=%d\n", err);
		switch (err){
		case ERROR_INVALID_PARAMETER:     return OS_INVALID_PARAMETER;
			break;
		case ERROR_ALREADY_EXISTS:        return OS_NAME_EXIST;
			break;			
		default:                          return OS_SYSTEM_ERROR;
			break;		
		}
	}
	*pSmHandle = (OS_HandleSharedMemory)hSharedMem;
	return OS_OK;
}


/**@Beschreibung:
 * Diese Funktion entfernt ein SharedMemory-Objekt.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @smHandle SharedMemory-Handle.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
int os_deleteSharedMemory(OS_HandleSharedMemory smHandle)
{
	BOOL bWinRet = CloseHandle( (HANDLE)smHandle );
	if(bWinRet == 0){
		DWORD err = GetLastError();
		printf("os_deleteSharedMemory: ERROR: Failed to remove file mapping, Win err=%d\n", err);
		switch (err){
		case ERROR_INVALID_HANDLE:        return OS_INVALID_HANDLE;
			break;		
		default:                          return OS_SYSTEM_ERROR;
			break;		
		}
	}
	return OS_OK;
}


/**@Beschreibung:
 * Diese Funktion öffnet ein SharedMemory-Objekt und liefert enen Zeiger auf den gemeinsamen 
 * Speicher zurück.
 * @Rückgabewert: Zeiger auf den Shared-Memory.
 * @pName Name des Shared-Memory.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
OS_FILE* os_openSharedMemory(char* pName)
{
	HANDLE hSharedMem;
	LPCTSTR pBuf;

	hSharedMem = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,     /* read/write access */
                   FALSE,                   /* do not inherit the name */
                   pName);                  /* name of mapping object */
	if (hSharedMem == NULL){ 
		printf("os_openSharedMemory: ERROR: Failed to open file mapping, Win err=%d\n", GetLastError());
		return NULL;
	} 
	pBuf = (LPTSTR) MapViewOfFile(hSharedMem, /* handle to map object */
               FILE_MAP_ALL_ACCESS,         /* read/write permission */
               0,                    
               0,                    
               0);                          /* map whole view */      
	if (pBuf == NULL){
		printf("os_openSharedMemory: ERROR: Failed to map view of file, Win err=%d\n", GetLastError());
		return NULL;
	}
	return (OS_FILE*)pBuf;
}


/**@Beschreibung:
 * Diese Funktion schliesst ein SharedMemory-Objekt.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @pFile Zeiger auf den Buffer des SharedMemory
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
int os_closeSharedMemory(OS_FILE** pFile)
{
	BOOL bWinRet = UnmapViewOfFile(*pFile);
	if(bWinRet == 0){
		DWORD err = GetLastError();
		printf("os_closeSharedMemory: ERROR: Failed unmap view of file, Win err=%d\n", err);
		switch (err){
		case ERROR_INVALID_ADDRESS:     return OS_INVALID_POINTER;
			break;		
		default:                        return OS_SYSTEM_ERROR;
			break;		
		}
	}
	*pFile = NULL;
	return OS_OK;
}


/**@Beschreibung:
 * Diese Funktion kopiert einen Speicherblock in das SharedMemory-Objekt.
 * Überlappen sich Quell- und Zielblocken, ist das Ergebnis undefiniert !!!!
 * @pFile Zeiger auf den Buffer des Shared-Memory.
 * @offset Adressabstand ab dem geschrieben werden soll.
 * @pBuf Zeiger auf den Quelle-Puffer
 * @bufLen Größe des Puffers in Bytes.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
void os_writeSharedMemory(OS_FILE* pFile, uint offset, char* pBuf, uint bufLen)
{
	CopyMemory((PVOID)(pFile+offset), pBuf, bufLen);
}


/**@Beschreibung:
 * Diese Funktion liest einen Speicherblock aus dem SharedMemory-Objekt.
 * Überlappen sich Quell- und Zielblocken, ist das Ergebnis undefiniert !!!!
 * @pFile Zeiger auf den Buffer des Shared-Memory.
 * @offset Adressabstand ab dem gelesen werden soll.
 * @pBuf Zeiger auf den Empfangspuffer.
 * @bufLen Größe des Puffers in Bytes.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
void os_readSharedMemory(OS_FILE* pFile, uint offset, char* pBuf, uint bufLen)
{
	CopyMemory(pBuf, (PVOID)(pFile+offset), bufLen);
}


