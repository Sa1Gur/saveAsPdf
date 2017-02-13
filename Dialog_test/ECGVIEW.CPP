const char szWindowEcgVTitle[]="ECG";
#define EcgVViewWind	WS_VISIBLE|WS_THICKFRAME|WS_SYSMENU|WS_MINIMIZEBOX		//WS_VISIBLE|WS_CHILD|WS_SIZEBOX
HWND	hwndEcgV;
#define NBrType	16
HWND	ECGFbtn[NBrType],ECGChbtn[NOptionChan];
HWND hwndGrCh;
UINT Timer_UINT;
VOID CALLBACK Timer_ProcedureBR(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
void SetOnOff(int oneparam,int secparam,int itemcheck,HWND hdlg);
BOOL	WndProc_RedrawEcgV(HWND hWnd);
void	FastRedraw	(HWND hwnd,BOOL FR=TRUE);
BOOL WndProc_OnCloseEcg(HWND hWnd);
DWORD	QRS2vm	(LPQRSinf qrs,LPvideomorda vmrd);
DWORD	Sample2vm	(DWORD sample,LPvideomorda vmrd);
#define	smalestXecg		400
#define	smalestYecg		300
videomorda	VMviewECG;
DWORD	current_qrs_seach=1;
void ClearSelected();
void NameTask(HWND hwnd,int newtype);
BOOL APIENTRY DialogTypeQRS	(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL DlgProc_OnInitDialogTypeQRS(HWND hdlg,HWND hwndFocus,LPARAM lParam);
BOOL DlgProc_OnCommandTypeQRS(HWND hdlg,int id,HWND hwndCtl,UINT codeNotify);
void	RedrawEcgV(HDC hdc,HWND hwnd,LPRECT lpr=NULL);
LPSTR	fnk[]={(LPSTR)&WinSelMsg,(LPSTR)&VeALLMsg,(LPSTR)&VeBGMMsg,(LPSTR)&VePairMsg,
	(LPSTR)&VeVTMsg,(LPSTR)&SVeALLMsg,(LPSTR)&SVePairMsg,(LPSTR)&SVeSVTMsg,
	(LPSTR)&PauseMsg,(LPSTR)&MAMsg,(LPSTR)&STelevMsg,(LPSTR)&SVdeprMsg,(LPSTR)&EventMsg,
	(LPSTR)&MarkedMsg,(LPSTR)&ArtfMsg,(LPSTR)&ALLQRSMsg};
int		EcgWinOn=0,SampleToCenter;
int		press_ve=1;
int		ecg_scale=1;
void	Q_classify();
void	SeachPrevEvent(HWND hWnd);
void	SeachNextEvent(HWND hWnd);
void CuptureToEcgView(LPMSG lpmsg);
void	SetViewVM(BOOL redraw=TRUE);
void LoadNewList(int type,HWND hdlg);
void SetOp(HWND hdlg);
void RemoveSingleQRS(DWORD nqrs);
void SetOnOffCheck(int flag,HWND hwnd);
void OffAll();
void OnOffChnl	(BOOL redraw=TRUE);
void OnOffChnlX	(LPDWORD lpmask,HWND* lphw,HWND xhwnd);
void OnOffXn	(LPDWORD lpmask,HWND* lphw,HWND xhwnd,int N);
void EnDizfChnlX	(LPDWORD lpmask,HWND* lphw,HWND xhwnd);
void DrawIzmValuers(HDC hdc);

BOOL TestXYOnOkkey(int X,int Y,LPRECT lprc);
DWORD SwitchInt(LPDWORD lp);
BOOL TestOnMyQRS(LPQRSinf qrs);
BOOL TestOnWinQRS(LPQRSinf qrs);
BOOL TestOnVEQRS(LPQRSinf qrs);
BOOL TestOnVEPRQRS();
BOOL TestOnVEBGMQRS();
BOOL TestOnVTQRS();
BOOL TestOnSVEPRQRS();
BOOL TestOnSVTQRS();
BOOL TestOnSVEQRS(LPQRSinf qrs);
BOOL TestOnMaStart();
BOOL TestOnSingleVE();
BOOL TestOnSingleSVE();

void	RedrawMarkersIzmer(HDC hdc);
void	DrawMarkersIzmer(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark);
void	RestoreScrBeforeDraw(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark);
void	SaveScrBeforeDraw(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark);
void	CloseIzmerDCandBitmap();
void	InitIzmerSoft();
void	RedrawMarkersIzmerNoDC();
DWORD	oldXleftECGmark,oldXRightECGmark,oldYleftECGmark,oldYRightECGmark;
DWORD	cXleftECGmark=100,cXRightECGmark=300,cYleftECGmark=20,cYRightECGmark=50;

extern void StandartSwitch	(int Id);
void	NextFrgView	(HWND hWnd);
void OnOffAll();
DWORD	WinFlag=0,VeallFlag=0,VePrFlag=0,VeBgmFlag=0,VeVTFlag=0,SVeallFlag=0,SVePrFlag=0,SVeSVTFlag=0,PauseFlag=0,MaFlag=0,StElFlag=0,StDeprFlag=0,EventFlag=0,MarkFlag=0,ArtfFlag=0,AllFlag=0,VeSingleFlag=0,SVeSingleFlag=0;
extern	DWORD	n_sys_maskecg;
DWORD	n_sys_maskecg=7,PrevPos=-1;
RECT	Okrect,OkrectEcg,rcECGview={0,0,0,0};
extern BOOL	cupRbutton;

DWORD EventElevQRSbuff[1024],EventDeprQRSbuff[1024];
DWORD NEventElev=0,NEventDepr=0,L1Sec=100;
extern	"C"	void CreateQRS_ST_eventBuffer();
int h_Vcal=100;
extern "C"	int mtrmode;
BOOL CheckCreateOk(int i);
BOOL blockredraw=FALSE;
BYTE CheckOkTab[]={1,1,1,1,
					1,1,1,1,
					1,0,0,0,
					0,1,1,1};

void CreateEcgVWin(void)
{	if (EcgWinOn==1)	return;
	PrevPos=-1;
	RECT rc,rcG;
//	LPQRSinf qrs;
	GetClientRect(hwndSys,&rc);
	rc.left=rc.left+(rc.right-rc.left)/10;
	rc.top=rc.top+(rc.bottom-rc.top)/7;
	rc.right=rc.left*9;
	rc.bottom=rc.top*6;

	current_qrs_seach=-1;
//	NextFrgView	(0);
	SetViewVM(FALSE);

//	VMviewECG=vm2;
//
//			n_nes_qrs=current_qrs_seach;
//	_asm	{	call	qrs_inform
//				mov		qrs,esi	}
//
//	SampleToCenter=QRS2vm	(qrs,&VMviewECG);		//it return that select

	int LeastX=btnCordLog[IzmEcgBtnCode].left+(W_MainF*11)+10;
	if (rc.right-rc.left<LeastX)	{rc.right=LeastX+rc.left;}
	BtnState[IzmEcgBtnCode]=0;

	if(rcECGview.left!=0)	{rc=rcECGview;}

	hwndEcgV = CreateWindow(szClassNameEcgV,szWindowEcgVTitle,EcgVViewWind,
	rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,hwndSys,0,hInst,NULL);
	EcgWinOn=1;

	for (int i=NTempVeBtnCode;i<=HelpFrgBtnCode;i++)
{	CreateMyBtnABS(i, hwndEcgV,1);	}

	rcG.top=btnCordLog[NTempVeBtnCode].bottom+(H_MainF/2);
	rcG.bottom=rcG.top+(18*4+(H_MainF*3/2));
	rcG.left=btnCordLog[NTempVeBtnCode].left;
	rcG.right=btnCordLog[FwdBrBtnCode].right;

	hwndGrCh=CreateGroupe (hwndEcgV,hInst,(LPSTR)&FRGChoise_msg,&rcG);
	int distX=(rcG.right-rcG.left-20)/4;
#if	defined(PMtrViever)
distX=(rcG.right-rcG.left-20)/3;
#endif
	int z=0;
	for (i=0;i<NBrType;i++)
	{	ECGFbtn[i]=NULL;
		if(CheckCreateOk(i)==TRUE)
		{	ECGFbtn[i]=ButtonWithFont (fnk[i],
			WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
			rcG.left+10+((z/4)*distX),
			rcG.top+H_MainF+((z-((z/4)*4))*18),distX,18,hwndEcgV,(HMENU)((LocalBtnCode*256)+i),hInst);	z+=1;}}

	RECT rcChn=btnCordLog[ExtrBtnCode];

	if(mtrmode!=1)	{
/*	rcChn.top=rcChn.bottom;		rcChn.bottom=rcChn.bottom+18;
	ECGChbtn[0]=ButtonWithFont ("1",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,rcChn.left,rcChn.top,
	rcChn.right-rcChn.left,18,hwndEcgV,(HMENU)((ChnCode*256)+0),hInst);

	rcChn.top=rcChn.bottom;		rcChn.bottom=rcChn.bottom+18;
	ECGChbtn[1]=ButtonWithFont ("2",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,rcChn.left,rcChn.top,
	rcChn.right-rcChn.left,18,hwndEcgV,(HMENU)((ChnCode*256)+1),hInst);

if (TheRec.n_chanel>=3)
{	rcChn.top=rcChn.bottom;		rcChn.bottom=rcChn.bottom+18;
	ECGChbtn[2]=ButtonWithFont ("3",WS_CHILD|WS_VISIBLE|BS_CHECKBOX,rcChn.left,rcChn.top,
	rcChn.right-rcChn.left,18,hwndEcgV,(HMENU)((ChnCode*256)+2),hInst);	}
*/	
//int z=0;
	distX=FixF16.W_Font*8;
	char Text[32];
	for (i=0;i<TheRec.n_chanel;i++)
{	SprintChanTitle(Text,i);
	z=LogChan2PhysX(i);
	ECGChbtn[i]=ButtonWithFont (Text,WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
	rcChn.left+((z/4)*distX),rcChn.bottom+((z-((z/4)*4))*(FixF16.H_Font+1)),
	distX,FixF16.H_Font+1,hwndEcgV,(HMENU)((ChnCode*256)+i),hInst);	/*z+=1;*/}
		

	
	
	}




	OnOffChnl	(FALSE);
	OnOffAll();

	NextFrgView	(hwndEcgV);


	cupRbutton=TRUE;
	SetFocus(hwndEcgV);
}



BOOL CheckCreateOk(int i)
{
#if	defined(FullViever)
	return TRUE;
#endif
	if(CheckOkTab[i]==1)	{	return TRUE;	}
	return FALSE;
}



void OnOffChnl	(BOOL redraw)
{	//n_sys_maskecg
	OnOffChnlX	(&n_sys_maskecg,&ECGChbtn[0],hwndEcgV);
	if (redraw==TRUE)	{InvalidateRect(hwndEcgV,&Okrect,TRUE);		}}


void OnOffChnlX	(LPDWORD lpmask,HWND* lphw,HWND xhwnd)
{	//n_sys_maskecg
	if(mtrmode==1)	{	*lpmask=1; return;	}
	int onoff,mask=*lpmask;
	for(int i=0;i<TheRec.n_chanel;i++)
	{	onoff=0;
		_asm	{
			mov eax,i
			bt mask,eax
			jnc not1		}
			onoff=1;
not1:	SetOnOffCheck(onoff,*(lphw+i));	}}

void OnOffXn	(LPDWORD lpmask,HWND* lphw,HWND xhwnd,int N)
{	//n_sys_maskecg
	if(mtrmode==1)	{	*lpmask=1; return;	}
	int onoff,mask=*lpmask;
	for(int i=0;i<N;i++)
	{	onoff=0;
		_asm	{
			mov eax,i
			bt mask,eax
			jnc not1		}
			onoff=1;
not1:	SetOnOffCheck(onoff,*(lphw+i));	}}


void EnDizfChnlX	(LPDWORD lpmask,HWND* lphw,HWND xhwnd)
{	//n_sys_maskecg
	if(mtrmode==1)	{	*lpmask=1; return;	}
	int onoff,mask=*lpmask;
	for(int i=0;i<TheRec.n_chanel;i++)
	{	onoff=0;
		_asm	{
			mov eax,i
			bt mask,eax
			jnc not1		}
			onoff=1;
not1:		EnableWindow(*(lphw+i),onoff);		}}


void OnOffAll()
{	SetOnOffCheck(WinFlag,ECGFbtn[0]);
	SetOnOffCheck(VeallFlag,ECGFbtn[1]);
	SetOnOffCheck(VeBgmFlag,ECGFbtn[2]);
	SetOnOffCheck(VePrFlag,ECGFbtn[3]);
	SetOnOffCheck(VeVTFlag,ECGFbtn[4]);
	SetOnOffCheck(SVeallFlag,ECGFbtn[5]);
	SetOnOffCheck(SVePrFlag,ECGFbtn[6]);
	SetOnOffCheck(SVeSVTFlag,ECGFbtn[7]);
	SetOnOffCheck(PauseFlag,ECGFbtn[8]);
	SetOnOffCheck(MaFlag,ECGFbtn[9]);
	SetOnOffCheck(StElFlag,ECGFbtn[10]);
	SetOnOffCheck(StDeprFlag,ECGFbtn[11]);
	SetOnOffCheck(EventFlag,ECGFbtn[12]);
	SetOnOffCheck(MarkFlag,ECGFbtn[13]);
	SetOnOffCheck(ArtfFlag,ECGFbtn[14]);
	SetOnOffCheck(AllFlag,ECGFbtn[15]);	}

#define	foward	0
#define	back	1
int direction;
void	NextFrgView	(HWND hWnd)
{	if (direction!=foward)	{PicTab[BrBtnCode]=PictBr;	InvalidateRect(ControlBtn[BrBtnCode],NULL,TRUE);}
	direction=foward;
	int LastQRS=current_qrs_seach;
	LPQRSinf qrs;

//Seach after Time
	if (PrevPos==-1)	goto	restart;
	if(EventFlag==1)	{	/*Seach prev event*/	SeachNextEvent(hWnd);	return;	}	
	n_nes_qrs=0;
ConttoSeach:;
	_asm	{	call qrs_inform
				jc	PassIt
				mov		qrs,esi	}
				if (qrs->position>PrevPos)
				{current_qrs_seach=n_nes_qrs-1;	goto	restart;}
				else {	n_nes_qrs+=1;	goto ConttoSeach;}
//End new





restart:;
		
				
	if(EventFlag==1)	{		n_nes_qrs=current_qrs_seach;	PrevPos=0;
				_asm	{	call	qrs_inform
						jc PassItEvent
						mov		qrs,esi	}
						PrevPos=qrs->position;
PassItEvent:;			
		/*Seach prev event*/		SeachNextEvent(hWnd);	return;	}
		
		n_nes_qrs=current_qrs_seach+1;
//outDigit(current_qrs_seach);

		_asm	{	call	qrs_inform
				jc PassIt
				mov		qrs,esi	}
				if (TestOnMyQRS(qrs)==TRUE)
	{	SampleToCenter=QRS2vm	(qrs,&VMviewECG);		//it return that select
	current_qrs_seach=n_nes_qrs;
	if(hWnd!=0)		{	FastRedraw	(hWnd);}
	LastQRS=current_qrs_seach;	}
	else	{current_qrs_seach+=1;		goto restart;}
//	InvalidateRect(hWnd,&Okrect,TRUE);
PassIt:;	current_qrs_seach=LastQRS;	PrevPos=-1;	}


void	SeachPrevEvent(HWND hWnd)
{		DWORD	eventdat[512],resread[2],Nevent,l;

		if(FileRead((LPSTR)&event_fail,&eventdat,sizeof(eventdat),NULL,&resread[0])==FALSE)		{	return;	}

		Nevent=resread[1]/8;
		if(Nevent==0)																{	return;	}

		for(l=0;l<Nevent;l++)
		{	if(eventdat[2*l]>=PrevPos)	{	if(l!=0)	{
			
		if(	current_qrs_seach==-1)	{current_qrs_seach=0;}
		SampleToCenter=Sample2vm(eventdat[2*(l-1)],&VMviewECG); PrevPos=eventdat[2*(l-1)];
//		InvalidateRect(hWnd,NULL,TRUE);
		FastRedraw	(hWnd);
		return;	}
											else		{	return;	}}}
		return;	}

void	SeachNextEvent(HWND hWnd)
{		DWORD	eventdat[512],resread[2],Nevent,l;
		if(FileRead((LPSTR)&event_fail,&eventdat,sizeof(eventdat),NULL,&resread[0])==FALSE)	{	return;	}
		Nevent=resread[1]/8;
		if(Nevent==0)																{	return;	}

		for(l=0;l<Nevent;l++)
		{	if(eventdat[2*l]>PrevPos)	{	if(	current_qrs_seach==-1)	{current_qrs_seach=0;}
		SampleToCenter=Sample2vm(eventdat[2*l],&VMviewECG); PrevPos=eventdat[2*l];
//		InvalidateRect(hWnd,NULL,TRUE);
	FastRedraw	(hWnd,FALSE);
		return;		}}
			return;	}

void	PrevFrgView	(HWND hWnd)
{	if (direction!=back)	{PicTab[BrBtnCode]=PictBrBack;	InvalidateRect(ControlBtn[BrBtnCode],NULL,TRUE);}
	direction=back;
	int LastQRS=current_qrs_seach;
	LPQRSinf qrs;


//Seach after Time
	if (PrevPos==-1)	goto	restart;

	if(EventFlag==1)	{	/*Seach prev event*/		SeachPrevEvent(hWnd);		return;	}		

	n_nes_qrs=0;
ConttoSeach:;
	_asm	{	call qrs_inform
				jc	PassIt
				mov		qrs,esi	}
				if (qrs->position>PrevPos)
				{ current_qrs_seach=n_nes_qrs; goto	restart;}
				else {	n_nes_qrs+=1;	goto ConttoSeach;}
//End new

restart:;
		
	if(EventFlag==1)	{	n_nes_qrs=current_qrs_seach;	PrevPos=0;
				_asm	{	call	qrs_inform
						jc PassItEvent
						mov		qrs,esi	}
						PrevPos=qrs->position;
PassItEvent:;			
		/*Seach prev event*/		SeachPrevEvent(hWnd);	return;	}
		
		n_nes_qrs=current_qrs_seach-1;


	_asm	{	call	qrs_inform
				jc PassIt
				mov		qrs,esi	}
	if (TestOnMyQRS(qrs)==TRUE)
	{	SampleToCenter=QRS2vm	(qrs,&VMviewECG);		//it return that select
	current_qrs_seach=n_nes_qrs;
	FastRedraw	(hWnd);	LastQRS=current_qrs_seach;}
	else	{current_qrs_seach-=1;		goto restart;}
//	InvalidateRect(hWnd,&Okrect,TRUE);
PassIt:;	current_qrs_seach=LastQRS;	PrevPos=-1;		}

DWORD	querQ[4];
BYTE	MAbyte[4],nMAbyte[4];
BOOL TestOnMyQRS(LPQRSinf qrs)
{//Test on Artf
	if (AllFlag==1) return TRUE;
	if (WinFlag==1)	{if (TestOnWinQRS(qrs)==TRUE)	{return TRUE;}}	
	if (VeallFlag==1)	{if (TestOnVEQRS(qrs)==TRUE)	{return TRUE;}}


	if (SVeallFlag==1)	{if (TestOnSVEQRS(qrs)==TRUE)	{return TRUE;}}	

//Make qrs querry
	querQ[0]=ArtfQRS;	querQ[1]=ArtfQRS;	querQ[3]=ArtfQRS;	querQ[2]=qrs->type;
	MAbyte[0]=0;		MAbyte[1]=0;		MAbyte[3]=0;		MAbyte[2]=qrs->MA;
	DWORD saveqrs=n_nes_qrs;	LPQRSinf theqrs;
	if (GetPrevQRS()==TRUE)	{
	_asm	{	call qrs_inform
			mov theqrs,esi}
		querQ[1]=theqrs->type;	MAbyte[1]=theqrs->MA;
	if (GetPrevQRS()==TRUE)	{
	_asm	{	call qrs_inform
			mov theqrs,esi}
	querQ[0]=theqrs->type;	MAbyte[0]=theqrs->MA;}}				n_nes_qrs=saveqrs;
	if (GetNextQRS()==TRUE)	{
	_asm	{	call qrs_inform
			mov theqrs,esi}
			querQ[3]=theqrs->type;	MAbyte[3]=theqrs->MA;}		n_nes_qrs=saveqrs;
	


	//substitute As to S
	for (int i=0;i<4;i++)
	{if (querQ[i]==SVEABQrs)	{querQ[i]=SVEQrs;}}

	//create nMAbyte
	for (i=0;i<4;i++)	{	nMAbyte[i]=(MAbyte[i]+1)&1;	}


	_asm	{	call qrs_inform
				call TestOnQRS
				jc	passsometests	}

	if (VeSingleFlag==1)	{if (TestOnSingleVE()==TRUE)	{return TRUE;}}
	if (SVeSingleFlag==1)	{if (TestOnSingleSVE()==TRUE)	{return TRUE;}}

	if (VePrFlag==1)	{if (TestOnVEPRQRS()==TRUE)	{return TRUE;}}	
	if (SVePrFlag==1)	{if (TestOnSVEPRQRS()==TRUE)	{return TRUE;}}	

	if (VeBgmFlag==1)	{if (TestOnVEBGMQRS()==TRUE)	{return TRUE;}}	
	if (VeVTFlag==1)	{if (TestOnVTQRS()==TRUE)	{return TRUE;}}	
	if (SVeSVTFlag==1)	{if (TestOnSVTQRS()==TRUE)	{return TRUE;}}	
passsometests:;

	if (MarkFlag==1)	{if(qrs->marker==1)	{return TRUE;}}
	if (PauseFlag==1)	{if(qrs->afterPause==1)	{return TRUE;}}

	if (StElFlag==1)
	{for (i=0;i<(int)NEventElev;i++)	{if (n_nes_qrs==EventElevQRSbuff[i])	return TRUE;}}
	
	if (StDeprFlag==1)
	{for (i=0;i<(int)NEventDepr;i++)	{if (n_nes_qrs==EventDeprQRSbuff[i])	return TRUE;}}

	if (MaFlag==1)	{if(TestOnMaStart()==TRUE)	return TRUE;}

	if (qrs->type==ArtfQRS)	{if (ArtfFlag==1) {return TRUE;} return FALSE;}


		
	
	return FALSE;			}

BOOL TestOnSingleVE()
{	if(querQ[2]==VEQrs)
	{if(querQ[0]!=VEQrs)
	{if(querQ[1]!=VEQrs)
	{if(querQ[3]!=VEQrs)	{	return TRUE;	}}}}	return FALSE;}

BOOL TestOnSingleSVE()
{	if((querQ[2]*nMAbyte[2])==SVEQrs)
	{if((querQ[0]*nMAbyte[0])!=SVEQrs)
	{if((querQ[1]*nMAbyte[1])!=SVEQrs)
	{if((querQ[3]*nMAbyte[3])!=SVEQrs)	{	return TRUE;	}}}}	return FALSE;}

BOOL TestOnMaStart()
{		if(MAbyte[2]==0)		{	return FALSE;}
		if(querQ[2]!=SVEQrs)	{	return FALSE;}

		if(MAbyte[1]==0)		{	return TRUE;}
		if(querQ[1]==SVEQrs)	{	return FALSE;}

		if(MAbyte[0]==0)		{	return TRUE;}
		if(querQ[1]==SVEQrs)	{	return FALSE;}

		return TRUE;}


void CreateQRS_ST_eventBuffer()
{				NEventElev=0;	NEventDepr=0;
				DWORD		Time=0;
				for (DWORD i=0;i<n_st_event;i++)
				{	_asm	{
					mov esi,offset SteventBuffer
					mov eax,i
					shl eax,4
					add esi,eax
					mov eax,[esi+4]				//time
					mul f_desc_10000
					mov ebx,10000
					div ebx
					mov edi,eax
				
					cmp byte ptr [esi],0		//depr
					je ItDepr
					cmp byte ptr [esi],1		//elev
					je ItElev
					jmp next
ItDepr:				call SeachNormQRS
					jc	next
					mov esi,offset EventDeprQRSbuff
					mov ebx,NEventDepr
					shl ebx,2
					mov eax,n_nes_qrs
					mov [esi+ebx],eax
					inc	NEventDepr
					jmp next
ItElev:				call SeachNormQRS
					jc	next
					mov esi,offset EventElevQRSbuff
					mov ebx,NEventElev
					shl ebx,2
					mov eax,n_nes_qrs
					mov [esi+ebx],eax
					inc	NEventElev
					jmp next	}
next:;}				return;	

				_asm		{
SeachNormQRS:		call Sample2QRS
					jc	SeachFail
nextqrs:			call qrs_inform
					jc	SeachFail
					mov	al,[esi+4]
					and al,1111b
					cmp al,NormQrs
					je QRSFound
					cmp al,SVEQrs
					je QRSFound
					dec n_nes_qrs
					jmp nextqrs
QRSFound:			clc
SeachFail:			ret				}

}

BOOL TestOnWinQRS(LPQRSinf qrs)
{	if (qrs->Ntemplate==0)			return FALSE;
	if (qrs->Ntemplate>Ntempltes)	return FALSE;
	if (Tselect[(qrs->Ntemplate)-1]==1)	{return TRUE;}	return FALSE;}

BOOL TestOnVEPRQRS()
{	if(querQ[0]==VEQrs)	return FALSE;
	if(querQ[1]!=VEQrs)	return FALSE;
	if(querQ[2]!=VEQrs)	return FALSE;
	if(querQ[3]==VEQrs)	return FALSE;
	return TRUE;		}


BOOL TestOnVEBGMQRS()
{
	if(querQ[1]!=VEQrs)	return FALSE;
	if(querQ[2]==VEQrs)		return FALSE;
	if(querQ[2]==ArtfQRS)	return FALSE;
	if(querQ[3]!=VEQrs)	return FALSE;
	return TRUE;		}

BOOL TestOnVTQRS()
{	if(querQ[0]==VEQrs)	return FALSE;
	if(querQ[1]!=VEQrs)	return FALSE;
	if(querQ[2]!=VEQrs)	return FALSE;
	if(querQ[3]!=VEQrs)	return FALSE;
	return TRUE;		}

BOOL TestOnSVEPRQRS()
{	if((querQ[0]*nMAbyte[0])==SVEQrs)	return FALSE;
	if((querQ[1]*nMAbyte[1])!=SVEQrs)	return FALSE;
	if((querQ[2]*nMAbyte[2])!=SVEQrs)	return FALSE;
	if((querQ[3]*nMAbyte[3])==SVEQrs)	return FALSE;
	return TRUE;		}


BOOL TestOnSVTQRS()
{	if((querQ[0]*nMAbyte[0])==SVEQrs)	return FALSE;
	if((querQ[1]*nMAbyte[1])!=SVEQrs)	return FALSE;
	if((querQ[2]*nMAbyte[2])!=SVEQrs)	return FALSE;
	if((querQ[3]*nMAbyte[3])!=SVEQrs)	return FALSE;
	return TRUE;		}

BOOL TestOnVEQRS(LPQRSinf qrs)
{	if (qrs->type==VEQrs)	{return TRUE;}	return FALSE;}

BOOL TestOnSVEQRS(LPQRSinf qrs)
{	if (qrs->type==SVEQrs)		{
	if(qrs->MA!=1)	{	return TRUE;	}
	else			{	return FALSE;	}}
	if (qrs->type==SVEABQrs)	{if(qrs->MA!=1)	{	return TRUE;	}}	return FALSE;}


int	br_speed=512,old_br_sp;
int	TimerEntered=0;
void	StartBrowrs	(HWND hwnd)
{
	Timer_UINT=SetTimer(hwnd,1,br_speed,(TIMERPROC) & Timer_ProcedureBR);
	old_br_sp=br_speed;	}
void ResetAllf();
void ResetEventf();

VOID CALLBACK Timer_ProcedureBR(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{	if (TimerEntered==1)	{return;}
	TimerEntered=1;

/*	if(idEvent==2)
{	//	Set Focus after Time
	SetFocus(hwnd);	
	KillTimer(hwnd,2);
	DrawValuer(2);
	TimerEntered=0;
	return; 
	}		*/

	if (direction!=back)	{NextFrgView	(hwnd);}

	else	{PrevFrgView	(hwnd);}
	if (old_br_sp!=br_speed)	{
	KillTimer(hwnd,Timer_UINT);
	Timer_UINT=SetTimer(hwnd,1,br_speed,(TIMERPROC) & Timer_ProcedureBR);
	old_br_sp=br_speed;	}

	TimerEntered=0;		}



void EndBrowrs (HWND hwnd)
{
	KillTimer(hwnd,Timer_UINT);		}

void	SetViewVM(BOOL redraw)
{	LPQRSinf qrs;

	switch(press_ve)
	{	case 0:	VMviewECG=vm0;	break;
		case 1:	VMviewECG=vm1;	break;
		case 2:	VMviewECG=vm2;	break;
		case 3:	VMviewECG=vm3;	break;	}

		n_nes_qrs=current_qrs_seach;
	_asm	{	call	qrs_inform
				mov		qrs,esi	}

	
	if(PrevPos==-1)
	{	SampleToCenter=QRS2vm	(qrs,&VMviewECG);	}	//it return that select
	else	{SampleToCenter=Sample2vm(PrevPos,&VMviewECG);}

	if (redraw==TRUE)	{ FastRedraw	(hwndEcgV,FALSE);		}	}

void	ForIzm()
{if (BtnState[IzmEcgBtnCode]==1)	{InitIzmerSoft();	}}


LRESULT WINAPI EcgVWndProc(HWND hWnd,UINT msg, WPARAM wPARAM,LPARAM lParam)
{	LPDRAWITEMSTRUCT itempointer;
	RECT	rc;
	int XCode,CCode;
	LPQRSinf	lpqrs;
	if(msg==HWM_QRSCLASSIFIED)	{
		if(blockredraw!=TRUE)	{	FastRedraw	(hWnd,FALSE);	}
		{		blockredraw=FALSE;}}

	switch (msg)
{	HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate);
	HANDLE_MSG(hWnd, WM_PAINT, WndProc_RedrawEcgV);
	HANDLE_MSG(hWnd,WM_CLOSE,WndProc_OnCloseEcg);


	case WM_CHAR:	switch((TCHAR) wPARAM)
		{		case NormChar0:
				case NormChar1:
				case NormChar2:
				case NormChar3:
//Norm call
								NameTask(hWnd,NormQrs);	break;
				case VEChar0:
				case VEChar1:
				case VEChar2:
				case VEChar3:
//VE call
								NameTask(hWnd,VEQrs);	break;
				case AbberChar0:
				case AbberChar1:
				case AbberChar2:
				case AbberChar3:
//Aberr call
								NameTask(hWnd,ABQrs);	break;


					}			break;



	case WM_COMMAND:
_asm	{		movzx eax,WORD PTR wPARAM
				mov ebx,eax
				and ebx,0ffh
				mov CCode,ebx
				shr eax,8
				mov XCode,eax	}

	if (HIWORD(wPARAM)==BN_CLICKED)
	{
//	DrawValuer(1);
//	SetTimer(hWnd,2,500,(TIMERPROC) & Timer_ProcedureBR);	//set focus 500 ms later
	SetFocus(hWnd);
		
		switch (XCode)		{case ChnCode:
		
		
		/*		switch (CCode)
	{	case 0:	_asm	{btc n_sys_maskecg,0}	OnOffChnl	();	break;
		case 1:	_asm	{btc n_sys_maskecg,1}	OnOffChnl	();	break;
		case 2:	_asm	{btc n_sys_maskecg,2}	OnOffChnl	();	break;	}*/
		_asm		{	mov eax,CCode
						btc n_sys_maskecg,eax	}	OnOffChnl	();		break;


					case LocalBtnCode:	switch (CCode)
						{case 0:	ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&WinFlag),(HWND) lParam);	break;
						case 1:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&VeallFlag),(HWND) lParam);	break;
						case 2:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&VeBgmFlag),(HWND) lParam);	break;
						case 3:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&VePrFlag),(HWND) lParam);	break;
						case 4:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&VeVTFlag),(HWND) lParam);	break;
						case 5:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&SVeallFlag),(HWND) lParam);	break;
						case 6:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&SVePrFlag),(HWND) lParam);	break;
						case 7:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&SVeSVTFlag),(HWND) lParam);	break;

						case 8:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&PauseFlag),(HWND) lParam);	break;
						case 9:		ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&MaFlag),(HWND) lParam);	break;
						case 10:	ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&StElFlag),(HWND) lParam);	break;
						case 11:	ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&StDeprFlag),(HWND) lParam);	break;
						case 12:	OffAll();						SetOnOffCheck(SwitchInt(&EventFlag),(HWND) lParam);	break;
						case 13:	ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&MarkFlag),(HWND) lParam);	break;
						case 14:	ResetAllf( ); ResetEventf();	SetOnOffCheck(SwitchInt(&ArtfFlag),(HWND) lParam);	break;
						case 15:	ResetEventf();	SetOnOffCheck(SwitchInt(&AllFlag),(HWND) lParam);	break;


							
	default:	break;	}		break;
	
					case ControlBtnCode:switch (CCode)
	{	case FwdBrBtnCode:			NextFrgView(hWnd);			break;
		case BackBrBtnCode:			PrevFrgView(hWnd);			break;
		case BrBtnCode:				StandartSwitch	(BrBtnCode);
			if (BtnState[BrBtnCode]==FALSE)	{EndBrowrs (hWnd);}
			else	{StartBrowrs (hWnd);	}					break;
		case IncSpdBrBtnCode:		if(br_speed>16)		{br_speed=br_speed/2;}	break;
		case DecSpdBrBtnCode:		if(br_speed<4096)	{br_speed=br_speed*2;}	break;

		case NTempVeBtnCode:		NameTask(hWnd,NormQrs);		break;
		case VETempVeBtnCode:		NameTask(hWnd,VEQrs);		break;
		case ABTempVeBtnCode:		NameTask(hWnd,ABQrs);		break;
		case PTempVeBtnCode:		NameTask(hWnd,Pwave);		break;
		case TTempVeBtnCode:		NameTask(hWnd,Twave);		break;
		case SVTempVeBtnCode:		NameTask(hWnd,SVpesm);		break;
		case TFTempVeBtnCode:		NameTask(hWnd,TFpesm);		break;
		case PFTempVeBtnCode:		NameTask(hWnd,PFpesm);		break;
		case SPTempVeBtnCode:		NameTask(hWnd,SPpesm);		break;
		case SV0TempVeBtnCode:		NameTask(hWnd,SV0pesm);		break;
		case SP0TempVeBtnCode:		NameTask(hWnd,SP0pesm);		break;
		case MPTempVeBtnCode:		NameTask(hWnd,MPany);		break;

		case RemoveVeBtnCode:		RemoveSingleQRS(current_qrs_seach);			break;
		case ComprBtnCode:			if (press_ve<=0)	{break;}
			else{	press_ve-=1;	SetViewVM();		break;}
		case ExtrBtnCode:			if (press_ve>=3)	{break;}
			else{	press_ve+=1;	SetViewVM();		break;}



		case MRKBtnCode:			n_nes_qrs=current_qrs_seach;
			_asm	{		call	qrs_inform
							jc passM
							mov		lpqrs,esi	}
						if (lpqrs->marker==0)	{lpqrs->marker=1;}
						else					{lpqrs->marker=0;}
passM:;				FastRedraw	(hwndEcgV);		break;	

		case DisMRKBtnCode:	if (OutErrYesNo(RemMarkQuest)!=IDYES)	{break;}
			n_nes_qrs=0;	nextqrs:;
			_asm	{		call	qrs_inform
							jc passDM
							mov		lpqrs,esi	}
							lpqrs->marker=0;	n_nes_qrs+=1;		goto nextqrs;
passDM:;					FastRedraw	(hWnd);						break;	

		case IncBtnCode:	ecg_scale+=1;	if(ecg_scale>2)	{ecg_scale=2;}	FastRedraw	(hWnd,FALSE);	break;
		case DecBtnCode:	ecg_scale-=1;	if(ecg_scale<0)	{ecg_scale=0;}	FastRedraw	(hWnd,FALSE);	break;
		case IzmEcgBtnCode:	StandartSwitch	(IzmEcgBtnCode);		
			if (BtnState[IzmEcgBtnCode]!=1)	{	CloseIzmerDCandBitmap();}
			FastRedraw	(hWnd,FALSE);			break;
		case HelpFrgBtnCode:			StartHelp(ID_HelpOnECGfrgview);	break;
		
		default:		break;	}}		break;			}
	
	//		SetFocus(hwndSys);
//	SetFocus(hWnd);	
	break;
	
//case WM_RBUTTONUP:
case WM_RBUTTONDOWN:
	if (BtnState[IzmEcgBtnCode]==1)
	{if	(TestXYOnOkkey(LOWORD(lParam),HIWORD(lParam),&OkrectEcg)==TRUE)
			{	cXRightECGmark=LOWORD(lParam)-OkrectEcg.left;	cYRightECGmark=HIWORD(lParam)-OkrectEcg.top;
			RedrawMarkersIzmerNoDC();	}}

	else	{	StandartSwitch	(BrBtnCode);
				if (BtnState[BrBtnCode]==FALSE)	{EndBrowrs (hWnd);}
				else	{StartBrowrs (hWnd);	}				}	break;		
	case WM_LBUTTONDOWN:
	if (BtnState[IzmEcgBtnCode]==1)
	{if	(TestXYOnOkkey(LOWORD(lParam),HIWORD(lParam),&OkrectEcg)==TRUE)
		{	cXleftECGmark=LOWORD(lParam)-OkrectEcg.left;	cYleftECGmark=HIWORD(lParam)-OkrectEcg.top;
			RedrawMarkersIzmerNoDC();	}}	break;		
				
	case WM_MOUSEMOVE:
//xPos = LOWORD(lParam);  // horizontal position of cursor 
//yPos = HIWORD(lParam);  // vertical position of cursor 
		if (BtnState[IzmEcgBtnCode]==1) 
		{		if	(TestXYOnOkkey(LOWORD(lParam),HIWORD(lParam),&OkrectEcg)==TRUE)
			{	if (wPARAM & MK_LBUTTON)
					{cXleftECGmark=LOWORD(lParam)-OkrectEcg.left;	cYleftECGmark=HIWORD(lParam)-OkrectEcg.top;
					RedrawMarkersIzmerNoDC();	break;	}
				if (wPARAM & MK_RBUTTON)
					{cXRightECGmark=LOWORD(lParam)-OkrectEcg.left;	cYRightECGmark=HIWORD(lParam)-OkrectEcg.top;
				RedrawMarkersIzmerNoDC();}}}	break;

	case WM_DRAWITEM:
	itempointer=(LPDRAWITEMSTRUCT)lParam;
	if (itempointer->CtlType != ODT_BUTTON) break;
	redrawMyButton(itempointer);
	return TRUE;							break;	


	case WM_KEYDOWN:	GeneralKeyProc(hWnd,wPARAM,lParam);         break;
	case WM_SIZE:
	GetWindowRect(hWnd,&rc);
	if 	(LOWORD(lParam)<smalestXecg)
	{	SetWindowPos(hWnd,0,0,0,rc.right-rc.left+20,rc.bottom-rc.top,SWP_NOMOVE|SWP_NOZORDER); }		
	if 	(HIWORD(lParam)<smalestYecg)
	{	SetWindowPos(hWnd,0,0,0,rc.right-rc.left,rc.bottom-rc.top+20,SWP_NOMOVE|SWP_NOZORDER); }				
	
	InvalidateRect(hWnd, NULL,TRUE);		break;
	case WM_WINDOWPOSCHANGED:        // 
	DefWindowProc(hWnd,msg,wPARAM,lParam);	break;
		
	default:							break;}
	return(DefWindowProc(hWnd,msg,wPARAM,lParam));				}

void CuptureToEcgView(LPMSG lpmsg)
{
//Test On my win
	for (int i=0;i<NBrType;i++)
	{	if(ECGFbtn[i]==lpmsg->hwnd)	goto SwitchBr;	}

	return;


	
SwitchBr:;		StandartSwitch	(BrBtnCode);
				if (BtnState[BrBtnCode]==FALSE)	{EndBrowrs (hwndEcgV);}
				else	{StartBrowrs (hwndEcgV);}	return;		}


DWORD SwitchInt(LPDWORD lp)
{	if (*lp==0) {*lp=1;}	else	{*lp=0;}	return *lp;}

void ResetAllf()
{	if (AllFlag==1)	{SetOnOffCheck(SwitchInt(&AllFlag),ECGFbtn[15]);}}
void ResetEventf()
{	if (EventFlag==1)	{SetOnOffCheck(SwitchInt(&EventFlag),ECGFbtn[12]);}}

void SetOnOffCheck(int flag,HWND hwnd)
{	if(hwnd==NULL)	{	return;	}
	if (flag==1)	{SendMessage(hwnd,BM_SETCHECK,BST_CHECKED,0L);}
	else	{SendMessage(hwnd,BM_SETCHECK,BST_UNCHECKED,0L);}}

void	ClearAllFragFlag();
void OffAll()
{	ClearAllFragFlag();
	OnOffAll();	}

void RemoveSingleQRS(DWORD nqrs)
{	
	
	n_nes_qrs=nqrs;
	LPQRSinf lpqrs;
	DWORD RemTab[N_MaxTemplate+1];
	StartTimeCount();
	int i;
_asm	{	call qrs_inform
			jc passdelqrs
			mov lpqrs,esi	}

			CreateUndoFiles(undorem1_code,1);	//undorem_code,1);
			int OldWin=lpqrs->Ntemplate;
			lpqrs->type=ArtfQRS;	lpqrs->Ntemplate=0;	lpqrs->artfBit=1;
	
			if (OldWin==0)			return;
			if (OldWin>Ntempltes)	return;

			if (GetTemplatePointer(OldWin-1)->N<=1)
	{		for (i=0;i<OldWin-1;i++)
			{RemTab[i]=i;}
			RemTab[OldWin-1]=-1;
			for (i=OldWin;i<Ntempltes;i++)
		{	RemTab[i]=i-1;		}	
			UpdateQRSTemplates(max_n_qrs,(LPDWORD)&RemTab);	Ntempltes=Ntempltes-1;
			ClearSelected();			}
			SaveTheResult();
//		ExRedrawTemplates();			
	GetTimeToBuff(7);
	if (movemode==1)	{ExRedrawTemplates();}

	blockredraw=TRUE;
	statinf.anal_fl.qrs_class=0;
	Q_classify();
	switch (direction)
{	case back:		PrevFrgView		(hwndEcgV);	break;
	case foward:	NextFrgView	(hwndEcgV);		break;
	default:		FastRedraw	(hwndEcgV);		break;}


passdelqrs:;				}

int SelType;
void NameTask(HWND hwnd,int newtype)
{	if ((int)current_qrs_seach<0)	return;
	SelType=newtype;
	if(Ntempltes==N_MaxTemplate)	return;
//Prep new Template
		LPQRSTemplate lpqrs=GetTemplatePointer(Ntempltes);
	videomorda	vmsave=vm;
	FirstInBuff=0;	LastInBuff=0;


//	SamplesInBuf=(GBLim/6)-512;
//	vm.cocomp=(int)((double)SamplesInBuf*((double)10000000)/(double)f_desc_10000);
//	Pointer1=GraphBuff;
//	Pointer2=Pointer1+(GBLim/3);
//	Pointer3=Pointer2+(GBLim/3);

	MemTemplateAllocate(GraphBuff,GBLim);

	CenterQRS=distTmpl/2;
	CenterQRS0=CenterQRS/TheRec.N_expand;
	n_nes_qrs=current_qrs_seach;
	ConfForStndTemplateOperation();
	LoadQRS	();
	*lpqrs=QRSx;

	vm=vmsave;

#if defined(FullViever)
	int SelectedWin=DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,(DLGPROC)DialogTypeQRS);
#else
	int SelectedWin=DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG24),hwnd,(DLGPROC)DialogTypeQRS);
#endif


//	DrawValuer(GetTimeCount());	
}

void DrawQRSExample(LPDRAWITEMSTRUCT itempointer);
int Selwin=0;
BOOL APIENTRY DialogTypeQRS	(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{		LPDRAWITEMSTRUCT	itempointer;
	
		switch (msg)
	{	HANDLE_MSG(hdlg,WM_INITDIALOG,DlgProc_OnInitDialogTypeQRS);
		HANDLE_MSG(hdlg,WM_COMMAND,DlgProc_OnCommandTypeQRS);

		case WM_DRAWITEM:
		itempointer=(LPDRAWITEMSTRUCT)lParam;
		if (itempointer->CtlType != ODT_BUTTON) break;
		DrawQRSExample(itempointer);
		return TRUE;							break;	

		default:	break;	}
		return FALSE;	}

BOOL DlgProc_OnInitDialogTypeQRS(HWND hdlg,HWND hwndFocus,LPARAM lParam)
{
	//fill current
	n_nes_qrs=current_qrs_seach;
	LPQRSinf	lpcqrs;
	char cQRSText[64];
	_asm	{	call	qrs_inform
				mov		lpcqrs,esi	}

	int z=Index2Title((DWORD)lpcqrs->type,(LPSTR)&cQRSText,TRUE);
	if (lpcqrs->type!=ArtfQRS)
	{	z+=sprintf((LPSTR)&cQRSText[z],winmess);
		z+=sprintf ((LPSTR)&cQRSText[z]," %d",lpcqrs->Ntemplate);	}
	cQRSText[z]=0;
	HWND hwndCqrs=GetDlgItem(hdlg,IDC_LIST1);
	SendMessage(hwndCqrs,LB_ADDSTRING,0,(LPARAM)&cQRSText);

	LoadNewList(SelType,hdlg);

//	int m;
//	for (int i=0;i<RealN_OfKtl;i++)
//{	if (i!=C_RecordKatalog)
//	{if (i!=C_katalog)
//	{m=SendMessage(hwndToListm,LB_ADDSTRING,0,(LPARAM)&KatalogTitles[i][0]);
//	SendMessage(hwndToListm,LB_SETITEMDATA,m,i);	}}}
//	SetWindowText(GetDlgItem(hdlg,IDC_EDIT1),(LPSTR)&KatalogTitles[C_katalog][0]);
	
	SetOp(hdlg);

	return TRUE;		}


void SetOp(HWND hdlg)
{	SetOnOff(SelType,NormQrs,IDC_CHECK1,hdlg);
	SetOnOff(SelType,VEQrs,IDC_CHECK2,hdlg);
	SetOnOff(SelType,ABQrs,IDC_CHECK3,hdlg);

	SetOnOff(SelType,Pwave,IDC_CHECK4,hdlg);
	SetOnOff(SelType,Twave,IDC_CHECK5,hdlg);

	SetOnOff(SelType,SVpesm,IDC_CHECK6,hdlg);
	SetOnOff(SelType,TFpesm,IDC_CHECK7,hdlg);

	SetOnOff(SelType,PFpesm,IDC_CHECK8,hdlg);
	SetOnOff(SelType,SPpesm,IDC_CHECK9,hdlg);
	SetOnOff(SelType,SV0pesm,IDC_CHECK10,hdlg);
	SetOnOff(SelType,SP0pesm,IDC_CHECK12,hdlg);

	SetOnOff(SelType,MPany,IDC_CHECK11,hdlg);		}
int TypeInList[N_MaxTemplate+1];
void LoadNewList(int type,HWND hdlg)
{	char cQRSText[64];
	LPQRSTemplate pointer;	
	int Cwin=0,x=0;
	HWND hwndLqrs=GetDlgItem(hdlg,IDC_LIST2);
	SendMessage(hwndLqrs,LB_RESETCONTENT,0,0);	
next:;
	int z=Index2Title((DWORD)type,(LPSTR)&cQRSText,TRUE,TRUE);
	z+=sprintf((LPSTR)&cQRSText[z],winmess);
//seach win
	if (Cwin<Ntempltes)
{	pointer=GetTemplatePointer(Cwin);
	if ((int)pointer->type==type)
	{//filling
	TypeInList[x]=Cwin;	x=x++;
	z+=sprintf ((LPSTR)&cQRSText[z]," %d",Cwin+1);
	cQRSText[z]=0;
	SendMessage(hwndLqrs,LB_ADDSTRING,0,(LPARAM)&cQRSText);	}
	Cwin+=1;	goto next;}
	else	{
	TypeInList[x]=Cwin;
	z+=sprintf ((LPSTR)&cQRSText[z]," %dnew",Cwin+1);
	cQRSText[z]=0;
	SendMessage(hwndLqrs,LB_ADDSTRING,0,(LPARAM)&cQRSText);
	cQRSText[1]=0;
	SendMessage(hwndLqrs,LB_SETCURSEL ,0,0);
	Selwin=0;
	InvalidateRect(GetDlgItem(hdlg,IDC_BUTTON2),NULL,TRUE);
	return;}}

sout_str	grph_Tmpe={0,2,1,distTmpl,0,4,500,0,200,1000,-1000,0,6,0,0,32767};
void DrawQRSExample(LPDRAWITEMSTRUCT itempointer)
{

	if (itempointer->CtlID !=IDC_BUTTON2)	return;
// it my
	HDC hdc=itempointer->hDC;
	RECT rc=itempointer->rcItem;
	int a=TypeInList[Selwin];
	int N_templ_chan=GetNbitOne(n_sys_mask_tmp);

	PretyWin (hdc,rc.left,rc.top,rc.right-rc.left-1,rc.bottom-rc.top-1);

	LPQRSTemplate pointer=GetTemplatePointer(a);

	grph_Tmpe.x_first_pt=(short)rc.left;
	grph_Tmpe.pix_per_unit=rc.right-rc.left;
	grph_Tmpe.sampl_per_unit=dist05s;
	grph_Tmpe.nsmpl_to_out=dist05s;

	int k=0,i;
	for (i=0;i<32;i++)
	{	_asm	{mov eax,n_sys_mask_tmp
				mov ebx,i
				bt eax,ebx
				jnc	notchan}
	grph_Tmpe.s_vadr=(((DWORD)&pointer->chan1)+((distTmpl-dist05s)*2))+(distTmpl*k*4);
_asm	{
		mov esi,k
		call get_MvValue
		mov a,ebx}
	if (a==0)	{a=1000000000;}	
	k=k++;
	grph_Tmpe.y_first_pt=rc.top+((rc.bottom-rc.top)*k/(N_templ_chan+1));
	grph_Tmpe.s_max_vid=rc.bottom-grph_Tmpe.y_first_pt-1;
	grph_Tmpe.s_min_vid=rc.top-grph_Tmpe.y_first_pt+1;
	
	grph_Tmpe.s_masht=65536*(rc.bottom-rc.top)/(N_templ_chan+1)/(2*a);
	CSout (hdc,black,(DWORD) &grph_Tmpe);
notchan:;}

	return;		}



void SetOnOff(int oneparam,int secparam,int itemcheck,HWND hdlg)
{	if (oneparam==secparam)	{SendDlgItemMessage(hdlg,itemcheck,BM_SETCHECK,BST_CHECKED,0L);}
	else	{SendDlgItemMessage(hdlg,itemcheck,BM_SETCHECK,BST_UNCHECKED,0L);}}


#define GcheckSw(id,type) {case id: SelType=type; SetOp(hdlg);	\
	LoadNewList(SelType,hdlg);	return TRUE;	break;}


BOOL DlgProc_OnCommandTypeQRS(HWND hdlg,int id,HWND hwndCtl,UINT codeNotify)
{//	int k, N;
//	LPdb_Record	lprecord;
	switch (id)
{	GcheckSw(IDC_CHECK1,NormQrs)
	GcheckSw(IDC_CHECK2,VEQrs)
	GcheckSw(IDC_CHECK3,ABQrs)
	GcheckSw(IDC_CHECK4,Pwave)
	GcheckSw(IDC_CHECK5,Twave)
	GcheckSw(IDC_CHECK6,SVpesm)
	GcheckSw(IDC_CHECK7,TFpesm)
	GcheckSw(IDC_CHECK8,PFpesm)
	GcheckSw(IDC_CHECK9,SPpesm)
	GcheckSw(IDC_CHECK10,SV0pesm)
	GcheckSw(IDC_CHECK12,SP0pesm)
	GcheckSw(IDC_CHECK11,MPany)
	case	IDC_LIST2:
		if (codeNotify==LBN_SELCHANGE)
		{	Selwin=SendMessage(hwndCtl,LB_GETCURSEL,0,0);
		InvalidateRect(GetDlgItem(hdlg,IDC_BUTTON2),NULL,TRUE);	return TRUE;}
		return FALSE;		break;

	case IDCANCEL:
	EndDialog(hdlg,-1);	return	TRUE; break;
	case	IDOK:
	n_nes_qrs=current_qrs_seach;
	LPQRSinf	lpcqrs;
	_asm	{	call	qrs_inform
				mov		lpcqrs,esi	}

	CreateUndoFiles(undorename_code,1);
	QRSinf oldqrs=*lpcqrs;

	lpcqrs->type=SelType;	lpcqrs->Ntemplate=TypeInList[Selwin]+1;	lpcqrs->artfBit=0;
	if(TypeInList[Selwin]==Ntempltes)
	{	GetTemplatePointer(Ntempltes)->type=SelType;	Ntempltes=TypeInList[Selwin]+1;}

	SaveTheResult();


	if(oldqrs.artfBit==0)
	{	if(oldqrs.Ntemplate<=Ntempltes)
	{	if(oldqrs.Ntemplate!=0)
	{	if (GetTemplatePointer(oldqrs.Ntemplate-1)->N<1)
	{		DWORD RemTab[N_MaxTemplate+1];
			int i;
			for (i=0;i<oldqrs.Ntemplate-1;i++)
			{RemTab[i]=i;}
			RemTab[oldqrs.Ntemplate-1]=-1;
			for (i=oldqrs.Ntemplate;i<Ntempltes;i++)
		{	RemTab[i]=i-1;		}	
			UpdateQRSTemplates(max_n_qrs,(LPDWORD)&RemTab);	Ntempltes=Ntempltes-1;
			ClearSelected();
			SaveTheResult();			}}}}

//	DrawValuer(GetTimeCount());	
	if (movemode==1)	{ExRedrawTemplates();}
//	FastRedraw	(hwndEcgV);
	blockredraw=TRUE;
	Q_classify();
	switch (direction)
{	case back:		PrevFrgView		(hwndEcgV);	break;
	case foward:	NextFrgView	(hwndEcgV);		break;
	default:		FastRedraw	(hwndEcgV);		break;}
	EndDialog(hdlg,0);

	return	TRUE;	break;

	default:	return FALSE;	break;}	}

void ClearSelected()
{		for (int i=0;i<Ntempltes;i++)		{	Tselect[i]=0;	}}




BOOL WndProc_OnCloseEcg(HWND hWnd)
{	cupRbutton=FALSE;
	GetWindowRect(hWnd,&rcECGview);


	for (int i=NTempVeBtnCode;i<=HelpFrgBtnCode;i++)
	{		DestroyMyBtn(i);	}
		DestroyWindow(hwndEcgV);	EcgWinOn=0;
		if (BtnState[ECGVeBtnCode]==TRUE)	{StandartSwitch	(ECGVeBtnCode);	}
		SetFocus(hwndSys);
		return NULL;}


//Izmer Soft
HDC			hMemDCIzmEcg;
HBITMAP		LeftHorBmp,LeftVertBmp,RightHorBmp,RightVertBmp;
BOOL		IzmerSoftInited=FALSE,was_izxmmarkSave=FALSE;
DWORD		MarkH,MarkL;
void	RedrawMarkersIzmerNoDC()
{		HDC hdc=GetDC(hwndEcgV);
		RedrawMarkersIzmer(hdc);
		ReleaseDC (hwndEcgV,hdc);		}


void	DrawIzmValuers(HDC hdc)
{		RECT	rc;
		rc.left=btnCordLog[HelpFrgBtnCode].left;	rc.top=btnCordLog[HelpFrgBtnCode].bottom+3;
		rc.right=rc.left+(W_MainF*11);			rc.bottom=rc.top+(H_MainF*3);

		HBRUSH	br=XBackColor;	//CreateSolidBrush(white);
		FillRect(hdc,(LPRECT) &rc,br); 
	//	DeleteObject(br);

		PretyWin (hdc,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);

		char TextBuff[50];
		DWORD valuer=100,z;
		rc.right=rc.right-3;	rc.top+=H_MainF/2;

		valuer=1000*((int)(cXRightECGmark-cXleftECGmark))/L1Sec;
		z=sprintf((LPSTR)&TextBuff[0],"%d",valuer);
		z+=sprintf((LPSTR)&TextBuff[z],msmess);
		z+=sprintf((LPSTR)&TextBuff[z],"\n");


		valuer=-(1000*(int)((cYRightECGmark-cYleftECGmark))/(int)h_Vcal);
		z+=sprintf((LPSTR)&TextBuff[z],"%d",valuer);
		z+=sprintf((LPSTR)&TextBuff[z],mkvmess);
		pict_in_BoxR(hdc,(LPCTSTR)&TextBuff,&rc,z,black,MainFont);		}


void InitIzmerSoftDC(HDC hdc)
{		hMemDCIzmEcg=CreateCompatibleDC(hdc);
		MarkH=OkrectEcg.bottom-OkrectEcg.top;
		MarkL=OkrectEcg.right-OkrectEcg.left;

		LeftVertBmp=CreateCompatibleBitmap(hdc,2,MarkH);
		RightVertBmp=CreateCompatibleBitmap(hdc,2,MarkH);
		LeftHorBmp=CreateCompatibleBitmap(hdc,MarkL,2);
		RightHorBmp=CreateCompatibleBitmap(hdc,MarkL,2);
		IzmerSoftInited=TRUE;	was_izxmmarkSave=FALSE;
		RedrawMarkersIzmer(hdc);}


void	InitIzmerSoft()
{		if (IzmerSoftInited==TRUE)	{CloseIzmerDCandBitmap();}

		HDC hdc=GetDC(hwndEcgV);
		InitIzmerSoftDC(hdc);
		ReleaseDC (hwndEcgV,hdc);		}

void	CloseIzmerDCandBitmap()
{			DeleteDC(hMemDCIzmEcg);
			DeleteObject(LeftHorBmp);
			DeleteObject(LeftVertBmp);
			DeleteObject(RightHorBmp);
			DeleteObject(RightVertBmp);	IzmerSoftInited=FALSE;	was_izxmmarkSave=FALSE;}



void	SaveScrBeforeDraw(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark)
{	SelectObject(hMemDCIzmEcg,LeftVertBmp);
	BitBlt(hMemDCIzmEcg,0,0,2,MarkH,hdc,OkrectEcg.left+XleftECGmark,OkrectEcg.top,SRCCOPY);
	SelectObject(hMemDCIzmEcg,RightVertBmp);
	BitBlt(hMemDCIzmEcg,0,0,2,MarkH,hdc,OkrectEcg.left+XRightECGmark,OkrectEcg.top,SRCCOPY);
	SelectObject(hMemDCIzmEcg,LeftHorBmp);
	BitBlt(hMemDCIzmEcg,0,0,MarkL,2,hdc,OkrectEcg.left,OkrectEcg.top+YleftECGmark,SRCCOPY);
	SelectObject(hMemDCIzmEcg,RightHorBmp);
	BitBlt(hMemDCIzmEcg,0,0,MarkL,2,hdc,OkrectEcg.left,OkrectEcg.top+YRightECGmark,SRCCOPY);
	was_izxmmarkSave=TRUE;}

void	RestoreScrBeforeDraw(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark)
{	if (was_izxmmarkSave==FALSE) return;
	SelectObject(hMemDCIzmEcg,LeftVertBmp);
	BitBlt(hdc,OkrectEcg.left+XleftECGmark,OkrectEcg.top,2,MarkH,hMemDCIzmEcg,0,0,SRCCOPY);
	SelectObject(hMemDCIzmEcg,RightVertBmp);
	BitBlt(hdc,OkrectEcg.left+XRightECGmark,OkrectEcg.top,2,MarkH,hMemDCIzmEcg,0,0,SRCCOPY);
	SelectObject(hMemDCIzmEcg,LeftHorBmp);
	BitBlt(hdc,OkrectEcg.left,OkrectEcg.top+YleftECGmark,MarkL,2,hMemDCIzmEcg,0,0,SRCCOPY);
	SelectObject(hMemDCIzmEcg,RightHorBmp);
	BitBlt(hdc,OkrectEcg.left,OkrectEcg.top+YRightECGmark,MarkL,2,hMemDCIzmEcg,0,0,SRCCOPY);	}


void	DrawMarkersIzmer(HDC hdc,DWORD	XleftECGmark,DWORD XRightECGmark,DWORD YleftECGmark,DWORD YRightECGmark)
{	HPEN	hgdiPen=CreatePen (PS_SOLID,NULL,b_yellow);
	HPEN	OldPen=SelectObject(hdc,hgdiPen);
	vertline1	(hdc,OkrectEcg.left+XleftECGmark,OkrectEcg.top,MarkH);
	vertline1	(hdc,OkrectEcg.left+XRightECGmark,OkrectEcg.top,MarkH);

	horline1	(hdc,OkrectEcg.left,OkrectEcg.top+YleftECGmark,MarkL);
	horline1	(hdc,OkrectEcg.left,OkrectEcg.top+YRightECGmark,MarkL);

	SelectObject (hdc,OldPen);
	DeleteObject(hgdiPen);						}


void	RedrawMarkersIzmer(HDC hdc)
{	int oldbackgr=SetBkMode(hdc,TRANSPARENT); 
	RestoreScrBeforeDraw(hdc,oldXleftECGmark,oldXRightECGmark,oldYleftECGmark,oldYRightECGmark);
	SaveScrBeforeDraw(hdc,cXleftECGmark,cXRightECGmark,cYleftECGmark,cYRightECGmark);
	DrawMarkersIzmer(hdc,cXleftECGmark,cXRightECGmark,cYleftECGmark,cYRightECGmark);

	oldXleftECGmark=cXleftECGmark;	oldYleftECGmark=cYleftECGmark;
	oldXRightECGmark=cXRightECGmark;	oldYRightECGmark=cYRightECGmark;


	DrawIzmValuers(hdc);
	SetBkMode(hdc,oldbackgr); 
	}


BOOL	TestXYOnOkkey(int X,int Y,LPRECT lprc)
{	if (X<lprc->left)	return FALSE;
	if (X>lprc->right)	return FALSE;
	if (Y<lprc->top)	return FALSE;
	if (Y>lprc->bottom)	return FALSE;
	return	TRUE;		}


DWORD	QRS2vm	(LPQRSinf qrs,LPvideomorda vmrd)		//it return that select
{		
	int fromstart=mSecond2Sample((vmrd->cocomp)/2);
	vmrd->start_point=(qrs->position)-fromstart;
	if (vmrd->start_point>=0)	return fromstart;
	vmrd->start_point=0;
	return qrs->position;								}


DWORD	Sample2vm	(DWORD sample,LPvideomorda vmrd)		//it return that select
{	int fromstart=mSecond2Sample((vmrd->cocomp)/2);
	vmrd->start_point=sample-fromstart;
	if (vmrd->start_point>=0)	return fromstart;
	vmrd->start_point=0;	return sample;						}


BOOL	WndProc_RedrawEcgV(HWND hWnd)
{	PAINTSTRUCT ps;
	HDC			hdc;
	hdc=BeginPaint(hWnd,&ps);

	int oldbackgr=SetBkMode(hdc,TRANSPARENT); 
	RedrawEcgV(hdc,hWnd);
	SetBkMode(hdc,oldbackgr); 
	
	EndPaint(hWnd,&ps);

//ForIzm();
	return 0;}

BOOL	fastRedraw=FALSE;
void	FastRedraw	(HWND hwnd,BOOL FR)
{	
	HDC hdc=GetDC(hwnd);
	int oldbackgr=SetBkMode(hdc,TRANSPARENT);
	fastRedraw=FR;
	RedrawEcgV(hdc,hwnd);
	SetBkMode(hdc,oldbackgr);
	ReleaseDC(hwnd,hdc);
	ForIzm();	}
/*
grph_X.s_vadr;			//vadr
grph_X.pix_per_unit;
grph_X.sampl_per_unit;		//eqv comp
grph_X.nsmpl_to_out;		//n samples to out (cx)
grph_X.s_shif;			//shif
grph_X.s_dddd;			//dddd
grph_X.s_masht;		//masht
grph_X.x_first_pt;
grph_X.y_first_pt;		//sh
grph_X.s_max_vid;
grph_X.s_min_vid;
grph_X.color_s;
grph_X.mode_ssout;
grph_X.reservsoutb;
grph_X.reservsout;
grph_X.res_valuer;		*/


void VMtime2char();
void	RedrawEcgV(HDC hdc,HWND hwnd,LPRECT lpr)
{
//	WINDOWPLACEMENT	wp;
//	GetWindowPlacement(hwnd,&wp);
//	if(wp.showCmd==SW_MINIMIZE)	{return;}

	RECT rc,rc1,rcG;
	DWORD	n_chn;
	BOOL	FirstEntry=TRUE;
	videomorda	savevm;
	LPCTSTR	ChanPointer;

	if(lpr!=NULL)
	{	rc1=*lpr;	goto draw;	}


	int centerX,dist,start,TotN;
	LPQRSinf	lpqrs;

	GetClientRect(hwnd,&rc);

	if((rc.right-rc.left)<100)	{return;}
	if((rc.bottom-rc.top)<100)	{return;}
	GetWindowRect(hwnd,&rc1);
	GetWindowRect(hwndGrCh,&rcG);
	
	
	rc1.top=rcG.bottom-rc1.top-GetSystemMetrics (SM_CYCAPTION);
	rc1.left=btnCordLog[NTempVeBtnCode].left;
	rc1.right=rc.right-W_MainF;
	rc1.bottom=rc.bottom-H_MainF;
	Okrect=rc1;
draw:;

	HBRUSH br=XBackColor;		//CreateSolidBrush(white);	//(blue);
	if (fastRedraw!=TRUE)
	{	FillRect(hdc,(LPRECT) &rc1,br); 
	PretyWin (hdc,rc1.left,rc1.top,rc1.right-rc1.left,rc1.bottom-rc1.top);	}

	rc.left=rc1.left+(7*6);	rc.top=rc1.top+5;	rc.right=rc1.right-5;	rc.bottom=rc1.bottom-5;
	OkrectEcg=rc;
//	Okrect=rc;
	if (current_qrs_seach==-1)	return;
//return;
_asm	{	mov edx,n_sys_maskecg
			call test_chanReg
			mov n_chn,eax			}

	if (n_chn<=0)	return;
//same load before draw
	savevm=vm;
	vm=VMviewECG;
	_asm	{	mov ecx,0
				mov vm.cocomp,100
				call	load_v_dat	}
	vm=savevm;
////////////////////////////

//	setka_v	(hdc,black,rc.left,rc.top,(n_chn+1)*4,VMviewECG.stk_n,rc.right-rc.left,rc.bottom-rc.top,3);
	int z=2*(rc.right-rc.left)/(VMviewECG.stk_n);
	int k;
	L1Sec=(rc.right-rc.left)*1000/vm.cocomp;

//	HorCalibr(hdc,z,rc.left, rc.bottom,(LPSTR)VMviewECG.adr_cal_mess);
	h_Vcal=(rc.bottom-rc.top)/((n_chn+1)*2);

	switch (ecg_scale)
	{	case 0:	h_Vcal=h_Vcal/2;	break;
		case 1:	h_Vcal=h_Vcal;		break;
		case 2:	h_Vcal=h_Vcal*3/2;	break;}
	

	grph_X.res_valuer=32767;
	grph_X.s_dddd=2;
	grph_X.pix_per_unit=(long)(rc.right-rc.left);

	k=1;
	vm=VMviewECG;
	L1Sec=(rc.right-rc.left)*1000/vm.cocomp;
	for	(int zz=31;zz>=0;zz--)
{	int i=LogChan2Phys(zz);
	grph_X.s_vadr=GraphBuff;
	grph_X.x_first_pt=(short)rc.left;
	vm.cocomp;

	_asm	{	mov eax,i	
				bt n_sys_maskecg,eax
				jnc PassTheChan
				mov ecx,eax
				inc ecx
				call	load_v_dat
				mov eax,vm.cocomp
				mov edx,f_desc_10000X
				mul edx
				mov ebx,10000000
				div ebx
				mov grph_X.sampl_per_unit,eax
				mov grph_X.nsmpl_to_out,eax	}
	TotN=grph_X.nsmpl_to_out;
	grph_X.s_shif=EstimateZero();
	grph_X.y_first_pt=(short)((((n_chn-k+1)*(rc.bottom-rc.top))/(n_chn+1))+rc.top);
	if (fastRedraw==FALSE)
{_asm	{
	mov eax,n_cha
	imul eax,eax,byte_per_chan
	add eax,offset ch_l
	inc eax
	mov ChanPointer,eax		}

	vertcal	(hdc,rc1.left+W_MainF,(long)grph_X.y_first_pt,h_Vcal);
	pict_x	(hdc,(LPCTSTR)&MshtTxt1_0,rc1.left,(long)grph_X.y_first_pt-h_Vcal-(H_MainF*7/10),7,black,FixFont16);	
	pict_x	(hdc,ChanPointer,rc1.left+W_MainF+6,grph_X.y_first_pt-(H_MainF*7/10),byte_per_chan-2,black,FixFont16);	}


	 
		vm.cal_lenth=h_Vcal;
	_asm	{		mov ecx,1000		//Lmasht
			call 	set_mashtab	}

	grph_X.s_max_vid=(short)(rc.bottom-grph_X.y_first_pt);
	grph_X.s_min_vid=(short)(rc.top-grph_X.y_first_pt);

	centerX=grph_X.x_first_pt+grph_X.pix_per_unit*SampleToCenter/grph_X.sampl_per_unit;
	dist=f_desc_10000X/20000;
	start=SampleToCenter-(dist/2);
	grph_X.nsmpl_to_out=start;

	if(FirstEntry==TRUE)	{	
	if (fastRedraw==TRUE)
	{	nt:;		if(IsItRetrase()!=TRUE)	{goto nt;}		FillRect(hdc,(LPRECT) &rc,br); 	}

	setka_v	(hdc,black,rc.left,rc.top,(n_chn+1)*4,VMviewECG.stk_n,rc.right-rc.left,rc.bottom-rc.top,3);
	HorCalibr(hdc,z,rc.left, rc.bottom,(LPSTR)VMviewECG.adr_cal_mess);	
	FirstEntry=FALSE;		}

	if(grph_X.nsmpl_to_out>0)	{	CSout (hdc,grph_X.color_s,(DWORD) &grph_X);	}

	grph_X.s_vadr=GraphBuff+(start*2);	
	grph_X.nsmpl_to_out=dist;
	grph_X.x_first_pt=(short)(rc.left+(start*grph_X.pix_per_unit/grph_X.sampl_per_unit));
	if(grph_X.nsmpl_to_out>0)	{if(grph_X.x_first_pt>=rc.left)	{	CSout (hdc,b_red,(DWORD) &grph_X);	}}

	grph_X.s_vadr=GraphBuff+((start+dist)*2);
	grph_X.nsmpl_to_out=TotN-dist-start;
	grph_X.x_first_pt=(short)(rc.left+((start+dist)*grph_X.pix_per_unit/grph_X.sampl_per_unit));
	if(grph_X.nsmpl_to_out>0)	{if(grph_X.x_first_pt>=rc.left)	{	CSout (hdc,grph_X.color_s,(DWORD) &grph_X);	}}

	k++;
PassTheChan:;	}

if(lpr==NULL)
{	GetTimeToBuff(1);

	BOOL savemcode=BtnState[MarkBtnCode];
	grph_X.x_first_pt=(short)rc.left;
	BtnState[MarkBtnCode]=TRUE;
	HGDIOBJ hgdiPen=CreatePen (PS_SOLID,NULL,b_red);
	HGDIOBJ OldPen=SelectObject(hdc,hgdiPen);
	blockredraw=TRUE;
	DrawQRS	(hdc,rc.top+12,vm.cal_lenth,1);

//DrawValuer(GetTimeCount());	
	GetTimeToBuff(2);
	SelectObject(hdc,OldPen);
	DeleteObject(hgdiPen);

	BtnState[MarkBtnCode]=savemcode;
									}			

//draw time
//	RECT rctime=rc;	rctime.right=rctime.left+W_MainF*12; rctime.bottom=rctime.top+H_MainF;
	RECT rctime=rc;	rctime.left=rctime.right-W_MainF*12; rctime.top=rctime.bottom-H_MainF;
	VMtime2char();
	pict_in_Box	(hdc,(LPCTSTR)&TheTime,(LPRECT) &rctime,9,b_blue,MainFont);


	vm=savevm;


	RECT		rcm;
	n_nes_qrs=current_qrs_seach;
		_asm	{	call qrs_inform
					jc pass_m
					mov lpqrs,esi	}					
//draw N ecg win

		if(hwnd!=NULL)
{		if(PrevPos==-1)
{		RECT rcwin=rc;	rcwin.top=rcwin.bottom-SmallF.H_Font;
		char str[32];
		if(lpqrs->artfBit==0)	{	pict_in_Box (hdc,str,&rcwin,sprintf(str,WinText,lpqrs->Ntemplate),black,SmallF.Font);	}}}



	rcm.left=rc.left;		rcm.top=rc.top+((rc.bottom-rc.top)/2);
	rcm.bottom=rcm.top+32;	rcm.right=rcm.left+32;	

	if (lpqrs->marker==1)	{pict_in_Box(hdc,"!",&rcm,1,b_red,MainFont);}

pass_m:

	vertlineN (hdc,centerX,rc.top,rc.bottom-rc.top,b_red,3);
//	DeleteObject(br);
	fastRedraw=FALSE;}



	
	
