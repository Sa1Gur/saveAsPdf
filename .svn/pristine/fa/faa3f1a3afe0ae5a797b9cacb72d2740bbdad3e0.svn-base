@echo off

SubWCRev .\ revision.tmpl main\revision.h

:SYS_DAT
IF EXIST .\sys.dat (
	GOTO HMW_INI
)
COPY /v .\templates\sys.tmpl .\sys.dat
:HMW_INI
IF EXIST .\hmw.ini (
	GOTO EXIT
)
COPY /v .\templates\hmw.tmpl .\hmw.ini
:EXIT