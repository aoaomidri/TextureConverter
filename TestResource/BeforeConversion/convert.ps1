# ���݂̃f�B���N�g������ *.png �t�@�C�����擾
$files = Get-ChildItem -Filter *.png

# �e�t�@�C��������
foreach ($file in $files) {
    Start-Process -FilePath "TextureConverter.exe" -ArgumentList @("$($file.FullName)") -Wait
}

# ����������ҋ@
Pause