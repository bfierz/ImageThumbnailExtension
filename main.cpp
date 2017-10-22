/*
 * This file is part of the Visual Computing Library (VCL) release under the
 * MIT license.
 *
 * Copyright (c) 2017 Basil Fierz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Windows API
#include <Objbase.h>
#include <Wincodec.h>

// DirectXTex
#include "DirectXTex\DirectXTex.h"

int wmain(int argc, wchar_t* argv[])
{
	if (argc != 2)
		return -1;

	CoInitialize(nullptr);

	DirectX::TexMetadata meta;
	DirectX::ScratchImage img, img2;
	DirectX::LoadFromDDSFile(argv[1], 0, &meta, img);

	if (DirectX::IsCompressed(meta.format))
		DirectX::Decompress(*img.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM, img2);
	else
		DirectX::Convert(*img.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0, img2);

	DirectX::SaveToWICFile(*img2.GetImage(0, 0, 0), 0, GUID_ContainerFormatBmp, L"test.bmp");

	return 0;
}
