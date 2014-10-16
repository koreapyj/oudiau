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
//	CDcdRectangle.cpp
// ****************************************************************
*/
#include "CDcdRectangle.h"
#include "CConverter_WinGdi.h"
// ****************************************************************
//	CDcdRectangle
// ****************************************************************
// ********************************
//	コンストラクタ
// ********************************
CDcdRectangle::CDcdRectangle( 
					const CdPenProp& aCdPenProp , 
					const CdBrushProp& aCdBrushProp ) 
	: m_CdPenProp( aCdPenProp )
	, m_CdBrushProp( aCdBrushProp ) 
{
}
CDcdRectangle::CDcdRectangle() 
{
}
CDcdRectangle::~CDcdRectangle() 
{
}

// ********************************
//	IfDcDraw
// ********************************
bool CDcdRectangle::DcDraw( IfDcdTarget* pIfDcdTarget ) 
{
	int		iRv = 0 ;
	bool	bRv = false ;
	

	// --------------------------------
	//	ペン・ブラシの生成
	// --------------------------------
	HPEN	hPen = NULL ;
	if ( iRv >= 0 ){
		hPen = pIfDcdTarget->CreatePen( m_CdPenProp ) ;
		if ( hPen == NULL ){
			iRv = -1 ;	//	ペンの作成に失敗しました。	\n
		}
	}
	HBRUSH	hBrush = NULL ;
	if ( iRv >= 0 ){
		hBrush = pIfDcdTarget->CreateBrush( m_CdBrushProp ) ;
		if ( hBrush == NULL ){
			iRv = -2 ;	//	ブラシの作成に失敗しました。	\n
		}
	}
	HBRUSH		hBrushSid = NULL ;
	if ( iRv >= 0 ){
		hBrushSid = (HBRUSH)SelectObject( pIfDcdTarget->getHdc() , hBrush ) ;
	}
	HPEN		hPenSid = NULL ;
	if ( iRv >= 0 ){
		hPenSid = (HPEN)SelectObject( pIfDcdTarget->getHdc() , hPen ) ;
	}
	int iBkModeSid = -1 ;
	if ( iRv >= 0 ){
		 iBkModeSid = SetBkMode( pIfDcdTarget->getHdc() , TRANSPARENT ) ;
	}
	// --------------------------------
	if ( iRv >= 0 ){
		CdDcdZoneXy	aCdDcdZoneXy = pIfDcdTarget->getZone() ;
		RECT	LRect ;
		LRect.left   = aCdDcdZoneXy.getX().getPos() + 
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.top    = aCdDcdZoneXy.getY().getPos() +
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.right  = aCdDcdZoneXy.getX().getEndPos() -
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		LRect.bottom = aCdDcdZoneXy.getY().getEndPos() -
					m_CdPenProp.getLogicalunitWidth() / 2 ;
		
		Rectangle( pIfDcdTarget->getHdc() , 
			LRect.left , LRect.top , LRect.right , LRect.bottom ) ;
		
	}
	if ( iRv >= 0 ){
		bRv = true ;
	}
	// --------------------------------
	if ( iBkModeSid != -1 ) {
		SetBkMode( pIfDcdTarget->getHdc() , iBkModeSid ) ;
	}
	if ( hBrushSid != NULL ){
		SelectObject( pIfDcdTarget->getHdc() , hBrushSid ) ;
		hBrushSid = NULL ;
	}
	if ( hPenSid != NULL ){
		SelectObject( pIfDcdTarget->getHdc() , hPenSid ) ;
		hPenSid = NULL ;
	}
	return ( bRv ) ;
}
	
bool CDcdRectangle::getItemSize( IfDcdTarget* pIfDcdTarget , 
							CdDcdSizeXy* pCdDcdSizeXy ) 
{
	return ( false ) ;
}


