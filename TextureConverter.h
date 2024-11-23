#pragma once
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<assert.h>
#include<Windows.h>
#include<cstdint>
#include<wrl.h>
#include <cassert>
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"
using namespace DirectX;

class TextureConverter{
public:
	

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:
	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadWICTextureFromFile(const std::string& filePath);

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

private:
	//�摜�̏��
	DirectX::TexMetadata metadata_;
	//�摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scrachhImage_;

	//�f�B���N�g���p�X
	std::wstring directoryPath_;
	//�f�B���N�g���p�X
	std::wstring fileName_;
	//�f�B���N�g���p�X
	std::wstring fileExt_;

	HRESULT hr_;

};

