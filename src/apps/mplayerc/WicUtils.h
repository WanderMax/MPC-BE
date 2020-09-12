/*
 * (C) 2020 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <wincodec.h>

class CWICImagingFactory
{
// http://www.nuonsoft.com/blog/2011/10/17/introduction-to-wic-how-to-use-wic-to-load-an-image-and-draw-it-with-gdi/
public:
	inline static CWICImagingFactory& GetInstance()
	{
		if (nullptr == m_pInstance.get())
			m_pInstance.reset(new CWICImagingFactory());
		return *m_pInstance;
	}

	virtual IWICImagingFactory* GetFactory() const;

protected:
	CComPtr<IWICImagingFactory> m_pWICImagingFactory;

private:
	CWICImagingFactory();   // Private because singleton
	static std::unique_ptr<CWICImagingFactory> m_pInstance;
};

struct WICCodecInfo_t {
	GUID containerFormat;
	std::wstring name;
	std::wstring fileExts;
	std::vector<WICPixelFormatGUID> pixelFmts;
};

HRESULT WicGetCodecs(std::vector<WICCodecInfo_t>& codecs, bool bEncoder);

HRESULT WicOpenImage(HBITMAP& hBitmap, const std::wstring_view& filename);

HRESULT WicSaveImage(
	BYTE* src, const UINT pitch,
	const UINT width, const UINT height,
	const WICPixelFormatGUID pixelFormat,
	const int quality, // for JPEG
	const std::wstring_view& filename,
	WICInProcPointer output, size_t& outLen
);