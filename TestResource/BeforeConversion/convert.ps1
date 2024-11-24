$OutputEncoding = [System.Text.Encoding]::UTF8
# ユーザーに数字の入力を求める
 Write-Host "※現在dds->pngの機能は実装されていないためスキップされますご了承ください"
do {
    # 入力を促す
    $input = Read-Host "同階層のテクスチャを.ddsに変換したい場合は0、.pngに変換したい場合は1を入力してください"

    # 入力が 0 または 1 かを確認
    if ($input -eq "0" -or $input -eq "1") {
        [int]$validInput = $input
        break
    } else {
        Write-Host "０か1を入力してください." -ForegroundColor Red
    }
} while ($true)

if ($validInput -eq 0) {
    Write-Host "0が入力されました。"
    # 現在のディレクトリ内の *.png ファイルを取得
    $files =Get-ChildItem -Path . | Where-Object { $_.Extension -match "\.png$|\.jpg$|\.tga$|\.bmp$|\.jpeg$|\.exr$|\.ktx$|\.pvr$|\.hdr$" }
} elseif ($validInput -eq 1) {
    Write-Host "1が入力されました。"
   # 現在のディレクトリ内の png以外のファイルを取得
   $files = Get-ChildItem -Path . | Where-Object { $_.Extension -match "\.jpg$|\.tga$|\.bmp$|\.jpeg$|\.exr$|\.ktx$|\.pvr$|\.hdr$" }
}

# 各ファイルを処理
foreach ($file in $files) {
    Start-Process -FilePath "TextureConverter.exe" -ArgumentList @("$($file.FullName)","$validInput") -Wait
}

# 処理完了を待機
Pause