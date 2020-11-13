#include "logic.hpp"
#include <string>
#include <cstdio>
#include <algorithm>
#include <3ds.h>

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
  bool KokirisEmerald  = false;
  bool GoronsRuby      = false;
  bool ZorasSapphire   = false;

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


  //Shops
  bool BuyDekuShield   = false;
  bool BuyHylianShield = false;
  bool BuyDekuNut5     = false;
  bool BuyDekuNut10    = false;
  bool BuyDekuStick1   = false;
  bool BuyBottleBug    = false;
  bool BuyBlueFire     = false;
  bool BuyBottledFish  = false;
  bool BuyFairysSpirit = false;
  bool BuyBombchus5    = false;
  bool BuyBombchus10   = false;
  bool BuyBombchus20   = false;

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

  bool Bombs        = false;
  bool DekuShield   = false;
  bool HylianShield = false;
  bool Nuts         = false;
  bool Sticks       = false;
  bool Bugs         = false;
  bool BlueFire     = false;
  bool Fish         = false;
  bool Fairy        = false;
  bool HasBigPoe    = false;

  bool HasBombchus     = false;
  bool FoundBombchus   = false;
  bool HasExplosives   = false;
  bool IsChild         = false;
  bool IsAdult         = false;
//bool IsGlitched      = false;
  bool CanBlastOrSmash = false;
  bool CanChildAttack  = false;
  bool CanChildDamage  = false;
  bool CanCutShrubs    = false;
  bool CanDive         = false;
  bool CanLeaveForest  = false;
  bool CanPlantBugs    = false;
  bool CanRideEpona    = false;
  bool CanStunDeku     = false;
  bool CanSummonGossipFairy = false;
  bool CanSummonGossipFairyWithoutSuns = false;
  bool CanPlantBean       = false;
  bool CanOpenBombGrotto  = false;
  bool CanOpenStormGrotto = false;

  bool GuaranteeTradePath     = false;
  bool GuaranteeHint          = false;
  bool HasFireSource          = false;
  bool HasFireSourceWithTorch = false;

  //Gerudo Fortress
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

  //Other (idk where these go yet)
  bool AtDay         = false;
  bool AtNight       = false;
  bool HasNightStart = false;
  bool LinksCow      = false;
  bool AtDampeTime   = false;
  bool DeliverLetter = false;

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

  /* --- END OF HELPERS AND LOCATION ACCESS --- */

  //Logic Settings
  bool LogicMidoBackflip        = false;
  bool LogicLostWoodsBridge     = false;
  bool LogicGrottosWithoutAgony = false;
  bool LogicBiggoronBolero      = false;
  bool LogicGerudoKitchen       = false;
  bool LogicWaterHookshotEntry  = false;
  bool LogicLensWasteland       = false;
  bool LogicReverseWasteland    = false;
  bool LogicVisibleCollision    = false;
  bool LogicManOnRoof           = false;
  bool LogicKakarikoTowerGS     = false;
  bool LogicDMTBombable              = false;
  bool LogicLinkGoronDins            = false;
  bool LogicGoronCityLeftMost        = false;
  bool LogicGoronCityPot             = false;
  bool LogicGoronCityPotWithStrength = false;
  bool LogicChildRollingWithStrength = false;
  bool LogicCraterUpperToLower       = false;
  bool LogicCraterBeanPoHWithHovers  = false;
  bool LogicZoraWithHovers           = false;
  bool LogicZoraWithCucco            = false;
  bool LogicFewerTunicRequirements   = false;
  bool LogicDekuB1WebsWithBow        = false;
  bool LogicDekuB1Skip               = false;
  bool LogicDCStaircase              = false;
  bool LogicDCJump                   = false;
  bool LogicDCSlingshotSkip          = false;
  bool LogicJabuBossGSAdult          = false;
  bool LogicForestOutsideBackdoor    = false;
  bool LogicForestScarecrow          = false;
  bool LogicForestVines              = false;
  bool LogicLabDiving                = false;
  bool LogicZoraRiverLower           = false;
  bool LogicZoraRiverUpper           = false;
  bool LogicGraveyardPoH             = false;
  bool LogicChildDampeRacePoH        = false;
  bool LogicFireBossDoorJump         = false;
  bool LogicFireStrength             = false;
  bool LogicFireScarecrow            = false;
  bool LogicFireFlameMaze            = false;
  bool LogicWaterTempleTorchLongshot = false;
  bool LogicWaterCentralBow          = false;
  bool LogicWaterCrackedWallNothing  = false;
  bool LogicWaterCrackedWallHovers   = false;
  bool LogicWaterBossKeyRegion       = false;
  bool LogicWaterDragonBombchu       = false;
  bool LogicWaterBKJumpDive          = false;
  bool LogicWaterNorthBasementLedgeJump = false;
  bool LogicWaterBKChest             = false;
  bool LogicWaterDragonJumpDive      = false;
  bool LogicSpiritLowerAdultSwitch   = false;
  bool LogicSpiritChildBombchu       = false;
  bool LogicSpiritWall               = false;
  bool LogicSpiritLobbyGS            = false;
  bool LogicSpiritMapChest           = false;
  bool LogicSpiritSunChest           = false;
  bool LogicShadowFireArrowEntry     = false;
  bool LogicShadowUmbrella           = false;
  bool LogicShadowFreestandingKey    = false;
  bool LogicShadowStatue             = false;
  bool LogicBotwCageGS               = false;
  bool LogicChildDeadhand            = false;
  bool LogicGtgWithoutHookshot       = false;
  bool LogicGtgFakeWall              = false;
  bool LogicLensSpirit               = false;
  bool LogicLensShadow               = false;
  bool LogicLensShadowBack           = false;
  bool LogicLensBotw                 = false;
  bool LogicLensGtg                  = false;
  bool LogicLensCastle               = false;
  bool LogicSpiritTrialHookshot      = false;
  bool KakarikoVillageGateOpen       = false;
  bool KingZoraThawed                = false;
  bool ForestTempleJoAndBeth         = false;
  bool ForestTempleAmyAndMeg         = false;
  bool BombchusInLogic       = false;
  bool BombchuDrop           = false;
  bool OpenDoorOfTime        = false;
  bool SkippedTrials         = false;
  std::string OpenForest       = "";
  std::string OpenKakariko     = "";
  std::string Bridge           = "";
  std::string LACSCondition    = "";
  std::string GerudoFortress   = "";
  std::string DamageMultiplier = "";
  std::string ZorasFountain    = "";
  std::string StartingAge      = "";
  std::string Age              = "";
  std::string TimeOfDay        = "";
  std::string Keysanity        = "";
  std::string BossKeysanity    = "";
  std::string MapsAndCompasses = "";
  bool IsStartingAge = false;
  bool CanBeAdult    = false;
  bool CanBeChild    = false;
  bool ShuffleDungeonEntrances       = false;
  bool ShuffleOverworldEntrances     = false;
  bool ShuffleSpecialIndoorEntrances = false;
  bool ShuffleWeirdEgg               = false;
  bool ShuffleGerudoToken            = false;
  bool ShuffleZeldasLetter           = false;
  bool ShuffleKokiriSword            = false;
  bool ShuffleSongs                  = false;
  bool Skullsanity                   = false;
  bool Shopsanity                    = false;

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
  bool DrainWellPast            = false;
  bool DampesWindmillAccessPast = false;
  bool DekuTreeClearPast        = false;
  bool GoronsRubyPast           = false;
  bool ZorasSapphirePast        = false;
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

  static bool IsMagicItem(std::string item) {
    return item == "Dins Fire"    ||
           item == "Farores Wind" ||
           item == "Nayrus Love"  ||
           item == "Lens of Truth";
  }

  static bool IsAdultItem(std::string item) {
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

  static bool IsChildItem(std::string item) {
    return item == "Slingshot"    ||
           item == "Boomerang"    ||
           item == "Kokiri Sword" ||
           item == "Sticks"       ||
           item == "Deku Shield";
  }

  static bool IsMagicArrow(std::string item) {
    return item == "Fire Arrows" ||
           item == "Ice Arrows"  ||
           item == "Light Arrows";
  }

  bool HasItem(std::string itemName) {
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
           (itemName == "KokiriSword"      && KokiriSword)     ||
           (itemName == "Sticks"           && Sticks)          ||
           (itemName == "DekuShield"       && DekuShield)      ||
           (itemName == "FireArrows"       && FireArrows)      ||
           (itemName == "Ice Arrows"       && IceArrows)       ||
           (itemName == "Light Arrows"     && LightArrows);

  }

  //Can the passed in item be used?
  bool CanUse(std::string itemName) {
    return (IsMagicItem(itemName)  && HasItem(itemName) && MagicMeter) ||
           (IsAdultItem(itemName)  && HasItem(itemName) && IsAdult)    ||
           (IsMagicArrow(itemName) && HasItem(itemName) && MagicMeter  && IsAdult && Bow) ||
           (IsChildItem(itemName)  && HasItem(itemName) && IsChild);
  }

  bool HasProjectile(std::string age) {
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
    DekuNutDrop   = NutPot   || DekuBabaNuts;
    BugsAccess    = BugShrub || WanderingBugs    || BugRock;
    FishAccess    = LoneFish || FishGroup;
    FairyAccess   = FairyPot || GossipStoneFairy || BeanPlantFairy || ButterflyFairy || FreeFairies || FairyPond;


    //refills
    Bombs        = BombBag;
    DekuShield   = BuyDekuShield   || DekuShield;   //TODO: Change back once logic testing is done
    HylianShield = BuyHylianShield || HylianShield;
    Nuts         = BuyDekuNut5     || BuyDekuNut10 || DekuNutDrop;
    Sticks       = BuyDekuStick1   || DekuStickDrop;
    Bugs         = HasBottle && (BugsAccess      || BuyBottleBug);
    BlueFire     = HasBottle && (BlueFireAccess  || BuyBlueFire);
    Fish         = HasBottle && (FishAccess      || BuyBottledFish);
    Fairy        = HasBottle && (FairyAccess     || BuyFairysSpirit);

    HasBombchus   = (BuyBombchus5 || BuyBombchus10 || BuyBombchus20 || BombchuDrop) && (BombchusInLogic || BombBag);
    FoundBombchus = (BombchusInLogic && (Bombchus || Bombchus5 || Bombchus10 || Bombchus20)) || (!BombchusInLogic && BombBag);
    HasExplosives =  Bombs || (BombchusInLogic && HasBombchus);

    IsChild = Age == "Child";
    IsAdult = Age == "Adult";
    IsStartingAge = Age == StartingAge; //what's this for?

  //IsGlitched = false;

    CanBlastOrSmash = HasExplosives || CanUse("Hammer");
    CanChildAttack  = IsChild && (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire"));
    CanChildDamage  = IsChild && (Slingshot ||              Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire"));
    CanStunDeku     = IsAdult || (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse("Dins Fire") || Nuts || DekuShield);
    CanCutShrubs    = IsAdult || Sticks || KokiriSword || Boomerang || HasExplosives;
    CanDive         = ProgressiveScale >= 1;
    CanLeaveForest  = OpenForest != "Closed" || IsAdult || DekuTreeClear;
    CanPlantBugs    = IsChild && Bugs;
    CanRideEpona    = IsAdult && Epona && CanPlay(EponasSong);
    CanSummonGossipFairy            = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime || SunsSong);
    CanSummonGossipFairyWithoutSuns = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime);
    CanPlantBean       = IsChild && (MagicBean || MagicBeanPack);
    CanOpenBombGrotto  = CanBlastOrSmash       && (ShardOfAgony || LogicGrottosWithoutAgony);
    CanOpenStormGrotto = CanPlay(SongOfStorms) && (ShardOfAgony || LogicGrottosWithoutAgony);

  //GuaranteeTradePath     = ShuffleInteriorEntrances || ShuffleOverworldEntrances || LogicBiggoronBolero || CanBlastOrSmash || 'Stop GC Rolling Goron As Adult';
  //GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints != "Agony");
    HasFireSource          = CanUse("Dins Fire") || CanUse("Fire Arrows");
    HasFireSourceWithTorch = HasFireSource || (IsChild && Sticks);

    //Gerudo Fortress
    CanFinishGerudoFortress = (GerudoFortress == "Normal" && GerudoFortressKeys >= 4 && (IsAdult || KokiriSword) && ((IsAdult && (Bow || Hookshot || HoverBoots)) || GerudoToken || LogicGerudoKitchen)) ||
                              (GerudoFortress == "Fast"   && GerudoFortressKeys >= 1 && (IsAdult || KokiriSword)) ||
                              (GerudoFortress != "Normal"  && GerudoFortress != "Fast");

    HasShield        = (IsAdult && HylianShield) ||                   (IsChild && DekuShield); //Mirror shield can't reflect attacks
    CanShield        = (IsAdult && (HylianShield || MirrorShield)) || (IsChild && DekuShield);
    CanJumpslash     = IsAdult || Sticks || KokiriSword;
    CanUseProjectile = HasExplosives || (IsAdult && (Bow || Hookshot)) || (IsChild && (Slingshot || Boomerang));

    //Bridge Requirements
    HasAllStones          = KokirisEmerald  && GoronsRuby    && ZorasSapphire;
    HasAllMedallions      = ForestMedallion && FireMedallion && WaterMedallion && ShadowMedallion && SpiritMedallion && LightMedallion;
    CanBuildRainbowBridge = Bridge == "Open" ||
                           (Bridge == "Vanilla"    && ShadowMedallion && SpiritMedallion && LightArrows) ||
                           (Bridge == "Stones"     && HasAllStones) ||
                           (Bridge == "Medallions" && HasAllMedallions) ||
                           (Bridge == "Dungeons"   && HasAllStones && HasAllMedallions);
                         //(Bridge == "Tokens"     && GoldSkulltulaTokens > Count);

    CanTriggerLACS = (LACSCondition == "Vanilla"    && ShadowMedallion && SpiritMedallion) ||
                     (LACSCondition == "Stones"     && HasAllStones)                       ||
                     (LACSCondition == "Medallions" && HasAllMedallions)                   ||
                     (LACSCondition == "Dungeons"   && HasAllStones && HasAllMedallions);

  }

  //Function to set flags depending on settings
  void UpdateSettings() {
    CanBeChild = true;
    LogicGrottosWithoutAgony = true;
    LogicBiggoronBolero = true;
    LogicGerudoKitchen = false;
    LogicManOnRoof = true;
    ShuffleWeirdEgg = false;
    ShuffleZeldasLetter = false;
    ShuffleKokiriSword  = false;
    BombchusInLogic = true;
    LogicDekuB1Skip = true;
    OpenDoorOfTime = true;
    LightMedallion = true;

    OpenForest = "Closed";
    Bridge = "Medallions";
    LACSCondition = "Medallions";
    DamageMultiplier = "1x";
    StartingAge = "Child";
    Keysanity = "All Locations";
    BossKeysanity = "Vanilla";
    MapsAndCompasses = "Vanilla";
    GerudoFortress = "Normal";

    UpdateHelpers();
  }

  bool SmallKeys(u8 dungeonKeyCount, u8 requiredAmount) {
    return (dungeonKeyCount >= requiredAmount) || Keysanity == "Vanilla";
  }

  bool EventsUpdated() {

      if (DekuTreeClearPast        != DekuTreeClear        ||
          GoronsRubyPast           != GoronsRuby           ||
          ZorasSapphirePast        != ZorasSapphire        ||
          ForestTrialClearPast     != ForestTrialClear     ||
          FireTrialClearPast       != FireTrialClear       ||
          WaterTrialClearPast      != WaterTrialClear      ||
          ShadowTrialClearPast     != ShadowTrialClear     ||
          SpiritTrialClearPast     != SpiritTrialClear     ||
          LightTrialClearPast      != LightTrialClear      ||
          DrainWellPast            != DrainWell            ||
          DampesWindmillAccessPast != DampesWindmillAccess ||
          BuyDekuShieldPast        != BuyDekuShield          ) {
            DekuTreeClearPast        = DekuTreeClear;
            GoronsRubyPast           = GoronsRuby;
            ZorasSapphirePast        = ZorasSapphire;
            ForestTrialClearPast     = ForestTrialClear;
            FireTrialClearPast       = FireTrialClear;
            WaterTrialClearPast      = WaterTrialClear;
            ShadowTrialClearPast     = ShadowTrialClear;
            SpiritTrialClearPast     = SpiritTrialClear;
            LightTrialClearPast      = LightTrialClear;
            DrainWellPast            = DrainWell;
            DampesWindmillAccessPast = DampesWindmillAccess;
            BuyDekuShieldPast        = BuyDekuShield;
            return true;
          }
     return false;
   }

  void GenericGrottoChecks() {
    GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
    ButterflyFairy   = ButterflyFairy   || (CanUse("Sticks"));
    BugShrub         = CanCutShrubs;
    LoneFish         = true;
  }
}
