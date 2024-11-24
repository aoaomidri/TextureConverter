#pragma once
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<assert.h>
#include<Windows.h>
#include<cstdint>
#include<wrl.h>
#include<wincodec.h>
#include <wrl/client.h>  // WIC用のCOMインターフェース管理（必要な場合）
#include <cassert>
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"
#include<fstream>
#include<iostream>
#include<filesystem>

/*画像を変換するコンバーター*/

using namespace DirectX;

class TextureConverter{
public:
	
	/// <summary>
	/// テクスチャをW変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTexture(const std::string& filePath, const int number);
	
private:
	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::wstring& filePath);

	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadDDSTextureFromFile(const std::wstring& filePath);

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

	/// <summary>
	/// PNGテクスチャとしてファイルの書き出し
	/// </summary>
	void SavePNGTextureToFile();

private:
	//画像の情報
	DirectX::TexMetadata metadata_;
	//画像イメージのコンテナ
	DirectX::ScratchImage scrachhImage_;

	std::wstring fileName_ = L"AfterConversion";

	std::wstring dds_ = L"dds";

	//ディレクトリパス
	std::wstring directoryPath_ = L"AfterConversion/";
	//テクスチャ名
	std::wstring texName_;
	//テクスチャ拡張子
	std::wstring texExt_;

	HRESULT hr_;

};

