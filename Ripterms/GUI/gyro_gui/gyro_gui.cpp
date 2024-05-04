#define IMGUI_DEFINE_MATH_OPERATORS
#include "gyro_gui.h"

bool ImGui::Toggle ( const char* label , bool* v )
{
	ImGuiWindow* window = GetCurrentWindow ( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID ( label );
	const ImVec2 label_size = CalcTextSize ( label , NULL , true );

	float height = ImGui::GetFrameHeight ( );
	const ImVec2 pos = window->DC.CursorPos;

	float width = height * 2.f;
	float radius = height * 0.50f;

	const ImRect total_bb ( pos , pos + ImVec2 ( width + ( label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f ) , label_size.y + style.FramePadding.y * 2.0f ) );

	ItemSize ( total_bb , style.FramePadding.y );
	if ( !ItemAdd ( total_bb , id ) )
		return false;

	float last_active_id_timer = g.LastActiveIdTimer;

	bool hovered , held;
	bool pressed = ButtonBehavior ( total_bb , id , &hovered , &held );
	if ( pressed )
	{
		*v = !( *v );
		MarkItemEdited ( id );
		g.LastActiveIdTimer = 0.f;
	}

	if ( g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed )
		g.LastActiveIdTimer = last_active_id_timer;

	float t = *v ? 1.0f : 0.0f;

	if ( g.LastActiveId == id )
	{
		float t_anim = ImSaturate ( g.LastActiveIdTimer / 0.16f );
		t = *v ? ( t_anim ) : ( 1.0f - t_anim );
	}

	ImU32 col_bg = GetColorU32 ( ( held && hovered ) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg );

	const ImRect frame_bb ( pos , pos + ImVec2 ( width , height ) );

	RenderFrame ( frame_bb.Min , frame_bb.Max , col_bg , true , height * 0.5f );
	RenderNavHighlight ( total_bb , id );

	ImVec2 label_pos = ImVec2 ( frame_bb.Max.x + style.ItemInnerSpacing.x , frame_bb.Min.y + style.FramePadding.y );
	RenderText ( label_pos , label );
	window->DrawList->AddCircleFilled ( ImVec2 ( pos.x + radius + t * ( width - radius * 2.0f ) , pos.y + radius ) , radius - 1.5f , ImGui::GetColorU32 ( ImGuiCol_CheckMark ) , 36 );

	return pressed;
}

bool ImGui::IOSToggle ( const char* label , bool* v )
{
	ImGuiWindow* window = GetCurrentWindow ( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID ( label );
	const ImVec2 label_size = CalcTextSize ( label , NULL , true );

	float height = ImGui::GetFrameHeight ( );
	const ImVec2 pos = window->DC.CursorPos;

	float width = height * 2.f;
	float radius = height * 0.50f;

	const ImRect total_bb ( pos , pos + ImVec2 ( width + ( label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f ) , label_size.y + style.FramePadding.y * 2.0f ) );

	ItemSize ( total_bb , style.FramePadding.y );
	if ( !ItemAdd ( total_bb , id ) )
		return false;

	float last_active_id_timer = g.LastActiveIdTimer;

	bool hovered , held;
	bool pressed = ButtonBehavior ( total_bb , id , &hovered , &held );
	if ( pressed )
	{
		*v = !( *v );
		MarkItemEdited ( id );
		g.LastActiveIdTimer = 0.f;
	}

	if ( g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed )
		g.LastActiveIdTimer = last_active_id_timer;

	float t = *v ? 1.0f : 0.0f;

	if ( g.LastActiveId == id )
	{
		float t_anim = ImSaturate ( g.LastActiveIdTimer / 0.16f );
		t = *v ? ( t_anim ) : ( 1.0f - t_anim );
	}

	//ImU32 col_bg = GetColorU32 ( ( held && hovered ) ? ImGuiCol_IOSToggleBgActive : hovered ? ImGuiCol_IOSToggleBgHovered : ImGuiCol_IOSToggleBg );
	ImU32 col_bg = GetColorU32 ( *v ? ImGuiCol_IOSToggleBgOn : ImGuiCol_IOSToggleBgOff );
	const ImRect frame_bb ( pos , pos + ImVec2 ( width , height ) );

	RenderFrame ( frame_bb.Min , frame_bb.Max , col_bg , true , height * 0.5f );
	RenderNavHighlight ( total_bb , id );

	ImVec2 label_pos = ImVec2 ( frame_bb.Max.x + style.ItemInnerSpacing.x , frame_bb.Min.y + style.FramePadding.y );
	RenderText ( label_pos , label );
	window->DrawList->AddCircleFilled ( ImVec2 ( pos.x + radius + t * ( width - radius * 2.0f ) , pos.y + radius ) , radius - 1.5f , ImGui::GetColorU32 ( ImGuiCol_IOSToggleCircle ) , 36 );

	return pressed;
}

bool ImGui::ButtonScrollableEx ( const char* label , const ImVec2& size_arg , ImGuiButtonFlags flags )
{
	ImGuiWindow* window = GetCurrentWindow ( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID ( label );
	const ImVec2 label_size = CalcTextSize ( label , NULL , true );

	ImVec2 pos = window->DC.CursorPos;
	if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset )
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize ( size_arg , label_size.x + style.FramePadding.x * 2.0f , label_size.y + style.FramePadding.y * 2.0f );

	const ImRect bb ( pos , pos + size );
	ItemSize ( size , style.FramePadding.y );
	if ( !ItemAdd ( bb , id ) )
		return false;

	bool hovered , held;
	bool pressed = ButtonBehavior ( bb , id , &hovered , &held , flags );

	const ImU32 col = GetColorU32 ( ( held && hovered ) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button );
	RenderNavHighlight ( bb , id );
	RenderFrame ( bb.Min , bb.Max , col , true , style.FrameRounding );

	const float offset = size.x >= label_size.x + style.FramePadding.x * 2.0f ? size.x + style.FramePadding.x : static_cast< int >( g.Time * 60.f ) % static_cast< int >( label_size.x + size.x + style.FramePadding.x * 2.f + 4 );
	const ImRect text = ImRect ( ImVec2 ( bb.Min.x + size.x - offset + style.FramePadding.x * 2.f , bb.Min.y + style.FramePadding.y ) , bb.Max - style.FramePadding );

	RenderTextClipped ( text.Min , text.Max , label , NULL , &label_size , size.x >= label_size.x + style.FramePadding.x * 2.0f ? g.Style.ButtonTextAlign : ImVec2 ( 0 , 0 ) , &bb );
	return pressed;
}

bool ImGui::CustomSliderScalar ( const char* label , ImGuiDataType data_type , void* p_data , const void* p_min , const void* p_max , const char* format , ImGuiSliderFlags flags )
{
	ImGuiWindow* window = GetCurrentWindow ( );
	if ( window->SkipItems )
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID ( label );
	const float w = CalcItemWidth ( );

	const ImVec2 label_size = CalcTextSize ( label , NULL , true );
	const ImRect frame_bb ( window->DC.CursorPos , window->DC.CursorPos + ImVec2 ( w , label_size.y + style.FramePadding.y * 2.0f ) );
	const ImRect total_bb ( frame_bb.Min , frame_bb.Max + ImVec2 ( label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f , 0.0f ) );

	const bool temp_input_allowed = ( flags & ImGuiSliderFlags_NoInput ) == 0;
	ItemSize ( total_bb , style.FramePadding.y );
	if ( !ItemAdd ( total_bb , id , &frame_bb , temp_input_allowed ? ImGuiItemFlags_Inputable : 0 ) )
		return false;

	// Default format string when passing NULL
	if ( format == NULL )
		format = DataTypeGetInfo ( data_type )->PrintFmt;

	const bool hovered = ItemHoverable ( frame_bb , id , g.LastItemData.InFlags );
	bool temp_input_is_active = temp_input_allowed && TempInputIsActive ( id );
	if ( !temp_input_is_active )
	{
		// Tabbing or CTRL-clicking on Slider turns it into an input box
		const bool clicked = hovered && IsMouseClicked ( 0 , id );
		const bool make_active = ( clicked || g.NavActivateId == id );
		if ( make_active && clicked )
			SetKeyOwner ( ImGuiKey_MouseLeft , id );
		if ( make_active && temp_input_allowed )
			if ( ( clicked && g.IO.KeyCtrl ) || ( g.NavActivateId == id && ( g.NavActivateFlags & ImGuiActivateFlags_PreferInput ) ) )
				temp_input_is_active = true;

		if ( make_active && !temp_input_is_active )
		{
			SetActiveID ( id , window );
			SetFocusID ( id , window );
			FocusWindow ( window );
			g.ActiveIdUsingNavDirMask |= ( 1 << ImGuiDir_Left ) | ( 1 << ImGuiDir_Right );
		}
	}

	if ( temp_input_is_active )
	{
		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
		const bool is_clamp_input = ( flags & ImGuiSliderFlags_AlwaysClamp ) != 0;
		return TempInputScalar ( frame_bb , id , label , data_type , p_data , format , is_clamp_input ? p_min : NULL , is_clamp_input ? p_max : NULL );
	}

	// Draw frame
	const ImU32 frame_col = GetColorU32 ( g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg );
	ImU32 slider_line_col = GetColorU32 ( ImGuiCol_SliderLine );

	RenderNavHighlight ( frame_bb , id );
	RenderFrame ( frame_bb.Min - ImVec2 ( -1 , -6 ) , frame_bb.Max - ImVec2 ( -1 , 6 ) , frame_col , false , 10 );

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = SliderBehavior ( frame_bb , id , data_type , p_data , p_min , p_max , format , flags , &grab_bb );
	if ( value_changed )
		MarkItemEdited ( id );

	// Render grab
	if ( grab_bb.Max.x > grab_bb.Min.x )
	{
		RenderFrame ( frame_bb.Min - ImVec2 ( 0 , -6 ) , grab_bb.Max - ImVec2 ( 0 , 4 ) , slider_line_col , false , 10 );
		window->DrawList->AddRectFilled ( grab_bb.Min - ImVec2 ( -1 , -5 ) , grab_bb.Max - ImVec2 ( -1 , 5 ) , GetColorU32 ( g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab ) , style.GrabRounding );
	}
	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[ 64 ];
	const char* value_buf_end = value_buf + DataTypeFormatString ( value_buf , IM_ARRAYSIZE ( value_buf ) , data_type , p_data , format );
	//RenderTextClipped ( frame_bb.Min - ImVec2 ( -1 , 25 ) , frame_bb.Max - ImVec2 ( -1 , 5 ) , value_buf , value_buf_end , NULL , ImVec2 ( 0.5f , 0.5f ) );

	if ( g.LogEnabled )
		LogSetNextTextDecoration ( "{" , "}" );
	RenderTextClipped ( frame_bb.Min , frame_bb.Max , value_buf , value_buf_end , NULL , ImVec2 ( 0.5f , 0.5f ) );

	if ( label_size.x > 0.0f )
		RenderText ( ImVec2 ( frame_bb.Max.x + style.ItemInnerSpacing.x , frame_bb.Min.y + style.FramePadding.y ) , label );

	IMGUI_TEST_ENGINE_ITEM_INFO ( id , label , g.LastItemData.StatusFlags | ( temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0 ) );
	return value_changed;
}


bool ImGui::ButtonScrollable ( const char* label , const ImVec2& size_arg )
{
	return ButtonScrollableEx ( label , size_arg , ImGuiButtonFlags_None );
}

void ImGui::CenterTextH ( const char* text )
{
	auto width = ImGui::GetContentRegionAvail ( ).x;
	auto text_width = ImGui::CalcTextSize ( text ).x;

	ImGui::SetCursorPosX ( ( width - text_width ) * .5f );
	ImGui::Text ( text );
}

void ImGui::CenterTextV ( const char* text )
{
	auto heigth = ImGui::GetContentRegionAvail ( ).y;
	auto text_heigth = ImGui::CalcTextSize ( text ).y;

	ImGui::SetCursorPosY ( ( heigth - text_heigth ) * .5f );
	ImGui::Text ( text );
}

void ImGui::CenterTextHV ( const char* text )
{
	auto avail = ImGui::GetContentRegionAvail ( );
	auto text_size = ImGui::CalcTextSize ( text );

	ImGui::SetCursorPos ( ImVec2 ( ( avail.x - text_size.x ) * .5f , ( avail.y - text_size.y ) * .5f ) );
	ImGui::Text ( text );
}


static ImVector<ImVec2> verticalLineStack;
void ImGui::BeginVerticalLine()
{
	verticalLineStack.push_back(ImGui::GetCursorScreenPos());
}

void ImGui::EndVerticalLine()
{
	const ImVec2& old_pos = verticalLineStack.back();
	ImGui::GetWindowDrawList()->AddLine(old_pos, {old_pos.x, ImGui::GetCursorScreenPos().y}, ImColor(56, 61, 69), 2.0f);
	verticalLineStack.pop_back();
}

bool ImGui::ColorEdit ( const char* label , float col[ 3 ] , ImGuiColorEditFlags flags )
{
	return ColorEdit4 ( label , col , flags | ImGuiColorEditFlags_NoInputs );
}

bool ImGui::ColorEditEx ( const char* label , float col[ 3 ] , ImGuiColorEditFlags flags )
{
	return ColorEdit4 ( label , col , flags | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs );
}

bool ImGui::CustomSliderFloat ( const char* label , float* v , float v_min , float v_max , const char* format , ImGuiSliderFlags flags )
{
	return CustomSliderScalar ( label , ImGuiDataType_Float , v , &v_min , &v_max , format , flags );
}

bool ImGui::CustomSliderInt ( const char* label , int* v , int v_min , int v_max , const char* format , ImGuiSliderFlags flags )
{
	return CustomSliderScalar ( label , ImGuiDataType_S32 , v , &v_min , &v_max , format , flags );
}
