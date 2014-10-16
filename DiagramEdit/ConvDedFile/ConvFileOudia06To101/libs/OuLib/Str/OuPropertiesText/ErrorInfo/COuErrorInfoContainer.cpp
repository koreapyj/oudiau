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
// $Id: COuErrorInfoContainer.cpp 10 2012-08-26 09:48:47Z okm $
// ****************************************************************
#include "str\OuPropertiesText\ErrorInfo\COuErrorInfoContainer.h"
#include "str\OuPropertiesText\CDirectory.h"
#include "Ou\dynamic_castOu.h"
#include "Ou\OuNew.h"

using namespace std ;
namespace OuPropertiesText{
namespace ErrorInfo{



// ****************************************************************
//	COuErrorInfoContainer
// ****************************************************************
	// ********************************
	//	コンストラクタ
	// ********************************
COuErrorInfoContainer::COuErrorInfoContainer()
{
}
	// ********************************
	//@name 関連
	// ********************************
IfCont<COuErrorInfo>* COuErrorInfoContainer::getCOuErrorInfoCont()
{
	return this ;
}
const IfCont<COuErrorInfo>* COuErrorInfoContainer::getCOuErrorInfoCont()const
{
	return this ;
};

	// ********************************
	//@name 操作
	// ********************************
	///@{
CNodeContainer COuErrorInfoContainer::toOuPropertiesTextErrorInfo()const
{
	CNodeContainer aCNodeContainer ;
	for ( int idx = 0 ; idx < this->size() ; idx ++ )
	{
		COuErrorInfo	aCOuErrorInfo = this->get( idx );
		Ou<CDirectory> pErrorInfo = aCOuErrorInfo.toOuPropertiesTextErrorInfo()  ;
		aCNodeContainer.insert( pErrorInfo ) ;

	}
	return aCNodeContainer ;
}

	/**
		OuPropertiesTextErrorInfo を保持している
		OuPropertiesText の内容を、this に反映します。
	@param aCNodeContainer [in]
		OuPropertiesTextErrorInfo を保持している
		OuPropertiesText の内容を指定してください。
	@return
		成功したら 0 以上、エラーなら負の数です。
	*/
int COuErrorInfoContainer::
fromOuPropertiesTextErrorInfo( const CNodeContainer* pCNodeContainer )
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		this->erase( 0 , INT_MAX ) ;
	}
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ;
			iRv >= 0 && 
			idx < pCNodeContainer->sizeInName( COuErrorInfo::DirectoryName_ErrorInfo ) ; 
			idx ++ )
		{
			Ou<CNode> pCNode = pCNodeContainer->getInName( COuErrorInfo::DirectoryName_ErrorInfo , idx ) ;
			Ou<CDirectory> pCDirectory = dynamic_castOu<CDirectory>( pCNode ) ;
			if ( pCDirectory != NULL )
			{
				COuErrorInfo	aCOuErrorInfo ;
				int iResult = aCOuErrorInfo.fromOuPropertiesTextErrorInfo( pCDirectory ) ;
				//	-1 ;	//	pCDirectory は "Directory" ではありません。
				//	-2 ;	//	Directory に"Reason" PropertyText がありません。
				if ( iResult < 0 )
				{
					//	-1 ;	//	pCDirectory は "Directory" ではありません。
					//	-2 ;	//	Directory に"Reason" PropertyText がありません。
					iRv = iResult ;
				}
				else
				{
					this->insert( aCOuErrorInfo ) ;
				}
			}
		}
	}

	return iRv ;
}
std::string COuErrorInfoContainer::toOuErrorInfoText()const 
{
	string strRv ;
	for ( int idxErrorInfo = 0 ; idxErrorInfo < this->size() ; idxErrorInfo ++ )
	{
		if ( !strRv.empty() )
		{
			strRv += '\n' ;
		}
		strRv += this->get( idxErrorInfo ).toOuErrorInfoText() ;
	}
	return strRv ;
}
#include "str\stringSplit.h"
int COuErrorInfoContainer::fromOuErrorInfoText( const std::string& strOuErrorInfoText ) 
{
	int iRv = 0 ;
	this->erase( 0 , INT_MAX ) ;
	deque<string> contstrLines = OuLib::splitc< deque< string > >( '\n' , strOuErrorInfoText ) ;
	for ( int idxLine = 0 ; 
		iRv >= 0 && idxLine < (int)contstrLines.size() ; 
		idxLine ++ )
	{
		COuErrorInfo aCOuErrorInfo ;
		int iResult = aCOuErrorInfo.fromOuErrorInfoText( contstrLines[idxLine] ) ;
		if ( iResult < 0 )
		{
			iRv = -1 ;	//	解釈に失敗しました。
		}
		else
		{
			this->insert( aCOuErrorInfo ) ;
		}
	}
	return iRv ;
}

} //namespace ErrorInfo{
} //namespace OuPropertiesText{
