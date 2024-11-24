#pragma once
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<assert.h>
#include<Windows.h>
#include<cstdint>
#include<wrl.h>
#include<wincodec.h>
#include <wrl/client.h>  // WIC�p��COM�C���^�[�t�F�[�X�Ǘ��i�K�v�ȏꍇ�j
#include <cassert>
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"
#include<fstream>
#include<iostream>
#include<filesystem>

/*�摜��ϊ�����R���o�[�^�[*/

using namespace DirectX;

class TextureConverter{
public:
	
	/// <summary>
	/// �e�N�X�`����W�ϊ�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void ConvertTexture(const std::string& filePath, const int number);
	
private:
	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadWICTextureFromFile(const std::wstring& filePath);

	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadDDSTextureFromFile(const std::wstring& filePath);

	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�
	/// </summary>
	/// <param name="mString">�}���`�o�C�g������</param>
	/// <returns>���C�h������</returns>
	static std::wstring ConvertMultiByteStringtoWideString(const std::string& mString);

	/// <summary>
	/// �t�H���_�ƃp�X�ƃt�@�C�����𕪗�����
	/// </summary>
	/// <param name="filePath"></param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <summary>
	/// DDS�e�N�X�`���Ƃ��ăt�@�C���̏����o��
	/// </summary>
	void SaveDDSTextureToFile();

	/// <summary>
	/// PNG�e�N�X�`���Ƃ��ăt�@�C���̏����o��
	/// </summary>
	void SavePNGTextureToFile();

private:
	//�摜�̏��
	DirectX::TexMetadata metadata_;
	//�摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scrachhImage_;

	std::wstring fileName_ = L"AfterConversion";

	std::wstring dds_ = L"dds";

	//�f�B���N�g���p�X
	std::wstring directoryPath_ = L"AfterConversion/";
	//�e�N�X�`����
	std::wstring texName_;
	//�e�N�X�`���g���q
	std::wstring texExt_;

	HRESULT hr_;

};

