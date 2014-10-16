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
//	IfConvFile.h
// ****************************************************************
/** @file */
#ifndef  IfConvFile_h
#define  IfConvFile_h

#include "IfByteBuffer.h"

// ****************************************************************
//	IfConvFile
// ****************************************************************
/**
@brief
  ConvFile オブジェクトは、ファイルフォーマットの変換を行うオブジェクトです。
  
  IfConvFile は、 ConvFile オブジェクトのインターフェースです。

  ConvFile オブジェクトは通常、 ConvFile_LeftFormatNameToRightFormatName
という形式のクラス名を持ちます。
  LeftFormatName,RightFormatName はフォーマット名に置き換えられます

  LeftToRight() メソッドにより、
  LeftFormat から RightFormat への変換を行うことができます。
  
　反対方向の変換を行う LeftFromRight() メソッドは、サポートしていない
場合があります。 LeftFromRightIsSupported() メソッドにより、
そのクラスが RightFormat から LeftFormat への変換をサポートしているか否かを
調べることができます。
  

*/
class IfConvFile
{
public:
	/**
		LeftFormat から RightFormat への変換を行います。
	@param pLeftFormat [in]
		LeftFormat のデータを指定してください。
	@param pRightFormat [out]
		この関数は変換が成功したら、
		このバッファに、RightFormat のデータを書き込みます。
	@param pErrorInfoString [out] 
		この関数は変換が失敗したら、
		このバッファにエラーの内容を示す文字列を
		書き込みます。
		但し、すべての ConvFile クラスがこの機能をサポートしているわけでは
		ありません。
		不要であればNULLでもかまいません。
	@return  
		成功したら 0 以上、エラーなら負の数です。
		-	-1 ;	//	pLeftFormat は正しい LeftFormat ではありません。
	*/
	virtual int LeftToRight( 
		const IfByteBuffer* pLeftFormat , 
		IfByteBuffer* pRightFormat , 
		IfByteBuffer* pErrorInfoString ) = 0 ; 

	/**
		LeftFormat が変換可能なフォーマットであるか否かを
		判定します。
		
		この関数は LeftFormat のデータの特徴に対して簡単な検査を
		行います。
		この関数が成功しても、 LeftToRight() が成功するとは
		限りません。
	@param pLeftFormat [in]
		LeftFormat のデータを指定してください。
	@return  
		成功したら 0 以上、エラーなら負の数です。
		-	0 以上 ;	//	変換可能なフォーマットです。
		-	-1 ;	//	pLeftFormat は正しい LeftFormat ではありません。
	*/
	virtual int isLeftFormat( 
		const IfByteBuffer* pLeftFormat) = 0 ; 

	/**
	@return 
		- true ;	//	RightToLeft(),isRightFormat() メソッドをサポートしています。
		- false ;	//	RightToLeft(),isRightFormat() メソッドをサポートしていません。
	*/
	virtual bool RightToLeftIsSupported() = 0 ; 

	/**
		RightFormat から LeftFormat への変換を行います。
	@param pRightFormat [in]
		RightFormat のデータを指定してください。
	@param pLeftFormat [out]
		この関数は変換が成功したら、
		このバッファに、LeftFormat のデータを書き込みます。
	@param pErrorInfoString [out] 
		この関数は変換が失敗したら、
		このバッファにエラーの内容を示す文字列を
		書き込みます。
		但し、すべての ConvFile クラスがこの機能をサポートしているわけでは
		ありません。
		不要であればNULLでもかまいません。
	@return  
		成功したら 0 以上、エラーなら負の数です。
		-	-1 ;	//	pLeftFormat は正しい LeftFormat ではありません。
		-	-2 ;	//	このメソッドはサポートされていません。
	*/
	virtual int RightToLeft( 
		const IfByteBuffer* pRightFormat , 
		IfByteBuffer* pLeftFormat , 
		IfByteBuffer* pErrorInfoString ) = 0 ; 

	/**
		RightFormat が変換可能なフォーマットであるか否かを
		判定します。
		
		この関数は RightFormat のデータの特徴に対して簡単な検査を
		行います。
		この関数が成功しても、 LeftFromRight() が成功するとは
		限りません。
	@param pRightFormat [in]
		RightFormat のデータを指定してください。
	@return  
		成功したら 0 以上、エラーなら負の数です。
		-	0 以上 ;	//	変換可能なフォーマットです。
		-	-1 ;	//	pRightFormat は正しい RightFormat ではありません。
		-	-2 ;	//	このメソッドはサポートされていません。
	*/
	virtual int isRightFormat( 
		const IfByteBuffer* pRightFormat ) = 0 ; 

	virtual ~IfConvFile(){} ;
};

#endif //IfConvFile_h




