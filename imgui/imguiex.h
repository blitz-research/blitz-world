#pragma once

#include "ImGuiFileDialog-checkout/ImGuiFileDialog.h"
#include "imgui-checkout/imgui.h"

#include <core/core.h>
#include <geom/geom.h>

namespace ImGuiEx {

bool Checkbox(const char* label, wb::BoolProperty& v);

bool InputInt(const char* label, wb::IntProperty& v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);

bool DragFloat(const char* label, wb::FloatProperty& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
			   const char* format = "%.3f", ImGuiSliderFlags flags = 0);

bool FilePath(const char* label, wb::StringProperty& v, const char* dialogTitle, const char* vFilters);

bool ColorEdit4(const char* label, wb::Property<wb::Vec4f>& v, ImGuiColorEditFlags flags = 0);

bool ColorPicker4(const char* label, wb::Property<wb::Vec4f>& v, ImGuiColorEditFlags flags = 0,
				  const float* ref_col = nullptr);

} // namespace ImGuiEx
