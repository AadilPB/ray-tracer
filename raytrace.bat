@echo off
if "%1"=="" (
    build\ray-tracer.exe
) else if "%1"=="11" (
    build\ray-tracer.exe 11 "scenes\%2.json"
) else (
    build\ray-tracer.exe %*
)

