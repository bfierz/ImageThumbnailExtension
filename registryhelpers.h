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

#include <windows.h>

//
//   FUNCTION: RegisterInprocServer
//
//   PURPOSE: Register the in-process component in the registry.
//
//   PARAMETERS:
//   * pszModule - Path of the module that contains the component
//   * clsid - Class ID of the component
//   * pszFriendlyName - Friendly name
//   * pszThreadModel - Threading model
//
//   NOTE: The function creates the HKCR\CLSID\{<CLSID>} key in the registry.
// 
//   HKCR
//   {
//      NoRemove CLSID
//      {
//          ForceRemove {<CLSID>} = s '<Friendly Name>'
//          {
//              InprocServer32 = s '%MODULE%'
//              {
//                  val ThreadingModel = s '<Thread Model>'
//              }
//          }
//      }
//   }
//
HRESULT RegisterInprocServer(PCWSTR pszModule, const CLSID& clsid, 
    PCWSTR pszFriendlyName, PCWSTR pszThreadModel);


//
//   FUNCTION: UnregisterInprocServer
//
//   PURPOSE: Unegister the in-process component in the registry.
//
//   PARAMETERS:
//   * clsid - Class ID of the component
//
//   NOTE: The function deletes the HKCR\CLSID\{<CLSID>} key in the registry.
//
HRESULT UnregisterInprocServer(const CLSID& clsid);


//
//   FUNCTION: RegisterShellExtThumbnailHandler
//
//   PURPOSE: Register the thumbnail handler.
//
//   PARAMETERS:
//   * pszFileType - The file type that the thumbnail handler is associated 
//     with. For example, '*' means all file types; '.txt' means all .txt 
//     files. The parameter must not be NULL.
//   * clsid - Class ID of the component
//
//   NOTE: The function creates the following key in the registry.
//
//   HKCR
//   {
//      NoRemove <File Type>
//      {
//          NoRemove shellex
//          {
//              {e357fccd-a995-4576-b01f-234630154e96} = s '{<CLSID>}'
//          }
//      }
//   }
//
HRESULT RegisterShellExtThumbnailHandler(PCWSTR pszFileType, const CLSID& clsid);


//
//   FUNCTION: UnregisterShellExtThumbnailHandler
//
//   PURPOSE: Unregister the thumbnail handler.
//
//   PARAMETERS:
//   * pszFileType - The file type that the thumbnail handler is associated 
//     with. For example, '*' means all file types; '.txt' means all .txt 
//     files. The parameter must not be NULL.
//
//   NOTE: The function removes the registry key
//   HKCR\<File Type>\shellex\{e357fccd-a995-4576-b01f-234630154e96}.
//
HRESULT UnregisterShellExtThumbnailHandler(PCWSTR pszFileType);
