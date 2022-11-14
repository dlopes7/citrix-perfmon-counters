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

```powershell
lodctr /M:citrix.xml $pwd\cmake-build-release
```

The second parameter is the folder where the `citrix-agent.exe` process is located

## Scripts

The script under `scripts/generate_xml.ps1` can be used on a target machine where you want to copy counters from

Example:

```bash
powershell -f scripts/generate_xml.ps1  Win32_PerfRawData_PerfOS_Processor
```

Will generate a file called `PerfOS.xml` that can be used to register the counters.
This can be specially useful if you are trying to simulate counters for technologies that you can't easily install counters for, like:

* Microsoft Exchange
* Citrix
* Microsoft SQL Server

You can then run the commands:

1. `ctrpp PerfOS.xml -o perf_os.h -rc perf_os.rc`

To generate the header and resource files

And, as administrator:

2.`lodctr /M:PerfOS.xml $pwd\cmake-build-release`

To register the counters