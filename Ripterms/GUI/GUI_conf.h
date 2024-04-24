#pragma once
#include <ImGui/imgui.h>

namespace Ripterms::GUI
{
	const char* client_name = "r i p t e r m s    g h o s t";
	constexpr float HEADER_HEIGHT = 40.f;
	constexpr float HEADER_CAT_DISTANCE = 10.f;
	constexpr float CATEGORY_WIDTH = 100.0f;

	static ImVec2 category_button_size = ImVec2(100, 51);

	/* other style*/

	static bool ripterms_title = true;
	/* both are false by default but eh why not */
	static bool show_color_theming = false;
	static bool show_rounding_theming = false;

	/* color picker colors */
	static ImColor color_active_tab = ImColor( 52 , 70 , 130 , 255);
	static ImColor color_child_bg = ImColor( 31 , 29 , 53 , 79);
	static ImColor color_slider_grab = ImColor( 78 , 108 , 211 , 255);
	static ImColor color_frame_bg = ImColor(50, 50, 50, 80);
	static ImColor color_frame_bg_active = ImColor(35, 35, 35, 255);
	static ImColor color_frame_bg_hovered = ImColor(68, 64, 64, 255);
	static ImColor color_window_bg = ImColor( 17 , 16 , 29 , 255);
	static ImColor color_button = ImColor( 31 , 29 , 53 , 80);
	static ImColor color_button_active = ImColor( 78 , 108 , 211 , 255);
	static ImColor color_button_hovered = ImColor( 52 , 70 , 130 , 255);
	static ImColor color_text = ImColor(200, 200, 200, 255);
	static ImColor color_header = ImColor(78, 78, 78, 255);
	static ImColor color_header_active = ImColor(78, 78, 78, 255);
	static ImColor color_header_hovered = ImColor(78, 78, 78, 255);
	static ImColor color_checkmark = ImColor(143, 46, 46, 255);
	static ImColor color_ios_toggle_circle = ImColor( 52 , 70 , 130, 255);
	static ImColor color_slider_line = ImColor( 52 , 70 , 130, 255);
	static ImColor color_ios_off = ImColor( 17 , 16 , 29, 255);
	static ImColor color_ios_on = ImColor( 17 , 16 , 29, 255);
	static ImColor color_border = ImColor( 78 , 108 , 211, 255); // Default gray value: 59, 59, 59
	static ImColor color_border_shadow = ImColor(0, 0, 0, 0);

	/* rounding */

	static float rounding_frame = 0.0f;
	static float rounding_window = 10.0f;
	static float rounding_child = 10.0f;
	static float rounding_grab = 20.0f;
	static float rounding_popup = 0.0f;
	static float rounding_scrollbar = 0.0f;
	static float rounding_tab = 0.0f;
}