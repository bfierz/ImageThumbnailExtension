
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

#define INITGUID
#include "common.h"
#include "classfactory.h"


STDAPI CThumbnailProvider_CreateInstance(REFIID riid, void** ppvObject);

ClassFactory::ClassFactory()
{
    _ref = 1;
    DllAddRef();
}


ClassFactory::~ClassFactory()
{
    DllRelease();
}


STDMETHODIMP ClassFactory::QueryInterface(REFIID riid, void** ppvObject)
{
    static const QITAB qit[] = 
    {
        QITABENT(ClassFactory, IClassFactory),
        {0},
    };
    return QISearch(this, qit, riid, ppvObject);
}


STDMETHODIMP_(ULONG) ClassFactory::AddRef()
{
    LONG cRef = InterlockedIncrement(&_ref);
    return (ULONG)cRef;
}


STDMETHODIMP_(ULONG) ClassFactory::Release()
{
    LONG cRef = InterlockedDecrement(&_ref);
    if (0 == cRef)
        delete this;
    return (ULONG)cRef;
}


STDMETHODIMP ClassFactory::CreateInstance(IUnknown* punkOuter,
                                           REFIID riid,
                                           void** ppvObject)
{
    if (NULL != punkOuter)
        return CLASS_E_NOAGGREGATION;

    return CThumbnailProvider_CreateInstance(riid, ppvObject);
}


STDMETHODIMP ClassFactory::LockServer(BOOL fLock)
{
    return E_NOTIMPL;
}
