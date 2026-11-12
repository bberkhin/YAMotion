# Сборка MatildaCNC из командной строки / VS Code.
#   .\build.ps1                          Release x64, все проекты решения
#   .\build.ps1 -Config Debug            Debug x64
#   .\build.ps1 -Target gcmc             только gcmc_vc.exe (компилятор + библиотека)
#   .\build.ps1 -Target editor           только MatildaCNC.exe
#   .\build.ps1 -Clean                   пересобрать с нуля
param(
	[ValidateSet('Release', 'Debug')][string]$Config = 'Release',
	[ValidateSet('all', 'editor', 'gcmc')][string]$Target = 'all',
	[switch]$Clean
)

$ErrorActionPreference = 'Stop'

$msbuild = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe'
$flexbison = 'C:\win_flex_bison'
$wx = 'C:\WxWidgets\lib\vc_x64_lib'
$src = Join-Path $PSScriptRoot 'src'

# что нужно для сборки лежит вне репозитория: проверяем до запуска
if (-not (Test-Path $msbuild)) { throw "MSBuild не найден: $msbuild (нужны VS 2022 Build Tools, тулсет v143)" }
if (-not (Test-Path "$flexbison\win_flex.exe")) { throw "win_flex_bison не найден в $flexbison" }
if (-not (Test-Path $wx)) { throw "wxWidgets не собран: нет $wx (см. CLAUDE.md, раздел «Сборка»)" }

# flex/bison запускаются из custom build rules и должны быть в PATH
$env:PATH = "$flexbison;$env:PATH"

# нельзя собрать, пока редактор запущен: exe заблокирован
$running = Get-Process MatildaCNC -ErrorAction SilentlyContinue
if ($running -and $Target -ne 'gcmc') {
	throw 'MatildaCNC.exe запущен. Закройте редактор и повторите сборку.'
}

$common = @("-p:Configuration=$Config", '-p:Platform=x64', '-v:q', '-nologo', '-clp:ErrorsOnly;Summary')

switch ($Target) {
	'all'    { $project = Join-Path $src 'EditorWx.sln';                           $extra = @('-m') }
	'editor' { $project = Join-Path $src 'EditorWx\EditorWx.vcxproj';              $extra = @('-m', "-p:SolutionDir=$src\") }
	'gcmc'   { $project = Join-Path $src 'gcmc_vc\gcmc_vc.vcxproj';                $extra = @() }
}
if ($Clean) { $extra += '-t:Rebuild' }

Write-Host "==> $Target / $Config / x64" -ForegroundColor Cyan
& $msbuild $project @common @extra
if ($LASTEXITCODE -ne 0) {
	Write-Host "СБОРКА НЕ УДАЛАСЬ (код $LASTEXITCODE)" -ForegroundColor Red
	exit $LASTEXITCODE
}

$exe = Join-Path $src "x64\$Config\MatildaCNC.exe"
if ($Target -eq 'gcmc') { $exe = Join-Path $src "gcmc_vc\x64\$Config\gcmc_vc.exe" }
Write-Host "Готово: $exe  ($((Get-Item $exe).LastWriteTime))" -ForegroundColor Green
