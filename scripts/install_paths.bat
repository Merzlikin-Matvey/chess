@echo off

IF "%~1"=="" (
    echo Not enough arguments
    exit /b 1
)

SET "resource_path=%~1"

FOR /F "tokens=1* delims==" %%A IN ('set') DO (
    IF /I "%%A"=="CHESS_ENGINE_RESOURCE_PATH" (
        SETX %%A ""
    )
)

echo INSTALLING PATH

SETX CHESS_ENGINE_RESOURCE_PATH "%resource_path%"

IF NOT DEFINED CHESS_ENGINE_RESOURCE_PATH (
    echo Failed to set CHESS_ENGINE_RESOURCE_PATH
    exit /b 1
)
