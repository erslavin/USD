//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//

#include "pxr/imaging/hd/rendererPluginHandle.h"

#include "pxr/imaging/hd/rendererPlugin.h"
#include "pxr/imaging/hd/rendererPluginRegistry.h"

PXR_NAMESPACE_OPEN_SCOPE

HdRendererPluginHandle::HdRendererPluginHandle(
    const HdRendererPluginHandle &other)
  : _pluginId(other._pluginId)
  , _plugin(other._plugin)
{
    if (_plugin) {
        HdRendererPluginRegistry::GetInstance().AddPluginReference(_plugin);
    }
}

HdRendererPluginHandle::~HdRendererPluginHandle()
{
    HdRendererPluginRegistry::GetInstance().ReleasePlugin(_plugin);
}

HdRendererPluginHandle &
HdRendererPluginHandle::operator=(const HdRendererPluginHandle &other)
{
    HdRendererPluginRegistry::GetInstance().ReleasePlugin(_plugin);
    _pluginId = other._pluginId;
    _plugin = other._plugin;
    if (_plugin) {
        HdRendererPluginRegistry::GetInstance().AddPluginReference(_plugin);
    }
    return *this;
}

HdRendererPluginHandle &
HdRendererPluginHandle::operator=(const std::nullptr_t &)
{
    *this = HdRendererPluginHandle();
    return *this;
}

bool
HdRendererPluginHandle::operator==(const HdRendererPluginHandle &other) const
{
    return
        (_pluginId == other._pluginId) &&
        (_plugin == other._plugin);
}

bool
HdRendererPluginHandle::operator!=(const HdRendererPluginHandle &other) const
{
    return !(*this == other);
}

PXR_NAMESPACE_CLOSE_SCOPE
