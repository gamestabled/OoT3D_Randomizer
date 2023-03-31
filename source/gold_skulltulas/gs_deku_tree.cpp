#include "gold_skulltulas.hpp"
#include "dungeon.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;
using namespace Dungeon;

void GsTable_Init_DekuTree() {
    gsTable[DEKU_TREE_GS_BASEMENT_BACK_ROOM] = new GoldSkulltulaData( //
        DEKU_TREE_GS_BASEMENT_BACK_ROOM, 0x00, 0x01, GS_AGE_BOTH, [] { return DekuTree.IsVanilla(); },
        // Original
        {
            DEKU_TREE_BASEMENT_BACK_ROOM,
            GsScene{ 0x0 },
            Room{ 8 },
            { [] { return HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return Bombs && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) &&
                         CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/ydan;ShareData=AEWO=Uj|1P8O,f|Tc0Kz=bmOl5dBMGUia8MUP{-q=Yt=N84kgY9Y0$[UifXs+^
            { DEKU_TREE_BASEMENT_BACK_ROOM,
              "Same room, behind the big skulltula.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -2719, -730, -747 },
                  { 16383, 8191, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
            // https://noclip.website/#oot3d/ydan;ShareData=ATOl497c+=9boF*UkX*J=N$[)6NV/7UY+0AUWvBU=LhJf9z-)CT*J*!93FH;+d
            { DEKU_TREE_BASEMENT_BACK_LOBBY,
              "Center of back lobby, on floor below the baby gohma eggs.",
              GsScene{ 0x0 },
              Room{ 7 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1963, -760, 78 },
                  { 0, 0, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
            // https://noclip.website/#oot3d/ydan;ShareData=AY-hS9jU,HStcWi8HqB,=IAFq6OkcUUvorTUKQio=CWTyS*LpHUT?P=9k]yoV[
            { DEKU_TREE_BASEMENT_TORCH_ROOM,
              "On wall by torch: Middle",
              GsScene{ 0x0 },
              Room{ 6 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1857, -710, 1350 },
                  { -16384, 0, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
        });

    gsTable[DEKU_TREE_GS_BASEMENT_GATE] = new GoldSkulltulaData( //
        DEKU_TREE_GS_BASEMENT_GATE, 0x00, 0x02, GS_AGE_BOTH, [] { return DekuTree.IsVanilla(); },
        // Original
        {
            DEKU_TREE_BASEMENT_LOWER,
            GsScene{ 0x0 },
            Room{ 3 },
            { [] { return CanChildAttack || CanAdultAttack; } },
        },
        {
            // https://noclip.website/#oot3d/ydan;ShareData=AAn:397:kd9a5q~UjPa&+9&i]6k|HfUhAK*Ud[f*=S}am9mMaBUMbtp9ha/HVt
            { DEKU_TREE_BASEMENT_LOWER,
              "Underwater, near the opposite gate.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -400, -940, 536 },
                  { 0, 0, 0 },
              },
              { [] { return CanAdultAttack || CanUseProjectile || CanUse(DINS_FIRE); } } },
            // https://noclip.website/#oot3d/ydan;ShareData=AB;qpUoH6X9eFVYUd~bs+yPFf5h{0XUYYQ*Uhfg{=DbU=9rbmW9crcbUi1oEV[
            { DEKU_TREE_BASEMENT_SCRUB_ROOM,
              "Behind grass lumps between doors.",
              GsScene{ 0x0 },
              Room{ 4 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -233, -880, 758 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/ydan;ShareData=AEI(KUa:J|9F^w-T*Mwj+:VxeQ}O:SUfHIUUSAv~=FYJ=9S^M79cpDeUnrnlV[
            { DEKU_TREE_BASEMENT_WATER_ROOM,
              "Underwater, on wall by slope back to land.",
              GsScene{ 0x0 },
              Room{ 5 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -530, -930, 1150 },
                  { 16384, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/ydan;ShareData=AY-hS9jU,HStcWi8HqB,=IAFq6OkcUUvorTUKQio=CWTyS*LpHUT?P=9k]yoV[
            { DEKU_TREE_BASEMENT_TORCH_ROOM,
              "On wall by torch: Left",
              GsScene{ 0x0 },
              Room{ 6 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1787, -710, 1350 },
                  { -16384, 0, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
        });

    gsTable[DEKU_TREE_GS_BASEMENT_VINES] = new GoldSkulltulaData( //
        DEKU_TREE_GS_BASEMENT_VINES, 0x00, 0x04, GS_AGE_BOTH, [] { return DekuTree.IsVanilla(); },
        // Original
        {
            DEKU_TREE_BASEMENT_LOWER,
            GsScene{ 0x0 },
            Room{ 3 },
            { [] { return CanUseProjectile || CanUse(DINS_FIRE) || (LogicDekuBasementGS && CanJumpslash); },
              /*Glitched*/
              [] {
                  return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                         CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE);
              } },
        },
        {
            // https://noclip.website/#oot3d/ydan;ShareData=AaMCX9h|[rTqVfh8yCI-=RDZX6KDVfUWJMZUwB+q=OzQ)Ty3o^UuYfS9t_$T98
            { DEKU_TREE_BASEMENT_UPPER,
              "On the vines that lead down to the three scrub guards.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -630, -870, 110 },
                  { -16383, 0, 0 },
              },
              { [] { return HasFireSourceWithTorch && CanUseProjectile; },
                /*Glitched*/
                [] {
                    return HasFireSourceWithTorch &&
                           (CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                            (CanUse(STICKS) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE)) ||
                            CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/ydan;ShareData=Aap7$93cM39f*Q:9oj(y++&gwRHp[tUufcJ9fN3(=Vi_oUc3w^9Wv8g94(2gV[
            { DEKU_TREE_BASEMENT_SCRUB_ROOM,
              "High on wall opposite of grass lumps between doors.",
              GsScene{ 0x0 },
              Room{ 4 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 87, -770, 1142 },
                  { 0, -8192, 16384 },
              },
              { [] { return HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return (CanUse(STICKS) || CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/ydan;ShareData=AW7LiUk^o;UD0O8Ugu3==ROo,6LOnTUX=3^9dnf}=M,FW9h&LQUI1h+UZy6LV[
            { DEKU_TREE_BASEMENT_WATER_ROOM,
              "On wall above spike log, opposite side of underwater switch.",
              GsScene{ 0x0 },
              Room{ 5 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -835, -750, 790 },
                  { 16384, 0, 0 },
              },
              { [] { return HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return (CanUse(STICKS) || CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) &&
                           HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/ydan;ShareData=AY-hS9jU,HStcWi8HqB,=IAFq6OkcUUvorTUKQio=CWTyS*LpHUT?P=9k]yoV[
            { DEKU_TREE_BASEMENT_TORCH_ROOM,
              "On wall by torch: Right",
              GsScene{ 0x0 },
              Room{ 6 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1927, -710, 1350 },
                  { -16384, 0, 0 },
              },
              { [] { return CanChildAttack || CanAdultAttack; } } },
        });

    gsTable[DEKU_TREE_GS_COMPASS_ROOM] = new GoldSkulltulaData( //
        DEKU_TREE_GS_COMPASS_ROOM, 0x00, 0x08, GS_AGE_BOTH, [] { return DekuTree.IsVanilla(); },
        // Original
        {
            DEKU_TREE_COMPASS_ROOM,
            GsScene{ 0x0 },
            Room{ 10 },
            { [] { return CanChildAttack || CanAdultAttack; } },
        },
        {
            // https://noclip.website/#oot3d/ydan;ShareData=AJiZlUim_A9Xe|:UIX-c=JUv)RBDwhUs5u/T}^?OWAviQ9karb9P/pDUt,i$VS
            { DEKU_TREE_COMPASS_ROOM,
              "Behind compass chest.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1545, 840, 10 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/ydan;ShareData=AbY(S93NP/9T3tZ9zKd_=DiFTRC3u}Uc@]s9eOV~V[{s:Uf$kd9YfL{9hh02VS
            { DEKU_TREE_COMPASS_ROOM,
              "On vines, top right.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -870, 940, 261 },
                  { -16384, 2000, 0 },
              },
              { [] { return CanUseProjectile || CanUse(DINS_FIRE); },
                /*Glitched*/
                [] {
                    return CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                           CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) ||
                           (CanUse(STICKS) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/ydan;ShareData=AF|0wUQTdN9eyBBUnT+WU,:_XQ*vR5Ud!AzT*Qi9V![Tq9o:r+8}$,&UFuk9+d
            { DEKU_TREE_LOBBY,
              "On side of log where you jump off to break web, the one opposite of vines.",
              GsScene{ 0x0 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -160, 750, -158 },
                  { 16384, 8000, 0 },
              },
              { [] { return CanUseProjectile || CanUse(DINS_FIRE); },
                /*Glitched*/
                [] {
                    return CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                           CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) ||
                           (CanUse(STICKS) && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE));
                } } },
        });

    gsTable[DEKU_TREE_MQ_GS_LOBBY] = new GoldSkulltulaData( //
        DEKU_TREE_MQ_GS_LOBBY, 0x00, 0x02, GS_AGE_BOTH, [] { return DekuTree.IsMQ(); },
        // Original
        {
            DEKU_TREE_MQ_LOBBY,
            GsScene{ 0x0 },
            Room{ 0 },
            { [] { return CanAdultAttack || CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/ydan_dd;ShareData=AAgxKUvUc|9L&zZ9WSlu++SyvQ@A4YUhx_?95blPV{fV}USD2EUocYmUen6CVt
            { DEKU_TREE_MQ_LOBBY,
              "Center of lobby roof.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 0, 1120, 0 },
                  { 0, 0, 32767 },
              },
              { [] { return HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/ydan_dd;ShareData=AOuhu9pY_B9dVA}UwM*A+10RW6CMCtUl7J*UIcg$VzhqD9oU7gURBx-97)b=Vt
            { DEKU_TREE_MQ_LOBBY,
              "Bottom of swirly path.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -144, 200, 445 },
                  { 0, -18000, 16383 },
              },
              {} },
        });
}
