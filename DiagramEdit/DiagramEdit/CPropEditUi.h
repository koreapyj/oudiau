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
//	$Id: CPropEditUi.h 197 2014-08-02 07:03:11Z okm $
// ****************************************************************

/** @file */
#ifndef  CPropEditUi_h
#define  CPropEditUi_h
#pragma once


	


/**
@brief
  プロパティ編集を行うUIの処理のフレームワークです。
  
 このクラスでは、以下の要素を扱います。
 
 - Target : 編集対象のプロパティを保持する変数へのポインタ 
 - UiData : ユーザーインターフェース(編集画面)の表示内容・
   入力内容を保持するメンバ変数
 - UiControl : 画面への表示・ユーザーの入力を受け取るオブジェクト
   (例:ダイアログボックス・およびダイアログボックス上のテキストボックス・
   チェックボックス) 


<H2>
【具象クラスの作成】
</H2>
　このクラスは、抽象クラスのクラステンプレートです。
　クラスユーザーは、テンプレートパラメータでテンプレートを具体化したあと、
このクラスを継承した具象クラス(派生クラス)を定義して、それを使用することに
なります。


<H3>
(1)UiDataの構造体を定義
</H3>

　クラスユーザーは、 UiData を保持する構造体を定義してください。
　その上で、UiDataの構造体を、このクラスのテンプレートパラメータに
渡してください。

<H3>
(2)派生クラスを定義し、純粋仮想関数を実装
</H3>

　以下の2段階の派生クラスを定義して、UIを実装してください
(以下2種類のインターフェースを、１段階の派生クラスに実装してもかまいません)。


<H4>
(2.1)『UiData - Target間のデータ転送』
</H4>

　Target のデータと UiData のデータの間のデータ変換・データの妥当性
検証を行います。

　この派生クラスでは、以下の仮想関数を実装してください。
　
  - UiDataFromTarget() ;
  - adjustUiData() ;
  - UiDataToTarget() ;
  
  また、Target へのポインタを保持するデータメンバを追加してください。
  このデータメンバは、コンストラクタで初期化してください。

　この派生クラスは、UI環境(Windows,MFCなど)には依存しません。このため、
自動単体テストを実装することができます。
　但し、この派生クラスからさらに、テスト環境に合わせた派生クラスを
定義して、『UiData - UiControl 間のデータ転送』仮想関数を実装する
必要はあります。


<H4>
(2.2)『UiData - UiControl 間のデータ転送』
</H4>

　この派生クラスでは、UiData と UiControl の間のデータ変換を行います。
以下の仮想関数を実装してください。

 - UiDataToUiControl()
 - UiDataFromUiControl()
 - setFocus()
 - showError()

　データの妥当性検証・エラーチェックなどは、なるべく
(2.1)『UiData - Target間のデータ転送』に実装するべきです。



<H2>
【使い方】
</H2>

(1) このクラスは抽象クラスの、クラステンプレートです。
 クラスユーザーは、このクラスの具象クラスを定義してください。
 
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



@param T_UIDATA [in]
	UiData を保持する構造体を定義し、その構造体を指定してください。
*/
template< class T_UIDATA >
class CPropEditUi
{
public:
	// ********************************
	//	CPropEditUi - インナータイプ
	// ********************************
	/**
	　UiData の内容に正しくない値があった場合の動作を指定します。
	*/
	enum EShowError
	{
		/**
		エラー表示を行わない。

		applyUiChange() , applyUiDataChange() で、EShowError を指定しなかった場合の
		既定値です。
		*/
		EShowError_None , 
		/**
		前回の adjustUiData から変更された値であれば、ShowError()でエラー表示を行う。

		*/
		EShowError_Changed,
		/**
		すべての値について、エラー表示を行う。

		endEdit() では、この動作になります。
		*/
		EShowError_All , 	
	};

	/** 
	UIDATA の型 。テンプレートパラメータで決まります。
	派生クラスでテンプレートパラメータを参照するためには、
	このtypedef が必要です。
	*/
	typedef	T_UIDATA 	UIDATA ;

public:
	// ********************************
	///@name CPropEditUi - 包含
	// ********************************
	///@{
	/**
	UiData(ユーザーインターフェース(編集画面)の表示内容・
	入力内容を保持するメンバ変数)。
	*/
	UIDATA	m_UiData ;

	///@}
private:
	// ================================
	///@name CPropEditUi - 内部データ
	// ================================
	///@{

	/**
	UiData の、編集開始直後(beginEdit()時)の値を保持します。
	UiDataToTarget() では、この値と m_UiData を比較することによって、
	「ユーザーによって変更された値」を見分けることができます。
	m_UiDataOnLastAdjust と m_UiData とで値が異なっている値は
	ユーザー操作によって変更された値となります。
	*/
	UIDATA	m_UiDataOnBeginEdit ;

	/**
	UiData の、前回 adjustUiData() 時の値を保持します。
	adjustUiData() では、この値と m_UiData を比較することによって、
	「ユーザーによって変更された値」を見分けることができます。
	m_UiDataOnLastAdjust と m_UiData とで値が異なっている値は
	ユーザー操作によって変更された値となります。
	*/
	UIDATA	m_UiDataOnLastAdjust ;

	///@}

protected:
	// ================================
	///@name CPropEditUi - 内部データ
	// ================================
	///@{
	const UIDATA& getUiDataOnBeginEdit()const
	{	return m_UiDataOnBeginEdit ;}
	///@}

protected:
	// ================================
	///@name adjustUiData() の下請関数
	// ================================
	///@{

	/**
	 adjustUiData 内でエラーを検出したときに、エラー表示を行うべきか否かを
	判定する関数です。

	@param eShowError [in]
		adjustUiData() の引数 eShowError を指定してください。
	@param bUiDataIsChanged [in]
		エラーを検出した UiData が変更されているか否かを指定してください。
		(例: UIDATA のメンバ strName でエラーを検出したときには、
		この引数に (m_UiData.strName != aUiDataPrev.strName )
		を指定してください。
	@return
		- true: エラー表示を行うべきです。
		- false: エラー表示を行うべきではありません。
		
	 この関数の戻り値は、以下のルールに従います。
	 - eShowError== CPropEditUi::EShowError_All の場合は、常にtrueを返します。
	 - eShowError== CPropEditUi::EShowError_Changed の場合は、
		bUiDataIsChanged の結果を返します。
	 - eShowError== CPropEditUi::EShowError_None の場合は、常にfalseを返します。
	*/
	static bool adjustUiData_isShowErrorRequired( 
		EShowError eShowError , 
		bool bUiDataIsChanged )
	{
		bool bRv = false ;
		if ( eShowError == EShowError_All )
		{
			bRv = true ;
		}
		else if ( eShowError== EShowError_Changed )
		{
			bRv = bUiDataIsChanged ;
		}
		return bRv ;
	}
protected:
	// ================================
	///@name CPropEditUi - UiData-Target間のデータ転送
	// ================================
	///@{
	/**
	  Targetの値を読み込み、UiData に反映します。
	*/
	virtual void UiDataFromTarget() = 0 ;
	
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
		成功したら0以上、UiDataに妥当性異常の値があれば負の数です。
		詳細な値は、派生クラスに依存します。
		
	*/
	virtual int adjustUiData( const UIDATA& aUiDataPrev , EShowError eShowError ) = 0 ;
	
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
	virtual int UiDataToTarget( const UIDATA& aUiDataPrev ) = 0 ;
	
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
	CPropEditUi( )
	{
	}
	virtual ~CPropEditUi(){}
	
	// ********************************
	///@name CPropEditUi - 操作
	// ********************************
	///@{
	/**
	  編集操作を開始します。

	(1)　UiDataFromTarget() で、Target の値を UiData に反映します。
	
	(2)　adjustUiData() で、UiData の正規化・エラーチェックを行います。

	(3)　UiDataToUiControl() で、 UiData を UiControl に反映します。
	*/
	void beginEdit() 
	{
		UiDataFromTarget() ;
		m_UiDataOnBeginEdit = m_UiData ;
		m_UiDataOnLastAdjust = m_UiData ;

		adjustUiData( m_UiDataOnLastAdjust , EShowError_None ) ;
		m_UiDataOnLastAdjust = m_UiData ;

		UiDataToUiControl() ;
	}

	/**
	 プロパティ編集実行中、 UI上でプロパティが編集されたときに
	呼び出してください。対応する処理を行います。

	 applyUiChange() は、UiDataFromUi() を呼び出して、変更されたプロパティの値を
	 UiData に反映させた後、adjustUiData() で、プロパティの値の正規化・
	エラーチェックを実施します。
	@param eShowError [in]
	　UiData の内容に正しくない値があった場合の動作を指定します。
	 省略した場合の既定値は、EShowError_None です。
	@param iOffsetofUiDataMember [in]
		-1 なら、すべての UiControl のデータの変更をを、
		UiData に反映します。@n
		特定の UiControl への変更内容を UiData に
		反映したい場合は、
		UiControlの内容を反映するデータメンバを指定してください。
		UiData内の対象となるデータメンバの、
		構造体の先頭アドレスからのオフセットを
		指定してください。
		(例:列車番号をに設定する場合は、
		offsetof(UIDATA,strRessyabangou ) )
	@return
		成功したら0以上、エラーなら負の数です。
	*/
	int applyUiChange( EShowError eShowError , int iOffsetofUiDataMember  ) 
	{
		int iRv = 0 ; 
		if ( iRv >= 0 )
		{
			iRv = UiDataFromUiControl( iOffsetofUiDataMember ) ;
		}
		if ( iRv >= 0 )
		{
			iRv = adjustUiData( m_UiDataOnLastAdjust , eShowError ) ;
			m_UiDataOnLastAdjust = m_UiData ;
		}
		if ( iRv >= 0 )
		{
			UiDataToUiControl() ;
		}
		return iRv ;
	}
	
	int applyUiChange( int iOffsetofUiDataMember ) 
	{	return applyUiChange( EShowError_None , iOffsetofUiDataMember  ) ; }


	/**
	 プロパティ編集実行中、 ユーザーの編集操作の結果を m_UiData に
	書き込んだときに呼び出してください。対応する処理を行います。

	　applyUiDataChange() は、adjustUiData() で、UiData の正規化・エラーチェックを
	実施します。
	@param eShowError [in]
	　UiData の内容に正しくない値があった場合の動作を指定します。
	@return
		成功したら0以上、エラーなら負の数です。
	*/
	int applyUiDataChange( EShowError eShowError ) 
	{
		int iRv = 0 ; 
		if ( iRv >= 0 )
		{
			iRv = adjustUiData( m_UiDataOnLastAdjust , eShowError ) ;
			m_UiDataOnLastAdjust = m_UiData ;
		}
		if ( iRv >= 0 )
		{
			UiDataToUiControl() ;
		}
		return iRv ;
	}
	
	int applyUiDataChange( ) 
	{	return applyUiDataChange( EShowError_None ) ; }

	/**
	 プロパティ編集が完了したときに呼び出してください。
	対応する処理を行います。

	(1)　UiDataFromUiControl() で、UiControl の値を UiData に反映します。
	
	(2)　adjustUiData() で、UiData の正規化・エラーチェックを行います。

	(3)　UiData にエラーがなければ、UiData を Target に反映し、0以上を
	返します。この時点で、プロパティの編集は終了となります。
	　(MFCによるモーダルダイアログを使用している場合は、 super::OnOK() を呼び出して
	ダイアログボックスを終了してください)

	　endEdit() は、UiDataにエラーがある場合は、 setFocus() でエラーのあった
	項目のUIにフォーカスを移動させて、shouError() でエラーメッセージの表示を
	行います。クラスユーザーは、この後も、プロパティの編集を継続します。

	@return
		成功したら0以上、エラーなら負の数です。

	*/
	int endEdit() 
	{
		int iRv = 0 ; 
		if ( iRv >= 0 )
		{
			iRv = UiDataFromUiControl( -1 ) ;
		}
		if ( iRv >= 0 )
		{
			iRv = adjustUiData( m_UiDataOnLastAdjust , EShowError_All ) ;
			m_UiDataOnLastAdjust = m_UiData ;
		}
		if ( iRv >= 0 )
		{
			iRv = UiDataToTarget( m_UiDataOnBeginEdit ) ;
		}
		return iRv ;
	}
	///@}


};




#endif /*CPropEditUi_h*/
