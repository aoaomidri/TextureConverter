#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//�A�v���P�[�V�����̃p�X
		kFilePath,			//�n���ꂽ�t�@�C���̃p�X

		NumArgument
	};

	assert(argc >= NumArgument);

	//COM���C�u�����̏�����
	

	//�e�N�X�`���R���o�[�^
	TextureConverter converter;

	//�e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	system("pause");
	return 0;
}