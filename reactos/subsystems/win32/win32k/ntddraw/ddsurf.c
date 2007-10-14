/*
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * PURPOSE:          Native DirectDraw implementation
 * FILE:             subsys/win32k/ntddraw/dd.c
 * PROGRAMER:        Magnus Olsen (greatlord@reactos.org)
 * REVISION HISTORY:
 *       19/7-2006  Magnus Olsen
 */

#include <w32k.h>
#include <reactos/drivers/directx/dxg.h>

//#define NDEBUG
#include <debug.h>

extern PDRVFN gpDxFuncs;

typedef DWORD (NTAPI *PGD_DDALPHABLT)(HANDLE, HANDLE, PDD_BLTDATA);
typedef BOOL (NTAPI *PGD_DDATTACHSURFACE)(HANDLE, HANDLE);
typedef DWORD (NTAPI *PGD_DXDDUNATTACHSURFACE)(HANDLE, HANDLE);
typedef DWORD (NTAPI *PGD_DXDDDESTROYSURFACE)(HANDLE, BOOL);
typedef DWORD (NTAPI *PGD_DXDDFLIP)(HANDLE, HANDLE, HANDLE, HANDLE, PDD_FLIPDATA);
/* Does not exists in win32k or dxg.sys PDD_SURFCB_SETCLIPLIST  SetClipList; */
typedef DWORD (NTAPI *PGD_DXDDLOCK)(HANDLE, PDD_LOCKDATA, HDC);
typedef DWORD (NTAPI *PGD_DXDDUNLOCK(HANDLE, PDD_UNLOCKDATA );
typedef DWORD (NTAPI *PGD_DDBLT)(HANDLE, HANDLE, PDD_BLTDATA);
typedef DWORD (NTAPI *PGD_DXDDSETCOLORKEY)(HANDLE, PDD_SETCOLORKEYDATA);
typedef DWORD (NTAPI *PGD_DDADDATTACHEDSURFACE)(HANDLE, HANDLE,PDD_ADDATTACHEDSURFACEDATA);
typedef DWORD (NTAPI *PGD_DXDDGETBLTSTATUS)(HANDLE, PDD_GETBLTSTATUSDATA);
typedef DWORD (NTAPI *PGD_DXDDGETFLIPSTATUS)(HANDLE, PDD_GETFLIPSTATUSDATA);
typedef DWORD (NTAPI *PGD_DXDDUPDATEOVERLAY)(HANDLE, HANDLE, PDD_UPDATEOVERLAYDATA);
typedef DWORD (NTAPI *PGD_DXDDSETOVERLAYPOSITION)(HANDLE, HANDLE, PDD_SETOVERLAYPOSITIONDATA);
/* from MSDN LPVOID  reserved4; are not inuse */
/* Does not exists in win32k or dxg.sys PDD_SURFCB_SETPALETTE  SetPalette */

#define DXG_GET_INDEX_FUNCTION(INDEX, FUNCTION) \
    if (gpDxFuncs) \
    { \
        for (i = 0; i <= DXG_INDEX_DxDdIoctl; i++) \
        { \
            if (gpDxFuncs[i].iFunc == INDEX)  \
            { \
                FUNCTION = (VOID *)gpDxFuncs[i].pfn;  \
                break;  \
            }  \
        } \
    }

/************************************************************************/
/* NtGdiDdDestroySurface                                                */
/************************************************************************/
DWORD
STDCALL
NtGdiDdDestroySurface(HANDLE hSurface, BOOL bRealDestroy)
{
    PGD_DXDDDESTROYSURFACE pfnDdDestroySurface = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdDestroySurface, pfnDdDestroySurface);

    if (pfnDdDestroySurface == NULL)
    {
        DPRINT1("Warring no pfnDdDestroySurface");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdDestroySurface");
    return pfnDdDestroySurface(hSurface, bRealDestroy);
}

/************************************************************************/
/* NtGdiDdFlip                                                          */
/************************************************************************/
DWORD
STDCALL
NtGdiDdFlip(HANDLE hSurfaceCurrent,
            HANDLE hSurfaceTarget,
            HANDLE hSurfaceCurrentLeft,
            HANDLE hSurfaceTargetLeft,
            PDD_FLIPDATA puFlipData)
{
    PGD_DXDDDESTROYSURFACE pfnDdDdFlip = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdFlip, pfnDdDdFlip);

    if (pfnDdDdFlip == NULL)
    {
        DPRINT1("Warring no pfnDdDdFlip");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdDdFlip");
    return pfnDdDdFlip(hSurfaceCurrent, hSurfaceTarget, hSurfaceCurrentLeft, hSurfaceTargetLeft, puFlipData);
}

/************************************************************************/
/* NtGdiDdUnlock                                                        */
/************************************************************************/
DWORD
STDCALL
NtGdiDdLock(HANDLE hSurface,
            PDD_LOCKDATA puLockData,
            HDC hdcClip)
{
    PGD_DXDDLOCK pfnDdLock = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdLock, pfnDdLock);

    if (pfnDdLock == NULL)
    {
        DPRINT1("Warring no pfnDdLock");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdLock");
    return pfnDdLock(hSurface, puLockData, hdcClip);
}

/************************************************************************/
/* NtGdiDdunlock                                                        */
/************************************************************************/
DWORD
STDCALL
NtGdiDdUnlock(HANDLE hSurface, 
              PDD_UNLOCKDATA puUnlockData)
{
    PGD_DXDDUNLOCK pfnDdUnlock = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdUnlock, pfnDdUnlock);

    if (pfnDdLock == NULL)
    {
        DPRINT1("Warring no pfnDdUnlock");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdUnlock");
    return pfnDdUnlock(hSurface, puUnlockData);
}

/************************************************************************/
/* NtGdiDdBlt                                                           */
/************************************************************************/
DWORD
STDCALL
NtGdiDdBlt(HANDLE hSurfaceDest,
           HANDLE hSurfaceSrc,
           PDD_BLTDATA puBltData)
{
    PGD_DDBLT pfnDdBlt = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdBlt, pfnDdBlt);

    if (pfnDdBlt == NULL)
    {
        DPRINT1("Warring no pfnDdBlt");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys DdBlt");
    return pfnDdBlt(hSurfaceDest,hSurfaceSrc,puBltData);
}

/************************************************************************/
/* NtGdiDdSetColorKey                                                   */
/************************************************************************/
DWORD
STDCALL
NtGdiDdSetColorKey(HANDLE hSurface,
                   PDD_SETCOLORKEYDATA puSetColorKeyData)
{
    PGD_DXDDSETCOLORKEY pfnDdSetColorKey;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdSetColorKey, pfnDdSetColorKey);

    if (pfnDdSetColorKey == NULL)
    {
        DPRINT1("Warring no pfnDdSetColorKey");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdSetColorKey");
    return pfnDdSetColorKey(hSurface,puSetColorKeyData);

}

/************************************************************************/
/* NtGdiDdAddAttachedSurface                                            */
/************************************************************************/

DWORD
STDCALL
NtGdiDdAddAttachedSurface(HANDLE hSurface,
                          HANDLE hSurfaceAttached,
                          PDD_ADDATTACHEDSURFACEDATA puAddAttachedSurfaceData)
{
    PGD_DDADDATTACHEDSURFACE pfnDdAddAttachedSurface = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdAddAttachedSurface, pfnDdAddAttachedSurface);

    if (pfnDdAddAttachedSurface == NULL)
    {
        DPRINT1("Warring no pfnDdAddAttachedSurface");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys DdAddAttachedSurface");
    return pfnDdAddAttachedSurface(hSurface,hSurfaceAttached,puAddAttachedSurfaceData);
}

/************************************************************************/
/* NtGdiDdGetBltStatus                                                  */
/************************************************************************/
DWORD
STDCALL
NtGdiDdGetBltStatus(HANDLE hSurface,
                    PDD_GETBLTSTATUSDATA puGetBltStatusData)
{
    PGD_DXDDGETBLTSTATUS pfnDdGetBltStatus = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdGetBltStatus, pfnDdGetBltStatus);

    if (pfnDdGetBltStatus == NULL)
    {
        DPRINT1("Warring no pfnDdGetBltStatus");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdGetBltStatus");
    return pfnDdGetBltStatus(hSurface,puGetBltStatusData);
}

/************************************************************************/
/* NtGdiDdGetFlipStatus                                                 */
/************************************************************************/
DWORD
STDCALL
NtGdiDdGetFlipStatus(HANDLE hSurface,
                     PDD_GETFLIPSTATUSDATA puGetFlipStatusData)
{
    PGD_DXDDGETFLIPSTATUS pfnDdGetFlipStatus = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdGetFlipStatus, pfnDdGetFlipStatus);

    if (pfnDdGetFlipStatus == NULL)
    {
        DPRINT1("Warring no pfnDdGetFlipStatus");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdGetFlipStatus");
    return pfnDdGetFlipStatus(hSurface,puGetFlipStatusData);
}

/************************************************************************/
/* NtGdiDdUpdateOverlay                                                 */
/************************************************************************/
DWORD
STDCALL
NtGdiDdUpdateOverlay(HANDLE hSurfaceDestination,
                     HANDLE hSurfaceSource,
                     PDD_UPDATEOVERLAYDATA puUpdateOverlayData)
{
    PGD_DXDDUPDATEOVERLAY pfnDdUpdateOverlay = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdUpdateOverlay, pfnDdUpdateOverlay);

    if (pfnDdUpdateOverlay == NULL)
    {
        DPRINT1("Warring no pfnDdUpdateOverlay");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdUpdateOverlay");
    return pfnDdUpdateOverlay(hSurfaceDestination,hSurfaceSource,puUpdateOverlayData);
}

/************************************************************************/
/* NtGdiDdSetOverlayPosition                                            */
/************************************************************************/

DWORD
STDCALL
NtGdiDdSetOverlayPosition(HANDLE hSurfaceSource,
                          HANDLE hSurfaceDestination,
                          PDD_SETOVERLAYPOSITIONDATA puSetOverlayPositionData)
{
    PGD_DXDDUPDATEOVERLAY pfnDdSetOverlayPosition = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdSetOverlayPosition, pfnDdSetOverlayPosition);

    if (pfnDdSetOverlayPosition == NULL)
    {
        DPRINT1("Warring no pfnDdSetOverlayPosition");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdSetOverlayPosition");
    return pfnDdSetOverlayPosition(hSurfaceSource,hSurfaceDestination,puSetOverlayPositionData);
}

/************************************************************************/
/* This is not part of the ddsurface interface but it have              */
/* deal with the surface                                                */
/************************************************************************/


/************************************************************************/
/* NtGdiDdAlphaBlt                                                      */
/************************************************************************/
DWORD
STDCALL
NtGdiDdAlphaBlt(HANDLE hSurfaceDest,
                HANDLE hSurfaceSrc,
                PDD_BLTDATA puBltData)
{
    PGD_DDALPHABLT pfnDdAlphaBlt = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdAlphaBlt, pfnDdAlphaBlt);

    if (pfnDdAlphaBlt == NULL)
    {
        DPRINT1("Warring no pfnDdAlphaBlt");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys DdAlphaBlt");
    return pfnDdAlphaBlt(hSurfaceDest,hSurfaceSrc,puBltData);
}

/************************************************************************/
/* NtGdiDdAttachSurface                                                 */
/************************************************************************/
BOOL
STDCALL
NtGdiDdAttachSurface(HANDLE hSurfaceFrom,
                     HANDLE hSurfaceTo
)
{
    PGD_DDATTACHSURFACE pfnDdAttachSurface = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdAttachSurface, pfnDdAttachSurface);

    if (pfnDdAttachSurface == NULL)
    {
        DPRINT1("Warring no pfnDdAttachSurface");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdAttachSurface");
    return pfnDdAttachSurface(hSurfaceFrom,hSurfaceTo);
}

/************************************************************************/
/* NtGdiDdUnattachSurface                                               */
/************************************************************************/
VOID
STDCALL
NtGdiDdUnattachSurface(HANDLE hSurface,
                       HANDLE hSurfaceAttached)
{
    PGD_DXDDUNATTACHSURFACE pfnDdUnattachSurface = NULL;
    INT i;

    DXG_GET_INDEX_FUNCTION(DXG_INDEX_DxDdUnattachSurface, pfnDdUnattachSurface);

    if (pfnDdUnattachSurface == NULL)
    {
        DPRINT1("Warring no pfnDdUnattachSurface");
        return DDHAL_DRIVER_NOTHANDLED;
    }

    DPRINT1("Calling on dxg.sys pfnDdUnattachSurface");
    return pfnDdUnattachSurface(hSurface,hSurfaceAttached);
}


