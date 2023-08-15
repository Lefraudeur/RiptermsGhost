#pragma once

#include "imgui.h"

namespace Ripterms
{
	namespace GUI
	{
		inline bool draw = false;
		bool init();
		void clean();

		static float alpha = 255;
		static bool tick = false;
		static float speed = .25f;
		static ImVec2 category_button_size = ImVec2(100, 30);

		/* other style*/

		static inline bool ripterms_title = true;

		/* color picker colors */
		static inline ImVec4 color_active_tab = ImVec4(.6f, .0f, .0f, 1.f);
		//static inline ImVec4 color_inactive_tab = ImVec4(.5f, .5f, .5f, 1.f);
		static inline ImColor color_child_bg = ImColor(23, 23, 23, 190);
		static inline ImColor color_bool_enabled = ImColor(10, 150, 10, 255);
		static inline ImColor color_bool_disabled = ImColor(173, 55, 65, 255);
		static inline ImColor color_slider_grab = ImColor(10, 150, 10, 255);
		static inline ImColor color_slider_line = ImColor(173, 55, 65, 255);
		static inline ImColor color_frame_bg = ImColor(25, 25, 25, 255);
		static inline ImColor color_frame_bg_active = ImColor(25, 25, 25, 255);
		static inline ImColor color_frame_bg_hovered = ImColor(25, 25, 25, 255);
		static inline ImColor color_window_bg = ImColor(11, 14, 15, 255);
		static inline ImColor color_button = ImColor(31, 30, 31, 255);
		static inline ImColor color_button_active = ImColor(239, 73, 88, 255);
		static inline ImColor color_button_hovered = ImColor(173, 55, 65, 255);
		static inline ImColor color_text = ImColor(200, 200, 200, 255);
		static inline ImColor color_header = ImColor(78, 78, 78, 255);
		static inline ImColor color_header_active = ImColor(78, 78, 78, 255);
		static inline ImColor color_header_hovered = ImColor(78, 78, 78, 255);

		/* rounding */

		static inline int rounding_frame = 10.f;
		static inline int rounding_window = 5.f;
		static inline int rounding_child = 5.f;
		static inline int rounding_grab = 5.f;
		static inline int rounding_popup = 5.f;
		static inline int rounding_scrollbar = 5.f;
		static inline int rounding_tab = 5.f;
	}
}