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
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:
	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::string& filePath);

	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	/// <param name="mString">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring ConvertMultiByteStringtoWideString(const std::string& mString);

	/// <summary>
	/// フォルダとパスとファイル名を分離する
	/// </summary>
	/// <param name="filePath"></param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <summary>
	/// DDSテクスチャとしてファイルの書き出し
	/// </summary>
	void SaveDDSTextureToFile();

private:
	//画像の情報
	DirectX::TexMetadata metadata_;
	//画像イメージのコンテナ
	DirectX::ScratchImage scrachhImage_;

	//ディレクトリパス
	std::wstring directoryPath_;
	//ディレクトリパス
	std::wstring fileName_;
	//ディレクトリパス
	std::wstring fileExt_;

	HRESULT hr_;

};

