#include"TextureConverter.h"

int main(int argc, char* argv[]) {
	enum Argument{
		kApplicationPath,	//�A�v���P�[�V�����̃p�X
		kFilePath,			//�n���ꂽ�t�@�C���̃p�X
		kSelectNumber,		//�I�������ԍ�
		NumArgument
	};

	assert(argc >= NumArgument);

	//COM���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	assert(SUCCEEDED(hr));
	IWICImagingFactory* pWICFactory = nullptr;
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
	if (FAILED(hr)) {
		std::wcerr << L"Failed to create WIC Imaging Factory." << std::endl;
		return 0;
	}
	//�e�N�X�`���R���o�[�^
	TextureConverter converter;
	//������int�^�ɕϊ�
	int num = std::stoi(argv[kSelectNumber]);

	std::cout << argv[kFilePath] << "��ϊ����Ă��܂��A���΂炭���҂���������" << std::endl;

	//�e�N�X�`���ϊ�
	converter.ConvertTexture(argv[kFilePath], num);

	//COM���C�u�����̏I��
	CoUninitialize();

	
	return 0;
}