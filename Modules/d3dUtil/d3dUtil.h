//***************************************************************************************
// d3dUtil.h by X_Jun(MKXJun) (C) 2018-2019 All Rights Reserved.
// Licensed under the MIT License.
//
// D3D实用工具集
// Direct3D utility tools.
//***************************************************************************************

#ifndef D3DUTIL_H
#define D3DUTIL_H

#include <d3d11_1.h>			// 已包含Windows.h
#include <DirectXCollision.h>	// 已包含DirectXMath.h
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include <filesystem>
#include <vector>
#include <string>
#include "ScreenGrab.h"
#include "DDSTextureLoader.h"	
#include "WICTextureLoader.h"

//
// 宏相关
//

// 安全COM组件释放宏
#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

//
// 着色器编译相关函数
//

// ------------------------------
// CreateShaderFromFile函数
// ------------------------------
// [In]csoFileNameInOut 编译好的着色器二进制文件(.cso)，若有指定则优先寻找该文件并读取
// [In]hlslFileName     着色器代码，若未找到着色器二进制文件则编译着色器代码
// [In]entryPoint       入口点(指定开始的函数)
// [In]shaderModel      着色器模型，格式为"*s_5_0"，*可以为c,d,g,h,p,v之一
// [Out]ppBlobOut       输出着色器二进制信息
HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut);

//
// 纹理数组相关函数
//

// ------------------------------
// CreateDDSTexture2DArrayFromFile函数
// ------------------------------
// 该函数要求所有的dds纹理的宽高、数据格式、mip等级一致
// [In]d3dDevice			D3D设备
// [In]d3dDeviceContext		D3D设备上下文
// [In]fileNames			dds文件名数组
// [OutOpt]textureArray		输出的纹理数组资源
// [OutOpt]textureArrayView 输出的纹理数组资源视图
// [In]generateMips			是否生成mipmaps
HRESULT CreateDDSTexture2DArrayFromFile(
	ID3D11Device * d3dDevice,
	ID3D11DeviceContext * d3dDeviceContext,
	const std::vector<std::wstring>& fileNames,
	ID3D11Texture2D** textureArray,
	ID3D11ShaderResourceView** textureArrayView,
	bool generateMips = false);

// ------------------------------
// CreateWICTexture2DArrayFromFile函数
// ------------------------------
// 该函数要求所有的dds纹理的宽高、数据格式、mip等级一致
// [In]d3dDevice			D3D设备
// [In]d3dDeviceContext		D3D设备上下文
// [In]fileNames			dds文件名数组
// [OutOpt]textureArray		输出的纹理数组资源
// [OutOpt]textureArrayView 输出的纹理数组资源视图
// [In]generateMips			是否生成mipmaps
HRESULT CreateWICTexture2DArrayFromFile(
	ID3D11Device * d3dDevice,
	ID3D11DeviceContext * d3dDeviceContext,
	const std::vector<std::wstring>& fileNames,
	ID3D11Texture2D** textureArray,
	ID3D11ShaderResourceView** textureArrayView,
	bool generateMips = false);


//
// 纹理立方体相关函数
//


// ------------------------------
// CreateWICTexture2DCubeFromFile函数
// ------------------------------
// 根据给定的一张包含立方体六个面的位图，创建纹理立方体
// 要求纹理宽高比为4:3，且按下面形式布局:
// .  +Y .  .
// -X +Z +X -Z 
// .  -Y .  .
// [In]d3dDevice			D3D设备
// [In]d3dDeviceContext		D3D设备上下文
// [In]cubeMapFileName		位图文件名
// [OutOpt]textureArray		输出的纹理数组资源
// [OutOpt]textureCubeView	输出的纹理立方体资源视图
// [In]generateMips			是否生成mipmaps
HRESULT CreateWICTexture2DCubeFromFile(
	ID3D11Device * d3dDevice,
	ID3D11DeviceContext * d3dDeviceContext,
	const std::wstring& cubeMapFileName,
	ID3D11Texture2D** textureArray,
	ID3D11ShaderResourceView** textureCubeView,
	bool generateMips = false);

// ------------------------------
// CreateWICTexture2DCubeFromFile函数
// ------------------------------
// 根据按D3D11_TEXTURECUBE_FACE索引顺序给定的六张纹理，创建纹理立方体
// 要求位图是同样宽高、数据格式的正方形
// 你也可以给定超过6张的纹理，然后在获取到纹理数组的基础上自行创建更多的资源视图
// [In]d3dDevice			D3D设备
// [In]d3dDeviceContext		D3D设备上下文
// [In]cubeMapFileNames		位图文件名数组
// [OutOpt]textureArray		输出的纹理数组资源
// [OutOpt]textureCubeView	输出的纹理立方体资源视图
// [In]generateMips			是否生成mipmaps
HRESULT CreateWICTexture2DCubeFromFile(
	ID3D11Device * d3dDevice,
	ID3D11DeviceContext * d3dDeviceContext,
	const std::vector<std::wstring>& cubeMapFileNames,
	ID3D11Texture2D** textureArray,
	ID3D11ShaderResourceView** textureCubeView,
	bool generateMips = false);


#endif
