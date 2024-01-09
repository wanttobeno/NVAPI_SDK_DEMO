// GPU_Info.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include"nvapi.h"


#ifdef _M_IX86
#pragma comment(lib,"../../x86/nvapi.lib")
#else
#pragma comment(lib,"../../amd64/nvapi64.lib")
#endif

int main()
{
	NvAPI_Initialize();

	NvAPI_Status status;
	NvPhysicalGpuHandle nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS];
	NvU32 gpuCount;
	status = NvAPI_EnumPhysicalGPUs(nvGPUHandle, &gpuCount);
	if (status != NVAPI_OK) {
		std::cerr << "Failed to enumerate physical GPUs" << std::endl;
		NvAPI_Unload();
		return 1;
	}

	if (gpuCount<1)
	{
		std::cerr << "No found physical GPUs" << std::endl;
		NvAPI_Unload();
		return 1;
	}

	std::thread t1([&]{

		while (gpuCount)
		{
			for (int i = 0; i < gpuCount; i++)
			{
				std::cout << "\nGPU " << i << std::endl;
				NV_GPU_CLOCK_FREQUENCIES_V2 clkFreq = { 0 };
				clkFreq.ClockType = NV_GPU_CLOCK_FREQUENCIES_CURRENT_FREQ;
				clkFreq.version = NV_GPU_CLOCK_FREQUENCIES_VER;
				status = status = NvAPI_GPU_GetAllClockFrequencies(nvGPUHandle[0], &clkFreq);
				if (status != NVAPI_OK) {
					std::cerr << "Failed to lock the voltage level" << std::endl;
					NvAPI_Unload();
					return 1;
				}
				auto coreClock = clkFreq.domain[NVAPI_GPU_PUBLIC_CLOCK_GRAPHICS].frequency / 1000;
				std::cout << "GPU CoreClock: " << coreClock << " mHz" << std::endl;
				auto memoryClock = clkFreq.domain[NVAPI_GPU_PUBLIC_CLOCK_MEMORY].frequency / 1000;
				std::cout << "GPU MemoryClock: " << memoryClock << " mHz" << std::endl;
				auto processorClock = clkFreq.domain[NVAPI_MAX_GPU_PUBLIC_CLOCKS].frequency / 1000;
				std::cout << "GPU ProcessorClock: " << processorClock << " mHz" << std::endl;
				auto videoClock = clkFreq.domain[NVAPI_GPU_PUBLIC_CLOCK_VIDEO].frequency / 1000;
				std::cout << "GPU VideoClock: " << videoClock << " mHz" << std::endl;
			}
			std::cout.flush();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			system("cls");
		}
	});

	t1.join();

	NvAPI_Unload();
}

