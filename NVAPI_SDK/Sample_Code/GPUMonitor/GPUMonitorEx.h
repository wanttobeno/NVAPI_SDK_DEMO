#pragma once
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <tchar.h>
#include "nvapi.h"

#define NVAPI_MAX_PHYSICAL_GPUS   64

struct GPUState
{
	int iTemperature;
	int iTachometer;
	int iGPUUsage;
	int iPerfstate;
	GPUState()
		:iTemperature(0)
		, iTachometer(0)
		, iGPUUsage(0)
		, iPerfstate(0)
	{

	}
};

struct MemInfo
{
	float fFreeMemory;
	float fTotalMemory;
	float fMemUsage;
	MemInfo()
		:fFreeMemory(0)
		, fTotalMemory(0)
		, fMemUsage(0.0f)
	{

	}
};


class GPUMonitorEx
{
public:
	GPUMonitorEx(void);
	~GPUMonitorEx(void);
	bool GPUInit();
	void getGPUInfo();
private:
	int getClockFreq(NvPhysicalGpuHandle gpuHandle);                    //GPU Frequency     MHz

	GPUState getDeviceState(NvPhysicalGpuHandle gpuHandle, int iDeviceID);

	MemInfo getDeviceMemory(NvPhysicalGpuHandle gpuHandle);

	void getDeviceProfile();

	void setDeviceProfileSetting(NvDRSSessionHandle hSession, NvDRSProfileHandle hProfile);
private:
	int                 m_iDeviceID;
	NvPhysicalGpuHandle m_gpuHandle;
	std::string         m_slogDir;
	HINSTANCE  NvApiLibrary = NULL;
};