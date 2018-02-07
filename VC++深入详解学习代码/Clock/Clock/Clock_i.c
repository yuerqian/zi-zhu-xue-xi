

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Aug 23 16:38:43 2017
 */
/* Compiler settings for Clock.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_ClockLib,0x15F9D509,0x7083,0x411B,0xA6,0xCF,0xE0,0x5B,0x23,0x0E,0x10,0xA8);


MIDL_DEFINE_GUID(IID, DIID__DClock,0x2E916B3D,0x01D2,0x4664,0xB6,0xB4,0x5E,0xD4,0x26,0xCB,0x1B,0xD0);


MIDL_DEFINE_GUID(IID, DIID__DClockEvents,0x73A9C65C,0x3333,0x4DEC,0x80,0xC8,0xDA,0xFF,0x63,0xFF,0xF0,0x4D);


MIDL_DEFINE_GUID(CLSID, CLSID_Clock,0x8499BC0B,0xDA67,0x4D10,0xA6,0x32,0xF6,0xC7,0x7B,0x93,0x88,0x87);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



