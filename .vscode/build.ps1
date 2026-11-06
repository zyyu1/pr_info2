# Inkrementeller Build fuer Windows (nur g++, PowerShell).
# Param: Boost-Include-Pfad (optional)
param([string]$BoostRoot = "")
 
$ErrorActionPreference = "Stop"
$out = "build\Debug\outDebug.exe"
New-Item -ItemType Directory -Force -Path "build\Debug" | Out-Null
 
$inc = @()
if ($BoostRoot -ne "") { $inc = @("-I$BoostRoot") }
 
# Neuester Header im aktuellen Ordner (ohne Unterordner)
$newestH = [long]0
foreach ($h in Get-ChildItem -File -Path '*.h','*.hpp' -ErrorAction SilentlyContinue) {
  if ($h.LastWriteTimeUtc.Ticks -gt $newestH) { $newestH = $h.LastWriteTimeUtc.Ticks }
}
 
$objs = @()
foreach ($f in Get-ChildItem -File -Path '*.cpp') {
  $o = "build\Debug\" + $f.BaseName + ".o"
  $objs += $o
 
  $rebuild = $false
  if (-not (Test-Path $o)) {
    $rebuild = $true
  } else {
    $ot = (Get-Item $o).LastWriteTimeUtc.Ticks
    if ($f.LastWriteTimeUtc.Ticks -gt $ot -or $newestH -gt $ot) { $rebuild = $true }
  }
 
  if ($rebuild) {
    Write-Host "Kompiliere $($f.Name)"
    & g++ -std=c++17 -g -Wall -DBOOST_ALL_NO_LIB @inc -c $f.Name -o $o
    if ($LASTEXITCODE -ne 0) { exit 1 }
  }
}
 
Write-Host "Linke $out"
& g++ -std=c++17 -g -o $out @objs -lws2_32
if ($LASTEXITCODE -ne 0) { exit 1 }