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
//	CWndDcdGrid2_CSelect.h
//$Id: CWndDcdGrid2_CSelect.h 94 2012-09-29 12:11:37Z okm $
// ****************************************************************
*/
/** @file */
#ifndef  CWndDcdGrid2_CSelect_h
#define  CWndDcdGrid2_CSelect_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
@file
このヘッダファイルを単体でインクルードすることはできません。
代わりに、 CWndDcdGrid.h をインクルードしてください。

このヘッダファイルは、CWndDcdGrid.h の末尾でインクルードしています。
このため、このクラスから CWndDcdGrid.h をインクルードすることはできません。
*/

#ifndef DcDraw_DcdGrid_WndDcdGrid_CWndDcdGrid2_CWndDcdGrid2_H
#error require to include "CWndDcdGrid.h"
#endif //DcDraw_DcdGrid_WndDcdGrid_CWndDcdGrid2_CWndDcdGrid2_H

namespace DcDrawLib{
namespace DcdGrid{
namespace WndDcdGrid2{

// ----------------------------------------------------------------
//	CWndDcdGrid2::CSelect
// ----------------------------------------------------------------
/**
@brief
	CWndDcdGrid2 のセル選択の制御をクラス化したものです。
	
	このクラスは、 CWndDcdGrid2  が内部的に生成するために存在します。
	それ以外の利用価値はありません。
*/
class CWndDcdGrid2::CSelect
{
	friend class CWndDcdGrid2 ;
public:
	// ****************************************************************
	//	CWndDcdGrid2::CSelect::ESelectMode
	// ****************************************************************
	/**
		CWndDcdGrid2のセル選択のモードを表します。
	*/
	enum ESelectMode
	{ 
		SelectMode_NONE , 	///< (デフォルト)選択は不可能です。
		SelectMode_XY , 	///< X列・Y列両方の選択が可能です。
		SelectMode_XColumn , 	///< X列の選択のみ可能です。Y列は常時全域選択となります。
		SelectMode_YColumn ,	///< Y列の選択のみ可能です。X列は常時全域選択となります。
	};

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
		外側の、 CWndDcdGrid2 への関連です。
		このオブジェクトの破棄の責務は、クラスユーザーにあります。
		このオブジェクトは、 this より長く生存しなくてはなりません。
		コンストラクタで決まります。
	 */
	CWndDcdGrid2*	m_pCWndDcdGrid2 ;

	/**
		選択セルに対して、選択マークを描画する
		DcDraw オブジェクトです。
	 */
	Ou<IfDcDraw>	m_pIfDcDrawSelect ;
	///@}

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		CWndDcdGrid2のセル選択のモードを表します。

	*/
	ESelectMode	m_eSelectMode ;

	/**
	  フォーカスセルが移動した場合は、属性 
	  CWndDcdGrid2::CSelect::m_bKeepAnchor(アンカーセルの保持)にしたがって、
	  アンカーセル・選択セルを変更します。

	  フォーカスセルが移動した場合に、アンカーセルを保持するか否かを指定します。
		-false : (デフォルト)  アンカーセルはフォーカスセルに移動させる。@n
			選択セルは「選択なし」とする
		-true: アンカーセルは移動させない。選択セルは、アンカーセルから@n
			フォーカスセルまでの範囲とする。
	*/
	bool m_bKeepAnchor ;



	/**
		選択可能制限範囲。
		単位はセル番号です。

		選択可能な範囲。デフォルトは、X,Yとも Posが 0 、SizeがINT_MAXとなります。
	*/
	CdDcdZoneXy	m_ColumnNumberSelectLimit ;

	/**
		アンカーセル

		ColumnNumberPosXy_NULL() なら、
		アンカーセルが不定であることを示します。
		onUpdate()で更新されます。
		
		m_ColumnNumberAnchorCell が m_ColumnNumberSelectLimit の
		外側になった場合は、強制的にNULLとなります。
	*/
	CdDcdPosXy	m_ColumnNumberAnchorCell;

	/**
		現在の選択範囲

		選択範囲がない場合、この値は
		ColumnNumberZoneXy_NULL()と等しくなります。
		
		onUpdate()で導出されます。
		また、メソッドで指定することもできます。
	*/
	CdDcdZoneXy	m_ColumnNumberSelect ;

	///@}
public:
	// ********************************
	///@name 定数
	// ********************************
	///@{
	/**
	@return
		セルの列番号のNULL値。

		セルの列番号は、
		x,y両方がINT_MINなら、NULLであることを示します。
	*/
	static CdDcdPosXy	ColumnNumberPosXy_NULL()
	{	return CdDcdPosXy( INT_MIN , INT_MIN ) ;};

	/**
	@return
		選択範囲のNULL値。

		m_ColumnNumberSelect がこの値に等しい場合は
		選択範囲がないことを示します。
	*/
	static CdDcdZoneXy	ColumnNumberZoneXy_NULL()
	{	return CdDcdZoneXy( CdDcdZone( 0 , 0 ) , CdDcdZone( 0 , 0 ) );};
	///@}

private:
	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
		フォーカスセルの前回値。
		初期値はNULLを示す
		onUpdate() で、カレントのフォーカスセルの値がコピーされます。
	*/
	CdDcdPosXy	m_ColumnNumberFocus_Old ;


	/**
		現在の画面での選択範囲。
		
		update_updateDisplay()で画面を更新したときに、
		m_ColumnNumberSelect の値がコピーされます。
	*/
	CdDcdZoneXy	m_ColumnNumberSelect_Old ;



protected:
	// --------------------------------
	///@name 下請関数
	// --------------------------------
	///@{

	/**
		列番号に対応した、X・Y列の範囲を
		論理単位(通常はピクセル。クライアント座標)で返します。

		列番号に、一番左・下の列が含まれる場合は、
		その左・下の罫線(グリッド全体の左・下の罫線)は範囲には含めません。
		列番号に一番左・下の列が含まれない場合は、
		範囲の左・下の罫線(列間の罫線)は範囲に含めます。
	*/
	virtual CdDcdZoneXy getColumnZoneOfColumnNumber(
		const CdDcdZoneXy& zonexyColumnNumber ) ;
	///@}
protected:
	// --------------------------------
	///@name CWndDcdGrid2 からの委譲
	// --------------------------------
	///@{
	/**
		update() の下請関数です。
	
		- 属性の補正
		- 属性の変化をCWndDcdGrid2に通知

		を行います。

	【1.属性の補正】

		対象となるのは、以下の属性です。
		
		- m_ColumnNumberSelect 
	
	  １． m_ColumnNumberSelect を m_ColumnNumberSelectLimit の
		内側にします。
	
	  ２． m_eSelectMode が SelectMode_XColumn なら、
		m_ColumnNumberSelect.Y は、 m_ColumnNumberSelectLimitY とします。
		m_eSelectMode が SelectMode_YColumn なら、
		m_ColumnNumberSelect.X は、 m_ColumnNumberSelectLimitX とします。

	 @param bKeepAnchor [in]
		- false; アンカーセルを現在位置に更新します。
		- true ; アンカーセルを更新しません。
	 @return 
		正規化の結果、何らかの値を変化させた場合は真です。
	 */
	bool update_adjustProp() ;

	/**
		update() の下請関数です。

		属性の変化を、画面上に反映します。
		対象となるのは、以下の属性です。
	
		- m_ColumnNumberSelect・・・変更前と変更後のセルを無効化し、
		再描画を行わせます。

		この変化を察知するために、this は以下のメンバ変数に前回値を
		保持しています。
	
		- m_ColumnNumberSelect_Old
		
	 @return 
		何らかの値の変化を画面上に反映させた場合は真です。
	 */
	bool update_updateScreen() ;


	/**
		CWndDcdGrid2 の同一メソッドの委譲を受けます。

	 	描画を要求します。
	 	この関数は、 pIfDcdTarget に、描画を行います。
	 @param pIfDcdTarget  [in]
	 	このオブジェクトに描画を行わせたいDCと領域を指定してください。
	 	CWndDcdGrid2のクライアント領域の IfDcdTarget を指定してください。
	 @return
	 	描画を行った場合は真・この領域への描画ができなかった場合は偽です。
	*/
	virtual bool OnPaint( IfDcdTarget* pIfDcdTarget ) ;

	/**
		CWndDcdGrid2 の同一メソッドの委譲を受けます。

		ウインドウ全域を無効化し、
		再描画を要求します。
		このとき、選択セルの属性の再設定・正規化も行います。
	
	 */
	virtual void InvalidateGrid( ) ;

	/**
		CWndDcdGrid2 の同一メソッドの委譲を受けます。

		選択セルを正規化・再設定します。
	*/
	void OnSize(UINT nType, int cx, int cy);

	/**
		CWndDcdGrid2 の同一メソッドの委譲を受けます。

		このクラスでは、処理はありません。
	*/
	void OnSetFocus(CWnd* pOldWnd);
	/**
		CWndDcdGrid2 の同一メソッドの委譲を受けます。

		このクラスでは、処理はありません。
	*/
	void OnKillFocus(CWnd* pNewWnd);

	///@}
public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	@param pCWndDcdGrid2 [in]
		外側の、 CWndDcdGrid2 への関連です。
		このオブジェクトの破棄の責務は、クラスユーザーにあります。
		このオブジェクトは、 this より長く生存しなくてはなりません。
	@param pIfDcDrawSelect [in]
		選択セルに対して、選択マークを描画する
		DcDraw オブジェクトです。
	 */
	CSelect( CWndDcdGrid2* pCWndDcdGrid2 ,
		Ou<IfDcDraw> pIfDcDrawSelect ) ;
	CSelect( CWndDcdGrid2* pCWndDcdGrid2 ) ;
	virtual ~CSelect() ;
public:
	// ********************************
	///@name CWndDcdGrid::CSelect 関連
	// ********************************
	///@{
	virtual Ou<IfDcDraw>	getIfDcDrawSelect() ;
	virtual void setIfDcDrawSelect( Ou<IfDcDraw> value ) ;
	///@}


	// ********************************
	///@name CWndDcdGrid::CSelect 属性
	// ********************************
	///@{
	ESelectMode	getSelectMode()const ;
	void setSelectMode( ESelectMode	value ) ;

	bool getKeepAnchor() ;
	void setKeepAnchor( bool value ) ;


	CdDcdZoneXy	getColumnNumberSelectLimit()const ;
	void setColumnNumberSelectLimit( const CdDcdZoneXy& value ) ;
	CdDcdPosXy	getColumnNumberAnchorCell();
	CdDcdZoneXy	getColumnNumberSelect()const ;
	void setColumnNumberSelect( const CdDcdZoneXy& value ) ;
	///@}


};

} //namespace WndDcdGrid2
} //namespace DcdGrid
} //namespace DcDrawLib

#endif //CWndDcdGrid2_CSelect_h
