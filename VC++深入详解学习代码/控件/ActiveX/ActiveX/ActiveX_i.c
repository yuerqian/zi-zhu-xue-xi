

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Sep 04 15:14:38 2017
 */
/* Compiler settings for ActiveX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ActiveXLib,0x4F3B047B,0x88CC,0x4FBF,0xB5,0x7B,0xD6,0xDF,0x6D,0xD8,0x42,0x29);


MIDL_DEFINE_GUID(IID, DIID__DActiveX,0x3F4DA7D3,0x959C,0x486E,0x95,0xAF,0xDA,0x7F,0xE3,0xD8,0xD2,0xB4);


MIDL_DEFINE_GUID(IID, DIID__DActiveXEvents,0x1E70B72B,0xCD4E,0x4C04,0xA8,0x3C,0x75,0x1F,0x38,0xCE,0xC8,0x07);


MIDL_DEFINE_GUID(CLSID, CLSID_ActiveX,0xD33F6026,0xFF75,0x4769,0x8E,0xEB,0xBB,0xC9,0xC8,0x8F,0xEE,0x03);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



