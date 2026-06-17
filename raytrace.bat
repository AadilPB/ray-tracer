@echo off
set "USER_INPUT=%~1"

if exist "%USER_INPUT%" (
    set "FINAL_PATH=%USER_INPUT%"
    echo [INFO] Rendering: %FINAL_PATH%
) else (
    set "FINAL_PATH=scenes\%~n1.json"
    echo [INFO] Rendering from scenes folder: %FINAL_PATH%
)

build\ray-tracer.exe "%FINAL_PATH%" %2




