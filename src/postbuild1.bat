echo Removing old archive
del ..\..\MatildaCNCx86*.zip
del ..\..\MatildaCNCx64*.zip

set outdir=..\..\MatildaCNC
echo Copy Pakarge to %outdir%
rmdir /Q /S %outdir%
mkdir %outdir%
xcopy ..\release_pack %outdir% /E


echo Start x86 build
echo Removing old executeble
del %outdir%\*.exe
copy Release\MatildaCNC.exe %outdir%
copy Release\gcmc_vc.exe %outdir%

"C:\Program Files\7-Zip\7z.exe" a -r ..\..\MatildaCNCx86_%1.zip %outdir%


echo Start x64 build
echo Removing old executeble
del %outdir%\*.exe

copy x64\Release\MatildaCNC.exe %outdir%
copy x64\Release\gcmc_vc.exe %outdir%

"C:\Program Files\7-Zip\7z.exe" a -r ..\..\MatildaCNCx64_%1.zip %outdir%
