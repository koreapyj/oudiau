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
//	CconvDcDrawProp.cpp
//$Id: CconvDcDrawProp.cpp 110 2012-09-30 01:24:19Z okm $
// ****************************************************************
/** @file */
#include "StdAfx.h"

#include "DcdCd\DcDrawProp\CconvDcDrawProp.h"
#include "str\strprintf.h"
#include "str\strToInt.h"

namespace DcDrawLib{
namespace DcdCd{
namespace DcDrawProp{

using namespace std ;
using namespace OuLib ;
const wchar_t namePointTextHeight[] = L"PointTextHeight" ; 
const wchar_t nameLogicalunitTextHeight[] = L"LogicalunitTextHeight" ; 
const wchar_t nameLogicalunitCellHeight[] = L"LogicalunitCellHeight" ;
const wchar_t nameFacename[] = L"Facename" ; 
const wchar_t nameBold[] = L"Bold" ; 
const wchar_t nameItaric[] = L"Itaric" ; 
const wchar_t nameUnderline[] = L"Underline" ; 
const wchar_t nameStrikeOut[] = L"StrikeOut" ; 
const wchar_t nameEscapement[] = L"Escapement" ; 


	// ********************************
	//	コンストラクタ
	// ********************************
CconvDcDrawProp::CconvDcDrawProp(void)
{
}

CconvDcDrawProp::~CconvDcDrawProp(void)
{
}

	// ********************************
	//@name CdFontProp
	// ********************************
int CconvDcDrawProp::CdFontProp_to_CdConnnectedString2( 
	const CdFontProp& aCdFontProp ,
	CdConnectedString2*	pCdConnectedString )
{
	int iRv = 0 ;

	//1.PointTextHeight 
	if ( iRv >= 0 )
	{
		int iValue = aCdFontProp.getPointTextHeight() ;
		if ( iValue != 0 )
		{
			wstring aStr = strprintf( L"%d" , iValue ) ;
			pCdConnectedString->setItem( namePointTextHeight , aStr ) ;
		}
	}
	//2.LogicalunitTextHeight 
	if ( iRv >= 0 )
	{
		int iValue = aCdFontProp.getLogicalunitTextHeight() ;
		if ( iValue != 0 )
		{
			wstring aStr = strprintf( L"%d" , iValue ) ;
			pCdConnectedString->setItem( nameLogicalunitTextHeight , aStr ) ;
		}
	}
	//3.LogicalunitCellHeight 
	if ( iRv >= 0 ){
		int iValue = aCdFontProp.getLogicalunitCellHeight() ;
		if ( iValue != 0 )
		{
			wstring aStr = strprintf( L"%d" , iValue ) ;
			pCdConnectedString->setItem( nameLogicalunitCellHeight , aStr ) ;
		}
	}
	//4.Facename 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdFontProp.getFacename() ;
		pCdConnectedString->setItem( nameFacename , strValue ) ;
	}
	//5.Bold 
	if ( iRv >= 0 )
	{
		bool bValue = aCdFontProp.getBold() ;
		if ( bValue )
		{
			pCdConnectedString->setItem( nameBold , bValue ? L"1" : L"0"  ) ;
		}
	}
	//6.Itaric 
	if ( iRv >= 0 )
	{
		bool bValue = aCdFontProp.getItaric() ;
		if ( bValue )
		{
			pCdConnectedString->setItem( nameItaric , bValue ? L"1" : L"0"  ) ;
		}
	}
	//7.Underline 
	if ( iRv >= 0 )
	{
		bool bValue = aCdFontProp.getUnderline() ;
		if ( bValue )
		{
			pCdConnectedString->setItem( nameUnderline , bValue ? L"1" : L"0"  ) ;
		}
	}
	//8.StrikeOut 
	if ( iRv >= 0 )
	{
		bool bValue = aCdFontProp.getStrikeOut() ;
		if ( bValue )
		{
			pCdConnectedString->setItem( nameStrikeOut , bValue ? L"1" : L"0"  ) ;
		}
	}
	//9.Escapement
	if ( iRv >= 0 )
	{
		int iValue = aCdFontProp.getEscapement() ;
		if ( iValue != 0 )
		{
			wstring aStr = strprintf( L"%d" , iValue ) ;
			pCdConnectedString->setItem( nameEscapement , aStr ) ;
		}
	}
	
	return ( iRv ) ;
}


int CconvDcDrawProp::CdFontProp_from_CdConnectedString2( 
	CdFontProp* pCdFontProp ,
	const CdConnectedString2& aCdConnectedString )
{
	int	iRv = 0 ;

	CdFontProp	aCdFontProp ;

	//1.PointTextHeight 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( namePointTextHeight ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <= iValue ) )
			{
				iRv = -12 ;	//	PointTextHeight の値が不正
			}
			else if ( 0 < iValue )
			{
				aCdFontProp.setPointTextHeight( iValue ) ;
			}
		}
	}
	//2.LogicalunitTextHeight 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameLogicalunitTextHeight ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <= iValue ) )
			{
				iRv = -22 ;	//	LogicalunitTextHeight の値が不正
			}
			else if ( 0 < iValue )
			{
				aCdFontProp.setLogicalunitTextHeight( iValue ) ;
			}
		}
	}
	//3.LogicalunitCellHeight 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameLogicalunitCellHeight ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <= iValue ) )
			{
				iRv = -32 ;	//	LogicalunitCellHeight の値が不正
			}
			else if ( 0 < iValue )
			{
				aCdFontProp.setLogicalunitCellHeight( iValue ) ;
			}
		}
	}
	//4.Facename 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameFacename ) ;
		if ( strValue.length() == 0 )
		{
			iRv = -42 ;	//	Facename の値が不正
		}
		else
		{
			aCdFontProp.setFacename( strValue ) ;
		}
	}
	//5.Bold 
	if ( iRv >= 0 ){
		wstring strValue = aCdConnectedString.getValue( 
			nameBold ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <=  iValue && iValue <= 1 ) )
			{
				iRv = -52 ;	//	Bold の値が不正
			}
			else
			{
				aCdFontProp.setBold( iValue == 1 ) ;
			}
		}
	}
	//6.Itaric 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameItaric ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <=  iValue && iValue <= 1 ) )
			{
				iRv = -62 ;	//	Itaric の値が不正
			}
			else
			{
				aCdFontProp.setItaric( iValue == 1 ) ;
			}
		}
	}
	//7.Underline 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameUnderline ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <=  iValue && iValue <= 1 ) )
			{
				iRv = -72 ;	//	Underline の値が不正
			}
			else
			{
				aCdFontProp.setUnderline( iValue == 1 ) ;
			}
		}
	}
	//8.StrikeOut 
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameStrikeOut ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <=  iValue && iValue <= 1 ) )
			{
				iRv = -82 ;	//	StrikeOut の値が不正
			}
			else
			{
				aCdFontProp.setStrikeOut( iValue == 1 ) ;
			}
		}
	}
	//9.Escapement
	if ( iRv >= 0 )
	{
		wstring strValue = aCdConnectedString.getValue( 
			nameEscapement ) ;
		if ( !strValue.empty() )
		{
			int iValue = _wtoi( strValue.c_str() ) ;
			if ( !( 0 <= iValue ) )
			{
				iRv = -92 ;	//	Escapement の値が不正
			}
			else if ( 0 < iValue )
			{
				aCdFontProp.setEscapement( iValue ) ;
			}
		}
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCdFontProp = aCdFontProp ;
	}

	return ( iRv ) ;
}

wstring CconvDcDrawProp::CdFontProp_to_string( const CdFontProp& aCdFontProp )
{
	int iRv = 0 ;
	CdConnectedString2	aCdConnectedString2 ;
	if ( iRv >= 0 ){
		iRv = CdFontProp_to_CdConnnectedString2( aCdFontProp ,
			&aCdConnectedString2 );
	}
	if ( iRv >= 0 ){
		return ( aCdConnectedString2 ) ;
	}
	return ( L"" ) ;
}



int CconvDcDrawProp::CdFontProp_from_string( 
	CdFontProp* pCdFontProp , 
	const wstring& aString  )
{
	int	iRv = 0 ;
	CdConnectedString2	aCdConnectedString( aString )  ;
	if ( iRv >= 0 ){
		iRv = CdFontProp_from_CdConnectedString2( pCdFontProp ,
			aCdConnectedString );
	}
	return ( iRv ) ;
}
	// ********************************
	//@name CdColorProp
	// ********************************

wstring CconvDcDrawProp::CdColorProp_to_string( const CdColorProp& aCdColorProp )
{
	unsigned long iColorref = 
		((unsigned long)aCdColorProp.getRed() << 0 )|
		((unsigned long)aCdColorProp.getGreen() << 8 ) | 
		((unsigned long)aCdColorProp.getBlue() << 16 ) ; 

	return strprintf( L"%08X" , iColorref ) ;
}

CdColorProp CconvDcDrawProp::CdColorProp_from_string( const wstring& aString  )
{
	unsigned long dwColor = wcstoul( aString.c_str() , NULL , 16 ) ;
	CdColorProp	aCdColorProp( 
		(unsigned char)(( dwColor >>  0 ) & 0xff) , 
		(unsigned char)(( dwColor >>  8 ) & 0xff) , 
		(unsigned char)(( dwColor >> 16 ) & 0xff) ) ;
	return aCdColorProp ;
}

	// ********************************
	///@name CdDcdFreeLineProp
	// ********************************

const wchar_t nameLogicalunitWidth[] = L"LogicalunitWidth" ;
const wchar_t nameColor[] = L"Color" ;
const wchar_t nameLinestyle[] = L"Linestyle" ;

int CconvDcDrawProp::CdDcdFreeLineProp_to_CdConnectedString2( 
	const CdDcdFreeLineProp& aCdDcdFreeLineProp ,
	CdConnectedString2*	pCdConnectedString )
{
	int iRv = 0 ;
	CconvDcDrawProp	aCconvDcDrawProp ;

	//int			m_iLogicalunitWidth ;
	if ( iRv >= 0 )
	{
		int iValue = aCdDcdFreeLineProp.getLogicalunitWidth() ;
		{
			wstring aStr = wstringOf( iValue ) ;
			pCdConnectedString->setItem( nameLogicalunitWidth , aStr ) ;
		}
	}
	//CdColorProp	m_colorrefColor ;
	if ( iRv >= 0 )
	{
		{
			wstring aStr = aCconvDcDrawProp.CdColorProp_to_string( 
				aCdDcdFreeLineProp.getColor() ) ;
			pCdConnectedString->setItem( nameColor , aStr ) ;
		}
	}

	//std::wstring	m_strLinestyle ;
	if ( iRv >= 0 )
	{
			pCdConnectedString->setItem( nameLinestyle , 
				aCdDcdFreeLineProp.getLinestyle() ) ;
	}

	return iRv ;
}

wstring CconvDcDrawProp::CdDcdFreeLineProp_to_string( 
	const CdDcdFreeLineProp& aCdDcdFreeLineProp )
{
	int iRv = 0 ;
	CdConnectedString2	aCdConnectedString2 ;
	if ( iRv >= 0 )
	{
		iRv = CdDcdFreeLineProp_to_CdConnectedString2( 
			aCdDcdFreeLineProp ,
			&aCdConnectedString2 );
	}
	if ( iRv >= 0 )
	{
		return ( aCdConnectedString2 ) ;
	}
	return ( L"" ) ;
}


int CconvDcDrawProp::CdDcdFreeLineProp_from_CdConnectedString2( 
		CdDcdFreeLineProp* pCdDcdFreeLineProp ,
		const CdConnectedString2*	pCdConnectedString ) 
{
	int iRv = 0 ;
	CdDcdFreeLineProp	aCdDcdFreeLineProp ;
	//const wchar_t nameLogicalunitWidth[] = "LogicalunitWidth" ;
	if ( iRv >= 0 )
	{
		int iValue = 0 ;
		wstring	strValue = pCdConnectedString->getValue( nameLogicalunitWidth ) ;
		if ( iRv >= 0 )
		{
			if ( strValue.length() <= 0 )
			{
				iRv = -11 ;	//	LogicalunitWidth の値が不正です
			}
			else
			{
				iValue = intOf( strValue ) ;
				if ( iValue < 0 )
				{
					iRv = -11 ;	//	LogicalunitWidth の値が不正です
				}
			}
		}
		if ( iRv >= 0 )
		{
			aCdDcdFreeLineProp.setLogicalunitWidth( iValue ) ;
		}
	}
	//const wchar_t nameColor[] = "Color" ;
	if ( iRv >= 0 )
	{
		CdColorProp	aCdColorProp ;
		wstring	strValue = pCdConnectedString->getValue( nameColor ) ;
		if ( iRv >= 0 )
		{
			if ( strValue.length() <= 0 )
			{
				iRv = -12 ;	//	Color の値が不正です
			}
			else
			{
				aCdColorProp = CdColorProp_from_string( strValue ) ;
			}
		}
		if ( iRv >= 0 )
		{
			aCdDcdFreeLineProp.setColor( aCdColorProp ) ;
		}
	}
	//const wchar_t nameLinestyle[] = "Linestyle" ;
	{
		CdColorProp	aCdColorProp ;
		wstring	strValue = pCdConnectedString->getValue( nameLinestyle ) ;
		aCdDcdFreeLineProp.setLinestyle( strValue ) ;
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		if ( pCdDcdFreeLineProp != NULL )
		{
			*pCdDcdFreeLineProp = aCdDcdFreeLineProp ;
		}
	}
	return iRv ;
}

int CconvDcDrawProp::CdDcdFreeLineProp_from_string( 
		CdDcdFreeLineProp* pCdDcdFreeLineProp ,
		const std::wstring& aString  )
{
	int iRv = 0 ;
	CdDcdFreeLineProp	aCdDcdFreeLineProp ;

	if ( iRv >= 0 )
	{
		int iResult = CdDcdFreeLineProp_from_CdConnectedString2( 
			&aCdDcdFreeLineProp , 
			&CdConnectedString2( aString ) ) ;
	}
	//iRv = 
	//	-	-11 ;	//	LogicalunitWidth の値が不正です
	//	-	-12 ;	//	Color の値が不正です
	// --------------------------------
	if ( iRv >= 0 )
	{
		if ( pCdDcdFreeLineProp != NULL )
		{
			*pCdDcdFreeLineProp = aCdDcdFreeLineProp ;
		}
	}
	return iRv ;
}

} //namespace DcDrawProp
} //namespace DcdCd
} //namespace DcDrawLib

