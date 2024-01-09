#include "GPUMonitorEx.h"

GPUMonitorEx::GPUMonitorEx(void)
	:m_iDeviceID(0)
	, m_gpuHandle(NULL)
{
	m_slogDir = ".\\GPUInfo\\";
	if (-1 == _access(m_slogDir.c_str(), 0))
	{
		_mkdir(m_slogDir.c_str());
	}
}

GPUMonitorEx::~GPUMonitorEx(void)
{}

bool GPUMonitorEx::GPUInit()
{
	NvAPI_ShortString               gpuversion;
	NvU32                           driveVersion;
	NvAPI_ShortString               driveBranch;
	NvU32   gpuCount = 0;
	NvAPI_Status ret = NVAPI_OK;
	NvPhysicalGpuHandle gpuHandles[NVAPI_MAX_PHYSICAL_GPUS];
	NvDisplayHandle hDisplay_a[NVAPI_MAX_PHYSICAL_GPUS * 2] = { 0 };
	NvAPI_Initialize();
	NvAPI_EnumPhysicalGPUs(gpuHandles, &gpuCount);
	if (gpuCount <= 0)
	{
		printf("There is No GPU");
		return false;
	}
	NvAPI_GetInterfaceVersionString(gpuversion);
	NvAPI_SYS_GetDriverAndBranchVersion(&driveVersion, driveBranch);
	printf("NVAPI Version: %s\n", gpuversion);
	printf("Drive Version: %.2f\n", driveVersion / 100.0f);
	printf("GPU Num: %d\n", gpuCount);
	printf("GPU  |  GPU Name    |  Frequency\n");
	for (int i = 0; i < (int)gpuCount; ++i)
	{
		NvAPI_ShortString gpuName = "";
		ret = NvAPI_GPU_GetFullName(gpuHandles[i], gpuName);
		NvU32 frequency = getClockFreq(gpuHandles[i]);
		printf("[%d]    %s     %d MHz\n", i, gpuName, frequency);
	}
	//NvAPI_EnumPhysicalGPUs(&m_gpuInfo.gpuHandle, &m_gpuInfo.gpuNum);
	//getDeviceProfile(); //profile info


	std::cout << "\nInput The Index of GPU You want to Monitor \n";
	int gpuID = 0;
	std::cin >> gpuID;
	std::cin.get();
	if (!gpuID)
	{
		m_iDeviceID = 0;
	}
	else
	{
		m_iDeviceID = gpuID;
	}
	m_gpuHandle = gpuHandles[m_iDeviceID];
	NV_GPU_GET_HDCP_SUPPORT_STATUS HDCPSupportStatus;
	HDCPSupportStatus.version = NV_GPU_GET_HDCP_SUPPORT_STATUS_VER;
	NvAPI_GPU_GetHDCPSupportStatus(m_gpuHandle, &HDCPSupportStatus);
	if (!ret == NVAPI_OK) {
		NvAPI_ShortString string;
		NvAPI_GetErrorMessage(ret, string);
		printf("NVAPI NvAPI_GPU_GetFullName: %s\n", string);
		return false;
	}

	return true;
}


void GPUMonitorEx::getGPUInfo()
{
	TCHAR strTime[80];
	SYSTEMTIME Time = { 0 };
	char sFileName[80];
	::GetLocalTime(&Time);

	time_t time1 = time(0);
	std::string logFile = m_slogDir + std::to_string((long long)time1) + ".log";

	std::ofstream slogFile(logFile, std::ios::binary | std::ios::beg);


	for (int i = 0; i < 10000; ++i)
	{
		::GetLocalTime(&Time);
		wsprintf(strTime, _T("%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u"), Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond, Time.wMilliseconds);
		GPUState gpuState = getDeviceState(m_gpuHandle, m_iDeviceID);
		MemInfo memInfo = getDeviceMemory(m_gpuHandle);
		Sleep(100);
		printf(" %s GPU%d %.2f MB( %.2f%% ) P%d %d%% %d ¡æ %d r/m \n", strTime, m_iDeviceID, memInfo.fTotalMemory - memInfo.fFreeMemory, memInfo.fMemUsage, gpuState.iPerfstate, gpuState.iGPUUsage, gpuState.iTemperature, gpuState.iTachometer);
		slogFile << strTime << "GPU[" << m_iDeviceID << "] " << std::to_string((long double)(memInfo.fTotalMemory - memInfo.fFreeMemory)) << "( " << std::to_string((long double)memInfo.fMemUsage)
			<< ") P" << std::to_string((long long)gpuState.iPerfstate) << "  " << std::to_string((long double)gpuState.iGPUUsage) << "% " << std::to_string((long long)gpuState.iTemperature) << " ¡æ "
			<< std::to_string((long long)gpuState.iTachometer) << " r/m \n";
		slogFile.flush();
	}
	slogFile.close();
}

void GPUMonitorEx::getDeviceProfile()
{
	NvAPI_Status status = NvAPI_Initialize();
	NvDRSSessionHandle hSession = 0;
	status = NvAPI_DRS_CreateSession(&hSession);
	status = NvAPI_DRS_LoadSettings(hSession);
	NvDRSProfileHandle hProfile = 0;
	unsigned int index = 0;
	status = NvAPI_DRS_GetBaseProfile(hSession, &hProfile);
	while (NVAPI_OK == status)
	{

		printf("profile in position %d:\n", index);

		NVDRS_PROFILE ProfileInfo = { 0 };
		ProfileInfo.version = NVDRS_PROFILE_VER;
		status = NvAPI_DRS_GetProfileInfo(hSession, hProfile, &ProfileInfo);
		if (status != NVAPI_OK) { return; }
		wprintf(L"profile Name: %s\n", ProfileInfo.profileName);
		printf("number of Applications associated with the Profile: %d\n", ProfileInfo.numOfApps);
		printf("number of Settings associated with the Profile: %d\n", ProfileInfo.numOfSettings);
		printf("is Predefined: %d\n", ProfileInfo.isPredefined);
		if (ProfileInfo.numOfApps)
		{
			NVDRS_APPLICATION *arrayApp = new NVDRS_APPLICATION[ProfileInfo.numOfApps];
			NvU32 AppNum = ProfileInfo.numOfApps;
			NvU32 startIndex = 0;
			arrayApp[0].version = NVDRS_APPLICATION_VER;
			status = NvAPI_DRS_EnumApplications(hSession, hProfile, startIndex, &AppNum, arrayApp);
			for (int i = 0; i < AppNum; i++)
			{
				wprintf(L"Executable: %s\n", arrayApp[i].appName);
				wprintf(L"User Friendly Name: %s\n",
					arrayApp[i].userFriendlyName);
				printf("Is Predefined: %d\n", arrayApp[i].isPredefined);
			}
			delete[] arrayApp;
		}
		index++;
		status = NvAPI_DRS_EnumProfiles(hSession, index, &hProfile);
	}
	status = NvAPI_DRS_DestroySession(hSession);
	hSession = 0;
}

void GPUMonitorEx::setDeviceProfileSetting(NvDRSSessionHandle hSession, NvDRSProfileHandle hProfile)
{
	NvAPI_Status status = NvAPI_Initialize();
	NVDRS_SETTING drsSetting = { 0 };
	drsSetting.version = NVDRS_SETTING_VER;
	drsSetting.settingId = 0;
	drsSetting.settingType = NVDRS_DWORD_TYPE;
	drsSetting.u32CurrentValue = 0;
	status = NvAPI_DRS_SetSetting(hSession, hProfile, &drsSetting);
	//status = NvAPI_DRS_SaveSettings(hSession);
	//NvAPI_UnicodeString fileName;
	//memcpy_s(fileName, sizeof(fileName), L"D:\\1.txt", 10*sizeof(wchar_t));
	//status = NvAPI_DRS_SaveSettingsToFile(hSession, fileName);
}

int GPUMonitorEx::getClockFreq(NvPhysicalGpuHandle gpuHandle)
{
	NV_GPU_CLOCK_FREQUENCIES table = { 0 };
	table.version = NV_GPU_CLOCK_FREQUENCIES_VER;
	table.ClockType = NV_GPU_CLOCK_FREQUENCIES_CURRENT_FREQ;
	NvAPI_GPU_GetAllClockFrequencies(gpuHandle, &table);
	NvU32 GraphicsClockInKhz = table.domain[NVAPI_GPU_PUBLIC_CLOCK_GRAPHICS].frequency;
	int nFrequency = int((GraphicsClockInKhz + 500) / 1000);
	return nFrequency;
}

GPUState GPUMonitorEx::getDeviceState(NvPhysicalGpuHandle gpuHandle, int iDeviceID)
{
	GPUState gpuStats;
	NV_GPU_THERMAL_SETTINGS thermal = { 0 };
	thermal.version = NV_GPU_THERMAL_SETTINGS_VER;
	NvAPI_GPU_GetThermalSettings(gpuHandle, 0, &thermal);
	gpuStats.iTemperature = static_cast<unsigned>(thermal.sensor[iDeviceID].currentTemp);

	NvU32 tachometer = 0;
	NvAPI_GPU_GetTachReading(gpuHandle, &tachometer);
	gpuStats.iTachometer = tachometer;

	NV_GPU_DYNAMIC_PSTATES_INFO_EX infoEx;
	infoEx.version = NV_GPU_DYNAMIC_PSTATES_INFO_EX_VER;
	NvAPI_GPU_GetDynamicPstatesInfoEx(gpuHandle, &infoEx);
	gpuStats.iGPUUsage = infoEx.utilization[iDeviceID].percentage;

	NV_GPU_PERF_PSTATE_ID CurrentPstate;
	NvAPI_GPU_GetCurrentPstate(gpuHandle, &CurrentPstate);
	gpuStats.iPerfstate = static_cast<int>(CurrentPstate);
	return gpuStats;
}

MemInfo GPUMonitorEx::getDeviceMemory(NvPhysicalGpuHandle gpuHandle)
{
	MemInfo memInfo;
	NV_GPU_MEMORY_INFO_EX pMemoryInfo;
	pMemoryInfo.version = NV_DISPLAY_DRIVER_MEMORY_INFO_VER;
	NvAPI_Status ret = NvAPI_GPU_GetMemoryInfoEx(gpuHandle, &pMemoryInfo);
	memInfo.fTotalMemory = pMemoryInfo.dedicatedVideoMemory / 1024.0f;
	memInfo.fFreeMemory = pMemoryInfo.curAvailableDedicatedVideoMemory / 1024.0f;
	memInfo.fMemUsage = (memInfo.fTotalMemory - memInfo.fFreeMemory) / memInfo.fTotalMemory*100.0f;
	return memInfo;
}