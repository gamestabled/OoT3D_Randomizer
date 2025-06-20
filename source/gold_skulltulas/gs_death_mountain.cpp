#include "gold_skulltulas.hpp"
#include "enemizer_logic.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_DeathMountain() {
    gsTable[DMT_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        DMT_GS_BEAN_PATCH, 0x0F, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            DEATH_MOUNTAIN_TRAIL,
            GsScene{ 0x60 },
            Room{ 0 },
            { [] {
                return CanPlantBugs &&
                       (HasExplosives || GoronBracelet ||
                        (LogicDMTSoilGS && (CanTakeDamage || CanUse(HOVER_BOOTS)) && CanUse(BOOMERANG)));
            } },
        },
        {
            // https://noclip.website/#oot3d/spot16;ShareData=AGj!6Up*,jTq~zH9V*J$=Q7Bt6uYrvUuaK+T?i5xWBeK2URT8H8~^-oUq,2[+^
            { DEATH_MOUNTAIN_TRAIL,
              "By freestanding heart piece, but as far in the corner as possible.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1426, 1108, -1448 },
                  { 8192, 0, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (CanTakeDamage || CanUse(HOVER_BOOTS)) && CanChildAttack;
              } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AO|6MUBhi{9HUG_91x?Z=X{~M6l0x4Uc+P69a2faWEycVUob8?UI7uLUO$-o+5
            { DEATH_MOUNTAIN_TRAIL,
              "Left of where you throw the bomb flower to open Dodongo's Cavern, on side of edge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1580, 1400, -211 },
                  { 16384, -13500, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && (CanUseProjectile || CanUse(DINS_FIRE)); },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AY3bRUn~E$Sl=kVS(vqn=OVGC6;q{oUqxU{9Tc7SV]4J97{G/4T)+fWUYuy;V[
            { DEATH_MOUNTAIN_TRAIL,
              "On wooden pole before rocks to summit.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -750, 1470, 520 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[DMT_GS_NEAR_KAK] = new GoldSkulltulaData( //
        DMT_GS_NEAR_KAK, 0x0F, 0x04, GS_AGE_BOTH, nullptr,
        // Original
        {
            DEATH_MOUNTAIN_TRAIL,
            GsScene{ 0x60 },
            Room{ 0 },
            { [] {
                 return CanBlastOrSmash || (IsChild && CanDetonateAnyEnemy(96, 0, 0, { 10, 11 })) ||
                        (IsAdult && CanDetonateEnemy(96, 2, 0, 6));
             },
              /*Glitched*/
              [] { return (CanUse(STICKS) && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)); } },
        },
        {
            // https://noclip.website/#oot3d/kakusiana;ShareData=AKl=VUaxXlTZ/!QTetn3WRWFBRJZgJUWDq;93~;JVTTRH8*b//UsTu=Ub|0d+5
            { DMT_COW_GROTTO,
              "Medium high on wall behind cow.",
              GsScene{ 0x3E },
              Room{ 3 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2400, 150, -590 },
                  { 16384, 0, 0 },
              },
              { [] { return HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=Aa@bAUE|_-ULJ:bUk;/7+};^9Q[L,{Us[D[9G|ErV@t-r9kDXXT4goKURk|2+d
            { DEATH_MOUNTAIN_TRAIL,
              "In the other wall recess that has a chest, up on wall.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -675, 1590, -130 },
                  { 24576, 12000, 0 },
              },
              { [] { return CanBlastOrSmash && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return CanBlastOrSmash && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });

    gsTable[DMT_GS_ABOVE_DODONGOS_CAVERN] = new GoldSkulltulaData( //
        DMT_GS_ABOVE_DODONGOS_CAVERN, 0x0F, 0x08, GS_AGE_ADULT, nullptr,
        // Original
        {
            DEATH_MOUNTAIN_TRAIL,
            GsScene{ 0x60 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && CanUse(MEGATON_HAMMER); },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS && CanUse(STICKS) &&
                         ((CanTakeDamageTwice && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE)) ||
                          CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot16;ShareData=AP@82UV],48f,b[9Fvu:+;P;$6,nB~UsAuu9Iu17WH!FVT29iEUSp7?Ulom-+^
            { DEATH_MOUNTAIN_TRAIL,
              "Above entrance to Goron City, on middle of cloth.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -410, 1350, -1900 },
                  { 16384, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=Aar7v9XDA2UMnOu91(/=+6zB}5{|&HUv(4SUSxQ0WLF{SUs+O]T0F{c9V(LW+5
            { DEATH_MOUNTAIN_TRAIL,
              "High on wall on other side of ravine near Goron City entrance.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 70, 1850, -320 },
                  { 16384, -19000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AXb|LT)fA;UP=c{UblB;=EoZv56HdrUjmj39fov*WM@f&935~;T2D^wUKEnw+^
            { DEATH_MOUNTAIN_TRAIL,
              "Opposite wall you see when throwing the bomb flower as child.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1980, 1632, -885 },
                  { 8192, 15000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); } } },
        });

    gsTable[DMT_GS_FALLING_ROCKS_PATH] = new GoldSkulltulaData( //
        DMT_GS_FALLING_ROCKS_PATH, 0x0F, 0x10, GS_AGE_ADULT, nullptr,
        // Original
        {
            DEATH_MOUNTAIN_SUMMIT,
            GsScene{ 0x60 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && CanUse(MEGATON_HAMMER); } },
        },
        {
            // https://noclip.website/#oot3d/spot16;ShareData=AV22aUux7^TQ*3WT6?_*V4?g46+K*1Uo!YU8@6u4WaJ?_8/C|*T/LqpUkB(,=a
            { DEATH_MOUNTAIN_SUMMIT,
              "High on wall above entrance to DMC.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 270, 3720, -4550 },
                  { 16384, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(HOOKSHOT); } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AJlvU92?~dUV{:@9Mdu(WAZ]mRrE?dUoBMzUmZ?WWUHj=UuI1]Ui,,O9S[0}=a
            { DEATH_MOUNTAIN_SUMMIT,
              "Between Biggoron's feet.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                         GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE);
              } },
              PosRot{
                  { 945, 2900, -3790 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AOY{,90|kG8&N&@UH-Z8=EX_JRzdVJUd!uMT|z&KV}99]9ZOD8UO2H:91W+i+^
            { DEATH_MOUNTAIN_SUMMIT,
              "On left ledge at the start where the falling rocks appear.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -660, 1850, -1580 },
                  { -5000, 4000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/spot16;ShareData=AUPJoUWD3K9bZ|N96)CE+!*Ib6gLrHUcqYz9PcdgWW3W8UV$K,T5MuhUEdn/=a
            { DEATH_MOUNTAIN_SUMMIT,
              "On right wall at the end of the falling rocks wall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 245, 2390, -3155 },
                  { 12000, -4000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });

    gsTable[DMC_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        DMC_GS_BEAN_PATCH, 0x0F, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            DMC_CENTRAL_LOCAL,
            GsScene{ 0x61 },
            Room{ 1 },
            { [] { return (FireTimer >= 8 || Hearts >= 3) && CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot17;ShareData=AMk+}9mA?=T^3^@UsEevWN?3f6Z60NUnX8|9e]*HV3wA49l9U09A]r*93*?L+5
            { DMC_CENTRAL_LOCAL,
              "On wall of east volcano, reachable from rupee platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 925, 490, -85 },
                  { 20000, 21000, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (FireTimer >= 24 || Hearts >= 3) && HookshotOrBoomerang;
              } } },
            // https://noclip.website/#oot3d/spot17;ShareData=AHX1u95iw:T^=RM9J9=GV$ak(RM+:+UiJa*UV-z1WEp7{T{IM~Ua1$k96]jt+d
            { DMC_UPPER_LOCAL,
              "On top of the east volcano.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return ((LogicFewerTunicRequirements && ItemPoolValue.IsNot(ITEMPOOL_MINIMAL)) ||
                          (GoronTunicAsChild && AgeItemsInLogic)) &&
                         ((GlitchEnabled(GlitchISG, GlitchDifficulty::INTERMEDIATE) &&
                           GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE)) ||
                          GlitchEnabled(GlitchMegaflip, GlitchDifficulty::ADVANCED));
              } },
              PosRot{
                  { 640, 1140, 30 },
                  { -2000, 2000, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && FireTimer >= 48 &&
                           ((CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                             (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE))) ||
                            CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::ADVANCED));
                } } },
            // https://noclip.website/#oot3d/spot17;ShareData=AMAY{Ui(A08@wh4T(&2[VJ6A{RUHgEUjtb/UQ/7!V|Lqh9Pju,9F?mjUY+,p+5
            { DMC_CENTRAL_LOCAL,
              "On left pillar by silver boulders to Fire Temple.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -60, 600, -630 },
                  { 18000, 5000, 0 },
              },
              { [] {
                  return IsChild && CanGetNightTimeGS && (FireTimer >= 16 || Hearts >= 3) && HookshotOrBoomerang;
              } } },
        });

    gsTable[DMC_GS_CRATE] = new GoldSkulltulaData( //
        DMC_GS_CRATE, 0x0F, 0x80, GS_AGE_CHILD, nullptr,
        // Original
        {
            DMC_UPPER_LOCAL,
            GsScene{ 0x61 },
            Room{ 1 },
            { [] { return IsChild && (FireTimer >= 8 || Hearts >= 3) && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot17;ShareData=AUFyuUi+-FUMXB)9MV(y=GY[ARBWLdUqoxlUYej?V|L=ZUNl?!9e:uhUh}L)V[
            { DMC_UPPER_LOCAL,
              "Inside boulder by ladder leading down to business scrub.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -505, 1145, 1075 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && (FireTimer >= 16 || Hearts >= 3) && CanBlastOrSmash; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && (FireTimer >= 24 || Hearts >= 3) && CanUse(STICKS) &&
                           CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);
                } } },
            // https://noclip.website/#oot3d/spot17;ShareData=AK?tEUbd9z9XTW:Uoz2[=U/t~Qw8W8UmeMxUU|fqWO3(I978]E9I=$aUSLi&V[
            { DMC_LADDER_AREA_NEARBY,
              "Down by business scrub, left on ledge by hammer boulder.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1145, 760, 985 },
                  { 16384, 7000, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS && (FireTimer >= 24 || Hearts >= 3) &&
                          (CanUse(SLINGSHOT) || CanUse(BOW) || CanUse(BOOMERANG) || CanUse(HOOKSHOT) ||
                           CanUse(DINS_FIRE));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && (FireTimer >= 24 || Hearts >= 3) &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot17;ShareData=AOVU49zGSqTg|kqT!!$iWJSVfQHQoBUp$(!9LkEHWD0X:8[*L@9M@vG9wB7*V[
            { DMC_UPPER_LOCAL,
              "On wall in crevice by gossip stone.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1300, 1600, 1710 },
                  { -16384, 0, 0 },
              },
              { [] {
                  return IsChild && (FireTimer >= 24 || Hearts >= 3) && CanBlastOrSmash && HookshotOrBoomerang;
              } } },
        });

    gsTable[GC_GS_CENTER_PLATFORM] = new GoldSkulltulaData( //
        GC_GS_CENTER_PLATFORM, 0x0F, 0x20, GS_AGE_ADULT, nullptr,
        // Original
        {
            GORON_CITY,
            GsScene{ 0x62 },
            Room{ 3 },
            { [] { return IsAdult && CanAdultAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot18;ShareData=AG=OxUY/tN8:olN9Yt![Vg^pc5]J:8UcYq~9Lj(7WCVbRUD?;_UGGdOUbmCEU!
            { GORON_CITY,
              "On eye of dodongo wall painting.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 165, 840, -170 },
                  { 18000, -4000, 0 },
              },
              { [] { return IsAdult && CanUse(LONGSHOT); } } },
            // https://noclip.website/#oot3d/spot18;ShareData=AW?KA9pQgVSxXt+8hDLWV$,2w6KBa?UdJeYT!|tnV)7:TTEQrOT~fx(92_DA+^
            { GC_GROTTO_PLATFORM,
              "On back of grotto platform hookshot pillar.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 968, 635, -1188 },
                  { 16384, -32768, 0 },
              },
              { [] { return IsAdult && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/shop_golon;ShareData=AUE0[UCew(T68Gw9tiXlVSc*[6JzXSUYO)@T&kKzU&jZrUWiWW8-_UbUQ1&+98
            { GC_SHOP,
              "On right stack of boxes.",
              GsScene{ 0x2E },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchRestrictedItems, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { 100, 15, -35 },
                  { 16384, -13000, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsAdult && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           (HasBoots || HasBottle || (FaroresWind && FaroresWindAnywhere)) &&
                           (HasExplosives || CanUse(DINS_FIRE));
                } } },
        });

    gsTable[GC_GS_BOULDER_MAZE] = new GoldSkulltulaData( //
        GC_GS_BOULDER_MAZE, 0x0F, 0x40, GS_AGE_CHILD, nullptr,
        // Original
        {
            GORON_CITY,
            GsScene{ 0x62 },
            Room{ 0 },
            { [] { return IsChild && CanBlastOrSmash; } },
        },
        {
            // https://noclip.website/#oot3d/spot18;ShareData=AMc~+UqSU,8LtgM8;hL:VmR-H5m5h_Uey2O8;mndVdD}aT:KHAT:*9:Uv3[s+^
            { GC_DARUNIAS_CHAMBER,
              "On the face of the Occam's statue.",
              GsScene{ 0x62 },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 90, 125, -1503 },
                  { 14000, 0, 0 },
              },
              { [] { return IsChild && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot18;ShareData=AY}(O9vUk68-PpK9JLAV+-|0j6ii6VUh!O^9Ic=/WF3sKUG4(;9Wa2o92BL$+^
            { GORON_CITY,
              "On wall by area where Hot-Rodder Goron gives bomb upgrade.",
              GsScene{ 0x62 },
              Room{ 3 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -75, 560, -695 },
                  { -16384, 5000, 0 },
              },
              { [] { return IsChild && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot18;ShareData=AJ~pwUW/chTBRIA8V@{1V|Mn=5{=I8Up;DnUg$yaWO32;TG=oT9ztg[UYQ*K+5
            { GORON_CITY,
              "In lava, hiding inside Song of Time block closest to central Goron City.",
              GsScene{ 0x62 },
              Room{ 3 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1030, 448, -372 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsChild && CanPlay(SongOfTime) &&
                         (CanUseProjectile || CanUse(DINS_FIRE) || (CanChildAttack && CanTakeDamage));
              } } },
        });
}
