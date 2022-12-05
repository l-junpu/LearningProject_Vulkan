@echo OFF

@REM [92m is Green, [93m is Yellow, [96m is Cyan, [97m is White (color for echo)
set RootPath=%cd%
set CMakeBuildFolder="%RootPath%\build"


@REM Cloning from git
call :clone_git glfw https://github.com/glfw/glfw.git
call :clone_git_branch imgui https://github.com/ocornut/imgui.git docking
@REM call :clone_git IconsFontAwesome https://github.com/juliettef/IconFontCppHeaders.git
@REM call :clone_git ImTerm https://github.com/Organic-Code/ImTerm.git
@REM call :clone_git spdlog https://github.com/gabime/spdlog.git


@REM Building
echo [96m==============================================================================
echo   Building glfw
echo ==============================================================================[97m
set path_to_glfw="%RootPath%/Dependencies/glfw"
set path_to_build="%RootPath%/Dependencies/glfw_build"
call :rmdir_if_exist %path_to_build%
echo Building "Dependencies/glfw"...
cmake -S %path_to_glfw% -B %path_to_build% -A x64 -T v142
cmake -S . -B build
cmake --build %path_to_build%


@REM Build Entire Project Using CMake
echo [96m==============================================================================
echo   Building CMake Project
echo ==============================================================================[97m
if exist CMakeBuildFolder (del "%RootPath%\build\CMakeCache.txt") else (mkdir build)
cd build
cmake .. -A x64 -T v142


echo [96m==============================================================================
echo   Done
echo ==============================================================================[97m
pause











@REM ===================================================================================
@REM							    	Helper Functions
@REM ===================================================================================

@REM Cloning from git url
@REM %1 is the lib, %2 is the git url
:clone_git
echo [96m==============================================================================
echo   Cloning %1 from main/master branch
echo ==============================================================================[97m
REM Remove the dir if it already exist
call :rmdir_if_exist "Dependencies/%1"
echo Starting to clone...
git clone %2 "Dependencies/%1"
echo.
EXIT /B 0

@REM Cloning from git url with stated branch
@REM %1 is the lib, %2 is the git url, %3 is the branch
:clone_git_branch
echo [96m==============================================================================
echo   Cloning %1 from %3 branch
echo ==============================================================================[97m
REM Remove the dir if it already exist
call :rmdir_if_exist "Dependencies/%1"
echo Starting to clone...
git clone --branch "%3" %2 "Dependencies/%1"
echo.
EXIT /B 0