﻿#include "pch.h"
#include "AlembicImporter.h"
#include "aiLogger.h"
#include "aiContext.h"
#include "aiObject.h"
#include "aiSchema.h"
#include "aiXForm.h"
#include "aiPolyMesh.h"
#include "aiCamera.h"
#include "aiPoints.h"

#ifdef _WIN32
#   include <windows.h>
#   define aiBreak() DebugBreak()
#else // _WIN32
#   define aiBreak() __builtin_trap()
#endif // _WIN32


aiCLinkage aiExport void aiEnableFileLog(bool on, const char *path)
{
    aiLogger::Enable(on, path);
}

aiCLinkage aiExport void aiCleanup()
{
#ifdef aiWithTBB
#else
    aiThreadPool::releaseInstance();
#endif
}

aiCLinkage aiExport aiContext* aiCreateContext(int uid)
{
    auto ctx = aiContext::create(uid);
    return ctx;
}

aiCLinkage aiExport void aiDestroyContext(aiContext* ctx)
{
    if (ctx)
    {
        aiContext::destroy(ctx);
    }
}


aiCLinkage aiExport bool aiLoad(aiContext* ctx, const char *path)
{
    return (ctx ? ctx->load(path) : false);
}

aiCLinkage aiExport void aiSetConfig(aiContext* ctx, const aiConfig* conf)
{
    if (ctx)
    {
        ctx->setConfig(*conf);
    }
}

aiCLinkage aiExport float aiGetStartTime(aiContext* ctx)
{
    return (ctx ? ctx->getStartTime() : 0.0f);
}

aiCLinkage aiExport float aiGetEndTime(aiContext* ctx)
{
    return (ctx ? ctx->getEndTime() : 0.0f);
}

aiCLinkage aiExport aiObject* aiGetTopObject(aiContext* ctx)
{
    return (ctx ? ctx->getTopObject() : 0);
}

aiCLinkage aiExport void aiDestroyObject(aiContext* ctx, aiObject* obj)
{
    if (ctx)
    {
        ctx->destroyObject(obj);
    }
}

aiCLinkage aiExport void aiUpdateSamples(aiContext* ctx, float time)
{
    if (ctx)
    {
        ctx->updateSamples(time);
    }
}

aiCLinkage aiExport void aiEnumerateChild(aiObject *obj, aiNodeEnumerator e, void *userData)
{
    if (!obj)
    {
        return;
    }
    
    size_t n = obj->getNumChildren();

    for (size_t i = 0; i < n; ++i)
    {
        try
        {
            aiObject *child = obj->getChild(i);
            e(child, userData);
        }
        catch (Alembic::Util::Exception e)
        {
            DebugLog("aiEnumerateChlid: %s", e.what());
        }
    }
}

aiCLinkage aiExport const char* aiGetNameS(aiObject* obj)
{
    return (obj ? obj->getName() : "");
}

aiCLinkage aiExport const char* aiGetFullNameS(aiObject* obj)
{
    return (obj ? obj->getFullName() : "");
}

aiCLinkage aiExport void aiSetDestroyCallback(aiObject* obj, aiDestroyCallback cb, void* arg)
{
    if (obj)
    {
        obj->setDestroyCallback(cb, arg);
    }
}

aiCLinkage aiExport void aiSchemaSetSampleCallback(aiSchemaBase* schema, aiSampleCallback cb, void* arg)
{
    if (schema)
    {
        schema->setSampleCallback(cb, arg);
    }
}

aiCLinkage aiExport void aiSchemaSetConfigCallback(aiSchemaBase* schema, aiConfigCallback cb, void* arg)
{
    if (schema)
    {
        schema->setConfigCallback(cb, arg);
    }
}

aiCLinkage aiExport const aiSampleBase* aiSchemaUpdateSample(aiSchemaBase* schema, float time)
{    
    return (schema ? schema->updateSample(time) : 0);
}

aiCLinkage aiExport const aiSampleBase* aiSchemaGetSample(aiSchemaBase* schema, float time)
{
    return (schema ? schema->findSample(time) : 0);
}


aiCLinkage aiExport bool aiHasXForm(aiObject* obj)
{
    return (obj ? obj->hasXForm() : false);
}

aiCLinkage aiExport aiXForm* aiGetXForm(aiObject* obj)
{
    return (obj ? &(obj->getXForm()) : 0);
}

aiCLinkage aiExport void aiXFormGetData(aiXFormSample* sample, aiXFormData *outData)
{
    if (sample)
    {
        sample->getData(*outData);
    }
}


aiCLinkage aiExport bool aiHasPolyMesh(aiObject* obj)
{
    return (obj ? obj->hasPolyMesh() : false);
}

aiCLinkage aiExport aiPolyMesh* aiGetPolyMesh(aiObject* obj)
{
    return (obj ? &(obj->getPolyMesh()) : 0);
}

aiCLinkage aiExport void aiPolyMeshGetSummary(aiPolyMesh* schema, aiMeshSummary* summary)
{
    if (schema)
    {
        schema->getSummary(*summary);
    }
}

aiCLinkage aiExport void aiPolyMeshGetSampleSummary(aiPolyMeshSample* sample, aiMeshSampleSummary* summary, bool forceRefresh)
{
    if (sample)
    {
        sample->getSummary(forceRefresh, *summary);
    }
}

aiCLinkage aiExport int aiPolyMeshGetVertexBufferLength(aiPolyMeshSample* sample, int splitIndex)
{
    return (sample ? sample->getVertexBufferLength(splitIndex) : 0);
}

aiCLinkage aiExport void aiPolyMeshFillVertexBuffer(aiPolyMeshSample* sample, int splitIndex, aiMeshSampleData* data)
{
    if (sample)
    {
        sample->fillVertexBuffer(splitIndex, *data);
    }
}

aiCLinkage aiExport int aiPolyMeshPrepareSubmeshes(aiPolyMeshSample* sample, const aiFacesets* facesets)
{
    return (sample ? sample->prepareSubmeshes(*facesets) : 0);
}

aiCLinkage aiExport int aiPolyMeshGetSplitSubmeshCount(aiPolyMeshSample* sample, int splitIndex)
{
    return (sample ? sample->getSplitSubmeshCount(splitIndex) : 0);
}

aiCLinkage aiExport bool aiPolyMeshGetNextSubmesh(aiPolyMeshSample* sample, aiSubmeshSummary* summary)
{
    return (sample ? sample->getNextSubmesh(*summary) : false);
}

aiCLinkage aiExport void aiPolyMeshFillSubmeshIndices(aiPolyMeshSample* sample, const aiSubmeshSummary* summary, aiSubmeshData* data)
{
    if (sample)
    {
        sample->fillSubmeshIndices(*summary, *data);
    }
}


aiCLinkage aiExport bool aiHasCamera(aiObject* obj)
{
    return (obj ? obj->hasCamera() : false);
}

aiCLinkage aiExport aiCamera* aiGetCamera(aiObject* obj)
{
    return (obj ? &(obj->getCamera()) : 0);
}

aiCLinkage aiExport void aiCameraGetData(aiCameraSample* sample, aiCameraData *outData)
{
    if (sample)
    {
        sample->getData(*outData);
    }
}


aiCLinkage aiExport bool aiHasPoints(aiObject* obj)
{
    return (obj ? obj->hasPoints() : false);
}

aiCLinkage aiExport aiPoints* aiGetPoints(aiObject* obj)
{
    return (obj ? &(obj->getPoints()) : 0);
}

aiCLinkage aiExport int aiPointsGetCount(aiPointsSample *sample)
{
    return (sample ? sample->getPointsCount() : 0);
}

aiCLinkage aiExport void aiPointsGetSampleSummary(aiPointsSample* sample, aiPointsSampleSummary *summary)
{
    if (sample)
    {
        sample->getSummary(*summary);
    }
}

aiCLinkage aiExport void aiPointsGetData(aiPointsSample* sample, aiPointsSampleData *outData)
{
    if (sample)
    {
        sample->getData(*outData);
    }
}

aiCLinkage aiExport int aiPointsGetPeakVertexCount(aiPoints *schema)
{
    return (schema ? schema->getPeakVertexCount() : 0);
}

aiCLinkage aiExport void aiPointsGetRawData(aiPointsSample* sample, aiPointsSampleData *outData)
{
    if (sample)
    {
        sample->getRawData(*outData);
    }
}

#ifdef aiSupportTextureData

#include "GraphicsDevice/aiGraphicsDevice.h"

aiCLinkage aiExport bool aiPointsCopyPositionsToTexture(aiPointsSampleData *data, void *tex, int width, int height, aiTextureFormat fmt)
{
    if (data == nullptr)
    {
        return false;
    }

    if (fmt == aiTextureFormat_ARGBFloat)
    {
        return aiWriteTextureWithConversion(tex, width, height, fmt, data->positions, data->count,
            [](void *dst, const abcV3 *src, int i) {
                ((abcV4*)dst)[i] = abcV4(src[i].x, src[i].y, src[i].z, 0.0f);
            });
    }
    else
    {
        DebugLog("aiPointsCopyPositionsToTexture(): format must be ARGBFloat");
        return false;
    }
}

aiCLinkage aiExport bool aiPointsCopyIDsToTexture(aiPointsSampleData *data, void *tex, int width, int height, aiTextureFormat fmt)
{
    if (data == nullptr)
    {
        return false;
    }

    if (fmt == aiTextureFormat_RInt)
    {
        return aiWriteTextureWithConversion(tex, width, height, fmt, data->ids, data->count,
            [](void *dst, const uint64_t *src, int i) {
                ((int32_t*)dst)[i] = (int32_t)(src[i]);
            });
    }
    else if (fmt == aiTextureFormat_RFloat)
    {
        return aiWriteTextureWithConversion(tex, width, height, fmt, data->ids, data->count,
            [](void *dst, const uint64_t *src, int i) {
                ((float*)dst)[i] = (float)(src[i]);
            });
    }
    else
    {
        DebugLog("aiPointsCopyIDsToTexture(): format must be RFloat or RInt");
        return false;
    }
}

#endif // aiSupportTextureData
