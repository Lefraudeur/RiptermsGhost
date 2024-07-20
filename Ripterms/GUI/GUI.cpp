#include "GUI.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_win32.h>
#include <Windows.h>
#include "../Modules/Modules.h"
#include "font.h"
#include "../Hook/Hook.h"
#include "GUI_conf.h"
#include "gl/GL.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"

namespace
{
	typedef BOOL(WINAPI* type_wglSwapBuffers)(HDC);
	type_wglSwapBuffers original_wglSwapBuffers = nullptr;
	WNDPROC original_WndProc = nullptr;
	type_wglSwapBuffers target_wglSwapBuffers = nullptr;

	HDC device = nullptr;
	ImGuiContext* imGuiContext = nullptr;
	HGLRC new_context = nullptr;
	HGLRC old_context = nullptr;

	Ripterms::Hook<type_wglSwapBuffers>* guiHook = nullptr;
}

static void update_style()
{
	/* colors  */

	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_CheckMark] = Ripterms::GUI::color_checkmark;
	style.Colors[ImGuiCol_IOSToggleCircle] = Ripterms::GUI::color_ios_toggle_circle;
	style.Colors[ImGuiCol_SliderLine] = Ripterms::GUI::color_slider_line;
	style.Colors[ImGuiCol_IOSToggleBgOff] = Ripterms::GUI::color_ios_off;
	style.Colors[ImGuiCol_IOSToggleBgOn] = Ripterms::GUI::color_ios_on;
	style.Colors[ImGuiCol_SliderGrab] = Ripterms::GUI::color_slider_grab;
	style.Colors[ImGuiCol_SliderGrabActive] = Ripterms::GUI::color_slider_grab;
	style.Colors[ImGuiCol_FrameBg] = Ripterms::GUI::color_frame_bg;
	style.Colors[ImGuiCol_FrameBgActive] = Ripterms::GUI::color_frame_bg_active;
	style.Colors[ImGuiCol_FrameBgHovered] = Ripterms::GUI::color_frame_bg_hovered;
	style.Colors[ImGuiCol_WindowBg] = Ripterms::GUI::color_window_bg;
	style.Colors[ImGuiCol_Button] = Ripterms::GUI::color_button;
	style.Colors[ImGuiCol_ButtonHovered] = Ripterms::GUI::color_button_hovered;
	style.Colors[ImGuiCol_ButtonActive] = Ripterms::GUI::color_button_active;
	style.Colors[ImGuiCol_Header] = Ripterms::GUI::color_header;
	style.Colors[ImGuiCol_Text] = Ripterms::GUI::color_text;
	style.Colors[ImGuiCol_HeaderActive] = Ripterms::GUI::color_header_active;
	style.Colors[ImGuiCol_HeaderHovered] = Ripterms::GUI::color_header_hovered;
	style.Colors[ImGuiCol_ChildBg] = Ripterms::GUI::color_child_bg;
	style.Colors[ImGuiCol_Border] = Ripterms::GUI::color_border;
	style.Colors[ImGuiCol_BorderShadow] = Ripterms::GUI::color_border_shadow;

	/*  rounding */

	style.FrameRounding = Ripterms::GUI::rounding_frame;
	style.WindowRounding = Ripterms::GUI::rounding_window;
	style.ChildRounding = Ripterms::GUI::rounding_child;
	style.GrabRounding = Ripterms::GUI::rounding_grab;
	style.PopupRounding = Ripterms::GUI::rounding_popup;
	style.ScrollbarRounding = Ripterms::GUI::rounding_scrollbar;
	style.TabRounding = Ripterms::GUI::rounding_tab;
	style.WindowBorderSize = 1.5f;
	style.FrameBorderSize = 1.0f;
	style.ChildBorderSize = 1.0f;
	style.WindowPadding = ImVec2(Ripterms::GUI::HEADER_CAT_DISTANCE, Ripterms::GUI::HEADER_CAT_DISTANCE);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK detour_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		Ripterms::GUI::draw = !Ripterms::GUI::draw;
	}

	if (Ripterms::GUI::draw)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return true;
	}

	if (msg == WM_KEYDOWN)
	{
		for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
		{
			for (Ripterms::Modules::IModule* m : category.modules)
			{
				m->onKeyBind(wParam);
			}
		}
	}

	return CallWindowProcA(original_WndProc, hWnd, msg, wParam, lParam);
}

static BOOL WINAPI detour_wglSwapBuffers(HDC unnamedParam1)
{
	static bool isInit = false;

	static RECT originalClip;
	static bool clipped = true;

	HWND current_window = WindowFromDC(unnamedParam1);
	if (isInit && current_window != Ripterms::window)
	{
		old_context = wglGetCurrentContext();
		wglMakeCurrent(unnamedParam1, new_context);
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext(imGuiContext);
		SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
		Ripterms::window = current_window;
		original_WndProc = (WNDPROC)SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)&detour_WndProc);
		wglMakeCurrent(unnamedParam1, old_context);
		isInit = false;
	}

	if (!isInit)
	{
		device = unnamedParam1;
		old_context = wglGetCurrentContext();
		if (new_context)
			wglDeleteContext(new_context);
		new_context = wglCreateContext(unnamedParam1);

		imGuiContext = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;


		ImFontConfig CustomFont;
		CustomFont.FontDataOwnedByAtlas = false;

		io.Fonts->AddFontFromMemoryTTF((void*)Custom.data(), (int)Custom.size(), 17.5f, &CustomFont);
		io.Fonts->AddFontDefault();
		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init();
		ImGui_ImplWin32_Init(Ripterms::window);
		isInit = true;
	}

	wglMakeCurrent(unnamedParam1, new_context);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if ((Ripterms::version.type == Ripterms::Version::MAJOR_1_8_9 || Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10) 
		&& Ripterms::p_env && Ripterms::cache->is_valid)
		ActiveRenderInfo::update_cache();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Overlay", nullptr, 
		ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
	{
		Ripterms::JNIFrame jni_frame(Ripterms::p_env, 30);
		for (Ripterms::Modules::Category& category : Ripterms::Modules::categories)
		{
			for (Ripterms::Modules::IModule* m : category.modules)
			{
				m->render();
			}
		}
	}
	ImGui::End();

	if (Ripterms::GUI::draw)
	{
		update_style();

		if (clipped)
		{
			GetClipCursor(&originalClip);
			ClipCursor(nullptr);
			clipped = false;
		}

		ImGui::SetNextWindowBgAlpha(1.f);
		ImGui::SetNextWindowSize(ImVec2(600.0f, 400.f));
		ImGui::Begin("Ripterms Ghost", nullptr, ImGuiWindowFlags_NoDecoration);
		{
			
			ImGui::BeginChild ( "##header" , ( ImVec2 ( ImGui::GetWindowWidth ( ) - ImGui::GetStyle ( ).WindowPadding.x * 2.f , Ripterms::GUI::HEADER_HEIGHT ) ) );

			if ( Ripterms::GUI::ripterms_title )
			{
				ImVec2 txt_size = ImGui::CalcTextSize ( Ripterms::GUI::client_name );
				ImGui::SetCursorPosY ( ( Ripterms::GUI::HEADER_HEIGHT - txt_size.y ) / 2.0 );
				ImGui::SetCursorPosX ( ImGui::GetWindowWidth ( ) / 2.0f - txt_size.x / 2.0f );
				ImGui::TextColored
				(
					/* if you guys do not like the color change on text there is the original one:
						ImColor
					(
						150 , 0 , 20 ,
						255
					) ,
					*/

					ImColor
					(
						78 , 108 , 211 ,
						255
					) ,
					Ripterms::GUI::client_name
				);
			}
			ImGui::EndChild();
			
			static uint8_t current_category_id = 0;
			constexpr uint8_t settings_id = sizeof(Ripterms::Modules::categories) / sizeof(Ripterms::Modules::Category);
			ImGui::SetCursorPosY(Ripterms::GUI::HEADER_HEIGHT + Ripterms::GUI::HEADER_CAT_DISTANCE + ImGui::GetStyle().WindowPadding.y);
			ImGui::BeginChild("##categories", ImVec2(Ripterms::GUI::CATEGORY_WIDTH, 0));
			{
				for (uint8_t i = 0; i < sizeof(Ripterms::Modules::categories) / sizeof(Ripterms::Modules::Category); ++i)
				{
					bool is_selected = i == current_category_id;
					if(is_selected) 
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(Ripterms::GUI::color_active_tab));
					if (ImGui::Button(Ripterms::Modules::categories[i].name, Ripterms::GUI::category_button_size))
						current_category_id = i;
					if (is_selected)
						ImGui::PopStyleColor();
				}

				ImGui::SetCursorPos(ImVec2(0, ImGui::GetWindowSize().y - Ripterms::GUI::category_button_size.y));

				bool is_settings_selected = current_category_id == settings_id;
				if (is_settings_selected) { ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(Ripterms::GUI::color_active_tab)); }
				if (ImGui::Button("Settings", Ripterms::GUI::category_button_size)) { current_category_id = settings_id; }
				if (is_settings_selected) { ImGui::PopStyleColor(); }
			}
			ImGui::EndChild();

			ImGui::SameLine();
		
			ImGui::SetCursorPosX(Ripterms::GUI::CATEGORY_WIDTH + Ripterms::GUI::HEADER_CAT_DISTANCE + ImGui::GetStyle().WindowPadding.x);
			ImGui::BeginChild("##modules", ImVec2 ( 0 , 0 ) , 0 , ImGuiWindowFlags_NoScrollbar );
			{
				if (current_category_id == settings_id)
				{
					ImGui::SetCursorPosX(ImGui::GetStyle().WindowPadding.x);
					ImGui::Text("Settings");
					ImGui::Separator();

					ImGui::BeginChild("settings content", { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground);

					ImGui::IOSToggle ("Ripterms Title", &Ripterms::GUI::ripterms_title);
					ImGui::IOSToggle ("Show Color Theming", &Ripterms::GUI::show_color_theming);
					ImGui::IOSToggle ("Show Rounding Theming", &Ripterms::GUI::show_rounding_theming);

					if(Ripterms::GUI::show_color_theming)
					{
						ImGui::Separator();

						ImGui::ColorEdit4("Active Tab", &Ripterms::GUI::color_active_tab.Value.x, ImGuiColorEditFlags_NoInputs);
						//ImGui::ColorEdit4("Inactive Tab", &Ripterms::GUI::color_inactive_tab.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Child Background", &Ripterms::GUI::color_child_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Slider Grab", &Ripterms::GUI::color_slider_grab.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background", &Ripterms::GUI::color_frame_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background Active", &Ripterms::GUI::color_frame_bg_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Frame Background Hovered", &Ripterms::GUI::color_frame_bg_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Window Background", &Ripterms::GUI::color_window_bg.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4 ( "IOS Toggle Circle" , &Ripterms::GUI::color_ios_toggle_circle.Value.x , ImGuiColorEditFlags_NoInputs );
						ImGui::ColorEdit4 ( "IOS On" , &Ripterms::GUI::color_ios_on.Value.x , ImGuiColorEditFlags_NoInputs );
						ImGui::ColorEdit4 ( "IOS Off" , &Ripterms::GUI::color_ios_off.Value.x , ImGuiColorEditFlags_NoInputs );
						ImGui::ColorEdit4 ( "Slider Line" , &Ripterms::GUI::color_slider_line.Value.x , ImGuiColorEditFlags_NoInputs );
						ImGui::ColorEdit4("Button", &Ripterms::GUI::color_button.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Button  Active", &Ripterms::GUI::color_button_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Button Hovered", &Ripterms::GUI::color_button_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Text", &Ripterms::GUI::color_text.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header", &Ripterms::GUI::color_header.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header Active", &Ripterms::GUI::color_header_active.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Header Hovered", &Ripterms::GUI::color_header_hovered.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Border", &Ripterms::GUI::color_border.Value.x, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4("Border Shadow", &Ripterms::GUI::color_border_shadow.Value.x, ImGuiColorEditFlags_NoInputs);
					}
				
					if (Ripterms::GUI::show_rounding_theming)
					{
						ImGui::Separator();

						ImGui::SliderFloat("Frame ##Rounding", &Ripterms::GUI::rounding_frame, 0, 100, "%1.0f");
						ImGui::SliderFloat("Window ##Rounding", &Ripterms::GUI::rounding_window, 0, 100, "%1.0f");
						ImGui::SliderFloat("Child ##Rounding", &Ripterms::GUI::rounding_child, 0, 100, "%1.0f");
						ImGui::SliderFloat("Grab ##Rounding", &Ripterms::GUI::rounding_grab, 0, 100, "%1.0f");
						ImGui::SliderFloat("Popup ##Rounding", &Ripterms::GUI::rounding_popup, 0, 100, "%1.0f");
						ImGui::SliderFloat("Scrollbar ##Rounding", &Ripterms::GUI::rounding_scrollbar, 0, 100, "%1.0f");
						ImGui::SliderFloat("Tab ##Rounding", &Ripterms::GUI::rounding_tab, 0, 100, "%1.0f");
					}

					ImGui::EndChild();
				}
				else
				{
					ImGui::SetCursorPosX(ImGui::GetStyle().WindowPadding.x);
					ImGui::Text(Ripterms::Modules::categories[current_category_id].name);
					ImGui::Separator();

					ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(6, 6));
					ImGui::BeginChild("content", { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground);
					{
						//Ripterms::JNIFrame jni_frame(Ripterms::p_env, 30);
						for (Ripterms::Modules::IModule* module : Ripterms::Modules::categories[current_category_id].modules)
						{
							if (ImGui::IOSToggle(module->get_name(), &module->enabled))
								module->display_options = module->enabled;
							if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
								module->display_options = !module->display_options;
							if (module->display_options)
							{
								ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);
								ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().WindowPadding.x);
								ImGui::BeginVerticalLine();
								ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().WindowPadding.x);
								ImGui::BeginGroup();
								ImGui::Text(module->get_description());
								module->renderGUI();
								ImGui::EndGroup();
								ImGui::EndVerticalLine();
								ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);
							}
							ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);
						}
					}
					ImGui::PopStyleVar();

					ImGui::EndChild();
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}
	else if (!clipped)
	{
		ClipCursor(&originalClip);
		clipped = true;
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(unnamedParam1, old_context);
	return original_wglSwapBuffers(unnamedParam1);
}

bool Ripterms::GUI::init()
{
	Ripterms::Module opengl("opengl32.dll");
	if (!opengl)
		return false;
	target_wglSwapBuffers = (type_wglSwapBuffers)opengl.getProcAddress("wglSwapBuffers");
	if (!target_wglSwapBuffers) return false;
	guiHook = new Ripterms::Hook<type_wglSwapBuffers>(target_wglSwapBuffers, detour_wglSwapBuffers, &original_wglSwapBuffers);
	if (guiHook->is_error) return false;
	original_WndProc = (WNDPROC)SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)&detour_WndProc);
	return true;
}

void Ripterms::GUI::clean()
{
	draw = false;
	wglMakeCurrent(device, new_context);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext(imGuiContext);
	SetWindowLongPtrA(Ripterms::window, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	wglMakeCurrent(device, old_context);
	wglDeleteContext(new_context);
	delete guiHook;
	return;
}
