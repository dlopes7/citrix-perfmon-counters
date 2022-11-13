## Fake Citrix Counters


This project runs a binary that allows you to create fake Citrix counters. 
It is used for development of the Citrix Extension

## Requirements

* Windows SDK

Add the path where the `ctrpp.exe` program is to your Path environment variable, example `C:\Program Files (x86)\Windows Kits\10\bin\10.0.22621.0\x64` 

* Visual Studio

Need to use a visual studio toolchain to avoid headaches

## Registering the counters

Need to run as administrator:

The second parameter is the folder where the `citrix-agent.exe` process is located

```powershell
lodctr /M:citrix.xml $pwd\cmake-build-release
```
