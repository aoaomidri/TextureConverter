#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){
	//�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);
	//DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile();

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){
	//�t�@�C���p�X�����C�h������ɕϊ�
	std::wstring wFilePath = ConvertMultiByteStringtoWideString(filePath);

	//WIC�e�N�X�`���̃��[�h
	hr_ = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scrachhImage_);

	if (FAILED(hr_)) {
		// �G���[���b�Z�[�W�ƃG���[�R�[�h�̏o��
		std::wcerr << L"Failed to load texture. HRESULT: " << std::hex << hr_ << std::endl;
	}
	assert(SUCCEEDED(hr_));

	SeparateFilePath(wFilePath);

}

std::wstring TextureConverter::ConvertMultiByteStringtoWideString(const std::string& mString){
	if (mString.empty()) {
		return std::wstring();
	}

	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, mString.c_str(), -1, nullptr, 0);
	if (sizeNeeded == 0) {
		return std::wstring();
	}
	std::wstring result;
	result.resize(sizeNeeded);
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &result[0], sizeNeeded);
	return result;
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath){
	size_t pos1;
	std::wstring exceptExt;

	//��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	//�������q�b�g
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pos1);

	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	//��؂蕶��'\\'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos){
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶��'/'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	directoryPath_ = L"";
	fileName_ = exceptExt;

}

void TextureConverter::SaveDDSTextureToFile(){
	ScratchImage mipChain;
	//�~�b�v�}�b�v����
	hr_ = GenerateMipMaps(scrachhImage_.GetImages(), scrachhImage_.GetImageCount(), scrachhImage_.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(hr_)){
		//�C���[�W�ƃ��^�f�[�^���A�~�b�v�}�b�v�łŒu��������
		scrachhImage_ = std::move(mipChain);
		metadata_ = scrachhImage_.GetMetadata();
	}

	//���k�`���ɕϊ�
	ScratchImage converted;
	hr_ = Compress(scrachhImage_.GetImages(), scrachhImage_.GetImageCount(), metadata_, 
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL, 1.0f, converted);

	if (SUCCEEDED(hr_)){
		scrachhImage_ = std::move(converted);
		metadata_ = scrachhImage_.GetMetadata();
	}


	//�ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	//�o�̓t�@�C���̐ݒ���s��
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDS�t�@�C���̏����o��
	hr_ = DirectX::SaveToDDSFile(scrachhImage_.GetImages(), scrachhImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(hr_));

}


