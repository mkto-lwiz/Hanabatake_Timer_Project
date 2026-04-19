# Force UTF-8 for this session

[Console]::InputEncoding  = [System.Text.Encoding]::UTF8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# Also set code page

chcp 65001 > $null

# Run your program

& "$PSScriptRoot\Hanabatake.exe" $args
