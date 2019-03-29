

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Sep 07 18:14:46 2017
 */
/* Compiler settings for MFCActiveXControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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

MIDL_DEFINE_GUID(IID, LIBID_MFCActiveXControl控件Lib,0x23D7284D,0xB51D,0x4A24,0xA7,0xEF,0x20,0xC7,0xB3,0xCF,0xAC,0xA3);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl控件,0x76028768,0xB3C4,0x4406,0xBB,0x5F,0x94,0xB7,0xC4,0x13,0x67,0xFB);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl控件Events,0xBAD78B2F,0x154B,0x433F,0x8C,0x01,0x60,0x46,0x36,0xF6,0x1E,0x96);


MIDL_DEFINE_GUID(CLSID, CLSID_MFCActiveXControl控件,0x5D7FE87E,0x11DA,0x4E62,0x8B,0x9C,0x65,0x0A,0x4E,0xD9,0x0F,0xDA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



