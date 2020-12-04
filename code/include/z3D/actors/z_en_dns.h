#ifndef _EN_DNS_H_
#define _EN_DNS_H_

#include "z3D/z3D.h"

struct EnDns;

typedef u32 (*EnDnsPurchaseableCheck)(struct EnDns*);
typedef void (*EnDnsSetRupeesAndFlags)(struct EnDns*);

typedef struct {
    /* 0x00 */ s16 itemPrice;
    /* 0x02 */ u16 itemAmount;
    /* 0x04 */ s32 getItemID;
    /* 0x08 */ EnDnsPurchaseableCheck purchaseableCheck;
    /* 0x0C */ EnDnsSetRupeesAndFlags setRupeesAndFlags;
} DnsItemEntry; // size = 0x10

typedef struct EnDns {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x64];
    /* 0x208 */ DnsItemEntry* dnsItemEntry;
    /* 0x20C */ char unk_20C[0x6A0];
} EnDns; // size 0x8AC

#endif //_EN_DNS_H_
