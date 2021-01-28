# Hangzhou Metro

### A metro analysis software based on Qt

:man_office_worker:Peiyu Chen

:email:pietychen@sjtu.edu.cn

:book:**P**rinciples-and-**P**ractice-of-Problem-**S**olving 2019 Fall

### Introduction

Hangzhou Metro is an application based on a real-world automated fare collection (AFC) dataset of Hangzhou metro system downloaded from Tianchi Competition. The application aims to gain a better understanding of the underlying passenger flow patterns in cities with overcrowding in metro systems.

### Function

* **Data Filter**: Load data according to selection
* **Traffic Trend**: Plot inflow,outflow and total flow trend of a specific station in a specific time period
* **Routes Recommendation**: Give feasible path suggestions to users  including options of `Shortest Route`,`Least Crowded Route`,`Recommended Route` and `All Routes`.

### Environment Requirements

![](https://img.shields.io/badge/C%2B%2B-11-green)![](https://img.shields.io/badge/Qt-5.9.0-yellowgreen)

**Device Type**: Desktop

**Compiler**: MinGW 5.3.0 32bit for C++

**Debugger**: Qt\Qt5.11\Tools\mingw530_32\bin\gdb.exe

**CMake Configuration:**

```
CMAKECXXCOMPILER:STRING=％
{Compiler:Executable:Cxx}
CMAKECCOMPILER:STRING—%{Compiler:Executable:C}
CMAKEPREFIXPATH:STRlNG=%{Qt:QTINSTALLPREFIX}
QTQMAKEEXECUTABLE:STRING=%{Qt:qmakeExecutable}
```

### Instructions to Run The Codes

**CHANGE THE ABSOLUTE PATH** in `mythread.cpp` *line 11 and 16* to your local dataset storage path.
**CHANGE THE ABSOLUTE PATH** in `mainwindow.cpp` *line 232* to your local `Metro_roadMap csv` file storage path.

### Support

Please contact me by email pietychen@sjtu.edu.cn if there's any question running the project.

### Acknowledgments

Chi Zhang @ Computer Science and Engineering Dept., SJTU.

Haotian Xue @ Computer Science and Engineering Dept., SJTU.
