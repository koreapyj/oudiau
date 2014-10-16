/*
	OuDia - Win32 Application Software to draw a "Train Service Planning
 Diagram" based on a "Train Timetable".

Copyright (C) 2006-2014 take-okm

This program is free software; you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the Free 
Software Foundation; either version 3 of the License, or (at your option) 
any later version. 

This program is distributed in the hope that it will be useful, but WITHOUT 
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
more details. 

You should have received a copy of the GNU General Public License along with
 this program. If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, take-okm
  gives permission to link the code of this program with
  the "MFC(Microsoft Foundation Class library) Version 9.0" 
  (or with modified versions of "MFC Version 9.0" that use the same license as 
  "MFC Version 9.0" ), and distribute linked combinations including
  the two.  You must obey the GNU General Public License in all
  respects for all of the code used other than  "MFC".  If you modify
  this file, you may extend this exception to your version of the
  file, but you are not obligated to do so.  If you do not wish to
  do so, delete this exception statement from your version.


(訳: 

	OuDia - 列車時刻表をもとに、ダイヤグラムを描画するWin32アプリケーシ
ョン。

Copyright (C) 2006-2014 take-okm 

このプログラムはフリーソフトウェアです。あなたはこれを、フリーソフトウェア財
団によって発行されたGNU 一般公衆利用許諾書(バージョン3か、それ以降のバージョ
ンのうちどれか)が定める条件の下で再頒布または改変 することができます。

このプログラムは有用であることを願って頒布されますが、*全くの無保証 *です。
商業可能性の保証や特定目的への適合性は、言外に示されたものも 含め、全く存在
しません。詳しくはGNU 一般公衆利用許諾書をご覧ください。

あなたはこのプログラムと共に、GNU 一般公衆利用許諾書のコピーを一部 受け取っ
ているはずです。もし受け取っていなければ、<http://www.gnu.org/licenses/> を
ご覧ください。

)

  加えて、特別な例外として、take-okm はこのプログラムのコードを 
  "MFC(Microsoft Foundation Class library) Version 9.0" 
  (  あるいは "MFC Version 9.0" と同じライセンスが適用された
  "MFC Version 9.0" の改変されたバージョン)とリンクし、
  リンクされた両者を含む結合著作物を頒布する許可を与えます。
  あなたは "MFC" 以外で使われているすべて
  のコードに関しては全面的にGNU一般公衆利用許諾契約書に従わなければ
  なりません。あなたがこのファイルを改変したならば、あなたはこの例外
  をあなたのバージョンのファイルに引き続き設けることもできますが、そ
  うする義務はありません。もし例外を設けたくなければ、この例外条項を
  あなたのバージョンからは削除してください。)
*/
// CEkiView.cpp : インプリメンテーション ファイル
//	$Id: CEkiView.cpp 141 2012-10-20 08:03:25Z okm $

#include "stdafx.h"

#include <sstream>

#include "logmsg/LogMsg.h"
#include "Ou/OuNew.h"
#include "str/strToInt.h"
#include "DcDraw/print/CaDcdTargetZoomDisplay.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "DcDraw\CaDcdTargetItemPosition.h"
#include "DcDrawMfc/CDcdTargetMfcPrintInfo.h"
#include "DcdGrid\CaDcdGrid_PageSelector.h"

#include "diagramedit.h"
#include "CDlgEkiProp.h"
#include "CconvCdPrintPageProp.h"
#include "CEkiView.h"
#include "ViewEki\EkiColSpec\EkiColSpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	// ********************************
	//@name CEkiView-操作
	// ********************************
namespace ViewEki{

using namespace std ;
using namespace EkiColSpec;
using namespace DcDrawLib::DcDraw::Print;
using namespace DcDrawLib::DcDrawMfc;


int CEkiView::openCDlgEkiProp( int iEkiIndex ) 
{
	int iRv = 0 ;

	CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc() ;
	const CentDedRosen*	pCentDedRosen = 
		pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen() ;
	const CentDedEkiCont* pCentDedEkiContGet = 
		pCentDedRosen->getCentDedEkiCont() ;

	//	iEkiIndex を Y列番号に変換
	CdEkiYColSpecCont	aYColSpecCont( pCentDedEkiContGet ) ;
	int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
		CdEkiYColSpec( CdEkiYColSpec::ColumnType_Eki ,
			iEkiIndex ) 
	) ;
	if ( iYColumnNumber < 0 )
	{
		iRv = -1 ;	//	列番号が不正です。
	}
	if ( iRv >= 0 )
	{
		//	フォーカスセルを、指定の位置に移動
		CdDcdPosXy posFocusCellColumnNumber 
			= m_pCWndDcdGrid->getCFocus()->getFocusCellColumnNumber() ;
		posFocusCellColumnNumber.setY( iYColumnNumber ) ;
		m_pCWndDcdGrid->getCFocus()->setFocusCellColumnNumber( posFocusCellColumnNumber ) ;

		//	プロパティダイアログを起動
		m_pCWndDcdGrid->execEkiPropDlg( false , FALSE ) ;
	}
	return iRv ;
}


/////////////////////////////////////////////////////////////////////////////
// CEkiView

IMPLEMENT_DYNCREATE(CEkiView, CView)

CEkiView::CEkiView()
	: m_pCWndDcdGrid( NULL ) 
{
}

CEkiView::~CEkiView()
{
}


BEGIN_MESSAGE_MAP(CEkiView, CView)
	//{{AFX_MSG_MAP(CEkiView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEkiView 描画

void CEkiView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}
void CEkiView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pCWndDcdGrid->OnUpdate(pSender, lHint, pHint);
}

/////////////////////////////////////////////////////////////////////////////
// CEkiView 診断

#ifdef _DEBUG
void CEkiView::AssertValid() const
{
	CView::AssertValid();
}

void CEkiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEkiView メッセージ ハンドラ

int CEkiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// --------------------------------	
	m_pCWndDcdGrid = new CWndDcdGridEki() ;
	m_pCWndDcdGrid->Create( this ) ;
	m_pCWndDcdGrid->ShowWindow( SW_SHOW ) ;
	
	return 0;
}

void CEkiView::OnDestroy() 
{
	m_pCWndDcdGrid->DestroyWindow() ;
	delete m_pCWndDcdGrid ;
	m_pCWndDcdGrid = NULL ;

	CView::OnDestroy();
}

void CEkiView::OnSize(UINT nType, int cx, int cy) 
{
	if ( nType == SIZE_MAXIMIZED   //ウィンドウは最大表示されます。
		|| nType == SIZE_RESTORED  // ウィンドウはサイズ変更されますが、SIZE_MINIMIZED と SIZE_MAXIMIZED は適用されません。
	){
		m_pCWndDcdGrid->MoveWindow( 0 , 0 , cx , cy , TRUE ) ;
		return ;
	}
	
	CView::OnSize(nType, cx, cy);
	
}

void CEkiView::OnSetFocus(CWnd* pOldWnd) 
{
	//CView::OnSetFocus(pOldWnd);
	CWnd*	pControl = GetNextDlgTabItem( (CWnd*)NULL , FALSE ) ;
	pControl->SetFocus() ;
	
}




BOOL CEkiView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CEkiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pCWndDcdGrid->OnUpdate( NULL , 0 , NULL ) ;
	
	CView::OnBeginPrinting(pDC, pInfo);
}


void CEkiView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	if ( pInfo != NULL ){
		//	印刷に関する処理
		LogMsg( "CEkiView::OnPrepareDC() " ) ;
		LogMsg( CDcdTargetMfcPrintInfo::stringOf( pInfo ).c_str() ) ;
	}	else	{
		CView::OnPrepareDC(pDC, pInfo);
	}
}

static CdDrawTextProp	getCdDrawTextPropStandard()
{ 
	return CdDrawTextProp( 
		CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ,
		CdColorProp( 0 , 0 , 0 ) ) ;
}


void CEkiView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	LogMsg( "CEkiView::OnPrint() " ) ;
	LogMsg( CDcdTargetMfcPrintInfo::stringOf( pInfo ).c_str() ) ;

	// --------------------------------
	//	描画面を作成
	// --------------------------------
	CDcdTargetMfcPrintInfo	aCDcdTargetMfcPrintInfo( pDC, pInfo ) ;

	// --------------------------------
	//	余白を除いた領域を作成
	// --------------------------------
	CaDcdTargetItemPosition	aTargetInnerMargin( &aCDcdTargetMfcPrintInfo , 
		CdDcdZoneXy() ) ;
	{
		LogMsg( DeviceCapsToString( 
			aCDcdTargetMfcPrintInfo.getPrinterHdc() ).c_str() ) ;
	
		CconvCdPrintPageProp aCconvCdPrintPageProp ;
		CdDcdZoneXy	zonexyInneraMargin = 
			aCconvCdPrintPageProp.calcZoneInnerMargin( 
				getCDiagramEditApp()->getCdPrintPageProp() , 
				aCDcdTargetMfcPrintInfo.getPrinterHdc() ) ;
		if ( zonexyInneraMargin.getX().getSize() <= 0 ){
			zonexyInneraMargin.setX( 
				aCDcdTargetMfcPrintInfo.getZone().getX() ) ;
		}
		if ( zonexyInneraMargin.getY().getSize() <= 0 ){
			zonexyInneraMargin.setY( 
				aCDcdTargetMfcPrintInfo.getZone().getY() ) ;
		}

		aTargetInnerMargin.setZone( zonexyInneraMargin ) ;

	}

	//aTargetInnerMargin = 余白部分を除いた描画領域。
	//	単位はプリンタのピクセルです。

	// --------------------------------
	//	論理座標を設定
	// --------------------------------
	CaDcdTargetZoomDisplay	aCaDcdTargetZoomDisplay( 
		&aTargetInnerMargin , 
		aCDcdTargetMfcPrintInfo.getPrinterHdc() ) ;
	//aCaDcdTargetZoomDisplay = 余白部分を除いた描画領域。
	//	単位は、画面上の１ピクセル相当になりました。

	// --------------------------------
	//	キャプションとページ番号の部品を作成
	// --------------------------------
	Ou<CDcdText>	pdcdCaption ;
	Ou<CDcdText>	pdcdPage ;
	{
		const CentDedRosen* pCentDedRosen = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
		CJikokuhyouDoc* pCJikokuhyouDoc = (CJikokuhyouDoc*)GetDocument() ;

		string	strText ;
		//	路線名
		if ( !pCentDedRosen->getName().empty() ){
			strText += pCentDedRosen->getName() ;
			strText += " " ;

			CString	aString ;
			aString.LoadString( IDS_WORD_EKI ) ;
			strText += (LPCTSTR)aString ;
		}
		pdcdCaption = OuNew<CDcdText>( new CDcdText( 
			strText , getCdDrawTextPropStandard() ) ) ;
	}
	// --------------------------------
	{
		CdDrawTextProp	aProp = getCdDrawTextPropStandard() ;
		CdDrawTextFormat	aFormat = aProp.getCdDrawTextFormat() ;
		aFormat.setHorizontal( aFormat.H_CENTER ) ;
		aProp.setCdDrawTextFormat( aFormat ) ;
		pdcdPage = OuNew<CDcdText>( new CDcdText( "" ,aProp , "99" ) ) ;
	}

	// --------------------------------
	//	キャプションとページ番号の部品・
	//	グリッドのレイアウトを決める	
	// --------------------------------
	Ou<IfDcdTarget>	pTargetCaption ;
	Ou<IfDcdTarget>	pTargetGrid ;
	Ou<IfDcdTarget>	pTargetPage ;
	{
		CdDcdZoneXy	zoneGrid = aCaDcdTargetZoomDisplay.getZone() ;
		CdDcdSizeXy	aSize ;

		pdcdCaption->getItemSize( &aCaDcdTargetZoomDisplay , &aSize ) ;
		CdDcdZoneXy zoneCaption( zoneGrid.getX() , 
			CdDcdZone( zoneGrid.getY().getPos() , aSize.getY() ) ) ;
		zoneGrid.setY( CdDcdZone().setBeginEndPos( 
			zoneCaption.getY().getEndPos() , zoneGrid.getY().getEndPos() ) ) ;
		//zoneCaption = 全領域の上部を、キャプション用に割り当てています。
		//zoneGrid = 全領域から、上部のキャプション領域を除いた領域です。

		pdcdPage->getItemSize( &aCaDcdTargetZoomDisplay , &aSize ) ;
		CdDcdZoneXy zonePage( zoneGrid.getX() , 
			CdDcdZone( zoneGrid.getY().getEndPos() - aSize.getY() , aSize.getY() ) ) ;
		zoneGrid.setY( CdDcdZone().setBeginEndPos( 
			zoneCaption.getY().getEndPos() , zonePage.getY().getPos() ) ) ;
		//zonePage = 全領域の下部を、ページ用に割り当てています。
		//zoneGrid = 上部のキャプションに続いて、下部のページ領域も除いた領域です。


		pTargetCaption = OuNew<CaDcdTargetItemPosition>( 
			new CaDcdTargetItemPosition( &aCaDcdTargetZoomDisplay , zoneCaption ) ) ;
		pTargetGrid = OuNew<CaDcdTargetItemPosition>( 
			new CaDcdTargetItemPosition( &aCaDcdTargetZoomDisplay , zoneGrid ) ) ;
		pTargetPage = OuNew<CaDcdTargetItemPosition>(
			new CaDcdTargetItemPosition( &aCaDcdTargetZoomDisplay , zonePage ) ) ;
	}
	// --------------------------------
	//	グリッドを描画
	// --------------------------------
	int iPage = 0 ;
	{
		CDcdGrid*	pCDcdGrid = m_pCWndDcdGrid->getCXDcdGrid() ;
		CaDcdGrid_PageSelector	aCaDcdGrid_PageSelector( pCDcdGrid , pTargetGrid ) ;
		aCaDcdGrid_PageSelector.setPage( pInfo->m_nCurPage - 1 ) ;
		aCaDcdGrid_PageSelector.DcDraw() ;

		if ( (int)pInfo->m_nCurPage >= aCaDcdGrid_PageSelector.getPageCount() ){
			//最終ページを印刷したら、印刷ループを終わります。
			//OnPrint() で 
			//pInfo->SetMaxPage( aCaDcdGrid_PageSelector.getPageCount() ) ;
			//	をしても効果はありません。

			pInfo->m_bContinuePrinting = false ;
		}	else	{
			pInfo->m_bContinuePrinting = true ;
		}
		
		iPage = aCaDcdGrid_PageSelector.getPage() ;
	}
	// --------------------------------
	//	キャプションとページ番号のテキストを作成
	// --------------------------------
	{
		//ページ番号を決定
		{
			string	strPage = stringOf( iPage + 1) ;
			pdcdPage->setText( strPage ) ;
		}
	}
	// --------------------------------
	//	キャプションとページ番号を描画
	// --------------------------------
	{
			pdcdCaption->DcDraw( pTargetCaption ) ;
			pdcdPage->DcDraw( pTargetPage ) ;
	}
}


void CEkiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	//	印刷終了後に画面表示が崩れる問題を回避。
	//
	//	このクラスは、印刷中はグリッドのスクロール位置を
	//	一時的に変更します。
	//	このときに m_pCWndDcdGrid に再描画が発生すると、
	//	画面には一時的に位置の変更されたグリッドが
	//	描画されるため、画面が崩れます。
	m_pCWndDcdGrid->InvalidateGrid() ;

	CView::OnEndPrinting(pDC, pInfo);
}

void CEkiView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if ( m_pCWndDcdGrid != NULL )
	{
		m_pCWndDcdGrid->OnActivateView( bActivate , pActivateView , pDeactiveView ) ;
	}
	//CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

BOOL CEkiView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	//	コマンドハンドラは、可能なら CWndDcdGrid に委譲します。
	if ( m_pCWndDcdGrid != NULL && 
		m_pCWndDcdGrid->OnCmdMsg( nID , nCode , pExtra , pHandlerInfo ) )
	{
		return ( TRUE ) ;
	}
	
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

} //namespace ViewEki
