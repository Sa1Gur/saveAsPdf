#include "customprintpreviewdialog.h"

SaveAsPdf::SaveAsPdf()
{
	n				= 3;
	hdcPainter		= 0;
	bitmapDC		= 0;

	nWidth			= 2100;
	nHeight			= 2970;	
	

	printerPDF		= new QPrinter();
	im = 0;
}

SaveAsPdf::~SaveAsPdf()
{
	
}

void	SaveAsPdf::ReleasePdfDC(HDC hdc)
{
	printerPDF->releaseDC(hdc);
}

HDC		SaveAsPdf::GetPdfDC()
{
	if (im)
	{
		qimage = im->image();
		qimage.fill(Qt::white);

		bitmapDC = im->getDC();

		SetMapMode(bitmapDC,		MM_ANISOTROPIC);
		SetWindowExtEx(bitmapDC,	nWidth,		nHeight,		NULL);
		SetViewportExtEx(bitmapDC,	n * nWidth,	n * nHeight,	NULL);
	}
	
	return bitmapDC;
}

void	SaveAsPdf::SetPaperSizeAndOrientation(QPrinter::PaperSize ps, QPrinter::Orientation or)
{
	printerPDF->setPaperSize(ps);
	printerPDF->setOrientation(or);

	if (printerPDF->orientation() == QPrinter::Orientation::Landscape)
	{
		nWidth	= 2970;
		nHeight	= 2100;
	}

	im				= new QDCWithImage(n * nWidth, n * nHeight);
}

bool	SaveAsPdf::InitiatePdf(wchar_t* path)
{
	bool validEngine = false;
	allowNewPage = false;
		
	printerPDF->setOutputFormat(QPrinter::PdfFormat);
	printerPDF->setOutputFileName(QString::fromUtf16(path));

	painter = new QPainter(printerPDF);
	
	if (painter->paintEngine())
	{
		validEngine = true;

		logX = painter->paintEngine()->paintDevice()->physicalDpiX();
		logY = painter->paintEngine()->paintDevice()->physicalDpiY();
	}

	nPage = 0;

	return validEngine;
}

void SaveAsPdf::CreatePdf()
{	
	im->releaseDC(bitmapDC);
	delete im;

	delete painter;
	delete printerPDF;
}

bool SaveAsPdf::newPage()
{
	bool result = false;
	if (allowNewPage)
	{
		result = printerPDF->newPage();
		if (result)
			nPage++;
	}
	return result; 
}

void SaveAsPdf::PrintPagePdf()
{
	mainRect = new QRect(0, nPage * 297 * logY, 210 * logX, 297 * logY);
	
	painter->fillRect(*mainRect, Qt::white);
	painter->setWindow(*mainRect);
	painter->drawImage(*mainRect, qimage);

	qimage.fill(Qt::white);

	delete mainRect;

	allowNewPage = true;
}