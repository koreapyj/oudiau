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
//	CconvWinDia.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "CconvWinDia.h"
#include "str/strToInt.h"
#include "str/strLf.h"
#include "str/stringSplit.h"
#include "str/CStrCharSizeMb.h"
#include "str/strprintf.h"

#include "Mu/CMup_deque.h"
#include "Mu/CaMui.h"


namespace WinDia{ 

using namespace OuLib ;
using namespace std ;

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone ,	// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
	) ;

// --------------------------------
//	WinDIA デフォルト
// --------------------------------
const CdColorProp	g_WinDIAColor[] = {
	CdColorProp(  0,  0,255) ,	//  青
	CdColorProp(  0,255,  0) ,	//  緑
	CdColorProp(  0,  0,132) ,	//  暗い青
	CdColorProp(  0,130,  0) ,	//  暗い緑
	CdColorProp(  0,255,255) ,	//  
	CdColorProp(255,  0,  0) ,	//  赤
	CdColorProp(  0,130,132) ,	//  
	CdColorProp(132,  0,  0) ,	//  
	CdColorProp(255,  0,255) ,	//  
	CdColorProp(255,255,  0) ,	//  黄
	CdColorProp(132,  0,132) ,	//  
	CdColorProp(132,130,  0) ,	//  
	CdColorProp(  0,  0,  0) ,	//  黒
	CdColorProp(132,130,132) ,	//
	CdColorProp(198,195,198) ,	//
	CdColorProp(255,255,255)  	//  白
};

const CentDedRessyasyubetsu g_WinDiaRessyasyubetsu[] = {
	CentDedRessyasyubetsu( L"普通"     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	// 0
	CentDedRessyasyubetsu( L"快速"     , L"快速" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	// 1
	CentDedRessyasyubetsu( L"特別快速" , L"特快" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	// 2
	CentDedRessyasyubetsu( L"新快速"   , L"新快" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	// 3
	CentDedRessyasyubetsu( L"通勤快速" , L"通快" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	// 4
	CentDedRessyasyubetsu( L"準急"     , L"準急" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	// 5
	CentDedRessyasyubetsu( L"急行"     , L"急行" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	// 6
	CentDedRessyasyubetsu( L"快速急行" , L"快急" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	// 7
	CentDedRessyasyubetsu( L"特急"     , L"特急" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	// 8
	CentDedRessyasyubetsu( L"快速特急" , L"快特" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	// 9
	CentDedRessyasyubetsu( L"通勤準急" , L"通準" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	//10
	CentDedRessyasyubetsu( L"通勤急行" , L"通急" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	//11
	CentDedRessyasyubetsu( L"区間快速" , L"区快" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//12
	CentDedRessyasyubetsu( L"区間急行" , L"区急" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , true  ) ,	//13
	CentDedRessyasyubetsu( L"回送"     , L"回送" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Ittensasen , false ) ,	//14
	CentDedRessyasyubetsu( L"貨物"     , L"貨物" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Hasen , false ) ,	//15
	CentDedRessyasyubetsu( L"急行貨物" , L"急貨" ,
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Hasen , true ) ,	//16

	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//17
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//18
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//19
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//20
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//21
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//22
	CentDedRessyasyubetsu( L""     , L"" , 
		g_WinDIAColor[12] , g_WinDIAColor[12] ,
		CentDedRessyasyubetsu::SenStyle_Jissen , false ) ,	//23
};
// --------------------------------
//	下請関数
// --------------------------------
/**
 *	指定の色に一番近い WinDIA 色番号を取得します。
 * @param aCdColorProp [in]
 *	対象の色を指定して下さい。
 * @return
 *	aCdColorProp に一番近い WinDIA 色番号を取得します。範囲は 0 ～ 15 です。
 */
static int getNearestWinDIAColorNumber( const CdColorProp& aCdColorProp ) 
{
	int idxMin = 0 ;
	unsigned long valueMin = 0 ;
	
	for ( int idx = 0 ; idx < sizeof(g_WinDIAColor) / sizeof(g_WinDIAColor[0]) ;
			idx ++ ){
		unsigned long valueTotal = 0 ;
		unsigned long value ;
		value = aCdColorProp.getRed() - g_WinDIAColor[idx].getRed() ;
		value *= value ;
		valueTotal += value ;
		value = aCdColorProp.getGreen() - g_WinDIAColor[idx].getGreen() ;
		value *= value ;
		valueTotal += value ;
		value = aCdColorProp.getBlue() - g_WinDIAColor[idx].getBlue() ;
		value *= value ;
		valueTotal += value ;
		
		if ( idx == 0 || valueMin > valueTotal ){
			valueMin = valueTotal ;
			idxMin = idx ;
		}
	}
	return ( idxMin ) ;
}
// --------------------------------
//	文字列を分割
// --------------------------------
/**
 *	文字列を１行ごとに分割し、コンテナに格納します。
 *
 *	末尾が "\" の行については、次の行との結合を行います。
 * @param pContStr [out]
 *	この関数は、このコンテナの末尾に、１行毎の文字列を追加します。
 *	コンテナがそれまで保持していたデータは維持します。
 * @param aString [in]
 *	分割する文字列を指定して下さい。
 */
static void ContStrFromString( 
	Mui< wstring >* pContStr ,
	const wstring& aString )
{
	deque< wstring >	contstr = splitc< deque< wstring > >( L'\n' , 
		aString ) ;

	CaMup_vector< deque< wstring > > aSrc( &contstr )  ;
	CaMui<wstring>	aDst( pContStr ) ;
	aDst.insert( &aSrc ) ;

	//pContStr = aString の内容を１行ごとにした配列
	
	// --------------------------------
	//	末尾が '\' の行は、次の行と結合
	// --------------------------------

	wstring	strCurr ;
	wstring	strNext ;
	for ( int idx = 0 ; idx < pContStr->size() - 1 ; idx ++ ){
		strCurr = pContStr->get( idx ) ;
		CStrCharSizeMb	aCStrCharSizeMb( strCurr ) ;
		
		wchar_t	chStrCurrLast = L'\0' ;
		int iCurrCharLast = aCStrCharSizeMb.CharLength() - 1 ;
		//iCurrCharLast = strCurr の一番最後の文字の、
		//	文字インデクス（２バイト文字も１と数えたインデクス）
		//	-1 なら、strCurrは空文字列です。
		if ( iCurrCharLast >= 0 ){
			if ( aCStrCharSizeMb.CsizeOfCidx( iCurrCharLast ) == 1 ){
				chStrCurrLast = strCurr[ aCStrCharSizeMb.BidxOfCidx( iCurrCharLast ) ] ;
			}
		}
		//chStrCurrLast = strCurr の末尾の文字。
		//	但し、末尾の文字が２バイト文字である場合は、 '\0' となります。

		strNext = pContStr->get( idx + 1 ) ;
		if ( chStrCurrLast == L'\\' && strNext.size() > 0 ){
			strCurr.erase( strCurr.size() - 1 ) ;
			strNext = strTrim( strNext , true , false ) ;
			strCurr += strNext ;
			pContStr->set( strCurr , idx ) ;
			pContStr->erase( idx + 1 ) ;
			idx -- ;
		}
	}
}

/**
	文字列コンテナを１行として、ひとつの文字列に結合します。

	200文字を超える行については、カンマの位置で "\\\n\t\t" を挿入して、改行を追加します。

	末尾が "\" の行については、次の行との結合を行います。
 @param pContStr [in]
	文字列コンテナを指定して下さい。
 @return
	結合した文字列を返します。
*/
static wstring ContStrToString( 
	Mu< wstring >* pContStr )
{

	wstring strRv ;

	for ( int idx = 0 ; idx < pContStr->size() ; idx ++ )
	{
		wstring strElement = pContStr->get( idx ) ;

		// --------------------------------
		//	strElement の200字ごとに、
		//	"\\\n\t\t" を挿入して strElement2 にコピー
		// --------------------------------
		wstring strElement2 ;
		while( strElement.size() > 0 )
		{
			if ( !strElement2.empty() )
			{
				strElement2 += L"\\\n\t\t" ;
			}

			if ( strElement.size() > 200 )
			{
				CStrCharSizeMb	aCStrCharSizeMb( strElement ) ;
				int iBidxComma = 0 ;
				for ( iBidxComma = 200 ; 
					iBidxComma > 0 ;
					iBidxComma = aCStrCharSizeMb.BidxNextChar( iBidxComma , -1 ) )
				{
					if ( aCStrCharSizeMb.CsizeOfBidx( iBidxComma ) == 1 && 
						strElement[iBidxComma] == ',' )
					{
						break ;
					}
				}
				//iBidxComma = 200バイト目より前で、200バイト目に一番近い ',' の
				//	バイトインデクス
				if ( iBidxComma == 0 )
				{
					//	カンマが見つかりませんでした。
					strElement2 += strElement ;
					strElement = L"" ;
				}
				else
				{
					iBidxComma = aCStrCharSizeMb.BidxNextChar( iBidxComma , 1 ) ;
					//iBidxComma = 200バイト目より前で、
					//	200バイト目に一番近い ',' の次の文字
					
					strElement2 += strElement.substr( 0 , iBidxComma ) ;

					strElement.erase( 0 , iBidxComma ) ;
				}
			}
			else
			{
				strElement2 += strElement ;
				strElement = L"" ;
			}
			//strElement = strLine 分を削除しました。

		}
		// --------------------------------
		strRv += strElement2 ;
		strRv += L"\n" ;
	}
	return ( strRv ) ;
}



// --------------------------------
//	WinDiaファイルのセクション	
// --------------------------------
/**
 *	  WinDia ファイル形式の文字列 から、セクションを取得します。
 *	
 *	@param pstrcontWinDiaFileContStr [in]
 *	  WinDia ファイル形式の文字列 を１行ずつ区切って格納した
 *	文字列コンテナを指定して下さい。
 *	@param strSection [in]
 *		セクション名を指定して下さい。
 *	@param pstrcontSection [in,out]
 *	  この関数はこのコンテナの末尾に、セクションの内側にある文字列を
 *	追加します。\n
 *	  このコンテナにそれまであった要素は維持します。
 *	@return
 *	  成功したら 0 以上、エラーなら負の数です。
 *	-	現在のところは、 0 のみです。
 */
static int WinDiaFile_getSection(
		Mu< wstring >* pstrcontWinDiaFileContStr ,
		const wstring& strSection , 
		Mui< wstring >* pstrcontSection ) 
{
	int idx ;
	int iRv = 0 ;
	wstring	aSection = wstring( L"[" ) + strSection + L"]" ;
	bool	bIsInSection = false ;
	for ( idx = 0 ; idx < pstrcontWinDiaFileContStr->size() ; idx ++ ){
		wstring	strLine = pstrcontWinDiaFileContStr->get( idx ) ;
		if ( !bIsInSection ){
			//	セクションの開始の検索を行っています。
			if ( aSection == strLine ){
				bIsInSection = true ;
				continue ;
			}
		}	else	{
			//	セクションの内容を取得しています。
			if ( strLine.empty() || ( strLine[0] == L'[' && 
					strLine[ strLine.size() - 1 ] == L']' ) ){
				bIsInSection = false ;
			}	else	{
				pstrcontSection->insert( strLine ) ;
			}
		}
	}
	return ( iRv ) ;
}


/**
 *	  セクションを、文字列コンテナに追加します。
 *	WinDia ファイル形式に対応した記号を、セクションの前後に追加します。
 *	
 *	@param pstrcontWinDiaFileContStr [in,out]
 *	  この関数はこのコンテナの末尾に、セクションの文字列を追加します。
 *	コンテナがそれまで保持していた要素は維持します。
 *	@param strSection [in]
 *		セクション名を指定して下さい。
 *	@param pstrcontSection [in]
 *	  セクションの内側に配置する文字列のコンテナを指定して下さい。
 *	@return
 *	  成功したら 0 以上、エラーなら負の数です。
 *	-	現在のところは、 0 のみです。
 */
static int WinDiaFile_setSection(
		Mui< wstring >* pstrcontWinDiaFileContStr ,
		const wstring& strSection , 
		Mu< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	
	wstring	aSection = wstring( L"[" ) + strSection + L"]" ;
	pstrcontWinDiaFileContStr->insert( aSection ) ;
	for ( int idx = 0 ; idx < pstrcontSection->size() ; idx ++ ){
		pstrcontWinDiaFileContStr->insert( pstrcontSection->get( idx ) ) ;
	}
	pstrcontWinDiaFileContStr->insert( L"" ) ;
	
	return ( iRv ) ;
}

// --------------------------------
//	[WinDia]
// --------------------------------
/**
 *	[WinDIA] セクションの各行の内容を保持している
 *	文字列コンテナの内容を読み込んで、
 *	CentDedRosen オブジェクトの属性に反映します。
 *	[WinDIA] セクションに関係のない属性は、そのまま維持します。
 * @param pCentDedRosen [in,out]
 *	この関数はこのオブジェクトに、属性を書き込みます。
 * @param pstrcontSection [in]
 *	WinDIA セクションの内容を保持している文字列コンテナを指定して下さい。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_readWinDIASection( CentDedRosen* pCentDedRosen , 
		Mu< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	// --------------------------------
	if ( pstrcontSection->size() > 0 ){
		pCentDedRosen->setName( pstrcontSection->get( 0 ) ) ;
	}
	// --------------------------------
	return ( iRv ) ;
}
	
/**
 *	CentDedRosen オブジェクトの属性をもとに、
 *	[WinDIA] セクションの行を生成し、文字列コンテナに追加します。
 * @param pCentDedRosen [in]
 *	CentDedRosen オブジェクトを指定して下さい。
 * @param pstrcontSection [in.out]
 *	この関数はこのオブジェクトに、行を追加します。
 *	コンテナがそれまで保持していた文字列は維持します。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_writeWinDIASection( 
		const CentDedRosen* pCentDedRosen , 
		Mui< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	// --------------------------------
	{
		pstrcontSection->insert( pCentDedRosen->getName() ) ;
	}
	// --------------------------------
	return ( iRv ) ;
}

// --------------------------------
//	[駅]
// --------------------------------
/**
 *	[駅] セクションの各行の内容を保持している
 *	文字列コンテナの内容を読み込んで、『駅』 CentDedEki 
 *	オブジェクトを生成し、
 *	CentDedRosen オブジェクトの、駅Indexの末尾に追加します。
 *	CentDedRosen オブジェクトがそれまで保持していた
 *	『駅』 オブジェクトは維持します。
 *	[駅] セクションに関係のない属性は、そのまま維持します。
 * @param pCentDedRosen [in,out]
 *	この関数はこのオブジェクトに、『駅』 CentDedEki オブジェクトを
 *	追加します。
 * @param pstrcontSection [in]
 *	[駅] セクションの内容を保持している文字列コンテナを指定して下さい。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_readEkiSection( CentDedRosen* pCentDedRosen , 
		Mu< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	// --------------------------------
	CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont() ;

	for ( int iEkiIndex = 0 ; 
			iRv >= 0 && iEkiIndex < pstrcontSection->size() ;
			iEkiIndex ++ ){
		wstring	strLine = pstrcontSection->get( iEkiIndex ) ;
		wstring	strEkiZokusei ;
		wstring	strEkimei ;
		wstring::size_type pos = strLine.find( ',' ) ;
		if ( pos != wstring::npos ){
			strEkiZokusei = strLine.substr( 0 , pos ) ;
			strEkimei = strLine.substr( pos + 1 ) ;
		}	else	{
			strEkimei = strLine ;
		}
		CentDedEki::EEkijikokukeisiki	eEkijikokukeisiki = 
			CentDedEki::Jikokukeisiki_Hatsu ;
		if ( strEkiZokusei.find( L'b' ) != wstring::npos ){
			eEkijikokukeisiki = CentDedEki::Jikokukeisiki_Hatsuchaku ;
		}	else if ( strEkiZokusei.find( L'd' ) != wstring::npos ){
			eEkijikokukeisiki = CentDedEki::Jikokukeisiki_KudariChaku ;
		}	else if ( strEkiZokusei.find( L'u' ) != wstring::npos ){
			eEkijikokukeisiki = CentDedEki::Jikokukeisiki_NoboriChaku ;
		}
		CentDedEki::EEkikibo	eEkikibo = CentDedEki::Ekikibo_Ippan ;
		if ( strEkiZokusei.find( L'p' ) != wstring::npos ){
			eEkikibo = CentDedEki::Ekikibo_Syuyou ;
		}		

		CentDedEki aCentDedEki( strEkimei , 
			eEkijikokukeisiki ,
			eEkikibo , false ) ;
		pCentDedEkiCont->insert( aCentDedEki ) ;
	}
	// --------------------------------
	return ( iRv ) ;
}


/**
 *	CentDedRosen オブジェクトが包含している
 *	 『駅』 CentDedEki オブジェクトの属性を元に、
 *	[駅] セクションの行を生成します。
 * @param pCentDedRosen [in]
 *	書き込み対象となる CentDedRosen オブジェクトを指定して下さい。
 * @param pstrcontSection [in,out]
 *	この関数はこの文字列コンテナに、行を追加します。
 *	コンテナがそれまで保持していた文字列は維持します。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_writeEkiSection( 
		const CentDedRosen* pCentDedRosen , 
		Mui< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	// --------------------------------
	const Mu<const CentDedEki*>*	pCentDedEkiContGet = 
		pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;

	for ( int iEkiIndex = 0 ; 
			iRv >= 0 && iEkiIndex < pCentDedEkiContGet->size() ;
			iEkiIndex ++ ){
		const CentDedEki* pCentDedEki = pCentDedEkiContGet->get( iEkiIndex ) ;

		wstring	strEkiZokusei ;
		wstring	strEkimei ;

		CentDedEki::EEkijikokukeisiki	eEkijikokukeisiki = 
			pCentDedEki->getEkijikokukeisiki() ;
		CentDedEki::EEkikibo	eEkikibo = pCentDedEki->getEkikibo() ;
		
		if ( eEkikibo == CentDedEki::Ekikibo_Syuyou ){
			strEkiZokusei += L'p' ;
		}
		switch( eEkijikokukeisiki ){
		 case CentDedEki::Jikokukeisiki_Hatsu :
			break ;
		 case CentDedEki::Jikokukeisiki_Hatsuchaku :
			strEkiZokusei += L'b' ;
			break ;
		 case CentDedEki::Jikokukeisiki_KudariChaku :
			strEkiZokusei += L'd' ;
			break ;
		 case CentDedEki::Jikokukeisiki_NoboriChaku :
			strEkiZokusei += L'u' ;
			break ;
		}
		
		strEkimei = pCentDedEki->getEkimei() ;
		
		wstring	strLine = strEkiZokusei + L',' + strEkimei ;
		
		pstrcontSection->insert( strLine ) ;
	}
	return ( iRv ) ;
}


// --------------------------------
//	[線種]
// --------------------------------
/**
 *	[線種] セクションの各行の内容を保持している
 *	文字列コンテナの内容を読み込んで、『列車種別』 CentDedRessyasyubetsu 
 *	オブジェクトを生成し、
 *	CentDedRosen オブジェクトの末尾に追加します。
 *
 *	CentDedRosen オブジェクトがそれまで保持していた
 *	『列車種別』 オブジェクトは維持します。
 *	[線種] セクションに関係のない属性は、そのまま維持します。
 *
 *	また、『列車種別』オブジェクトが１７個に満たない場合は、
 *	WinDIA のデフォルトの列車種別を追加します。
 * @param pCentDedRosen [in,out]
 *	この関数はこのオブジェクトに、『列車種別』 CentDedRessyasyubetsu 
 *	オブジェクトを
 *	追加します。
 * @param pstrcontSection [in]
 *	[線種] セクションの内容を保持している文字列コンテナを指定して下さい。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	-1 ;	//	Train00 の番号部分の値が不適切です。
 */
static int CentDedRosen_readSensyuSection( CentDedRosen* pCentDedRosen , 
		Mu< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;

	CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = 
		pCentDedRosen->getCentDedRessyasyubetsuCont() ;
	
	// --------------------------------
	//	デフォルト列車種別を設定
	// --------------------------------
	if ( iRv >= 0 ){
		for ( int iRessyasyubetsuIdx = 
				pCentDedRessyasyubetsuCont->size() ;
			iRessyasyubetsuIdx < sizeof(g_WinDiaRessyasyubetsu) / 
				sizeof(g_WinDiaRessyasyubetsu[0]) ; 
			iRessyasyubetsuIdx ++ ){
			pCentDedRessyasyubetsuCont->insert( g_WinDiaRessyasyubetsu[iRessyasyubetsuIdx] ) ;
		}
	}

	// --------------------------------
	//	LINES=
	// --------------------------------
	wstring	strLINES ;
	if ( iRv >= 0 ){
		if ( pstrcontSection->size() > 0 ){
			wstring	aString = pstrcontSection->get( 0 ) ;
			if ( aString.substr( 0 , 6 ) == L"LINES=" ) {
				strLINES = aString.substr( 6 ) ;
			}
		}
		//strLINES = "LINES=" 行の、値部分
		if ( strLINES.length() > 0 ){
			deque<wstring>	contstr = splitc< deque< wstring > >( L',' , strLINES ) ;
			for ( int iRessyasyubetsuIdx = 0 ; 
					iRessyasyubetsuIdx <  (int)contstr.size() && 
					iRessyasyubetsuIdx < 
						pCentDedRessyasyubetsuCont->size() ;
					iRessyasyubetsuIdx ++ ){
				CentDedRessyasyubetsu* pCentDedRessyasyubetsu = 
					pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()->get( iRessyasyubetsuIdx ) ;
				// --------------------------------
				unsigned int iValue = _wtoi( contstr[iRessyasyubetsuIdx].c_str() ) ;
				CentDedRessyasyubetsu::ESenStyle eSenStyle = 
					CentDedRessyasyubetsu::SenStyle_Jissen ;
				bool	bIsBold = false ;
				CdColorProp	aCOLORREF = pCentDedRessyasyubetsu->
					getDiagramSenColor() ;
				int iColorNum = -1 ;
				switch( ( iValue >> 0 ) & 0x3 ) {
				 case 0 :
					eSenStyle = CentDedRessyasyubetsu::SenStyle_Jissen ;
					break ;
				 case 1 :
					eSenStyle = CentDedRessyasyubetsu::SenStyle_Hasen ;
					break ;
				 case 2 :
					eSenStyle = CentDedRessyasyubetsu::SenStyle_Tensen ;
					break ;
				 case 3 :
					eSenStyle = CentDedRessyasyubetsu::SenStyle_Ittensasen ;
					break ;
				} 
				if ( ( ( iValue >> 7 ) & 0x1 ) > 0 ){
					bIsBold = true ;
				}
				if ( ( ( iValue >> 6 ) & 0x1 ) > 0 ){
					iColorNum = ( ( iValue >> 2 ) & 0x0f ) ;
					aCOLORREF = g_WinDIAColor[ iColorNum ] ;
				}
				
				pCentDedRessyasyubetsu->setDiagramSenStyle( eSenStyle ) ;
				pCentDedRessyasyubetsu->setDiagramSenIsBold( bIsBold ) ;
				pCentDedRessyasyubetsu->setDiagramSenColor( aCOLORREF ) ;			
				pCentDedRessyasyubetsu->setJikokuhyouMojiColor( aCOLORREF ) ;			
			}
		}
	}
	
	// --------------------------------
	//	Train00=
	// --------------------------------
	for ( int idxLine = 1 ; 
			iRv >= 0 && idxLine < pstrcontSection->size() ;
			idxLine ++ ){
		wstring	strLine = pstrcontSection->get( idxLine ) ;
		//strLine = Train00 行全体
		//	(例:"Train02=Ｊ編成こだま,ＪＫ")


		int iRessyasyubetsuIdx = 0 ;
		wstring	strSyubetsumei ;
		wstring	strRyakusyou ;
		{
			wstring::size_type pos = strLine.find( L'=' ) ;
			if ( pos == wstring::npos ){
				continue ;
			}
			wstring strRessyasyubetsIdx = strLine.substr( 0 , pos ) ;
			//strRessyasyubetsIdx =	"Train00" の部分
			//	(例:"Train02")

			strRessyasyubetsIdx.erase( 0 , 5 ) ;	
			//strRessyasyubetsIdx =	"Train" の部分を削除し 
			//	"00" の部分だけを残しました。
			//	(例:"02")
			iRessyasyubetsuIdx = _wtoi( strRessyasyubetsIdx.c_str() ) ;
			//iRessyasyubetsuIdx = 記述されている列車種別Index
			//	(例:2)

			wstring strSyubetsumeiRyakusyou = strLine.substr( pos + 1 ) ;

			pos = strSyubetsumeiRyakusyou.find( L',' ) ;
			if ( pos == wstring::npos ){
				strSyubetsumei = strSyubetsumeiRyakusyou ;
			}	else	{
				strSyubetsumei = strSyubetsumeiRyakusyou.substr( 0 , pos ) ;
				strRyakusyou = strSyubetsumeiRyakusyou.substr( pos + 1 ) ;
			}
			//strSyubetsumei = 種別名
			//	(例:"Ｊ編成こだま")
			//strRyakusyou = 略称
			//	(例:"ＪＫ")
		}
		CentDedRessyasyubetsu* pCentDedRessyasyubetsu = 
				pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()->get( iRessyasyubetsuIdx ) ;
		if ( pCentDedRessyasyubetsu == NULL ){
			iRv = -1 ;	//	Train00 の番号部分の値が不適切です。
		}	else	{
			pCentDedRessyasyubetsu->setSyubetsumei( strSyubetsumei ) ;
			pCentDedRessyasyubetsu->setRyakusyou( strRyakusyou ) ;
		}
	}

	// --------------------------------
	//	列車種別名が空の列車種別(idx 17以上)は削除します。
	// --------------------------------
	if ( iRv >= 0 ){
		for ( int idxRessyasyubetsu = pCentDedRessyasyubetsuCont->size() - 1 ;
				idxRessyasyubetsu >= 0 ;
				idxRessyasyubetsu -- ){
			CentDedRessyasyubetsu* pCentDedRessyasyubetsu = 
				pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()->get( idxRessyasyubetsu ) ;
			if ( pCentDedRessyasyubetsu->getSyubetsumei().empty() ){
				pCentDedRessyasyubetsuCont->erase( idxRessyasyubetsu ) ;
			}	else	{
				break ;
			}
		}
	}
	return ( iRv ) ;
}


/**
 *	CentDedRosen オブジェクトが包含している
 *	『列車種別』 CentDedRessyasyubetsu オブジェクトをもとに、
 *	[線種] セクションの行を生成します。
 * @param pCentDedRosen [in]
 *	『列車種別』 CentDedRessyasyubetsu オブジェクトを包含している
 *	CentDedRosen オブジェクトを指定して下さい。
 * @param pstrcontSection [in,out]
 *	この関数はこの文字列コンテナに、行を追加します。
 *	コンテナがそれまで保持していた文字列は維持します。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	-1 ;	//	WinDIA 形式では、列車種別は24種類までに制限されています。
 *	-	-2 ;	//	略称の長さが半角５文字を超える列車種別があります。
 */
static int CentDedRosen_writeSensyuSection( const CentDedRosen* pCentDedRosen , 
		Mui< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;

	const Mu<const CentDedRessyasyubetsu*>*	pCentDedRessyasyubetsuContGet = pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr() ;
	// --------------------------------
	//	ガード条件
	// --------------------------------
	if ( iRv >= 0 ){
		if ( pCentDedRessyasyubetsuContGet->size() > 
			sizeof(g_WinDiaRessyasyubetsu)/sizeof(g_WinDiaRessyasyubetsu[0]) ){
			iRv = -1 ;	
				//	WinDIA 形式では、列車種別は24種類までに制限されています。
		}
	}
	// --------------------------------
	//	LINES=
	// --------------------------------
	wstring	strLINES ;
	if ( iRv >= 0 ){
		int idxRessyasyubetsu = 0 ;
		for ( idxRessyasyubetsu = 0 ; iRv >= 0 && 
				idxRessyasyubetsu <  
					pCentDedRessyasyubetsuContGet->size() ;
				idxRessyasyubetsu  ++ ){
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = 
				pCentDedRessyasyubetsuContGet->get( idxRessyasyubetsu ) ;
			CentDedRessyasyubetsu::ESenStyle eSenStyle = 
				pCentDedRessyasyubetsu->getDiagramSenStyle() ;
			bool bIsBold = pCentDedRessyasyubetsu->getDiagramSenIsBold() ;
			CdColorProp aCOLORREF = pCentDedRessyasyubetsu->getDiagramSenColor() ;


			unsigned int iValue = 0 ;
			
			iValue |= ( 1 << 6 ) ;
			
			switch( eSenStyle ){
 			 case CentDedRessyasyubetsu::SenStyle_Jissen :
				iValue |= ( 0 << 0 ) ;
				break ;
			 case CentDedRessyasyubetsu::SenStyle_Hasen :
				iValue |= ( 1 << 0 ) ;
				break ;
			 case CentDedRessyasyubetsu::SenStyle_Tensen :
				iValue |= ( 2 << 0 ) ;
				break ;
			 case CentDedRessyasyubetsu::SenStyle_Ittensasen :
				iValue |= ( 3 << 0 ) ;
				break ;
			}
			if ( bIsBold ){
				iValue |= ( 1 << 7 ) ;
			}
			int iColorNum = getNearestWinDIAColorNumber( aCOLORREF ) ;
			{
				iValue |= ( (unsigned int)iColorNum << 2 ) ;
			}
			// --------------------------------
			if ( !strLINES.empty() ){
				strLINES += L',' ;
			}
			strLINES += wstringOf( (int)iValue ) ;
		}
		for ( ; iRv >= 0 && 
				idxRessyasyubetsu <  24 ; idxRessyasyubetsu  ++ ){
			if ( !strLINES.empty() ){
				strLINES += L',' ;
			}
		}
		strLINES = wstring( L"LINES=" + strLINES ) ;
		pstrcontSection->insert( strLINES ) ;
	}
	// --------------------------------
	//	Train00=
	// --------------------------------
	if ( iRv >= 0 ){
		int idxRessyasyubetsu = 0 ;
		for ( idxRessyasyubetsu = 0 ; iRv >= 0 && 
				idxRessyasyubetsu <  
					pCentDedRessyasyubetsuContGet->size() ;
				idxRessyasyubetsu  ++ ){
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = 
				pCentDedRessyasyubetsuContGet->get( idxRessyasyubetsu ) ;
			wstring	strSyubetsumei = pCentDedRessyasyubetsu->getSyubetsumei() ;
			wstring	strRyakusyou = pCentDedRessyasyubetsu->getRyakusyou() ;

			if ( strRyakusyou.length() > 4 ){
				iRv = -2 ;	//	略称の長さが半角５文字を超える列車種別があります。
			}	else	{
				wstring	strLs = strprintf( L"Train%02d=" , idxRessyasyubetsu ) ;
				strLs += strSyubetsumei + L"," + strRyakusyou ;
				pstrcontSection->insert( strLs ) ;
			}
		}
	}
	return ( iRv ) ;
}

// --------------------------------
//	[下り][上り]
// --------------------------------
/**
 *	[下り]か[上り] セクションの各行の内容を保持している
 *	文字列コンテナの内容を読み込んで、『列車』 CentDedRessya 
 *	オブジェクトを生成し、
 *	CentDedRessyaCont オブジェクトの末尾に追加します。
 *	CentDedRessyaCont オブジェクトがそれまで保持していた
 *	『列車』 CentDedressya オブジェクトは維持します。
 *	[下り][上り] セクションに関係のない属性は、そのまま維持します。
 *
 *	この関数の実行前に、 CentDedRessyaCont の
 *
 *	- CentDedRessyaCont::m_iEkiCount 
 *	- CentDedRessyaCont::m_eRessyahoukou 
 *
 *	属性が設定されていなくてはなりません。
 *
 * @param pCentDedRessyaCont [in,out]
 *	この関数はこのオブジェクトに、『列車』 CentDedRessya
 *	オブジェクトを
 *	追加します。
 * @param pstrcontSection [in]
 *	[下り] [上り]セクションの内容を保持している文字列コンテナを指定して下さい。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_readKudariNoboriSection( 
		CentDedRessyaCont* pCentDedRessyaCont ,
		Mu< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	
	for ( int idxLine = 0 ; iRv >= 0 && 
		idxLine < pstrcontSection->size() ; idxLine ++ ){
		
		wstring	strLine = pstrcontSection->get( idxLine ) ;
		deque<wstring>	contstrItem = splitc< deque<wstring>	>( L',' , strLine );
		if ( contstrItem.size() < 
			deque<wstring>::size_type( 4 + pCentDedRessyaCont->getEkiCount() ) )
		{
			iRv = -1 ;	//	駅時刻が少なすぎます。
			continue ;
		}

		// --------------------------------
		CentDedRessya aCentDedRessya( 
			pCentDedRessyaCont->getEkiCount() ,
			pCentDedRessyaCont->getRessyahoukou() ) ;

		// --------------------------------
		//	列車種別・列車番号・列車名・号数
		// --------------------------------
		if ( iRv >= 0 ){
			wstring	strRessyasyubetsu = contstrItem[0] ;

			//	列車種別番号に続いて、()で色番号を指定している場合、
			//	これは削除（無視）します。
			wstring::size_type	pos = strRessyasyubetsu.find( L'(' ) ;
			if ( pos != wstring::npos ){
				strRessyasyubetsu.erase( pos , wstring::npos ) ;
			}

			int iRessyasyubetsuIdx = _wtoi( strRessyasyubetsu.c_str() ) ;
			wstring	strRessyabangou = contstrItem[1] ;
			wstring	strRessyamei = contstrItem[2] ;
			wstring	strGousuu = contstrItem[3] ;
			
			aCentDedRessya.setRessyasyubetsuIndex( iRessyasyubetsuIdx ) ;
			aCentDedRessya.setRessyabangou( strRessyabangou ) ;
			aCentDedRessya.setRessyamei( strRessyamei ) ;
			aCentDedRessya.setGousuu( strGousuu ) ;
		}
		// --------------------------------
		//	駅時刻
		// --------------------------------
		if ( iRv >= 0 ){
			for ( int iEkiIndex = 0 ; iRv >= 0 && 
					iEkiIndex < aCentDedRessya.getCentDedEkiJikokuCount() && 
					iEkiIndex < (int)contstrItem.size() - 4 ; iEkiIndex ++ ){
				wstring	strItem = contstrItem[iEkiIndex+4] ;
				
				wstring	strChaku ;
				wstring	strHatsu ;
				bool bChakuQ = false ;
				bool bHatsuQ = false ;
				bool bTsuuka = false ;
					
				wstring::size_type	pos = strItem.find( L'/' ) ;
				if ( pos == wstring::npos ){
					strHatsu = strItem ;
				}	else	{
					strChaku = strItem.substr( 0 , pos ) ;
					strHatsu = strItem.substr( pos + 1 ) ;
				}
				if ( strChaku.size() >= 1 && strChaku[ strChaku.size() - 1 ] == L'?' ){
					bChakuQ = true ;
					strChaku.erase( strChaku.size() - 1 ) ;
				}
				if ( strHatsu.size() >= 1 && strHatsu[ strHatsu.size() - 1 ] == L'?' ){
					bHatsuQ = true ;
					strHatsu.erase( strHatsu.size() - 1 ) ;
				}
				if ( strChaku == L"-" || strHatsu == L"-" ){
					bTsuuka = true ;
				} 
				//strChaku = 着時刻。 "900" の形式。指定がない場合は空文字列。
				//strHatsu = 発時刻。 "900" の形式。指定がない場合は空文字列。
				//bChakuQ = 着時刻が推定時刻 "?" なら真。
				//bHatsuQ = 発時刻が推定時刻 "?" なら真。
				//bTsuuka = 通過なら真。

				CdDedJikoku	jikokuChaku( strChaku ) ;
				CdDedJikoku	jikokuHatsu( strHatsu ) ;
				//jikokuChaku = 着時刻。 指定がない場合は Null 状態。
				//jikokuHatsu = 発時刻。 指定がない場合は Null 状態。

				CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(
					aCentDedRessya.EkiOrderOfEkiIndex( iEkiIndex ) ) ;
				if ( ( !jikokuChaku.isNull() && !bChakuQ ) || 
						( !jikokuHatsu.isNull() && !bHatsuQ ) ){
					//	駅扱は停車
					aCentDedEkiJikoku.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_Teisya ) ;
					aCentDedEkiJikoku.setChakujikoku( jikokuChaku ) ;
					aCentDedEkiJikoku.setHatsujikoku( jikokuHatsu ) ;
				}	else if ( !jikokuChaku.isNull() || !jikokuHatsu.isNull() || bTsuuka ){
					//	駅扱は通過
					aCentDedEkiJikoku.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_Tsuuka ) ;
					aCentDedEkiJikoku.setChakujikoku( jikokuChaku ) ;
					aCentDedEkiJikoku.setHatsujikoku( jikokuHatsu ) ;
				}
				aCentDedRessya.setCentDedEkiJikoku( 
				 	aCentDedRessya.EkiOrderOfEkiIndex( iEkiIndex ) , aCentDedEkiJikoku ) ;
			}
		}
		// --------------------------------
		//	備考
		// --------------------------------
		if ( iRv >= 0 ){
			if ( (int)contstrItem.size() >= 4 + aCentDedRessya.getCentDedEkiJikokuCount() + 1 ){
				wstring	strBikou = contstrItem[4 + aCentDedRessya.getCentDedEkiJikokuCount() ] ;
				if ( strBikou.size() > 0 && strBikou[0] == L'%' ){
					strBikou.erase( 0 , 1 ) ;
				}
				aCentDedRessya.setBikou( strBikou ) ;
			}
		}
		// --------------------------------
		if ( iRv >= 0 ){
			pCentDedRessyaCont->insert( aCentDedRessya ) ;
		}		
	}
	return ( iRv ) ;
}


/**
 *	CentDedRessyaCont オブジェクトに格納されている
 *	『列車』 CentDedRessya オブジェクトを読み込んで、
 *	[下り]か[上り] セクションの行を生成します。
 *
 * @param pCentDedRessyaCont [in]
 *	『列車』 CentDedRessya	オブジェクトが格納されている CentDedRessyaCont
 *	を指定して下さい。
 * @param pstrcontSection [in]
 *	この関数はこの文字列コンテナに、行を追加します。
 *	コンテナがそれまで保持していた文字列は維持します。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_writeKudariNoboriSection( 
		const CentDedRessyaCont* pCentDedRessyaCont ,
		Mui< wstring >* pstrcontSection ) 
{
	int iRv = 0 ;
	
	// --------------------------------
	const Mu<const CentDedRessya*>*	pCentDedRessyaContGet = pCentDedRessyaCont->getMuPtr() ;
	for ( int idxRessya = 0 ; iRv >= 0 && 
			idxRessya < pCentDedRessyaContGet->size() ;
			idxRessya ++ ){
		const CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get( idxRessya );
		wstring	strLine ;
		
		// --------------------------------
		//	列車種別・列車番号・列車名・号数
		// --------------------------------
		if ( pCentDedRessya->getRessyasyubetsuIndex() > 0 ){
			strLine += wstringOf( pCentDedRessya->getRessyasyubetsuIndex() ) ;
		}
		strLine += L',' ;
		strLine += pCentDedRessya->getRessyabangou() ;
		strLine += L',' ;
		strLine += pCentDedRessya->getRessyamei() ;
		strLine += L',' ;
		strLine += pCentDedRessya->getGousuu() ;
		// --------------------------------
		//	駅時刻
		// --------------------------------
		if ( iRv >= 0 ){
			for ( int iEkiIndex = 0 ; iRv >= 0 && 
					iEkiIndex < pCentDedRessya->getCentDedEkiJikokuCount() ;
					iEkiIndex ++ ){
				wstring	strItem ;
				// --------------------------------
				CentDedEkiJikoku aCentDedEkiJikoku =
					 pCentDedRessya->getCentDedEkiJikoku(
						pCentDedRessya->EkiOrderOfEkiIndex( iEkiIndex ) ) ;
				
				if ( aCentDedEkiJikoku.getEkiatsukai() == 
						CentDedEkiJikoku::Ekiatsukai_Teisya ){
					//	停車
					if ( !aCentDedEkiJikoku.getChakujikoku().isNull() ){
						wstring str = g_CdDedJikokuConv.encode( aCentDedEkiJikoku.getChakujikoku() ) ;
						strItem += ( str + L'/' ) ;
					}
					if ( !aCentDedEkiJikoku.getHatsujikoku().isNull() ){
						wstring str = g_CdDedJikokuConv.encode( aCentDedEkiJikoku.getHatsujikoku() ) ;
						strItem += ( str ) ;
					}
				}	if ( aCentDedEkiJikoku.getEkiatsukai() == 
						CentDedEkiJikoku::Ekiatsukai_Tsuuka ){
					//	通過
					if ( !aCentDedEkiJikoku.getChakujikoku().isNull() ){
						wstring str = g_CdDedJikokuConv.encode( aCentDedEkiJikoku.getChakujikoku() ) ;
						strItem += ( str + L'?' + L'/' ) ;
					}
					if ( !aCentDedEkiJikoku.getHatsujikoku().isNull() ){
						wstring str = g_CdDedJikokuConv.encode( aCentDedEkiJikoku.getHatsujikoku() ) ;
						strItem += ( str + L'?' ) ;
					}
					if ( strItem.empty() ){
						//	時刻指定なしの通過
						strItem = L"-" ;
					}
				}	if ( aCentDedEkiJikoku.getEkiatsukai() == 
						CentDedEkiJikoku::Ekiatsukai_Keiyunasi){
					//	経由なし

					//	(通過とみなします）
					strItem = L"-" ;
				}
				// --------------------------------
				strLine += L',' ;
				strLine += strItem ;
			}
		}
		// --------------------------------
		//	備考
		// --------------------------------
		if ( iRv >= 0 ){
			wstring strBikou = pCentDedRessya->getBikou() ;
			if ( !strBikou.empty() ){
				strLine += L",%" ;
				strLine += strBikou ; 
			}
		}
		pstrcontSection->insert( strLine ) ;
	}
	
	
	// --------------------------------
	return ( iRv ) ;
}

/**
 *	CentDedRosen オブジェクトに格納されているすべての列車のうち、
 *	終着駅の駅時刻形式が[発時刻]の列車の終着駅着時刻を
 *	発時刻に補正します（終着時刻を時刻表ビューに表示させるため）。
 *
 * @param pCentDedRosen [in]
 *	この関数は、この『路線』 CentDedRosen	オブジェクト内の列車を
 *	補正します。
 * @return
 *	成功したら 0 以上、エラーなら負の数です。
 *	-	現在は 0 しか返しません。
 */
static int CentDedRosen_SyuuchakuekiEkijikokuHosei( 
	CentDedRosen* pCentDedRosen )
{
	int iRv = 0 ;
	if ( iRv >= 0 ){
		CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont() ;
		Mu<CentDedDia*>* pCentDedDiaContGet = pCentDedRosen->getCentDedDiaCont()->getMuPtr() ;

		//	ダイヤ毎のループ
		for ( int iDiaIndex = 0 ; iRv >= 0 && iDiaIndex < pCentDedDiaContGet->size() ; iDiaIndex ++ ){
			CentDedDia* pCentDedDia = pCentDedDiaContGet->get( iDiaIndex ) ;

			//	列車方向毎のループ
			for ( int iRessyahoukou = Ressyahoukou_Kudari ;
					iRv >= 0 && iRessyahoukou <= Ressyahoukou_Nobori ;
					iRessyahoukou ++ ){
				Mu<CentDedRessya*>* pCentDedRessyaContGet = 
					pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou )->getMuPtr() ;

				//	列車毎のループ
				for ( int iRessyaIndex = 0 ; iRv >= 0 && iRessyaIndex < pCentDedRessyaContGet->size() ; iRessyaIndex ++ ){
					CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get( iRessyaIndex ) ;
					int iSyuuchakuEkiOrder = pCentDedRessya->getSyuuchakuEki() ;


					//iSyuuchakuEkiOrder = この列車の終着駅の駅Order
					//	時刻が全く入力されていない列車の場合は -1 になります。
					if ( iSyuuchakuEkiOrder >= 0 )
					{

						int iChaku = 0 ;
						int iHatsu = 0 ;
						
						const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont = pCentDedEkiCont->getMuPtr( (ERessyahoukou)iRessyahoukou ) ;
						CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get( iSyuuchakuEkiOrder ) ;
						if ( aCdDedEki.getChakujikokuHyouji() )
						{
							iChaku = 1 ;
						}
						if ( aCdDedEki.getHatsujikokuHyouji() )
						{
							iHatsu = 1 ;
						}
						
						//　以下の条件を満たす列車
						//
						//		終着駅の駅時刻形式が、「着時刻を表示しない」「発時刻を表示する」
						//		終着駅の駅時刻の着時刻が設定あり・発時刻が設定なし
						//
						//	に対して、以下の処理を行う
						//
						//	終着駅の駅時刻の着時刻を発時刻に設定。発時刻は空欄にする。

						CentDedEkiJikoku	aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku( iSyuuchakuEkiOrder ) ;
						if ( iChaku == 0 && iHatsu == 1 && 
								!aCentDedEkiJikoku.getChakujikoku().isNull() && 
								aCentDedEkiJikoku.getHatsujikoku().isNull() ){
							aCentDedEkiJikoku.setHatsujikoku( aCentDedEkiJikoku.getChakujikoku() ) ;
							aCentDedEkiJikoku.setChakujikoku( CdDedJikoku() ) ;
							pCentDedRessya->setCentDedEkiJikoku( iSyuuchakuEkiOrder , aCentDedEkiJikoku ) ;
						}

					}
				}
			}
				
		}
	}
	return ( iRv ) ;
}





// ********************************
//	CDedRosenFileData
// ********************************

int CconvWinDia::CDedRosenFileData_From_WinDiaFileString(
		CDedRosenFileData* pCDedRosenFileData ,
		const wstring& strWinDiaFileString ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	CDedRosenFileData を初期化
	// --------------------------------
	CentDedRosen* pCentDedRosen = NULL ;
	if ( iRv >= 0 ){
		*pCDedRosenFileData = CDedRosenFileData() ;
		pCentDedRosen = pCDedRosenFileData->getCentDedRosen() ;
		pCentDedRosen->getCentDedDiaCont()->insert( 
			CentDedDia( 
				L"ダイヤ" , 
				pCentDedRosen->getCentDedEkiCont()->getMuPtr()->size() , 
				pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()->size() ) 
		) ;
	}
	// --------------------------------
	//	文字列を行ごとに分割
	// --------------------------------
	CMup_deque< wstring >	contstrWinDiaFile ;
	if ( iRv >= 0 ){
		ContStrFromString( 
			&contstrWinDiaFile ,
			strWinDiaFileString ) ;
	}
	//contstrWinDiaFile = WinDia 文字列を、行ごとに分割しました。
	 

	// --------------------------------
	//	[WinDIA]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionWinDia ;
		WinDiaFile_getSection(
			&contstrWinDiaFile , 
			L"WinDIA" , 
			&contstrSectionWinDia ) ;
		int iResult = CentDedRosen_readWinDIASection( 
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionWinDia ) ;
		if ( iResult < 0 ){
			iRv = iResult ;
		}
	}
	// --------------------------------
	//	[駅]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionEki ;
		WinDiaFile_getSection(
				&contstrWinDiaFile , 
				L"駅" , 
				&contstrSectionEki ) ;
		int iResult = CentDedRosen_readEkiSection( 
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionEki ) ;
		if ( iResult < 0 ){
			iRv = iResult - 10 ;
		}	
	}
	// --------------------------------
	//	[線種]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionSensyu ;
		WinDiaFile_getSection(
				&contstrWinDiaFile , 
			L"線種" , 
			&contstrSectionSensyu ) ;
		int iResult = CentDedRosen_readSensyuSection( 	
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionSensyu ) ;
		//iResult = 
		//	-1 ;	//	Train00 の番号部分の値が不適切です。
		if ( iResult < 0 ){
			iRv = iResult - 20 ;
			//iRv = 
			//	-21 ;	//	Train00 の番号部分の値が不適切です。
		}	
	}
	// --------------------------------
	//	[下り]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionKudari ;
		WinDiaFile_getSection(
			&contstrWinDiaFile , 
			L"下り" , 
			&contstrSectionKudari ) ;
		CentDedRessyaCont* pCentDedRessyaCont = 
			pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( 0 )->
			getCentDedRessyaCont( Ressyahoukou_Kudari ) ;
		int iResult = CentDedRosen_readKudariNoboriSection( 
			pCentDedRessyaCont ,
			&contstrSectionKudari ) ; 
		if ( iResult < 0 ){
			iRv = iResult - 30 ;
		}	
	}
	// --------------------------------
	//	[上り]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionNobori ;
		WinDiaFile_getSection(
			&contstrWinDiaFile , 
			L"上り" , 
			&contstrSectionNobori ) ;
		CentDedRessyaCont* pCentDedRessyaCont = 
			pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( 0 )->
			getCentDedRessyaCont( Ressyahoukou_Nobori ) ;
		int iResult = CentDedRosen_readKudariNoboriSection( 
			pCentDedRessyaCont ,
			&contstrSectionNobori ) ; 
		if ( iResult < 0 ){
			iRv = iResult -40 ;
		}	
	}
	// --------------------------------
	//	[下り]・[上り]セクション
	//	終着駅の駅時刻形式が[発時刻]の列車の終着駅着時刻を
	//	発時刻に補正する（終着時刻を時刻表ビューに表示させるため）
	// --------------------------------
	if ( iRv >= 0 ){
		int iResult = CentDedRosen_SyuuchakuekiEkijikokuHosei( pCentDedRosen );
		if ( iResult < 0 ){
			iRv = iResult -50 ;
		}	
	}
	
	
	// --------------------------------
	return iRv ;
}

int CconvWinDia::CDedRosenFileData_To_WinDiaFileString( 
		const CDedRosenFileData* pCDedRosenFileData ,
		int idxDia ,
		wstring* pstrWinDiaFileString ) 
{
	int iRv = 0 ;

	
	// --------------------------------
	CMup_deque< wstring >	contstrWinDiaFile ;
	const CentDedRosen* pCentDedRosen = NULL ;
	if ( iRv >= 0 ){
		pCentDedRosen = pCDedRosenFileData->getCentDedRosen() ;
	}	 
	// --------------------------------
	//	ガード条件
	// --------------------------------
	if ( iRv >= 0 ){
		if ( !( 0 <= idxDia && 
				idxDia < pCentDedRosen->getCentDedDiaCont()->getMuPtr()->size() ) ){
			iRv = -1 ;	//	idxDia の指定が不正です。
		}
	}

	// --------------------------------
	//	[WinDIA]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionWinDia ;
		int iResult = CentDedRosen_writeWinDIASection( 
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionWinDia ) ;
		if ( iResult < 0 ){
			iRv = iResult ;
		}	else	{
			WinDiaFile_setSection(
				&contstrWinDiaFile , 
				L"WinDIA" , 
				&contstrSectionWinDia ) ;
		}
	}
	// --------------------------------
	//	[駅]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionEki ;
		int iResult = CentDedRosen_writeEkiSection( 
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionEki ) ;
		if ( iResult < 0 ){
			iRv = iResult - 10 ;
		}	else	{
			WinDiaFile_setSection(
					&contstrWinDiaFile , 
					L"駅" , 
					&contstrSectionEki ) ;
		}
	}
	// --------------------------------
	//	[線種]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionSensyu ;
		int iResult = CentDedRosen_writeSensyuSection( 	
				pCDedRosenFileData->getCentDedRosen() ,
				&contstrSectionSensyu ) ;
		//iResult = 
		//	-1 ;	//	WinDIA 形式では、列車種別は24種類までに制限されています。
		//	-2 ;	//	略称の長さが半角５文字を超える列車種別があります。
		if ( iResult < 0 ){
			iRv = iResult - 20 ;
		}	else	{	
			WinDiaFile_setSection(
				&contstrWinDiaFile , 
				L"線種" , 
				&contstrSectionSensyu ) ;
		}
	}
	// --------------------------------
	//	[下り]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionKudari ;
		const CentDedRessyaCont* pCentDedRessyaCont = 
			pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( idxDia )->
			getCentDedRessyaCont( Ressyahoukou_Kudari ) ;
		int iResult = CentDedRosen_writeKudariNoboriSection( 
			pCentDedRessyaCont ,
			&contstrSectionKudari ) ; 
		//	-	現在は 0 しか返しません。
		if ( iResult < 0 ){
			iRv = iResult - 30 ;
		}	else	{
			WinDiaFile_setSection(
				&contstrWinDiaFile , 
				L"下り" , 
				&contstrSectionKudari ) ;
		}
	}
	// --------------------------------
	//	[上り]セクション
	// --------------------------------
	if ( iRv >= 0 ){
		CMup_deque< wstring >	contstrSectionNobori ;
		const CentDedRessyaCont* pCentDedRessyaCont = 
			pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( idxDia )->
			getCentDedRessyaCont( Ressyahoukou_Nobori ) ;
		int iResult = CentDedRosen_writeKudariNoboriSection( 
			pCentDedRessyaCont ,
			&contstrSectionNobori ) ; 
		//	-	現在は 0 しか返しません。
		if ( iResult < 0 ){
			iRv = iResult - 40 ;
		}	else	{
			WinDiaFile_setSection(
				&contstrWinDiaFile , 
				L"上り" , 
				&contstrSectionNobori ) ;
		}
	}
	//contstrWinDiaFile = WinDia 文字列すべて格納しました。
	
	// --------------------------------
	//	行ごとに分割されたコンテナを、文字列に結合
	// --------------------------------
	if ( iRv >= 0 ){
		*pstrWinDiaFileString = ContStrToString( &contstrWinDiaFile ) ;
	}
	return iRv ;
}



} //namespace WinDia
