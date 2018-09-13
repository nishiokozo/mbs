echo off
rm err.txt 2>nul
make 2>err.txt

if %ERRORLEVEL%==0 goto _OK

ed err.txt

goto _FIN

:_OK
start /B main.exe

:_FIN
