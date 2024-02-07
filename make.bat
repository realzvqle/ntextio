@echo off


cl src\*.c /Fentext.exe /link user32.lib
del *.obj
ntext.exe