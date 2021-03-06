#pragma once
// Definition: relative pixel = 1 pixel at 96 DPI and scaled based on actual DPI.
class CDPI
{
public:
	CDPI() : _fInitialized(false), m_dpi(96)
	{ 
	}

	void Update(int dpi) { m_dpi = dpi; }

	// Get screen DPI.
	int GetDPI() { _Init(); return m_dpi; }

	// Convert between raw pixels and relative pixels.
	int Scale(int x) { _Init(); return MulDiv(x, m_dpi, 96); }
	int UnScale(int x) { _Init(); return MulDiv(x, 96, m_dpi); }
	
	// Invalidate any cached metrics.
	void Invalidate() { _fInitialized = false; }

private:
	void _Init()
	{
		if (!_fInitialized)
		{
			HDC hdc = GetDC(NULL);
			if (hdc)
			{
				m_dpi = GetDeviceCaps(hdc, LOGPIXELSX);
				ReleaseDC(NULL, hdc);
			}
			_fInitialized = true;
		}
	}

private:
	bool _fInitialized;
	int m_dpi;
};
