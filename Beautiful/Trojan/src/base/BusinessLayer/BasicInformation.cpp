#include "BasicInformation.h"


BasicInformation::BasicInformation(void)
{
	m_unknownResult = "Unknown";
	m_unknownVector.push_back(m_unknownResult);
	// Retrive all information about network card.
	_getNetworkInfo();
}

BasicInformation::~BasicInformation(void)
{

}

string& BasicInformation::getSystemBootTime()
{
	if (_getSystemBootTime())
	{
		return m_boottime;
	}
	return m_unknownResult;
}

string& BasicInformation::getCPUInfos()
{
	if (_getCPUInfos())
	{
		return m_cpuinfo;
	}
	return m_unknownResult;
}

string& BasicInformation::getHostName()
{
	if (_getHostName())
	{
		return m_hostname;
	}
	return m_unknownResult;
}
vector<string> BasicInformation::getIPAddress()
{
	return m_ipaddr.empty()?m_unknownVector:m_ipaddr;
}

vector<string> BasicInformation::getMACAddress()
{
	return m_macaddr.empty()?m_unknownVector:m_macaddr;
}

string& BasicInformation::getMemAvailTotal()
{
	if (_getMemAvailTotal())
	{
		return m_memAvailTotal;
	}
	return m_unknownResult;
}

vector<string> BasicInformation::getNetworkCard()
{
	return m_ncard.empty()?m_unknownVector:m_ncard;
}

string& BasicInformation::getOSInformation()
{
	if (_getOSInformation())
	{
		return m_osinfo;
	}
	return m_unknownResult;
}

vector<string> BasicInformation::getVolumeInformation()
{
	if (_getVolumeInformation())
	{
		return m_volinfo;
	}
	return m_unknownVector;
}
/*
 * Get system boot time
 */
bool BasicInformation::_getSystemBootTime()
{
	SYSTEM_TIME_INFORMATION Sti;   
	LONG                    status;   
	FILETIME                ftSystemBoot;   
	SYSTEMTIME              stSystemBoot;  
	char                    datetime[48];

	PROCNTQSI NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtQuerySystemInformation");   
	if (!NtQuerySystemInformation) 
	{
		return false;   
	}
	status = NtQuerySystemInformation(SystemTimeInformation,&Sti,sizeof(Sti),0);   
	if (status!=NO_ERROR)   
	{
		return false;   
	}
	ftSystemBoot = *(FILETIME *)&(Sti.liKeBootTime);   
	FileTimeToLocalFileTime(&ftSystemBoot,&ftSystemBoot);   
	FileTimeToSystemTime(&ftSystemBoot,&stSystemBoot);   
	sprintf(datetime, "%04d-%02d-%02d %02d:%02d:%02d",   
			 stSystemBoot.wYear, stSystemBoot.wMonth, stSystemBoot.wDay,   
			 stSystemBoot.wHour, stSystemBoot.wMinute, stSystemBoot.wSecond);
	m_boottime = datetime;

	return true;
}
/*
 * CPU information
 */
bool BasicInformation::_getCPUInfos()
{
	HKEY hkey;
	LPCWSTR StrKey = TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, StrKey, NULL, KEY_ALL_ACCESS, &hkey))
	{
		DWORD dwSize = 256;
		DWORD dwType = REG_SZ;   
		char str[256] = {'\0'};      
		if (ERROR_SUCCESS == RegQueryValueExA(hkey, "ProcessorNameString", 0, &dwType, (LPBYTE)str, &dwSize))   
		{   
			m_cpuinfo = str;
			RegCloseKey(hkey);
		}   
		else
		{
			RegCloseKey(hkey);
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}
/*
 * Get host name
 */
bool BasicInformation::_getHostName()
{
	CHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	if( !GetComputerNameA( infoBuf, &bufCharCount ))
	{
		return false;
	}
	m_hostname = infoBuf;

	return true;
}
/*
 * Get free memory
 */
bool BasicInformation::_getMemAvailTotal()
{
	MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(mem_info);
	if (!GlobalMemoryStatusEx(&mem_info)) {
		return false;
	}

	string tmp;
	CHAR total[16] = {'\0'};   
	CHAR avail[16] = {'\0'};
	CHAR allinfo[32] = {'\0'};
	sprintf(total, "%.2f(GB)", ((mem_info.ullTotalPhys/DIV)/DIV)/DIV);    // to avoid the overflow of multiplication 
	sprintf(avail, "%.2f(GB)", ((mem_info.ullAvailPhys/DIV)/DIV)/DIV);   
	strncat(allinfo, avail, strlen(avail));
	strncat(allinfo, "/", strlen("/"));
	strncat(allinfo, total, strlen(total));

	m_memAvailTotal = allinfo;

	return true;
}
/*
 * ��ȡϵͳ����ӿڿ���Ϣ
 */
bool BasicInformation::_getNetworkInfo()
{
	char macaddr[24] = {'\0'};
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	}
	if (ERROR_SUCCESS == nRel)
	{
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{
			string singleItem = pIpAdapterInfo->Description;
			m_ncard.push_back(singleItem);
			sprintf(macaddr, "%02X-%02X-%02X-%02X-%02X-%02X", pIpAdapterInfo->Address[0],
													pIpAdapterInfo->Address[1],
													pIpAdapterInfo->Address[2],
													pIpAdapterInfo->Address[3],
													pIpAdapterInfo->Address[4],
													pIpAdapterInfo->Address[5]);
			singleItem = macaddr;
			m_macaddr.push_back(singleItem);
			//���������ж�IP,���ͨ��ѭ��ȥ�ж�
			IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
			do 
			{
				singleItem = pIpAddrString->IpAddress.String;
				m_ipaddr.push_back(singleItem);
				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	//�ͷ��ڴ�ռ�
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	return true;
}
/*
 * ��ȡ����ϵͳ������Ϣ
 */
bool BasicInformation::_getOSInformation()
{
	HKEY  hKey;   
	UCHAR name[32]={'\0'};   
	UCHAR version[32]={'\0'}; 
	CHAR allinfo[64] = {'\0'};
	DWORD len = 32;    
	DWORD dwDataType = 0;       
	OSVERSIONINFO OsInfo;   
	string singleItem;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);   
	if (GetVersionEx(&OsInfo))
	{    
		switch (OsInfo.dwPlatformId)   
		{   
		case VER_PLATFORM_WIN32_WINDOWS:   
			if(OsInfo.dwMajorVersion == 3)   
			{   
				m_osinfo = "Windows 95";   
			}   
			else if(OsInfo.dwMajorVersion == 4)   
			{   
				if (OsInfo.dwMinorVersion==0x5a)   
				{   
					m_osinfo = "Windows ME";   
				}   
				else   
					m_osinfo = "Windows 98";   
			}   
			break;   
		case VER_PLATFORM_WIN32_NT:   
			if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion"), 0, KEY_READ,   &hKey) == ERROR_SUCCESS)   
			{   
				RegQueryValueExA(hKey, "ProductName", NULL, &dwDataType, name, &len);   
				RegQueryValueExA(hKey, "CSDVersion", NULL, &dwDataType, version, &len);    
				RegCloseKey(hKey);    
				strncat(allinfo, (char*)name, strlen((char*)name));
				strncat(allinfo, "  ", strlen("  "));
				strncat(allinfo, (char*)version, strlen((char*)version));
				m_osinfo = allinfo;
			}
			else
			{
				m_osinfo = m_unknownResult;
			}
			break;   
		default:   
			m_osinfo = m_unknownResult;
			break;   
		}  
	}
	// this function would never fail.
	return true;
}
/*
 * ��ȡϵͳ���̻�����Ϣ
 */
bool BasicInformation::_getVolumeInformation()
{
	string singleItem;

	const char* UNKNOWNTYPE = " UNKNOWN";
	const char* SOFTDISK = " SOFTDISK";
	const char* REMOVABLEDISK = " REMOVABLE";
	const char* LOCALDISK = " LOCAL";
	const char* NETDISK = " REMOTE";
	const char* CDROM = " CDROM";
	const char* RAMDISK = " RAMDISK";
	const int DISKINFO_LEN = 64;
	const int LABELITEM_LEN = 4;   //ÿ���̷�ռ4���ַ�
	const int FILESYSTEM_LEN = 10;

	char diskInfo[DISKINFO_LEN] = {'\0'};
	char cItem[DISKINFO_LEN] = {'\0'};
	char fmt[DISKINFO_LEN] = {'\0'};
	char FileSystemNameBuffer[FILESYSTEM_LEN] = {'\0'};
	char VolumeNameBuffer[DISKINFO_LEN] = {'\0'};
	GetLogicalDriveStringsA(DISKINFO_LEN, diskInfo);
	char* index = diskInfo;
	unsigned int ret;

	while (*index)
	{
		memset(cItem, 0, strlen(cItem));
		memset(fmt, 0, strlen(fmt));
		memset(FileSystemNameBuffer, 0, strlen(FileSystemNameBuffer));
		memset(VolumeNameBuffer, 0, strlen(VolumeNameBuffer));
		strncat(cItem, index, strlen(index));
		ret = GetDriveTypeA(index);
		switch(ret)
		{
		case DRIVE_UNKNOWN:
			strncat(cItem, UNKNOWNTYPE, strlen(UNKNOWNTYPE));
			break;
		case DRIVE_NO_ROOT_DIR:
			strncat(cItem, SOFTDISK, strlen(SOFTDISK));
			break;
		case DRIVE_REMOVABLE:
			strncat(cItem, REMOVABLEDISK, strlen(REMOVABLEDISK));
			break;
		case DRIVE_FIXED:
			strncat(cItem, LOCALDISK, strlen(LOCALDISK));
			break;
		case DRIVE_REMOTE:
			strncat(cItem, NETDISK, strlen(NETDISK));
			break;
		case DRIVE_CDROM:
			strncat(cItem, CDROM, strlen(CDROM));
			break;
		case DRIVE_RAMDISK:
			strncat(cItem, RAMDISK, strlen(RAMDISK));
			break;
		}
		if (ret != DRIVE_CDROM)  // retrive ultra information if other than CDROM
		{
			 DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;
			 if (!GetDiskFreeSpaceA(index, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters))
			 {
				 return false;
			 }
			 sprintf(fmt, " %5.2f(GB)/%5.2f(GB)", ((NumberOfFreeClusters/DIV)*SectorsPerCluster*(BytesPerSector/DIV))/DIV, ((TotalNumberOfClusters/DIV)*SectorsPerCluster*(BytesPerSector/DIV))/DIV);
			 strncat(cItem, fmt, strlen(fmt));
			 
			 DWORD VolumeSerialNumber;
			 DWORD MaximumComponentLength;
			 DWORD FileSystemFlags;
			 if (!GetVolumeInformationA(index, VolumeNameBuffer, DISKINFO_LEN, &VolumeSerialNumber, &MaximumComponentLength, &FileSystemFlags, FileSystemNameBuffer, FILESYSTEM_LEN))
			 {
				 return false;
			 }
			 memset(fmt, 0, strlen(fmt));
			 sprintf(fmt, " %s %s", VolumeNameBuffer, FileSystemNameBuffer);
			 strncat(cItem, fmt, strlen(fmt));
			 
		}
		m_volinfo.push_back(string(cItem));
		index += 4;  // skip to the next record.
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
// Cache record information
IECacheInfo::IECacheInfo()
{
	// pointer to memory allocated in somewhere, so we have to free
	// the memory manually at last.
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
	HANDLE hCacheDir;
	CacheEntry tmp;
	// To get the first cache entry
	
	hCacheDir = getStartCacheEntry(&lpCacheEntry);
	if (hCacheDir)
	{
		setAllFields(&tmp, lpCacheEntry);
		transformTimeFormat(&tmp, lpCacheEntry);
		delete [] lpCacheEntry;
		m_recordsVec.push_back(tmp);  // push the first cache record
		while (getNextCacheEntry(hCacheDir, &lpCacheEntry))
		{
			if (lpCacheEntry->lpszLocalFileName == NULL)
			{
				continue;
			}
			memset(&tmp, 0, sizeof(CacheEntry));
			setAllFields(&tmp, lpCacheEntry);
			transformTimeFormat(&tmp, lpCacheEntry);
			delete [] lpCacheEntry;
			m_recordsVec.push_back(tmp);
		}
		FindCloseUrlCache(hCacheDir);  // close the file handle.
	}
}

HANDLE IECacheInfo::getStartCacheEntry(LPINTERNET_CACHE_ENTRY_INFO* startEnt)
{
	HANDLE hCacheEnt;
	DWORD dwEntrySize;
	DWORD MAX_CACHE_ENTRY_INFO_SIZE = 4096;
	dwEntrySize = MAX_CACHE_ENTRY_INFO_SIZE;
	*startEnt = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
	(*startEnt)->dwStructSize = dwEntrySize;
HeadAgain:
	if (!(hCacheEnt = FindFirstUrlCacheEntry(NULL, *startEnt, &dwEntrySize)))
	{
		delete [] *startEnt;
		switch (GetLastError())
		{
		case ERROR_INSUFFICIENT_BUFFER:  // To allocate more memory to store the entry information
			*startEnt = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
			(*startEnt)->dwStructSize = dwEntrySize;
			goto HeadAgain;
			break;
		default:
			return (HANDLE)0;
		}
	}

	return hCacheEnt;
}

bool IECacheInfo::getNextCacheEntry(HANDLE hDir, LPINTERNET_CACHE_ENTRY_INFO* next)
{
	DWORD dwEntrySize;
	DWORD MAX_CACHE_ENTRY_INFO_SIZE = 4096;
	dwEntrySize = MAX_CACHE_ENTRY_INFO_SIZE;

	*next = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
	(*next)->dwStructSize = dwEntrySize;
HeadAgain:
	if (!FindNextUrlCacheEntry(hDir, *next, &dwEntrySize))
	{
		delete [] *next;
		switch(GetLastError())
		{
		case ERROR_INSUFFICIENT_BUFFER:
			*next = (LPINTERNET_CACHE_ENTRY_INFO)new char[dwEntrySize];
			(*next)->dwStructSize = dwEntrySize;
			goto HeadAgain;
			break;
		default:
			FindCloseUrlCache(hDir);
			return false;
		}
	}
	return true;
}

void IECacheInfo::setAllFields(pCacheEntry entry, const LPINTERNET_CACHE_ENTRY_INFO record)
{
	char *ptr = NULL;
	char chTemp[512] = {'\0'};
	char localPath[256] = {'\0'};

	if (record->lpszLocalFileName == NULL || record->lpszSourceUrlName == NULL)  // some cache entry present without this field. We just ignore it.
	{
		return ;
	}
	entry->m_hits = record->dwHitRate;
	wcstombs(chTemp, record->lpszSourceUrlName, 256);
	entry->m_urlStr = chTemp;
	wcstombs(localPath, record->lpszLocalFileName, 256);
	entry->m_localPath = localPath;
	entry->m_entrySize = record->dwSizeLow;
	memset(chTemp, 0, 256);
	if (record->lpHeaderInfo)
	{
		wcstombs(chTemp, record->lpHeaderInfo, 256);
		entry->m_headerInfo = chTemp;
	}
	else
	{
		entry->m_headerInfo = "None exists";
	}

	ptr = strrchr(localPath, '\\');
	// skip to the next character to copy.
	entry->m_fileName = ptr+1; 

	// set the name of sub folder into which we store the cache file.
	// truncate the path
	*ptr = '\0';  
	ptr = strrchr(localPath, '\\');
	entry->m_subFolder = ptr + 1; 
}

void IECacheInfo::transformTimeFormat(pCacheEntry entry, const LPINTERNET_CACHE_ENTRY_INFO lpCacheEnt)
{
	SYSTEMTIME st;
	FILETIME ft;
	const int TIMEBUFFER = 32;
	char chDateTime[TIMEBUFFER];

	// transform the last access time format.
	memset(chDateTime, 0, TIMEBUFFER);
	FileTimeToLocalFileTime(&lpCacheEnt->LastAccessTime, &ft);
	FileTimeToSystemTime(&ft, &st);
	_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	entry->m_lastAccess = chDateTime;

	// transform the last modified time format
	memset(chDateTime, 0, TIMEBUFFER);
	if (lpCacheEnt->LastModifiedTime.dwHighDateTime != 0 && lpCacheEnt->LastModifiedTime.dwLowDateTime != 0)
	{
		FileTimeToLocalFileTime(&lpCacheEnt->LastModifiedTime, &ft);
		FileTimeToSystemTime(&ft, &st);
		_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		_snprintf(chDateTime, TIMEBUFFER, "N/A");
	}
	entry->m_lastModified = chDateTime;

	// transform the last synchronized time format
	memset(chDateTime, 0, TIMEBUFFER);
	FileTimeToLocalFileTime(&lpCacheEnt->LastSyncTime, &ft);
	FileTimeToSystemTime(&ft, &st);
	_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	entry->m_lastChecked = chDateTime;

	// transform the format of expiration time
	memset(chDateTime, 0, TIMEBUFFER);
	if (lpCacheEnt->ExpireTime.dwHighDateTime != 0 && lpCacheEnt->ExpireTime.dwLowDateTime != 0)
	{
		FileTimeToLocalFileTime(&lpCacheEnt->ExpireTime, &ft);
		FileTimeToSystemTime(&ft, &st);
		_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		_snprintf(chDateTime, TIMEBUFFER, "N/A");
	}
	entry->m_expiration = chDateTime;
}

IECookieInfo::IECookieInfo(void)
{
	// Need to be fixed
	const string fileName = getCookiePath("index.dat");
	// create a kernel file object
	m_hFile = CreateFileA(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_READONLY, NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, fileName.c_str(), fileName.c_str(), MB_OKCANCEL);
		return;
	}

	// create a kernel file mapping object
	m_hMapping = CreateFileMappingA(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (m_hMapping == NULL)
	{
		MessageBoxA(NULL, "Error", "Can't create file mapping object.", MB_OKCANCEL);
		CloseHandle(m_hFile);
		m_hFile = NULL;
		return ;
	}

	m_startAddr = (LPSTR)MapViewOfFile(m_hMapping, FILE_MAP_READ, 0, 0, 0);
	if (m_startAddr == NULL)
	{
		MessageBoxA(NULL, "Error", "Can't mappping the index.dat file.", MB_OKCANCEL);
		CloseHandle(m_hFile);
		m_hFile = NULL;
		CloseHandle(m_hMapping);
		m_hMapping = NULL;
		return;
	}
	initializeEntriesVec();

}
IECookieInfo::~IECookieInfo()
{
	if (m_startAddr) UnmapViewOfFile((PBYTE)m_startAddr);
	if (m_hMapping) CloseHandle(m_hMapping);
	if (m_hFile) CloseHandle(m_hFile);
}

const string IECookieInfo::getCookiePath(const char* appendice)
{
	
	DWORD BUFSIZE = TMPSIZE;
	char windir[TMPSIZE] = {'\0'};
	char paths[TMPSIZE] = {'\0'};
	GetWindowsDirectoryA(windir, TMPSIZE);
	QSysInfo sysinfo;
	char uname[TMPSIZE] = {'\0'};
	GetUserNameA(uname, &BUFSIZE);
	if (QSysInfo::WV_WINDOWS7 == sysinfo.windowsVersion())  // For Windows 7.
	{
		_snprintf(paths, 256, "%c:\\Users\\%s\\AppData\\Roaming\\Microsoft\\Windows\\Cookies\\%s", windir[0], uname, appendice);
	}
	else if (QSysInfo::WV_XP == sysinfo.windowsVersion())  // For Windows XP.
	{
		_snprintf(paths, 256, "%c:\\Documents and Settings\\%s\\Cookies\\%s", windir[0], uname, appendice);
	}
	else // For other Windows versions.
	{
		_snprintf(paths, 256, "Unknown");
	}
	return paths;
}

void IECookieInfo::initializeEntriesVec()
{
	const int PATH_LEN = 256;
	char path_buf[PATH_LEN] = {L'\0'};
	// the flag indicates whether subdirectories exist.
	int isSubDirExist = 0;
	// retrieve the index.dat header
	LPMEMMAP_HEADER_SMALL lpsmallHead = (LPMEMMAP_HEADER_SMALL)m_startAddr;

	// If none hash header exists in this .dat file, simply return.
	if (lpsmallHead->dwHashTableOffset == 0) 
	{
		return ;
	}
	char subdirNames[16][8] = {'\0'};
	// If there exist subdirectories...
	if (lpsmallHead->nDirCount)
	{
		isSubDirExist = 1; 
		// jump to the beginning of the subdir entries.
		LPSTR subdirBeginAddr = (LPSTR)lpsmallHead + 76; 
		int subdirCount = 0;
		while (subdirCount < lpsmallHead->nDirCount)
		{
			subdirBeginAddr += 4; // skip the items count in the subdir, 4 byte 
			strncpy(subdirNames[subdirCount], subdirBeginAddr, 8);
			subdirBeginAddr += 8; // skip the next subdirectory entry.
			subdirCount++;
		}
	}

	LPHASH_ITEM lphashItem = NULL;
	HASH_ITEM hashItem;
	HASH_FILEMAP_ENTRY hashEntry;
	LPIE5_URL_FILEMAP_ENTRY lpie5Record = NULL;
	IE5_URL_FILEMAP_ENTRY ie5Record;
	CookieEntry record;
	int ordNum;
	// get the first hash table.
	LPHASH_FILEMAP_ENTRY lphashHeader = (LPHASH_FILEMAP_ENTRY)(m_startAddr + lpsmallHead->dwHashTableOffset);
	while (lphashHeader)
	{
		ordNum = 1;
		memcpy(&hashEntry, lphashHeader, sizeof(HASH_FILEMAP_ENTRY));
		// iterate through all hash items
		lphashItem = (LPHASH_ITEM)(lphashHeader + 1);
		memcpy(&hashItem, lphashItem, sizeof(HASH_ITEM));
		// Terminated when the URL entry offset is 0xDEADBEEF
		while (ordNum <= (hashEntry.nBlocks*0x80-16)/8 && hashItem.dwOffset != 0xDEADBEEF)
		{
			// skip the holes in the hash section until the end of hash section.
			if (hashItem.dwHash != 0x0 && hashItem.dwHash != 0x3)
			{
				lpie5Record = (LPIE5_URL_FILEMAP_ENTRY)(m_startAddr + hashItem.dwOffset);
				memcpy(&ie5Record, lpie5Record, sizeof(IE5_URL_FILEMAP_ENTRY));
				record.m_lastAccess = transformTimeFormat(ie5Record.LastAccessedTime);
				record.m_lastModified = transformTimeFormat(ie5Record.LastModifiedTime);
				record.m_hits = ie5Record.NumAccessed;
				record.m_cookieSize = ie5Record.dwFileSize;;
				if (isSubDirExist)
				{
					// generate the local path of the cookie file.
					record.m_localPath = getCookiePath(subdirNames[ie5Record.DirIndex]);
				}
				else
				{
					record.m_localPath = getCookiePath("");
				}
				record.m_fileName = string((char*)lpie5Record + lpie5Record->InternalFileNameOffset);
				splitCookieURL((char*)lpie5Record + lpie5Record->UrlNameOffset, record);
				record.m_recordNum = ordNum;

				m_recordsVec.push_back(record);
			}
			lphashItem += 1;  // skip to the next hash item.
			memcpy(&hashItem, lphashItem, sizeof(HASH_ITEM));
			ordNum++;
		}

		lphashHeader = hashEntry.dwNext?(LPHASH_FILEMAP_ENTRY)(m_startAddr + hashEntry.dwNext):NULL;
	}

}

const string IECookieInfo::transformTimeFormat(LONGLONG dtime)
{
	SYSTEMTIME st;
	FILETIME ft;
	FILETIME tmp;
	const int TIMEBUFFER = 32;
	char chDateTime[TIMEBUFFER] = {'\0'};

	memcpy(&tmp, &dtime, sizeof(LONGLONG)); 
	if (tmp.dwHighDateTime == 0 && tmp.dwLowDateTime == 0)
	{
		_snprintf(chDateTime, TIMEBUFFER, "N/A");
	}
	else
	{
		FileTimeToLocalFileTime(&tmp, &ft);
		FileTimeToSystemTime(&ft, &st);
		_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}

	return string(chDateTime);
}

void IECookieInfo::splitCookieURL(char* url, CookieEntry& obj)
{
	char* chPtrStart = NULL;
	char* chPtrEnd = NULL;
	const int BUFSIZE = 128;
	char  tmp[BUFSIZE] = {'\0'};

	chPtrStart = strchr(url, ':');
	chPtrEnd = strchr(url, '@');
	strncpy(tmp, chPtrStart+1, chPtrEnd - chPtrStart - 1);
	obj.m_user = tmp;

	memset(tmp, 0, BUFSIZE);
	chPtrStart = chPtrEnd;
	strncpy(tmp, chPtrStart+1, strlen(chPtrStart+1));
	obj.m_website = tmp;
}

/*
 * Retrieve the list of software installed.
 * Flags: KEY_WOW64_64KEY, KEY_WOW64_32KEY 
 */
void RetrieveHelper::setApplist()
{
	if (determineOSBit())  // the windows is 64bit
	{
		retrieveAppkey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_WOW64_32KEY);
	}
	// KEY_WOW64_64KEY will be ignored by 32bit windows.
	retrieveAppkey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_WOW64_64KEY);
}
/*
 * Retrieve the list of process running
 */
void RetrieveHelper::setProclist()
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;
	ProcEntry entry;
	TCHAR buffer[MAX_PATH];

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
	{
		return;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		CloseHandle( hProcessSnap );          // clean the snapshot object
		return ;
	}

	do
	{
		entry.procName = pe32.szExeFile ;
		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess( PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID );
		if(hProcess)
		{
			dwPriorityClass = GetPriorityClass(hProcess);
		}

		entry.procId =  pe32.th32ProcessID;
		entry.ctThread = pe32.cntThreads;
		entry.procPid = pe32.th32ParentProcessID;
		entry.priorBase = pe32.pcPriClassBase;
		if( dwPriorityClass )
			entry.priorClass = dwPriorityClass; 
		if (hProcess)
		{
			DWORD size = GetModuleFileNameEx(hProcess, NULL, buffer, MAX_PATH);
			if (!size)
			{
				// for compatible with windows 7 64bits.
				if (GetProcessImageFileName(hProcess, buffer, MAX_PATH))
				{
					NormalizeNTPath(buffer, MAX_PATH);
				}
			}
			CloseHandle(hProcess);
		}
		entry.exePath = buffer;
		m_procList.push_back(entry);

	} while( Process32Next( hProcessSnap, &pe32 ) );

	CloseHandle(hProcessSnap);
}

/*
 * To determine whether we are running under Wow64
 * Returns: returns true if process running on Wow64.
 */
BOOL RetrieveHelper::determineOSBit()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	BOOL bIsWow64 = false; // assume 32 bit

	// can't call IsWow64Process on x32, so first look up the entry point in kernel32
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
	// if we have an entry point for IsWow64Process, we can call it
	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			bIsWow64 = FALSE;
		}
	}
	return bIsWow64;
}

/*
 * Enumerate the default registry key.
 * For Windows 32bit and 64bit, the default registry path is:
 *   HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall
 * While running under Windows 64bits, all 32bits applications are registered under:
 *   HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall
 */
void RetrieveHelper::retrieveAppkey(HKEY hKey, LPCTSTR szDesKeyItem, LONG flag)
{
	AppEntry entry;
	HKEY hSubKey;
	DWORD dwIndex = 0;
	long lResult;
	const unsigned int BUFSIZE = 1024;
	TCHAR s_name[256] = {0};				// application name			
	TCHAR buffer[BUFSIZE] = {'\0'};
	DWORD cbName = BUFSIZE*sizeof(TCHAR);	
	DWORD typeSZ = REG_SZ;	
	HKEY hItem;		// next level

	lResult = RegOpenKeyEx(hKey, szDesKeyItem, 0, KEY_READ|flag, &hSubKey);		// Open windows registry
	if(ERROR_SUCCESS == lResult) 
	{
		lResult = RegEnumKeyEx(hSubKey, dwIndex, s_name, &cbName, 0, NULL, NULL, NULL);		// enumerate keys
		while (lResult == ERROR_SUCCESS && lResult != ERROR_MORE_DATA)
		{
			cbName = BUFSIZE*sizeof(TCHAR);  // reset the value
			if(RegOpenKeyEx(hSubKey, s_name, 0, KEY_READ, &hItem) == ERROR_SUCCESS)
			{
				// the display name of application
				lResult = RegQueryValueEx(hItem, TEXT("DisplayName"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
				if (lResult == ERROR_SUCCESS)  // the registry value exist, so we continue
				{
					entry.appName = buffer;
					memset(buffer, 0, BUFSIZE);
					cbName = BUFSIZE*sizeof(TCHAR);
					// the publisher
					lResult = RegQueryValueEx(hItem, TEXT("Publisher"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.publisher = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.publisher = TEXT("/");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// Get the location of installation
					lResult = RegQueryValueEx(hItem, TEXT("InstallLocation"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.location = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.location = TEXT("/");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// installation date
					lResult = RegQueryValueEx(hItem, TEXT("InstallDate"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.installDate = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.installDate = TEXT("N/A");
					}
					cbName = BUFSIZE*sizeof(TCHAR);
					// display version of application
					lResult = RegQueryValueEx(hItem, TEXT("DisplayVersion"), 0, &typeSZ, (LPBYTE)buffer, &cbName);
					if (lResult == ERROR_SUCCESS && buffer[0])
					{
						entry.appVer = buffer;
						memset(buffer, 0, BUFSIZE);
					}
					else
					{
						entry.appVer = TEXT("/");
					}
					m_appList.push_back(entry);
				}
				RegCloseKey(hItem);
			}

			dwIndex = dwIndex + 1;			// move to the next key
			cbName = BUFSIZE*sizeof(TCHAR);
			lResult = RegEnumKeyEx(hSubKey, dwIndex, s_name, &cbName, 0, NULL, NULL, NULL);
		}
		RegCloseKey(hSubKey);
	}
	RegCloseKey(hKey);
}

// Normalizes the path returned by GetProcessImageFileName
bool RetrieveHelper::NormalizeNTPath(wchar_t* pszPath, size_t nMax)
{
	wchar_t* pszSlash = wcschr(&pszPath[1], '\\');
	if (pszSlash) pszSlash = wcschr(pszSlash+1, '\\');
	if (!pszSlash)
		return false;
	wchar_t suffix[MAX_PATH];
	wcscpy_s(suffix, MAX_PATH, pszSlash);
	*pszSlash = 0;

	wchar_t szNTPath[MAX_PATH];
	wchar_t szDrive[MAX_PATH] = TEXT("A:");
	// We'll need to query the NT device names for the drives to find a match with pszPath
	for (wchar_t cDrive = 'A'; cDrive < 'Z'; ++cDrive)
	{
		szDrive[0] = cDrive;
		szNTPath[0] = 0;
		if (0 != QueryDosDevice(szDrive, szNTPath, MAX_PATH) && 0 == _wcsicmp(szNTPath, pszPath))
		{
			// Match
			wcscat_s(szDrive, MAX_PATH, suffix);
			wcscpy_s(pszPath, nMax, szDrive);
			return true;
		}
	}
	return false;
}
