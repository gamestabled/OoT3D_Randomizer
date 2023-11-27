#include "gold_skulltulas.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_CastleTown() {
    gsTable[OGC_GS] = new GoldSkulltulaData( //
        OGC_GS, 0x0E, 0x01, GS_AGE_ADULT, nullptr,
        // Original
        {
            GANONS_CASTLE_GROUNDS,
            GsScene{ 0x64 },
            Room{ 0 },
            // the terrain was lowered such that you can't get this GS with a simple sword slash
            { [] { return CanUse(DINS_FIRE) || CanUseProjectile || (CanJumpslash && LogicOutsideGanonsGS); } },
        },
        {
            // https://noclip.website/#oot3d/ganon_tou;ShareData=ALr~FT{seaUUE5j9h]xOWH}+/59;lKUWu_BUm5!=WEwp5UtS&q9S]};UTdAtWP
            { GANONS_CASTLE_GROUNDS,
              "Under ribcage of dead monster.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 940, 1652, 2225 },
                  { 0, 0, 2000 },
              },
              { [] {
                   return IsAdult && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) ||
                                      CanUse(STICKS) || CanUse(MEGATON_HAMMER) || CanUse(DINS_FIRE) || HasExplosives);
               },
                /*Glitched*/
                [] { return IsAdult && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE); } } },
            // https://noclip.website/#oot3d/ganon_tou;ShareData=ASux)UZ^tGTKx789Z8wM=UH15Q]EzHUmOj;T:(b{WFH;nUT[x]8((umUr_b2V[
            { GANONS_CASTLE_LEDGE,
              "On bottom of wall, westmost side of the ledge.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1310, 1630, 435 },
                  { 16384, -2000, 0 },
              },
              { [] { return IsAdult && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/ganon_tou;ShareData=AE{B-UuWpfULAkWUpI_HV&G+LQ|DL=UfpCl9XzPPV*@{d9o+k^UMMgQUcKIOVt
            { GANONS_CASTLE_LEDGE,
              "High up on wall, eastmost side of the ledge.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 500, 1830, 80 },
                  { 16384, 6000, 0 },
              },
              { [] { return IsAdult && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsAdult && (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });

    gsTable[HC_GS_STORMS_GROTTO] = new GoldSkulltulaData( //
        HC_GS_STORMS_GROTTO, 0x0E, 0x02, GS_AGE_BOTH, nullptr,
        // Original
        {
            HC_STORMS_GROTTO,
            GsScene{ 0x3E },
            Room{ 8 },
            { [] { return CanBlastOrSmash && HookshotOrBoomerang; },
              /*Glitched*/
              [] { return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } },
        },
        {
            // https://noclip.website/#oot3d/kakusiana;ShareData=AWtp=959wAT*cLI9mv[xV]stM54_LNUV1|ZT)v2hVaG2)Ut?]BUBnvn9iUK=V[
            { HC_STORMS_GROTTO,
              "In other small wall, but lower near the ground",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2020, 30, 1495 },
                  { 16384, -21500, 0 },
              },
              { [] { return CanBlastOrSmash; } } },
            // https://noclip.website/#oot3d/kakusiana;ShareData=AN1r3Ue,lj9e{?]UJmD$WA87-Q[9~MUgsF9Ue[vpVmEHk9iZXv9p={TUt;W)V[
            { HC_STORMS_GROTTO,
              "Hiding behind the Gossip Stone.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1810, -40, 700 },
                  { 0, 0, 0 },
              },
              { [] { return CanBlastOrSmash; } } },
        });

    gsTable[HC_GS_TREE] = new GoldSkulltulaData( //
        HC_GS_TREE, 0x0E, 0x04, GS_AGE_CHILD, nullptr,
        // Original
        {
            HYRULE_CASTLE_GROUNDS,
            GsScene{ 0x5F },
            Room{ 0 },
            { [] { return IsChild && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot15;ShareData=AG_=,9kia&UsUwHUDPaKV|wj4Q7NK!UtL:J9h:d/V&},79p3+K96!ie9Ig-$WP
            { HYRULE_CASTLE_GROUNDS,
              "On roof in small room by the first gate.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1160, 1310, 3192 },
                  { -32768, 0, 0 },
              },
              { [] { return IsChild && HookshotOrBoomerang; },
                /*Glitched*/
                [] { return IsChild && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } } },
            // https://noclip.website/#oot3d/spot15;ShareData=AI?Dh9wYQ_T$YP2919I1+$D[?RdW{ZUbjBGT~OB6V]G|KUh6$!T-O1890TK?WP
            { HYRULE_CASTLE_GROUNDS,
              "Up on side of tree near market entrance, reachable from elevated ground.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -145, 1390, 2960 },
                  { 16384, -24576, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot15;ShareData=Aa(hEUerSz9Q*g?T)Z}9V|3PF59jRJUW[aoUj^&(WCq6m9THi^9dCLoUlbmf+5
            { HYRULE_CASTLE_GROUNDS,
              "On water fence near gardens entrance.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 700, 1480, -685 },
                  { 16384, 0, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (CanJumpslash || CanUseProjectile || CanUse(DINS_FIRE));
              } } },
            // Can become inaccessible if the guards start blocking during day time.
            // TODO: Decide if the garden should always be open or if this should be removed.
            // https://noclip.website/#oot3d/nakaniwa;ShareData=AE$m_9vfZdTi+]mTbqHC+)/!KRcb;wUiU+_9L_kFVFpi?8o,BO9JmZv97ju?+5
            //{ HC_GARDEN,
            //  "Under the stone bridge where Zelda stands.",
            //  GsScene{ 0x4A },
            //  Room{ 0 },
            //  GsTimeCondition{ GS_TIME_ALWAYS },
            //  SettingRequirements{ nullptr },
            //  PosRot{
            //      { -430, 64, -10 },
            //      { -32768, 0, 0 },
            //  },
            //  { [] { return IsChild && (CanJumpslash || CanUseProjectile); },
            //    /*Glitched*/
            //    [] {
            //        return IsChild && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
            //               (HasBottle || (FaroresWind && FaroresWindAnywhere)) && CanUse(DINS_FIRE);
            //    } } },
        });

    gsTable[MARKET_GS_GUARD_HOUSE] = new GoldSkulltulaData( //
        MARKET_GS_GUARD_HOUSE, 0x0E, 0x08, GS_AGE_CHILD, nullptr,
        // Original
        {
            MARKET_GUARD_HOUSE,
            GsScene{ 0x4D },
            Room{ 0 },
            { [] { return IsChild; } },
        },
        {
            // https://noclip.website/#oot3d/market_night;ShareData=AT$t@9S(U2UC0hzUhi]H+93No6YS(:UmOkH9N]H:V9cY792]kG8!,(59W|XYVS
            { THE_MARKET,
              "On wooden ledge above bombchu shop.",
              GsScene{ 0x21 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -350, 160, 170 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((FaroresWind && FaroresWindAnywhere) || HasBottle) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // noclip scene missing
            { MARKET_MAN_IN_GREEN_HOUSE,
              "On middle of bed.",
              GsScene{ 0x2B },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 0, 25, 100 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild; } } },
            // https://noclip.website/#oot3d/market_alley_n;ShareData=AU)eV9o|;jUL6:N928[H+],]0Q9f,aUqeb9UU(UAVq^PsUevP5UNolQ93*OPV[
            { MARKET_BACK_ALLEY,
              "In center path by the two bottles.",
              GsScene{ 0x1F },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -135, 0, 1350 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((FaroresWind && FaroresWindAnywhere) || HasBottle) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // https://noclip.website/#oot3d/kakariko_impa;ShareData=AJ|?V9VI0r9RDIjUl$gu+kewuQz{hiUoP+ST{PbjVlP-b937f)T6ccD9TSagVS
            { MARKET_DOG_LADY_HOUSE,
              "On the bright sofa.",
              GsScene{ 0x35 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchRestrictedItems, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { -180, 24, 95 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((FaroresWind && FaroresWindAnywhere) || HasBottle) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // https://noclip.website/#oot3d/shrine_n;ShareData=ARY[cUvn{ZUWWGG9inOZWH&Gu5_])xUhVAWUj|TqVuCpjUf,o;9VGkCUGmsi+^
            { TOT_ENTRANCE,
              "In the leftmost corner of the path.",
              GsScene{ 0x24 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 670, 61, -1306 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((FaroresWind && FaroresWindAnywhere) || HasBottle) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // https://noclip.website/#oot3d/market_night;ShareData=AS$Z]95t~YT{KCK97ek,V~5*/QBEWSUVsVeUuZk@V-*?VUjOQ4UGLSy9p$uHVt
            { THE_MARKET,
              "Inside the crate to the right of bazaar door.",
              GsScene{ 0x21 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 500, 0, 350 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((FaroresWind && FaroresWindAnywhere) || HasBottle) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
        });
}
