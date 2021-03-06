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
//	$Id: CPropEditUI_Ekijikoku.cpp 179 2014-05-05 13:50:33Z okm $
// ****************************************************************

/** @file */

#include "stdafx.h"
#include "ViewJikokuhyou\CPropEditUi_EkiJikoku.h"
#include "str\CStrCharSizeMb.h"
#include "str\strLf.h"

namespace ViewJikokuhyou{
	using namespace OuLib::Str;

		
/** ダイアログボックスへの時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone ,		//	HourZeroToNone 
	CdDedJikoku::CConv::ESecond_NotIfZero ) ;	//	NoSecond


/**
	時刻のUI形式を解釈して、時刻に変換します。
	エディットコントロールの内容が2桁数字の場合は、
	前の駅時刻Orderをもとに、時を補完します。
@param strUIJikoku [in]
	UI形式の時刻を指定してください。
@param jikokuRevOrder [in]
	直前の『駅時刻』。
	この値は、strControlが分のみ(数字2桁)の場合、時を補完するのに使います。
	『NULL状態』の場合、時の補完は行われません。
@param pCdDedJikoku [out]
	この関数は、文字列の解釈に成功したら、文字列の内容を変換した時刻を
	ここに書き込みます。
@return
	成功したら 0 以上。時刻への変換ができなければ負の数です。
	-	-1 ;	//	項目数が不足しています。
	-	-2 ;	//	時・分・秒の表記が不正です。
*/
static int	getJikokuFromUI( 
	const wstring& strUIJikoku , 
	const CdDedJikoku& jikokuRevOrder , 
	CdDedJikoku* pCdDedJikoku ) 
{
	int	iRv = 0 ;
	CdDedJikoku	aCdDedJikoku ;
	wstring	strControl = CStrCharSizeMb::strToSingleByte( 
		OuLib::Str::strTrim( strUIJikoku ) ) ;

	int iResult = aCdDedJikoku.decode( strControl ) ;
	if ( iResult < 0 )
	{
		iRv = iResult ;
		//	文字列が解釈できません。
	}
	//iRv = 
	//-	-1 ;	//	項目数が不足しています。
	//-	-2 ;	//	時・分・秒の表記が不正です。

	//	着時刻が2桁で、前の駅時刻がある場合は、
	//	着時刻に時を補完
	if ( iRv == -1 && 
		 !jikokuRevOrder.isNull() && 
		strControl.size() == 2 && 
		isdigit( strControl[0] ) && 
		isdigit( strControl[1] ) )
	{
		int iMin = _wtoi( strControl.c_str() ) ;
		if ( 0 <= iMin && iMin < 60 )
		{
			aCdDedJikoku.setTime( jikokuRevOrder.getHour() , iMin ) ;
			CdDedJikan	jikanSub = aCdDedJikoku.subJikoku( 
				jikokuRevOrder ) ;
			if ( jikanSub.getTotalSeconds() < 0 )
			{
				aCdDedJikoku = aCdDedJikoku.getTotalSeconds() + 60*60 ;
			}
			//aCdDedJikoku = 現在入力された2桁の文字列に、
			//	jikokuRevOrder 以後となる時を補完

			iRv = 0 ;	//	時刻補完に成功しました。 
		}
	}

	// --------------------------------
	if ( pCdDedJikoku != NULL )
	{
		*pCdDedJikoku = aCdDedJikoku ;
	}
	return iRv ;
}

	// ********************************
	//@name エラーメッセージ
	// ********************************
const wchar_t* const CPropEditUi_EkiJikoku::ERRMSG_INVALID_CHAKUJIKOKU = L"Invalid ChakuJikoku.";
const wchar_t* const CPropEditUi_EkiJikoku::ERRMSG_INVALID_HATSUJIKOKU = L"Invalid HatsuJikoku.";




	// ================================
	//@name 下請関数
	// ================================
void CPropEditUi_EkiJikoku::UiDataFromTarget( 
	UIDATA* pUiData , const CentDedRessya* pRessya , int iEkiOrder) 
{
	CdDedJikoku::CConv	aJikokuConv( true , CdDedJikoku::CConv::EHour_ZeroToNone , CdDedJikoku::CConv::ESecond_NotIfZero ) ;
	CentDedEkiJikoku aEkiJikoku = pRessya->getCentDedEkiJikoku( iEkiOrder ) ;

	pUiData->iEkiatsukai = 0 ;
	switch( aEkiJikoku.getEkiatsukai() )
	{
	case CentDedEkiJikoku::Ekiatsukai_None:
		pUiData->iEkiatsukai = 0 ;	//	運行なし
		break ;
	case CentDedEkiJikoku::Ekiatsukai_Teisya:
		pUiData->iEkiatsukai = 1 ;	// 停車
		break ;
	case CentDedEkiJikoku::Ekiatsukai_Tsuuka:
		pUiData->iEkiatsukai = 2 ;	// 通過
		break ;
	case CentDedEkiJikoku::Ekiatsukai_Keiyunasi:
		pUiData->iEkiatsukai = 3 ;	// 経由なし
		break ;
	}

	pUiData->strChakujikoku = aJikokuConv.encode( aEkiJikoku.getChakujikoku() ) ;
	pUiData->strHatsujikoku = aJikokuConv.encode( aEkiJikoku.getHatsujikoku() ) ;

}


int CPropEditUi_EkiJikoku::UiDataToTarget( 
	const UIDATA& aUiDataPrev , 
	const UIDATA& aUiDataModified , 
	CentDedRessya* pRessya , 
	int iEkiOrder ,
	bool bModifyHatsujikoku ) 
{
	CentDedEkiJikoku aEkiJikoku = pRessya->getCentDedEkiJikoku( iEkiOrder ) ;

	int iRv = 0 ;

	// iEkiatsukai
	if ( iRv >= 0 )
	{
		if ( aUiDataPrev.iEkiatsukai != aUiDataModified.iEkiatsukai )
		{
			CentDedEkiJikoku::EEkiatsukai eEkiatsukai = CentDedEkiJikoku::Ekiatsukai_None ;
			switch( aUiDataModified.iEkiatsukai )
			{
			case 0:
				eEkiatsukai = CentDedEkiJikoku::Ekiatsukai_None ;
				break ;
			case 1:
				eEkiatsukai = CentDedEkiJikoku::Ekiatsukai_Teisya ;
				break ;
			case 2:
				eEkiatsukai = CentDedEkiJikoku::Ekiatsukai_Tsuuka ;
				break ;
			case 3:
				eEkiatsukai = CentDedEkiJikoku::Ekiatsukai_Keiyunasi ;
				break ;
			}
			aEkiJikoku.setEkiatsukai( eEkiatsukai ) ;	
		}
	}

	// strChakujikoku
	if ( iRv >= 0 )
	{
		if ( aUiDataModified.bChakujikokuIsEnable && 
			aUiDataPrev.strChakujikoku != aUiDataModified.strChakujikoku )
		{
			CdDedJikoku	aJikoku ;
			int iResult = aJikoku.decode( aUiDataModified.strChakujikoku ) ;
			if ( iResult >= 0 )
			{
				aEkiJikoku.setChakujikoku( aJikoku ) ;
			}

		}
	}
	// strHatsujikoku
	if ( iRv >= 0 )
	{
		if ( aUiDataModified.bHatsujikokuIsEnable && 
			aUiDataPrev.strHatsujikoku != aUiDataModified.strHatsujikoku )
		{
			CdDedJikoku	aJikoku ;
			int iResult = aJikoku.decode( aUiDataModified.strHatsujikoku ) ;
			if ( iResult >= 0 )
			{
				aEkiJikoku.setHatsujikoku( aJikoku ) ;
			}
		}
	}

	//  --------------------------------
	if ( iRv >= 0 )
	{
		if ( bModifyHatsujikoku )
		{
			pRessya->modifyCentDedEkiJikoku( iEkiOrder , aEkiJikoku ) ;
		}
		else
		{
			pRessya->setCentDedEkiJikoku( iEkiOrder , aEkiJikoku ) ;
		}
	}

	return iRv ;
}

	// ================================
	//@name UiData - Target間のデータ転送
	// ================================


void CPropEditUi_EkiJikoku::UiDataFromTarget() 
{
	//◇[単一選択時]
	//　○駅扱はTarget を反映
	//　○着時刻・発時刻
	//　　駅扱が通過・停車なら、有効・Targetを反映
	//　　経由なしなら有効･空
	//　　運行なしなら有効･空
	if ( m_pTarget->size() == 1 )
	{
		CentDedRessya* pRessya = m_pTarget->get( 0 ) ;
		UIDATA aUiData ;
		UiDataFromTarget( &aUiData , pRessya , m_iEkiOrder ) ;
		//	駅扱が通過・停車なら、有効・Targetを反映
		if ( aUiData.iEkiatsukai == 1 
			|| aUiData.iEkiatsukai == 2 )
		{
			aUiData.bChakujikokuIsEnable = true ;
			aUiData.bHatsujikokuIsEnable = true ;
		}
		//	経由なしなら有効・空
		else if ( aUiData.iEkiatsukai == 3 )
		{
			aUiData.bChakujikokuIsEnable = true ;
			aUiData.bHatsujikokuIsEnable = true ;
			aUiData.strChakujikoku = L"" ;
			aUiData.strHatsujikoku = L"" ;
		}
		// 運行なしなら有効・空
		else 
		{
			aUiData.bChakujikokuIsEnable = true ;
			aUiData.bHatsujikokuIsEnable = true ;
			aUiData.strChakujikoku = L"" ;
			aUiData.strHatsujikoku = L"" ;
		}
		m_UiData = aUiData ;
	}

	//◇[複数選択時]
	//　○駅扱いはTargetを反映
	//　○着時刻・発時刻は無効・空
	else if ( m_pTarget->size() > 1 )
	{

		for ( int i = 0 ; i < m_pTarget->size() ; i ++ )
		{
			UIDATA aUiData ;
			CentDedRessya* pRessya = m_pTarget->get( i ) ;
			UiDataFromTarget( &aUiData , pRessya , m_iEkiOrder ) ;

			// 複数選択の内容を m_UiData に反映する。
			if ( i == 0 )
			{
				m_UiData.iEkiatsukai = aUiData.iEkiatsukai ;
				m_UiData.bChakujikokuIsEnable = false ;
				m_UiData.bHatsujikokuIsEnable = false ;
				m_UiData.strChakujikoku = L"" ;
				m_UiData.strHatsujikoku = L"" ;
			}
			else
			{
				// iEkiatsukai
				if ( m_UiData.iEkiatsukai >= 0 
					&&  m_UiData.iEkiatsukai != aUiData.iEkiatsukai )
				{
					m_UiData.iEkiatsukai = -1 ;
				}
				// strChakujikoku
				if ( m_UiData.bChakujikokuIsEnable )
				{
					if ( m_UiData.strChakujikoku.length() > 0 
						&& m_UiData.strChakujikoku != aUiData.strChakujikoku )
					{
						m_UiData.strChakujikoku = L"" ;
					}
				}
				// strChakujikoku
				if ( m_UiData.bHatsujikokuIsEnable )
				{
					if ( m_UiData.strHatsujikoku.length() > 0 
						&& m_UiData.strHatsujikoku != aUiData.strHatsujikoku )
					{
						m_UiData.strHatsujikoku = L"" ;
					}
				}
			}
		}
	}
	// --------------------------------
	m_UiData.bModifyHatsujikoku = *m_pbModifyHatsujikoku ;

}
int CPropEditUi_EkiJikoku::adjustUiData( const UIDATA& aUiDataPrev , EShowError eShowError ) 
{
	int iRv = 0 ;


	//◇[単一選択時]
	if ( m_pTarget->size() == 1 )
	{
		//　○【駅扱】駅扱が運行なし・経由なしで、着時刻か発時刻が変更されたら、駅扱は停車にする
		if ( iRv >= 0 )
		{
			if ( ( m_UiData.iEkiatsukai == 0 || m_UiData.iEkiatsukai == 3 )
				&& ( aUiDataPrev.strChakujikoku != m_UiData.strChakujikoku
					|| aUiDataPrev.strHatsujikoku != m_UiData.strHatsujikoku ) 	)
			{
				m_UiData.iEkiatsukai = 1 ;	
			}
		}
		//　○【着時刻・発時刻】駅扱が運行なし・経由なしに変更されたら、着時刻・発時刻は無効にする
		//　○【着時刻・発時刻】駅扱が停車・通過に変更されたら、着時刻・発時刻は有効にする。
		if ( iRv >= 0 )
		{
			if ( aUiDataPrev.iEkiatsukai !=  m_UiData.iEkiatsukai )
			{
				if ( m_UiData.iEkiatsukai == 0 || m_UiData.iEkiatsukai == 3 )
				{
					m_UiData.bChakujikokuIsEnable = false ;
					m_UiData.bHatsujikokuIsEnable = false ;
				}
				else 
				{
					m_UiData.bChakujikokuIsEnable = true ;
					m_UiData.bHatsujikokuIsEnable = true ;
				}
			}
		}

		//	直前の時刻Orderの駅時刻を取得
		//	この値は、時が省略されて分のみが入力されたときに、
		//	時を補完するのに使います。
		CdDedJikoku jikokuRevOrder ;
		if ( iRv >= 0 )
		{
			if ( m_UiData.bChakujikokuIsEnable )
			{
				CentDedRessya* pRessya = m_pTarget->get( 0 ) ;
				CdDedJikokuOrder aJikokuOrderRev = pRessya->findrevJikoku( 
					CdDedJikokuOrder( m_iEkiOrder - 1 , CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ) ;
				if ( !aJikokuOrderRev.getIsNull() )
				{
					jikokuRevOrder = pRessya->getEkiJikoku( aJikokuOrderRev ) ;
				}
			}
		}
		//jikokuRevOrder = 直前の時刻Orderの駅時刻



		//　○【着時刻】着時刻が変更されたら、
		//　　(1)文字列を半角に変換
		//　　(2)着時刻に2桁入力なら、時を補完します。
		if ( iRv >= 0 )
		{
			if ( aUiDataPrev.strChakujikoku != m_UiData.strChakujikoku )
			{
				if ( m_UiData.bChakujikokuIsEnable )
				{
					CdDedJikoku aJikoku ;
					int iResult = getJikokuFromUI( 
						m_UiData.strChakujikoku , 
						jikokuRevOrder , 
						&aJikoku ) ;
					if ( iResult >= 0 )
					{
						m_UiData.strChakujikoku = g_CdDedJikokuConv.encode( aJikoku ) ;
					}
				}
			}
		}

		//	直前の時刻Orderを着時刻で更新。
		//	この値は、時が省略されて分のみが入力されたときに、
		//	時を補完するのに使います。
		if ( iRv >= 0 )
		{
			CdDedJikoku aJikoku( m_UiData.strChakujikoku ) ;
			if ( !aJikoku.isNull() )
			{
				jikokuRevOrder = aJikoku ;
			}
		}
		//jikokuRevOrder = 直前の時刻Orderの駅時刻。
		//	但し、着時刻の入力があれば、着時刻。

		//　○【発時刻】発時刻が変更されたら、
		//　　(1)文字列を半角に変換
		//　　(2)着時刻に2桁入力なら、時を補完します。
		if ( iRv >= 0 )
		{
			if ( aUiDataPrev.strHatsujikoku != m_UiData.strHatsujikoku )
			{
				if ( m_UiData.bHatsujikokuIsEnable )
				{
					CdDedJikoku aJikoku ;
					int iResult = getJikokuFromUI( 
						m_UiData.strHatsujikoku , 
						jikokuRevOrder , 
						&aJikoku ) ;
					if ( iResult >= 0 )
					{
						m_UiData.strHatsujikoku = g_CdDedJikokuConv.encode( aJikoku ) ;
					}
				}
			}
		}
		//　○【発時刻】着時刻が変更され、『時刻の繰上げ・繰り下げ』=『有効』で、発時刻が入力済みなら、発時刻の繰上げ・繰り下げを行います。　
		if ( iRv >= 0 )
		{
			if ( aUiDataPrev.strChakujikoku != m_UiData.strChakujikoku )
			{
				if ( m_UiData.bModifyHatsujikoku )
				{
					//	着時刻の前回値・現在値・発時刻の入力を取得
					CdDedJikoku	jikokuChakuPrev( aUiDataPrev.strChakujikoku ) ;
					CdDedJikoku	jikokuChaku( m_UiData.strChakujikoku ) ;
					CdDedJikoku jikokuHatsu( m_UiData.strHatsujikoku ) ;
					if ( !jikokuChakuPrev.isNull() 
						&& !jikokuChaku.isNull()
						&& !jikokuHatsu.isNull() )
					{
						jikokuHatsu.addSeconds( jikokuChaku.subJikoku( jikokuChakuPrev ) );
						m_UiData.strHatsujikoku = g_CdDedJikokuConv.encode( jikokuHatsu ) ;
					}
				}
				
			}
		}
		//　○【着時刻】着時刻が空文字列でないなら、
		//	値の時刻への変換を試みて、不正ならエラー表示
		if ( iRv >= 0 )
		{
			CdDedJikoku aJikoku ;
			int iResult = aJikoku.decode( m_UiData.strChakujikoku ) ;
			if ( iResult < 0 )
			{
				iRv = -11 ;
			}
		}

		//　○【発時刻】発時刻が空文字列でないなら、
		//	値の時刻への変換を試みて、不正ならエラー表示
		if ( iRv >= 0 )
		{
			CdDedJikoku aJikoku ;
			int iResult = aJikoku.decode( m_UiData.strHatsujikoku ) ;
			if ( iResult < 0 )
			{
				iRv = -12 ;
			}
		}
		

	}
	//◇［複数選択時]
	else if ( m_pTarget->size() > 1 )
	{
		if ( iRv >= 0 )
		{
			//　○【着時刻・発時刻】着時刻・発時刻は無効・空
			m_UiData.bChakujikokuIsEnable = false ;
			m_UiData.bHatsujikokuIsEnable = false ;
		}
	}
	// --------------------------------
	//	エラーメッセージを表示します
	// --------------------------------
	if ( iRv < 0 && eShowError != EShowError_None )
	{
		switch( iRv )
		{
		case -11 :
			if ( eShowError == EShowError_All 
				|| aUiDataPrev.strChakujikoku != m_UiData.strChakujikoku )
			{
				showError( ERRMSG_INVALID_CHAKUJIKOKU ) ;
				setFocus( offsetof( UIDATA , strChakujikoku )) ;
			}
			break ;
		case -12 :
			if ( eShowError == EShowError_All 
				|| aUiDataPrev.strHatsujikoku != m_UiData.strHatsujikoku )
			{
				showError( ERRMSG_INVALID_HATSUJIKOKU ) ;
				setFocus( offsetof( UIDATA , strHatsujikoku ) );
			}
			break ;
		}

	}
	return iRv ;
}	
		
int CPropEditUi_EkiJikoku::UiDataToTarget( const UIDATA& aUiDataPrev ) 
{
	int iRv = 0 ; 
	for ( int i = 0 ; iRv >= 0 && i < m_pTarget->size() ; i ++ )
	{
		CentDedRessya* pRessya = m_pTarget->get( i ) ; 
		iRv = UiDataToTarget( aUiDataPrev , 
			m_UiData , pRessya , m_iEkiOrder ,
			m_UiData.bModifyHatsujikoku ) ; 
	}
	
	if ( aUiDataPrev.bModifyHatsujikoku != m_UiData.bModifyHatsujikoku )
	{
		*m_pbModifyHatsujikoku = m_UiData.bModifyHatsujikoku ;
	}
	return iRv ;
}	



	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUi_EkiJikoku::CPropEditUi_EkiJikoku( 
		Mu<CentDedRessya*>* pTarget , 
		bool* pbModifyHatsujikoku ,
		int iEkiOrder ) 
		: m_pTarget( pTarget ) 
		, m_pbModifyHatsujikoku( pbModifyHatsujikoku )
		, m_iEkiOrder( iEkiOrder )
{
}



} //namespace ViewJikokuhyou

