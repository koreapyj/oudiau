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
//	CconvCentDed.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include <vector>
#include <map>
using namespace std ;

#include "str\strToInt.h"
#include "str\stringSplit.h"
#include "Ou\OuNew.h"
#include "Ou\dynamic_castOu.h"
#include "Mu\CaMui.h"
#include "DcdCd\DcDrawProp\CconvDcDrawProp.h"
//#include "DedRosenFileData\CdDedDispProp.h"
#include "CconvCentDed.h"

using namespace OuLib::Str ;
using namespace OuLib::Str::OuPropertiesText;
using namespace OuLib::Str::OuPropertiesText::ErrorInfo;

/*delete 遅いので抑止
#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
*/

namespace entDed{

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone ,
	CdDedJikoku::CConv::ESecond_NotIfZero ) ;
// ********************************
//	CdColorProp
// ********************************

/**
	aCdColorProp を文字列に変換します。
@param aCdColorProp [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
*/
static wstring CdColorProp_to_string( const CdColorProp& aCdColorProp )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_to_string( aCdColorProp ) ;
	
}


/**
	文字列を aCdColorProp に変換します。
@param aString [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
 */
static CdColorProp CdColorProp_from_string( const wstring& aString  )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_from_string( aString ) ;
}


// ********************************
//	CentDedEki
// ********************************
const wchar_t nameEkimei[] = L"Ekimei" ;
const wchar_t nameEkijikokukeisiki[] = L"Ekijikokukeisiki" ;
const wchar_t nameEkikibo[] = L"Ekikibo" ;
const wchar_t nameKyoukaisen[] = L"Kyoukaisen" ;
const wchar_t nameDiagramRessyajouhouHyoujiKudari[] = L"DiagramRessyajouhouHyoujiKudari" ;
const wchar_t nameDiagramRessyajouhouHyoujiNobori[] = L"DiagramRessyajouhouHyoujiNobori" ;

const CEnumToString< CentDedEki::EEkijikokukeisiki >& 
CconvCentDed::getEEkijikokukeisikiToString()
{
	static CEnumToString< CentDedEki::EEkijikokukeisiki >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::Jikokukeisiki_Hatsu , L"Jikokukeisiki_Hatsu" ) ;
		aCEnumToString.add( CentDedEki::Jikokukeisiki_Hatsuchaku , L"Jikokukeisiki_Hatsuchaku" ) ;
		aCEnumToString.add( CentDedEki::Jikokukeisiki_KudariChaku , L"Jikokukeisiki_KudariChaku" ) ;
		aCEnumToString.add( CentDedEki::Jikokukeisiki_NoboriChaku , L"Jikokukeisiki_NoboriChaku"  ) ;
	}
	return aCEnumToString ;
}


const CEnumToString< CentDedEki::EEkikibo >& 
CconvCentDed::getEEkikiboToString()
{
	static CEnumToString< CentDedEki::EEkikibo >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::Ekikibo_Ippan , L"Ekikibo_Ippan" ) ;
		aCEnumToString.add( CentDedEki::Ekikibo_Syuyou , L"Ekikibo_Syuyou" ) ;
	}
	return aCEnumToString ;
}


const CEnumToString< CentDedEki::EDiagramRessyajouhouHyouji >& 
CconvCentDed::getEDiagramRessyajouhouHyoujiToString()
{
	static CEnumToString< CentDedEki::EDiagramRessyajouhouHyouji >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::DiagramRessyajouhouHyouji_Origin , 
			L"" ) ;
		aCEnumToString.add( CentDedEki::DiagramRessyajouhouHyouji_Anytime , 
			L"DiagramRessyajouhouHyouji_Anytime" ) ;
		aCEnumToString.add( CentDedEki::DiagramRessyajouhouHyouji_Not , 
			L"DiagramRessyajouhouHyouji_Not" ) ;
	}
	return aCEnumToString ;
}

int CconvCentDed::CentDedEki_To_OuPropertiesText( 
			const CentDedEki& aCentDedEki , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------	
	//1.Ekimei
	if ( iRv >= 0 ){
		//memo:
		//	以前は、空文字列の駅名はエラーでしたが、
		//	現在はこれを認めるようになりました。
		pCNodeContainer->setValue( nameEkimei , 
			aCentDedEki.getEkimei() ) ;
	}
	//2.Ekijikokukeisiki
	if ( iRv >= 0 )
	{
		wstring strValue = getEEkijikokukeisikiToString().wstringOf( 
			aCentDedEki.getEkijikokukeisiki() ) ;
		pCNodeContainer->setValue( nameEkijikokukeisiki , strValue ) ;
	}

	//3.Ekikibo
	if ( iRv >= 0 )
	{
		wstring strValue = getEEkikiboToString().wstringOf( 
			aCentDedEki.getEkikibo() ) ;
		pCNodeContainer->setValue( nameEkikibo , 
				strValue ) ;
	}
	//4.Kyoukaisen
	if ( iRv >= 0 )
	{
		if ( aCentDedEki.getKyoukaisen() )
		{
			pCNodeContainer->setValue( nameKyoukaisen ,L"1" ) ;
		}
	}
	//5. m_bDiagramRessyajouhouHyoujiKudari ;
	if ( iRv >= 0 )
	{
		wstring strValue = getEDiagramRessyajouhouHyoujiToString().wstringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiKudari() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( 
				nameDiagramRessyajouhouHyoujiKudari , strValue ) ;
		}
	}
	//6.m_bDiagramRessyajouhouHyoujiNobori
	if ( iRv >= 0 )
	{
		wstring strValue = getEDiagramRessyajouhouHyoujiToString().wstringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiNobori() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( nameDiagramRessyajouhouHyoujiNobori ,strValue) ;
		}
	}
	// --------------------------------	
	return ( iRv ) ;
}

int CconvCentDed::CentDedEki_From_OuPropertiesText( 
			CentDedEki* pCentDedEki ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	
	CentDedEki	aCentDedEki ; 
	// --------------------------------	
	//1.Ekimei
	if ( iRv >= 0 )
	{
		wstring strValue = pCNodeContainer->getValue( nameEkimei ) ;
		//memo:
		//	以前は、空文字列の駅名はエラーでしたが、
		//	現在はこれを認めるようになりました。

		aCentDedEki.setEkimei( strValue ) ;
	}

	//2.Ekijikokukeisiki
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameEkijikokukeisiki );
		CentDedEki::EEkijikokukeisiki eValue = CentDedEki::Jikokukeisiki_Hatsu ;
		if ( getEEkijikokukeisikiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_EkijikokukeisikiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameEkijikokukeisiki , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -22 ;	//	Ekijikokukeisiki の値が不正です。
		}
		else
		{
			aCentDedEki.setEkijikokukeisiki( eValue ) ; 
		}

	}

	//3.Ekikibo
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameEkikibo );
		CentDedEki::EEkikibo eValue = CentDedEki::Ekikibo_Ippan ;
		if ( getEEkikiboToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_EkikiboIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameEkikibo , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -32 ;	//	Ekikibo の値が不正です。
		}
		else
		{
			aCentDedEki.setEkikibo( eValue ) ; 
		}
	}
	//4.Kyoukaisen
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameKyoukaisen ) ; 
		aCentDedEki.setKyoukaisen( _wtoi( strValue.c_str() ) == 1 ) ;
	}

	//5. m_eDiagramRessyajouhouHyoujiKudari ;
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameDiagramRessyajouhouHyoujiKudari ) ; 
		CentDedEki::EDiagramRessyajouhouHyouji eValue = 
			CentDedEki::DiagramRessyajouhouHyouji_Origin ;
		if ( strValue.length() > 0 && 
			getEDiagramRessyajouhouHyoujiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramRessyajouhouHyoujiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramRessyajouhouHyoujiKudari , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
		}
		else
		{
			aCentDedEki.setDiagramRessyajouhouHyoujiKudari( eValue ) ;
		}
	}
	//6.m_eDiagramRessyajouhouHyoujiNobori
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameDiagramRessyajouhouHyoujiNobori ) ; 
		CentDedEki::EDiagramRessyajouhouHyouji eValue = 
			CentDedEki::DiagramRessyajouhouHyouji_Origin ;
		if ( strValue.length() > 0 && 
			getEDiagramRessyajouhouHyoujiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramRessyajouhouHyoujiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramRessyajouhouHyoujiNobori , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
		}
		else
		{
			aCentDedEki.setDiagramRessyajouhouHyoujiNobori( eValue ) ;
		}
	}
	// --------------------------------
	if ( iRv >= 0 ){
		*pCentDedEki = aCentDedEki ;
	}
	return ( iRv ) ;
}

	// ********************************
	//	CentDedEkiCont
	// ********************************
const wchar_t nameEki[] = L"Eki" ;
	
int CconvCentDed::CentDedEkiCont_To_OuPropertiesText( 
			const CentDedEkiCont& aCentDedEkiCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxEki = 0 ; iRv >= 0 && idxEki < aCentDedEkiCont.size() ; idxEki ++ )
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameEki ) ) ;
			int iResult = CentDedEki_To_OuPropertiesText(
				aCentDedEkiCont.get( idxEki ) ,
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	

int CconvCentDed::CentDedEkiCont_From_OuPropertiesText( 
			CentDedEkiCont* pCentDedEkiCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxEki = 0 ; iRv >= 0 && idxEki < pCNodeContainer->sizeInName( nameEki )  ; idxEki ++ )
		{
			Ou<const CDirectory> pCDirectory ; 
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu<const CDirectory>( 
					pCNodeContainer->getInName( nameEki , idxEki ) ) ;
				if ( pCDirectory == NULL )
				{
					COuErrorInfo aCOuErrorInfo( ERRREASON_EkiIsNotDirectory() ) ;
					aCOuErrorInfo.getProp()->setValue( 
						ERRPROP_Index() , wstringOf( idxEki ) ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -101 ;	//	Eki がディレクトリではありません。

				}
			}
			//pCDirectory = 対応するディレクトリ

			CentDedEki aCentDedEki ;
			if ( iRv >= 0 )
			{
				int iResult = CentDedEki_From_OuPropertiesText( 
					&aCentDedEki , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				if ( iResult < 0 )
				{
					iRv = iResult ;
					//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
					//	-	-32 ;	//	Ekikibo の値が不正です。
					//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
					//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
				}
			}
			//aCentDedEki = Directory の内容を反映しました。
			if ( iRv >= 0 )
			{
				pCentDedEkiCont->insert( aCentDedEki ) ;
			}
				
		}
	}
	return iRv ;
}


// ********************************
//	CentDedRessyasyubetsu
// ********************************

const wchar_t nameSyubetsumei[]=L"Syubetsumei" ;
const wchar_t nameRyakusyou[]=L"Ryakusyou" ;
const wchar_t nameJikokuhyouMojiColor[]=L"JikokuhyouMojiColor" ;
const wchar_t nameJikokuhyouFontIndex[] = L"JikokuhyouFontIndex" ;
const wchar_t nameDiagramSenColor[]=L"DiagramSenColor" ;
const wchar_t nameDiagramSenStyle[]=L"DiagramSenStyle" ;
const wchar_t nameDiagramSenIsBold[]=L"DiagramSenIsBold" ;
const wchar_t nameDiagramRessyaFont[] = L"DiagramRessyaFont" ;
const wchar_t nameStopMarkDrawType[] = L"StopMarkDrawType" ;

const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
CconvCentDed::getESenStyleToString()
{
	static CEnumToString< CentDedRessyasyubetsu::ESenStyle >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Jissen , L"SenStyle_Jissen" ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Hasen , L"SenStyle_Hasen" ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Tensen , L"SenStyle_Tensen") ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Ittensasen , L"SenStyle_Ittensasen" ) ;
	}
	return aCEnumToString ;
}

const CEnumToString< CentDedRessyasyubetsu::EStopMarkDrawType >& 
CconvCentDed::getEStopMarkDrawTypeToString()
{
	static CEnumToString< CentDedRessyasyubetsu::EStopMarkDrawType >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop , L"EStopMarkDrawType_DrawOnStop" ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_Nothing , L"EStopMarkDrawType_Nothing" ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnPass , L"EStopMarkDrawType_DrawOnPass") ;
	}
	return aCEnumToString ;
}

int CconvCentDed::CdDiagramLineStyle_To_OuPropertiesText( 
	const CentDedRessyasyubetsu::CdDiagramLineStyle& aCdDiagramLineStyle , 
	OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//5.DiagramSenColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramSenColor , 
			CdColorProp_to_string( aCdDiagramLineStyle.getDiagramSenColor() ) ) ;
	}

	//6.DiagramSenStyle
	if ( iRv >= 0 )
	{
		wstring strValue = getESenStyleToString().wstringOf( aCdDiagramLineStyle.getDiagramSenStyle() ) ;
		pCNodeContainer->setValue( nameDiagramSenStyle , strValue ) ;

	}

	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		bool bValue = aCdDiagramLineStyle.getDiagramSenIsBold();
		if ( bValue )
		{
			pCNodeContainer->setValue( nameDiagramSenIsBold , L"1" ) ;
		}
	}
	return iRv ;
}

int CconvCentDed::CdDiagramLineStyle_From_OuPropertiesText( 
	CentDedRessyasyubetsu::CdDiagramLineStyle* pCdDiagramLineStyle ,
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	CentDedRessyasyubetsu::CdDiagramLineStyle aCdDiagramLineStyle;

	// --------------------------------	
	//5.DiagramSenColor
	if ( iRv >= 0 ){
		wstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenColor ) ;
		aCdDiagramLineStyle.setDiagramSenColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	
	//6.DiagramSenStyle
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenStyle ) ;
		CentDedRessyasyubetsu::ESenStyle eValue = CentDedRessyasyubetsu::SenStyle_Jissen ;
		if ( getESenStyleToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo	aCOuErrorInfo( ERRREASON_DiagramSenStyleIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramSenStyle , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -52 ;	//	DiagramSenStyle の値が不正です。
		}
		else
		{
			aCdDiagramLineStyle.setDiagramSenStyle( eValue ) ;
		}
	}

	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenIsBold ) ;
		unsigned long iValue = wcstoul( strValue.c_str() , NULL , 10 ) ;
		aCdDiagramLineStyle.setDiagramSenIsBold( iValue != 0 ) ;
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCdDiagramLineStyle = aCdDiagramLineStyle ;
	}
	return iRv ;
}


int CconvCentDed::CentDedRessyasyubetsu_To_OuPropertiesText( 
			const CentDedRessyasyubetsu& aCentDedRessyasyubetsu , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//1.Syubetsumei
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getSyubetsumei().empty() )
		{
			iRv = -11 ;	//	Syubetsumei が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue( nameSyubetsumei , 
				aCentDedRessyasyubetsu.getSyubetsumei() ) ;
		}
	}


	//2.Ryakusyou
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getRyakusyou().empty() )
		{

		}
		else
		{
			pCNodeContainer->setValue( nameRyakusyou , 
				aCentDedRessyasyubetsu.getRyakusyou() ) ;
		}
	}

	//3.JikokuhyouMojiColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameJikokuhyouMojiColor , 
			CdColorProp_to_string( aCentDedRessyasyubetsu.getJikokuhyouMojiColor() ) ) ;
	}
	//4.JikokuhyouFontIndex
	if ( iRv >= 0 )
	{
		int iValue = aCentDedRessyasyubetsu.getJikokuhyouFontIndex() ;
		{
			pCNodeContainer->setValue( 
				nameJikokuhyouFontIndex , 
				wstringOf( iValue ) ) ;
		}
	}
	//5.DiagramSenColor
	//6.DiagramSenStyle
	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		CdDiagramLineStyle_To_OuPropertiesText( 
			aCentDedRessyasyubetsu.getCdDiagramLineStyle() ,
			pCNodeContainer ) ;
	}

	//9 StopMarkDrawType
	if ( iRv >= 0 )
	{
		wstring strValue = getEStopMarkDrawTypeToString().wstringOf( aCentDedRessyasyubetsu.getStopMarkDrawType() ) ;
		pCNodeContainer->setValue( nameStopMarkDrawType , strValue ) ;
	}
	return ( iRv ) ;
}


int CconvCentDed::CentDedRessyasyubetsu_From_OuPropertiesText( 
			CentDedRessyasyubetsu* pCentDedRessyasyubetsu ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	CentDedRessyasyubetsu aCentDedRessyasyubetsu ;

	// --------------------------------	
	//1.Syubetsumei
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameSyubetsumei ) ;
		if ( strValue.empty() )
		{
			COuErrorInfo	aCOuErrorInfo( ERRREASON_SyubetsumeiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameSyubetsumei , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -11 ;	//	Syubetsumei が指定されていません。
		}
		else
		{
			aCentDedRessyasyubetsu.setSyubetsumei( strValue ) ;
		}
	}
	
	//2.Ryakusyou
	if ( iRv >= 0 ){
		wstring	strValue = pCNodeContainer->getValue( nameRyakusyou ) ;
		if ( strValue.empty() ){
		}	else	{
			aCentDedRessyasyubetsu.setRyakusyou( strValue ) ;
		}
	}
	
	//3.JikokuhyouMojiColor
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( 
			nameJikokuhyouMojiColor ) ;
		aCentDedRessyasyubetsu.setJikokuhyouMojiColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	//4.JikokuhyouFontIndex
	if ( iRv >= 0 )
	{
		wstring strValue = pCNodeContainer->getValue( 
			nameJikokuhyouFontIndex ) ;
		if ( !strValue.empty() )
		{
			int iValue = intOf( strValue ) ;
			if ( !( 0 <= iValue && iValue < CentDedRessyasyubetsu::JIKOKUHYOUFONT_COUNT ) )
			{
				COuErrorInfo	aCOuErrorInfo( ERRREASON_InvalidValueFormat() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameJikokuhyouFontIndex ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -101 ;	//	値の形式が正しくありません。
			}
			else
			{
				aCentDedRessyasyubetsu.setJikokuhyouFontIndex( iValue ) ;
			}
		}
	}
	//5.DiagramSenColor
	//6.DiagramSenStyle
	//7.DiagramSenIsBold
	{
		CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle ;
		int iResult = CdDiagramLineStyle_From_OuPropertiesText( 
			&aCdDiagramLineStyle ,
			pCNodeContainer ,
			pCOuErrorInfoContainer ) ;
		//iResult = 
		//	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
			//iRv = 
			//	-52 ;	//	DiagramSenStyle の値が不正です。
		}
		else
		{
			aCentDedRessyasyubetsu.setCdDiagramLineStyle( aCdDiagramLineStyle ) ;
		}
	}
	

	//9 StopMarkDrawType
	if ( iRv >= 0 )
	{
		CentDedRessyasyubetsu::EStopMarkDrawType eStopMarkDrawType = 
			CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop ;
		wstring strValue = pCNodeContainer->getValue( nameStopMarkDrawType ) ;
		if ( !strValue.empty() )
		{
			getEStopMarkDrawTypeToString().fromString( strValue , &eStopMarkDrawType ) ;
		}
		aCentDedRessyasyubetsu.setStopMarkDrawType( eStopMarkDrawType ) ;
	}

	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCentDedRessyasyubetsu = aCentDedRessyasyubetsu ;
	}

	return ( iRv ) ;
}

void CconvCentDed::CentDedRessyasyubetsu_to_CDcdFreeLineProp(
	CdColorProp aCOLORREF ,
	CentDedRessyasyubetsu::ESenStyle eSenStyle , 
	bool bIsBold , 
	CdDcdFreeLineProp* pCdLineProp )	
{
		pCdLineProp->setColor( aCOLORREF ) ;
		switch( eSenStyle ){
		 // 実線 
		 case CentDedRessyasyubetsu::SenStyle_Jissen :
			pCdLineProp->setLinestyle( LINESTYLE_SOLID ) ;
			break ;
		 // 破線
		 case CentDedRessyasyubetsu::SenStyle_Hasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH ) ;
			break ;
		 // 点線
		 case CentDedRessyasyubetsu::SenStyle_Tensen :
			pCdLineProp->setLinestyle( LINESTYLE_DOT ) ;
			break ;
		 // 一点鎖線
		 case CentDedRessyasyubetsu::SenStyle_Ittensasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH_DOT ) ;
			break ;
		}
		pCdLineProp->setLogicalunitWidth( bIsBold ? 2 : 1 ) ;

}
	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
const wchar_t nameRessyasyubetsu[] = L"Ressyasyubetsu" ;
	

int CconvCentDed::CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			const CentDedRessyasyubetsuCont& aCentDedRessyasyubetsuCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ; iRv >= 0 && idx < aCentDedRessyasyubetsuCont.size() ; idx ++ )
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessyasyubetsu ) ) ;
			int iResult = CentDedRessyasyubetsu_To_OuPropertiesText(
				aCentDedRessyasyubetsuCont.get( idx ) ,
				pCDirectory->getCNodeContainer() ) ;
			//	-	-11 ;	//	Syubetsumei が指定されていません。
			//	-	-52 ;	//	DiagramSenStyle の値が不正です。
			if ( iResult < 0 )
			{
				//	-	-11 ;	//	Syubetsumei が指定されていません。
				//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
int CconvCentDed::CentDedRessyasyubetsuCont_From_OuPropertiesText( 
			CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ; iRv >= 0 && idx < pCNodeContainer->sizeInName( nameRessyasyubetsu )  ; idx ++ )
		{
			Ou<const CDirectory> pCDirectory ; 
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu<const CDirectory>( 
					pCNodeContainer->getInName( nameRessyasyubetsu , idx ) ) ;
				if ( pCDirectory == NULL )
				{
					COuErrorInfo aCOuErrorInfo( ERRREASON_RessyasyubetsuIsNotDirectory() ) ;
					aCOuErrorInfo.getProp()->setValue( 
						ERRPROP_Index() , wstringOf( idx ) ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -101 ;	//	Ressyasyubetsu がディレクトリではありません。

				}
			}
			//pCDirectory = 対応するディレクトリ

			CentDedRessyasyubetsu aCentDedRessyasyubetsu ;
			if ( iRv >= 0 )
			{
				int iResult = CentDedRessyasyubetsu_From_OuPropertiesText( 
					&aCentDedRessyasyubetsu , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//	-	-11 ;	//	Syubetsumei が指定されていません。
				//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				if ( iResult < 0 )
				{
					iRv = iResult ;
					//	-	-11 ;	//	Syubetsumei が指定されていません。
					//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				}
			}
			//aCentDedRessyasyubetsu = Directory の内容を反映しました。
			if ( iRv >= 0 )
			{
				pCentDedRessyasyubetsuCont->insert( aCentDedRessyasyubetsu ) ;
			}
				
		}
	}
	return iRv ;
}

	// ********************************
	//	CentDedEkiJikoku
	// ********************************
wstring CconvCentDed::CentDedEkiJikoku_To_string( 
			const CentDedEkiJikoku* pCentDedEkiJikoku ) 
{
	wstring	strEkiatsukai ;
	wstring strChaku ;
	wstring strHatsu ;
	//	駅扱
	if ( pCentDedEkiJikoku->getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None )
	{
		strEkiatsukai = wstringOf( 
			(int)pCentDedEkiJikoku->getEkiatsukai() ) ;
	}
	//	着時刻
	if ( !pCentDedEkiJikoku->getChakujikoku().isNull() )
	{
		strChaku = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getChakujikoku() ) ;
	}
	//	発時刻
	if ( !pCentDedEkiJikoku->getHatsujikoku().isNull() )
	{
		strHatsu = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getHatsujikoku() ) ;
	}

	wstring	strEkijikoku ;
	strEkijikoku.reserve( 32 ) ;
	if ( !strEkiatsukai.empty() )
	{
		strEkijikoku += strEkiatsukai ;
		if ( !strChaku.empty() || !strHatsu.empty() )
		{
			strEkijikoku += ';' ;
			if ( !strChaku.empty() )
			{
				strEkijikoku += strChaku ;
				strEkijikoku += '/' ;
			}
			strEkijikoku += strHatsu ;
		}
	}
	return strEkijikoku ;
}

int CconvCentDed::CentDedEkiJikoku_From_string( 
			CentDedEkiJikoku* pCentDedEkiJikoku , 
			const std::wstring strValue ) 
{
	int iRv = 0 ;
	// --------------------------------
	wstring strEkijikoku = strValue ;
	wstring	strEkiatsukai ;
	wstring strChaku ;
	wstring strHatsu ;

	wstring::size_type pos = 0 ;
	pos = strEkijikoku.find( ';' ) ;
	if ( pos != wstring::npos )
	{
		strEkiatsukai = strEkijikoku.substr( 0 , pos ) ;
		strEkijikoku.erase( 0 , pos + 1 ) ;
		
		pos = strEkijikoku.find( '/' ) ;
		if ( pos != wstring::npos )
		{
			strChaku = strEkijikoku.substr( 0 , pos ) ;
			strEkijikoku.erase( 0 , pos + 1 ) ;
		}
		strHatsu = strEkijikoku ;
	}
	else
	{
		strEkiatsukai = strEkijikoku ;
	}
	//strEkiatsukai = 駅扱・空文字列は『運行なし』。"1"～"3" ;
	//strChaku = 着時刻
	//strHatsu = 発時刻
	
	int iEkiatsukai = 0 ;
	if ( !strEkiatsukai.empty() )
	{
		iEkiatsukai = _wtoi( strEkiatsukai.c_str() ) ;
	}
	if ( !( 0 <= iEkiatsukai && iEkiatsukai < 4 ) )
	{
		iEkiatsukai = 0 ;
	}
	CdDedJikoku jikokuChaku( strChaku ) ;
	CdDedJikoku jikokuHatsu( strHatsu ) ;
	CentDedEkiJikoku	aCentDedEkiJikoku( 
		(CentDedEkiJikoku::EEkiatsukai)iEkiatsukai , 
		jikokuChaku , jikokuHatsu ) ;

	// --------------------------------
	if ( pCentDedEkiJikoku != NULL )
	{
		*pCentDedEkiJikoku = aCentDedEkiJikoku ;
	}
	return iRv ;
}

// ********************************
//	CentDedRessya
// ********************************

const CEnumToString<ERessyahoukou>& CconvCentDed::getERessyahoukouToString()
{
	static CEnumToString<ERessyahoukou> aEnumToString ;
	if ( aEnumToString.size() == 0 )
	{
		aEnumToString.add( Ressyahoukou_Kudari , L"Kudari" ) ;
		aEnumToString.add( Ressyahoukou_Nobori , L"Nobori" ) ;
	}
	return aEnumToString ;
};
const wchar_t nameRessyahoukou[]=L"Houkou" ;
const wchar_t nameRessyasyubetsuIndex[]=L"Syubetsu" ;
const wchar_t nameEkiJikoku3[]=L"EkiJikoku" ;
const wchar_t nameRessyabangou[]=L"Ressyabangou" ;
const wchar_t nameRessyamei[]=L"Ressyamei" ;
const wchar_t nameGousuu[]=L"Gousuu" ;
const wchar_t nameBikou[]=L"Bikou" ;





int CconvCentDed::CentDedRessya_To_OuPropertiesText( 
			const CentDedRessya* pCentDedRessya , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------
	//0.IsNull
	bool bIsNull = false ;
	if ( iRv >= 0 )
	{
		bIsNull = pCentDedRessya->isNull() ;
	}

	if ( !bIsNull )
	{
		//1.Ressyahoukou
		if ( iRv >= 0 )
		{
			wstring strValue = getERessyahoukouToString().wstringOf( 
				pCentDedRessya->getRessyahoukou() ) ;
			if ( strValue.empty() )
			{
				iRv = -12 ;	//	Ressyahoukou の値が不正です。
			}
			else
			{
				pCNodeContainer->setValue( nameRessyahoukou , 
					strValue ) ;
			}
		}
		//2.RessyasyubetsuIndex ;
		if ( iRv >= 0 )
		{
			pCNodeContainer->setValue( 
				nameRessyasyubetsuIndex , 
				wstringOf( 
					pCentDedRessya->getRessyasyubetsuIndex() 
				) 
			) ;
		}


		//4."Ressyabangou" ;
		if ( iRv >= 0 )
		{
			wstring strValue = pCentDedRessya->getRessyabangou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyabangou , 
					strValue ) ;
			}
		}
		//5."Ressyamei" ;
		if ( iRv >= 0 )
		{
			wstring strValue = pCentDedRessya->getRessyamei() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyamei , 
					 strValue) ;
			}
		}
		//6."Gousuu" ;
		if ( iRv >= 0 )
		{
			wstring strValue = pCentDedRessya->getGousuu() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameGousuu , 
					strValue ) ;
			}
		}
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			vector<wstring>	contstrEkijikoku ;
			int iEkiOrder ;
			for ( iEkiOrder = 0 ; 
					iEkiOrder <= pCentDedRessya->getSyuuchakuEki() ; 
					iEkiOrder ++ )
			{
				CentDedEkiJikoku	aCentDedEkiJikoku = 
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
				wstring	strEkijikoku = CentDedEkiJikoku_To_string(
					&aCentDedEkiJikoku ) ;
				
				contstrEkijikoku.push_back( strEkijikoku ) ;
			}
			wstring strEkijikoku2 = joinc( L',' , contstrEkijikoku ) ;
			pCNodeContainer->setValue( nameEkiJikoku3 ,
						strEkijikoku2 ) ; 
		}
		//7."Bikou" ;
		if ( iRv >= 0 )
		{
			wstring strValue = pCentDedRessya->getBikou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameBikou , 
					strValue ) ;
			}
		}
	}
	// --------------------------------
	return ( iRv ) ;
}

int CconvCentDed::CentDedRessya_From_OuPropertiesText( 
			CentDedRessya* pCentDedRessya ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	// --------------------------------
	bool	bIsNull = false ;
	ERessyahoukou	eRessyahoukou = Ressyahoukou_Kudari ;

	//1.Ressyahoukou
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameRessyahoukou );
		int iResult = getERessyahoukouToString().fromString( 
			strValue , &eRessyahoukou ) ;
		if ( iResult < 0 )
		{
			bIsNull = true ;
		}
	}
	//bIsNull = この列車に関する記述がない場合は、真です。
	//eRessyahoukou = 1.Ressyahoukouの値。
	//	但し、bIsNull が真の場合は、この値は無効です。
	
	if ( !bIsNull )
	{
		int iRessyasyubetsuIndex = -1 ; 
		//2.RessyasyubetsuIndex ;
		if ( iRv >= 0 )
		{
			wstring	strValue = pCNodeContainer->getValue( 
				nameRessyasyubetsuIndex ) ;
			int iValue = _wtoi( strValue.c_str() ) ;
			pCentDedRessya->setRessyasyubetsuIndex( iValue ) ;
		}
		
		//iRessyasyubetsuIndex = 2.RessyasyubetsuIndexの値。
		//	但し、bIsNull が真の場合は、この値は無効です。

		//4."Ressyabangou" ;
		if ( iRv >= 0 )
		{
			wstring	strValue = pCNodeContainer->getValue( nameRessyabangou ) ;
			pCentDedRessya->setRessyabangou( strValue ) ;
		}
		//5."Ressyamei" ;
		if ( iRv >= 0 ){
			wstring	strValue = pCNodeContainer->getValue( nameRessyamei ) ;
			pCentDedRessya->setRessyamei( strValue ) ;
		}
		//6."Gousuu" ;
		if ( iRv >= 0 ){
			wstring	strValue = pCNodeContainer->getValue( nameGousuu ) ;
			pCentDedRessya->setGousuu( strValue ) ;
		}
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			wstring strEkijikoku2 = pCNodeContainer->getValue( 
				nameEkiJikoku3 ) ;
			if ( !strEkijikoku2.empty() )
			{
				deque<wstring>	contstrEkijikoku = 
					splitc< deque< wstring > >( L',' , strEkijikoku2 ) ;
					
				int iEkiOrder ;
				for ( iEkiOrder = 0 ; iRv >= 0 && 
					iEkiOrder < (int)contstrEkijikoku.size() && 
					iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCount() ;
					iEkiOrder ++ )
				{
					wstring strEkijikoku = contstrEkijikoku[iEkiOrder] ;
					CentDedEkiJikoku	aCentDedEkiJikoku ;
					int iResult = CentDedEkiJikoku_From_string( 
						&aCentDedEkiJikoku , 
						strEkijikoku ) ;
					assert( iResult >= 0 ) ;

					pCentDedRessya->setCentDedEkiJikoku( iEkiOrder , 
						aCentDedEkiJikoku ) ;
				}
			}
		}
		//7."Bikou" ;
		if ( iRv >= 0 ){
			wstring	strValue = pCNodeContainer->getValue( nameBikou ) ;
			pCentDedRessya->setBikou( strValue ) ;
		}
	}
	return ( iRv ) ;
}


// ********************************
//	CentDedRessyaCont
// ********************************
const wchar_t nameRessya[]=L"Ressya" ;

int CconvCentDed::CentDedRessyaCont_To_OuPropertiesText( 
			const CentDedRessyaCont* pCentDedRessyaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	
		
	int idxRessya ;
	for ( idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; 
			idxRessya ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessya ) ) ;

		const CentDedRessya*	pCentDedRessya = 
			pCentDedRessyaCont->getMuPtr()->get( idxRessya );
		int iResult = CentDedRessya_To_OuPropertiesText( 
			pCentDedRessya , pCDirectory->getCNodeContainer() ) ;
		//	-	-12 ;	//	Ressyahoukou の値が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
		}
		else
		{
			pCNodeContainer->insert( pCDirectory ) ;
		}
	}
	
	return ( iRv ) ;
}
int CconvCentDed::CentDedRessyaCont_From_OuPropertiesText( 
			CentDedRessyaCont* pCentDedRessyaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	int iRessyaCount = 0 ;

	if ( iRv >= 0 )
	{
		int idxRessya ;
		for ( idxRessya = 0 ; iRv >= 0 && 
			idxRessya < pCNodeContainer->sizeInName( nameRessya )  ; 
				idxRessya ++ )
		{
			Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>( 
				pCNodeContainer->getInName( nameRessya , idxRessya ) ) ;
			if ( pCDirectory != NULL )
			{
				CentDedRessya	aCentDedRessya( 
					pCentDedRessyaCont->getEkiCount() , 
					pCentDedRessyaCont->getRessyahoukou() ) ;
				int iResult = CentDedRessya_From_OuPropertiesText( 
					&aCentDedRessya , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//iResult = 現在、この値が負の数になることはありません
				if ( iResult < 0 )
				{
					iRv = iResult ;
				}
				else
				{
					pCentDedRessyaCont->insert( aCentDedRessya );
				}
			}
		}
	}
	return ( iRv ) ;
}



// ********************************
//	CentDedDia
// ********************************
const wchar_t nameDiaName[]=L"DiaName" ;

int CconvCentDed::CentDedDia_To_OuPropertiesText( 
			const CentDedDia* pCentDedDia , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.DiaName
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiaName , 
			pCentDedDia->getName() ) ;
	}
	//3.Kudari
	//  Nobori
	if ( iRv >= 0 )
	{
		int iRessyahoukou = 0 ; 
		for ( iRessyahoukou = Ressyahoukou_Kudari ; 
				iRessyahoukou <= Ressyahoukou_Nobori ; 
				iRessyahoukou ++ )
		{
			ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
			wstring	strRessyahoukou = 
				getERessyahoukouToString().wstringOf( eRessyahoukou ) ;
			
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( 
				new CDirectory( strRessyahoukou ) ) ;
			int iResult = CentDedRessyaCont_To_OuPropertiesText( 
				pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou ) , 
				pCDirectory->getCNodeContainer() );
			//iResult = 
			//	-12 ;	//	Ressyahoukou の値が不正です。
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	
	return ( iRv ) ;
}



int CconvCentDed::CentDedDia_From_OuPropertiesText( 
			CentDedDia* pCentDedDia ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	
	int iEkiCount = pCentDedDia->getEkiCount() ;

	//1.DiaName
	wstring	strDiaName ;
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameDiaName ) ;
		if ( strValue.length() == 0 )
		{
			ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_DiaNameInvalid() ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -11 ;	//	DiaName が指定されていません。
		}
		else
		{
			strDiaName = strValue ;
			pCentDedDia->setName( strDiaName ) ;
		}
	}

	//3.Ressya[Ressyahoukou_Kudari][]
	//  Ressya[Ressyahoukou_Nobori][]
	if ( iRv >= 0 )
	{
		int iRessyahoukou = 0 ; 
		for ( iRessyahoukou = Ressyahoukou_Kudari ; 
				iRessyahoukou <= Ressyahoukou_Nobori ; 
				iRessyahoukou ++ )
		{
			ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
			wstring	strRessyahoukou = 
				getERessyahoukouToString().wstringOf( eRessyahoukou ) ;

			Ou<const CDirectory> pCDirectory ;
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu< const CDirectory >( 
					pCNodeContainer->getInName( strRessyahoukou , 0 ) ) ;
				if ( pCDirectory == NULL )
				{
					ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_ResyaContIsNotExist() ) ;
					aCOuErrorInfo.getProp()->setValue( ERRPROP_Ressyahoukou() , strRessyahoukou ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -12 ;	//	RessyaContが見つかりません。
				}
			}
			//pCDirectory = Kudari,NoboriのRessyaCont
			if ( iRv >= 0 )
			{
				CentDedRessyaCont	aCentDedRessyaCont( iEkiCount , 
					(ERessyahoukou)iRessyahoukou  , 
					pCentDedDia->getRessyasyubetsuCount() ) ;
				int iResult = CentDedRessyaCont_From_OuPropertiesText( 
					&aCentDedRessyaCont , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer );
				if ( iResult < 0 )
				{
				}
				else
				{
					*pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou ) 
						= aCentDedRessyaCont ; 
				}
			}
		}
	}
	return ( iRv ) ;
}
	// ********************************
	//	CentDedDiaCont
	// ********************************
const wchar_t nameDia[] = L"Dia" ;
	
int CconvCentDed::CentDedDiaCont_To_OuPropertiesText( 
			const CentDedDiaCont* pCentDedDiaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	for ( int idxDia = 0 ; iRv >= 0 && idxDia < pCentDedDiaCont->size() ; idxDia ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameDia ) ) ;
		CentDedDia aCentDedDia = pCentDedDiaCont->get( idxDia ) ; 
		if ( iRv >= 0 )
		{
			int iResult = CentDedDia_To_OuPropertiesText( 
				&aCentDedDia , 
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
int CconvCentDed::CentDedDiaCont_From_OuPropertiesText( 
			CentDedDiaCont* pCentDedDiaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxDia = 0 ; 
			iRv >= 0 && idxDia < pCNodeContainer->sizeInName( nameDia ) ;
			idxDia ++ )
		{
			Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>( 
				pCNodeContainer->getInName( nameDia , idxDia ) ) ;
			if ( pCDirectory != NULL )
			{
				CentDedDia aCentDedDia( pCentDedDiaCont->getEkiCount() , 
					pCentDedDiaCont->getRessyasyubetsuCount() ) ;
				int iResult = CentDedDia_From_OuPropertiesText( 
					&aCentDedDia , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//	-	-11 ;	//	DiaName が指定されていません。
				//	-	-12 ;	//	RessyaContが見つかりません。
				if ( iResult < 0 )
				{
					//	-	-11 ;	//	DiaName が指定されていません。
					//	-	-12 ;	//	RessyaContが見つかりません。
					iRv = iResult ;
				}
				else
				{
					pCentDedDiaCont->insert( aCentDedDia ) ;
				}
			}
		}
	}
	return iRv ;
}

// ********************************
//	CentDedRosen
// ********************************
const wchar_t nameRosenmei[] = L"Rosenmei" ;
const wchar_t nameKitenJikoku[] = L"KitenJikoku" ;
const wchar_t nameDiagramDgrYZahyouKyoriDefault[] = L"DiagramDgrYZahyouKyoriDefault" ;
const wchar_t nameComment[] = L"Comment" ;


int CconvCentDed::CentDedRosen_To_OuPropertiesText( 
			const CentDedRosen* pCentDedRosen , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.Rosenmei
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameRosenmei , 
			pCentDedRosen->getName() ) ;
	}
	//2.Eki[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedEkiCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedEkiCont() , 
			pCNodeContainer ) ;
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			iRv = iResult ;
		}
	}
	

	//3.Ressyasyubetsu[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedRessyasyubetsuCont() , 
			pCNodeContainer ) ;
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-111 ;	//	Syubetsumei が指定されていません。
			//	-	-152 ;	//	DiagramSenStyle の値が不正です。
			iRv = iResult - 100 ;
		}
	}
	
	//4.Dia[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedDiaCont_To_OuPropertiesText( 
			pCentDedRosen->getCentDedDiaCont() , 
			pCNodeContainer ) ;
		//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			iRv = iResult - 200 ;
		}
	}
	//5.KitenJikoku
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameKitenJikoku , 
			g_CdDedJikokuConv.encode( pCentDedRosen->getKitenJikoku() ) ) ;
		
	}
	//6.DiagramDgrYZahyouKyoriDefault
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramDgrYZahyouKyoriDefault , 
			wstringOf( pCentDedRosen->getDiagramDgrYZahyouKyoriDefault() ) ) ;
	}
	//7.Comment
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameComment ,pCentDedRosen->getComment() ) ;
	}
	return ( iRv ) ;
}

int CconvCentDed::CentDedRosen_From_OuPropertiesText( 
			CentDedRosen* pCentDedRosen ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	pCentDedRosen->clear() ;

	//1.Rosenmei
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameRosenmei ) ;
		pCentDedRosen->setName( strValue ) ;
	}
	//2.Eki[]
	if ( iRv >= 0 )
	{
		CentDedEkiCont aCentDedEkiCont ;
		int iResult = CentDedEkiCont_From_OuPropertiesText( 
			&aCentDedEkiCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
		//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
		//	-	-101 ;	//	Eki がディレクトリではありません。
		if ( iResult < 0 )
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
			//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
			//	-	-101 ;	//	Eki がディレクトリではありません。
			iRv = iResult ;
		}
		else
		{
			//*pCentDedRosen->getCentDedEkiCont() = aCentDedEkiCont ;
			CaMui<CentDedEki>	aCaCont( pCentDedRosen->getCentDedEkiCont() ) ; 
			aCaCont.insert( &aCentDedEkiCont ) ;
		}
	}

	//3.Ressyasyubetsu[]
	if ( iRv >= 0 )
	{
		CentDedRessyasyubetsuCont aCentDedRessyasyubetsuCont ;
		int iResult = CentDedRessyasyubetsuCont_From_OuPropertiesText( 
			&aCentDedRessyasyubetsuCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		//	-	-101 ;	//	Ressyasyubetsu がディレクトリではありません。
		if ( iResult < 0 )
		{
			//	-	-111 ;	//	Syubetsumei が指定されていません。
			//	-	-152 ;	//	DiagramSenStyle の値が不正です。
			//	-	-201 ;	//	Ressyasyubetsu がディレクトリではありません。
			iRv = iResult - 100 ;
		}
		else
		{
			//*pCentDedRosen->getCentDedRessyasyubetsuCont() = aCentDedRessyasyubetsuCont ;
			CaMui<CentDedRessyasyubetsu>	aCaCont( pCentDedRosen->getCentDedRessyasyubetsuCont() ) ; 
			aCaCont.insert( &aCentDedRessyasyubetsuCont ) ;
			//	デフォルトの種別を削除
			aCaCont.getAdaptee()->erase( 0 , 1 ) ;
		}
	}
	
	//4.Dia[]
	if ( iRv >= 0 )
	{
		CentDedDiaCont aCentDedDiaCont( 
			pCentDedRosen->getCentDedEkiCont()->size() , 
			pCentDedRosen->getCentDedRessyasyubetsuCont()->size() )  ;
		int iResult = CentDedDiaCont_From_OuPropertiesText( 
			&aCentDedDiaCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-11 ;	//	DiaName が指定されていません。
		//	-	-12 ;	//	RessyaContが見つかりません。
		if ( iResult < 0 )
		{
			//	-	-211 ;	//	DiaName が指定されていません。
			//	-	-212 ;	//	RessyaContが見つかりません。
			iRv = iResult - 200 ;
		}
		else
		{
			//*pCentDedRosen->getCentDedDiaCont() = aCentDedDiaCont ;

			CaMui<CentDedDia>	aCaCont( pCentDedRosen->getCentDedDiaCont() ) ; 
			aCaCont.insert( &aCentDedDiaCont ) ;
		}
	}
	//5.KitenJikoku
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameKitenJikoku ) ;
		CdDedJikoku	aCdDedJikoku ;
		if ( !strValue.empty() )
		{
			if ( aCdDedJikoku.decode( strValue ) < 0 )
			{
				ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_KitenjikokuIsInvalid() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Jikoku() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -352 ;	//	起点時刻の設定が不適切です。
			}
		}
		if ( iRv >= 0 )
		{
			pCentDedRosen->setKitenJikoku( aCdDedJikoku ) ;
		}
	}
	//6.DiagramDgrYZahyouKyoriDefault
	if ( iRv >= 0 )
	{
		wstring	strValue = pCNodeContainer->getValue( nameDiagramDgrYZahyouKyoriDefault ) ;
		int iDiagramDgrYZahyouKyoriDefault = 60 ;
		if ( !strValue.empty() )
		{
			iDiagramDgrYZahyouKyoriDefault = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <= iDiagramDgrYZahyouKyoriDefault ) )
			{
				ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramDgrYZahyouKyoriDefaultIsInvalid() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -353 ;	//	ダイヤグラムの既定の駅間幅が不正です。
			}
		}
		if ( iRv >= 0 )
		{
			pCentDedRosen->setDiagramDgrYZahyouKyoriDefault( iDiagramDgrYZahyouKyoriDefault ) ;
		}
	}
	//7.Comment
	if ( iRv >= 0 ){
		wstring	strValue = pCNodeContainer->getValue( nameComment )  ;
		if ( iRv >= 0 )
		{
			pCentDedRosen->setComment( strValue ) ;
		}
	}


	return ( iRv ) ;
}

} //namespace entDed


