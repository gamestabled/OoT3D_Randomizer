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
    /* 0x1A4 */ void* action_fn;
    /* 0x1A8 */ char collider[0x58];
    /* 0x200 */ s16 dust_timer;
    /* 0x202 */ char unk_202;
    /* 0x203 */ u8 maintain_collider;
    /* 0x204 */ u8 stand_on_ground;
    /* 0x205 */ u8 drop_collectible;
    /* 0x206 */ char unk_206[0x2];
    /* 0x208 */ DnsItemEntry* dnsItemEntry;
    /* 0x20C */ char unk_20C[0x6A0];
} EnDns; // size 0x8AC

#endif //_EN_DNS_H_
