/* Copyright (c) 2019-2025, Arm Limited and Contributors
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

#include "wide_gamut.h"

#include "common/vk_common.h"
#include "filesystem/legacy.h"
#include "gltf_loader.h"
#include "gui.h"
#include "platform/platform.h"
#include "rendering/subpasses/forward_subpass.h"
#include "stats/stats.h"

WideGamut::WideGamut()
{
	/* Enable VK_EXT_swapchain_color_space_ext when available. Without this extension swapchains should not support additional color spaces. */
	add_instance_extension(VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME, true);
}

bool WideGamut::prepare(const vkb::ApplicationOptions &options)
{
	if (!VulkanSample::prepare(options))
	{
		return false;
	}

	return true;
}

void WideGamut::build_command_buffers()
{
}

void WideGamut::render(float /*delta_time*/)
{
	if (!prepared)
	{
		return;
	}
	// submit command buffer for frame to the queue
}

/**
 * 	@brief Setting custom surface format priority list to required VK_FORMAT_B8G8R8A8_UNORM format
 */
void WideGamut::create_render_context()
{
	auto surface_priority_list = std::vector<VkSurfaceFormatKHR>{
	    surface.formats[surface.format_index],
	    /* Fallback to sRGB. */
	    {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR},
	};
	VulkanSample::create_render_context(surface_priority_list);
}

void WideGamut::on_update_ui_overlay(vkb::Drawer &drawer)
{
	if (drawer.header("Settings"))
	{
		if (drawer.combo_box("Surface Color Space", &surface.format_index, surface.format_names))
		{
			// recreate_swapchain();
		}
	}
}

std::unique_ptr<vkb::VulkanSampleC> create_wide_gamut()
{
	return std::make_unique<WideGamut>();
}
