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
#if !defined(AFX_CDLGRESSYAPROP_H__F050E857_4156_4A3E_A851_A5094C83E766__INCLUDED_)
#define AFX_CDLGRESSYAPROP_H__F050E857_4156_4A3E_A851_A5094C83E766__INCLUDED_
/** @file */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgRessyaProp.h : ヘッダー ファイル
//
#include "entDed\CentDedRessya.h"
#include "OuDlg/CKeyinputSenderToModalDlg.h"
#include "resource.h"
#include "ViewJikokuhyou\CPropEditUi_Ressya.h"

namespace ViewJikokuhyou{
	using namespace OuMfc::OuDlg;

/////////////////////////////////////////////////////////////////////////////
// CDlgRessyaProp ダイアログ

/**
@brief
【概要】
  列車のプロパティダイアログです
 */
class CDlgRessyaProp : public CDialog
{
private:
	// ================================================================
	//	CDlgRessyaProp::CPropEditUiInternal
	// ================================================================
	/**
	@brief 
		時刻表のプロパティ編集を行うクラスです。
	*/
	class CPropEditUiInternal : public CPropEditUi_Ressya
	{
	protected:
		// ================================
		///@name UIとのインターフェース
		// ================================
		///@{
		/**
			UiData を、UiControlに反映します。
		*/
		virtual void UiDataToUiControl() ;

		/**
			UiDataに、UiControlの内容を反映します。
			
		@param bShowError [in]
			- true: 妥当性検証を行い、場合によってはエラーを表示します。
			- false: エラー表示は行いません。
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
		virtual int UiDataFromUiControl( int iOffsetofUiDataMember ) ;
		
		
		/**
			プロパティ編集のUIに、フォーカスを設定します。
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
		virtual void setFocus( int iOffsetofUiDataMember ) ;
		
		/**
			エラーメッセージを表示します。
		@param lpszError [in]
			エラーメッセージを指定してください。
			これは、this.ERROR_* のいずれかとなります。
		*/
		virtual void showError( const wchar_t* const lpszError ) ;
		
		
		///@}
	public:
		// ********************************
		//	コンストラクタ
		// ********************************
		/**
		@param pTarget [in]
			編集対象。コンストラクタで決まります。
			列車を格納したコンテナです。
		@param iRessyasyubetsu [in]
			列車種別の数。コンストラクタで決まります。
		*/
		CPropEditUiInternal( Mu<CentDedRessya*>* pTarget , int iRessyasyubetsu ) ;
		
	} m_PropEditUiInternal ;
	friend class CPropEditUiInternal ;

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
	 親ウインドウへのキー入力を契機に ModalDialog を開く場合、
	モーダルダイアログの特定のエディットコントロールに、
	キー入力メッセージ（ WM_KEYDOWN , WM_KEYUP ）を転送します。
	
	  このオブジェクトの破棄の責務は、クラスユーザー（『転送元ウインドウ』）
	にあります。
	このオブジェクトは、 this より長く生存しなくてはなりません。
	不要であれば NULL でもかまいません。
	コンストラクタで決まります。
	 */
	CKeyinputSenderToModalDlg*	m_pCKeyinputSenderToModalDlg ;
	///@}
private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	
	/**
	  編集開始時のフォーカス位置。

	  コンストラクタで決まります。

	- 0	;	//	空行
	- 1	;	//	列車番号
	- 2	;	//	列車種別
	- 3	;	//	列車名
	- 4	;	//	号数
	- 5	;	//	備考

	OnShowWindow() でフォーカスを設定します。
	フォーカス設定後は、 -1 に変わります。

	 */
	int m_iFocusItem ;

	

	///@}
protected:
	// --------------------------------
	///@name 下請関数
	// --------------------------------
	///@{
	/**
	　このコンストラクタの iFocusItem の引数を、
	m_PropEditUiInternal のコンストラクタの引数に変換しました。
	*/
	static int FirstFocusItemArgConvert( int iFocusItem ) ;

	///@}
// ********************************
//	CDlgRessyaProp
// ********************************
 public:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	///@}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------


// コンストラクション
public:
	/**
	@param pTarget [in]
		編集対象。コンストラクタで決まります。
		列車を格納したコンテナです。
	@param iRessyasyubetsuCount [in]
		列車種別の数。コンストラクタで決まります。
	@param iFocusItem [in]
		最初にフォーカスを設定する項目を保持します。
		コンストラクタで決まります。
		- 0	;	//	空行
		- 1	;	//	列車番号
		- 2	;	//	列車種別
		- 3	;	//	列車名
		- 4	;	//	号数
		- 5	;	//	備考
	@param pCKeyinputSenderToModalDlg [in]
	    親ウインドウへのキー入力を契機に ModalDialog を開く場合、
	   モーダルダイアログの特定のエディットコントロールに、
	   キー入力メッセージ（ WM_KEYDOWN , WM_KEYUP ）を転送します。
		このオブジェクトの破棄の責務は、クラスユーザー（『転送元ウインドウ』）
		にあります。
		このオブジェクトは、 this より長く生存しなくてはなりません。
		不要であれば NULL でもかまいません。
	@param pParent [in]
		親ウインドウオブジェクトを指定してください。
	*/
	CDlgRessyaProp(
		Mu<CentDedRessya*>* pTarget ,
		int iFocusItem ,
		CKeyinputSenderToModalDlg*	pCKeyinputSenderToModalDlg ,
		CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgRessyaProp)
	enum { IDD = IDD_RessyaProp };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgRessyaProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgRessyaProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	afx_msg void OnCHECKIsNull();
	afx_msg void OnEnKillfocusEditRessyabangou();
	afx_msg void OnCbnSelchangeComboRessyasyubetsu();
	afx_msg void OnEnKillfocusEditRessyamei();
	afx_msg void OnEnKillfocusEditGousuu();
	afx_msg void OnEnKillfocusEditBikou();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

} //namespace ViewJikokuhyou

#endif // !defined(AFX_CDLGRESSYAPROP_H__F050E857_4156_4A3E_A851_A5094C83E766__INCLUDED_)
