/*
 * Copyright (C) 2015-2017 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(WEBGL2)

#include "WebGLRenderingContextBase.h"
#include <memory>

namespace WebCore {

class WebGLQuery;
class WebGLSampler;
class WebGLSync;
class WebGLTransformFeedback;
class WebGLVertexArrayObject;

class WebGL2RenderingContext final : public WebGLRenderingContextBase {
    WTF_MAKE_ISO_ALLOCATED(WebGL2RenderingContext);
public:
    static std::unique_ptr<WebGL2RenderingContext> create(CanvasBase&, GraphicsContextGLAttributes);
    static std::unique_ptr<WebGL2RenderingContext> create(CanvasBase&, Ref<GraphicsContextGLOpenGL>&&, GraphicsContextGLAttributes);

    ~WebGL2RenderingContext();

    // Buffer objects
    using WebGLRenderingContextBase::bufferData;
    using WebGLRenderingContextBase::bufferSubData;
    void bufferData(GCGLenum target, const ArrayBufferView& data, GCGLenum usage, GCGLuint srcOffset, GCGLuint length);
    void bufferSubData(GCGLenum target, long long offset, const ArrayBufferView& data, GCGLuint srcOffset, GCGLuint length);
    void copyBufferSubData(GCGLenum readTarget, GCGLenum writeTarget, GCGLint64 readOffset, GCGLint64 writeOffset, GCGLint64 size);
    void getBufferSubData(GCGLenum target, long long srcByteOffset, RefPtr<ArrayBufferView>&& dstData, GCGLuint dstOffset = 0, GCGLuint length = 0);

    // Framebuffer objects
    WebGLAny getFramebufferAttachmentParameter(GCGLenum target, GCGLenum attachment, GCGLenum pname) final;
    void blitFramebuffer(GCGLint srcX0, GCGLint srcY0, GCGLint srcX1, GCGLint srcY1, GCGLint dstX0, GCGLint dstY0, GCGLint dstX1, GCGLint dstY1, GCGLbitfield mask, GCGLenum filter);
    void framebufferTextureLayer(GCGLenum target, GCGLenum attachment, WebGLTexture*, GCGLint level, GCGLint layer);
    WebGLAny getInternalformatParameter(GCGLenum target, GCGLenum internalformat, GCGLenum pname);
    void invalidateFramebuffer(GCGLenum target, const Vector<GCGLenum>& attachments);
    void invalidateSubFramebuffer(GCGLenum target, const Vector<GCGLenum>& attachments, GCGLint x, GCGLint y, GCGLsizei width, GCGLsizei height);
    void readBuffer(GCGLenum src);

    // Renderbuffer objects
    void renderbufferStorageMultisample(GCGLenum target, GCGLsizei samples, GCGLenum internalformat, GCGLsizei width, GCGLsizei height);

    // Texture objects
    void texStorage2D(GCGLenum target, GCGLsizei levels, GCGLenum internalFormat, GCGLsizei width, GCGLsizei height);
    void texStorage3D(GCGLenum target, GCGLsizei levels, GCGLenum internalFormat, GCGLsizei width, GCGLsizei height, GCGLsizei depth);

#if ENABLE(VIDEO)
    using TexImageSource = WTF::Variant<RefPtr<ImageBitmap>, RefPtr<ImageData>, RefPtr<HTMLImageElement>, RefPtr<HTMLCanvasElement>, RefPtr<HTMLVideoElement>>;
#else
    using TexImageSource = WTF::Variant<RefPtr<ImageBitmap>, RefPtr<ImageData>, RefPtr<HTMLImageElement>, RefPtr<HTMLCanvasElement>>;
#endif

    using WebGLRenderingContextBase::texImage2D;
    void texImage2D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLint border, GCGLenum format, GCGLenum type, GCGLintptr offset);
    ExceptionOr<void> texImage2D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLint border, GCGLenum format, GCGLenum type, TexImageSource&&);
    void texImage2D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLint border, GCGLenum format, GCGLenum type, RefPtr<ArrayBufferView>&& srcData, GCGLuint srcOffset);

    void texImage3D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, GCGLenum format, GCGLenum type, GCGLint64 pboOffset);
    ExceptionOr<void> texImage3D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, GCGLenum format, GCGLenum type, TexImageSource&&);
    void texImage3D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, GCGLenum format, GCGLenum type, RefPtr<ArrayBufferView>&& pixels);
    void texImage3D(GCGLenum target, GCGLint level, GCGLint internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, GCGLenum format, GCGLenum type, RefPtr<ArrayBufferView>&& srcData, GCGLuint srcOffset);

    using WebGLRenderingContextBase::texSubImage2D;
    void texSubImage2D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLsizei width, GCGLsizei height, GCGLenum format, GCGLenum type, GCGLintptr pboOffset);
    ExceptionOr<void> texSubImage2D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLsizei width, GCGLsizei height, GCGLenum format, GCGLenum type, TexImageSource&&);
    void texSubImage2D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLsizei width, GCGLsizei height, GCGLenum format, GCGLenum type, RefPtr<ArrayBufferView>&& srcData, GCGLuint srcOffset);

    void texSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLenum format, GCGLenum type, GCGLint64 pboOffset);
    void texSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLenum format, GCGLenum type, RefPtr<ArrayBufferView>&& pixels, GCGLuint srcOffset);
    ExceptionOr<void> texSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLenum format, GCGLenum type, TexImageSource&&);

    void copyTexSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLint x, GCGLint y, GCGLsizei width, GCGLsizei height);

    using WebGLRenderingContextBase::compressedTexImage2D;
    void compressedTexImage2D(GCGLenum target, GCGLint level, GCGLenum internalformat, GCGLsizei width, GCGLsizei height, GCGLint border, GCGLsizei imageSize, GCGLint64 offset);
    void compressedTexImage2D(GCGLenum target, GCGLint level, GCGLenum internalformat, GCGLsizei width, GCGLsizei height, GCGLint border, ArrayBufferView& data, GCGLuint srcOffset, GCGLuint srcLengthOverride);
    void compressedTexImage3D(GCGLenum target, GCGLint level, GCGLenum internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, GCGLsizei imageSize, GCGLint64 offset);
    void compressedTexImage3D(GCGLenum target, GCGLint level, GCGLenum internalformat, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLint border, ArrayBufferView& srcData, GCGLuint srcOffset, GCGLuint srcLengthOverride);

    using WebGLRenderingContextBase::compressedTexSubImage2D;
    void compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLintptr offset);
    void compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, ArrayBufferView& srcData, GLuint srcOffset, GLuint srcLengthOverride);

    void compressedTexSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLenum format, GCGLsizei imageSize, GCGLint64 offset);
    void compressedTexSubImage3D(GCGLenum target, GCGLint level, GCGLint xoffset, GCGLint yoffset, GCGLint zoffset, GCGLsizei width, GCGLsizei height, GCGLsizei depth, GCGLenum format, ArrayBufferView& data, GCGLuint srcOffset, GCGLuint srcLengthOverride);

    // Programs and shaders
    GCGLint getFragDataLocation(WebGLProgram&, const String& name);

    // Uniforms and attributes
    using Uint32List = TypedList<Uint32Array, uint32_t>;
    using Float32List = TypedList<Float32Array, float>;
    void uniform1ui(WebGLUniformLocation*, GCGLuint v0);
    void uniform2ui(WebGLUniformLocation*, GCGLuint v0, GCGLuint v1);
    void uniform3ui(WebGLUniformLocation*, GCGLuint v0, GCGLuint v1, GCGLuint v2);
    void uniform4ui(WebGLUniformLocation*, GCGLuint v0, GCGLuint v1, GCGLuint v2, GCGLuint v3);
    void uniform1uiv(WebGLUniformLocation*, Uint32List&& data, GCGLuint srcOffset, GCGLuint srcLength);
    void uniform2uiv(WebGLUniformLocation*, Uint32List&& data, GCGLuint srcOffset, GCGLuint srcLength);
    void uniform3uiv(WebGLUniformLocation*, Uint32List&& data, GCGLuint srcOffset, GCGLuint srcLength);
    void uniform4uiv(WebGLUniformLocation*, Uint32List&& data, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix2x3fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix3x2fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix2x4fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix4x2fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix3x4fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void uniformMatrix4x3fv(WebGLUniformLocation*, GCGLboolean transpose, Float32List&& value, GCGLuint srcOffset, GCGLuint srcLength);
    void vertexAttribI4i(GCGLuint index, GCGLint x, GCGLint y, GCGLint z, GCGLint w);
    void vertexAttribI4iv(GCGLuint index, Int32List&& v);
    void vertexAttribI4ui(GCGLuint index, GCGLuint x, GCGLuint y, GCGLuint z, GCGLuint w);
    void vertexAttribI4uiv(GCGLuint index, Uint32List&& v);
    void vertexAttribIPointer(GCGLuint index, GCGLint size, GCGLenum type, GCGLsizei stride, GCGLint64 offset);

    using WebGLRenderingContextBase::uniform1fv;
    using WebGLRenderingContextBase::uniform2fv;
    using WebGLRenderingContextBase::uniform3fv;
    using WebGLRenderingContextBase::uniform4fv;
    void uniform1fv(WebGLUniformLocation* location, Float32List data, GLuint srcOffset, GLuint srcLength);
    void uniform2fv(WebGLUniformLocation* location, Float32List data, GLuint srcOffset, GLuint srcLength);
    void uniform3fv(WebGLUniformLocation* location, Float32List data, GLuint srcOffset, GLuint srcLength);
    void uniform4fv(WebGLUniformLocation* location, Float32List data, GLuint srcOffset, GLuint srcLength);

    using WebGLRenderingContextBase::uniform1iv;
    using WebGLRenderingContextBase::uniform2iv;
    using WebGLRenderingContextBase::uniform3iv;
    using WebGLRenderingContextBase::uniform4iv;
    void uniform1iv(WebGLUniformLocation* location, Int32List data, GLuint srcOffset, GLuint srcLength);
    void uniform2iv(WebGLUniformLocation* location, Int32List data, GLuint srcOffset, GLuint srcLength);
    void uniform3iv(WebGLUniformLocation* location, Int32List data, GLuint srcOffset, GLuint srcLength);
    void uniform4iv(WebGLUniformLocation* location, Int32List data, GLuint srcOffset, GLuint srcLength);

    using WebGLRenderingContextBase::uniformMatrix2fv;
    using WebGLRenderingContextBase::uniformMatrix3fv;
    using WebGLRenderingContextBase::uniformMatrix4fv;
    void uniformMatrix2fv(WebGLUniformLocation* location, GLboolean transpose, Float32List data, GLuint srcOffset, GLuint srcLength);
    void uniformMatrix3fv(WebGLUniformLocation* location, GLboolean transpose, Float32List data, GLuint srcOffset, GLuint srcLength);
    void uniformMatrix4fv(WebGLUniformLocation* location, GLboolean transpose, Float32List data, GLuint srcOffset, GLuint srcLength);

    // Writing to the drawing buffer
    void clear(GCGLbitfield mask) final;
    void vertexAttribDivisor(GCGLuint index, GCGLuint divisor);
    void drawArraysInstanced(GCGLenum mode, GCGLint first, GCGLsizei count, GCGLsizei instanceCount);
    void drawElementsInstanced(GCGLenum mode, GCGLsizei count, GCGLenum type, GCGLint64 offset, GCGLsizei instanceCount);
    void drawRangeElements(GCGLenum mode, GCGLuint start, GCGLuint end, GCGLsizei count, GCGLenum type, GCGLint64 offset);

    // Multiple render targets
    void drawBuffers(const Vector<GCGLenum>& buffers);
    void clearBufferiv(GCGLenum buffer, GCGLint drawbuffer, Int32List&& values, GCGLuint srcOffset);
    void clearBufferuiv(GCGLenum buffer, GCGLint drawbuffer, Uint32List&& values, GCGLuint srcOffset);
    void clearBufferfv(GCGLenum buffer, GCGLint drawbuffer, Float32List&& values, GCGLuint srcOffset);
    void clearBufferfi(GCGLenum buffer, GCGLint drawbuffer, GCGLfloat depth, GCGLint stencil);

    // Query objects
    RefPtr<WebGLQuery> createQuery();
    void deleteQuery(WebGLQuery*);
    GCGLboolean isQuery(WebGLQuery*);
    void beginQuery(GCGLenum target, WebGLQuery&);
    void endQuery(GCGLenum target);
    RefPtr<WebGLQuery> getQuery(GCGLenum target, GCGLenum pname);
    WebGLAny getQueryParameter(WebGLQuery&, GCGLenum pname);

    // Sampler objects
    RefPtr<WebGLSampler> createSampler();
    void deleteSampler(WebGLSampler*);
    GCGLboolean isSampler(WebGLSampler*);
    void bindSampler(GCGLuint unit, WebGLSampler*);
    void samplerParameteri(WebGLSampler&, GCGLenum pname, GCGLint param);
    void samplerParameterf(WebGLSampler&, GCGLenum pname, GCGLfloat param);
    WebGLAny getSamplerParameter(WebGLSampler&, GCGLenum pname);

    // Sync objects
    RefPtr<WebGLSync> fenceSync(GCGLenum condition, GCGLbitfield flags);
    GCGLboolean isSync(WebGLSync*);
    void deleteSync(WebGLSync*);
    GCGLenum clientWaitSync(WebGLSync&, GCGLbitfield flags, GCGLuint64 timeout);
    void waitSync(WebGLSync&, GCGLbitfield flags, GCGLint64 timeout);
    WebGLAny getSyncParameter(WebGLSync&, GCGLenum pname);

    // Transform feedback
    RefPtr<WebGLTransformFeedback> createTransformFeedback();
    void deleteTransformFeedback(WebGLTransformFeedback* id);
    GCGLboolean isTransformFeedback(WebGLTransformFeedback* id);
    void bindTransformFeedback(GCGLenum target, WebGLTransformFeedback* id);
    void beginTransformFeedback(GCGLenum primitiveMode);
    void endTransformFeedback();
    void transformFeedbackVaryings(WebGLProgram&, const Vector<String>& varyings, GCGLenum bufferMode);
    RefPtr<WebGLActiveInfo> getTransformFeedbackVarying(WebGLProgram&, GCGLuint index);
    void pauseTransformFeedback();
    void resumeTransformFeedback();

    // Uniform buffer objects and transform feedback buffers
    void bindBufferBase(GCGLenum target, GCGLuint index, WebGLBuffer*);
    void bindBufferRange(GCGLenum target, GCGLuint index, WebGLBuffer*, GCGLint64 offset, GCGLint64 size);
    WebGLAny getIndexedParameter(GCGLenum target, GCGLuint index);
    Optional<Vector<GCGLuint>> getUniformIndices(WebGLProgram&, const Vector<String>& uniformNames);
    WebGLAny getActiveUniforms(WebGLProgram&, const Vector<GCGLuint>& uniformIndices, GCGLenum pname);
    GCGLuint getUniformBlockIndex(WebGLProgram&, const String& uniformBlockName);
    WebGLAny getActiveUniformBlockParameter(WebGLProgram&, GCGLuint uniformBlockIndex, GCGLenum pname);
    WebGLAny getActiveUniformBlockName(WebGLProgram&, GCGLuint uniformBlockIndex);
    void uniformBlockBinding(WebGLProgram&, GCGLuint uniformBlockIndex, GCGLuint uniformBlockBinding);

    // Vertex array objects
    RefPtr<WebGLVertexArrayObject> createVertexArray();
    void deleteVertexArray(WebGLVertexArrayObject* vertexArray);
    GCGLboolean isVertexArray(WebGLVertexArrayObject* vertexArray);
    void bindVertexArray(WebGLVertexArrayObject* vertexArray);

    WebGLExtension* getExtension(const String&) final;
    Optional<Vector<String>> getSupportedExtensions() final;
    WebGLAny getParameter(GCGLenum pname) final;

    using WebGLRenderingContextBase::readPixels;
    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLintptr offset);
    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, ArrayBufferView& dstData, GLuint dstOffset);

    void renderbufferStorage(GCGLenum target, GCGLenum internalformat, GCGLsizei width, GCGLsizei height) final;
    void hint(GCGLenum target, GCGLenum mode) final;

private:
    WebGL2RenderingContext(CanvasBase&, GraphicsContextGLAttributes);
    WebGL2RenderingContext(CanvasBase&, Ref<GraphicsContextGLOpenGL>&&, GraphicsContextGLAttributes);

    bool isWebGL2() const final { return true; }

    RefPtr<ArrayBufferView> arrayBufferViewSliceFactory(const char* const functionName, const ArrayBufferView& data, unsigned startByte, unsigned bytelength);
    RefPtr<ArrayBufferView> sliceArrayBufferView(const char* const functionName, const ArrayBufferView& data, GCGLuint srcOffset, GCGLuint length);
    RefPtr<ArrayBufferView> sliceTypedArrayBufferView(const char* const functionName, RefPtr<ArrayBufferView>&, GCGLuint);

    void initializeVertexArrayObjects() final;
    GCGLint getMaxDrawBuffers() final;
    GCGLint getMaxColorAttachments() final;
    bool validateIndexArrayConservative(GCGLenum type, unsigned& numElementsRequired) final;
    bool validateBlendEquation(const char* functionName, GCGLenum mode) final;
    bool validateCapability(const char* functionName, GCGLenum cap) final;
    bool validateFramebufferFuncParameters(const char* functionName, GCGLenum target, GCGLenum attachment) final;
    bool validateFramebufferTarget(const char* functionName, GCGLenum target);
    bool validateNonDefaultFramebufferAttachment(const char* functionName, GCGLenum attachment);

    GCGLenum baseInternalFormatFromInternalFormat(GCGLenum internalformat);
    bool isIntegerFormat(GCGLenum internalformat);
    void initializeShaderExtensions();
    void initializeTransformFeedbackBufferCache();
    void initializeSamplerCache();

    bool validateTexStorageFuncParameters(GCGLenum target, GCGLsizei levels, GCGLenum internalFormat, GCGLsizei width, GCGLsizei height, const char* functionName);

    void uncacheDeletedBuffer(WebGLBuffer*) final;

    RefPtr<WebGLTransformFeedback> m_boundTransformFeedback;
    Vector<RefPtr<WebGLBuffer>> m_boundTransformFeedbackBuffers;

    HashMap<GCGLenum, RefPtr<WebGLQuery>> m_activeQueries;

    Vector<RefPtr<WebGLSampler>> m_boundSamplers;
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_CANVASRENDERINGCONTEXT(WebCore::WebGL2RenderingContext, isWebGL2())

#endif // WEBGL2
