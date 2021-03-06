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
/*
// ****************************************************************
//	CWndDcdGrid2_CSelect.cpp
//$Id: CWndDcdGrid2_CSelect.cpp 110 2012-09-30 01:24:19Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "CWndDcdGrid2.h"

#include "Ou\OuNew.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "DcDraw\CDcdFillrectRop.h"
#include "DcDraw\CaDcdTargetItemPosition.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace DcDrawLib{
namespace DcdGrid{
namespace WndDcdGrid2{

// ----------------------------------------------------------------
//	CWndDcdGrid2::CSelect
// ----------------------------------------------------------------


CdDcdZoneXy CWndDcdGrid2::CSelect::getColumnZoneOfColumnNumber( 
	const CdDcdZoneXy& zonexyColumnNumber ) 
{
	CdDcdZoneXy	aZoneXy ;
	//X
	{
		CdDcdZone	zoneColumnNumber = zonexyColumnNumber.getX() ;
		CdDcdZone	aZone ;
		if ( zoneColumnNumber.getSize() > 0 )
		{
			aZone.setPos( m_pCWndDcdGrid2->getXColumnZone( zoneColumnNumber.getPos() ).getPos() );
			if ( zoneColumnNumber.getEndPos() == m_pCWndDcdGrid2->getCXDcdGrid()->getXColumnCount() )
			{
				//列番号に、一番左・下の列が含まれる場合は、
				//その左・下の罫線(グリッド全体の左・下の罫線)は範囲には含めません。
				aZone.setEndPos( m_pCWndDcdGrid2->getXColumnZone( zoneColumnNumber.getEndPos() - 1 ).getEndPos() );
			}
			else
			{
				//列番号に一番左・下の列が含まれない場合は、
				//範囲の左・下の罫線(列間の罫線)は範囲に含めます。
				aZone.setEndPos( m_pCWndDcdGrid2->getXColumnBorderZone( zoneColumnNumber.getEndPos() - 1 ).getEndPos() );
			}
		}
		aZoneXy.setX( aZone ) ;
	}

	//Y
	{
		CdDcdZone	zoneColumnNumber = zonexyColumnNumber.getY() ;
		CdDcdZone	aZone ;
		if ( zoneColumnNumber.getSize() > 0 )
		{
			aZone.setPos( m_pCWndDcdGrid2->getYColumnZone( zoneColumnNumber.getPos() ).getPos() );
			if ( zoneColumnNumber.getEndPos() == m_pCWndDcdGrid2->getCXDcdGrid()->getYColumnCount() )
			{
					//列番号に、一番左・下の列が含まれる場合は、
				//その左・下の罫線(グリッド全体の左・下の罫線)は範囲には含めません。
				aZone.setEndPos( m_pCWndDcdGrid2->getYColumnZone( zoneColumnNumber.getEndPos() - 1 ).getEndPos() );
			}
			else
			{
				//列番号に一番左・下の列が含まれない場合は、
				//範囲の左・下の罫線(列間の罫線)は範囲に含めます。
				aZone.setEndPos( m_pCWndDcdGrid2->getYColumnBorderZone( zoneColumnNumber.getEndPos() - 1 ).getEndPos() );
			}
		}
		aZoneXy.setY( aZone ) ;
	}
	return aZoneXy ;
}


	// --------------------------------
	//@name CWndDcdGrid2 からの委譲
	// --------------------------------
bool CWndDcdGrid2::CSelect::update_adjustProp() 
{
	bool bRv = false ;


	CdDcdPosXy	aColumnNumberFocus( ColumnNumberPosXy_NULL() )  ;
	{
		CDcdGridCell* pCell =  m_pCWndDcdGrid2->getCFocus()->getFocusCell() ;
		if ( pCell != NULL )
		{
			aColumnNumberFocus.setX( 
				m_pCWndDcdGrid2->getCXDcdGrid()->getXColumnNumberOfCell( pCell ) ) ;
			aColumnNumberFocus.setY( 
				m_pCWndDcdGrid2->getCXDcdGrid()->getYColumnNumberOfCell( pCell ) ) ;
		}
	}
	//aColumnNumberFocus = フォーカスセルの列番号


	// --------------------------------
	//	アンカーセルの正規化(アンカーセルがグリッドの範囲外なら、
	//	NULL に修正
	// --------------------------------
	if ( m_ColumnNumberAnchorCell != ColumnNumberPosXy_NULL() )
	{
		if ( !( 
			0 <= m_ColumnNumberAnchorCell.getX() && 
			m_ColumnNumberAnchorCell.getX() < m_pCWndDcdGrid2->getCXDcdGrid()->getXColumnCount() &&
			0 <= m_ColumnNumberAnchorCell.getY() && 
			m_ColumnNumberAnchorCell.getY() < m_pCWndDcdGrid2->getCXDcdGrid()->getYColumnCount() ) )
		{
			m_ColumnNumberAnchorCell = ColumnNumberPosXy_NULL() ;
		}
	}
	// --------------------------------
	//	フォーカスセル移動時に、選択セルを決定
	// --------------------------------
	CdDcdZoneXy	zonexyColumnNumberSelectNew = m_ColumnNumberSelect ;
	if ( m_ColumnNumberFocus_Old != aColumnNumberFocus )
	{

		if( !m_bKeepAnchor )
		{
			//＜3.2.1＞フォーカスセルの移動(アンカーセル更新)
				
			if ( m_ColumnNumberSelectLimit.IsInner( aColumnNumberFocus ) )
			{
				//○[FocusCellが m_ColumnNumberSelectLimitの範囲内]m_ColumnNumberAnchorCell=FocusCell
				m_ColumnNumberAnchorCell = aColumnNumberFocus ;
				zonexyColumnNumberSelectNew = ColumnNumberZoneXy_NULL() ;
			}
			else
			{
				//　○[else]m_ColumnNumberAnchorCell=NULL;m_ColumnNumberSelect=NULL
				m_ColumnNumberAnchorCell = ColumnNumberPosXy_NULL() ; 
				zonexyColumnNumberSelectNew = ColumnNumberZoneXy_NULL();
			}
		}
		else
		{
			//＜3.2.2＞フォーカスセルの移動(アンカーセル非更新)


			if ( m_ColumnNumberAnchorCell != ColumnNumberPosXy_NULL() )
			{
				//○[m_ColumnNumberAnchorCell!=NULL]

				CdDcdPosXy	aColumnNumberFocus( INT_MIN , INT_MIN )  ;
				CDcdGridCell* pCell =  m_pCWndDcdGrid2->getCFocus()->getFocusCell() ;
				if ( pCell != NULL )
				{
					aColumnNumberFocus.setX( 
						m_pCWndDcdGrid2->getCXDcdGrid()->getXColumnNumberOfCell( pCell ) ) ;
					aColumnNumberFocus.setY( 
						m_pCWndDcdGrid2->getCXDcdGrid()->getYColumnNumberOfCell( pCell ) ) ;
				}
					
				if ( m_ColumnNumberSelectLimit.IsInner( aColumnNumberFocus ) )
				{

					//  　○[FocusCellが m_ColumnNumberSelectLimitの範囲内]
					//X
					{
						int iPosMin = min( aColumnNumberFocus.getX() , m_ColumnNumberAnchorCell.getX() ) ;
						int iPosMax = max( aColumnNumberFocus.getX() , m_ColumnNumberAnchorCell.getX() ) ;
						zonexyColumnNumberSelectNew.setX( CdDcdZone( iPosMin , iPosMax - iPosMin + 1 ) ) ;
					}
					//Y
					{
						int iPosMin = min( aColumnNumberFocus.getY() , m_ColumnNumberAnchorCell.getY() ) ;
						int iPosMax = max( aColumnNumberFocus.getY() , m_ColumnNumberAnchorCell.getY() ) ;
						zonexyColumnNumberSelectNew.setY( CdDcdZone( iPosMin , iPosMax - iPosMin + 1 ) ) ;
					}

				}
			}
		}
		// --------------------------------
		m_ColumnNumberFocus_Old = aColumnNumberFocus ;
		bRv = true ;
	}

	// --------------------------------
	//	選択セルを、制限で補正
	// --------------------------------

	//	モードがNONEの場合は、選択セルなし
	if ( m_eSelectMode == SelectMode_NONE )
	{
		zonexyColumnNumberSelectNew = ColumnNumberZoneXy_NULL() ;
	}



	//	選択セルは、選択可能制限範囲内にする。
	//○[m_ColumnNumberSelect!=NULL]
	//　○m_ColumnNumberSelect は、 m_ColumnNumberSelectLimit の範囲内にする。
	//　○[SelectMode=SelectMode_XColumn]
	//     m_ColumnNumberSelect.Y = m_ColumnNumberSelectLimit.Y
	//　○[SelectMode=SelectMode_YColumn]
	//     m_ColumnNumberSelect.X = m_ColumnNumberSelectLimit.X
	if ( zonexyColumnNumberSelectNew != ColumnNumberZoneXy_NULL() ) 
	{

		CdDcdZoneXy	zonexyColumnNumberSelectLimit( 
			CdDcdPosXy( 0 , 0 ) ,
			CdDcdSizeXy( 
				m_pCWndDcdGrid2->getCXDcdGrid()->getXColumnCount() , 
				m_pCWndDcdGrid2->getCXDcdGrid()->getYColumnCount() ) ) ;
		zonexyColumnNumberSelectLimit = zonexyColumnNumberSelectLimit.CrossZone( m_ColumnNumberSelectLimit ) ;
		//zonexyColumnNumberSelectLimit = m_ColumnNumberSelectLimit を
		//	Gridの列数でクリップしたもの。

		//　○m_ColumnNumberSelect は、 m_ColumnNumberSelectLimit の範囲内にする。
		zonexyColumnNumberSelectNew = zonexyColumnNumberSelectLimit.CrossZone( zonexyColumnNumberSelectNew ) ;


		//　○[SelectMode=SelectMode_XColumn]
		//     m_ColumnNumberSelect.Y = m_ColumnNumberSelectLimit.Y
		if ( m_eSelectMode == SelectMode_XColumn )
		{
			zonexyColumnNumberSelectNew.setY( zonexyColumnNumberSelectLimit.getY() ) ;
		}
		//　○[SelectMode=SelectMode_YColumn]
		//     m_ColumnNumberSelect.X = m_ColumnNumberSelectLimit.X
		if ( m_eSelectMode == SelectMode_YColumn )
		{
			zonexyColumnNumberSelectNew.setX( zonexyColumnNumberSelectLimit.getX() ) ;
		}

	}
	// --------------------------------
	if ( m_ColumnNumberSelect != zonexyColumnNumberSelectNew )
	{
		m_ColumnNumberSelect = zonexyColumnNumberSelectNew ;
		bRv = true ;
	}
	return bRv ;
}

bool CWndDcdGrid2::CSelect::update_updateScreen() 
{
	bool bRv = false ;
	CConverter_WinGdi	aCConverter_WinGdi ;

	//	イベント処理のための仮想関数呼び出し
	if ( m_ColumnNumberSelect_Old != m_ColumnNumberSelect )
	{
		m_pCWndDcdGrid2->OnSetColumnNumberSelect( m_ColumnNumberSelect ) ;
	}

	//	画面を更新
	//memo:
	//	このクラスでは、CWnd::InvalidateRect()を呼び出すときに
	//	bErase 引数をTRUEにしなくてはなりません。
	//	これがFALSEだと、
	//	(1)  罫線がNULLPENの列を選択→選択解除した際、
	//		罫線部分が反転されたまま更新されません。

	if ( m_ColumnNumberSelect_Old != m_ColumnNumberSelect )
	{
		//○[m_ColumnNumberSelectOld=NULL and m_ColumnNumberSelect!=NULL]
		//   ○m_ColumnNumberSelect 列の領域をInvalidateRect()
		if ( m_ColumnNumberSelect_Old == ColumnNumberZoneXy_NULL() &&
			m_ColumnNumberSelect != ColumnNumberZoneXy_NULL() )
		{
			CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( m_ColumnNumberSelect ) ;
			RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
			m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
		}
		//○[m_ColumnNumberSelectOld!=NULL and m_ColumnNumberSelect=NULL]
		//   ○m_ColumnNumberSelectOld 列の領域をInvalidateRect()
		else if ( m_ColumnNumberSelect_Old != ColumnNumberZoneXy_NULL() && 
			m_ColumnNumberSelect == ColumnNumberZoneXy_NULL() )
		{
			CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( m_ColumnNumberSelect_Old ) ;
			RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
			m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
		}
		//○[m_ColumnNumberSelectOld!=NULL and m_ColumnNumberSelect!=NULL]
		else if ( m_ColumnNumberSelect_Old != ColumnNumberZoneXy_NULL() && 
			m_ColumnNumberSelect !=ColumnNumberZoneXy_NULL() )
		{
			CdDcdZoneXy	zonexyCross = m_ColumnNumberSelect_Old.CrossZone( m_ColumnNumberSelect ) ;
			//　○[m_ColumnNumberSelectOldとm_ColumnNumberSelectが交差している]
			//   　　列番号OuterX.Pos   =min(m_ColumnNumberSelectOld.X.Pos,m_ColumnNumberSelect.X.Pos)
			//   　　列番号OuterX.EndPos=
			//        max(m_ColumnNumberSelectOld.X.EndPos,m_ColumnNumberSelect.X.EndPos)
			//   　　列番号InvalidateX1.Pos=
			//        min(m_ColumnNumberSelectOld.X.Pos,m_ColumnNumberSelect.X.Pos)
			//   　　列番号InvalidateX1.EndPos=
			//       max(m_ColumnNumberSelectOld.X.Pos,m_ColumnNumberSelect.X.Pos)
			//   　　列番号InvalidateX2.Pos=
			//       min(m_ColumnNumberSelectOld.X.EndPos,m_ColumnNumberSelect.X.EndPos)
			//   　　列番号InvalidateX2.EndPos=
			//       max(m_ColumnNumberSelectOld.X.EndPos,m_ColumnNumberSelect.X.EndPos)
			if ( zonexyCross.getX().getSize() > 0 && zonexyCross.getY().getSize() )
			{
				//Old           |--------|   
				//New                |---------|
				//Outer         |--------------|
				//Invalidate    |--1-|   |---2-|
				//
				//Old           |--------------|   
				//New                |---|
				//Outer         |--------------|
				//Invalidate    |--1-|   |---2-|
				//
				CdDcdZone	aXColumnNumberOuter ;
				aXColumnNumberOuter.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getX().getPos() , m_ColumnNumberSelect.getX().getPos() ) ,
						max( m_ColumnNumberSelect_Old.getX().getEndPos() , m_ColumnNumberSelect.getX().getEndPos() ) ) ;

				CdDcdZone	aXColumnNumberInvalidate1 ;
				aXColumnNumberInvalidate1.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getX().getPos() , m_ColumnNumberSelect.getX().getPos() ) ,
						max( m_ColumnNumberSelect_Old.getX().getPos() , m_ColumnNumberSelect.getX().getPos() ) ) ;

				CdDcdZone	aXColumnNumberInvalidate2 ;
				aXColumnNumberInvalidate2.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getX().getEndPos() , m_ColumnNumberSelect.getX().getEndPos() ) ,
						max( m_ColumnNumberSelect_Old.getX().getEndPos() , m_ColumnNumberSelect.getX().getEndPos() ) ) ;

				CdDcdZone	aYColumnNumberOuter ;
				aYColumnNumberOuter.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getY().getPos() , m_ColumnNumberSelect.getY().getPos() ) ,
						max( m_ColumnNumberSelect_Old.getY().getEndPos() , m_ColumnNumberSelect.getY().getEndPos() ) ) ;

				CdDcdZone	aYColumnNumberInvalidate1 ;
				aYColumnNumberInvalidate1.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getY().getPos() , m_ColumnNumberSelect.getY().getPos() ) ,
						max( m_ColumnNumberSelect_Old.getY().getPos() , m_ColumnNumberSelect.getY().getPos() ) ) ;

				CdDcdZone	aYColumnNumberInvalidate2 ;
				aYColumnNumberInvalidate2.setBeginEndPos(
						min( m_ColumnNumberSelect_Old.getY().getEndPos() , m_ColumnNumberSelect.getY().getEndPos() ) ,
						max( m_ColumnNumberSelect_Old.getY().getEndPos() , m_ColumnNumberSelect.getY().getEndPos() ) ) ;

				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( 
						CdDcdZoneXy( aXColumnNumberInvalidate1 , aYColumnNumberOuter ) ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( 
						CdDcdZoneXy( aXColumnNumberInvalidate2 , aYColumnNumberOuter ) ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( 
						CdDcdZoneXy( aXColumnNumberOuter , aYColumnNumberInvalidate1 ) ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( 
						CdDcdZoneXy( aXColumnNumberOuter , aYColumnNumberInvalidate2 ) ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
			}
			//　○[m_ColumnNumberSelectOldとm_ColumnNumberSelectが交差していない]
			//   　○m_ColumnNumberSelect 列の領域をInvalidateRect()
			//   　○m_ColumnNumberSelectOld 列の領域をInvalidateRect()
			else
			{
				//Old           |----|   
				//New                    |-----|
				//Outer         |--------------|
				//Invalidate    |--1-|   |---2-|
				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( m_ColumnNumberSelect ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
				{
					CdDcdZoneXy	zonexyToInvalidate = getColumnZoneOfColumnNumber( m_ColumnNumberSelect_Old ) ;
					RECT	rectToInvalidate = aCConverter_WinGdi.RECTOf( zonexyToInvalidate ) ;
					m_pCWndDcdGrid2->InvalidateRect( &rectToInvalidate , TRUE ) ; 
				}
			}
		}
		// --------------------------------
		//	前回値を更新
		// --------------------------------
		m_ColumnNumberSelect_Old = m_ColumnNumberSelect ;

		bRv = true ;
	}
	return bRv ;
}

bool CWndDcdGrid2::CSelect::OnPaint( IfDcdTarget* pIfDcdTarget ) 
{
	bool bRv = false ;
	// --------------------------------	
	//	選択マーク
	// --------------------------------	
	if ( m_pIfDcDrawSelect != NULL )
	{
		if ( m_ColumnNumberSelect.getX().getSize() > 0 && 
			 m_ColumnNumberSelect.getY().getSize() > 0 )
		{
			CdDcdZoneXy	zoneSelect = getColumnZoneOfColumnNumber(
				m_ColumnNumberSelect ) ;

			CaDcdTargetItemPosition	aCDcdTargetItemPosition( pIfDcdTarget ,
				zoneSelect ) ;
			if ( aCDcdTargetItemPosition.isDrawable() )
			{
				m_pIfDcDrawSelect->DcDraw( &aCDcdTargetItemPosition ) ;
				
				bRv = true ;
			}
		}
	}
	// --------------------------------
	//	属性前回値を更新
	// --------------------------------

	return bRv ;
}

void CWndDcdGrid2::CSelect::InvalidateGrid( ) 
{
	//	このクラスの画面描画はすべてOnPaintで行われます。
	//	InvalidateGridでは、特別な処理は不要です。

}


void CWndDcdGrid2::CSelect::OnSize(UINT nType, int cx, int cy)
{
	if ( cx == 0 || cy == 0 ){
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
}

void CWndDcdGrid2::CSelect::OnSetFocus(CWnd* pOldWnd)
{
}

void CWndDcdGrid2::CSelect::OnKillFocus(CWnd* pNewWnd)
{
}


	// ********************************
	//	コンストラクタ
	// ********************************
CWndDcdGrid2::CSelect::CSelect(
	CWndDcdGrid2* pCWndDcdGrid2 ,
	Ou<IfDcDraw> pIfDcDrawSelect ) 
	: m_pCWndDcdGrid2( pCWndDcdGrid2 )
	, m_pIfDcDrawSelect( pIfDcDrawSelect )
	, m_eSelectMode( SelectMode_NONE ) 
	, m_bKeepAnchor( false ) 
	, m_ColumnNumberSelectLimit( CdDcdZone( 0 , INT_MAX ) , CdDcdZone( 0 , INT_MAX ) )
	, m_ColumnNumberAnchorCell( ColumnNumberPosXy_NULL()  ) 
	, m_ColumnNumberSelect( ColumnNumberZoneXy_NULL() )
	, m_ColumnNumberFocus_Old( ColumnNumberPosXy_NULL() ) 
	, m_ColumnNumberSelect_Old( ColumnNumberZoneXy_NULL() )
{
}

CWndDcdGrid2::CSelect::CSelect( CWndDcdGrid2* pCWndDcdGrid2 ) 
	: m_pCWndDcdGrid2( pCWndDcdGrid2 )
	, m_eSelectMode( SelectMode_NONE ) 
	, m_bKeepAnchor( false ) 
	, m_ColumnNumberSelectLimit( CdDcdZone( 0 , INT_MAX ) , CdDcdZone( 0 , INT_MAX ) )
	, m_ColumnNumberAnchorCell( ColumnNumberPosXy_NULL()  ) 
	, m_ColumnNumberSelect( ColumnNumberZoneXy_NULL() )
	, m_ColumnNumberFocus_Old( ColumnNumberPosXy_NULL() ) 
	, m_ColumnNumberSelect_Old( ColumnNumberZoneXy_NULL() )
{
	m_pIfDcDrawSelect = OuNew<CDcdFillrectRop>( new CDcdFillrectRop( 
		CdBrushProp( CdColorProp( 0 , 0 , 0 ) , CdBrushProp::SOLID ) ,
		R2_NOTXORPEN 
		) ) ;
	
}

CWndDcdGrid2::CSelect::~CSelect() 
{
}

// ********************************
//@name 関連
// ********************************

Ou<IfDcDraw>	CWndDcdGrid2::CSelect::getIfDcDrawSelect() 
{
	return m_pIfDcDrawSelect ;
}
void CWndDcdGrid2::CSelect::setIfDcDrawSelect( Ou<IfDcDraw> value ) 
{
	m_pIfDcDrawSelect = value ;
}



	// ********************************
	//@name 属性
	// ********************************
CWndDcdGrid2::CSelect::ESelectMode	CWndDcdGrid2::CSelect::getSelectMode()const 
{
	return m_eSelectMode ;
}
void CWndDcdGrid2::CSelect::setSelectMode( ESelectMode	value ) 
{
	m_eSelectMode = value ;
	m_pCWndDcdGrid2->update() ;
}

bool CWndDcdGrid2::CSelect::getKeepAnchor() 
{
	return m_bKeepAnchor ;
}
void CWndDcdGrid2::CSelect::setKeepAnchor( bool value ) 
{
	m_bKeepAnchor = value ;
	m_pCWndDcdGrid2->update() ;
}


CdDcdZoneXy	CWndDcdGrid2::CSelect::getColumnNumberSelectLimit()const 
{
	return m_ColumnNumberSelectLimit ;
}
void CWndDcdGrid2::CSelect::setColumnNumberSelectLimit( const CdDcdZoneXy& value ) 
{
	m_ColumnNumberSelectLimit = value ;
	m_pCWndDcdGrid2->update() ;
}
CdDcdPosXy	CWndDcdGrid2::CSelect::getColumnNumberAnchorCell()
{
	return m_ColumnNumberAnchorCell ;
}
CdDcdZoneXy	CWndDcdGrid2::CSelect::getColumnNumberSelect()const 
{
	return m_ColumnNumberSelect ;
}
void CWndDcdGrid2::CSelect::setColumnNumberSelect( const CdDcdZoneXy& value ) 
{
	m_ColumnNumberSelect = value ;
	m_pCWndDcdGrid2->update() ;
}

} //namespace WndDcdGrid2
} //namespace DcdGrid
} //namespace DcDrawLib
