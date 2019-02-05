#include "customprintpreviewdialog.h"

SaveAsPdf::SaveAsPdf()
{
	nScale			= 3;//for increasing quality of pictures
	bitmapDC		= 0;
	
	printerPDF		= 0;
	painter			= 0;
	im				= 0;
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
		SetViewportExtEx(bitmapDC,	nScale * nWidth,	nScale * nHeight,	NULL);
	}
	
	return bitmapDC;
}

bool	SaveAsPdf::InitiatePdf(wchar_t* path)
{
	bool validEngine = false;

	if (!printerPDF)
	{
		printerPDF = new QPrinter();
	}

	allowNewPage = false;

	printerPDF->setOutputFormat(QPrinter::PdfFormat);
	printerPDF->setOutputFileName(QString::fromUtf16(path));

	if (!painter)
	{
		painter = new QPainter(printerPDF);

		if (painter->paintEngine())
		{
			logX = painter->paintEngine()->paintDevice()->physicalDpiX();
			logY = painter->paintEngine()->paintDevice()->physicalDpiY();

			validEngine = true;
		}

		nPage = 0;
	}

	return validEngine;
}

void	SaveAsPdf::SetPaperSizeAndOrientation(QPrinter::PaperSize ps, QPrinter::Orientation or)
{
	if (!printerPDF)
	{
		printerPDF = new QPrinter();
	}		

	printerPDF->setPaperSize(ps);
	printerPDF->setOrientation(or);

	if (printerPDF->orientation() == QPrinter::Orientation::Landscape)
	{
		nWidth = 2970;
		nHeight = 2100;
	}
	else
	{
		nWidth = 2100;
		nHeight = 2970;
	}

	if (im)
	{
		im->releaseDC(bitmapDC);
		delete im;
		im = 0;
	}

	im = new QDCWithImage(nScale * nWidth, nScale * nHeight);
}

void SaveAsPdf::CreatePdf()
{	
	if (im)
	{
		im->releaseDC(bitmapDC);
		delete im;
		im = 0;
	}

	delete painter;
	painter = 0;
	delete printerPDF;
	printerPDF = 0;
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
	auto coeff = (float)qimage.dotsPerMeterX() / 10000;
	mainRect = new QRect(0, 0, coeff * nWidth, coeff * nHeight);
	painter->fillRect(*mainRect, Qt::white);
	painter->drawImage(*mainRect, qimage);

	qimage.fill(Qt::white);

	delete mainRect;	

	allowNewPage = true;
}