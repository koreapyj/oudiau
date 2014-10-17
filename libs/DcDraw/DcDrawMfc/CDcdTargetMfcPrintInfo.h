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
//	CDcdTargetMfcPrintInfo.h
// ****************************************************************
*/
/** @file */
#ifndef  CDcdTargetMfcPrintInfo_h
#define  CDcdTargetMfcPrintInfo_h

#include <afxext.h>

#include "DcDraw/IfDcdTarget.h"
#include "DcDraw/CGdiCache.h"

namespace DcDrawLib{
	using namespace DcDraw;
namespace DcDrawMfc{


// ****************************************************************
//	CDcdTargetMfcPrintInfo
// ****************************************************************
/**
 * @brief
 *	【概要】
 *	  MFC の DocView モデルでの、印刷/印刷プレビューの描画領域を提供する
 *	クラスです。印刷の場合・印刷プレビューの場合とも、このクラスを
 *	利用することができます。
 *	
 *	  MFCのDocViewアプリケーションでは、CView::OnPrint() のオーバライドで
 *	このオブジェクトを生成することにより、DcDrawモデルによるプリンタへの
 *	描画を行うことができます。
 *	
 *	  このクラスのインスタンスは、CView::OnPrint() のオーバライドの中で
 *	生成し、その関数がリターンするまでに破棄しなくてはなりません。
 *	通常は、自動変数としてインスタンスを生成してください。
 *	
 *	<H4>
 *	【座標系について】
 *	</H4>
 *	
 *	  このクラスは、印刷の情報は、OnPrint() で渡される CDC と CPrintInfo 
 *	から取得します。描画領域（ getZone() で取得できる領域）は、
 *	CPrintInfo::m_rectDraw （ページの描画できる領域）に等しくなります。
 *	
 *	  描画領域の座標値は、印刷の場合も印刷プレビューの場合も、
 *	プリンタの１ドット＝１論理単位となります。
 *	  印刷プレビューの場合、MFCは OnPrint() を呼び出す前に、DCにプリンタの
 *	ピクセルに合わせたマッピングモードが設定されています。
 *	  つまり、プリンタの用紙の左端から右端までのドット数が1000であれば、
 *	印刷プレビュー画面の用紙部分の左端から右端までの論理単位も1000に
 *	調整されています。
 *	
 *	@see CaDcdTargetZoomDisplay 
 *	  このオブジェクトに関連する CaDcdTargetZoomDisplay アダプタクラスの
 *	オブジェクトを生成すると、ディスプレイと同様の座標系で描画を行うことが
 *	できます。
 *	
 *	<H4>
 *	【使い方】
 *	</H4>
 *	
 *	１．  CView::OnPrint() のオーバライドで、このクラスのオブジェクトを
 *	生成してください。
 *	  このクラスのインスタンスは、CView::OnPrint() のオーバライドの中で
 *	生成し、その関数がリターンするまでに破棄しなくてはなりません。
 *	  通常は、自動変数としてインスタンスを生成してください。
 *	
 *	２．  このオブジェクトを IfDcDraw インターフェースに渡して、描画を
 *	行うことができます。
 *	
 */
class CDcdTargetMfcPrintInfo : public IfDcdTarget 
{
// ********************************
///@name 関連
// ********************************
///@{
 private:
	/**
	  	対象となる DC 。
	 	CView::OnPrint() のオーバライドの引数を渡してください。
	 
	 	印刷の場合、
	  @code
	    m_pCPrintInfo->m_bPreview = FALSE
	  	m_pDC->GetSafeHdc() = プリンタのDC
	  	m_pDC->m_hAttribDC = プリンタのDC
	  @endcode
	 	印刷プレビューの場合、
	 
	  @code
	    - m_pCPrintInfo->m_bPreview = TRUE
	  	- m_pDC->GetSafeHdc() = プレビュー画面のDC
	    - m_pDC->m_hAttribDC = プリンタのDC
	  @endcode
	 	となります。
	 
	 	このオブジェクトの破棄の責務は クラスユーザーにあります。
	  	このオブジェクトは、thisより長く生存しなくてはなりません。
	 */
	CDC*			m_pCDC ;
	
	/**
	 * 	  MFC から渡された  CPrintInfo です。
	 *	CView::OnPrint() のオーバライドの引数を渡してください。
	 *	
	 *	  このクラスは、 CPrintInfo の内容を変更しません。
	 *
	 *	このオブジェクトの破棄の責務は クラスユーザーにあります。
	 * 	このオブジェクトは、thisより長く生存しなくてはなりません。
	 */
	const CPrintInfo*	m_pCPrintInfo ;
	
///@}
// ********************************
///@name 属性
// ********************************
///@{
 private:
	/**
	 * 	  描画の必要な領域の座標範囲。
	 *	  描画領域の座標値は、印刷の場合も印刷プレビューの場合も、
	 *	プリンタの１ドット＝１となります。
	 *	
	 *	コンストラクタで決まります。
	 */
	CdDcdZoneXy	m_zonexyZone ;
	
	
///@}
// --------------------------------
///@name	内部データ
// --------------------------------
///@{
 private:
	/**
	 *	GDIオブジェクトの属性と、ハンドルの対照表を保持します。
	 */
	CGdiCache	m_CGdiCache ;
///@}

// ********************************
//	コンストラクタ
// ********************************
 public:
	/**
	 * @aram pCDC [in]
	 * 	対象となる DC 。
	 *	CView::OnPrint() のオーバライドの引数を渡してください。
	 *	このオブジェクトの破棄の責務は クラスユーザーにあります。
	 * 	このオブジェクトは、thisより長く生存しなくてはなりません。
	 * @param pCPrintInfo [in]
	 * 	  MFC から渡された  CPrintInfo です。
	 *	CView::OnPrint() のオーバライドの引数を渡してください。
	 *	  このクラスは、 CPrintInfo の内容を変更しません。\n
	 *	このオブジェクトの破棄の責務は クラスユーザーにあります。
	 * 	このオブジェクトは、thisより長く生存しなくてはなりません。
	 */
	CDcdTargetMfcPrintInfo( 
		CDC*			pCDC ,
		const CPrintInfo*	pCPrintInfo ) ;
	virtual ~CDcdTargetMfcPrintInfo() ; 

// ********************************
///@name	IfDcdTarget
// ********************************
///@{
 public:
	/**
	 * @return
	 * 	描画を行うDCを取得します。
	 * 	このHDCの破棄の責務は、thisにあります。
	 *
	 *	【オーバライド】
	 *
	 *	印刷の場合、この関数が返すのは プリンタのDCです。
	 *	印刷プレビューの場合は、この関数が返すのは、プレビュー画面のDCです。
	 *
	 *	印刷プレビューの場合は、プリンタのDCは getPrinterHdc() で取得できます。
	 */
	virtual HDC	getHdc() ;
	
	/**
	 * @return
	 * 	描画の必要な領域の座標範囲を取得することができます。
	 * 	単位は、論理単位です。
	 */
	virtual CdDcdZoneXy getZone() ;
	
	/**
	 * @return
	 * 	描画が有効な範囲を取得できます。
	 * 	通常は、getZone()と同じ領域となります。
	 * 
	 * 	ウインドウのWM_PAINTによる描画の場合、この関数が返すのは、
	 * 	再描画が必要な領域となります。
	 * 	この領域を無視してもかまいません。ただし、この範囲外への描画は
	 * 	意味がありませんので、この範囲外への描画を抑制するようにすれば、
	 * 	描画処理の効率の改善が期待できます。
	 */
	virtual CdDcdZoneXy getDrawableZone() ;

	/**
	 	CdFontPropオブジェクトの属性をもとに、フォントを生成します
	 @param aCdFontProp [in]
	 	フォント属性を指定してください。
	 @return
		フォントのハンドルを保持する CGdiHFontHolder を返します。
	*/
	virtual Ou<CGdiHFontHolder>	createGdiHFontHolder(  const CdFontProp& aCdFontProp ) ;
	
	/**
	 	CdPenPropオブジェクトの属性をもとに、ペンを生成します
	 @param aCdPenProp [in]
	 	ペン属性を指定してください。
	 @return
		ペンのハンドルを保持する CGdiHPenHolder を返します。
	*/
	virtual  Ou<CGdiHPenHolder>		createGdiHPenHolder(  const CdPenProp& aCdPenProp ) ;

	/**
	 	CdBrushPropオブジェクトの属性をもとに、ブラシを生成します
	 @param aCdBrushProp [in]
	 	ブラシ属性を指定してください。
	 @return
		ブラシのハンドルを保持する CGdiHBrushHolder を返します。
	*/
	virtual Ou<CGdiHBrushHolder>	createGdiHBrushHolder(  const CdBrushProp& aCdBrushProp ) ;


///@}
// ********************************
//	CDcdTargetMfcPrintInfo
// ********************************
 public:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	CDC*			getCDC(){	return m_pCDC ;};
	const CPrintInfo*	getCPrintInfo(){	return m_pCPrintInfo ;};

	/**
	 * @return
	 * 	プリンタのDCを取得します。
	 * 	このHDCの破棄の責務は、thisにあります。
	 *
	 *	印刷の場合も、印刷プレビューの場合も、
	 *	この関数はプリンタのDCを返します。
	 */
	virtual HDC getPrinterHdc() ;
	///@}
	// ********************************
	///@name 操作
	// ********************************
	///@{
	/**
	 *	プリントプレビューなら真です。
	 */
	virtual bool isPreview() ;
	///@}
	// ********************************
	///@name デバッグ用関数
	// ********************************
	///@{
	/**
	 *	CPrintInfo の内容を記述した可読文字列を作成します。
	 *	
	 *	この文字列の用途は、デバッグに限られます。
	 * @param pInfo [in]
	 *	対象となる CPrintInfo オブジェクトを指定してください。
	 * @return 
	 *	CPrintInfo の内容を記述した可読文字列。
	 *	
	 */
	static std::wstring stringOf( CPrintInfo* pInfo ) ;
	///@}

};

} //namespace DcDrawMfc
} //namespace DcDrawLib

#endif /*CDcdTargetMfcPrintInfo_h*/
