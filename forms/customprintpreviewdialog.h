#ifndef SAVEASPDF_H
#define SAVEASPDF_H

#include <tchar.h>
#include <Windows.h>

#include <QtGui/QPrinter>
#include <QtGui/QPainter>
#include <QtGui/QPaintEngine>
#include <QtGui/QPrintPreviewDialog>

class QDCWithImage
{
    public:
        bool isValid() const
        {
            return ( m_Bitmap != 0 &&
                     m_BitmapData != 0 );
        }

        QImage image() const
        {
            if( !isValid() )
                return QImage();

            return QImage(
                        m_BitmapData,
                        m_Width,
                        m_Height,
                        QImage::Format_RGB32 );
        }

        HDC getDC()
        {
            if( !isValid() || m_DCBitmap != 0 )
                return 0;

            HDC screenDC = GetDC( 0 );

            HDC result = CreateCompatibleDC( screenDC );

            ReleaseDC( 0, screenDC );

            m_DCBitmap = reinterpret_cast< HBITMAP >(
                                SelectObject( result, m_Bitmap ) );


			SetBkColor(result, RGB(255, 255, 255));

            return result;
        }

        void releaseDC( HDC dc )
        {
            if( dc == 0 || m_DCBitmap == 0 )
                return;

            SelectObject( dc, m_DCBitmap );
            DeleteDC( dc );

            m_DCBitmap = 0;
        }

        HBITMAP bitmap()
        {
            return m_Bitmap;
        }

        QDCWithImage( int width, int height ):
            m_Bitmap( 0 ),
            m_Width( width ),
            m_Height( height ),
            m_BitmapData( 0 ),
            m_DCBitmap( 0 )
        {
            BITMAPINFO bitmapInfo;

            memset( &bitmapInfo, 0, sizeof( bitmapInfo ) );

            bitmapInfo.bmiHeader.biSize            = sizeof( BITMAPINFOHEADER );
            bitmapInfo.bmiHeader.biWidth        = width;
            bitmapInfo.bmiHeader.biHeight        = -height;
            bitmapInfo.bmiHeader.biPlanes        = 1;
            bitmapInfo.bmiHeader.biSizeImage    = 0;

            bitmapInfo.bmiHeader.biBitCount        = 32;
            bitmapInfo.bmiHeader.biCompression    = BI_RGB;

            HDC screenDC = GetDC( 0 );

            m_Bitmap = CreateDIBSection(
                                 screenDC,
                                &bitmapInfo,
                                 DIB_RGB_COLORS,
                                 reinterpret_cast< void** >( &m_BitmapData ),
                                 0,
                                 0 );

            ReleaseDC( 0, screenDC );
        }

        ~QDCWithImage()
        {
            DeleteObject( m_Bitmap );
        }

    private:
        Q_DISABLE_COPY( QDCWithImage )

        HBITMAP  m_Bitmap;
        int         m_Width;
        int         m_Height;
        uchar    *m_BitmapData;

        HBITMAP     m_DCBitmap;
};

class SaveAsPdf : public QPrintPreviewDialog
{
	Q_OBJECT

public:
	explicit SaveAsPdf();
	~SaveAsPdf();	
	void	ReleasePdfDC(HDC hdc);
	HDC		GetPdfDC();
	void	SetPaperSizeAndOrientation(QPrinter::PaperSize ps, QPrinter::Orientation or);
	bool	InitiatePdf(wchar_t* path);
	void	CreatePdf();
	void	PrintPagePdf();
	bool	newPage();


//private Q_SLOTS:
	HDC				hdcPainter;
	HDC				bitmapDC;
	QPrinter*		printerPDF;
	QPainter*		painter;
	QDCWithImage*	im;
	QImage			qimage;
	QRect			*mainRect;
	int				nPage,
					logX,
					logY,
					n;
	int				nWidth;
	int				nHeight;
	bool			allowNewPage;
//signals:
//	void paintRequested(QPrinter * printer);// QPrinter *);

//private:
//	QPrinter *m_printer;
};

#endif // SAVEASPDF_H