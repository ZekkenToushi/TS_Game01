#pragma once
class IGameObject
{
public:
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画。
	/// </summary>
	virtual void Render();
	/// <summary>
	/// 削除リクエストを行う。
	/// </summary>
	void RequestDelete() {
		isRequestDelete = true;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// trueが返ってきたら,リクエストを受けている。
	/// </returns>
	bool IsRequestDelete() {
		return isRequestDelete;
	}
private:
	bool  isRequestDelete = false;//削除リクエスト。すぐ消すとアップデートの中でアクセスしてしまうので。

};
