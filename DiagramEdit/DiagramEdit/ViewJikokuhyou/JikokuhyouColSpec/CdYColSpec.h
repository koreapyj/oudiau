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
// $Id: CdYColSpec.h 137 2012-10-07 06:42:01Z okm $
// ****************************************************************
/** @file */
#pragma once
#ifndef ViewJikokuhyou_CdYColSpec_h
#define ViewJikokuhyou_CdYColSpec_h

namespace ViewJikokuhyou{ namespace JikokuhyouColSpec{

/**
@brief
　時刻表ビューの CWndJikokuhyou において、グリッドのY列に表示
  すべき内容を記述した、単純データクラスです。

  この値は NULL 状態を持ちます。
*/
class CdYColSpec
{
public:
	// ********************************
	//	インナータイプ
	// ********************************
	/** Y列の種類 */
	enum EColumnType
	{
		/**	列車番号 */
		ColumnType_Ressyabangou = 0 ,
		/**	列車種別 */
		ColumnType_Ressyasyubetsu ,
		/**	列車名 */
		ColumnType_Ressyamei ,
		/**	号数 */
		ColumnType_Gousuu ,
		/**	「号」表示 */
		ColumnType_Gou ,
		/**	着時刻 */
		ColumnType_Ekijikoku_Chaku ,
		/**	発時刻 */
		ColumnType_Ekijikoku_Hatsu ,
		/**	備考 */
		ColumnType_Bikou ,

		/**	NULL状態を示します */
		ColumnType_NULL = -1 
	};

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/** Y列の種類 */
	EColumnType	m_eColumnType ;

	/** 
		駅Order。
		m_eColumnType が ColumnType_Ekijikoku_Chaku,
		ColumnType_Ekijikoku_Hatsu の場合にのみ有効です。

		その他の場合は意味を持ちません。-1 となります。
	*/
	int m_iEkiOrder ;
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************

	/**
	@param eColumnType 
		Y列の種類 
	@param iEkiOrder 
		駅Order。
		m_eColumnType が ColumnType_Ekijikoku_Chaku,
		ColumnType_Ekijikoku_Hatsu の場合にのみ有効です。
		その他の場合は意味を持ちません。
	*/
	CdYColSpec( 
		EColumnType eColumnType , 
		int iEkiOrder ) 
		: m_eColumnType( eColumnType ) 
		, m_iEkiOrder( iEkiOrder ){}
	CdYColSpec( 
		EColumnType eColumnType ) 
		: m_eColumnType( eColumnType ) 
		, m_iEkiOrder( -1 ){}
	CdYColSpec()
		: m_eColumnType( ColumnType_NULL ) 
		, m_iEkiOrder( -1 ){}

public:
	// ********************************
	///@name CdYColSpec-属性
	// ********************************
	EColumnType	getColumnType()const{	return m_eColumnType ;};
	int getEkiOrder()const{ return m_iEkiOrder ;};

	/**
	@return
		この列が駅時刻(着・発両方を含む)なら true を返します。
	*/
	bool isEkiJikoku()const
	{	return ( m_eColumnType == ColumnType_Ekijikoku_Chaku 
				|| m_eColumnType == ColumnType_Ekijikoku_Hatsu ) ; }

	/**
	@return
		列の種類が
		ColumnType_Ressyabangou(列車番号)～ColumnType_Gou(「号」表示) です。
	*/
	bool isRessyaProp()const
	{
		return(  
			(int)CdYColSpec::ColumnType_Ressyabangou 
				<= (int)m_eColumnType && 
			(int)m_eColumnType 
				<= (int)CdYColSpec::ColumnType_Gou ) ;
	}

	/**
		値を設定します。
	@param eColumnType 
		Y列の種類 
	@param iEkiOrder 
		駅Order。
		m_eColumnType が ColumnType_Ekijikoku_Chaku,
		ColumnType_Ekijikoku_Hatsu の場合にのみ有効です。
		その他の場合は意味を持ちません。
	*/
	void set( 
		EColumnType eColumnType , 
		int iEkiOrder )
	{
		m_eColumnType = eColumnType ;
		m_iEkiOrder = iEkiOrder ;
	}


	bool isNull()const{	return m_eColumnType == ColumnType_NULL ;};
	/* 
		this をNULL状態にします。
	*/
	void setNull(){	*this = CdYColSpec() ;};	

	/**
		他のオブジェクトとの間で、属性が同一か否かを判定します。
	@param value
		比較対象を指定してください。
	@return
		属性が同一であれば true 
	*/
	bool isEqualTo( const CdYColSpec& value )const
	{
		bool bRv = false ;
		if ( m_eColumnType == value.m_eColumnType )
		{
			//	列が着時刻・発時刻の場合は、
			//	Y列の種類と駅Orderの一致で、一致とみなします。
			if ( m_eColumnType == ColumnType_Ekijikoku_Chaku ||
				m_eColumnType == ColumnType_Ekijikoku_Hatsu )
			{
				if ( m_iEkiOrder == value.m_iEkiOrder )
				{
					bRv = true ;
				}
			}
			else
			{
				//	列が着時刻・発時刻以外なら、、
				//	駅Order は関係ありません。
				bRv = true ;
			}
		}
		return bRv ;
	}
	bool operator==(const CdYColSpec& value )const
	{	return isEqualTo( value ) ;}
	bool operator!=(const CdYColSpec& value )const
	{	return !isEqualTo( value ) ;}
};

} } //namespace JikokuhyouColSpec namespace ViewJikokuhyou

#endif /*ViewJikokuhyou_CdYColSpec_h*/
