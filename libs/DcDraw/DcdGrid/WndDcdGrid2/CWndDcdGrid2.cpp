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
// CWndDcdGrid2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "CWndDcdGrid2.h"
#include "CWndDcdGrid2_CXDcdGrid.h"
#include "CWndDcdGrid2_CFocus.h"
#include "CWndDcdGrid2_CSelect.h"
#include "Ou/OuNew.h"
#include "DcDraw/CDcdTargetGetDC.h"
#include "DcDraw/CDcdTargetOnPaint.h"
#include "DcDraw/CaDcdTargetItemPosition.h"
#include "DcDraw/CDcdRectangle.h"
#include "LogMsg/LogMsg.h"
#include "CWndDcdGrid2_CWndDcdGrid2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace DcDrawLib{
namespace DcdGrid{
namespace WndDcdGrid2{


/////////////////////////////////////////////////////////////////////////////
// CWndDcdGrid2

///	「領域外ドラッグスクロール」のタイマID
const UINT_PTR OutsideDrag_TIMERID = 1 ;

// --------------------------------
//@name	下請関数
// --------------------------------
bool CWndDcdGrid2::update() 
{
	bool bRv = false ;
	if ( !m_bDisable_UpdateAll )
	{
		m_bDisable_UpdateAll = true ;
		// --------------------------------
		bRv |= m_pCDcdGrid->update_adjustProp() ;
		bRv |= m_pCFocus->update_adjustProp() ;
		bRv |= m_pCSelect->update_adjustProp() ;
		// --------------------------------
		bRv |= m_pCDcdGrid->update_updateScreen() ;
		bRv |= m_pCFocus->update_updateScreen() ;
		bRv |= m_pCSelect->update_updateScreen() ;
		// --------------------------------
		m_bDisable_UpdateAll = false ;
	}
	return ( bRv ) ;
}
// ********************************
//	コンストラクタ
// ********************************
CWndDcdGrid2::CWndDcdGrid2()
	: m_iOutsideDrag_TimeMs( 100 )
	, m_bOutsideDrag_TimerOn( false ) 
	, m_bDisable_UpdateAll( false ) 
	, m_bLButtonIsDown( false ) 
{
	m_pCDcdGrid = new CXDcdGrid( this ) ;

	m_pCFocus = new CFocus( this ) ;

	m_pCSelect = new CSelect( this ) ;
}

CWndDcdGrid2::~CWndDcdGrid2()
{
	delete m_pCSelect ;
	m_pCSelect = NULL ;

	delete m_pCFocus ;
	m_pCFocus = NULL ;

	delete m_pCDcdGrid ;
	m_pCDcdGrid = NULL ;
}

// ********************************
//	CDcdGrid
// ********************************
	// --------------------------------
	//@name 行・列・セルの初期化
	// --------------------------------
void CWndDcdGrid2::OnCreateXColumn( int iXColumnNumber , 
		CDcdGridXColumn* pCDcdGridXColumn ) 
{
	m_pCDcdGrid->CDcdGrid::OnCreateXColumn( iXColumnNumber , 
		pCDcdGridXColumn ) ;
}
	
void CWndDcdGrid2::OnDeleteXColumn( int iXColumnNumber , 
		CDcdGridXColumn* pCDcdGridXColumn ) 
{
	m_pCDcdGrid->CDcdGrid::OnDeleteXColumn( iXColumnNumber , 
		pCDcdGridXColumn ) ;
}

void CWndDcdGrid2::OnCreateYColumn( int iYColumnNumber , 
		CDcdGridYColumn* pCDcdGridYColumn ) 
{
	m_pCDcdGrid->CDcdGrid::OnCreateYColumn( iYColumnNumber , 
		pCDcdGridYColumn ) ;
}

void CWndDcdGrid2::OnDeleteYColumn( int iYColumnNumber , 
		CDcdGridYColumn* pCDcdGridYColumn ) 
{
	m_pCDcdGrid->CDcdGrid::OnDeleteYColumn( iYColumnNumber , 
		pCDcdGridYColumn ) ;
}

void CWndDcdGrid2::OnCreateCell( int iXColumnNumber , int iYColumnNumber , 
		CDcdGridCell* pCDcdGridCell ) 
{
	m_pCDcdGrid->CDcdGrid::OnCreateCell( 
		iXColumnNumber , iYColumnNumber , 
		pCDcdGridCell ) ;
}
	
void CWndDcdGrid2::OnDeleteCell( int iXColumnNumber , int iYColumnNumber , 
		CDcdGridCell* pCDcdGridCell ) 
{
	m_pCDcdGrid->CDcdGrid::OnDeleteCell( 
		iXColumnNumber , iYColumnNumber , 
		pCDcdGridCell ) ;
}

	// ********************************
	//	@name Y列・X列の位置
	// ********************************
CdDcdZone	CWndDcdGrid2::getYColumnZone( 
			int iYColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getYColumnZone( 
			&aCDcdTarget , iYColumnNumber ) ;
};
		
CdDcdZone	CWndDcdGrid2::getXColumnZone( 
			int iXColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getXColumnZone( 
			&aCDcdTarget  , iXColumnNumber ) ;
};
	
CdDcdZone	CWndDcdGrid2::getYColumnBorderZone( 
			int iYColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getYColumnBorderZone( 
			&aCDcdTarget  , iYColumnNumber ) ;
};

CdDcdZone	CWndDcdGrid2::getXColumnBorderZone( 
			int iXColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getXColumnBorderZone( 
			 &aCDcdTarget  , iXColumnNumber ) ;
};

CdDcdZoneXy	CWndDcdGrid2::getCellZone( 
		int iXColumnNumber , int iYColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getCellZone( 
			&aCDcdTarget  , iXColumnNumber , iYColumnNumber ) ;
};
	

int CWndDcdGrid2::getYColumnNumberOfPos( 
		int iPos , bool* pbIsBorder ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getYColumnNumberOfPos( 
			&aCDcdTarget  , iPos , pbIsBorder ) ;
};

int CWndDcdGrid2::getXColumnNumberOfPos( 
		int iPos , bool* pbIsBorder ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getXColumnNumberOfPos( 
			&aCDcdTarget  , iPos , pbIsBorder ) ;
};


CDcdGridCell* CWndDcdGrid2::getCellOfPos( 
		const CdDcdPosXy& aCdDcdPosXy ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getCellOfPos( 
			&aCDcdTarget  , aCdDcdPosXy ) ;
};

CdDcdSizeXy CWndDcdGrid2::calcIncreaseOnOutsideDrag( const POINT& pos ) 
{
	CdDcdSizeXy	sizeFixafterColumnNumberIncrease ;

	CRect	rectClient ;
	GetClientRect( &rectClient ) ; 

	//	フォーカスセルの列番号
	CdDcdPosXy	posFocusCellColumnNumber = getCFocus()->getFocusCellColumnNumber() ;

	//	X方向
	if ( m_pCDcdGrid->getXFixColumnCount() <= posFocusCellColumnNumber.getX() &&
		posFocusCellColumnNumber.getX() < m_pCDcdGrid->getXColumnCount() )
	{
		//	フォーカスセルが、スクロール可能列にある

		//	[左へのスクロールが可能(FixColumnCount < FixafterColumnNumber)
		//	AND マウスカーソルのX座標が、FixColumn上より左 ]
		//	タイマでの右スクロール
		if ( m_pCDcdGrid->getXFixColumnCount() < m_pCDcdGrid->getXFixafterColumnNumber() )	//	左へのスクロールが可能
		{
			int iScrollColumnStartPos = rectClient.left ;
			if ( m_pCDcdGrid->getXFixColumnCount() > 0 )
			{
				CdDcdZone	aZone = getXColumnBorderZone( m_pCDcdGrid->getXFixColumnCount() - 1 ) ;
				if ( iScrollColumnStartPos < aZone.getEndPos() )
				{
					iScrollColumnStartPos = aZone.getEndPos() ;
				}
			}
			//	iScrollColumnStartPos = スクロール可能列の左側のX座標
			if ( pos.x < iScrollColumnStartPos )
			{
				//	左への「領域外ドラッグスクロール」が必要な状況
				sizeFixafterColumnNumberIncrease.setX( -1 );
			}
		}
		//	[右へのスクロールが可能( FixafterColumnNumber < ColumnCount - 1 )
		//	AND マウスカーソルのX座標が、Grid・またはウインドウのクライアント座標より右 ]
		//	タイマでの左スクロール
		if ( m_pCDcdGrid->getXFixafterColumnNumber() < m_pCDcdGrid->getXColumnCount() - 1 )	//	右へのスクロールが可能
		{
			int iScrollColumnEndPos = rectClient.right ;
			{
				CdDcdZone	aZone = getXColumnBorderZone( m_pCDcdGrid->getXColumnCount() - 1 ) ;
				if ( iScrollColumnEndPos > aZone.getPos() ) 
				{
					iScrollColumnEndPos = aZone.getPos() ;
				}
			}
			if ( iScrollColumnEndPos < pos.x )
			{
				//	右への「領域外ドラッグスクロール」が必要な状況
				sizeFixafterColumnNumberIncrease.setX( +1 );
			}
		}
	}

	//	Y方向
	if ( m_pCDcdGrid->getYFixColumnCount() <= posFocusCellColumnNumber.getY() &&
		posFocusCellColumnNumber.getY() < m_pCDcdGrid->getYColumnCount() )
	{
		//	フォーカスセルが、スクロール可能列にある

		//	[上へのスクロールが可能(FixColumnCount < FixafterColumnNumber)
		//	AND マウスカーソルのY座標が、FixColumn上より上 ]
		//	タイマでの右スクロール
		if ( m_pCDcdGrid->getYFixColumnCount() < m_pCDcdGrid->getYFixafterColumnNumber() )	//	左へのスクロールが可能
		{
			int iScrollColumnStartPos = rectClient.top ;
			if ( m_pCDcdGrid->getYFixColumnCount() > 0 )
			{
				CdDcdZone	aZone = getYColumnBorderZone( m_pCDcdGrid->getYFixColumnCount() - 1 ) ;
				if ( iScrollColumnStartPos < aZone.getEndPos() )
				{
					iScrollColumnStartPos = aZone.getEndPos() ;
				}
			}
			//	iScrollColumnStartPos = スクロール可能列の上側のY座標
			if ( pos.y < iScrollColumnStartPos )
			{
				//	上への「領域外ドラッグスクロール」が必要な状況
				sizeFixafterColumnNumberIncrease.setY( -1 );
			}
		}
		//	[右へのスクロールが可能( FixafterColumnNumber < ColumnCount - 1 )
		//	AND マウスカーソルのY座標が、Columnより下、またはウインドウより下 ]
		//	タイマでの左スクロール
		if ( m_pCDcdGrid->getYFixafterColumnNumber() < m_pCDcdGrid->getYColumnCount() - 1 )	//	右へのスクロールが可能
		{
			int iScrollColumnEndPos = rectClient.bottom ;
			{
				CdDcdZone	aZone = getYColumnBorderZone( m_pCDcdGrid->getYColumnCount() - 1 ) ;
				if ( iScrollColumnEndPos > aZone.getPos() ) 
				{
					iScrollColumnEndPos = aZone.getPos() ;
				}
			}
			//	iScrollColumnStartPos = スクロール可能列の上側のY座標
			if ( iScrollColumnEndPos < pos.y )
			{
				//	下への「領域外ドラッグスクロール」が必要な状況
				sizeFixafterColumnNumberIncrease.setY( +1 );
			}
		}
	}

	return sizeFixafterColumnNumberIncrease ;
}
	// ********************************
	//	@name	セルの結合
	// ********************************
CdDcdZone	CWndDcdGrid2::getYColumnZoneOverlap( 
			int iYColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getYColumnZoneOverlap( 
			&aCDcdTarget  , iYColumnNumber ) ;
}
CdDcdZone	CWndDcdGrid2::getXColumnZoneOverlap( 
			int iXColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getXColumnZoneOverlap( 
			&aCDcdTarget  , iXColumnNumber ) ;
}

CdDcdZoneXy	CWndDcdGrid2::getCellZoneOverlap( 
		int iXColumnNumber , int iYColumnNumber ) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	return m_pCDcdGrid->getCellZoneOverlap( 
		&aCDcdTarget  , iXColumnNumber , iYColumnNumber ) ;
}
// ********************************
//	@name	操作
// ********************************

// ********************************
//	CWndDcdGrid2
// ********************************
	// --------------------------------
	//@name	イベント処理のための仮想関数
	// --------------------------------
void CWndDcdGrid2::OnSetFocusCell( CDcdGridCell* pcdcdgridcell ) 
{
	if ( pcdcdgridcell!= NULL ){
		LogMsg( "onsetfocuscell( x=%d y=%d )" , 
			m_pCDcdGrid->getXColumnNumberOfCell( pcdcdgridcell ) ,
			m_pCDcdGrid->getYColumnNumberOfCell( pcdcdgridcell ) ) ;
	}	else	{
		LogMsg( "onsetfocuscell( null )" ) ;
	}
}
void CWndDcdGrid2::OnSetXFixafterColumnNumber( int iFixafterColumnNumber ) 
{
	LogMsg( "CWndDcdGrid2::OnSetXFixafterColumnNumber(%d)" , 
		iFixafterColumnNumber ) ;
}
void CWndDcdGrid2::OnSetYFixafterColumnNumber( int iFixafterColumnNumber ) 
{
	LogMsg( "CWndDcdGrid2::OnSetYFixafterColumnNumber(%d)" , 
		iFixafterColumnNumber ) ;
}

void CWndDcdGrid2::OnSetColumnNumberSelect( const CdDcdZoneXy& aColumnNumberSelect ) 
{
}

	// ********************************
	//@name 関連
	// ********************************

	// ********************************
	//@name 包含
	// ********************************
CWndDcdGrid2::CXDcdGrid*	CWndDcdGrid2::getCXDcdGrid() 
{
	return m_pCDcdGrid ;
}
CWndDcdGrid2::CFocus*	CWndDcdGrid2::getCFocus() 
{
	return m_pCFocus ;
}

CWndDcdGrid2::CSelect*	CWndDcdGrid2::getCSelect() 
{
	return m_pCSelect ;
}

	// ********************************
	//@name	構築
	// ********************************
BOOL CWndDcdGrid2::Create( 
	const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	return CreateEx( 0 
		, AfxRegisterWndClass( CS_DBLCLKS //| CS_HREDRAW | CS_VREDRAW 
			, LoadCursor( NULL , IDC_ARROW ) 
			, (HBRUSH)GetStockObject( WHITE_BRUSH ) 
			, NULL ) 
		, "CWndDcdGrid2"	//	この文字列が表示されることはありません
		, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP
		, rect
		, pParentWnd
		, nID
		, NULL ) ;
}

BOOL CWndDcdGrid2::Create( CWnd* pParentWnd, UINT nID )
{
	return CreateEx( 0 
		, AfxRegisterWndClass( CS_DBLCLKS //| CS_HREDRAW | CS_VREDRAW 
			, LoadCursor( NULL , IDC_ARROW ) 
			, (HBRUSH)GetStockObject( WHITE_BRUSH ) 
			, NULL ) 
		, "CWndDcdGrid2"	//	この文字列が表示されることはありません
		, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP
		, CRect( 0 , 0 , 0 , 0 ) 
		, pParentWnd
		, nID
		, NULL ) ;
}

	// ********************************
	//@name	操作
	// ********************************
int  CWndDcdGrid2::InvalidateXColumnBorder( int iXColumnNumber , 
	bool bErase ) 
{
	int iRv = 0 ;

	// --------------------------------
	//	再描画領域を求める
	// --------------------------------
	CRect	rectClient ;
	CdDcdZone	zoneClient ;
	if ( iRv >= 0 ){
		GetClientRect( &rectClient ) ;
		zoneClient.setPos( rectClient.left ).setSize( rectClient.right - rectClient.left ) ;
	}
	//rectClient = クライアント領域の矩形
	//zoneClient = クライアント領域の幅

	CdDcdZone	zoneInvalidate ;
	if ( iRv >= 0 ){
		CdDcdZone	zoneBorder = getXColumnBorderZone( iXColumnNumber ) ;
		zoneInvalidate = zoneBorder.CrossZone( zoneClient ) ;
	}
	//zoneInvalidate = クライアント領域中で、境界線領域
	
	// --------------------------------
	//	再描画
	// --------------------------------
	if ( iRv >= 0 ){
		if ( zoneInvalidate.getSize() > 0 ){
			CRect	rectInvalidate = rectClient ;
			rectInvalidate.left = zoneInvalidate.getPos() ;
			rectInvalidate.right = zoneInvalidate.getEndPos() ;
			InvalidateRect( rectInvalidate , bErase ) ;
			iRv = 1 ;
		}
	}	
	

	return ( iRv ) ;
	
}

int CWndDcdGrid2::InvalidateYColumnBorder( int iYColumnNumber ,
	bool bErase ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	再描画領域を求める
	// --------------------------------
	CRect	rectClient ;
	CdDcdZone	zoneClient ;
	if ( iRv >= 0 ){
		GetClientRect( &rectClient ) ;
		zoneClient.setPos( rectClient.top ).setSize( rectClient.bottom - rectClient.top ) ;
	}
	//rectClient = クライアント領域の矩形
	//zoneClient = クライアント領域の幅

	CdDcdZone	zoneInvalidate ;
	if ( iRv >= 0 ){
		CdDcdZone	zoneBorder = getYColumnBorderZone( iYColumnNumber ) ;
		zoneInvalidate = zoneBorder.CrossZone( zoneClient ) ;
	}
	//zoneInvalidate = クライアント領域中で、境界線領域
	
	// --------------------------------
	//	再描画
	// --------------------------------
	if ( iRv >= 0 ){
		if ( zoneInvalidate.getSize() > 0 ){
			CRect	rectInvalidate = rectClient ;
			rectInvalidate.top = zoneInvalidate.getPos() ;
			rectInvalidate.bottom = zoneInvalidate.getEndPos() ;
			InvalidateRect( rectInvalidate , bErase ) ;
			iRv = 1 ;
		}
	}	
	

	return ( iRv ) ;
}

int CWndDcdGrid2::InvalidateCell( int iXColumnNumber , int iYColumnNumber , 
	bool bErase ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	再描画領域を求める
	// --------------------------------
	CRect	rectClient ;
	CdDcdZoneXy	zoneClient ;
	if ( iRv >= 0 ){
		GetClientRect( &rectClient ) ;
		zoneClient.setX( CdDcdZone( rectClient.left , rectClient.right - rectClient.left ) )
			.setY( CdDcdZone( rectClient.top , rectClient.bottom - rectClient.top ) ) ;
	}
	//rectClient = クライアント領域の矩形
	//zoneClient = クライアント領域の幅

	CdDcdZoneXy	zoneInvalidate ;
	if ( iRv >= 0 ){
		CdDcdZoneXy	zoneCell = getCellZone( iXColumnNumber , iYColumnNumber ) ;
		zoneInvalidate = zoneCell.CrossZone( zoneClient ) ;
	}
	//zoneInvalidate = クライアント領域中で、境界線領域
	
	// --------------------------------
	//	再描画
	// --------------------------------
	if ( iRv >= 0 ){
		if ( zoneInvalidate.getX().getSize() > 0 && 
				zoneInvalidate.getY().getSize() > 0 ){
			CRect	rectInvalidate = rectClient ;
			rectInvalidate.left = zoneInvalidate.getX().getPos() ;
			rectInvalidate.right = zoneInvalidate.getX().getEndPos() ;
			rectInvalidate.top = zoneInvalidate.getY().getPos() ;
			rectInvalidate.bottom = zoneInvalidate.getY().getEndPos() ;
			InvalidateRect( rectInvalidate , bErase ) ;
			iRv = 1 ;
		}
	}	
	
	return ( iRv ) ;
}

 void CWndDcdGrid2::InvalidateGrid( 
		bool bFixafterColumnNumberChange , 
		bool bErase )
{
	m_pCDcdGrid->InvalidateGrid( bFixafterColumnNumberChange , bErase ) ;
	m_pCFocus->InvalidateGrid( bFixafterColumnNumberChange , bErase ) ;
	m_pCSelect->InvalidateGrid() ;
	
	super::Invalidate( bErase ) ;

	//	全体の属性を更新
	update() ;
 }

	// ********************************
	//@name CWndDcdGrid2-フォーカス
	// ********************************
// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGrid2, CWnd)
	//{{AFX_MSG_MAP(CWndDcdGrid2)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndDcdGrid2 メッセージ ハンドラ

void CWndDcdGrid2::OnPaint() 
{
	// --------------------------------
	//	描画
	// --------------------------------
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト
		
		CDcdTargetOnPaint	aCDcdTarget( GetSafeHwnd() , &dc.m_ps ) ;
		
		{
			CdDcdZoneXy	aDrawableZone = aCDcdTarget.getDrawableZone() ;
			LogMsgL( 3 , "CWndDcdGrid2::OnPaint() x=%d,%d y=%d,%d" ,
				aDrawableZone.getX().getPos() , 
				aDrawableZone.getX().getSize() , 
				aDrawableZone.getY().getPos() , 
				aDrawableZone.getY().getSize() ) ;
		}
		// --------------------------------	
		//	Grid
		// --------------------------------	
		m_pCDcdGrid->DcDraw( &aCDcdTarget );
		
		// --------------------------------	
		//	フォーカスマーク
		// --------------------------------	
		m_pCFocus->OnPaint(  &aCDcdTarget ) ;

		// --------------------------------	
		//	選択マーク
		// --------------------------------	
		m_pCSelect->OnPaint(  &aCDcdTarget ) ;


	}
}


/**
@return
	SHIFTキーが押されていたらtrue 
*/
static bool isShiftPressed()
{
	bool bShiftPressed = false ;
	{
		SHORT	iVal = GetKeyState( VK_SHIFT ) ;
		bShiftPressed = ( ( iVal & 0x8000 ) != 0 ) ;
	}
	//bShiftPressed = Shiftキーが押されていたらtrue
	return bShiftPressed ;
}

void CWndDcdGrid2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	
	SCROLLINFO	aSCROLLINFO ;
	memset ( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
	aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;
	aSCROLLINFO.fMask = SIF_ALL ;
	GetScrollInfo( SB_HORZ , &aSCROLLINFO , SIF_ALL ) ;
	
	if ( pScrollBar == NULL )
	{
		switch( nSBCode )
		{
		 case SB_LINELEFT:
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( m_pCDcdGrid->getXFixafterColumnNumber() - 1 ) ;
				}
			}
			break ; 
		 case SB_LINERIGHT:
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( m_pCDcdGrid->getXFixafterColumnNumber() + 1 ) ;
				}
			}
			break ; 
		 case SB_PAGELEFT:
			{
				int iFixafterColumnNumber = m_pCDcdGrid->getXFixafterColumnNumber() ;
				int iFixafterColumnNumberNew = m_pCDcdGrid->
					calcXFixafterColumnNumberPagemove( &aCDcdTarget , 
						iFixafterColumnNumber , false ) ;
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( iFixafterColumnNumberNew ) ;
				}
			}
			break ;
		 case SB_PAGERIGHT:
			{
				int iFixafterColumnNumber = m_pCDcdGrid->getXFixafterColumnNumber() ;
				int iFixafterColumnNumberNew = m_pCDcdGrid->
					calcXFixafterColumnNumberPagemove( &aCDcdTarget , 
						iFixafterColumnNumber , true ) ;
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( iFixafterColumnNumberNew ) ;
				}
			}
			break ;
		 case SB_THUMBPOSITION :
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( nPos ) ;
				}
			}
			break ;
		 case SB_THUMBTRACK :
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setXFixafterColumnNumber( nPos ) ;
				}
			}
			break ;
		 case SB_ENDSCROLL:
			{
			}
			break ;
		}
	}
	else
	{
		super::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}	

void CWndDcdGrid2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;
	
	SCROLLINFO	aSCROLLINFO ;
	memset ( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
	aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;
	aSCROLLINFO.fMask = SIF_ALL ;
	GetScrollInfo( SB_VERT , &aSCROLLINFO , SIF_ALL ) ;
	
	if ( pScrollBar == NULL )
	{
		switch( nSBCode )
		{
		 case SB_LINEUP:
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( m_pCDcdGrid->getYFixafterColumnNumber() - 1 ) ;
				}
			}
			break ; 
		 case SB_LINEDOWN:
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( m_pCDcdGrid->getYFixafterColumnNumber() + 1 ) ;
				}
			}
			break ; 
		 case SB_PAGEUP:
			{
				int iFixafterColumnNumber = m_pCDcdGrid->getYFixafterColumnNumber() ;
				int iFixafterColumnNumberNew = m_pCDcdGrid->
					calcYFixafterColumnNumberPagemove( &aCDcdTarget , 
						iFixafterColumnNumber , false ) ;
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( iFixafterColumnNumberNew ) ;
				}
			}
			break ;
		 case SB_PAGEDOWN:
			{
				int iFixafterColumnNumber = m_pCDcdGrid->getYFixafterColumnNumber() ;
				int iFixafterColumnNumberNew = m_pCDcdGrid->
					calcYFixafterColumnNumberPagemove( &aCDcdTarget , 
						iFixafterColumnNumber , true ) ;
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( iFixafterColumnNumberNew ) ;
				}
			}
			break ;
		 case SB_THUMBPOSITION :
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( nPos ) ;
				}
			}
			break ;
		 case SB_THUMBTRACK :
			{
				{
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
					m_pCDcdGrid->setYFixafterColumnNumber( nPos ) ;
				}
			}
			break ;
		 case SB_ENDSCROLL:
			{
			}
			break ;
		}
	}
	else
	{
		super::OnVScroll(nSBCode, nPos, pScrollBar);
	}
	
}

void CWndDcdGrid2::OnSize(UINT nType, int cx, int cy) 
{
	
	if ( cx == 0 || cy == 0 )
	{
		//	この２つのうちのいずれかが0の場合、それは
		//	Create() でサイズを指定せずにウインドウを
		//	生成したものと思われます。
		//	この場合は、ユーザーには何も見えないわけですから、
		//	フォーカスセルの位置の最適化などはおこなう
		//	必要がありません。
		//
		//	また、この大きさのときに adjustProp() を
		//	行うと、フォーカス位置は無条件に (0,0) に
		//	移動してしまいます。このため、
		//	adjustProp() はしない方が
		//	よいでしょう。
		return ;
	}
	//	集約インスタンスに委譲
	m_pCFocus->OnSize( nType, cx, cy) ;
	m_pCSelect->OnSize( nType, cx, cy) ;
	super::OnSize(nType, cx, cy);

	{
		CPropStack	aPropStack( 
			this , 
			false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
			false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
			false ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
		update() ;
	}

}

void CWndDcdGrid2::OnSetFocus(CWnd* pOldWnd) 
{
	//	集約インスタンスに委譲
	m_pCFocus->OnSetFocus( pOldWnd ) ;
	m_pCSelect->OnSetFocus( pOldWnd ) ;

	super::OnSetFocus(pOldWnd);
}

void CWndDcdGrid2::OnKillFocus(CWnd* pNewWnd) 
{
	//(3.1)ウインドウフォーカスを失った場合は、マウスキャプチャOFF
	//	マウスのキャプチャ解放
	ReleaseCapture() ;

	//	「領域外ドラッグスクロール」タイマを解放します。
	if ( m_bOutsideDrag_TimerOn )
	{
		KillTimer( OutsideDrag_TIMERID ) ;
		m_bOutsideDrag_TimerOn = false ;
	}

	//	フォーカスを失ったときには、
	//	左ボタン押し下げを解除。
	m_bLButtonIsDown = false ;

	//	集約インスタンスに委譲
	m_pCFocus->OnKillFocus( pNewWnd ) ;
	m_pCSelect->OnKillFocus( pNewWnd ) ;

	super::OnKillFocus(pNewWnd);
}

void CWndDcdGrid2::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//	フォーカスを失ったときには、
	//	左ボタン押し下げを解除。
	m_bLButtonIsDown = true ;


	//(4.1)マウス左ボタン押し下げ(LButtonDown)
	//　マウスのキャプチャON
	//	フォーカスを移動
	if ( m_bLButtonIsDown )	//   マウスの左ボタンが押されている場合に設定します。
	{
		//　マウスのキャプチャON
		SetCapture() ;

		//	「領域外ドラッグスクロール」のタイマーON
		SetTimer( OutsideDrag_TIMERID , m_iOutsideDrag_TimeMs , NULL ) ;
		m_bOutsideDrag_TimerOn = true ;

		//	フォーカスセルをカーソル位置に移動
		CDcdGridCell*	pCell = getCellOfPos( CdDcdPosXy( point.x , point.y ) ) ;
		if ( pCell != NULL )
		{
			SetFocus() ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCFocus->setFocusCell( pCell ) ;
			}
		}
	}
	
	super::OnLButtonDown(nFlags, point);
}
void CWndDcdGrid2::OnLButtonUp(UINT nFlags, CPoint point)
{
	//((4.2)マウス左ボタン解放(LButtonUp)
	//	マウスのキャプチャ解放
	ReleaseCapture() ;

	//	「領域外ドラッグスクロール」タイマを解放します。
	if ( m_bOutsideDrag_TimerOn )
	{
		KillTimer( OutsideDrag_TIMERID ) ;
		m_bOutsideDrag_TimerOn = false ;
	}

	//	左ボタン押し下げを解除。
	m_bLButtonIsDown = false ;

	CWnd::OnLButtonUp(nFlags, point);
}

void CWndDcdGrid2::OnMouseMove(UINT nFlags, CPoint point)
{
	//(4.1)マウス左ボタン押し下げ(LButtonDown)
	//　マウスのキャプチャON
	//	カーソルがGrid内にあれば、
	//	フォーカスセルをカーソル位置に移動
	if ( m_bLButtonIsDown )	//   マウスの左ボタンが押されている場合に設定します。
	{

		//	カーソルが「領域外ドラッグスクロール」の
		//	必要な位置にあるか否かを調べます。
		CdDcdSizeXy	sizeFixafterColumnNumberIncrease = 
			calcIncreaseOnOutsideDrag( point ) ;
		if ( sizeFixafterColumnNumberIncrease.getX() != 0 ||
			sizeFixafterColumnNumberIncrease.getY() != 0 )
		{
			//	「領域外ドラッグスクロール」が
			//	必要な場合は、フォーカスの移動は行いません
			//	(OnTimer()で、フォーカスの移動を行います)
		}
		else
		{
			CRect rectClient ;
			GetClientRect( &rectClient ) ;
			if ( rectClient.left <= point.x && point.x < rectClient.right && 
				rectClient.top <= point.y && point.y < rectClient.bottom )
			{
				//	マウスがクライアント領域内なら、
				//	フォーカスセルをカーソル位置に移動
				CDcdGridCell*	pCell = getCellOfPos( CdDcdPosXy( point.x , point.y ) ) ;
				if ( pCell != NULL )
				{
					{
						//	スクロール位置を更新します。
						//	アンカーセルは、保持します
						CPropStack	aPropStack( 
							this , 
							false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
							true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
							true ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false

						m_pCFocus->setFocusCell( pCell ) ;
						// --------------------------------
						//	集約オブジェクトからの updateAll() 再許可
						_ASSERT( !m_bDisable_UpdateAll ) ;
						m_bDisable_UpdateAll = false ;

						// --------------------------------
					}
				}
			}
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CWndDcdGrid2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDcdTargetGetDC	aCDcdTarget( GetSafeHwnd() ) ;

	bool bShiftPressed = isShiftPressed() ;

	switch( nChar ){
	 case VK_LEFT :	
		{
			CDcdGridCell*	pCell = m_pCDcdGrid->calcMovedCell( 
				m_pCFocus->getFocusCell() , -1 , 0 ) ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					bShiftPressed ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCFocus->setFocusCell( pCell ) ;
				
			}
		}
		break ;
	 case VK_RIGHT :	
		{
			CDcdGridCell*	pCell = m_pCDcdGrid->calcMovedCell( 
				m_pCFocus->getFocusCell() , +1 , 0 ) ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					bShiftPressed ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCFocus->setFocusCell( pCell ) ;
			}
		}
		break ;
	 case VK_UP :	
		{
			CDcdGridCell*	pCell = m_pCDcdGrid->calcMovedCell( 
				m_pCFocus->getFocusCell() , 0 , -1 ) ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					bShiftPressed ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCFocus->setFocusCell( pCell ) ;
			}
		}
		break ;
	 case VK_DOWN :	
		{
			CDcdGridCell*	pCell = m_pCDcdGrid->calcMovedCell( 
				m_pCFocus->getFocusCell() , 0 , +1 ) ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					bShiftPressed ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCFocus->setFocusCell( pCell ) ;
			}
		}
		break ;
	 case VK_PRIOR ://PageUp	
		{
			//	VK_SHIFT が押されていません。
			//	Y 方向の PageUPです
			int iFixafterColumnNumber = m_pCDcdGrid->getYFixafterColumnNumber() ;
			int iFixafterColumnNumberNew = m_pCDcdGrid->
				calcYFixafterColumnNumberPagemove( &aCDcdTarget , 
					iFixafterColumnNumber , false ) ;

			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCDcdGrid->setYFixafterColumnNumber( iFixafterColumnNumberNew ) ;
			}
			
		}
		break ;
	 case VK_NEXT :	//PageDown	
		{
			//	Y 方向の PageDownです
			int iFixafterColumnNumber = m_pCDcdGrid->getYFixafterColumnNumber() ;
			int iFixafterColumnNumberNew = m_pCDcdGrid->
				calcYFixafterColumnNumberPagemove( &aCDcdTarget , 
					iFixafterColumnNumber , true ) ;
			
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCDcdGrid->setYFixafterColumnNumber( iFixafterColumnNumberNew ) ;
			}
		}
		break ;
	 case VK_HOME :
		{
			//	VK_SHIFT が押されています。
			//	X 方向の PageUPです

			int iFixafterColumnNumber = m_pCDcdGrid->getXFixafterColumnNumber() ;
			int iFixafterColumnNumberNew = m_pCDcdGrid->
				calcXFixafterColumnNumberPagemove( &aCDcdTarget , 
					iFixafterColumnNumber , false ) ;

			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCDcdGrid->setXFixafterColumnNumber( iFixafterColumnNumberNew ) ;
			}
		}
		break ;
	 case VK_END :
		{
			//	VK_SHIFT が押されています。
			//	X 方向の PageDownです
			int iFixafterColumnNumber = m_pCDcdGrid->getXFixafterColumnNumber() ;
			int iFixafterColumnNumberNew = m_pCDcdGrid->
				calcXFixafterColumnNumberPagemove( &aCDcdTarget , 
					iFixafterColumnNumber , true ) ;
			{
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
				m_pCDcdGrid->setXFixafterColumnNumber( iFixafterColumnNumberNew ) ;
			}			
		}
		break ;

	 default:
		{
			super::OnKeyDown(nChar, nRepCnt, nFlags);
		}
	}
	
}

int CWndDcdGrid2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CWndDcdGrid2::OnDestroy() 
{
	CWnd::OnDestroy();
}


BOOL CWndDcdGrid2::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if ( nFlags == 0 )
	{
		int iYMove = zDelta / (-WHEEL_DELTA) ;
		//iYMove = Y方向に移動する数。
		{
			//	スクロール位置に合わせてフォーカス位置を更新します。
			//	アンカーセルは、Shiftが押されていたら保持します。
			//	Shiftが押されていない場合は更新します。
			CPropStack	aPropStack( 
				this , 
				false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
				false ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
				isShiftPressed() ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false
			m_pCDcdGrid->setYFixafterColumnNumber( m_pCDcdGrid->getYFixafterColumnNumber() + iYMove ) ;
		}

		return ( TRUE ) ;
	}	
	return super::OnMouseWheel(nFlags, zDelta, pt);
}



void CWndDcdGrid2::OnTimer(UINT_PTR nIDEvent)
{
	//	「領域外ドラッグスクロール」
	if ( nIDEvent == OutsideDrag_TIMERID )
	{
		CPoint	point ;
		GetCursorPos( &point ) ;
		ScreenToClient( &point ) ;

		//	カーソルが「領域外ドラッグスクロール」の
		//	必要な位置にあるか否かを調べます。
		CdDcdSizeXy	sizeFixafterColumnNumberIncrease = 
			calcIncreaseOnOutsideDrag( point ) ;
		if ( sizeFixafterColumnNumberIncrease.getX() != 0 ||
			sizeFixafterColumnNumberIncrease.getY() != 0 )
		{
			//	「領域外ドラッグスクロール」が
			//	必要な場合は、スクロールを行います。

			//// --------------------------------
			////	FixafterColumnNumberを変化させる方法。
			////	フォーカスセルがついてこないという欠点があります。
			//// --------------------------------
			//setXFixafterColumnNumber( getXFixafterColumnNumber() + sizeFixafterColumnNumberIncrease.getX() ) ;
			//setYFixafterColumnNumber( getYFixafterColumnNumber() + sizeFixafterColumnNumberIncrease.getY() ) ;

			// --------------------------------
			//	フォーカスセルを移動させる方法
			// --------------------------------
			CDcdGridCell*	pCell = m_pCFocus->getFocusCell() ;
			if ( pCell != NULL )
			{
				pCell = m_pCDcdGrid->calcMovedCell( pCell , 
					sizeFixafterColumnNumberIncrease.getX() , 
					sizeFixafterColumnNumberIncrease.getY() ) ; 

				{
					//	スクロール位置を更新します。
					//	アンカーセルは、保持します(このタイマが有効な場合は
					//	ドラッグ中のため)。
					CPropStack	aPropStack( 
						this , 
						false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
						true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
						true ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false

					m_pCFocus->setFocusCell( pCell ) ;
				}
			}
		}
	}
	else
	{
		CWnd::OnTimer(nIDEvent);
	}
}


void CWndDcdGrid2::OnRButtonDown(UINT nFlags, CPoint point)
{
	//	フォーカスセルを移動します。
	//	この処理は、右ポタンによるコンテキストメニューを動作させるのに必要です

	//	右ボタンが押されたときは、このウインドウに明示的に
	//	フォーカスを設定する必要があります。
	//
	//【理由】
	//	このウインドウが開いた直後は、このウインドウは
	//	フォーカスを持っていません。
	//	また、ウインドウは右ボタン押し下げだけでは、
	//	フォーカスを得ません。
	//	このため、CWndDcdGrid2::CFocus::m_bIsFocusmarkShowEvery が
	//	falseの場合は、セルを右クリックでも、そのセルにフォーカスマークが描画されません。
	SetFocus() ;

	{
		//	マウスがクライアント領域内で、フォーカスセル以外のセルにあるなら、
		//	フォーカスセルをカーソル位置に移動
		CRect rectClient ;
		GetClientRect( &rectClient ) ;
		if ( rectClient.left <= point.x && point.x < rectClient.right && 
			rectClient.top <= point.y && point.y < rectClient.bottom )
		{
			CDcdGridCell*	pCell = getCellOfPos( CdDcdPosXy( point.x , point.y ) ) ;
			CDcdGridCell*	pCellFocus = getCFocus()->getFocusCell() ;
			if ( pCell != NULL && pCell != pCellFocus )
			{
				//	スクロール位置を更新します。
				//	アンカーセルは、保持しません(領域選択は解除)
				CPropStack	aPropStack( 
					this , 
					false ,		//CWndDcdGrid2::CXDcdGrid::m_bUpdateCWndDcdGrid
					true ,		//CWndDcdGrid2::CFocus::m_bFixafterColumnNumberChange
					false ) ;	//CWndDcdGrid2::CSelect::m_bKeepAnchor=false

				m_pCFocus->setFocusCell( pCell ) ;
			}
		}
	}

	CWnd::OnRButtonDown(nFlags, point);
}

} //namespace WndDcdGrid2
} //namespace DcdGrid
} //namespace DcDrawLib
