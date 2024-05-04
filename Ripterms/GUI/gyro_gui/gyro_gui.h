#pragma once

#include "../../../Include/ImGui/imgui.h"
#include "../../../Include/ImGui/imgui_internal.h"

namespace ImGui
{
	IMGUI_API bool Toggle ( const char* label , bool* v );
	IMGUI_API bool IOSToggle ( const char* label , bool* v );
	IMGUI_API bool ColorEditEx ( const char* label , float col[ 3 ] , ImGuiColorEditFlags flags );
	IMGUI_API bool ColorEdit ( const char* label , float col[ 3 ] , ImGuiColorEditFlags flags );

	IMGUI_API bool ButtonScrollableEx ( const char* label , const ImVec2& size_arg = ImVec2 ( 0 , 0 ) , ImGuiButtonFlags flags = 0 );
	IMGUI_API bool CustomSliderScalar ( const char* label , ImGuiDataType data_type , void* p_data , const void* p_min , const void* p_max , const char* format , ImGuiSliderFlags flags );
	IMGUI_API bool CustomSliderInt ( const char* label , int* v , int v_min , int v_max , const char* format , ImGuiSliderFlags flags );
	IMGUI_API bool CustomSliderFloat ( const char* label , float* v , float v_min , float v_max , const char* format , ImGuiSliderFlags flags );
	IMGUI_API bool ButtonScrollable ( const char* label , const ImVec2& size_arg = ImVec2 ( 0 , 0 ) );
	IMGUI_API void CenterTextH ( const char* text );
	IMGUI_API void CenterTextV ( const char* text );
	IMGUI_API void CenterTextHV ( const char* text );

	IMGUI_API void BeginVerticalLine();
	IMGUI_API void EndVerticalLine();
}