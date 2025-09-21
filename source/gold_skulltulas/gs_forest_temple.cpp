#include "gold_skulltulas.hpp"
#include "dungeon.hpp"
#include "enemizer_logic.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;
using namespace Dungeon;

void GsTable_Init_ForestTemple() {
    gsTable[FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD] = new GoldSkulltulaData( //
        FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD, 0x03, 0x01, GS_AGE_BOTH, [] { return ForestTemple.IsVanilla(); },
        // Original
        {
            FOREST_TEMPLE_NE_OUTDOORS_LOWER,
            GsScene{ 0x3 },
            Room{ 7 },
            { [] {
                return CanUse(HOOKSHOT) || (LogicForestOutdoorEastGS && CanUse(BOOMERANG)) ||
                       Here(FOREST_TEMPLE_FALLING_ROOM,
                            [] { return CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives; });
            } },
        },
        {
            // https://noclip.website/#oot3d/bmori1;ShareData=ANXhL9HM_w94kq&UndS|V}wE9Q+shUUtPY)UcgUUV=m8,91g$yT,5hi9e~cv+^
            { FOREST_TEMPLE_NE_OUTDOORS_LOWER,
              "Hiding behind the well, on the floor.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1265, 193, -1600 },
                  { 0, 0, 0 },
              },
              { [] { return CanAdultAttack || CanChildAttack; } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=ADUPXUjr=dUU6o*UIa95WH2-U6b~XdUe9[c92td0WH+i)95J5vUj4ZSUV{F6=a
            { FOREST_TEMPLE_NE_OUTDOORS_LOWER,
              "Under the red switch balcony.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 915, 740, -2980 },
                  { 0, 0, 32767 },
              },
              { [] { return CanUse(LONGSHOT); } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AQe|L8:Sv5Uk_EQ9t-i@V|eH5RKonnUqvMxUf+fvV8(~nUt0X&T7iD$8mpri=a
            { FOREST_TEMPLE_NE_OUTDOORS_LOWER,
              "In water, by corner near original location.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1512, 83, -2895 },
                  { 0, 0, 0 },
              },
              { [] {
                   return CanUse(SLINGSHOT) || CanUse(BOW) || CanUse(HOOKSHOT) ||
                          Here(FOREST_TEMPLE_FALLING_ROOM, [] { return CanUse(DINS_FIRE); });
               },
                /*Glitched*/
                [] {
                    return (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                           CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);
                } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AL3O{UZqYlT/:hR9J8v{WM^A!RAs^MUrNWwT^jcVWN2f^UUW_e9ES9=Ulsk&=a
            { FOREST_TEMPLE_NE_OUTDOORS_LOWER,
              "On wall by door to falling platform room.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1730, 560, -2857 },
                  { 16384, 0, 0 },
              },
              { [] { return Here(FOREST_TEMPLE_FALLING_ROOM, [] { return CanAdultAttack || CanChildAttack; }); } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=Aa,4jUh4:wS[WJFTmpwDWJ!p~5*g_*UeHi{8~QKWWOWa)83QgtT1!i&UmR3p=a
            { FOREST_TEMPLE_NE_OUTDOORS_UPPER,
              "On wall by red switch.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 915, 830, -3150 },
                  { 16384, 0, 0 },
              },
              { [] { return CanAdultAttack || CanChildAttack; } } },
        });

    gsTable[FOREST_TEMPLE_GS_FIRST_ROOM] = new GoldSkulltulaData( //
        FOREST_TEMPLE_GS_FIRST_ROOM, 0x03, 0x02, GS_AGE_BOTH, [] { return ForestTemple.IsVanilla(); },
        // Original
        {
            FOREST_TEMPLE_FIRST_ROOM,
            GsScene{ 0x3 },
            Room{ 0 },
            { [] {
                 return (IsAdult && Bombs) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(BOOMERANG) ||
                        CanUse(SLINGSHOT) || HasBombchus || CanUse(DINS_FIRE);
             },
              /*Glitched*/
              [] {
                  return (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                         CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);
              } },
        },
        {
            // https://noclip.website/#oot3d/bmori1;ShareData=AJCgYUg:hA8ZW4~T_QGjV5A!k6K93!Ubk;CT;d@+WK}&a8=g688;1J~UW!I;Vt
            { FOREST_TEMPLE_FIRST_ROOM,
              "By roof above door towards lobby, on wall, on Forest Temple's symbol.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 115, 858, 140 },
                  { 16384, 0, 0 },
              },
              { [] {
                   return CanJumpslash || HookshotOrBoomerang ||
                          ((CanUseProjectile || CanUse(DINS_FIRE)) && CanUse(HOVER_BOOTS));
               },
                /*Glitched*/
                [] {
                    return (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                            CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) ||
                           CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AQ?**9q&~$8+|6)TmmkGV1Z!nRT=eQUWj_)UCsiGV[BQ(8&z4pUL^LH9kqe]Vt
            { FOREST_TEMPLE_FIRST_ROOM,
              "Hidden behind some leaves behind the right tree.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 428, 309, 314 },
                  { 0, 0, 0 },
              },
              { [] { return CanAdultAttack || CanChildAttack; } } },
        });

    gsTable[FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD] = new GoldSkulltulaData( //
        FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD, 0x03, 0x04, GS_AGE_BOTH, [] { return ForestTemple.IsVanilla(); },
        // Original
        {
            FOREST_TEMPLE_NW_OUTDOORS_LOWER,
            GsScene{ 0x3 },
            Room{ 8 },
            { [] {
                return CanUse(LONGSHOT) || Here(FOREST_TEMPLE_NW_OUTDOORS_UPPER,
                                                [] { return HookshotOrBoomerang && CanPassEnemy(3, 0, 8, 5); });
            } },
        },
        {
            // https://noclip.website/#oot3d/bmori1;ShareData=ABmX19sPT/9IAZnUa)53=C1c+RdGHHUc4a,UlG)tV606h9tP4hUP4;{9q3g-=a
            { FOREST_TEMPLE_NW_OUTDOORS_LOWER,
              "On top of the broken pillar.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1367, 351, -2699 },
                  { 0, 4000, -6000 },
              },
              { [] { return HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AWu:nT|b~n9pscYUp5*|=LZULRR,hvUh@~@UwB~8Vw4wg9ji$v8/|=oT1Uwu+^
            { FOREST_TEMPLE_NW_OUTDOORS_LOWER,
              "Hidden by the well.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1088, 203, -1612 },
                  { 0, 0, 0 },
              },
              { [] { return CanAdultAttack || CanChildAttack; } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AZD{^UgiJVUY{DE94&Ns=Yp+d6W^zZUf8KAUpf@)Vw3tyUXVnE9XcJRT}8yR=a
            { FOREST_TEMPLE_NW_OUTDOORS_LOWER,
              "Underwater, on side of bridge that's towards upper ledge.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1214, 135, -2478 },
                  { 0, 4000, 16384 },
              },
              { [] {
                   return CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || CanUse(BOOMERANG) ||
                          CanUse(DINS_FIRE);
               },
                /*Glitched*/
                [] {
                    return (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                           CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);
                } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AI]z07-rL,T9=X5Uj4~D=Bl{KRMT:oUX|U]9AnS8WO$TY96ESZ6$vy;7sMI5=a
            { FOREST_TEMPLE_NW_OUTDOORS_UPPER,
              "Upper ledge, in alcove guarded by Big Deku Baba.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1720, 570, -2361 },
                  { 0, 0, -16384 },
              },
              { [] { return (CanAdultAttack || CanChildAttack) && CanPassEnemy(3, 0, 8, 5); } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AW8}NTR;S19tt:c97cJT=CGp96eKwsUty|F9k8ITWL7I)UVKV+S@doIS5f!o=a
            { FOREST_TEMPLE_NW_OUTDOORS_LOWER,
              "At the very top of the wall, above door to hallway that leads to other courtyard.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{
                  [] { return GlitchEnabled(GlitchHookshotJump_Boots, GlitchDifficulty::INTERMEDIATE); } },
              PosRot{
                  { -305, 1500, -2800 },
                  { 0, 0, 16384 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) &&
                           (CanUse(BOW) || CanUse(SLINGSHOT) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                            (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)));
                } } },
        });

    gsTable[FOREST_TEMPLE_GS_LOBBY] = new GoldSkulltulaData( //
        FOREST_TEMPLE_GS_LOBBY, 0x03, 0x08, GS_AGE_BOTH, [] { return ForestTemple.IsVanilla(); },
        // Original
        {
            FOREST_TEMPLE_LOBBY,
            GsScene{ 0x3 },
            Room{ 2 },
            { [] { return HookshotOrBoomerang; },
              /*Glitched*/
              [] { return HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE); } },
        },
        {
            // https://noclip.website/#oot3d/bmori1;ShareData=AGK[e8GdaB90Q$oUX7~GWI9*yRW90&Uv/h-Urx99WOe@T910RMS{SY27|D9m+^
            { FOREST_TEMPLE_LOBBY,
              "On balcony from Green Poe room.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 628, 463, -1432 },
                  { 0, 0, 0 },
              },
              { [] { return Here(FOREST_TEMPLE_EAST_CORRIDOR, [] { return CanAdultAttack || CanChildAttack; }); } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AUXj998Rc/TVu9CTB(//Vlv3)5)ikjUZQCB9h_jjVt&!Z8JR?H967Az9004H+^
            { FOREST_TEMPLE_LOBBY,
              "High on wall above door from entrance.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 117, 950, -720 },
                  { 0, 0, -16384 },
              },
              { [] { return CanUse(LONGSHOT); } } },
            // https://noclip.website/#oot3d/bmori1;ShareData=AZY=X97GxaS4:|a7~~U5Vs~EY6o;AXUfYSnUo!e8V,L,ETC1!)Uu[X[94m+C=a
            { FOREST_TEMPLE_LOBBY,
              "Inside stairs used for boss key skip.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] {
                  return GlitchEnabled(GlitchForestBKSkip) ||
                         GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE);
              } },
              PosRot{
                  { 117, 313, -2280 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return (IsAdult && GlitchForestBKSkip && (CanUse(HOOKSHOT) || CanUse(BOW) || CanUse(SLINGSHOT))) ||
                           CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE);
                } } },
        });

    gsTable[FOREST_TEMPLE_GS_BASEMENT] = new GoldSkulltulaData( //
        FOREST_TEMPLE_GS_BASEMENT, 0x03, 0x10, GS_AGE_BOTH, [] { return ForestTemple.IsVanilla(); },
        // Original
        {
            FOREST_TEMPLE_BOSS_REGION,
            GsScene{ 0x3 },
            Room{ 17 },
            { [] { return HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return Bombs && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) &&
                         CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/bmori1;ShareData=AZz{aUjQNwS]mV6S&{^[Vl1WVQ)Aw6Usn*x9r~jv=VN1&8Bp]5UpS@AUm}g8=a
            { FOREST_TEMPLE_BOSS_REGION,
              "Above boss door, on emblem.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 120, -545, -2795 },
                  { 16384, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/bmori1;ShareData=AD&ssTnA8h9G=maUd0sy+}ju0Rvza5Ub]J6UIyRr=ErvO9i,2[8Ts15TyM*a+^
            { FOREST_TEMPLE_BOSS_REGION,
              "Inside rotating wall, pink carpet, opposite of button room.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -400, -730, -1560 },
                  { 0, 0, -16384 },
              },
              { [] { return CanAdultAttack || CanChildAttack; } } },
        });
}
