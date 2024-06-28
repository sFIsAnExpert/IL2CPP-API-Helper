#pragma once

class Camera : public UObject {
public:
	static Camera* GetMain() {
		return Method::Call<Camera * (*)()>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_main", 0)();
	}
	static Camera* GetCurrent() {
		return Method::Call<Camera * (*)()>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_current", 0)();
	}
	static Array<Camera*>* GetAllCameras() {
		return Method::Call<Array<Camera*>*(*)()>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_allCameras", 0)();
	}
	static Camera* GetCamera() {
		auto arr = GetAllCameras();
		if (!arr) return nullptr;

		return arr->GetValue(1);
	}
	static void IterateCameras() {
		auto arr = Camera::GetAllCameras();
		if (!arr) return;

		for (uint8_t i = 0; i < arr->GetLength(); i++) {
			auto cam = arr->GetValue(i);
			if (!cam) continue;
			std::cout << "Valid Camera at -> " << unsigned int(i) << "\n";
		}
	}
	bool WorldToScreen(Vector2& screen, Vector3 world) {
		Vector3 ret = Method::Call<Vector3(*)(Camera*, Vector3*)>("UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToViewportPoint", 1)(this, &world);
		if (ret.z < 0)
			return false;

		screen.x = ret.x *= Screen::Width();
		screen.y = ret.y *= Screen::Height();
		screen.y = Screen::Height() - screen.y;

		return true;
	}
};