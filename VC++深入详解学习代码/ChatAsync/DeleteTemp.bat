@echo off&setlocal enabledelayedexpansion
title ATM辅助工具-临时目录及文件删除工具@alex
cls&color 3f
ping/n 1 127.0.0.1>nul
CSCRIPT   DeleteTemp.vbs 
ping/n 2 127.0.0.1>nul
pause
