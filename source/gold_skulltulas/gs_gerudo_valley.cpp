#include "gold_skulltulas.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_GerudoValley() {
    gsTable[GV_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        GV_GS_BEAN_PATCH, 0x13, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            GV_UPPER_STREAM,
            GsScene{ 0x5A },
            Room{ 0 },
            { [] { return IsChild && CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot09;ShareData=AOD+G95[U_T)W&~9y~h}Vz!:UQ:,uzUVwb6UZ1&{+7JCEUqqa;UTp$[9h=V]V[
            { GV_GROTTO_LEDGE,
              "By other end of ledge, opposite of silver boulder.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 330, -555, 700 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot09;ShareData=Aag&-Uwf@x9Zzi_Us;We=NyL86kgXlUqS9SUi8WZV;~3,94u}R9L9m&UM[rWVt
            { GV_FORTRESS_SIDE,
              "In southmost crate.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return Settings::ShuffleOverworldEntrances || (HookshotAsChild && AgeItemsInLogic) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                          GlitchEnabled(GlitchHover, GlitchDifficulty::NOVICE)) ||
                         GlitchEnabled(GlitchSeamWalk, GlitchDifficulty::HERO);
              } },
              PosRot{
                  { -765, 31, 155 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot09;ShareData=AVNR290gLQUEJICUdZ~p+5!r66Ure}Uk)RF9Q!3M+?Le291Vh_9fxud9i!xWV[
            { GV_CRATE_LEDGE,
              "On wall above the ledge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -405, -400, 1450 },
                  { 16384, 16384, 0 },
              },
              { [] {
                   return IsChild && CanGetNightTimeGS &&
                          (HookshotOrBoomerang ||
                           (ChildCanAccess(GERUDO_VALLEY) && (CanUse(SLINGSHOT) || CanUse(BOW))));
               },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           ((Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                             CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) ||
                            (ChildCanAccess(GERUDO_VALLEY) &&
                             (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                              CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE))));
                } } },
        });

    gsTable[GV_GS_SMALL_BRIDGE] = new GoldSkulltulaData( //
        GV_GS_SMALL_BRIDGE, 0x13, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            GERUDO_VALLEY,
            GsScene{ 0x5A },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsChild && CanGetNightTimeGS &&
                         (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot09;ShareData=AGP]y8?^Or9K,D&9tp;{VLoGNQ?C,/Unci?9cHskUG}R2Uj+N:87[So8_Nls+5
            { GERUDO_VALLEY,
              "On inward bridge hookshot target, Hyrule Field side.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 385, 165, -120 },
                  { 16384, -16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot09;ShareData=ACCAzUmIeVTLp~pTlWt-+~W/(5?sKrUY8ZI9G/_S=QLIV84{:hUM?sSUY-Ul=a
            { GV_UPPER_STREAM,
              "Behind bottom left of large waterwall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -250, -1880, -2695 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
            // https://noclip.website/#oot3d/spot09;ShareData=AW{?(9V-m^8@@GDUkJe0+7RyL6m60IUeBJET,!px+T+h:96-0:Tnrou9WZDQ+5
            { GERUDO_VALLEY,
              "On gate behind the Gerudo in white.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -385, -40, -120 },
                  { 16384, 16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
        });

    gsTable[GV_GS_PILLAR] = new GoldSkulltulaData( //
        GV_GS_PILLAR, 0x13, 0x04, GS_AGE_ADULT, nullptr,
        // Original
        {
            GV_FORTRESS_SIDE,
            GsScene{ 0x5A },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/kakusiana;ShareData=AN4C^UqA:V7|psiTWE9]U*(i$5;{=sUkS4;T)09_VWbsB8PBBZ9O{ZEUhc?}V[
            { GV_OCTOROK_GROTTO,
              "On wall at the end of the grotto.",
              GsScene{ 0x3E },
              Room{ 5 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 8, 50, 608 },
                  { 16384, 0, 0 },
              },
              { [] {
                   return IsAdult &&
                          ((CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(8) && CanUse(HOOKSHOT)) || CanUse(LONGSHOT));
               },
                /*Glitched*/
                [] {
                    return IsAdult && (Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE));
                } } },
            // https://noclip.website/#oot3d/spot09;ShareData=ABF91UWo-uSjv2MS?@[@U=/KPRI*-5UXTJ$9M[^S=hsrm7;B@ZT{imiUr[)rWP
            { GV_LOWER_STREAM,
              "Behind last waterfall, up on the middle of the wall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 0, -3030, 1790 },
                  { 18000, 0, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS && CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(8) &&
                         CanUse(HOOKSHOT);
              } } },
            // https://noclip.website/#oot3d/spot09;ShareData=AY2,KUg}!@9OlCDUiCkjWM@&E6HP$eUaP*^UcqK{+4l/G9nJ7C9MO7MUu4Z2VS
            { GERUDO_VALLEY,
              "In the middle of the three rocks in the pond under the wooden bridge.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1625, -202, -20 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
        });

    gsTable[GV_GS_BEHIND_TENT] = new GoldSkulltulaData( //
        GV_GS_BEHIND_TENT, 0x13, 0x08, GS_AGE_ADULT, nullptr,
        // Original
        {
            GV_FORTRESS_SIDE,
            GsScene{ 0x5A },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS &&
                         CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/spot09;ShareData=Aa}SSUtJ*mT)=+B9N[=UWDA~c6hZt~Ud1k(UQw4(V==^yUPTCJ9OB~MUcmX8+^
            { GERUDO_VALLEY,
              "Inside north red boulder on Hyrule Field side.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 865, 85, -770 },
                  { 0, 0, 2000 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(MEGATON_HAMMER); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && CanUse(STICKS) &&
                           ((CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) && CanTakeDamageTwice) ||
                            CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED));
                } } },
            // https://noclip.website/#oot3d/tent;ShareData=AG0YXUkH,UUTO_C9i9j++pZ095X&}!UmKymT^F[VV~yLIUbUui9Wbu/Ud=v/Uw
            { GV_CARPENTER_TENT,
              "In the corner furthest away from the camera.",
              GsScene{ 0x39 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] { return GlitchEnabled(GlitchRestrictedItems, GlitchDifficulty::NOVICE); } },
              PosRot{
                  { 100, 0, -135 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsAdult && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           (HasBoots || (FaroresWind && FaroresWindAnywhere) || HasBottle) &&
                           (HasExplosives || CanUse(DINS_FIRE));
                } } },
            // https://noclip.website/#oot3d/spot09;ShareData=AC5pxT*DgQRSYmZ9okNxVv^0*RDuFRUsl&PRJIbz=n]N+UnQ|b5!z(-T{RJ7=a
            { GV_UPPER_STREAM,
              "Bottom right of waterfall, in the corner where you can stand.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 683, -2180, -2675 },
                  { 18000, -16384, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
        });

    gsTable[GF_GS_ARCHERY_RANGE] = new GoldSkulltulaData( //
        GF_GS_ARCHERY_RANGE, 0x14, 0x01, GS_AGE_ADULT, nullptr,
        // Original
        {
            GF_ARCHERY_RANGE,
            GsScene{ 0x5D },
            Room{ 1 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot12;ShareData=AKc+cTozaU9Bz(k9wp4kWlzu55-NO!UdUSh8]R2KV)//DUnnBPS9q^HTkzP_=a
            { GF_ARCHERY_RANGE,
              "In the center of the largest target.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 4520, 1720, -2300 },
                  { 12000, -16384, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot12;ShareData=ARZck9gcH@9S!17Uue(zWiV4WRC_lSUs)K6UMmT0WDc!&9q[~FUA(9=9c4&B+5
            { GF_ARCHERY_RANGE,
              "On top of the mountain to the right after entering the archery range.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2610, 1755, -40 },
                  { 5000, 24576, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE) ||
                            (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE) &&
                             CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE))) &&
                           CanAdultAttack;
                } } },
            // https://noclip.website/#oot3d/spot12;ShareData=AY2]EUl_Tr8Ec({82/J;Wp)p|6Ku1$UY~]u8+BgdWD,g^Tkz{dTuI5RUlVctV[
            { GF_ARCHERY_RANGE,
              "On the opposite target from original location, on the side facing away.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3360, 1725, 505 },
                  { 16384, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot12;ShareData=AT6G)8qhsY9enOxUuY4?V^ZnM5yS4sUc~:PUH9-?V)0G~90[TVTUqLg82=TO+5
            { GF_ARCHERY_RANGE,
              "On the hanging sign on the path up to, and facing, archery range",
              GsScene{ 0x5D },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1100, 895, -440 },
                  { 16384, 16384, 0 },
              },
              {} },
        });

    gsTable[GF_GS_TOP_FLOOR] = new GoldSkulltulaData( //
        GF_GS_TOP_FLOOR, 0x14, 0x02, GS_AGE_ADULT, nullptr,
        // Original
        {
            GERUDO_FORTRESS,
            GsScene{ 0x5D },
            Room{ 0 },
            { [] {
                return IsAdult && CanGetNightTimeGS &&
                       (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || LogicGerudoKitchen) &&
                       CanAdultAttack;
            } },
        },
        {
            // https://noclip.website/#oot3d/spot12;ShareData=ABE:dUjQv@9c{GFUooT]V82_K5$:FJUi-WUUFddQWMAL,9v{[C9W/{TUc!jg=a
            { GERUDO_FORTRESS,
              "In crate above jail.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 40, 1113, -3000 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsAdult && CanGetNightTimeGS && (CanUse(SCARECROW) || CanUse(HOVER_BOOTS)) && CanUse(HOOKSHOT);
              } } },
            // https://noclip.website/#oot3d/spot12;ShareData=AY9W19QF329Mf$DUhXRy=F~hMRr2F1Uk(JTUL)i^V$OQr9op,1T,Kau9gO3d=a
            { GERUDO_FORTRESS,
              "By the Gerudo that opens the gate to Haunted Wasteland, on the stone thing that's part of the gate.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1030, 670, -3217 },
                  { 16384, 26000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && GerudoToken && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot12;ShareData=AFLD*UdGv;8s&)^UR/uf+_j33Rd[a7UYC^TT9S))V&=nk9JjeW8)v:NUs-h6+^
            { GERUDO_FORTRESS,
              "High up on pole on the center rock.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -378, 720, -2235 },
                  { 16384, 6000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/gerudoway;ShareData=AYk:E9t$|B8mWpqTmr5hWL-&fRFD59Up5;kUjeZNV4TkK8=EHsUYrZ!9uTV9+^
            { GERUDO_FORTRESS,
              "In kitchen inside hideout, in the large soup pot.",
              GsScene{ 0xC },
              Room{ 3 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1940, 70, -575 },
                  { 0, 0, 0 },
              },
              { [] {
                  return IsAdult && (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT)) &&
                         (HookshotOrBoomerang || (CanTakeDamage && CanAdultAttack));
              } } },
        });

    gsTable[WASTELAND_GS] = new GoldSkulltulaData( //
        WASTELAND_GS, 0x15, 0x02, GS_AGE_BOTH, nullptr,
        // Original
        {
            HAUNTED_WASTELAND,
            GsScene{ 0x5E },
            Room{ 0 },
            { [] { return HookshotOrBoomerang; },
              /*Glitched*/
              [] { return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } },
        },
        {
            // Carpet not drawn in noclip
            { HAUNTED_WASTELAND,
              "In the back of the floating carpet.",
              GsScene{ 0x5E },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1435, -345, 3565 },
                  { 0, 0, 0 },
              },
              { [] { return CanGetNightTimeGS && CanJumpslash; } } },
            // https://noclip.website/#oot3d/spot13;ShareData=AaVOa9kpM+8h],NTtS}YWHpjFROM~SUe[:cUCd}!V71/v8tGi4T*?rV93dE1=a
            { HAUNTED_WASTELAND,
              "On the back of the eye of truth tablet.",
              GsScene{ 0x5E },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 645, 255, -2265 },
                  { 16384, -32768, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/spot13;ShareData=AT(G89HMl89eQU8Uf@sP=BeUZRJ07lUew6*UG}_CV7$xn9uQ)JT8n4o9L&wL+^
            { WASTELAND_NEAR_COLOSSUS,
              "In crate near entrance to Desert Colossus.",
              GsScene{ 0x5E },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1530, 80, -970 },
                  { 0, 0, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/spot13;ShareData=AXPkEUPe;_9T[Q|9ncqKWa@W~RVGa{Uo4X$9JKdN+};0;Ukz(CT27QDT{3F8WP
            { WASTELAND_NEAR_FORTRESS,
              "High up on left pole near beginning.",
              GsScene{ 0x5E },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 4245, -150, 3103 },
                  { 16384, -16384, 0 },
              },
              { [] { return CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[COLOSSUS_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        COLOSSUS_GS_BEAN_PATCH, 0x15, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            DESERT_COLOSSUS,
            GsScene{ 0x5C },
            Room{ 0 },
            { [] { return IsChild && CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot11;ShareData=AVKy69w5M9Tb7LX86JDQWBikL5tZ,}T)L4VUb_;tV@EIDTZUyQUZ6C}9H|UlV[
            { DESERT_COLOSSUS,
              "In the bottom center of the dried pond.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 815, -90, 2210 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot11;ShareData=AQRDf9UfBi9n[s|UbJnOWIcjO6WEwAUsJT5UZ{i!VyN7j9rTw1UD;Ot9KGz;Vt
            { DESERT_COLOSSUS,
              "In sand between the two pieces of rubble and the small stone.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1480, 132, 625 },
                  { 1000, 8000, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot11;ShareData=AbHzCUiWO48z,pE8{{T~WT~@IRJi&9Uf)QY9O!ULV+!$xT;6r+UL$W5Uq?2j+^
            { DESERT_COLOSSUS,
              "High up on right tree to Great Fairy Fountain.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2410, 300, -1405 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot11;ShareData=AX{D(9Tv/tT8s[PUh(kk=V6e)RZa*=Ury,A8/e0&V_{OR9mT)M89l0q9aPVa+^
            { DESERT_COLOSSUS,
              "On wall in corner of desert to the right of Spirit Temple entrance.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -2005, 300, -1270 },
                  { 16384, 16384, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
        });

    gsTable[COLOSSUS_GS_HILL] = new GoldSkulltulaData( //
        COLOSSUS_GS_HILL, 0x15, 0x04, GS_AGE_ADULT, nullptr,
        // Original
        {
            DESERT_COLOSSUS,
            GsScene{ 0x5C },
            Room{ 0 },
            { [] {
                 return IsAdult && CanGetNightTimeGS && CanAdultAttack &&
                        (CanPlantBean(DESERT_COLOSSUS) || CanUse(LONGSHOT) || (LogicColossusGS && CanUse(HOOKSHOT)));
             },
              /*Glitched*/
              [] {
                  return IsAdult && CanGetNightTimeGS && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::EXPERT) &&
                         CanShield && CanAdultAttack;
              } },
        },
        {
            // https://noclip.website/#oot3d/spot11;ShareData=Aam[PUcs,NTio^o8qHb-=U?p0RTLHgUWa~/Ua)o)V[{]{TiR&09xUY[UuY9,+5
            { COLOSSUS_MEGALITH,
              "On top, north end.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -660, 462, -310 },
                  { 3000, -8192, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/spot11;ShareData=AHUWuUh[1A9MBS-UR$nB=MX1SRNdS4Ukch(UBqy9Vwf^H9d|!y9W=40UW:qE=a
            { DESERT_COLOSSUS,
              "On edge-of-map hill north of warp platform.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1070, 292, -2860 },
                  { 3000, 4000, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && CanUse(HOVER_BOOTS) &&
                           CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED);
                } } },
        });

    gsTable[COLOSSUS_GS_TREE] = new GoldSkulltulaData( //
        COLOSSUS_GS_TREE, 0x15, 0x08, GS_AGE_ADULT, nullptr,
        // Original
        {
            DESERT_COLOSSUS,
            GsScene{ 0x5C },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && HookshotOrBoomerang; } },
        },
        {
            // https://noclip.website/#oot3d/spot11;ShareData=AI81g9xDru8*;{~T-ZSw=NI6v6DY(qUo3!bUmFv?WC!G]9gfKVUXBzB9uYYIVt
            { COLOSSUS_MEGALITH,
              "On top, south end.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -645, 404, 290 },
                  { 2000, -16384, 0 },
              },
              { [] { return CanGetNightTimeGS && (CanChildAttack || CanAdultAttack); } } },
            // https://noclip.website/#oot3d/spot11;ShareData=AX32EUs{Dc8-{9DUQFg|Vwa]dQr*7QUdBw2UtOrwV([iX9L0bj96@tJUX7QpV[
            { DESERT_COLOSSUS,
              "On top of south hill.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 320, 465, 1315 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanPlantBean(DESERT_COLOSSUS) && CanAdultAttack; },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS && CanUse(HOVER_BOOTS) &&
                           CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED);
                } } },
        });
}
