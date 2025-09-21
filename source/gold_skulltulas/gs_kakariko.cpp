#include "gold_skulltulas.hpp"
#include "enemizer_logic.hpp"

using namespace GoldSkulltulas;
using namespace Logic;
using namespace Settings;

void GsTable_Init_Kakariko() {
    gsTable[KAK_GS_HOUSE_UNDER_CONSTRUCTION] = new GoldSkulltulaData( //
        KAK_GS_HOUSE_UNDER_CONSTRUCTION, 0x10, 0x08, GS_AGE_CHILD, nullptr,
        // Original
        {
            KAKARIKO_VILLAGE,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS; } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AJ3g{9Cl:@9frO*Um9$MV*{nMQ]kghUvKz&UOTnmWH6v]9mSZsTrpTS8[)}DVt
            { KAK_BACKYARD,
              "Behind Windmill: Left",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1598, 520, 650 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=ANkC39I]q)9j7fmUh6h$VwO/hQ!tLTUwC/3UV_zpV:Y6897WX@UFuJB9F,JMV[
            { KAKARIKO_VILLAGE,
              "On wooden beam of construction, by hidden read rupee.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 170, 300, 1172 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AE$9YUFqa9T62i5Uvs1lWD1-wRSm@LUWsIi8]LkIV,J4n9vFfrT4usjUR&nKV[
            { KAKARIKO_VILLAGE,
              "On wall above crate by entrance to Graveyard.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1677, 269, 1363 },
                  { 16383, 16383, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot01;ShareData=APU&j90nvq9L80,Ur4_FV1:QcQ@ppTUpj]aUE:|{V4)oa9sP]DUJhis9d+eMV[
            { KAKARIKO_VILLAGE,
              "On hay pile inside cucco fence.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 255, 140, 1782 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AKN9K9yh~K8}HaHUEHlpWAqc!6M]C|Uh(*[UHW?,V1c;=9T;B}UUFzD9tVRS+d
            { KAK_BACKYARD,
              "Low on fence near well.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1080, 130, 35 },
                  { -16383, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AMj?|UBN9q9kBNtUjEZ6WGnoXQ}_|/UZIoVUdG=9Vx6mA90OJS9Pb]{UQGLlV[
            { KAKARIKO_VILLAGE,
              "In wall where you triple slash clip to get into Bottom of the Well with the cucco.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return GlitchEnabled(GlitchTripleSlashClip, GlitchDifficulty::NOVICE) ||
                         GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE);
              } },
              PosRot{
                  { 1244, 90, 1565 },
                  { 0, 0, 2048 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE));
                } } },
        });

    gsTable[KAK_GS_SKULLTULA_HOUSE] = new GoldSkulltulaData( //
        KAK_GS_SKULLTULA_HOUSE, 0x10, 0x10, GS_AGE_CHILD, nullptr,
        // Original
        {
            KAKARIKO_VILLAGE,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS; } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AJ3g{9Cl:@9frO*Um9$MV*{nMQ]kghUvKz&UOTnmWH6v]9mSZsTrpTS8[)}DVt
            { KAK_BACKYARD,
              "Behind Windmill: Middle-Left",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1598, 530, 595 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=ABQ?:93[s}UI*qO95/B2=uMYi6MhL,Ua^;&T)*/rV6@-fUb2xxUK~+:9pKDGV[
            { KAKARIKO_VILLAGE,
              "By the entrance to Hyrule Field, on the other wall by the guard.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -2144, 165, 1200 },
                  { 16383, -16383, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot01;ShareData=AX-FU9kTFrUOCUt91}Tr+?8m}6J*PqUnAnFUNTr6V~;_AUXHVOUM=8)93GQUV[
            { KAKARIKO_VILLAGE,
              "Besides the guard outside Impa's house.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -424, 240, 1780 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/kinsuta;ShareData=ADti$Uq@[h9UNJ@UNQ{6+3k9gQ:t/SUkZSSUF3;QVdV{A9fwbn9Qb/SUX/Ar+d
            { KAK_HOUSE_OF_SKULLTULA,
              "Inside House of Skulltula, on piano stool.",
              GsScene{ 0x50 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { -105, 20, -175 },
                  { 8192, 6000, 0 },
              },
              { [] { return IsChild && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)); },
                /*Glitched*/
                [] {
                    return IsChild && CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                           (HasBottle || (FaroresWind && FaroresWindAnywhere)) && (HasExplosives || CanUse(DINS_FIRE));
                } } },
        });

    gsTable[KAK_GS_GUARDS_HOUSE] = new GoldSkulltulaData( //
        KAK_GS_GUARDS_HOUSE, 0x10, 0x02, GS_AGE_CHILD, nullptr,
        // Original
        {
            KAKARIKO_VILLAGE,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS; } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AJ3g{9Cl:@9frO*Um9$MV*{nMQ]kghUvKz&UOTnmWH6v]9mSZsTrpTS8[)}DVt
            { KAK_BACKYARD,
              "Behind Windmill: Center",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1598, 535, 535 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AQ_Re94[/o9GpurUi?ERVhJ[RRZn4[UXyQAUHYKHWOO{n9o/ZHT^wxq9vbVU+^
            { KAKARIKO_VILLAGE,
              "By entrance to DMT, on the other side of the stone wall by the guard.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -136, 440, -1405 },
                  { 16383, 31000, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot01;ShareData=AXFMaUZN[*8*si!T[?/==D*A4Q$8OGUVS)YUH]AEV?ksZ8)PjE9IYx-Um6+E+5
            { KAKARIKO_VILLAGE,
              "In the crate below the guard's house.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -620, 220, -502 },
                  { 0, 13000, 16383 },
              },
              {} },
            // https://noclip.website/#oot3d/spot01;ShareData=AW6?kUHJeF9cH;bUf|e;WI5I4RHq*|UdC)RUP19JVwlh29tZr98!ID/US|5S+5
            { KAK_BACKYARD,
              "On back door to (adult) Potion Shop.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 561, 360, -592 },
                  { 0, -4000, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=ATFiNUOio7URkpx9jAK9=EUsj6ePAuUwL,-T*XEyV_8EbUaa&09C:DJT+GP*+^
            { KAKARIKO_VILLAGE,
              "Inside the Kak Bazaar shop, but actually in Kakariko.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return GlitchEnabled(GlitchTripleSlashClip, GlitchDifficulty::NOVICE) ||
                         GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE);
              } },
              PosRot{
                  { -400, 320, -690 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::HookshotClip, GlitchDifficulty::NOVICE));
                } } },
        });

    gsTable[KAK_GS_TREE] = new GoldSkulltulaData( //
        KAK_GS_TREE, 0x10, 0x20, GS_AGE_CHILD, nullptr,
        // Original
        {
            KAKARIKO_VILLAGE,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] { return IsChild && CanGetNightTimeGS; } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AJ3g{9Cl:@9frO*Um9$MV*{nMQ]kghUvKz&UOTnmWH6v]9mSZsTrpTS8[)}DVt
            { KAK_BACKYARD,
              "Behind Windmill: Middle-Right",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1598, 540, 475 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=ATf1J8]c@?UVT7r9vFUX=Wjyw6W_:SUYdN^UfaQlVjIsvUfs:+TnFi(84Ub:V[
            { KAKARIKO_VILLAGE,
              "In front of the guy under the tree.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -947, 5, 532 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/spot01;ShareData=ADUL+Udk2jUSMDF900Zc+|Xri6Pk9dUi3NbUJ4M(Vl=QqUc4ud9dh4VUW^yfVS
            { KAKARIKO_VILLAGE,
              "Inside crate near Carpenter Boss's door.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -50, 0, -55 },
                  { 0, 0, 0 },
              },
              {} },
            // https://noclip.website/#oot3d/kakusiana;ShareData=AR$j3UlUA/8MbZ}8(:/GWFuyCQ7n[3Ua?WJ9S$/bVYFKQT&^m(UARs;UpAFV+5
            { KAK_REDEAD_GROTTO,
              "High on wall between redeads.",
              GsScene{ 0x3E },
              Room{ 2 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1805, 120, -585 },
                  { 16384, 2000, 0 },
              },
              { [] { return IsChild && HookshotOrBoomerang; },
                /*Glitched*/
                [] {
                    return IsChild && Bombs && CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE) &&
                           CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                } } },
        });

    gsTable[KAK_GS_WATCHTOWER] = new GoldSkulltulaData( //
        KAK_GS_WATCHTOWER, 0x10, 0x04, GS_AGE_CHILD, nullptr,
        // Original
        {
            KAKARIKO_VILLAGE,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] {
                 return IsChild && CanGetNightTimeGS && (Slingshot || HasBombchus || CanUse(BOW) || CanUse(LONGSHOT));
             },
              /*Glitched*/
              [] {
                  return IsChild && CanGetNightTimeGS &&
                         (CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) ||
                          CanDoGlitch(GlitchType::SuperStab, GlitchDifficulty::NOVICE) ||
                          (Sticks && CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE)));
              } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AJ3g{9Cl:@9frO*Um9$MV*{nMQ]kghUvKz&UOTnmWH6v]9mSZsTrpTS8[)}DVt
            { KAK_BACKYARD,
              "Behind Windmill: Right",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 1598, 545, 420 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AWI_4UQ[{^T}(7=90{_3V4[vGQ7l}2Uj=FXUY(![V?S!4Ups1]9YP{wUSs9vVt
            { KAKARIKO_VILLAGE,
              "On Carpenter Boss's house roof, in corner closest to well.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 286, 220, 282 },
                  { 5000, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AWpB,T1gCl9G8)qUnVXjWO6qdRBE{FUi|NJURD:IV9wXu9hT|88OEUaT9QK{U!
            { KAK_BACKYARD,
              "On door to Granny's Potion Shop.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] { return LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic); } },
              PosRot{
                  { 753, 230, 30 },
                  { 0, 0, -16383 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AT[Qs95[v,UB-e19soLGV_|,|6U(/fUptM9UpPygV-le|UbrY/ULt,R9kj[Z+^
            { KAK_BACKYARD,
              "Inside the Kak Potion shop, but actually in Kakariko.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return (LogicManOnRoof || (HookshotAsChild && AgeItemsInLogic)) &&
                         GlitchEnabled(GlitchTripleSlashClip, GlitchDifficulty::NOVICE);
              } },
              PosRot{
                  { 415, 320, -735 },
                  { 0, 0, 0 },
              },
              { [] { return false; },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS &&
                           CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE);
                } } },
        });

    gsTable[KAK_GS_ABOVE_IMPAS_HOUSE] = new GoldSkulltulaData( //
        KAK_GS_ABOVE_IMPAS_HOUSE, 0x10, 0x40, GS_AGE_ADULT, nullptr,
        // Original
        {
            KAK_IMPAS_ROOFTOP,
            GsScene{ 0x52 },
            Room{ 0 },
            { [] { return IsAdult && CanGetNightTimeGS && (CanJumpslash || CanUseProjectile); } },
        },
        {
            // https://noclip.website/#oot3d/spot01;ShareData=AS4@I8]oOUT^gid96aC2V*[Li6n2^*Ue1ZAULs!+V5RKZUg+mlT,E0!8-VS,V[
            { KAK_BACKYARD,
              "In silver boulder behind the windmill.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1435, 395, 1370 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && SilverGauntlets && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/spot01;ShareData=AVm8^T,LxU9qoQQUbGu5WGZS@RMgKIUvjs!Uh*V]V|-1@94eeK8se!=T7b9XV[
            { KAKARIKO_VILLAGE,
              "Inside the top of the windmill tower.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 1240, 901, 637 },
                  { 0, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsAdult && CanGetNightTimeGS &&
                           (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot01;ShareData=APdnxUW?wfT1yIf9PU*nV*e/FROEj=Ucz:LUQleB+-46]UT|cw9cVyWUn]X9V[
            { KAKARIKO_VILLAGE,
              "At the bottom of the well, on the left wall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { 888, -460, 462 },
                  { 18000, 0, 0 },
              },
              { [] { return IsAdult && CanGetNightTimeGS && CanAdultAttack; } } },
            // https://noclip.website/#oot3d/hakasitarelay;ShareData=ALW:1TY}CX9k}k~9HF)=Wnnf}Qn5ntT}FM49txxQ+)E?HUfPE9TtI0vTy=-|VS
            { KAK_WINDMILL,
              "High on wall, above music box man.",
              GsScene{ 0x48 },
              Room{ 6 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 3185, 190, 37 },
                  { 0, 0, 18000 },
              },
              { [] { return IsAdult && HookshotOrBoomerang; },
                /*Glitched*/
                [] { return IsAdult && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } } },
        });

    gsTable[GRAVEYARD_GS_WALL] = new GoldSkulltulaData( //
        GRAVEYARD_GS_WALL, 0x10, 0x80, GS_AGE_CHILD, nullptr,
        // Original
        {
            THE_GRAVEYARD,
            GsScene{ 0x53 },
            Room{ 1 },
            { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; },
              /*Glitched*/
              [] {
                  return IsChild && CanGetNightTimeGS &&
                         CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
              } },
        },
        {
            // https://noclip.website/#oot3d/spot02;ShareData=AMW]-UpO}28Q1NITv@S5=Rkp{RblcwUnhAVUP/A5Veif*8naMA9S~J[UV036V[
            { THE_GRAVEYARD,
              "On wall of Dampe's Hut closest to terrain wall.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -847, 35, 738 },
                  { 16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot02;ShareData=AV2a3S!$[1ULuSo92+I)V!ZgH6GLe}UsRr@UJXGVV[M?TUioE175sU5S8Uw9VS
            { GRAVEYARD_WARP_PAD_REGION,
              "On stone platform for casting Din's Fire to open Shadow Temple gate.",
              GsScene{ 0x53 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 2138, 124, 88 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
            // https://noclip.website/#oot3d/spot02;ShareData=AQ3a{Unah-UVCc296LdlWP+IJ6OSG?UmTRoUY{_5VuywvUdhQ29T{8hUCn/KVt
            { GRAVEYARD_WARP_PAD_REGION,
              "On right protrusion by Shadow Temple gate.",
              GsScene{ 0x53 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] {
                  return (HookshotAsChild && AgeItemsInLogic) ||
                         GlitchEnabled(GlitchSeamWalk, GlitchDifficulty::NOVICE) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                          GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE));
              } },
              PosRot{
                  { 2575, 360, 245 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && CanChildAttack &&
                           (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/hakaana_ouke;ShareData=AMCgIUlhe|UQhem9nb_qV=vs+Q9+~bUuiDIUW-$TVc=@pUcW8p9bm95Uv4AMVt
            { GRAVEYARD_COMPOSERS_GRAVE,
              "In poison water, right side, near wall.",
              GsScene{ 0x41 },
              Room{ 1 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 280, -20, 300 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanTakeDamage && CanChildAttack && CanDefeatEnemies(65, 0, 3); } } },
        });

    gsTable[GRAVEYARD_GS_BEAN_PATCH] = new GoldSkulltulaData( //
        GRAVEYARD_GS_BEAN_PATCH, 0x10, 0x01, GS_AGE_CHILD, nullptr,
        // Original
        {
            THE_GRAVEYARD,
            GsScene{ 0x53 },
            Room{ 1 },
            { [] { return CanPlantBugs && CanChildAttack; } },
        },
        {
            // https://noclip.website/#oot3d/spot02;ShareData=AMzJF88bI:UMXcFUs~KI=PH^oRL7P}Uaeoa9W3N?VdeTk9h?WY8iF$L88amSVt
            { THE_GRAVEYARD,
              "On wooden gate top sign, inwards towards graveyard.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -1003, 187, 270 },
                  { 0, 0, -16384 },
              },
              { [] { return IsChild && CanGetNightTimeGS && HookshotOrBoomerang; } } },
            // https://noclip.website/#oot3d/spot02;ShareData=ANsD09xMF_9Icr8UtKFX=DNo9Q(5-;Ua^&SUSSMlV~bI?94Hn:T0vG@94Yk:+5
            { THE_GRAVEYARD,
              "On heart piece ledge, low on wooden fence, in corner towards entrance to Kakariko.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ [] {
                  return (HookshotAsChild && AgeItemsInLogic) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                          GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE));
              } },
              PosRot{
                  { -1150, 310, -180 },
                  { -16384, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] { return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } } },
            // Scene missing from noclip?
            { GRAVEYARD_SHIELD_GRAVE,
              "Bathing in the center of the fairy fountain in shield grave.",
              GsScene{ 0x40 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ nullptr },
              PosRot{
                  { 990, -30, 10 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanBlastOrSmash; },
                /*Glitched*/
                [] {
                    return IsChild && CanChildAttack &&
                           Here(GRAVEYARD_SHIELD_GRAVE, [] { return GlitchBlueFireWall && BlueFire; });
                } } },
            // https://noclip.website/#oot3d/spot02;ShareData=ATkN99t:SAUUSRo90D!0WfV|!5([OSUf]e7US@~IV1Y6QUhxZOUU/Pq9u4!v+5
            { GRAVEYARD_WARP_PAD_REGION,
              "On left protrusion by Shadow Temple gate.",
              GsScene{ 0x53 },
              Room{ 0 },
              GsTimeCondition{ GS_TIME_ALWAYS },
              SettingRequirements{ [] {
                  return (HookshotAsChild && AgeItemsInLogic) ||
                         GlitchEnabled(GlitchSeamWalk, GlitchDifficulty::NOVICE) ||
                         (GlitchEnabled(GlitchISG, GlitchDifficulty::NOVICE) &&
                          GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE));
              } },
              PosRot{
                  { 2575, 360, -73 },
                  { 0, 0, 0 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanUse(LONGSHOT); },
                /*Glitched*/
                [] {
                    return IsChild && CanGetNightTimeGS && CanChildAttack &&
                           (CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE) ||
                            CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE));
                } } },
            // https://noclip.website/#oot3d/spot02;ShareData=AJ6&_T2_uO9aT!BUni_M=B9Q2QxlpbUvEILUIck)Vd_aG9oUv:8z}VTT31pLVt
            { THE_GRAVEYARD,
              "Behind R.I.P stone sign.",
              GsTimeCondition{ GS_TIME_NIGHT },
              SettingRequirements{ nullptr },
              PosRot{
                  { -773, 25, 270 },
                  { 0, 0, -16384 },
              },
              { [] { return IsChild && CanGetNightTimeGS && CanChildAttack; } } },
        });
}
