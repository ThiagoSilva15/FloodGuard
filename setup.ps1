<#
    setup.ps1
    Gera a estrutura de pastas para o projeto FloodGuard IoT
#>

# Permite sobrescrever itens já existentes
$force = $true

# 1. Pastas principais
$dirs = @(
    ".github",
    "docs",
    "src\backend",
    "src\frontend",
    "src\models",
    "hardware\firmware\src",
    "data\public",
    "data\synthetic"
)

foreach ($d in $dirs) {
    New-Item -ItemType Directory -Path $d -Force:$force | Out-Null
}

# 2. Arquivos-base
$files = @(
    "README.md",
    "docs\CP02_GOV.pdf",
    "hardware\schematics.pdf",
    "hardware\firmware\src\main.cpp",
    "data\synthetic\flood_synthetic.csv"
)

foreach ($f in $files) {
    New-Item -ItemType File -Path $f -Force:$force | Out-Null
}

Write-Host "Estrutura de pastas e arquivos criada com sucesso!"
