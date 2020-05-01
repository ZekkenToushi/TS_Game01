#include "stdafx.h"
#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game()
{	
	if (m_instance != nullptr) {
		abort();
	}
	m_instance = this;

	//物理エンジンの更新。
	g_physics.Update();
	//カメラを初期化。
	g_camera3D.SetFar(50000.0f);
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	
	//ステージ振り分け。
	switch (Stage) {
	case 0:
		CreateStage0();
		break;
	default:
		CreateStage0();
	}
	
}


Game::~Game()
{
	m_instance = nullptr;
	
	//DeleteGO(m_field1);

}

void Game::CreateStage0() {
	//フィールドの生成。
	m_field1 = NewGO<Field_1>();
	//プレイヤーの更新。
	m_player = NewGO<Player>();
	//プレイ用のカメラ更新。
	m_tsCamera = NewGO<tsCamera>();
	//ライトの更新。
	m_light = NewGO<Light>();
	//スライムジェネレーターの更新。
	m_slaveganerator = NewGO<SlaveGenerator>();
	//行列マネージャーの更新。
	m_tracerowmanager = NewGO<TracerowManager>();
	//敵ジェネレーターの更新。
	m_enemygenerator = NewGO<EnemyGenerator>();
}

void Game::Update()
{
	//constant buffer
}

void Game::Render()
{
	/*
	//レンダリングモード。
	EnRenderMode renderMode = enRenderMode_Normal;
	//描画開始。
	g_graphicsEngine->BegineRender();

	///////////////////////////////////////////////
	//まずはオフスクリーンレンダリング
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(1, &oldRenderTargetView, &oldDepthStencilView);
	//レンダリングターゲットを切り替える。
	ID3D11RenderTargetView* rts[] = {
		//m_renderTargetView
		m_renderTarget.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_renderTarget.GetDepthStensilView());
	//レンダリングターゲットをクリア。
	float clearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
	//d3dDeviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
	//d3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_renderTarget.ClearRenderTarget(clearColor);
	


	///////////////////////////////////////////////
	//ここからオンスクリーンレンダリング。
	///////////////////////////////////////////////
	
	
	//レンダリングターゲットを元に戻す。
	d3dDeviceContext->OMSetRenderTargets(1, &oldRenderTargetView, oldDepthStencilView);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();


	//描画終了。
	g_graphicsEngine->EndRender();
	*/
}

Game * Game::GetInstance()
{
	return m_instance;
}
