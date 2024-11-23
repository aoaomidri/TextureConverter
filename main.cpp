#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//�A�v���P�[�V�����̃p�X
		kFilePath,			//�n���ꂽ�t�@�C���̃p�X

		NumArgument
	};

	assert(argc >= NumArgument);

	//COM���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));
	//�e�N�X�`���R���o�[�^
	TextureConverter converter;

	//�e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COM���C�u�����̏I��
	CoUninitialize();

	
	return 0;
}