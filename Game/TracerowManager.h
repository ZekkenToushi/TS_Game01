#pragma once
#include "GameObjectManager.h"
#include "Tracerow.h"

class TracerowManager
	: public IGameObject
{
public:
	TracerowManager();
	~TracerowManager();
	//Update関数をオーバーライド。
	void Update();
	//Render関数をオーバーライド。
	void Render();

	/// <summary>
	/// Tracerowを管理する。列の作成とm_centerrow(中心、中心はプレイヤーへ追従）の追従処理。
	/// </summary>
	void TRManagement();

	/// <summary>
	/// 指定した分の席を用意する。（その行のみ）
	/// </summary>
	/// <param name="j">列番号</param>
	/// <param name="i"></param>
	/// <param name="Tyousei"></param>
	void Gyouseiretu(int j, int i);

	/// <summary>
	/// Tracerowの回転,プレイヤーの回転に合わせて列も回転する。//回転させた位置ベクトルを返す。
	/// </summary>
	CVector3 TracerowRotation(CVector3 position);

	/// <summary>
	/// 指定したrowを作る。
	/// 例えば50個のSlaveが並べる行列を作るには 50回 (0～49のnumとpositionを指定して)この関数を呼べば作れる。
	/// </summary>
	/// <param name="num">そのポイントのナンバー</param>
	/// <param name="position">そのポイントのポジション</param>
	void TracerowSet(int num, CVector3 position);

	/// <summary>
	/// 出撃可能のslaveを探す、一番若い席にいるslave番号を返す。-1を返した時は誰もいない。
	/// </summary>
	int SearchReadyNum();

	int GetMaxrow() {
		return Maxrow;
	}
	Tracerow* Gettracerow(int num) {
		return &tracerow[num];
	}
private:
	SkinModel TEST;
	CQuaternion m_rotation = CQuaternion::Identity();//回転。
	//tracerow系。
	CVector3 m_centerrow = CVector3::Zero();//行列の中心。ここを中心にSlave達は整列する。
	CVector3 m_rowForward = CVector3::Zero();//行列の前方向。（プレイヤーへのベクトル）。
	CVector3 m_seatPos = CVector3::Zero();//行列の中心からそれぞれのポイントへのベクトル。行列を作る際距離調整に使用。
	int m_numberfirstrow = 5;//一行目の人数。
	int m_column = 9;//列の数。
	int m_columnhalf = 4;//列の数の半分。
	float m_syakankyori = 70.0f;//基本的な車間距離。
	float m_centerrowdistance = 350.0f;//隊列の中心とプレイヤーとの距離。
	static constexpr int Maxrow = 61;//この数だけ↓配列作る。
	Tracerow tracerow[Maxrow];//Slaveが並ぶ列配列。
	int m_rowcount = 0;//tracerowを作る時に使う。現在作っているrowナンバー。
	bool m_right = true;//tracerowを作る時に使う。右から交互に並べる、trueなら右　falseなら左
};


