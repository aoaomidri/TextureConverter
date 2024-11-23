# 現在のディレクトリ内の *.png ファイルを取得
$files = Get-ChildItem -Filter *.png

# 各ファイルを処理
foreach ($file in $files) {
    Start-Process -FilePath "TextureConverter.exe" -ArgumentList @("$($file.FullName)") -Wait
}

# 処理完了を待機
Pause