#ifndef _BUSINESS_SCRUBS_H_
#define _BUSINESS_SCRUBS_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_en_dns.h"
#include "z3D/actors/z_en_shopnuts.h"

void EnDns_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnDns_StartBurrow(EnDns* thisx);

void EnShopnuts_rInit(Actor* thisx, GlobalContext* globalCtx);

#endif //_BUSINESS_SCRUBS_H_
