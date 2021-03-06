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
// ****************************************************************
//	$Id: CPropEditUi_Ressya.cpp 179 2014-05-05 13:50:33Z okm $
// ****************************************************************

#include "stdafx.h"
#include "ViewJikokuhyou\CPropEditUi_Ressya.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewJikokuhyou{

	// ********************************
	//@name エラーメッセージ
	// ********************************
	// 列車種別が範囲外です。
const wchar_t* const CPropEditUi_Ressya::ERRMSG_INVALID_RESSYASYUBETSU = L"Invalid Ressyasyubetsu." ;

	// ================================
	//@name 下請関数
	// ================================

void CPropEditUi_Ressya::UiDataFromTarget( UIDATA* pUiData , const CentDedRessya* pRessya ) 
{
	pUiData->iIsNull = (int)pRessya->isNull() ;
	if ( pUiData->iIsNull )
	{
		pUiData->strRessyabangou = L"" ;
		pUiData->bRessyabangouIsEnable = false ;
		pUiData->iRessyasyubetsuIndex = 0 ;
		pUiData->bRessyasyubetsuIndexIsEnable = false ;
		pUiData->strRessyamei = L"" ;
		pUiData->bRessyameiIsEnable = false ;
		pUiData->strGousuu = L"" ;
		pUiData->bGousuuIsEnable = false ;
		pUiData->strBikou = L"" ;
		pUiData->bBikouIsEnable = false ;
	}
	else 
	{
		pUiData->strRessyabangou = pRessya->getRessyabangou() ;
		pUiData->bRessyabangouIsEnable = true ;
		pUiData->iRessyasyubetsuIndex = pRessya->getRessyasyubetsuIndex() ;
		pUiData->bRessyasyubetsuIndexIsEnable = true ;
		pUiData->strRessyamei = pRessya->getRessyamei() ;
		pUiData->bRessyameiIsEnable = true ;
		pUiData->strGousuu = pRessya->getGousuu() ;
		pUiData->bGousuuIsEnable = true ;
		pUiData->strBikou = pRessya->getBikou() ;
		pUiData->bBikouIsEnable = true ;
	}
}

int  CPropEditUi_Ressya::UiDataToTarget( 
	const UIDATA& aUiDataPrev , 
	const UIDATA& aUiDataModified , 
	CentDedRessya* pRessya ) 
{
	int iRv = 0 ;

	//	iIsNull が変化した場合
	if ( aUiDataPrev.iIsNull != aUiDataModified.iIsNull && 
		aUiDataModified.iIsNull != -1 )
	{
		pRessya->setIsNull( aUiDataModified.iIsNull == 1 ) ;
	}
	//	iIsNull以外に変更が加えられた場合は、
	//	変更を列車に反映します。
	//	但し、Nullの列車には変更を加えません
	//	(属性を設定することにより、NULL状態の列車が非NULLに変化するためです)。
	if ( !pRessya->isNull() )
	{
		if ( aUiDataPrev.strRessyabangou != aUiDataModified.strRessyabangou )
		{
			pRessya->setRessyabangou( aUiDataModified.strRessyabangou ) ;
		}
		if ( aUiDataPrev.iRessyasyubetsuIndex != aUiDataModified.iRessyasyubetsuIndex )
		{
			pRessya->setRessyasyubetsuIndex( aUiDataModified.iRessyasyubetsuIndex ) ;
		}
		if ( aUiDataPrev.strRessyamei != aUiDataModified.strRessyamei )
		{
			pRessya->setRessyamei( aUiDataModified.strRessyamei ) ;
		}
		if ( aUiDataPrev.strGousuu != aUiDataModified.strGousuu )
		{
			pRessya->setGousuu( aUiDataModified.strGousuu ) ;
		}
		if ( aUiDataPrev.strBikou != aUiDataModified.strBikou )
		{
			pRessya->setBikou( aUiDataModified.strBikou ) ;
		}
	}

	return iRv ;
}



	// ================================
	//@name UiData - Target間のデータ転送
	// ================================
void CPropEditUi_Ressya::UiDataFromTarget() 
{
	for ( int i = 0 ; i < m_pTarget->size() ; i ++ )
	{
		UIDATA aUiData ;
		CentDedRessya* pRessya = m_pTarget->get( i ) ;
		UiDataFromTarget( &aUiData , pRessya ) ;
		if ( i == 0 )
		{
			m_UiData = aUiData ;
		}
		else
		{
			if ( m_UiData.iIsNull >= 0 
				&&  m_UiData.iIsNull != aUiData.iIsNull )
			{
				m_UiData.iIsNull = -1 ;
			}
			if ( m_UiData.strRessyabangou.length() > 0 
				&& m_UiData.strRessyabangou != aUiData.strRessyabangou )
			{
				m_UiData.strRessyabangou.erase() ;
			}
			if ( m_UiData.iRessyasyubetsuIndex >= 0 
				&& m_UiData.iRessyasyubetsuIndex != aUiData.iRessyasyubetsuIndex )
			{
				m_UiData.iRessyasyubetsuIndex = -1 ; 
			}
			if ( m_UiData.strRessyamei.length() >= 0 
				&& m_UiData.strRessyamei != aUiData.strRessyamei )
			{
				m_UiData.strRessyamei.erase() ;
			}
			if ( m_UiData.strGousuu.length() >= 0 
				&& m_UiData.strGousuu != aUiData.strGousuu )
			{
				m_UiData.strGousuu.erase() ;
			}
			if ( m_UiData.strBikou.length() >= 0 
				&& m_UiData.strBikou != aUiData.strBikou )
			{
				m_UiData.strBikou.erase() ;
			}
		}
	}
}

int CPropEditUi_Ressya::adjustUiData( const UIDATA& aUiDataPrev , EShowError eShowError ) 
{
	int iRv = 0 ; 

	//	空行(NULL)である場合は、
	//	他の項目をすべて無効にします。
	//	空行でない場合は他の項目は有効にしますが、
	//	ターゲットが複数の場合は列車番号は無効にします。
	if ( m_UiData.iIsNull == 1 )
	{
		m_UiData.bRessyabangouIsEnable = false ;
		m_UiData.bRessyasyubetsuIndexIsEnable = false ;
		m_UiData.bRessyameiIsEnable = false ;
		m_UiData.bGousuuIsEnable = false ;
		m_UiData.bBikouIsEnable = false ;
	}
	else
	{
		if ( m_pTarget->size() > 1 )
		{
			m_UiData.bRessyabangouIsEnable = false ;
		}
		else
		{
			m_UiData.bRessyabangouIsEnable = true ;
		}
		m_UiData.bRessyasyubetsuIndexIsEnable = true ;
		m_UiData.bRessyameiIsEnable = true ;
		m_UiData.bGousuuIsEnable = true ;
		m_UiData.bBikouIsEnable = true ;
	}

	//	列車種別Indexが範囲外の場合は、
	//	エラーを発生させます。
	//	列車種別Indexの有効範囲は、
	//	[Targetが1の場合]0～m_iRessyasyubetsuCount
	//	[Targetが1より多い場合]-1～m_iRessyasyubetsuCount
	int iIndexLowerBound = 0 ;
	if ( m_pTarget->size() > 1 ){	iIndexLowerBound = -1 ;}
	if ( m_UiData.bRessyasyubetsuIndexIsEnable )
	{
		if ( !( iIndexLowerBound <= m_UiData.iRessyasyubetsuIndex 
			&& m_UiData.iRessyasyubetsuIndex < m_iRessyasyubetsuCount ) )
		{
			iRv = -1 ;
			if ( eShowError == EShowError_All || 
				( eShowError == EShowError_Changed 
					&& aUiDataPrev.iRessyasyubetsuIndex != m_UiData.iRessyasyubetsuIndex ) 
			)
			{
				showError( ERRMSG_INVALID_RESSYASYUBETSU ) ;
				setFocus( offsetof( UIDATA , iRessyasyubetsuIndex ) ) ;
			}

		}
	}

	return iRv ;
}


int CPropEditUi_Ressya::UiDataToTarget( const UIDATA& aUiDataPrev )  
{
	int iRv = 0 ; 
	for ( int i = 0 ; iRv >= 0 && i < m_pTarget->size() ; i ++ )
	{
		CentDedRessya* pRessya = m_pTarget->get( i ) ; 
		iRv = UiDataToTarget( aUiDataPrev , m_UiData , pRessya ) ; 
	}
	return iRv ;
}
	
	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUi_Ressya::CPropEditUi_Ressya( 
	Mu<CentDedRessya*>* pTarget ,
	int iRessyasyubetsuCount 
	) 
	: m_pTarget( pTarget ) 
	, m_iRessyasyubetsuCount( iRessyasyubetsuCount ) 
{
}
	
	

} //namespace ViewJikokuhyou

