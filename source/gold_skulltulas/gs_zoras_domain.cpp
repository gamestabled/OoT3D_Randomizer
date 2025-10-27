#include "gold_skulltulas.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_ZorasDomain() {
    gsTable[ZR_GS_LADDER] = new GoldSkulltulaData( //
        ZR_GS_LADDER, 0x11, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            ZORAS_RIVER,
            GsScene{ 0x54 },
            Room{ 1 },
            { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot03;ShareData=AC3QWUhTbaS~}Kv8@=BIWknCMRZG/FUruY6T(E_;WI8wtT!~tz9DRplUdAy=+^
            { ZORAS_RIVER,
              "On the largest stalagmite near waterfall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3615, 580, -1170 },
                  { 16384, -4000, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot03;ShareData=ASCzwT8;e9T{~ME90NdlV$!ah6S[&gUtGt,UN[^vV~CdGUrqss8ND!jT3?kx+^
            { ZORAS_RIVER,
              "In small waterfall before wooden bridge near Zora's Domain entrance.",
              GsScene{ 0x54 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2286, 400, -530 },
                  { 16384, -16384, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot03;ShareData=APwmj9sK,cUN&eP97(PUWZ;T86X9$+Ub1zJUICTQV&Pv(UVu5NUTQ/S9pb$a+^
            { ZORAS_RIVER,
              "On wall in water under dirt path right before wooden bridge towards Zora's Domain entrance.",
              GsScene{ 0x54 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3085, 500, -840 },
                  { 16384, -16384, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanJumpslash || CanUse(SLINGSHOT) || CanUse(BOOMERANG) || CanUse(BOW) || CanUse(HOOKSHOT) ||
                           CanUse(DINS_FIRE));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
        });

    gsTable[ZR_GS_TREE] = new GoldSkulltulaData( //
        ZR_GS_TREE, 0x11, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            ZR_FRONT,
            GsScene{ 0x54 },
            Room{ 0 },
            { [] { return IsChild && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot03;ShareData=ARBe?Uj}i6Ukk489wHzP=S6_05y:6^Ue=o$Ub?4^V~TB-Uov1S9WVdkUAsD^+d
            { ZORAS_RIVER,
              "On small pillar of gate by bean salesman.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -634, 220, -159 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot03;ShareData=AY5N98!pAtUog~@UhE+nVAh3ARcR1hUZ32T96pDT+u,xU9i@DT8$ryl8:Huz+5
            { ZORAS_RIVER,
              "Under stone bridge after bean salesman.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -135, 95, -245 },
                  { 30000, 16384, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(DINS_FIRE) || (CanUse(IRON_BOOTS) && CanUse(HOOKSHOT)));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot03;ShareData=ADewPUXg{m9K=a@UGzpCWGy3ERfNU_UWK?rUl~uqV:}+z9USNf9r8C0UsXW,+^
            { ZORAS_RIVER,
              "In fence area, center of Zora's River.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 825, 293, -875 },
                  { 2500, -16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
        });

    gsTable[ZR_GS_ABOVE_BRIDGE] = new GoldSkulltulaData( //
        ZR_GS_ABOVE_BRIDGE, 0x11, 0x08, GS_AGE_ADULT, nullptr,
        // Original
        {
            ZORAS_RIVER,
            GsScene{ 0x54 },
            Room{ 1 },
            { [] { return IsAdult && CanGetNightTimeGS && CanUse(HOOKSHOT); } },
        },
        {
            // https://noclip.website/#oot3d/spot03;ShareData=AER{^Tl;mm935)W93gw{Wn;F:RZ!:,UVJSM9tc[mWE]A^Uh{AnTlF@]TaTV~+^
            { ZORAS_RIVER,
              "In water below large waterfall, between the four red rupees.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 4220, 520, -1400 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS &&
                         (HookshotOrBoomerang || (CanUse(IRON_BOOTS) && (CanUse(BOW) || CanUse(SLINGSHOT))));
              } } },
            // https://noclip.website/#oot3d/spot03;ShareData=AQC~4UWf?i9fA-~9L]g9Wgi5lRi$_8ULv?}9v)A~WJ2xVUD}3mUqkMmUUVdN+^
            { ZORAS_RIVER,
              "In small wall tree, left of large waterfall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 4050, 1280, -1550 },
                  { 27000, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot03;ShareData=ANmj~9zSU&T|sSSUG)4PWBQFZ5X/=uUiem)9f!_PVt*[G9HP_69aZ/89hzfj+^
            { ZORAS_RIVER,
              "Under stone bridge near logs where frogs used to be.",
              GsScene{ 0x54 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1160, 300, -850 },
                  { -32768, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[ZR_GS_NEAR_RAISED_GROTTOS] = new GoldSkulltulaData( //
        ZR_GS_NEAR_RAISED_GROTTOS, 0x11, 0x10, GS_AGE_ADULT, nullptr,
        // Original
        {
            ZORAS_RIVER,
            GsScene{ 0x54 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot03;ShareData=AQa$,97b?|9G,gr9s&;Q=J/DZ5@qDhUd_&r9SO@=V9HjhUaB]r9Pj([92WpDV[
            { ZR_FRONT,
              "Near entrance from Hyrule Field, high on wall between grass.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1335, 450, 1480 },
                  { 16384, -22000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); } } },
            // https://noclip.website/#oot3d/spot03;ShareData=AOG^)9iBxL8g2$p833miV7j_k5&gUGUeGG39WZxjWNF2+Tn?AY9b[h|9pe1WVt
            { ZORAS_RIVER,
              "On mountain out of bounds, near grotton entrance.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 210, 1100, 490 },
                  { 16384, -30000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); } } },
            // https://noclip.website/#oot3d/spot03;ShareData=AYb)J96t+!8jl[kTt/4&WC8266D{rtUm{O&UJumTV!YwK8r^=UT}IH29k_7A+^
            { ZORAS_RIVER,
              "Hiding behind gossip stone on raised platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 800, 570, -1100 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
        });

    gsTable[ZD_GS_FROZEN_WATERFALL] = new GoldSkulltulaData( //
        ZD_GS_FROZEN_WATERFALL, 0x11, 0x40, GS_AGE_ADULT, nullptr,
        // Original
        {
            ZORAS_DOMAIN,
            GsScene{ 0x58 },
            Room{ 1 },
            { [] {
                return IsAdult && CanGetNightTimeGS &&
                       (HookshotOrBoomerang || CanUse(SLINGSHOT) || Bow ||
                        (MagicMeter && (MasterSword || BiggoronSword)));
            } },
        },
        {
            // https://noclip.website/#oot3d/spot07;ShareData=AMN:PT1Ph$T_WM$9n(m5=X8-E59FErUn~TxT@/|O+~=CPUsD)w8eGjXT?NQX+^
            { ZORAS_DOMAIN,
              "On wall in entrance to unicorn fountain.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchZDOoBJumpSlash); } },
              PosRot{
                  { -745, -460, -695 },
                  { 16384, -16384, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsAdult && CanSurviveUnderwaterFor(16) && CanUse(IRON_BOOTS) &&
                           (CanUse(HOOKSHOT) || CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot07;ShareData=AL&,_Uc^(A8H@L88[qLX+$n:UQ&lg]UhWe/8pcnBVkzeqT44(pTY1ZKUpN@o+^
            { ZORAS_DOMAIN,
              "On wall inside frozen waterfall, where big chest used to be for child.",
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchZDOoBJumpSlash); } },
              PosRot{
                  { -195, 50, -1125 },
                  { 16384, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] { return IsAdult && CanSurviveUnderwaterFor(8) && CanUse(IRON_BOOTS) && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot07;ShareData=AQI(B9x*+Q8rWf!8sn=[WC1&*Q9/KCUZE;s9Qf|dV|R@aTYn0)9WQQI9t|yV=a
            { ZD_BEHIND_KING_ZORA,
              "Behind the metal Zora emblem behind King Zora.",
              GsScene{ 0x58 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 625, 1190, -1910 },
                  { 16384, -32768, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot07;ShareData=AM7A-UltJYTkW~38p*y,WEEh^RXVl*Uh0qqUo*L1WHcdMTwPw39l^2,UviU_+^
            { ZORAS_DOMAIN,
              "Sat on by King Zora.",
              GsScene{ 0x58 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 625, 1012, -1780 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS &&
                         (DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) ||
                          (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult)) &&
                         CanAdultAttack;
              } } },
        });

    gsTable[ZF_GS_ABOVE_THE_LOG] = new GoldSkulltulaData( //
        ZF_GS_ABOVE_THE_LOG, 0x11, 0x04, GS_AGE_CHILD, nullptr,
        // Original
        {
            ZORAS_FOUNTAIN,
            GsScene{ 0x59 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsChild && CanGetNightTimeGS &&
                         (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot08;ShareData=AXg;RTfhwsUoPg[Un3Bn=FCtA6WGP}Ue7r?95fuK+;~ZD94mriTULr(TNywV+d
            { ZORAS_FOUNTAIN,
              "In water, under Jabu-Jabu's stone platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1500, 0, -50 },
                  { -32768, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (CanUse(DINS_FIRE) || (CanUse(IRON_BOOTS) && CanUse(HOOKSHOT)));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=AGQqeUMYknUc||Q9K|gi=FNR@RqQ7TUK)_kUW}S]V6?rvUXt{T9b9j2T_?*dV[
            { ZORAS_FOUNTAIN,
              "On end of branch of the large log in water.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1330, 253, 1635 },
                  { 0, 0, -2000 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/spot08;ShareData=AZ,vST]^IyUXU:)95tGL=S:|@6Mtm[UkIHDUvs~Z=KA&dUvtC?9A/HRT@G:TVS
            { ZORAS_FOUNTAIN,
              "At bottom of lake, where heart piece if for adult.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return AgeItemsInLogic && IronBootsAsChild &&
                         (HookshotAsChild || GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) ||
                          GlitchEnabled(GlitchSuperStab, GlitchDifficulty::NOVICE));
              } },
              PosRot{
                  { 0, -1450, 0 },
                  { 0, 0, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS && CanSurviveUnderwaterFor(16, 24) && CanUse(IRON_BOOTS) &&
                          CanUse(HOOKSHOT);
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && CanSurviveUnderwaterFor(16, 24) && CanUse(IRON_BOOTS) &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
        });

    gsTable[ZF_GS_TREE] = new GoldSkulltulaData( //
        ZF_GS_TREE, 0x11, 0x80, GS_AGE_CHILD, nullptr,
        // Original
        {
            ZORAS_FOUNTAIN,
            GsScene{ 0x59 },
            Room{ 0 },
            { [] { return IsChild; } },
        },
        {
            // https://noclip.website/#oot3d/spot08;ShareData=AZh!$TssBD8-=aa9n;[}V]MzfRPo,JUla[88*eOVVkPoHUXUyIS,BO~TfYZ)Vt
            { ZORAS_FOUNTAIN,
              "On east wall, where deep water begins.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1600, 100, 415 },
                  { 15000, -16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=AKSLVUmrl09r;MKUWL&(WCT~ZRU+t8Ut-6qUdZ5^WK|Wc9wz_d9G^:TUFimHV[
            { ZORAS_FOUNTAIN,
              "Top of hidden cave, on floor near edge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return GlitchEnabled(GlitchASlide, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { 940, 906, 1325 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::NOVICE);
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=ADP]j94RyoTZE&A8?Sv++8F]i5(219Us89ST*Ul+V(|)*T$:|~UFBdr92&LEV[
            { ZORAS_FOUNTAIN,
              "Above entrance to Great Fairy Fountain.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return GlitchEnabled(GlitchSeamWalk, GlitchDifficulty::ADVANCED) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                          (GlitchEnabled(GlitchSeamWalk, GlitchDifficulty::INTERMEDIATE) ||
                           GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE)));
              } },
              PosRot{
                  { 91, 570, 3031 },
                  { -8192, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                            (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::ADVANCED) && CanChildAttack) ||
                            (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                             CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)));
                } } },
        });

    gsTable[ZF_GS_HIDDEN_CAVE] = new GoldSkulltulaData( //
        ZF_GS_HIDDEN_CAVE, 0x11, 0x20, GS_AGE_ADULT, nullptr,
        // Original
        {
            ZORAS_FOUNTAIN,
            GsScene{ 0x59 },
            Room{ 0 },
            { [] {
                 return IsAdult && CanGetNightTimeGS && CanUse(SILVER_GAUNTLETS) && CanBlastOrSmash &&
                        HookshotOrBoomerang;
             },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS &&
                         CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::INTERMEDIATE) && HookshotOrBoomerang;
              } },
        },
        {
            // https://noclip.website/#oot3d/spot08;ShareData=ACbZ=UYG[EUFMl!9TMq==H*O?5$s?6UoD]4UN]A5+*kC0UNx809epn;Utem}WP
            { ZORAS_FOUNTAIN,
              "In water, at bottom of tree in south-west pond.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1220, -330, 2320 },
                  { 16384, -2000, 0 },
              },
              { [] {
                   return IsAdult && CanGetNightTimeGS &&
                          (CanUse(LONGSHOT) || (CanUse(IRON_BOOTS) && CanUse(HOOKSHOT)) ||
                           ((CanUse(IRON_BOOTS) || GoldScale) && (CanUse(BOW) || CanUse(SLINGSHOT))));
               },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && (CanUse(IRON_BOOTS) || GoldScale) &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=AYQT)959X!9QV2gURNZ*=AcZQRc}oeUh{gDUsr*oV+J(L9bW{IUQsmy9j=;aV[
            { ZORAS_FOUNTAIN,
              "On large rock south of icebergs.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -690, 290, 950 },
                  { 4000, 26000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(SCARECROW); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                            CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=AXTJT8sN/KUijgnUHTin+,tmt5(NKKUC?g[9y?Y_=Y6Fl9osW487^()89@&{+d
            { ZORAS_FOUNTAIN,
              "In water, under first stationary iceberg.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1150, -335, -30 },
                  { -32768, 0, 0 },
              },
              { [] {
                   return IsAdult && CanGetNightTimeGS && CanSurviveUnderwaterFor(16) && CanUse(IRON_BOOTS) &&
                          CanUse(LONGSHOT);
               },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && CanSurviveUnderwaterFor(8) && CanUse(IRON_BOOTS) &&
                           (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot08;ShareData=Aa}BdT:~@NUKd(K9ke:4WFPz:6F8ZYUe([?T^eeFV?75uUWvp78x9WIT$ce)Vt
            { ZORAS_FOUNTAIN,
              "On east mountain ledge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1600, 220, 60 },
                  { 3000, -21000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
        });
}
