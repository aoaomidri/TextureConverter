#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//アプリケーションのパス
		kFilePath,			//渡されたファイルのパス

		NumArgument
	};

	assert(argc >= NumArgument);

	//COMライブラリの初期化
	

	//テクスチャコンバータ
	TextureConverter converter;

	//テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	system("pause");
	return 0;
}