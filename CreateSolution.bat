rem DEL /S *.sln
rem DEL /S *.vcxproj
rem DEL /S *.vcxproj.filters
rem DEL /S *.vcxproj.user
rem DEL /q .vs
rmdir /q /s build

CALL vendor\premake\premake5.exe vs2022

pause