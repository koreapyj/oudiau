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
//	$Id: CPropEditUi_Ressyasyubetsu.cpp 197 2014-08-02 07:03:11Z okm $
// ****************************************************************

/** @file */
#include "stdafx.h"
#include "CPropEditUi_Ressyasyubetsu.h"

namespace ViewRessyasyubetsu {

// ****************************************************************
//	CPropEditUi_Ressyasyubetsu
// ****************************************************************
	// 種別名が指定されていません
const wchar_t* const CPropEditUi_Ressyasyubetsu::ERRMSG_SYUBETUSMEI_EMPTY = L"Ressyasyubetsumei is empty." ;

	// 略称が長すぎます
const wchar_t* const CPropEditUi_Ressyasyubetsu::ERRMSG_RYAKUSYOULENGTH = L"Ryakusyou is too long(Limit is 6 characters)." ;


	// ================================
	//@name 下請関数
	// ================================
void CPropEditUi_Ressyasyubetsu::UiDataFromTarget( 
		UIDATA* pUiData , 
		const CentDedRessyasyubetsu* pTarget ) 
{
	// 列車種別名 
	pUiData->strSyubetsumei = pTarget->getSyubetsumei() ;
	
	// 列車種別名の有効・無効 
	pUiData->bSyubetsumeiIsEnable = true ;

	// 略称（種別名の略称） 
	pUiData->strRyakusyou = pTarget->getRyakusyou();
	
	//	時刻表文字色(ダイヤグラムの列車情報の文字色を兼ねます)	
	pUiData->colorJikokuhyouMojiColor = pTarget->getJikokuhyouMojiColor() ;
	
	//時刻表ビューで、この列車種別の時刻を表示するための時刻表フォント
	pUiData->iJikokuhyouFontIndex= pTarget->getJikokuhyouFontIndex() ;

	// ダイヤグラム線の色
	pUiData->colorDiagramSenColor = pTarget->getDiagramSenColor() ;
	
	//ダイヤグラム線の線スタイル	
	pUiData->iDiagramSenStyle = (int)pTarget->getDiagramSenStyle() ;

	// ダイヤグラム線の線スタイルが太線か否かを指定します。
	pUiData->iDiagramSenIsBold = (int)pTarget->getDiagramSenIsBold() ;
	
	//停車駅明示の方法
	pUiData->iStopMarkDrawType = (int)pTarget->getStopMarkDrawType() ;
}

int CPropEditUi_Ressyasyubetsu::UiDataToTarget( 
		const UIDATA& aUiDataPrev , 
		const UIDATA& aUiDataModified , 
		CentDedRessyasyubetsu* pTarget  ) 
{
	int iRv = 0 ;
	
	// 列車種別名 
	if ( iRv >= 0 && aUiDataPrev.strSyubetsumei != aUiDataModified.strSyubetsumei 
		&& aUiDataModified.bSyubetsumeiIsEnable ) 
	{
		pTarget->setSyubetsumei( aUiDataModified.strSyubetsumei ) ;
	}

	// 略称（種別名の略称） 
	if ( iRv >= 0 && aUiDataPrev.strRyakusyou != aUiDataModified.strRyakusyou ) 
	{
		pTarget->setRyakusyou( aUiDataModified.strRyakusyou ) ;
	}


	//	時刻表文字色(ダイヤグラムの列車情報の文字色を兼ねます)	
	if ( iRv >= 0 && aUiDataPrev.colorJikokuhyouMojiColor != aUiDataModified.colorJikokuhyouMojiColor ) 
	{
		pTarget->setJikokuhyouMojiColor( aUiDataModified.colorJikokuhyouMojiColor ) ;
	}
	
	//時刻表ビューで、この列車種別の時刻を表示するための時刻表フォント
	if ( iRv >= 0 && aUiDataPrev.iJikokuhyouFontIndex != aUiDataModified.iJikokuhyouFontIndex ) 
	{
		if ( aUiDataModified.iJikokuhyouFontIndex >= 0 )
		{
			pTarget->setJikokuhyouFontIndex( aUiDataModified.iJikokuhyouFontIndex ) ;
		}
	}



	// ダイヤグラム線の色
	if ( iRv >= 0 && aUiDataPrev.colorDiagramSenColor != aUiDataModified.colorDiagramSenColor ) 
	{
		pTarget->setDiagramSenColor( aUiDataModified.colorDiagramSenColor ) ;
	}
	
	//ダイヤグラム線の線スタイル	
	if ( iRv >= 0 && aUiDataPrev.iDiagramSenStyle != aUiDataModified.iDiagramSenStyle ) 
	{
		if ( aUiDataModified.iDiagramSenStyle >= 0 )
		{
			pTarget->setDiagramSenStyle( (CentDedRessyasyubetsu::ESenStyle)aUiDataModified.iDiagramSenStyle ) ;
		}
	}

	// ダイヤグラム線の線スタイルが太線か否かを指定します。
	if ( iRv >= 0 && aUiDataPrev.iDiagramSenIsBold != aUiDataModified.iDiagramSenIsBold ) 
	{
		if ( aUiDataModified.iDiagramSenIsBold >= 0 )
		{
			pTarget->setDiagramSenIsBold( aUiDataModified.iDiagramSenIsBold == 1 ) ;
		}
	}
	
	//停車駅明示の方法
	if ( iRv >= 0 && aUiDataPrev.iStopMarkDrawType != aUiDataModified.iStopMarkDrawType ) 
	{
		if ( aUiDataModified.iStopMarkDrawType >= 0 )
		{
			pTarget->setStopMarkDrawType( (CentDedRessyasyubetsu::EStopMarkDrawType)aUiDataModified.iStopMarkDrawType ) ;
		}
	}

	return iRv ;
}

	// ================================
	//@name CPropEditUi - UiData-Target間のデータ転送
	// ================================
void CPropEditUi_Ressyasyubetsu::UiDataFromTarget() 
{
	//◇[単一選択時]
	if ( m_pTarget->size() == 1 )
	{
		UiDataFromTarget( &m_UiData , m_pTarget->get( 0 ) ) ;
	}
	//◇[複数選択時]
	else 
	{
		for ( int i = 0 ; i < m_pTarget->size() ; i ++ )
		{
			UIDATA aUiData ;
			UiDataFromTarget( &aUiData , m_pTarget->get( i ) ) ;
			if ( i == 0 ) 
			{
				m_UiData = aUiData ;
			}
			else
			{
				// 列車種別名 
				if ( m_UiData.strSyubetsumei != L""
					&& m_UiData.strSyubetsumei != aUiData.strSyubetsumei )
				{
					m_UiData.strSyubetsumei = L"" ;
				}
	
				// 略称（種別名の略称） 
				if ( m_UiData.strRyakusyou != L""
					&& m_UiData.strRyakusyou != aUiData.strRyakusyou )
				{
					m_UiData.strRyakusyou = L"" ;
				}


				//	時刻表文字色(ダイヤグラムの列車情報の文字色を兼ねます)	
				if ( m_UiData.colorJikokuhyouMojiColor != CdColorProp( 255 , 255 , 255 )
					&& m_UiData.colorJikokuhyouMojiColor != aUiData.colorJikokuhyouMojiColor )
				{
					m_UiData.colorJikokuhyouMojiColor = CdColorProp( 255 , 255 , 255 ) ;
				}


				//時刻表ビューで、この列車種別の時刻を表示するための時刻表フォント
				if ( m_UiData.iJikokuhyouFontIndex != -1
					&& m_UiData.iJikokuhyouFontIndex != aUiData.iJikokuhyouFontIndex )
				{
					m_UiData.iJikokuhyouFontIndex = -1 ;
				}

				// ダイヤグラム線の色
				if ( m_UiData.colorDiagramSenColor != CdColorProp( 255 , 255 , 255 )
					&& m_UiData.colorDiagramSenColor != aUiData.colorDiagramSenColor )
				{
					m_UiData.colorDiagramSenColor = CdColorProp( 255 , 255 , 255 ) ;
				}
	
				//ダイヤグラム線の線スタイル	
				if ( m_UiData.iDiagramSenStyle != -1
					&& m_UiData.iDiagramSenStyle != aUiData.iDiagramSenStyle )
				{
					m_UiData.iDiagramSenStyle = -1 ;
				}

				// ダイヤグラム線の線スタイルが太線か否かを指定します。
				if ( m_UiData.iDiagramSenIsBold != -1
					&& m_UiData.iDiagramSenIsBold != aUiData.iDiagramSenIsBold )
				{
					m_UiData.iDiagramSenIsBold = -1 ;
				}
	
				//停車駅明示の方法
				if ( m_UiData.iStopMarkDrawType != -1
					&& m_UiData.iStopMarkDrawType != aUiData.iStopMarkDrawType )
				{
					m_UiData.iStopMarkDrawType = -1 ;
				}
			}
		}
	}
}



int CPropEditUi_Ressyasyubetsu::adjustUiData( const UIDATA& aUiDataPrev , EShowError eShowError ) 
{
	int iRv = 0 ; 

	
	// 列車種別名の有効・無効 
	if ( iRv >= 0 )
	{
		//	選択列車が1つの場合、列車種別名が空文字列の場合は、エラーです。
		//	選択列車が2つ以上の場合、列車種別名が空文字に変更されたらエラーです。
		//	(複数選択の場合は、異なる名前の２つが選択されると、この
		//	テキスト入力は空になるためです。)
		if ( ( m_pTarget->size() == 1	
				&& m_UiData.strSyubetsumei.length() == 0 )
		 ||  ( m_pTarget->size() > 1 
				&& m_UiData.strSyubetsumei.length() == 0 
				&& m_UiData.strSyubetsumei != getUiDataOnBeginEdit().strSyubetsumei ) )
		{
			iRv = -1 ;      //  種別名が指定されていません
			if ( adjustUiData_isShowErrorRequired( eShowError 
				, m_UiData.strSyubetsumei != aUiDataPrev.strSyubetsumei ) )
			{
				showError( ERRMSG_SYUBETUSMEI_EMPTY ) ;
				setFocus( offsetof( UIDATA , strSyubetsumei )) ;
			}
		}
	}
	if ( iRv >= 0 )
	{
		if ( m_UiData.strRyakusyou.length() > 6 )
		{
			iRv = -2 ;      //  略称が長すぎます(略称は6文字まで(半角)です)
			if ( adjustUiData_isShowErrorRequired( eShowError 
				, m_UiData.strRyakusyou != aUiDataPrev.strRyakusyou  ) )
			{
				showError( ERRMSG_RYAKUSYOULENGTH ) ;
				setFocus( offsetof( UIDATA , strRyakusyou )) ;
			}
		}
	}

	return iRv ;
}
	
int CPropEditUi_Ressyasyubetsu::UiDataToTarget( const UIDATA& aUiDataPrev ) 
{
	int iRv = 0 ; 
	for ( int i = 0 ; iRv >= 0 && i < m_pTarget->size() ; i ++ )
	{
		CentDedRessyasyubetsu* pCentDedRessyasyubetsu = m_pTarget->get( i ) ; 
		iRv = UiDataToTarget( aUiDataPrev , m_UiData , pCentDedRessyasyubetsu ) ;
	}
	return iRv ;
}



	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUi_Ressyasyubetsu::CPropEditUi_Ressyasyubetsu( Mu<CentDedRessyasyubetsu*>* pTarget )
	: m_pTarget( pTarget ) 
{
	
}

} //namespace ViewRessyasyubetsu 



