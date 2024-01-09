

##### NVAPI SDK (Windows)


https://developer.nvidia.com/gameworksdownload#?search=nvapi


#### NVAPI SDK VERSION

NVAPI R535 07/03/2023

https://developer.nvidia.com/downloads/assets/gameworks/downloads/secure/nvapi-r545/r545-developer.zip


#### Help Docs


[NVAPI_Reference_Developer.chm](./NVAPI_SDK/docs/NVAPI_Reference_Developer.chm)




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




