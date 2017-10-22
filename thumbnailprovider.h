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
#pragma once

// DirectXTex
#include <DirectXTex\DirectXTex.h>

class ThumbnailProvider : public IThumbnailProvider, IObjectWithSite, IInitializeWithStream
{
public:
	ThumbnailProvider();
	~ThumbnailProvider();

	//  IUnknown methods
	STDMETHOD(QueryInterface)(REFIID, void**);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();

	//  IInitializeWithSteam methods
	STDMETHOD(Initialize)(IStream*, DWORD);

	//  IThumbnailProvider methods
	STDMETHOD(GetThumbnail)(UINT, HBITMAP*, WTS_ALPHATYPE*);

	//  IObjectWithSite methods
	STDMETHOD(GetSite)(REFIID, void**);
	STDMETHOD(SetSite)(IUnknown*);
	
private:
	LONG m_cRef;
	IUnknown* m_pSite;

	//! Loaded Texture
	DirectX::ScratchImage _image;

	//! Meta-data of the image
	DirectX::TexMetadata _meta;

	//! Indicates that the texture was loaded
	bool _loaded;
};
