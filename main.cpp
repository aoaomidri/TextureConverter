#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//アプリケーションのパス
		kFilePath,			//渡されたファイルのパス

		NumArgument
	};

	assert(argc >= NumArgument);

	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));
	//テクスチャコンバータ
	TextureConverter converter;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COMライブラリの終了
	CoUninitialize();

	
	return 0;
}