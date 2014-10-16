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
//$Id: DcDrawLib.h 94 2012-09-29 12:11:37Z okm $
#ifndef  DcDrawLib_h
#define  DcDrawLib_h
/**
 @file 
 @brief
	名前空間の関数群・クラス群のすべてをインクルードします。
*/


/**
@brief
  DcDrawモデルを構成するクラス群です。
  DcDrawモデルは、GDIによるグラフィック処理を実現するための
フレームワークです。

  DcDrawモデルでは、次の２つのインターフェースを用いて、グラフィック処理を
実施します。

- IfDcdTarget:
  DcDrawモデルにおける、描画を行う領域を表すオブジェクトのインターフェース
です。このインターフェースは、DCを保持します。
  このインターフェースをサポートするクラスの一例は、 CDcdTargetOnPaint です。
  CDcdTargetOnPaint は、Win32 のウインドウにおいて、 WM_PAINT で渡される
デバイスコンテキストを保持するクラスです。
- IfDcDraw:
  DcDrawモデルにおける、描画処理を表すクラスがサポートするインターフェース
です。
  このインターフェースをサポートするクラスの一例は、 CDcdFillRectangleText
です。このクラスは、背景色つき・枠つきでのテキストの描画を行います。


 IfDcdTarget オブジェクトを IfDcDraw::DcDraw() に渡すと、 IfDcDraw::DcDraw() 
メソッドは、 IfDcdTarget が表す領域にグラフィックの描画を行います。

(例)  WM_PAINT メッセージハンドラで CDcdTargetOnPaint オブジェクトを生成し、
CDcdFillRectangleText::DcDraw() メソッドに渡すことにより、
CDcdFillRectangleText オブジェクトは DC に、背景色つき・枠つきテキストの
描画を行います。

*/
namespace DcDrawLib{
} //namespace DcDrawLib

#include "DcdCd\DcdCd.h"
#include "DcdGrid\DcdGrid.h"
#include "DcDraw\DcDraw.h"
#include "DcDrawMfc\DcDrawMfc.h"
#include "WinUtil\WinUtil.h"


#endif //DcDrawLib_h
