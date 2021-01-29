/*
 * Copyright (C) 2020 Igalia S.L. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(WEBXR)

#include "XRHandedness.h"
#include "XRTargetRayMode.h"
#include <wtf/IsoMalloc.h>
#include <wtf/Ref.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class WebXRSpace;

class WebXRInputSource : public RefCounted<WebXRInputSource> {
    WTF_MAKE_ISO_ALLOCATED(WebXRInputSource);
public:
    static Ref<WebXRInputSource> create(Ref<WebXRSpace>&&);
    ~WebXRInputSource();

    XRHandedness handedness() const;
    XRTargetRayMode targetRayMode() const;
    const WebXRSpace& targetRaySpace() const;
    RefPtr<WebXRSpace> gripSpace() const;
    const Vector<String>& profiles() const;

private:
    WebXRInputSource(Ref<WebXRSpace>&&);

    XRHandedness m_handedness;
    XRTargetRayMode m_targetRayMode;
    Ref<WebXRSpace> m_targetRaySpace;
    Vector<String> m_profiles;
};

} // namespace WebCore

#endif // ENABLE(WEBXR)
