#include "gold_skulltulas.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_LostWoods() {
    gsTable[KF_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        KF_GS_BEAN_PATCH, 0x0C, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            KOKIRI_FOREST,
            GsScene{ 0x55 },
            Room{ 0 },
            { [] { return CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot04;ShareData=AGjzMUeeTY8,kfo92UOlV6i}DROj^WUq]=79HNZ3VzEfkUwJFUUIC_OUWu80+5
            { KOKIRI_FOREST,
              "Behind top of waterfall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 386, 206, -540 },
                  { 17000, 0, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) &&
                         CanUseProjectile;
              } } },
            // https://noclip.website/#oot3d/spot04;ShareData=ANg=7URPGY9W_)Z9ipZ0=J^abRSlpXUnJba9iloWV1]|UUd^xsT,WMTUNB8Q+^
            { KOKIRI_FOREST,
              "On the branch on top of Mido's House.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -620, 320, -635 },
                  { 30000, 0, 14000 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) &&
                          HookshotOrBoomerang;
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AAEK09n@?D9IUvKUQg+cV]4e!RROmfUuv23UtqX@Vb~!F9GH7VUJYak9uT={+^
            { KOKIRI_FOREST,
              "On ground behind shop.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 791, 0, -635 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) &&
                         CanChildAttack;
              } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AU5{:9k?9N8;CAa9THVkWQ0wDRGZ&LUria[9Pm=SVNj4OT)z-o9F(h696~?[=a
            { KF_OUTSIDE_DEKU_TREE,
              "On Deku Tree, his right side.",
              GsScene{ 0x55 },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 4540, 210, -1930 },
                  { -14000, -3000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[KF_GS_KNOW_IT_ALL_HOUSE] = new GoldSkulltulaData( //
        KF_GS_KNOW_IT_ALL_HOUSE, 0x0C, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            KOKIRI_FOREST,
            GsScene{ 0x55 },
            Room{ 0 },
            { [] {
                return IsChild && CanGetNightTimeGS && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) &&
                       CanChildAttack;
            } },
        },
        {
            // https://noclip.website/#oot3d/spot04;ShareData=AHbm^UvAdO9gZJ/T}AdYVXWUd6Wa(;UethxUPMhoVll@Z9KU&~9Gu:mUoowPV[
            { KOKIRI_FOREST,
              "Behind Link's House.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -70, 0, 1370 },
                  { 15000, 0, 6000 },
              },
              {} },
            // https://noclip.website/#oot3d/spot04;ShareData=AU6@WUqk?{9dz|)UV@~CWNEqY6oPX*UY^8XUB)[$VcyIT9iw[n9LZGgUl4|2V[
            { KOKIRI_FOREST,
              "Behind Twin's House.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1238, 0, 750 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/link;ShareData=AR0diUl&0PUP7NZ9lR6G+j}C9RGQW:Uhk0EUIfSqVTINbUq{B09I)F2Ur6;ZVS
            { KF_LINKS_HOUSE,
              "Inside Link's House, on the middle stump.",
              GsScene{ 0x34 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchRestrictedItems, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { -2, 20, 7 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           (HasBottle || (FaroresWind && FaroresWindAnywhere)) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AC_a[8:WU3Tt|P9Uvkvc=CPu!5)-;fUpSlw8npraV5~@/9woW+7$Bp-8)wf)V[
            { KOKIRI_FOREST,
              "In Kokiri Sword maze, in alcove before chest.",
              GsScene{ 0x55 },
              Room{ 2 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -737, 160, 1890 },
                  { 0, 0, -16384 },
              },
              {} },
        });

    gsTable[KF_GS_HOUSE_OF_TWINS] = new GoldSkulltulaData( //
        KF_GS_HOUSE_OF_TWINS, 0x0C, 0x04, GS_AGE_ADULT, nullptr,
        // Original
        {
            KOKIRI_FOREST,
            GsScene{ 0x55 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS &&
                         (CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::INTERMEDIATE) ||
                          CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot04;ShareData=AGl$PUhD(tT/BDl9jf,oWLcPVQ@=U,Ubcz/T;of@V-&odUV0kZ87v0-UmN=L+5
            { KOKIRI_FOREST,
              "By bean rupees.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1400, 300, -640 },
                  { 17000, 0, 10000 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS &&
                         ((CanAdultAttack && CanPlantBean(KOKIRI_FOREST)) || CanUse(LONGSHOT));
              } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AHNUUUV,+7T3l!a9wA0l=KLveQ^zZCUj1m|T:ujBWOnoqUpos?9C;y{UbNR~+^
            { KOKIRI_FOREST,
              "On top-left side of log to Lost Woods.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -402, 530, -1400 },
                  { 9000, -15000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AQx6GUm48!UIaP]9o0|T++G3nRP2jhUupP?USchVV6f2*Une&i9S~vdUR)r6V[
            { KOKIRI_FOREST,
              "On top of Link's House.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -52, 326, 1287 },
                  { 0, 8000, 4000 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) ||
                            CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot04;ShareData=AVNZ^UMQZ194HW^9lo~jWR)HoRE9b)UehYq96K2xVjC,YUlbBjT|wYmT{4!C+^
            { KF_OUTSIDE_DEKU_TREE,
              "On the underside of Deku Tree's nose.",
              GsScene{ 0x55 },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3960, 355, -1200 },
                  { 0, 0, -32768 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); } } },
        });

    gsTable[LW_GS_BEAN_PATCH_NEAR_BRIDGE] = new GoldSkulltulaData( //
        LW_GS_BEAN_PATCH_NEAR_BRIDGE, 0x0D, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            THE_LOST_WOODS,
            GsScene{ 0x5B },
            Room{ 5 },
            { [] { return CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot10;ShareData=AC-uMUhX;,UN+nE9f)[1=ZwuZQoocJUeYJeUn,[MVZ}7=T{)A!9zb?!Uh|_1V[
            { THE_LOST_WOODS,
              "Near original dirt patch, on top of closest tree.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1143, -12, 1220 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (HookshotOrBoomerang ||
                           ((CanJumpslash || CanUseProjectile || CanUse(DINS_FIRE)) && CanUse(HOVER_BOOTS)));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) ||
                            (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                             (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE))));
                } } },
            // https://noclip.website/#oot3d/spot10;ShareData=AR@C89bDJ+UvS[M9irQHV}eH=RK*KrUpBwiUp6Yn+P|}GUqJqNT;]jJ9el;eVt
            { THE_LOST_WOODS,
              "In grass behind ocarina memory game.",
              GsScene{ 0x5B },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1355, -180, 540 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot10;ShareData=AIR)TUblhc89aO08l^1+WD{i)6d0j8UpPRp9enJsVp$0DTemZ,UI4dNUgqW1+^
            { THE_LOST_WOODS,
              "At the top of the gate towards Goron City.",
              GsScene{ 0x5B },
              Room{ 2 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 800, 175, -1000 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot10;ShareData=AIAJa9pAd:8vbMr8x{4c=M*PpRb&TUUl5BE94Qwn+}]cDTZdiY9wjj_90$]4V[
            { THE_LOST_WOODS,
              "Underside of bridge between Kokiri Forest and Hyrule Field.",
              GsScene{ 0x5B },
              Room{ 5 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1200, -245, 1605 },
                  { 0, 0, -32768 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
        });

    gsTable[LW_GS_BEAN_PATCH_NEAR_THEATER] = new GoldSkulltulaData( //
        LW_GS_BEAN_PATCH_NEAR_THEATER, 0x0D, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            LW_BEYOND_MIDO,
            GsScene{ 0x5B },
            Room{ 6 },
            { [] { return CanPlantBugs && (CanChildAttack || (Scrubsanity.Is(SCRUBSANITY_OFF) && DekuShield)); } },
        },
        {
            // https://noclip.website/#oot3d/spot10;ShareData=AOFbh929eZT{]je9o,X8VUoF!REKOBUjN,BUkFxWVd3|RUVOHFT)Y:y92Qt8+^
            { LW_BEYOND_MIDO,
              "Behind tree near original location, hidden in grass.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 184, -20, -1752 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot10;ShareData=AFIF496*^T9MDYYUmnxdWQzF7RV!WlUmW!4UZhq6VZKk;9sWYQUE1+-9ncR;+^
            { THE_LOST_WOODS,
              "Behind the stone thing to Zora's River.",
              GsScene{ 0x5B },
              Room{ 3 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2300, 0, -848 },
                  { 0, 0, -16384 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/kakusiana;ShareData=ACzV9UnZHi8?mthUN!d2WT[fa5!6mTUmY:DT^EO@VW_un9Wi/09V/k4UpWpfV[
            { DEKU_THEATER,
              "In deku theater, to the left of audience.",
              GsScene{ 0x3E },
              Room{ 11 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3586, 1, 714 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot10;ShareData=AUDd/8o*duT[CM/9jf0PWNFm,6DX-=UWm-7T2A]-VYB]$Uc-4oSkJA)88V(s+^
            { LW_BEYOND_MIDO,
              "In fake log, opposite of the one leading to Deku Theater.",
              GsScene{ 0x5B },
              Room{ 4 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2200, 70, -1590 },
                  { 0, 0, 16384 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[LW_GS_ABOVE_THEATER] = new GoldSkulltulaData( //
        LW_GS_ABOVE_THEATER, 0x0D, 0x04, GS_AGE_ADULT, nullptr,
        // Original
        {
            LW_BEYOND_MIDO,
            GsScene{ 0x5B },
            Room{ 6 },
            { [] {
                 return IsAdult && CanGetNightTimeGS && CanAdultAttack &&
                        (CanPlantBean(LW_BEYOND_MIDO) ||
                         (LogicLostWoodsGSBean && CanUse(HOOKSHOT) &&
                          (CanUse(LONGSHOT) || CanUse(BOW) || CanUse(SLINGSHOT) || HasBombchus || CanUse(DINS_FIRE))));
             },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS &&
                         CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/spot10;ShareData=AM=~@9Bh1mUqsUQ9yuJ^V=9BmQ=:X/Up5;kUgeZaVv,vqUvBN0T]ETu8:Bts+^
            { LW_BEYOND_MIDO,
              "On top of tree by Deku Theater.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 245, 157, -1725 },
                  { 3000, 0, 0 },
              },
              { [] {
                   return IsAdult && CanGetNightTimeGS &&
                          (HookshotOrBoomerang || (CanPlantBean(LW_BEYOND_MIDO) && CanAdultAttack));
               },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/spot10;ShareData=ACzp?9SMY,UCpl}941h;WI7j!Q,XqyUrx!$UQWkRV1;7sUiRoGT(ovy9Z~AB+^
            { LW_BEYOND_MIDO,
              "Other side of upper part by original location.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 713, 210, -1390 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot10;ShareData=AV:,@Tn|f-8~[hl9jVVxWEY:WQ@tI-Usr{88$OUbVN@]6UXxxQS,U:{Teurk+C
            { THE_LOST_WOODS,
              "On slingshot target.",
              GsScene{ 0x5B },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1345, 50, -21 },
                  { 0, 0, 16384 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(HOOKSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot10;ShareData=ALDKeUsSAu9G$G}UC:p$=IB-g6bZ?MUn;bTUvFqqVpg$/9zC^+9L[XYUY@cPV[
            { THE_LOST_WOODS,
              "On top of tree closest to bridge, Business Scrub's side.",
              GsScene{ 0x5B },
              Room{ 5 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1102, -10, 1737 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS && ((CanUse(HOVER_BOOTS) && CanAdultAttack) || CanUse(LONGSHOT));
              } } },
        });

    gsTable[SFM_GS] = new GoldSkulltulaData( //
        SFM_GS, 0x0D, 0x08, GS_AGE_ADULT, nullptr,
        // Original
        {
            SACRED_FOREST_MEADOW,
            GsScene{ 0x56 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot05;ShareData=ALIP?9hH3t9KuQYUj2z;+!WX1RR,k1UiKczUr2}RVl5UU9iJ{3UR^a29r&?~V[
            { SFM_ENTRYWAY,
              "Hidden in grass by entrace from Lost Woods.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -342, 2, 2132 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot05;ShareData=ATy7RUiz|79gNGgUE9y;U5tVI6RrX*Uj8KXUq&1FVx/]89Y?IH9Sy)OUnYz{+d
            { SACRED_FOREST_MEADOW,
              "On left pillar before hallway towards warp platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -70, 158, -190 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot05;ShareData=AI--,UXTd7Uo^O19Vz]$Vw,9e6ZLF,T*3DCUbsLwV9HaQUccMp9xp4OUMwjxU!
            { SACRED_FOREST_MEADOW,
              "In the bottom center of deep pool of water before hallway towards warp platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 350, -215, -77 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsAdult && CanGetNightTimeGS &&
                          (HookshotOrBoomerang ||
                           ((CanUse(BOW) && CanUse(SLINGSHOT) && (CanUse(IRON_BOOTS) || SilverScale))));
               },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                           (CanUse(IRON_BOOTS) || SilverScale);
                } } },
            // https://noclip.website/#oot3d/spot05;ShareData=AS6j7Uh55x9bCbQUFDAMV,ft86d]JwUYhu~URY~7V[$mF9ajIu9gy$nUZTbH=a
            { SACRED_FOREST_MEADOW,
              "On Saria's stump.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 125, 500, -2960 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot05;ShareData=AKd6-9iVrF9VKJ?9x;(I+]8?C6F1L0UkbIW9UsjDWG,IRUbV~-9OhXG95buM=a
            { SACRED_FOREST_MEADOW,
              "Top of back of tree by Forest Temple entrance.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -190, 724, -3075 },
                  { 16383, -28000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot05;ShareData=ABGs^Ud5((UT4Y$931vAV:})v6PR+OUVRCVUMKMXWG^ddUcYcr9ZLBKUnR9[=a
            { SACRED_FOREST_MEADOW,
              "Corner of right ledge outside Forest Temple.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 372, 680, -3217 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });
}
