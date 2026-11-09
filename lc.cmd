@echo off
rem Runs lc.py from the repo root, wherever you call it from.
where py >nul 2>nul
if %errorlevel%==0 (
    py -3 "%~dp0lc.py" %*
) else (
    python "%~dp0lc.py" %*
)
