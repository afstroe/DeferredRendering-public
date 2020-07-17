set CRT_DIR=%cd%
set LIBS_INC="%CRT_DIR%\glfw\inc"
set LIBS_DIR=%CRT_DIR%\glfw\lib
set PATH=%PATH%;%LIBS_DIR%
start "Visual Studio" "devenv.exe" "%CRT_DIR%\DeferredRenderer.sln"
exit