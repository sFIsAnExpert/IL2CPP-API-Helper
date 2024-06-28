#include "sdk/sdk.hpp"

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    IL2CPP_API::Initialize();

    

    //while (true) {
    //    auto list = PlayerControl::GetPlayers();
    //    if (!list) continue;
    //    if (list->Count() == 0) continue;
    //    auto arr = list->GetValues();
    //    if (!arr) continue;
    //    for (uint8_t i = 0; i < list->Count(); i++) {
    //        PlayerControl* p = arr->GetValue(i);
    //        if (!p) continue;
    //        Transform* trans = p->GetTransform();
    //        Vector3 pos = trans->GetPosition();
    //        Vector2 screen;
    //        /*
    //        if (!mCam->WorldToScreen(screen, pos)) continue;*/
    //        GUI::Label({ 15, 15, 15, 15 }, "Entity");
    //    }
    //    Sleep(10);
    //}

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, MainThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

