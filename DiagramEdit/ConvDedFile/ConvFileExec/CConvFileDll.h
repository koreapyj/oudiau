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
// CConvFileDll.h: CConvFileDll クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////
/** @file */
//$Id: CConvFileDll.h 10 2012-08-26 09:48:47Z okm $


#if !defined(AFX_CCONVFILEDLL_H__162E52FE_B36F_46AC_970A_5F0CD20B7F20__INCLUDED_)
#define AFX_CCONVFILEDLL_H__162E52FE_B36F_46AC_970A_5F0CD20B7F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <vector>
using namespace std ;


#include "ConvFile2Dll.h"
#include "IfConvFile.h"
/**
  このクラスは、 ConvFileDll を使ったフォーマット変換を行うラッパークラスです。

*/
class CConvFileDll  
{
private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		このクラスが利用するConvFileDllのファイル名。
		コンストラクタで決まります。
	*/
	string	m_strDllFilename ;

	///@}
	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
		通常はNULL。
		validate() から invalidate() までは、DLLのハンドルが入ります。
	*/
	HMODULE	m_hModule ;

	/**
		通常はNULL。
		validate() から invalidate() までは、
		DLL関数のAPIとなります。
	*/
	ConvFile2Dll_getIfConvFile_FUNCPTR	ConvFile2Dll_getIfConvFile ;

	///@}
public:
	// ********************************
	//	コンストラクタ・デストラクタ
	// ********************************
	CConvFileDll( const string&	strDllFilename );
	virtual ~CConvFileDll();

	// ********************************
	///@name 属性
	// ********************************
	///@{
	string	getDllFilename()const
	{	return m_strDllFilename ;};
	///@}

	// ********************************
	///@name IfValidate
	// ********************************
	///@{
	/**
	 * 	　オブジェクトの準備処理を行い、有効化します。
	 * 	　準備処理にあたって必要なパラメータは、コンストラクタなどで
	 * 	指定している
	 * 	必要があります。
	 * @return
	 * 	　有効化に成功したら１以上、
	 * 	　すでに有効化が終了していた場合は０、
	 * 	　エラーの場合は負の数を返します。\n
	 * 	　成功したときの１以上の値の意味は、実装するクラスが自由に定義
	 * 	できます。\n
	 * 	　失敗したときの負の数の意味も、実装クラスが定義できます。これにより、
	 * 	失敗の理由ごとに異なるエラー値を返すことができます。
	 *	-	-1 ;	//	DLLがロードできません。
	 * 	
	 */
	virtual int validate() ;
	
	/**
	 * 	　オブジェクトを無効化します。
	 * 	　有効化時に確保したリソースを開放します。
	 * 	  有効状態でないオブジェクトに対しては、なにもしません。
	 */
	virtual void invalidate() ;
	
	/**
	 * @return
	 * 	　現在オブジェクトが有効状態であれば真を返します。
	 */
	virtual bool isValid() ;
	///@}
	// ********************************
	///@name	CConvFile2Dll
	// ********************************
	///@{
	/**
	 * @return
	 * 	　IfConvFile インターフェースを返します。
	 */
	IfConvFile* getIfConvFile() ;
	///@}	
};

#endif // !defined(AFX_CCONVFILEDLL_H__162E52FE_B36F_46AC_970A_5F0CD20B7F20__INCLUDED_)
