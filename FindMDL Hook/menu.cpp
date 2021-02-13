#include <imgui.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>

typedef HRESULT(_stdcall* EndScene)(LPDIRECT3DDEVICE9 pDevice);
HRESULT _stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
EndScene oEndScene = NULL;

void main()
{
    if (GetAsyncKeyState(VK_HOME) & 1)
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        static const char* knife_models[]{ "v_minecraft_pickaxe" };
        static const char* ak47_models[]{ "v_rif_beast" };
        static const char* awp_models[]{ "v_snip_msr" };
        static int selectedItem = 0;
        static int selectedItem2 = 0;
        static int selectedItem3 = 0;

        {
            ImGui::Begin("Model Changer");
            ImGui::Combo("Knife Model", &selectedItem, knife_models, IM_ARRAYSIZE(knife_models), 2);
            ImGui::Combo("AK47 Model", &selectedItem2, ak47_models, IM_ARRAYSIZE(ak47_models), 2);
            ImGui::Combo("AWP Model", &selectedItem3, awp_models, IM_ARRAYSIZE(awp_models), 2);
        }

        ImGui::End();
        ImGui::EndFrame();
        ImGui::EndCombo();
    }
}
