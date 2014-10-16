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
//	CentDedDgrRessyasenCont.h
//	$Id: CentDedDgrRessyasenCont.h 94 2012-09-29 12:11:37Z okm $
// ****************************************************************
*/
#ifndef  CentDedDgrRessyasenCont_h
#define  CentDedDgrRessyasenCont_h
/** @file */
#include "Mu\CMuiCopied.h"
#include "entDgr\CentDedDgrRessyasen.h"
#include "entDgr\CentDedDgrEkiCont.h"

namespace entDgr{

class CentDedDgrRessya ;

// ****************************************************************
//	CentDedDgrRessyasenCont
// ****************************************************************
/**
@brief
	『ダイヤグラムエンティティクラス群』の
	『列車線』クラス CentDedDgrRessyasen を保持するコンテナです。
	
	このクラスは、『列車線コンテナ』 (CentDedDgrRessyasenCont) に
	包含されます。多重度は、
	
	『列車』 (CentDedDgrRessya):『列車線コンテナ』CentDedDgrRessyasenCont
	=1:1

	『列車線コンテナ』CentDedDgrRessyasenCont :『列車線』CentDedDgrRessyasen 
	=1:（0以上複数）
	
	となります。
	
	また、このクラスは Mu<CentDedDgrEkiJikoku> と関連を持ちます。
	このコンテナに列車線を追加すると、関連する
	Mu<CentDedDgrEkiJikoku> 内の CentDedDgrEkiJikoku::m_iDgrXZahyouRessyasen
	に属性が設定されます。
*/
class CentDedDgrRessyasenCont : public CMuiCopied<CentDedDgrRessyasen>
{
public:
	typedef CMuiCopied<CentDedDgrRessyasen>	super ;
private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
		この列車線コンテナに対応する駅コンテナ。
		このオブジェクトの破棄の責務はクラスユーザーにあります。
		このオブジェクトは、thisが生存する間は生存しなくてはなりません。
	*/
	const CentDedDgrEkiCont*	m_pCentDedDgrEkiCont ;

	/**
		このオブジェクトを保持する列車オブジェクト。
		このオブジェクトの破棄の責務はクラスユーザーにあります。
		このオブジェクトは、thisが生存する間は生存しなくてはなりません。
	*/
	CentDedDgrRessya* m_pCentDedDgrRessya ;

	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CentDedDgrRessyasenCont( 
		//const const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki , 
		const CentDedDgrEkiCont*	pCentDedDgrEkiCont ,
		CentDedDgrRessya* pCentDedDgrRessya ) ;

protected:
	// --------------------------------
	///@name 下請関数
	// --------------------------------
	///@{
	/**
		iEkiOrderBegin , iEkiOrderEnd の間にある
		CentDedDgrEkiJikoku の
		CentDedDgrEkiJikoku::m_iDgrXPosRessyasen に、
		「iEkiOrderBegin と iEkiOrderEnd を結ぶ直線」と駅の交点の DgrXPos を設定します。
	@param iEkiOrderBegin [in]
		線の起点の 駅Order。
	@param iEkiOrderEnd [in]
		線の終点の 駅Order。
	@return 
		成功したら 0以上、エラーなら負の数
		-	0 ;	//	成功
		-	-1 ;	//	iEkiOrderBegin にX座標(m_iDgrXChaku,m_iDgrXHatsuのいずれか)がありません。
		-	-2 ;	//	iEkiOrderEnd にX座標(m_iDgrXChaku,m_iDgrXHatsuのいずれか)がありません。
	*/
	void setDgrXPosRessyasen( 
		int iEkiOrderBegin ,  
		int iEkiOrderEnd  ) ;

	/**
		iEkiOrderBegin , iEkiOrderEnd の間にある
		CentDedDgrEkiJikoku の
		CentDedDgrEkiJikoku::m_iDgrXPosRessyasen を 
		INT_MIN にリセットします。

		iEkiOrderBegin と、 iEkiOrderEnd の
		CentDedDgrEkiJikoku::m_iDgrXPosRessyasen は更新されません。
	@param iEkiOrderBegin [in]
		処理対象の最初の駅時刻。
	@param iEkiOrderEnd [in]
		処理対象の終端の駅時刻。
		
	*/
	void clearDgrXPosRessyasen( 
		int iEkiOrderBegin , 
		int iEkiOrderEnd ) ;

	///@}

public:
	// ********************************
	///@name Mui
	// ********************************
	///@{
	/**
	 	コンテナ内の、インデクスで指定された場所に、
	 	要素のコピーを追加します。
	 @param element [in]
	 	要素を指定してください。
	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 以下です。
	 	０は、先頭・size()なら末尾への追加になります。
		但し、INT_MAX は、末尾を指定したものとみなします。
	 @return
	 	0以上は成功、負の数はエラーです
	*/
	virtual int insert( const CentDedDgrRessyasen& element , int iIndex = INT_MAX ) ;
	
	/**
	 	コンテナ内の、インデクスで指定された場所の
	 	要素を削除します。
	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 未満です。
	 	但し、INT_MAX は、末尾を指定したものとみなします。
	 @param iSize [in]
	 	削除する要素の数を指定してください。
	 	但し、INT_MAX は、 iIndex から末尾までを表します。
	 @attention
		iIndex と iSize の両方を INT_MAX にすることはできません。
	 @return
	 	0以上は成功、負の数はエラーです
	*/
	virtual int erase( int iIndex  , int iSize = 1 ) ;
	
	/**
	 	コンテナ内の、インデクスで指定された場所に、
	 	要素を上書きします。
	 @param element [in]
	 	要素を指定してください。
	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 未満です。
		但し、INT_MAX は、末尾を指定したものとみなします。
	 @return
	 	0以上は成功、負の数はエラーです
	*/
	virtual int set( const CentDedDgrRessyasen& element , int iIndex ) ;
	///@}
public:
	// ********************************
	///@name CentDedDgrRessyasenCont::関連
	// ********************************
	///@{
	const CentDedDgrEkiCont*	getCentDedDgrEkiCont()const ;
	CentDedDgrRessya* getCentDedDgrRessya() ;
	///@}

};

} //namespace entDgr

#endif /*CentDedDgrRessyasenCont_h*/
