## Fake Citrix Counters


This project runs a binary that allows you to create fake Citrix counters. 
It is used for development of the Citrix Extension


## Registering the counters

Need to run as administrator:

The second parameter is the folder where the `citrix-agent.exe` process is located

```powershell
lodctr /M:citrix.xml C:\workspace\c\citrix_counters\cmake-build-release
```

## Building

I am using clion, but it can be built with

```powershell
cmake.exe --build C:\workspace\c\citrix_counters\cmake-build-release --target citrix_counters -j 12
```