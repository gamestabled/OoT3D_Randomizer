#include "logic.hpp"
#include "settings.hpp"
#include <string>
#include <string_view>
#include <cstdio>
#include <algorithm>
#include <3ds.h>
#include <vector>

using namespace Settings;

namespace Logic {

  //Child item logic
  bool KokiriSword   = false;
  bool ZeldasLetter  = false;
  bool WeirdEgg      = false;
  bool HasBottle     = false;
  bool Bombchus      = false;
  bool Bombchus5     = false;
  bool Bombchus10    = false;
  bool Bombchus20    = false;
  bool MagicBean     = false;
  bool MagicBeanPack = false;
  bool RutosLetter   = false;
  bool Boomerang     = false;
  bool DinsFire      = false;
  bool FaroresWind   = false;
  bool NayrusLove    = false;
  bool LensOfTruth   = false;
  bool ShardOfAgony  = false;
  bool SkullMask     = false;
  bool MaskOfTruth   = false;

  //Adult logic
  bool Hammer        = false;
  bool IronBoots     = false;
  bool HoverBoots    = false;
  bool MirrorShield  = false;
  bool GoronTunic    = false;
  bool ZoraTunic     = false;
  bool Epona         = false;
  bool BigPoe        = false;
  bool GerudoToken   = false;
  bool FireArrows    = false;
  bool IceArrows     = false;
  bool LightArrows   = false;

  //Trade Quest
  bool PocketEgg     = false;
  bool PocketCucco   = false;
  bool Cojiro        = false;
  bool OddMushroom   = false;
  bool OddPoultice   = false;
  bool PoachersSaw   = false;
  bool BrokenSword   = false;
  bool Prescription  = false;
  bool EyeballFrog   = false;
  bool Eyedrops      = false;
  bool ClaimCheck    = false;

  //Trade Quest Events
  bool WakeUpAdultTalon   = false;
  bool CojiroAccess       = false;
  bool OddMushroomAccess  = false;
  bool OddPoulticeAccess  = false;
  bool PoachersSawAccess  = false;
  bool BrokenSwordAccess  = false;
  bool PrescriptionAccess = false;
  bool EyeballFrogAccess  = false;
  bool EyedropsAccess     = false;
  bool DisableTradeRevert = false;

  //Songs
  bool ZeldasLullaby    = false;
  bool SariasSong       = false;
  bool SunsSong         = false;
  bool SongOfStorms     = false;
  bool EponasSong       = false;
  bool SongOfTime       = false;
  bool MinuetOfForest   = false;
  bool BoleroOfFire     = false;
  bool SerenadeOfWater  = false;
  bool RequiemOfSpirit  = false;
  bool NocturneOfShadow = false;
  bool PreludeOfLight   = false;

  //Stones and Meddallions
  bool ForestMedallion = false;
  bool FireMedallion   = false;
  bool WaterMedallion  = false;
  bool SpiritMedallion = false;
  bool ShadowMedallion = false;
  bool LightMedallion  = false;
  bool KokiriEmerald   = false;
  bool GoronRuby       = false;
  bool ZoraSapphire    = false;

  //Dungeon Clears
  bool DekuTreeClear       = false;
  bool DodongosCavernClear = false;
  bool JabuJabusBellyClear = false;
  bool ForestTempleClear   = false;
  bool FireTempleClear     = false;
  bool WaterTempleClear    = false;
  bool SpiritTempleClear   = false;
  bool ShadowTempleClear   = false;

  //Trial Clears
  bool ForestTrialClear = false;
  bool FireTrialClear   = false;
  bool WaterTrialClear  = false;
  bool SpiritTrialClear = false;
  bool ShadowTrialClear = false;
  bool LightTrialClear  = false;

  //Progressive Items
  u8 ProgressiveBulletBag = 0;
  u8 ProgressiveBombBag   = 0;
  u8 ProgressiveMagic     = 0;
  u8 ProgressiveScale     = 0;
  u8 ProgressiveHookshot  = 0;
  u8 ProgressiveBow       = 0;
  u8 ProgressiveWallet    = 0;
  u8 ProgressiveStrength  = 0;
  u8 ProgressiveOcarina   = 0;

  //Keys
  u8 ForestTempleKeys          = 0;
  u8 FireTempleKeys            = 0;
  u8 WaterTempleKeys           = 0;
  u8 SpiritTempleKeys          = 0;
  u8 ShadowTempleKeys          = 0;
  u8 GanonsCastleKeys          = 0;
  u8 GerudoFortressKeys        = 0;
  u8 GerudoTrainingGroundsKeys = 0;
  u8 BottomOfTheWellKeys       = 0;

  //Boss Keys
  bool BossKeyForestTemple = false;
  bool BossKeyFireTemple   = false;
  bool BossKeyWaterTemple  = false;
  bool BossKeySpiritTemple = false;
  bool BossKeyShadowTemple = false;
  bool BossKeyGanonsCastle = false;

  //Gold Skulltula Count
  u8 GoldSkulltulaTokens = 0;

  //Drops and Bottle Contents Access
  bool DekuNutDrop      = false;
  bool NutPot           = false;
  bool NutCrate         = false;
  bool DekuBabaNuts     = false;
  bool DekuStickDrop    = false;
  bool StickPot         = false;
  bool DekuBabaSticks   = false;
  bool BugsAccess       = false;
  bool BugShrub         = false;
  bool WanderingBugs    = false;
  bool BugRock          = false;
  bool BlueFireAccess   = false;
  bool FishAccess       = false;
  bool FishGroup        = false;
  bool LoneFish         = false;
  bool FairyAccess      = false;
  bool GossipStoneFairy = false;
  bool BeanPlantFairy   = false;
  bool ButterflyFairy   = false;
  bool FairyPot         = false;
  bool FreeFairies      = false;
  bool FairyPond        = false;

  bool BuyBombchus5     = false;
  bool BuyBombchus10    = false;
  bool BuyBombchus20    = false;

  /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
  /* These are used to simplify reading the logic, but need to be updated
  /  every time a base value is updated.                       */

  bool Slingshot        = false;
  bool Ocarina          = false;
  bool BombBag          = false;
  bool MagicMeter       = false;
  bool Hookshot         = false;
  bool Longshot         = false;
  bool Bow              = false;
  bool GoronBracelet    = false;
  bool SilverGauntlets  = false;
  bool GoldenGauntlets  = false;
  bool SilverScale      = false;
  bool GoldScale        = false;

  bool ScarecrowSong    = false;
  bool Scarecrow        = false;
  bool DistantScarecrow = false;

  bool Bombs            = false;
  bool DekuShield       = false;
  bool HylianShield     = false;
  bool Nuts             = false;
  bool Sticks           = false;
  bool Bugs             = false;
  bool BlueFire         = false;
  bool Fish             = false;
  bool Fairy            = false;
  bool BottleWithBigPoe = false;

  bool HasBombchus      = false;
  bool FoundBombchus    = false;
  bool HasExplosives    = false;
  bool IsChild          = false;
  bool IsAdult          = false;
//bool IsGlitched       = false;
  bool CanBlastOrSmash  = false;
  bool CanChildAttack   = false;
  bool CanChildDamage   = false;
  bool CanCutShrubs     = false;
  bool CanDive          = false;
  bool CanLeaveForest   = false;
  bool CanPlantBugs     = false;
  bool CanRideEpona     = false;
  bool CanStunDeku      = false;
  bool CanSummonGossipFairy = false;
  bool CanSummonGossipFairyWithoutSuns = false;
  bool CanPlantBean        = false;
  bool CanOpenBombGrotto   = false;
  bool CanOpenStormGrotto  = false;
  bool BigPoeKill          = false;
  bool HookshotOrBoomerang = false;

  bool GuaranteeTradePath     = false;
  bool GuaranteeHint          = false;
  bool HasFireSource          = false;
  bool HasFireSourceWithTorch = false;

  bool CanFinishGerudoFortress = false;

  bool HasShield        = false;
  bool CanShield        = false;
  bool CanJumpslash     = false;
  bool CanUseProjectile = false;

  //Bridge Requirements
  bool HasAllStones          = false;
  bool HasAllMedallions      = false;
  bool CanBuildRainbowBridge = false;
  bool CanTriggerLACS        = false;

  //Other
  bool AtDay         = false;
  bool AtNight       = false;
  bool IsStartingAge = false;
  u8 Age             = 0;

  //Events
  bool ShowedMidoSwordAndShield  = false;
  bool CarpenterRescue           = false;
  bool GF_GateOpen               = false;
  bool DampesWindmillAccess      = false;
  bool DrainWell                 = false;
  bool GoronCityChildFire        = false;
  bool GCWoodsWarpOpen           = false;
  bool StopGCRollingGoronAsAdult = false;
  bool ChildWaterTemple          = false;
  bool RaiseWaterLevel           = false;
  bool KakarikoVillageGateOpen   = false;
  bool KingZoraThawed            = false;
  bool ForestTempleJoAndBeth     = false;
  bool ForestTempleAmyAndMeg     = false;
  bool LinksCow                  = false;
  bool AtDampeTime               = false;
  bool DeliverLetter             = false;

  /* --- END OF HELPERS AND LOCATION ACCESS --- */

  //Placement Tracking
  u8 AddedProgressiveBulletBags = 0;
  u8 AddedProgressiveBombBags   = 0;
  u8 AddedProgressiveMagics     = 0;
  u8 AddedProgressiveScales     = 0;
  u8 AddedProgressiveHookshots  = 0;
  u8 AddedProgressiveBows       = 0;
  u8 AddedProgressiveWallets    = 0;
  u8 AddedProgressiveStrengths  = 0;
  u8 AddedProgressiveOcarinas   = 0;
  u8 TokensInPool               = 0;

  //Event checking past
  bool DrainWellPast            = false;
  bool DampesWindmillAccessPast = false;
  bool DekuTreeClearPast        = false;
  bool GoronRubyPast            = false;
  bool ZoraSapphirePast         = false;
  bool ForestTrialClearPast     = false;
  bool FireTrialClearPast       = false;
  bool WaterTrialClearPast      = false;
  bool SpiritTrialClearPast     = false;
  bool ShadowTrialClearPast     = false;
  bool LightTrialClearPast      = false;
  bool BuyDekuShieldPast        = false;

  bool CanPlay(bool song) {
    return Ocarina && song;
  }

  static bool IsMagicItem(std::string_view item) {
    return item == "Dins Fire"    ||
           item == "Farores Wind" ||
           item == "Nayrus Love"  ||
           item == "Lens of Truth";
  }

  static bool IsAdultItem(std::string_view item) {
    return item == "Bow"              ||
           item == "Hammer"           ||
           item == "Iron Boots"       ||
           item == "Hover Boots"      ||
           item == "Hookshot"         ||
           item == "Longshot"         ||
           item == "Silver Gauntlets" ||
           item == "Golden Gauntlets" ||
           item == "Goron Tunic"      ||
           item == "Zora Tunic"       ||
           item == "Scarecrow"        ||
           item == "Distant Scarecrow";
  }

  static bool IsChildItem(std::string_view item) {
    return item == "Slingshot"    ||
           item == "Boomerang"    ||
           item == "Kokiri Sword" ||
           item == "Sticks"       ||
           item == "Deku Shield";
  }

  static bool IsMagicArrow(std::string_view item) {
    return item == "Fire Arrows" ||
           item == "Ice Arrows"  ||
           item == "Light Arrows";
  }

  bool HasItem(std::string_view itemName) {
    return (itemName == "Dins Fire"        && DinsFire)        ||
           (itemName == "Farores Wind"     && FaroresWind)     ||
           (itemName == "NayrusLove"       && NayrusLove)      ||
           (itemName == "Lens of Truth"    && LensOfTruth)     ||
           (itemName == "Bow"              && Bow)             ||
           (itemName == "Hammer"           && Hammer)          ||
           (itemName == "Iron Boots"       && IronBoots)       ||
           (itemName == "Hover Boots"      && HoverBoots)      ||
           (itemName == "Hookshot"         && Hookshot)        ||
           (itemName == "Longshot"         && Longshot)        ||
           (itemName == "Silver Gauntlets" && SilverGauntlets) ||
           (itemName == "Golden Gauntlets" && GoldenGauntlets) ||
           (itemName == "Goron Tunic"      && GoronTunic)      ||
           (itemName == "Zora Tunic"       && ZoraTunic)       ||
           (itemName == "Scarecrow"        && Scarecrow)       ||
           (itemName == "Distant Scarecrow"&& DistantScarecrow)||
           (itemName == "Slingshot"        && Slingshot)       ||
           (itemName == "Boomerang"        && Boomerang)       ||
           (itemName == "Kokiri Sword"     && KokiriSword)     ||
           (itemName == "Sticks"           && Sticks)          ||
           (itemName == "Deku Shield"      && DekuShield)      ||
           (itemName == "Fire Arrows"      && FireArrows)      ||
           (itemName == "Ice Arrows"       && IceArrows)       ||
           (itemName == "Light Arrows"     && LightArrows);

  }

  //Can the passed in item be used?
  bool CanUse(std::string_view itemName) {
    return (IsMagicItem(itemName)  && HasItem(itemName) && MagicMeter) ||
           (IsAdultItem(itemName)  && HasItem(itemName) && IsAdult)    ||
           (IsMagicArrow(itemName) && HasItem(itemName) && MagicMeter  && IsAdult && Bow) ||
           (IsChildItem(itemName)  && HasItem(itemName) && IsChild);
  }

  bool HasProjectile(std::string_view age) {
    return HasExplosives ||
           (age == "Child"  && (Slingshot || Boomerang)) ||
           (age == "Adult"  && (Hookshot  || Bow      )) ||
           (age == "Both"   && (Slingshot || Boomerang)  && (Hookshot || Bow)) ||
           (age == "Either" && (Slingshot || Boomerang   ||  Hookshot || Bow));
  }

  //Updates all logic helpers. Should be called whenever a non-helper is changed
  void UpdateHelpers() {
    Slingshot       = ProgressiveBulletBag >= 1;
    Ocarina         = ProgressiveOcarina   >= 1;
    MagicMeter      = ProgressiveMagic     >= 1;
    BombBag         = ProgressiveBombBag   >= 1;
    Hookshot        = ProgressiveHookshot  >= 1;
    Longshot        = ProgressiveHookshot  >= 2;
    Bow             = ProgressiveBow       >= 1;
    GoronBracelet   = ProgressiveStrength  >= 1;
    SilverGauntlets = ProgressiveStrength  >= 2;
    GoldenGauntlets = ProgressiveStrength  >= 3;
    SilverScale     = ProgressiveScale     >= 1;
    GoldScale       = ProgressiveScale     >= 2;

    Scarecrow        = Hookshot && CanPlay(ScarecrowSong);
    DistantScarecrow = Longshot && CanPlay(ScarecrowSong);

    //Drop Access
    DekuStickDrop = StickPot || DekuBabaSticks;
    DekuNutDrop   = NutPot   || NutCrate         || DekuBabaNuts;
    BugsAccess    = BugShrub || WanderingBugs    || BugRock;
    FishAccess    = LoneFish || FishGroup;
    FairyAccess   = FairyPot || GossipStoneFairy || BeanPlantFairy || ButterflyFairy || FreeFairies || FairyPond;


    //refills
    Bombs        = BombBag;
    Nuts         = DekuNutDrop || Nuts;
    Sticks       = DekuStickDrop || Sticks;
    Bugs         = HasBottle && BugsAccess;
    BlueFire     = HasBottle && BlueFireAccess;
    Fish         = HasBottle && FishAccess;
    Fairy        = HasBottle && FairyAccess;

    HasBombchus   = (BuyBombchus5 || BuyBombchus10 || BuyBombchus20 /*|| BombchuDrops*/) && (BombchusInLogic || BombBag);
    FoundBombchus = (BombchusInLogic && (Bombchus || Bombchus5 || Bombchus10 || Bombchus20)) || (!BombchusInLogic && BombBag);
    HasExplosives =  Bombs || (BombchusInLogic && HasBombchus);

    IsChild = Age == AGE_CHILD;
    IsAdult = Age == AGE_ADULT;
    IsStartingAge = StartingAge.Is(Age); //what's this for?

  //IsGlitched = false;

    CanBlastOrSmash = HasExplosives || CanUse("Hammer");
    CanChildAttack  = IsChild && (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire"));
    CanChildDamage  = IsChild && (Slingshot ||              Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire"));
    CanStunDeku     = IsAdult || (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire") || Nuts || DekuShield);
    CanCutShrubs    = IsAdult || Sticks || KokiriSword || Boomerang || HasExplosives;
    CanDive         = ProgressiveScale >= 1;
    CanLeaveForest  = OpenForest.IsNot(OPENFOREST_CLOSED) || IsAdult || DekuTreeClear;
    CanPlantBugs    = IsChild && Bugs;
    CanRideEpona    = IsAdult && Epona && CanPlay(EponasSong);
    CanSummonGossipFairy            = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime || SunsSong);
    CanSummonGossipFairyWithoutSuns = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime);
    CanPlantBean        = IsChild && (MagicBean || MagicBeanPack);
    CanOpenBombGrotto   = CanBlastOrSmash       && (ShardOfAgony || LogicGrottosWithoutAgony);
    CanOpenStormGrotto  = CanPlay(SongOfStorms) && (ShardOfAgony || LogicGrottosWithoutAgony);
    HookshotOrBoomerang = CanUse("Hookshot") || CanUse("Boomerang");

    GuaranteeTradePath     = ShuffleInteriorEntrances || ShuffleOverworldEntrances || LogicBiggoronBolero || CanBlastOrSmash || StopGCRollingGoronAsAdult;
  //GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints != "Agony");
    HasFireSource          = CanUse("Dins Fire") || CanUse("Fire Arrows");
    HasFireSourceWithTorch = HasFireSource || (IsChild && Sticks);

    //Gerudo Fortress
    CanFinishGerudoFortress = (GerudoFortress.Is(GERUDOFORTRESS_NORMAL)    && GerudoFortressKeys >= 4 && (IsAdult || KokiriSword) && ((IsAdult && (Bow || Hookshot || HoverBoots)) || GerudoToken || LogicGerudoKitchen)) ||
                              (GerudoFortress.Is(GERUDOFORTRESS_FAST)      && GerudoFortressKeys >= 1 && (IsAdult || KokiriSword)) ||
                              (GerudoFortress.IsNot(GERUDOFORTRESS_NORMAL) && GerudoFortress.IsNot(GERUDOFORTRESS_FAST));

    HasShield        = (IsAdult && HylianShield) ||                   (IsChild && DekuShield); //Mirror shield can't reflect attacks
    CanShield        = (IsAdult && (HylianShield || MirrorShield)) || (IsChild && DekuShield);
    CanJumpslash     = IsAdult || Sticks || KokiriSword;
    CanUseProjectile = HasExplosives || (IsAdult && (Bow || Hookshot)) || (IsChild && (Slingshot || Boomerang));

    //Bridge Requirements
    HasAllStones          = KokiriEmerald   && GoronRuby     && ZoraSapphire;
    HasAllMedallions      = ForestMedallion && FireMedallion && WaterMedallion && ShadowMedallion && SpiritMedallion && LightMedallion;
    CanBuildRainbowBridge = Bridge.Is(RAINBOWBRIDGE_OPEN)       ||
                           (Bridge.Is(RAINBOWBRIDGE_VANILLA)    && ShadowMedallion && SpiritMedallion) ||
                           (Bridge.Is(RAINBOWBRIDGE_STONES)     && HasAllStones) ||
                           (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS) && HasAllMedallions) ||
                           (Bridge.Is(RAINBOWBRIDGE_DUNGEONS)   && HasAllStones && HasAllMedallions) ||
                           (Bridge.Is(RAINBOWBRIDGE_TOKENS)     && GoldSkulltulaTokens >= TokenCount.Value<u8>());

    CanTriggerLACS = (LACSCondition == LACSCONDITION_VANILLA    && ShadowMedallion && SpiritMedallion) ||
                     (LACSCondition == LACSCONDITION_STONES     && HasAllStones)                       ||
                     (LACSCondition == LACSCONDITION_MEDALLIONS && HasAllMedallions)                   ||
                     (LACSCondition == LACSCONDITION_DUNGEONS   && HasAllStones && HasAllMedallions);

  }

  bool SmallKeys(u8 dungeonKeyCount, u8 requiredAmount) {
    return (dungeonKeyCount >= requiredAmount);
  }

  bool EventsUpdated() {

      if (DekuTreeClearPast        != DekuTreeClear        ||
          GoronRubyPast            != GoronRuby            ||
          ZoraSapphirePast         != ZoraSapphire         ||
          ForestTrialClearPast     != ForestTrialClear     ||
          FireTrialClearPast       != FireTrialClear       ||
          WaterTrialClearPast      != WaterTrialClear      ||
          ShadowTrialClearPast     != ShadowTrialClear     ||
          SpiritTrialClearPast     != SpiritTrialClear     ||
          LightTrialClearPast      != LightTrialClear      ||
          DrainWellPast            != DrainWell            ||
          DampesWindmillAccessPast != DampesWindmillAccess) {
            DekuTreeClearPast        = DekuTreeClear;
            GoronRubyPast            = GoronRuby;
            ZoraSapphirePast         = ZoraSapphire;
            ForestTrialClearPast     = ForestTrialClear;
            FireTrialClearPast       = FireTrialClear;
            WaterTrialClearPast      = WaterTrialClear;
            ShadowTrialClearPast     = ShadowTrialClear;
            SpiritTrialClearPast     = SpiritTrialClear;
            LightTrialClearPast      = LightTrialClear;
            DrainWellPast            = DrainWell;
            DampesWindmillAccessPast = DampesWindmillAccess;
            return true;
          }
     return false;
   }

   //Reset All Logic to true or false
   void LogicReset() {
     //Child item logic
     KokiriSword   = false;
     ZeldasLetter  = false;
     WeirdEgg      = false;
     HasBottle     = false;
     Bombchus      = false;
     Bombchus5     = false;
     Bombchus10    = false;
     Bombchus20    = false;
     MagicBean     = false;
     MagicBeanPack = false;
     RutosLetter   = false;
     Boomerang     = false;
     DinsFire      = false;
     FaroresWind   = false;
     NayrusLove    = false;
     LensOfTruth   = false;
     ShardOfAgony  = false;
     SkullMask     = false;
     MaskOfTruth   = false;

     //Adult logic
     Hammer        = false;
     IronBoots     = false;
     HoverBoots    = false;
     MirrorShield  = false;
     GoronTunic    = false;
     ZoraTunic     = false;
     Epona         = false;
     BigPoe        = false;
     GerudoToken   = false;
     FireArrows    = false;
     IceArrows     = false;
     LightArrows   = false;

     //Trade Quest
     PocketEgg     = false;
     PocketCucco   = false;
     Cojiro        = false;
     OddMushroom   = false;
     OddPoultice   = false;
     PoachersSaw   = false;
     BrokenSword   = false;
     Prescription  = false;
     EyeballFrog   = false;
     Eyedrops      = false;
     ClaimCheck    = false;

     //Trade Quest Events
     WakeUpAdultTalon   = false;
     CojiroAccess       = false;
     OddMushroomAccess  = false;
     OddPoulticeAccess  = false;
     PoachersSawAccess  = false;
     BrokenSwordAccess  = false;
     PrescriptionAccess = false;
     EyeballFrogAccess  = false;
     EyedropsAccess     = false;
     DisableTradeRevert = false;

     //Songs
     ZeldasLullaby    = false;
     SariasSong       = false;
     SunsSong         = false;
     SongOfStorms     = false;
     EponasSong       = false;
     SongOfTime       = false;
     MinuetOfForest   = false;
     BoleroOfFire     = false;
     SerenadeOfWater  = false;
     RequiemOfSpirit  = false;
     NocturneOfShadow = false;
     PreludeOfLight   = false;

     //Stones and Meddallions
     ForestMedallion = false;
     FireMedallion   = false;
     WaterMedallion  = false;
     SpiritMedallion = false;
     ShadowMedallion = false;
     LightMedallion  = false;
     KokiriEmerald   = false;
     GoronRuby       = false;
     ZoraSapphire    = false;

     //Dungeon Clears
     DekuTreeClear       = false;
     DodongosCavernClear = false;
     JabuJabusBellyClear = false;
     ForestTempleClear   = false;
     FireTempleClear     = false;
     WaterTempleClear    = false;
     SpiritTempleClear   = false;
     ShadowTempleClear   = false;

     //Trial Clears
     ForestTrialClear = false;
     FireTrialClear   = false;
     WaterTrialClear  = false;
     SpiritTrialClear = false;
     ShadowTrialClear = false;
     LightTrialClear  = false;

     //Progressive Items
     ProgressiveBulletBag = 0;
     ProgressiveBombBag   = 0;
     ProgressiveMagic     = 0;
     ProgressiveScale     = 0;
     ProgressiveHookshot  = 0;
     ProgressiveBow       = 0;
     ProgressiveWallet    = 0;
     ProgressiveStrength  = 0;
     ProgressiveOcarina   = 0;

     //Keys
     ForestTempleKeys          = 0;
     FireTempleKeys            = 0;
     WaterTempleKeys           = 0;
     SpiritTempleKeys          = 0;
     ShadowTempleKeys          = 0;
     GanonsCastleKeys          = 0;
     GerudoFortressKeys        = 0;
     GerudoTrainingGroundsKeys = 0;
     BottomOfTheWellKeys       = 0;

     //Boss Keys
     BossKeyForestTemple = 0;
     BossKeyFireTemple   = 0;
     BossKeyWaterTemple  = 0;
     BossKeySpiritTemple = 0;
     BossKeyShadowTemple = 0;
     BossKeyGanonsCastle = 0;

     //Gold Skulltula Count
     GoldSkulltulaTokens = 0;



     //Drops and Bottle Contents Access
     DekuNutDrop      = false;
     NutPot           = false;
     NutCrate         = false;
     DekuBabaNuts     = false;
     DekuStickDrop    = false;
     StickPot         = false;
     DekuBabaSticks   = false;
     BugsAccess       = false;
     BugShrub         = false;
     WanderingBugs    = false;
     BugRock          = false;
     BlueFireAccess   = false;
     FishAccess       = false;
     FishGroup        = false;
     LoneFish         = false;
     FairyAccess      = false;
     GossipStoneFairy = false;
     BeanPlantFairy   = false;
     ButterflyFairy   = false;
     FairyPot         = false;
     FreeFairies      = false;
     FairyPond        = false;

     BuyBombchus5     = false;
     BuyBombchus10    = false;
     BuyBombchus20    = false;

     /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
     /* These are used to simplify reading the logic, but need to be updated
     /  every time a base value is updated.                       */

     Slingshot        = false;
     Ocarina          = false;
     BombBag          = false;
     MagicMeter       = false;
     Hookshot         = false;
     Longshot         = false;
     Bow              = false;
     GoronBracelet    = false;
     SilverGauntlets  = false;
     GoldenGauntlets  = false;
     SilverScale      = false;
     GoldScale        = false;

     ScarecrowSong    = false;
     Scarecrow        = false;
     DistantScarecrow = false;

     Bombs            = false;
     DekuShield       = false;
     HylianShield     = false;
     Nuts             = false;
     Sticks           = false;
     Bugs             = false;
     BlueFire         = false;
     Fish             = false;
     Fairy            = false;
     BottleWithBigPoe = false;

     HasBombchus      = false;
     FoundBombchus    = false;
     HasExplosives    = false;
     IsChild          = false;
     IsAdult          = false;
   //IsGlitched       = false;
     CanBlastOrSmash  = false;
     CanChildAttack   = false;
     CanChildDamage   = false;
     CanCutShrubs     = false;
     CanDive          = false;
     CanLeaveForest   = false;
     CanPlantBugs     = false;
     CanRideEpona     = false;
     CanStunDeku      = false;
     CanSummonGossipFairy = false;
     CanSummonGossipFairyWithoutSuns = false;
     CanPlantBean        = false;
     CanOpenBombGrotto   = false;
     CanOpenStormGrotto  = false;
     BigPoeKill          = false;
     HookshotOrBoomerang = false;

     GuaranteeTradePath     = false;
     GuaranteeHint          = false;
     HasFireSource          = false;
     HasFireSourceWithTorch = false;

     CanFinishGerudoFortress = false;

     HasShield        = false;
     CanShield        = false;
     CanJumpslash     = false;
     CanUseProjectile = false;

     //Bridge Requirements
     HasAllStones          = false;
     HasAllMedallions      = false;
     CanBuildRainbowBridge = false;
     CanTriggerLACS        = false;

     //Other
     AtDay         = false;
     AtNight       = false;
     IsStartingAge = false;
     Age           = Settings::StartingAge.Value<u8>();

     //Events
     ShowedMidoSwordAndShield  = false;
     CarpenterRescue           = false;
     GF_GateOpen               = false;
     DampesWindmillAccess      = false;
     DrainWell                 = false;
     GoronCityChildFire        = false;
     GCWoodsWarpOpen           = false;
     StopGCRollingGoronAsAdult = false;
     ChildWaterTemple          = false;
     KakarikoVillageGateOpen   = false;
     KingZoraThawed            = false;
     ForestTempleJoAndBeth     = false;
     ForestTempleAmyAndMeg     = false;
     LinksCow                  = false;
     AtDampeTime               = false;
     DeliverLetter             = false;

     DrainWellPast            = false;
     DampesWindmillAccessPast = false;
     DekuTreeClearPast        = false;
     GoronRubyPast            = false;
     ZoraSapphirePast         = false;
     ForestTrialClearPast     = false;
     FireTrialClearPast       = false;
     WaterTrialClearPast      = false;
     SpiritTrialClearPast     = false;
     ShadowTrialClearPast     = false;
     LightTrialClearPast      = false;
     BuyDekuShieldPast        = false;
   }
}
