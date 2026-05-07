#ifndef _EN_DNS_H_
#define _EN_DNS_H_

#include "z3D/z3D.h"

typedef enum EnDnsType {
    DNS_TYPE_DEKU_NUTS_5,
    DNS_TYPE_DEKU_STICKS_1,
    DNS_TYPE_HEART_PIECE,
    DNS_TYPE_DEKU_SEEDS_30,
    DNS_TYPE_DEKU_SHIELD,
    DNS_TYPE_BOMBS_5,
    DNS_TYPE_ARROWS_30,
    DNS_TYPE_RED_POTION,
    DNS_TYPE_GREEN_POTION,
    DNS_TYPE_DEKU_STICK_UPGRADE,
    DNS_TYPE_DEKU_NUT_UPGRADE,
    DNS_TYPE_MAX,
} EnDnsType;

typedef enum EnDnsCanBuyResult {
    DNS_CANBUY_RESULT_NEED_RUPEES,
    DNS_CANBUY_RESULT_CAPACITY_FULL,
    DNS_CANBUY_RESULT_SUCCESS_NEW_ITEM,
    DNS_CANBUY_RESULT_CANT_GET_NOW,
    DNS_CANBUY_RESULT_SUCCESS,
} EnDnsCanBuyResult;

struct EnDns;

typedef void (*EnDnsActionFunc)(struct EnDns* this, GlobalContext* globalCtx);
typedef u32 (*EnDnsCanBuyFunc)(struct EnDns*);
typedef void (*EnDnsPaymentFunc)(struct EnDns*);

typedef struct {
    /* 0x00 */ s16 itemPrice;
    /* 0x02 */ u16 itemAmount;
    /* 0x04 */ s32 getItemID;
    /* 0x08 */ EnDnsCanBuyFunc canBuy;
    /* 0x0C */ EnDnsPaymentFunc payment;
} DnsItemEntry; // size = 0x10

typedef struct EnDns {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnDnsActionFunc action_fn;
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
