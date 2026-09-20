# run_tests.ps1 - Generic competitive programming test runner
# Usage: .\run_tests.ps1 <problem_directory>
# Example: .\run_tests.ps1 .\GraphAlgorithms\Counting_Rooms

param(
    [Parameter(Position=0)]
    [string]$ProblemDir = "."
)

$ErrorActionPreference = "Stop"

# Resolve paths
$ProblemDir = Resolve-Path $ProblemDir
$srcFile = Join-Path $ProblemDir "main.cpp"
$exeFile = Join-Path $ProblemDir "main.exe"
$testDir = Join-Path $ProblemDir "tests"

# Validate
if (-not (Test-Path $srcFile)) {
    Write-Host "ERROR: $srcFile not found!" -ForegroundColor Red
    exit 1
}
if (-not (Test-Path $testDir)) {
    Write-Host "ERROR: $testDir not found!" -ForegroundColor Red
    exit 1
}

# Compile
Write-Host "`n=== Compiling $srcFile ===" -ForegroundColor Cyan
g++ -O2 -o $exeFile $srcFile 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation FAILED!" -ForegroundColor Red
    exit 1
}
Write-Host "Compilation OK`n" -ForegroundColor Green

# Find all test cases
$testFiles = Get-ChildItem "$testDir\*.in" | Sort-Object { [int]($_.BaseName) }
$total = $testFiles.Count
$passed = 0
$failed = 0

$tmpOut = Join-Path $ProblemDir "tmp_out.txt"
$tmpErr = Join-Path $ProblemDir "tmp_err.txt"

foreach ($inFile in $testFiles) {
    $testNum = $inFile.BaseName
    $outFile = Join-Path $testDir "$testNum.out"

    if (-not (Test-Path $outFile)) {
        Write-Host "Test $testNum : SKIP (no .out file)" -ForegroundColor Yellow
        continue
    }

    $expected = (Get-Content $outFile -Raw).Trim()

    # Run with timeout (10 seconds)
    $process = Start-Process -FilePath $exeFile -RedirectStandardInput $inFile.FullName `
        -RedirectStandardOutput $tmpOut `
        -RedirectStandardError $tmpErr `
        -NoNewWindow -PassThru

    $finished = $process.WaitForExit(10000)

    if (-not $finished) {
        $process.Kill()
        Write-Host "Test $testNum : TLE (>10s)" -ForegroundColor Red
        $failed++
        continue
    }

    if ($process.ExitCode -ne 0) {
        Write-Host "Test $testNum : RTE (exit code $($process.ExitCode))" -ForegroundColor Red
        $failed++
        continue
    }

    $actual = (Get-Content $tmpOut -Raw).Trim()

    if ($actual -eq $expected) {
        Write-Host "Test $testNum : PASS" -ForegroundColor Green
        $passed++
    } else {
        Write-Host "Test $testNum : FAIL" -ForegroundColor Red
        Write-Host "  Expected: $expected" -ForegroundColor DarkGray
        Write-Host "  Got:      $actual" -ForegroundColor DarkGray
        $failed++
    }
}

# Cleanup
Remove-Item $tmpOut -ErrorAction SilentlyContinue
Remove-Item $tmpErr -ErrorAction SilentlyContinue

# Summary
Write-Host "`n=== Results ===" -ForegroundColor Cyan
Write-Host "Total: $total | Passed: $passed | Failed: $failed" -ForegroundColor $(if ($failed -eq 0) { "Green" } else { "Red" })
