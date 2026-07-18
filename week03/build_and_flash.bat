@echo off
setlocal

echo STEP 1: CLEANING BUILD DIRECTORY

REM Xoa thu muc build neu da ton tai
if exist build (
    echo Deleting existing build folder...
    rmdir /s /q build
)

echo.
echo STEP 2: CONFIGURING PROJECT WITH CMAKE

REM Cau hinh du an bang CMake voi Ninja
cmake -B build -G Ninja
if %ERRORLEVEL% neq 0 (
    echo Configuration failed!
    pause
    exit /b 1
)

echo.
echo STEP 3: COMPILING FIRMWARE WITH NINJA

REM Build du an
cmake --build build
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo STEP 4: FLASHING FIRMWARE TO TARGET MCU

REM Nap firmware vao STM32 va Reset sau khi nap
STM32_Programmer_CLI -c port=SWD -w build/app_firmware.bin 0x08000000 -v -rst
if %ERRORLEVEL% neq 0 (
    echo Flash failed!
    pause
    exit /b 1
)

echo.
echo Build and Flash completed successfully!
pause

endlocal