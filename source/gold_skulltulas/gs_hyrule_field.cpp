#include "gold_skulltulas.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_HyruleField() {
    gsTable[HF_GS_COW_GROTTO] = new GoldSkulltulaData( //
        HF_GS_COW_GROTTO, 0x0A, 0x01, GS_AGE_BOTH, nullptr,
        // Original
        {
            HF_COW_GROTTO,
            GsScene{ 0x3E },
            Room{ 4 },
            { [] { return HasFireSource && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return (CanUse(STICKS) && Bombs && CanSurviveDamage &&
                          CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) &&
                         HookshotOrBoomerang;
              } },
        },
        {
            // https://noclip.website/#oot3d/spot00;ShareData=Aar+dT(kb&8?M?IUrCl!=j/;nRQ$5VUt=DfT+GZm+;5F|9vatd8ReooT4-DUV[
            { HYRULE_FIELD,
              "On water-fence thing northwest of Hyrule Field, where the water exits.",
              GsScene{ 0x51 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -5875, -250, 820 },
                  { 16384, 16384, 0 },
              },
              { [] { return CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot00;ShareData=AUb}kT|H0BT}R}89u3yE=cB&nREu|iUsm?&ULb5cV66q{UY)+W9R*=nT}(laWP
            { HYRULE_FIELD,
              "On the top end of west stone wall that goes out from Lon Lon Ranch.",
              GsScene{ 0x51 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -4980, 46, 6540 },
                  { 0, 0, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/kakusiana;ShareData=AGb_tUnp+y9WjZcUAYBbWGty66V?jwUjU$^Uv@^7Vcm~-9hnRQ9mVqSUWM/T+5
            { HF_INSIDE_FENCE_GROTTO,
              "In the middle-left puddle.",
              GsScene{ 0x3E },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1170, -30, -260 },
                  { 0, 0, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
        });

    gsTable[HF_GS_NEAR_KAK_GROTTO] = new GoldSkulltulaData( //
        HF_GS_NEAR_KAK_GROTTO, 0x0A, 0x02, GS_AGE_BOTH, nullptr,
        // Original
        {
            HF_NEAR_KAK_GROTTO,
            GsScene{ 0x3E },
            Room{ 13 },
            { [] { return HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot00;ShareData=AFBaDUlPY;S]g/zTBDKeVM*6bQr:jNUWoci9Yo]9V2+lD8Yj^lUNfvXUd$@wV[
            { HYRULE_FIELD,
              "On Triforce emblem by market entrance.",
              GsScene{ 0x51 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 0, 470, 582 },
                  { 16384, 0, 0 },
              },
              { [] {
                  return CanGetNightTimeGS &&
                         ((IsChild && ((CanJumpslash && CanTakeDamage) || CanUse(SLINGSHOT) || CanUse(BOOMERANG) ||
                                       CanUse(BOW) || CanUse(HOOKSHOT) || Bombs || CanUse(DINS_FIRE))) ||
                          (IsAdult && CanUse(LONGSHOT)));
              } } },
            // https://noclip.website/#oot3d/spot00;ShareData=AGR|q9oka(UkWg)9fVJbV|h-!5|aSVUWgeFUcs-@WI]$4UYQY|UUQyq9UZZnWP
            { HYRULE_FIELD,
              "On top of middle of stone wall east of Lon Lon Ranch.",
              GsScene{ 0x51 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1435, 438, 5930 },
                  { 0, 0, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/spot00;ShareData=APzkMUwX9H9KRR3Ui=4XWZlfPQ*N}eUu?@1Up)[CVqi($9lxNW9LIMEUkzqKV[
            { HYRULE_FIELD,
              "Below bridge between Market and Kakariko.",
              GsScene{ 0x51 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1935, -160, 820 },
                  { 0, 0, 0 },
              },
              { [] {
                   return CanUse(SLINGSHOT) || CanUse(BOOMERANG) || CanUse(BOW) || CanUse(HOOKSHOT) ||
                          CanUse(DINS_FIRE);
               },
                /*Glitched*/
                [] {
                    return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                           CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);
                } } },
        });

    gsTable[LLR_GS_BACK_WALL] = new GoldSkulltulaData( //
        LLR_GS_BACK_WALL, 0x0B, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            LON_LON_RANCH,
            GsScene{ 0x63 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsChild && CanGetNightTimeGS &&
                         CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/spot20;ShareData=AHn)a95d3PS-;Xc8gn$yV(O+RRe(Z,UldSTUI!84V4*0rTVPLFUBi819g{4W+C
            { LON_LON_RANCH,
              "On bench under rain shed: Left-Left",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 840, 23, 285 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/souko;ShareData=ACGJ~Tpnf~9po2SUXedQ+8yOlRJBsfUn;/GUa{]aV;aD99wgW-8tK;PTv2b0+d
            { LLR_TOWER,
              "In milk crate near left wall.",
              GsScene{ 0x4C },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -370, -10, -103 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)); } } },
        });

    gsTable[LLR_GS_RAIN_SHED] = new GoldSkulltulaData( //
        LLR_GS_RAIN_SHED, 0x0B, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            LON_LON_RANCH,
            GsScene{ 0x63 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS; } },
        },
        {
            // https://noclip.website/#oot3d/spot20;ShareData=AHn)a95d3PS-;Xc8gn$yV(O+RRe(Z,UldSTUI!84V4*0rTVPLFUBi819g{4W+C
            { LON_LON_RANCH,
              "On bench under rain shed: Middle-Left",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 795, 23, 285 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/spot20;ShareData=AY}tUUv&nwS9_t58HLgvWFj~M6zyCNUbXrFUuT!cV4[9vS9tuI9m)2@UX/[xVt
            { LON_LON_RANCH,
              "On top of rain shed.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return (HookshotAsChild && AgeItemsInLogic) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::INTERMEDIATE) &&
                          GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE));
              } },
              PosRot{
                  { 740, 157, 250 },
                  { 2000, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });

    gsTable[LLR_GS_HOUSE_WINDOW] = new GoldSkulltulaData( //
        LLR_GS_HOUSE_WINDOW, 0x0B, 0x04, GS_AGE_CHILD, nullptr,
        // Original
        {
            LON_LON_RANCH,
            GsScene{ 0x63 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot20;ShareData=AHn)a95d3PS-;Xc8gn$yV(O+RRe(Z,UldSTUI!84V4*0rTVPLFUBi819g{4W+C
            { LON_LON_RANCH,
              "On bench under rain shed: Middle-Right",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 690, 23, 285 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/souko;ShareData=AQ4hLUn)5@9K3KAUWWe2WO@l_Q,_LDUbGO]Ubb5:V4R,P90Q^o9OdH2UcJ-kVS
            { LLR_TALONS_HOUSE,
              "Hidden in hay stack on the first floor.",
              GsScene{ 0x4C },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 660, 0, -120 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)); } } },
            // https://noclip.website/#oot3d/souko;ShareData=AaW$fUf;1dURO9V9h6AVWO4KW6fvn0Uv;/OURE5FV4J7bUdVY}9XnnoUrt}R+C
            { LLR_TALONS_HOUSE,
              "On the bed on the second floor.",
              GsScene{ 0x4C },
              Room{ 2 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1550, 164, -130 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild; } } },
        });

    gsTable[LLR_GS_TREE] = new GoldSkulltulaData( //
        LLR_GS_TREE, 0x0B, 0x08, GS_AGE_CHILD, nullptr,
        // Original
        {
            LON_LON_RANCH,
            GsScene{ 0x63 },
            Room{ 0 },
            { [] { return IsChild; } },
        },
        {
            // https://noclip.website/#oot3d/spot20;ShareData=AHn)a95d3PS-;Xc8gn$yV(O+RRe(Z,UldSTUI!84V4*0rTVPLFUBi819g{4W+C
            { LON_LON_RANCH,
              "On bench under rain shed: Right-Right",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 645, 23, 285 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/spot20;ShareData=ASP!)Ur|?DT)s,e9kmQ5V)}Hs5/VuyUma~$UY/HzV/h]]UdwlT9Qq+xUv6st=a
            { LON_LON_RANCH,
              "In crate near original tree.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1161, 0, -2370 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/spot20;ShareData=AFumC97I=DTM;qNTy8|G+8uj+Q)EBKUkrdx9Jx3[VZIC*85vv69KhgO9o6*g+^
            { LON_LON_RANCH,
              "Up on wooden gate to horse area.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -220, 167, -1520 },
                  { -16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[LH_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        LH_GS_BEAN_PATCH, 0x12, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            LAKE_HYLIA,
            GsScene{ 0x57 },
            Room{ 0 },
            { [] { return IsChild && CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot06;ShareData=AV4N-Uqy{nT=KKk9OwiQ+[VIZQi-f9Ul1e4Ub,zc=EYOIUO;2y92@sNUZVu&WP
            { LAKE_HYLIA,
              "In field, a bit behind Bonooru.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -140, -1293, 2790 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AM,lV9j);09Oqf[UsLfd=M&iu6hf+fUij,hUn4^-=L|PI9mspaUDPJV96]VyWP
            { LAKE_HYLIA,
              "On broken pillar near Zora's Domain shortcut.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1035, -1225, 3355 },
                  { -3000, -2000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AV-sr9i[[oToy509M3?9=QAmyRSvo^Ua:zMT,tcO=P43,UTn7VT+i3Z9iZ{*WP
            { LAKE_HYLIA,
              "Near shortcut to Zora's Domain, on zora emblem on left pillar in water.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -815, -1255, 3960 },
                  { -16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
        });

    gsTable[LH_GS_SMALL_ISLAND] = new GoldSkulltulaData( //
        LH_GS_SMALL_ISLAND, 0x12, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            LAKE_HYLIA,
            GsScene{ 0x57 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot06;ShareData=AUS=EUn@QYT3CtWUTIp0=Fbo3QO,&lUVt9t9XNn:=RCy59G)6cUCs~CUi;EvWP
            { LAKE_HYLIA,
              "On back of big tree, high up.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -645, -1105, 7575 },
                  { 16384, 5000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AE7((9kuen8Ro!(9lvO+=QQl?Q6_S@Uk,898+4$L=BIJVUs9QZ8I{~19nN;XWP
            { LAKE_HYLIA,
              "Under the end of the bridge towards the big tree's island.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1415, -1320, 7030 },
                  { 10000, -24000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AIO+eT^{[jT*qmv9qWc}V$dj?6RXETUhGV)T},d3=RiE]Uq]_u8()FvT)Jz|WP
            { LH_FISHING_ISLAND,
              "At right edge of fishing island.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1390, -1305, 4360 },
                  { 3000, -5000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
        });

    gsTable[LH_GS_LAB_WALL] = new GoldSkulltulaData( //
        LH_GS_LAB_WALL, 0x12, 0x04, GS_AGE_CHILD, nullptr,
        // Original
        {
            LAKE_HYLIA,
            GsScene{ 0x57 },
            Room{ 0 },
            { [] {
                return IsChild && CanGetNightTimeGS && (HookshotOrBoomerang || (LogicLabWallGS && CanJumpslash));
            } },
        },
        {
            // https://noclip.website/#oot3d/spot06;ShareData=AFS&!Uq-ehTF8T;87m4u=1,SO6fdM-Uus*CT/Y:N=L6,iTm$N69BGtdUWDf}WP
            { LAKE_HYLIA,
              "Behind small waterfall near lab.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -3445, -1235, 3640 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && (CanUseProjectile || CanUse(DINS_FIRE)); } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AK6(IUGLty9e(bUUtR{b=0f?^RW{P7UcbG6T()dG=MtLm9m?$x8)jT&UU)4EWP
            { LAKE_HYLIA,
              "On tiny, pointy island after small waterfall, facing bridge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -3295, -1303, 4450 },
                  { 6000, 16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
        });

    gsTable[LH_GS_LAB_CRATE] = new GoldSkulltulaData( //
        LH_GS_LAB_CRATE, 0x12, 0x08, GS_AGE_BOTH, nullptr,
        // Original
        {
            LH_LAB,
            GsScene{ 0x38 },
            Room{ 0 },
            { [] { return CanUse(IRON_BOOTS) && CanUse(HOOKSHOT); },
              /*Glitched*/
              [] {
                  return (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) && HasBombchus &&
                          (HasBottle || (IsAdult && (HasBoots || ClaimCheck)) || (IsChild && WeirdEgg)) &&
                          (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::ADVANCED) ||
                           ((Bugs || Fish) && CanUse(HOVER_BOOTS) &&
                            CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) ||
                           (CanUse(FARORES_WIND) && CanUse(NAYRUS_LOVE) &&
                            CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) ||
                           ProgressiveScale >= 2 || CanUse(IRON_BOOTS))) ||
                         (CanUse(IRON_BOOTS) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE));
              } },
        },
        {
            // https://noclip.website/#oot3d/hylia_labo;ShareData=ATiXS8udDR8(vBBUraQV+v-k=5-bj0UrTFQT3CSm+&4g-9nhxdTNpW:8zB8x+5
            { LH_LAB,
              "In mouth of shark behind gate.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { -260, -335, -120 },
                  { -2000, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsAdult && CanUse(IRON_BOOTS) && WaterTimer >= 16 &&
                           CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);
                } } },
            // https://noclip.website/#oot3d/turibori;ShareData=ACqN3UFMsI9ZYaMUweleV3fZOQ!QfOUpRw}UKf/n+tUKh9r)})9eF&KUK[xmVS
            { LH_FISHING_HOLE,
              "Bottom center of pond.",
              GsScene{ 0x49 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return GlitchEnabled(GlitchRestrictedItems, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { 0, -160, 0 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return CanGetNightTimeGS && (CanUse(IRON_BOOTS) || CanUse(HOVER_BOOTS)) &&
                           CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           ((IsAdult && CanUse(DINS_FIRE)) || HasBombchus);
                } } },
        });

    gsTable[LH_GS_TREE] = new GoldSkulltulaData( //
        LH_GS_TREE, 0x12, 0x10, GS_AGE_ADULT, nullptr,
        // Original
        {
            LAKE_HYLIA,
            GsScene{ 0x57 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS &&
                         (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::INTERMEDIATE) ||
                          CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot06;ShareData=AE&|HUbUQE9N6VnUD7)r=n(P-6zaI:Ur,JHUlX/e+*4-R9cLCV96Y|1T)g,ZWP
            { LAKE_HYLIA,
              "On top of Lab, on chimney sticking out from the small tower.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -2670, -474, 3637 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsAdult && CanGetNightTimeGS && (CanUse(SCARECROW) || CanPlantBean(LAKE_HYLIA)) &&
                          CanUse(HOOKSHOT);
               },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && CanUse(HOOKSHOT);
                } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AIO$+Uq=KgT{k,@UZl5]=l_1L6X!cWUfgmG9fDnI=E_jC9tlUVT/C1AUQ1+bWP
            { LAKE_HYLIA,
              "On wall behind waterfall from Gerudo Valley.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -4075, -1000, 2420 },
                  { 16384, 12000, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS && CanUse(IRON_BOOTS) && WaterTimer >= 8 && CanUse(HOOKSHOT);
              } } },
            // https://noclip.website/#oot3d/spot06;ShareData=ACvGwUt!c*TR+=h8pA=J=HD];6u)Y3Udom^UAVJ5=WTr{Tn_y29agDYUq{pSWP
            { LAKE_HYLIA,
              "Inside ice at shortcut to Zora's Domain.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { -915, -1553, 3600 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE); } } },
            // https://noclip.website/#oot3d/spot06;ShareData=AZ7{}UqgXG7(q&NThL3P=MLek6uY)8Uq}2dT:{ih=B5gs8pYe:9C:B4Ul?LBWP
            { LAKE_HYLIA,
              "On the pillar furthest away from the shortcut, on the zora emblem pointing towards Water Temple.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -997, -1265, 4340 },
                  { 16384, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(HOOKSHOT); } } },
        });
}
