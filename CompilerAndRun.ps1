# coding=utf-8
# file: CompilerAndRun.ps1

$source_file = "source\main.cpp"
$output_file = "bin\XPGame-TomAndJerry.exe"
$compiler = "g++.exe"
$flags = @("-Wall",
           "-g",
           "-O2",
           "-std=c++17",
           "-finput-charset=UTF-8",
           "-static",
           "-static-libgcc",
           "-static-libstdc++")


# Compile
& "$compiler" "$source_file" $flags -o "$output_file"

if ($LASTEXITCODE -eq 0) {
    #$Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown") | Out-Null
    # Run
    Clear-Host
    & "$output_file"
    if ($LASTEXITCODE -eq 0) {
        # Finish
        Write-Host ""
        Write-Host "Finish" -ForegroundColor Green
    } else {
        Write-Error "RunError: your code return $LASTEXITCODE"
    }
} else {
    # CE
    Write-Error "CompileError: compiler return $LASTEXITCODE"
}
