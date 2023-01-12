﻿// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// WanrealEditorView.cpp: CWanrealEditorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WanrealEditor.h"
#endif

#include "WanrealEditorDoc.h"
#include "WanrealEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWanrealEditorView

IMPLEMENT_DYNCREATE(CWanrealEditorView, CView)

BEGIN_MESSAGE_MAP(CWanrealEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CWanrealEditorView 생성/소멸

CWanrealEditorView::CWanrealEditorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWanrealEditorView::~CWanrealEditorView()
{
}

BOOL CWanrealEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWanrealEditorView 그리기

void CWanrealEditorView::OnDraw(CDC* /*pDC*/)
{
	CWanrealEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CWanrealEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWanrealEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWanrealEditorView 진단

#ifdef _DEBUG
void CWanrealEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CWanrealEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWanrealEditorDoc* CWanrealEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWanrealEditorDoc)));
	return (CWanrealEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CWanrealEditorView 메시지 처리기