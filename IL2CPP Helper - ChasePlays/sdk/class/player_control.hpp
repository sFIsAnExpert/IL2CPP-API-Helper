#pragma once

class PlayerControl;

class PlayerInfo : public Object {
public:
	String* GetName() {
		return this->GetClass()->GetMethod("get_PlayerName", 0)->InternalCall<String*>();
		//return Method::Call<String*(*)(PlayerInfo*)>("Assembly-CSharp", "", "GameData-PlayerInfo", "get_PlayerName", 0)(this);
	}
	String* GetFriendCode() {
		return this->GetField("FriendCode")->GetValue<String*>(this);
	}
	PlayerControl* GetPlayer() {
		return this->GetField("_object")->GetValue<PlayerControl*>(this);
	}
};

class PlayerControl : public Component {
public:
	static PlayerControl* GetLocalPlayer() {
		return Class::Resolve("Assembly-CSharp", "", "PlayerControl")->GetField("LocalPlayer")->GetStaticValue<PlayerControl*>();
	}
	static List<PlayerControl*>* GetPlayers() {
		return Class::Resolve("Assembly-CSharp", "", "PlayerControl")->GetField("AllPlayerControls")->GetStaticValue<List<PlayerControl*>*>();
	}
	PlayerInfo* GetInfo() {
		return Method::Call<PlayerInfo * (*)(PlayerControl*)>("Assembly-CSharp", "", "PlayerControl", "get_Data", 0)(this);
	}
	Vector2 GetTruePosition() {
		return Method::Call<Vector2(*)(PlayerControl*)>("Assembly-CSharp", "", "PlayerControl", "GetTruePosition", 0)(this);
	}
};

class GameData : public Component {
public:
	static List<PlayerInfo*>* GetPlayers() {
		GameData* data = GetInstance();
		if (!data) return nullptr;
		return data->GetField("AllPlayers")->GetValue<List<PlayerInfo*>*>(data);
	}
	static GameData* GetInstance() {
		return Class::Resolve("Assembly-CSharp", "", "GameData")->GetField("Instance")->GetStaticValue<GameData*>();
	}
	int GetPlayerCount() {
		return Method::Call<int(*)(GameData*)>("Assembly-CSharp", "", "GameData", "get_PlayerCount", 0)(this);
	}
};