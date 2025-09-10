/* Copyright (c) 2019-2024, Arm Limited and Contributors
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 the "License";
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "api_vulkan_sample.h"
#include "rendering/render_pipeline.h"
#include "scene_graph/components/camera.h"

class WideGamut : public ApiVulkanSample
{
	struct
	{
		const std::vector<VkSurfaceFormatKHR> formats = {
		    {VK_FORMAT_R16G16B16A16_SFLOAT, VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT},
		    {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR},
		};
		const std::vector<std::string> format_names = {
		    std::string("Extended sRGB (Linear)"),
		    std::string("sRGB"),
		};
		int format_index = 0;
	} surface;

  public:
	WideGamut();

	virtual bool prepare(const vkb::ApplicationOptions &options) override;
	virtual void create_render_context() override;
	virtual void build_command_buffers() override;
	virtual void render(float delta_time) override;
	virtual void on_update_ui_overlay(vkb::Drawer &drawer) override;

	virtual ~WideGamut() = default;
};

std::unique_ptr<vkb::VulkanSampleC> create_wide_gamut();
