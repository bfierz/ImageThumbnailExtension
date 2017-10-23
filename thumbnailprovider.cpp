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

#include "common.h"
#include "thumbnailprovider.h"

// Windows API
#include <Windows.h>

ThumbnailProvider::ThumbnailProvider()
{
	DllAddRef();
	m_cRef = 1;
	m_pSite = NULL;
}


ThumbnailProvider::~ThumbnailProvider()
{
	if (m_pSite)
	{
		m_pSite->Release();
		m_pSite = NULL;
	}
	DllRelease();
}


STDMETHODIMP ThumbnailProvider::QueryInterface(REFIID riid,
												void** ppvObject)
{
	static const QITAB qit[] = 
	{
		QITABENT(ThumbnailProvider, IInitializeWithStream),
		QITABENT(ThumbnailProvider, IThumbnailProvider),
		QITABENT(ThumbnailProvider, IObjectWithSite),
		{0},
	};
	return QISearch(this, qit, riid, ppvObject);
}


STDMETHODIMP_(ULONG) ThumbnailProvider::AddRef()
{
	LONG cRef = InterlockedIncrement(&m_cRef);
	return (ULONG)cRef;
}


STDMETHODIMP_(ULONG) ThumbnailProvider::Release()
{
	LONG cRef = InterlockedDecrement(&m_cRef);
	if (0 == cRef)
		delete this;
	return (ULONG)cRef;
}

STDMETHODIMP ThumbnailProvider::Initialize(IStream *pstm, 
											DWORD grfMode)
{
	ULONG len;
	STATSTG stat;
	if (pstm->Stat(&stat, STATFLAG_DEFAULT) != S_OK)
		return S_FALSE;

	char * data = new char[stat.cbSize.QuadPart];

	if (pstm->Read(data, stat.cbSize.QuadPart, &len) != S_OK)
		return S_FALSE;
	
	HRESULT hr = DirectX::LoadFromDDSMemory(data, stat.cbSize.QuadPart, 0, &_meta, _image);
	if (FAILED(hr))
		return hr;

	if (_meta.format == DXGI_FORMAT_UNKNOWN)
		return S_FALSE;

	return S_OK;
}


STDMETHODIMP ThumbnailProvider::GetThumbnail(UINT cx, 
											 HBITMAP *phbmp, 
											 WTS_ALPHATYPE *pdwAlpha)
{
	*phbmp = NULL; 
	*pdwAlpha = WTSAT_ARGB;
	
	// Determine the actual size of the thumbnail.
	// Ensures that the aspect ratio matches the one of the original image.
	int width = cx;
	int height = cx;	
	if (_loaded)
	{
		int img_width = _meta.width;
		int img_height = _meta.height;
		
		if (img_width > img_height)
		{
			width = cx;
			height = img_height * ((double)cx / (double)img_width);
		}
		else if (img_width < img_height)
		{
			width = img_width * ((double)cx / (double)img_height);
			height = cx;
		}
	}
	
	DirectX::ScratchImage bitmap;
	if (DirectX::IsCompressed(_meta.format))
		DirectX::Decompress(*_image.GetImage(0, 0, 0), DXGI_FORMAT_B8G8R8A8_UNORM, bitmap);
	else
		DirectX::Convert(*_image.GetImage(0, 0, 0), DXGI_FORMAT_B8G8R8A8_UNORM, DirectX::TEX_FILTER_LINEAR, 0, bitmap);
	
	DirectX::ScratchImage thumbnail;
	DirectX::Resize(*bitmap.GetImage(0, 0, 0), width, height, DirectX::TEX_FILTER_LINEAR, thumbnail);

	*phbmp = CreateBitmap(width, height, 1, 32, thumbnail.GetPixels());
	
	if (*phbmp != nullptr)
		return NOERROR;

	return E_NOTIMPL;
}


STDMETHODIMP ThumbnailProvider::GetSite(REFIID riid, 
										 void** ppvSite)
{
	if (m_pSite)
	{
		return m_pSite->QueryInterface(riid, ppvSite);
	}
	return E_NOINTERFACE;
}


STDMETHODIMP ThumbnailProvider::SetSite(IUnknown* pUnkSite)
{
	if (m_pSite)
	{
		m_pSite->Release();
		m_pSite = NULL;
	}

	m_pSite = pUnkSite;
	if (m_pSite)
	{
		m_pSite->AddRef();
	}
	return S_OK;
}


STDAPI CThumbnailProvider_CreateInstance(REFIID riid, void** ppvObject)
{
	*ppvObject = NULL;

	ThumbnailProvider* ptp = new ThumbnailProvider();
	if (!ptp)
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hr = ptp->QueryInterface(riid, ppvObject);
	ptp->Release();
	return hr;
}
