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
//	$Id: CPropEditUi_Ressya.h 179 2014-05-05 13:50:33Z okm $
// ****************************************************************

/** @file */
#ifndef  ViewJikokuhyou_CPropEditUi_Ressya_h
#define  ViewJikokuhyou_CPropEditUi_Ressya_h
#pragma once

#include "entDed\CentDedRessyaCont.h"
#include "Mu\Mu.h"
#include <string>
#include "CPropEditUi.h"

namespace ViewJikokuhyou{
	using namespace entDed;
	using namespace OuLib::NsMu ;
	using namespace std ;
	

// ********************************
//	UIDATA_Ressya
// ********************************
/**
	このクラスで編集するプロパティの、編集中の値を保持します。
*/
struct UIDATA_Ressya
{
	/** 
		列車がNullか否かを指定するチェックボックスです。 
		-	1: ON
		-	0: OFF
		-	-1: 中間
	*/
	int iIsNull ;

	/** 列車番号 */
	wstring strRessyabangou ;
	/** strRessyabangou の編集の有効・無効。true なら有効です */
	bool bRessyabangouIsEnable ;

	/** 列車種別のIndex */
	int iRessyasyubetsuIndex ;
	/** iRessyasyubetsuIndex の編集の有効・無効。true なら有効です */
	bool bRessyasyubetsuIndexIsEnable ;

	/** 列車名 */
	wstring strRessyamei ;
	/** strRessyamei の編集の有効・無効。true なら有効です */
	bool bRessyameiIsEnable ;

	/** 号数 */
	wstring strGousuu ;
	/** strGousuu の編集の有効・無効。true なら有効です */
	bool bGousuuIsEnable ;

	/** 備考 */
	wstring strBikou ;
	/** strBikou の編集の有効・無効。true なら有効です */
	bool bBikouIsEnable ;

};
		

/**
@brief
  時刻表のプロパティ編集を行うクラスです。

　このクラスでは、以下の要素を扱います。
 
 - Target : 編集対象のプロパティを保持する変数へのポインタ 
 - UiData : ユーザーインターフェース(編集画面)の表示内容・
   入力内容を保持するメンバ変数
 - UiControl : 画面への表示・ユーザーの入力を受け取るオブジェクト
   (例:ダイアログボックス・およびダイアログボックス上のテキストボックス・
   チェックボックス) 

　このクラスでは、『UiData - Target間のデータ転送』を実装します。

  このクラスは抽象クラスです。
  このクラスは、使用するUI環境(例：Windows,MFC)には依存しません。
　クラスユーザーは、このクラスを継承して、
 『UiData - UiControl 間のデータ転送』の仮想関数に、
 UI環境に依存した処理を実装してください。


【使い方】

(0) このクラスは抽象クラスです。
 クラスユーザーは、このクラスを継承した派生クラスを定義してください。
 その派生クラスで、『UiData - UiControl 間のデータ転送』仮想関数を実装して
ください。

(1) プロパティ編集開始時に、派生クラスのインスタンスを生成してください。
 コンストラクタには、Target(編集対象のプロパティを保持する変数へのポインタ)
を指定してください。
(このクラスでは、列車を格納したコンテナの Mu<CentDedRessyaCont*>* )

(2) プロパティ編集開始時には、 beginEdit を呼び出してください。
(MFCによるモーダルダイアログを使用している場合は、 OnInitDialog() )
　beginEdit() は、以下の処理を行います。

-# UiDataFromTarget() で Target の内容を UiData に反映します。
-# UiDataToUiControl() で、UiDataの内容を UiControl に表示します。

(3) プロパティ編集実行中、 UiControl 上でプロパティが編集された場合は、以下のいずれかを
実行してください。

(3.1) applyUiChange() を呼び出す

　編集されたプロパティの値が UiControl に保持され、UiDataFromUiControl() 
によって取得可能な場合は、こちらの方法を使用してください。
　applyUiChange() は、UiDataFromUiControl() を呼び出して、変更されたプロパティの値を
 UiData に反映させた後、adjustUiData() で、プロパティの値の正規化・
エラーチェックを実施します。
　(MFCによるモーダルダイアログを使用している場合は、 以下の場合に
　この関数を呼び出してください。
　エディットボックスのEN_KILLFOCUS,
　ラジオボタン・チェックボックスのチェックの変更・
　リストボックスの選択変更・
　コンボボックスのEN_KILLFOCUS )

(3.2) プロパティを UiData に書き込んでから、 applyUiDataChange() を呼び出す

　編集されたのプロパティの値をがUIに保持されず、 UiDataFromUiControlによって
取得できないな場合は、こちらの方法を使用してください。
　このような例としては、モーダルダイアログによってプロパティを編集する場合が
当てはまります。
　applyUiDataChange() は、adjustUiData() で、UiData の正規化・エラーチェックを
実施します。

(4) プロパティ編集が完了したときに場合は、endEdit() を呼び出してください
　(MFCによるモーダルダイアログを使用している場合は、 OnOK() から呼び出してください)。
　endEdit()は、プロパティの値の正規化・エラーチェックを行います。

　endEdit()は、プロパティにエラーがなければ、UiData の内容を Target に反映し、0以上を
返します。この時点で、プロパティの編集は終了となります。
　(MFCによるモーダルダイアログを使用している場合は、 super::OnOK() を呼び出して
ダイアログボックスを終了してください)

　endEdit() は、プロパティにエラーがある場合は、 setFocus() でエラーのあった
項目のUIにフォーカスを移動させて、showError() でエラーメッセージの表示を
行います。クラスユーザーは、この後も、プロパティの編集を継続します。

*/
class CPropEditUi_Ressya : public CPropEditUi<UIDATA_Ressya>
{

public:
	// ********************************
	///@name エラーメッセージ
	// ********************************
	///@{
	/// 列車種別が範囲外です。
	static const wchar_t* const ERRMSG_INVALID_RESSYASYUBETSU ;
	///@}

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。

	 　列車を格納したコンテナです。
	*/
	Mu<CentDedRessya*>* m_pTarget ;

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	///@}

	// ================================
	///@name 内部データ
	// ================================
	///@{
	/**
		列車種別の数。コンストラクタで決まります。
	*/
	int m_iRessyasyubetsuCount ;


	///@}
protected:
	// ================================
	///@name 下請関数
	// ================================
	///@{
	/**
	  Target1つの内容を、UiData に反映します。
	@param pUiData [out]
		この関数はこの UiData に、pRessya の内容を書き込みます。Target１つの値
	@param pRessya [in]
		ターゲットオブジェクト１つを指定してください。
	*/
	static void UiDataFromTarget( 
		UIDATA* pUiData , 
		const CentDedRessya* pRessya ) ;
	
	/**
		Target1つに、UIDATA の変化点を反映します。
	@param aUiDataPrev [in]
		変更前の UIDATA を指定してください。
	@param aUiDataModified [in]
		変更後の UIDATA を指定してください。
	@param pRessya [in,out]
		この関数はこのターゲットオブジェクトに、
		aUiDataModified の内容を反映します。
		但し、aUiDataPrev と aUiDataModified とで値が等しい
		属性は変更しません。
	@return
		-	0: Targetへの書き込みに成功しました。
		-	負の数: エラーがありました。
	*/
	static int UiDataToTarget( 
		const UIDATA& aUiDataPrev , 
		const UIDATA& aUiDataModified , 
		CentDedRessya* pRessya ) ;

	///@}

protected:
	// ================================
	///@name CPropEditUi - UiData-Target間のデータ転送
	// ================================
	///@{
	/**
	  Targetの値を読み込み、UiData に反映します。
	*/
	virtual void UiDataFromTarget() ;
	
	/**
	　UiData の正規化・妥当性検証を行います。
	@param aUiDataPrev [in]
		UiData の、前回 adjustUiData() 時の値を保持します。
		adjustUiData() では、この値と m_UiData を比較することによって、
		「ユーザーによって変更された値」を見分けることができます。
		m_UiDataOnLastAdjust と m_UiData とで値が異なっている値は
		ユーザー操作によって変更された値となります。
	@param eShowError [in]
	　UiData の内容に正しくない値があった場合の動作を指定します。
	@return
		成功したら0以上、エラーなら負の数です。
		
	*/
	virtual int adjustUiData( const UIDATA& aUiDataPrev , EShowError eShowError ) ;
	
	/**
	 Target に、UiData の内容を書き込みます。
	@param aUiDataPrev [in]
		UiData の、編集開始直後(beginEdit()時)の値を保持します。
		UiDataToTarget() では、この値と m_UiData を比較することによって、
		「ユーザーによって変更された値」を見分けることができます。
		m_UiDataOnLastAdjust と m_UiData とで値が異なっている値は
		ユーザー操作によって変更された値となります。
	@return
		-	0: Targetへの書き込みに成功しました。
		-	負の数: エラーがありました。
	*/
	virtual int UiDataToTarget( const UIDATA& aUiDataPrev ) ;
	
	///@}
protected:
	// ================================
	///@name CPropEditUi - UiData - UiControl 間のデータ転送
	// ================================
	///@{
	/**
	  UiData を、UiControlに反映します。
	*/
	virtual void UiDataToUiControl() = 0 ;

	/**
	  UiDataに、UiControlの内容を反映します。
	@param iOffsetofUiDataMember [in]
		-1 なら、すべての UiControl のデータを、
		UiData に反映します。@n
		特定の UiControl の内容を UiData に
		反映したい場合は、
		UiControlの内容を反映するデータメンバを指定してください。
		UiData内の対象となるデータメンバの、
		構造体の先頭アドレスからのオフセットを
		指定してください。
		(例:列車番号をに設定する場合は、
		offsetof(UIDATA,strRessyabangou ) )
	@return
		成功したら0以上、エラーなら負の数です。

		(MFCダイアログの場合、bShowError を false にしても、
		MFCによるエラーメッセージ表示が
		実施される場合があります。)
	*/
	virtual int UiDataFromUiControl( int iOffsetofUiDataMember ) = 0 ;
	
	
	/**
	 プロパティ編集のUiControlに、フォーカスを設定します。
	@param iOffsetofUiDataMember [in]
		フォーカスを設定する編集項目を指定してください。
		UiData内の対象となるデータメンバの、構造体の先頭アドレスからのオフセットを
		指定してください。
		(例:フォーカスを列車番号に設定する場合は、
		offsetof(UIDATA,strRessyabangou ) )
	@return
		成功したら0以上、エラーなら負の数です。
		-	-1; パラメータが正しくありません。
	*/
	virtual void setFocus( int iOffsetofUiDataMember ) = 0 ;
	
	/**
	 エラーメッセージを表示します。
	@param strError [in]
		エラーメッセージを指定してください。
		これは、this.ERROR_* のいずれかとなります。
	*/
	virtual void showError( const wchar_t* const strError ) = 0 ;
	
	
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	@param pTarget [in,out]
	 編集対象。コンストラクタで決まります。
	 列車を格納したコンテナです。
	@param iRessyasyubetsuCount [in]
	 列車種別の数。コンストラクタで決まります。
	*/
	CPropEditUi_Ressya( 
		Mu<CentDedRessya*>* pTarget , 
		int iRessyasyubetsuCount  ) ;
	
	

};



} //namespace ViewJikokuhyou

#endif /*ViewJikokuhyou_CPropEditUi_Ressya_h*/
