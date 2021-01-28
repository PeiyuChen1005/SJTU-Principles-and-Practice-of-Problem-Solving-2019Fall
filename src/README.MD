#HangZhou Metro
HangZhou Metro is a application based on a  real-world automated fare collection (AFC) dataset of Hangzhou metro system downloaded from Tianchi Competition.The application aims to gain a better understanding of the underlying passenger flow patterns in cities with overcrowding in metro systems.

#Basic Function
Data Filter can load data selectively.
Traffic Trend can plot inflow,outflow and total flow trend of a specific station in a specific time period.
Routes Recommendation can give feasible path suggestions to users  includin options of "Shortest Route","Least Crowded Route","Recommended Route" and "All Routes".

#Elective Analysis
Please check the REPORT.pdf

#Environment Requirements	
Device type:Desktop
Compiler:MinGW 5.3.0 32bit for C++
Debugger:Qt\Qt5.11\Tools\mingw530_32\bin\gdb.exe
CMake:Unconfigured
CMake Configuration:
CMAKECXXCOMPILER:STRING=£¥
{Compiler:Executable:Cxx}
CMAKECCOMPILER:STRING¡ª%{Compiler:Executable:C}
CMAKEPREFIXPATH:STRlNG=%{Qt:QTINSTALLPREFIX}
QTQMAKEEXECUTABLE:STRING=%{Qt:qmakeExecutable}

###PLEASE REFER TO ENVIRONMENT.PNG###

#Instructions to Run The Codes
CHANGE THE ABSOLUTE PATH in mythread.cpp line 11 and 16 to your local dataset storage path.£¨dataset£©
CHANGE THE ABSOLUTE PATH in mainwindow.cpp line 232 to your local Metro_roadMap csv file storage path.£¨metro map£©

#Support
Please contact me by email c872270844@163.com if there's any question running the project.

#License
MIT License

Copyright (c) 2019 Peiyu Chen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.