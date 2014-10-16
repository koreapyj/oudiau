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
//	CWjkState.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "CWjkState.h"
#include "ViewJikokuhyou\WndJikokuhyou\CWndJikokuhyou.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewJikokuhyou{ namespace WndJikokuhyou{

// ****************************************************************
//	CWjkState
// ****************************************************************
	// --------------------------------
	//@name	下請関数
	// --------------------------------
CJikokuhyouDoc*	CWjkState::GetDocument()
{
	return m_pCWndDcdGrid->GetDocument() ;
};
	
ERessyahoukou CWjkState::getRessyahoukou() 
{
	return m_pCWndDcdGrid->getRessyahoukou() ;
};
	
const CentDedDia*	CWjkState::getCentDedDia()
{
	return m_pCWndDcdGrid->getCentDedDia() ;
};
	
const CentDedRessyaCont*
CWjkState::getCentDedRessyaCont()
{
	return m_pCWndDcdGrid->getCentDedRessyaCont() ;	
};


	// ********************************
	//	コンストラクタ
	// ********************************
CWjkState::CWjkState( CWndJikokuhyou*	pCWndDcdGrid ) :
	m_pCWndDcdGrid( pCWndDcdGrid )
{
};
CWjkState::~CWjkState()
{
} ;

	// ********************************
	//	CWjkState
	// ********************************
	// ********************************
	//@name 関連
	// ********************************
CWndJikokuhyou*	CWjkState::getCWndDcdGrid()
{
	return m_pCWndDcdGrid ;
};

	
	// ********************************
	//@name 操作
	// ********************************
int CWjkState::canEnter()
{
	return 0 ;
};

	// ********************************
	//@name CView からの委譲
	// ********************************
void CWjkState::
	OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
};
	// ********************************
	//@name メッセージハンドラ・コマンドハンドラ-CWnd
	// ********************************
void CWjkState::
	OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnKeyDown( nChar, nRepCnt, nFlags);
};
void CWjkState::
	OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnKeyUp(nChar, nRepCnt, nFlags);
};
void CWjkState::
	OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnChar( nChar, nRepCnt, nFlags);
};
void CWjkState::OnWM_IME_STARTCOMPOSITION() 
{
	 m_pCWndDcdGrid->Default();
}

void CWjkState::
	OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnLButtonDblClk( nFlags, point);
};


// --------------------------------
//	Edit
int CWjkState::OnEditCut_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnEditCopy_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
};
int CWjkState::
	OnEditPaste_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
};

int CWjkState::
	OnEditClear_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
};

int CWjkState::
	OnEditPasteEkiJikoku_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnEditSelectAll_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int OnJikokuhyouRessyaProp_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}
int OnJikokuhyouRessyaInsert_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int OnJikokuhyouFocusMoveDown_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int OnJikokuhyouFocusMoveRight_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int OnJikokuhyouEKikanSaisyouSec_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int OnJikokuhyouSort_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouRessyaProp_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
};

int CWjkState::
	OnJikokuhyouRessyaInsert_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
};

int CWjkState::
	OnJikokuhyouFocusMoveDown_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouFocusMoveRight_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouEKikanSaisyouSec_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::OnJikokuhyouSort_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}
int CWjkState::OnJikokuhyouUnify_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouEkijikokuProp_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouJikokuSakujo_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouTsuuka_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouTsuukateisya_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouKeiyunasi_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}







int CWjkState::
	OnJikokuhyouSihatsu_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}
int CWjkState::
	OnJikokuhyouSyuuchaku_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int CWjkState::
	OnJikokuhyouDirect_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}
int CWjkState::
	OnJikokuhyouUndirect_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouRenzoku_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}



int CWjkState::
	OnJikokuhyouEkijikokuInsert_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouEkijikokuErase_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
	OnJikokuhyouModifyEkijikokuCmd_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}
int CWjkState::
	OnJikokuhyouModifyEkijikokuCmdRepeat_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
OnJikokuhyouEkijikokuDec_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}

int CWjkState::
OnJikokuhyouEkijikokuDecNoMove_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int CWjkState::
OnJikokuhyouEkijikokuNext_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int CWjkState::
OnJikokuhyouEkijikokuPrev_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int CWjkState::
OnJikokuhyouEkijikokuInc_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


int CWjkState::
OnJikokuhyouEkijikokuIncNoMove_Process( BOOL bQueryEnable )
{
	return -1 ;	//	このコマンドは選択できません
}


		// --------------------------------
	// ********************************
	//@name	CWndDcdGrid
	// ********************************
void CWjkState::
	OnSetFocusCell( CDcdGridCell* pCDcdGridCell )
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnSetFocusCell( pCDcdGridCell ) ;
};
void CWjkState::
	OnSetXFixafterColumnNumber( int iFixafterColumnNumber )
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnSetXFixafterColumnNumber( iFixafterColumnNumber );
};
void CWjkState::
	OnSetYFixafterColumnNumber( int iFixafterColumnNumber )
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnSetYFixafterColumnNumber( iFixafterColumnNumber );
};

void CWjkState::OnChangeSelectCell( 
		int iXColumnNumber , int iYColumnNumber , bool bIsSelected ) 
{
	m_pCWndDcdGrid->CWndJikokuhyou::super::
		OnChangeSelectCell( iXColumnNumber , iYColumnNumber , bIsSelected );
}


} } // namespace WndJikokuhyou namespace ViewJikokuhyou
