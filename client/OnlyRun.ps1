# coding=utf-8
# file: OnlyRun.ps1

$output_file = "client\bin\XPGame-TomAndJerry.exe"


Clear-Host
& "$output_file"
if ($LASTEXITCODE -eq 0) {
    # Finish
    Write-Host ""
    Write-Host "Finish" -ForegroundColor Green
} else {
    Write-Error "RunError: your code return $LASTEXITCODE"
}
