#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QFile>

#include "../forms/customprintpreviewdialog.h"

extern "C"	__declspec( dllexport ) 	HDC		_cdecl	GetPdfDC();
extern "C"	__declspec( dllexport ) 	void	_cdecl	SetPaperSizeAndOrientation(int ps, int or);
extern "C"	__declspec( dllexport ) 	bool	_cdecl	InitiatePdf(wchar_t* path);
extern "C"	__declspec( dllexport ) 	void	_cdecl	CreatePdf();
extern "C"	__declspec( dllexport ) 	void	_cdecl	InitiateQtApp();
extern "C"	__declspec( dllexport ) 	void	_cdecl	PrintPagePdf();
extern "C"	__declspec( dllexport ) 	bool	_cdecl	NewPdfPage();

SaveAsPdf		*SaveAsPdf_;
QApplication	*app;

HDC		_cdecl	GetPdfDC()
{
	return	SaveAsPdf_->GetPdfDC();
}

void	_cdecl	InitiateQtApp()
{
	if (!app)
	{
		int		argc = QApplication::GuiClient;
		char	*argv[1];
		app = new QApplication(argc, argv);

		QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
		QTextCodec::setCodecForCStrings(codec);
		QTextCodec::setCodecForTr(codec);

		QCoreApplication::setOrganizationName("Ltd Meditek");
		QCoreApplication::setOrganizationDomain("www.astrocard-meditek.com");
		QCoreApplication::setApplicationName("saveAsPdf");

		SaveAsPdf_ = new SaveAsPdf();
	}
}

void SetPaperSizeAndOrientation(int ps, int or)
{
	QPrinter::PageSize		ps_ = QPrinter::PageSize::A4;
	QPrinter::Orientation	or_  = QPrinter::Orientation::Portrait;

	switch (ps)
	{	
	case DMPAPER_LETTER:
		ps_ = QPrinter::PageSize::Letter;
		break;
	case DMPAPER_TABLOID:
		ps_ = QPrinter::PageSize::Tabloid;
		break;
	case DMPAPER_LEDGER:
		ps_ = QPrinter::PageSize::Ledger;
		break;
	case DMPAPER_LEGAL:
		ps_ = QPrinter::PageSize::Legal;
		break;
	case DMPAPER_EXECUTIVE:
		ps_ = QPrinter::PageSize::Executive;
		break;
	case DMPAPER_A3:
		ps_ = QPrinter::PageSize::A3;
		break;
	case DMPAPER_A4:
		ps_ = QPrinter::PageSize::A4;
		break;
	case DMPAPER_A5:
		ps_ = QPrinter::PageSize::A5;
		break;
	case DMPAPER_B4:
		ps_ = QPrinter::PageSize::B4;
		break;
	case DMPAPER_B5:
		ps_ = QPrinter::PageSize::B5;
		break;
	case DMPAPER_FOLIO:
		ps_ = QPrinter::PageSize::Folio;
		break;
	}

	switch (or)
	{	
	case DMORIENT_PORTRAIT:
		or_ = QPrinter::Orientation::Portrait;
		break;
	case DMORIENT_LANDSCAPE:
		or_ = QPrinter::Orientation::Landscape;
		break;
	}

	SaveAsPdf_->SetPaperSizeAndOrientation(ps_, or_);
}

bool	_cdecl	InitiatePdf(wchar_t* path)
{
	return SaveAsPdf_->InitiatePdf(path);
}

void	_cdecl CreatePdf() 
{
	SaveAsPdf_->CreatePdf();
}

void	_cdecl	PrintPagePdf()
{
	return SaveAsPdf_->PrintPagePdf();
}

bool	_cdecl	NewPdfPage()
{
	return SaveAsPdf_->newPage();
}