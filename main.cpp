#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//アプリケーションのパス
		kFilePath,			//渡されたファイルのパス
		kSelectNumber,		//選択した番号
		NumArgument
	};

	assert(argc >= NumArgument);

	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	assert(SUCCEEDED(hr));
	IWICImagingFactory* pWICFactory = nullptr;
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
	if (FAILED(hr)) {
		std::wcerr << L"Failed to create WIC Imaging Factory." << std::endl;
		return 0;
	}
	//テクスチャコンバータ
	TextureConverter converter;
	//文字をint型に変換
	int num = std::stoi(argv[kSelectNumber]);

	std::cout << argv[kFilePath] << "を変換しています、しばらくお待ちください" << std::endl;

	//テクスチャ変換
	converter.ConvertTexture(argv[kFilePath], num);

	//COMライブラリの終了
	CoUninitialize();

	
	return 0;
}