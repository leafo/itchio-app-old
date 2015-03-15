rmdir  /S /Q dependencies\Lato\
mkdir dependencies\Lato\
powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.latofonts.com/download/Lato2OFL.zip', 'dependencies\Lato\lato.zip')"