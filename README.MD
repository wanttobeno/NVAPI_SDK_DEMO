

##### NVAPI SDK (Windows)


https://developer.nvidia.com/gameworksdownload#?search=nvapi


#### NVAPI SDK VERSION

NVAPI R535 07/03/2023

https://developer.nvidia.com/downloads/assets/gameworks/downloads/secure/nvapi-r545/r545-developer.zip


#### Help Docs


[NVAPI_Reference_Developer.chm](./NVAPI_SDK/docs/NVAPI_Reference_Developer.chm)

#### Sample_Code

[Sample_Code](./Sample_Code)

##### GPUMonitor

https://www.codenong.com/cs106902684/

```
NVAPI Version: NVidia Complete Version 1.10
Drive Version: 531.79
GPU Num: 2
GPU  |  GPU Name    |  Frequency
[0]    NVIDIA GeForce RTX 3060     225 MHz

Input The Index of GPU You want to Monitor
0
 2 GPU0 0.00 MB( 0.00% ) P8 17% 48 ℃ 0 r/m
 2 GPU0 0.00 MB( 0.00% ) P8 20% 47 ℃ 0 r/m
 2 GPU0 0.00 MB( 0.00% ) P8 20% 48 ℃ 0 r/m
 2 GPU0 0.00 MB( 0.00% ) P8 18% 47 ℃ 0 r/m
 ...
```


##### CustomTiming


```
//////////////////////////////////////////////////

Number of Displays in the system =  1
Custom Timing to be tried: 1024 X 999 @ 60.00 hz
NvAPI_DISP_TryCustomDisplay().....Success!
NvAPI_DISP_SaveCustomDisplay().....Success!
NvAPI_DISP_RevertCustomDisplayTrial().....Success!
//////////////////////////////////////////////////
```


##### i2c

```
No of displays = 1
Display handles:  00000000DE000001
Total number of GPU's = 2
Testing GPU handle=0000000000000100, Output ID=512, Display no=0, Display handle=00000000DE000001...
- Regular I2C read operation test mode
6E 88 2 0 10 0 0 64 0 63 A3

   The display 0x200 is DDC/CI capable

  Current brightness value = 99 and max brightness value = 100

  Succesfully modified brightness value to 20!
  Pausing for 5 seconds...

  Succesfully restored the brightness value to 99.
  Pausing for 5 more seconds...

- Barco DDC test I2C read operation test mode
  Current brightness value = 99 and max brightness value = 100

  Succesfully modified brightness value to 20!
  Pausing for 5 seconds...

  Succesfully restored the brightness value to 99.
  Pausing for 5 more seconds...


I2C Read/Write brightness test PASSE
```

#### GPU_INFO


```
GPU 0
GPU CoreClock: 285 mHz
GPU MemoryClock: 405 mHz
GPU ProcessorClock: 3435973 mHz
GPU VideoClock: 555 mHz
```




