param (
    [string]$CHESS_LIB_path
)

if (-not $CHESS_LIB_path) {
    Write-Host "Not enough arguments"
    exit 1
}

[Environment]::SetEnvironmentVariable("CHESS_LIB_PATH", $CHESS_LIB_path, "User")

if (-not [Environment]::GetEnvironmentVariable("CHESS_LIB_PATH", "User")) {
    Write-Host "Failed to set CHESS_LIB_PATH"
    exit 1
}

function Add-Path-User($newPath) {
    $Path = [Environment]::GetEnvironmentVariable("PATH", "User") + [IO.Path]::PathSeparator + $newPath
    [Environment]::SetEnvironmentVariable("Path", $Path, "User")
}

function Add-Path-Machine($newPath) {
    $Path = [Environment]::GetEnvironmentVariable("PATH", "Machine") + [IO.Path]::PathSeparator + $newPath
    [Environment]::SetEnvironmentVariable("Path", $Path, "Machine")
}

Function Set-PathVariable {
    param (
        [string]$AddPath,
        [ValidateSet('Process', 'User', 'Machine')]
        [string]$Scope = 'Process'
    )

    $regexPaths = @()
    if ($PSBoundParameters.Keys -contains 'AddPath') {
        $regexPaths += [regex]::Escape($AddPath)
    }

    $arrPath = [System.Environment]::GetEnvironmentVariable('PATH', $Scope).Split([IO.Path]::PathSeparator)
    foreach ($path in $regexPaths) {
        $arrPath = $arrPath | Where-Object { $_ -notMatch "^$path\\?$" }
    }

    $value = ($arrPath + $addPath).Join([IO.Path]::PathSeparator)
    [System.Environment]::SetEnvironmentVariable('PATH', $value, $Scope)
}

$CHESS_LIB_bin_path = Join-Path -Path $CHESS_LIB_path -ChildPath "bin"
Add-Path-User $CHESS_LIB_bin_path
Add-Path-Machine $CHESS_LIB_bin_path