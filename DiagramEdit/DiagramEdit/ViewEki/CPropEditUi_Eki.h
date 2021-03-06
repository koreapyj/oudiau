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
//	$Id: CPropEditUi_Eki.h 179 2014-05-05 13:50:33Z okm $
// ****************************************************************

/** @file */
#ifndef  CPropEditUi_Eki_h
#define  CPropEditUi_Eki_h
#include <string>
#include "CPropEditUi.h"
#include "entDed\CentDedEkiCont.h"

namespace ViewEki {

	using namespace std ;
	using namespace entDed ;

/**
@brief
	CPropEditUi_Eki で編集する UIDATA 構造体です
*/
struct UIData_Eki
{
	/** 駅名 */
	wstring strEkimei ;
	
	/** 駅時刻形式 
	-	0以上: CentDedEki::EEkijikokukeisiki 
	-	-1 : 不定
	*/
	int iEkijikokukeisiki ;
	
	/** 駅規模 
	-	0以上: CentDedEki::EEkikibo
	-	-1 : 不定
	*/
	int iEkikibo ;

	/** 境界線あり 
	-	1: 境界線あり
	-	0: 境界線なし
	-	-1: 不定
	*/
	int  iKyoukaisen ;

	/** ダイヤグラム列車情報表示（下り） 
	- 0以上: CentDedEki::EDiagramRessyajouhouHyouji 
	-	-1: 不定
	*/
	int iDiagramRessyajouhouHyoujiKudari ;

	/** ダイヤグラム列車情報表示（上り） 
	- 0以上: CentDedEki::EDiagramRessyajouhouHyouji 
	-	-1: 不定
	*/
	int iDiagramRessyajouhouHyoujiNobori ;

	/**
		[駅時刻を駅時刻形式で正規化]の設定です。
	*/
	bool bAdjustByEkijikokukeisiki ;
};



/**
@brief
  駅プロパティの編集を行うクラスです。
  
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


<H2>
【使い方】
</H2>

(1) このクラスは抽象クラスです。
 クラスユーザーは、このクラスの具象クラスを定義してください。
 派生クラスで『UiData - UiControl 間のデータ転送』仮想関数を実装してください。
 
(2) プロパティ編集開始時に、具象クラスのインスタンスを生成してください。
 コンストラクタには、Target(編集対象のプロパティを保持する変数へのポインタ)
を指定してください。


(3) プロパティ編集開始時には、 beginEdit を呼び出してください。
(MFCによるモーダルダイアログを使用している場合は、 OnInitDialog() から
beginEdit() を呼び出してください。)
　beginEdit() は、以下の処理を行います。

-# UiDataFromTarget() で Target の内容を UiData に反映します。
-# UiDataToUiControl() で、UiDataの内容を UiControl に表示します。

(4) プロパティ編集実行中、 UiControl 上でプロパティが編集された場合は、以下のいずれかを
実行してください。

(4.1) applyUiChange() を呼び出す

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

(4.2) プロパティを UiData に書き込んでから、 applyUiDataChange() を呼び出す

　編集されたのプロパティの値をがUIに保持されず、 UiDataFromUiControlによって
取得できないな場合は、こちらの方法を使用してください。
　このような例としては、モーダルダイアログによってプロパティを編集する場合が
当てはまります。
　applyUiDataChange() は、adjustUiData() で、UiData の正規化・エラーチェックを
実施します。

(5) プロパティ編集が完了したときに場合は、endEdit() を呼び出してください
　(MFCによるモーダルダイアログを使用している場合は、 OnOK() から呼び出してください)。
　endEdit()は、UiDataFromUiControl() でコントロールの入力内容を取得したあと、
adjustUiData() を呼び出して、プロパティの値の正規化・エラーチェックを行います。

　endEdit()は、プロパティにエラーがなければ、UiDataToTarget() で、
UiData の内容を Target に反映し、0以上を返します。この時点で、プロパティの編集は
終了となります。
　(MFCによるモーダルダイアログを使用している場合は、 super::OnOK() を呼び出して
ダイアログボックスを終了してください)

　endEdit() は、プロパティにエラーがある場合は、 setFocus() でエラーのあった
項目のUIにフォーカスを移動させて、showError() でエラーメッセージの表示を
行います。クラスユーザーは、この後も、プロパティの編集を継続します。


*/
class CPropEditUi_Eki : public CPropEditUi< UIData_Eki >
{
public:
	// ********************************
	///@name エラーメッセージ
	// ********************************
	///@{
	/// 駅名が長すぎます
	static const wchar_t* const ERRMSG_EKIMEI_TOO_LONG ;
	///@}
	

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。
	*/
	Mu<CentDedEki*>* m_pTarget ;

	/**
		Target(編集対象のプロパティを保持する変数へのポインタ)。
		[駅時刻を駅時刻形式で正規化]の設定です。
		コンストラクタで決まります。
	*/
	bool* m_pbAdjustByEkijikokukeisiki ;
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
	@param pTarget [in]
		ターゲットオブジェクト１つを指定してください。
	*/
	static void UiDataFromTarget( 
		UIDATA* pUiData , 
		const CentDedEki* pTarget ) ;

	/**
		Target1つに、UiData の変化点を反映します。
	@param aUiDataPrev [in]
		変更前の UiData を指定してください。
	@param aUiDataModified [in]
		変更後の UiData を指定してください。
	@param pTarget [in,out]
		この関数はこのターゲットオブジェクトに、
		aUiDataModified の内容を反映します。
		但し、aUiDataPrev と aUiDataModified とで値が等しい
		属性は変更しません。
	@return
		-	0: Targetへの書き込みに成功しました。
		-	-11 ;		//	着時刻が解釈できません。
		-	-12 ;		//	発時刻が解釈できません。
	*/
	static int UiDataToTarget( 
		const UIDATA& aUiDataPrev , 
		const UIDATA& aUiDataModified , 
		CentDedEki* pTarget  ) ;

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
		(例:UIDATAのメンバstrNumber の内容を反映する場合は、
		offsetof(UIDATA,strNumber ) を指定してください。)
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
		(例:フォーカスを、UIDATAのメンバstrNumber のUiControl に設定
		する場合は、 offsetof(UIDATA,strNumber ) を指定してください。)
	@return
		成功したら0以上、エラーなら負の数です。
		-	-1; パラメータが正しくありません。
	*/
	virtual void setFocus( int iOffsetofUiDataMember ) = 0 ;
	
	/**
	 エラーメッセージを表示します。
	@param strError [in]
		エラーメッセージを指定してください。
		
		strError は、最終的にUiControlに表示する文字列でなくてもかまいません。
		strError には何らかのIDを指定するようにして、 showError() で実際に
		UiControl に表示する文字列を導出することもできます。
		(例:Windowsの場合は、showError() で、文字列リソースに格納された文字列へ
		変換することをお勧めします)
	*/
	virtual void showError( const wchar_t* const strError ) = 0 ;
	
	
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	@param pTarget [in,out]
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。
	@param pbAdjustBuEkijikokukeisiki [in,out]
		編集対象。コンストラクタで決まります。
		[駅時刻を駅時刻形式で正規化]です。
	*/
	CPropEditUi_Eki( Mu<CentDedEki*>* pTarget ,
		bool* pbAdjustBuEkijikokukeisiki );
	
};

} //namespace ViewEki 



#endif /*CPropEditUi_Eki_h*/
