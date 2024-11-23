#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){
	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);
	//DDS形式に変換して書き出す
	SaveDDSTextureToFile();

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){
	//ファイルパスをワイド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringtoWideString(filePath);

	//WICテクスチャのロード
	hr_ = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &matedata_, scrachhImage_);

	if (FAILED(hr_)) {
		// エラーメッセージとエラーコードの出力
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

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//検索がヒット
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pos1);

	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos){
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字'/'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	directoryPath_ = L"";
	fileName_ = exceptExt;

}

void TextureConverter::SaveDDSTextureToFile(){
	matedata_.format = DirectX::MakeSRGB(matedata_.format);

	//出力ファイルの設定を行う
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDSファイルの書き出し
	hr_ = DirectX::SaveToDDSFile(scrachhImage_.GetImages(), scrachhImage_.GetImageCount(), matedata_, DirectX::DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(hr_));

}


