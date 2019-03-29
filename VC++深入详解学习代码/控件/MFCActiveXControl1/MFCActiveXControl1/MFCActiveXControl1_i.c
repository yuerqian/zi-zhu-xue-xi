

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Sep 01 17:45:57 2017
 */
/* Compiler settings for MFCActiveXControl1.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_MFCActiveXControl1Lib,0xC8E4BF1B,0x5F04,0x4959,0xA4,0x2F,0xFF,0x51,0x1B,0x1D,0x8D,0xB6);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl1,0xD31C7349,0x7B99,0x4C52,0xAC,0x16,0x29,0xDB,0x80,0x73,0xE8,0xA9);


MIDL_DEFINE_GUID(IID, DIID__DMFCActiveXControl1Events,0x02E2BF7D,0x933A,0x460A,0xB8,0x44,0x95,0x20,0xDD,0x29,0x74,0x45);


MIDL_DEFINE_GUID(CLSID, CLSID_MFCActiveXControl1,0x3F3C61E6,0xADB6,0x482E,0x80,0x4C,0xAC,0x51,0xEE,0x88,0xDA,0x92);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



