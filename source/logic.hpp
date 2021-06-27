#pragma once

#include <3ds.h>

namespace Logic {

  extern bool noVariable;

  //Child item logic
  extern bool KokiriSword;
  extern bool Slingshot;
  extern bool ZeldasLetter;
  extern bool WeirdEgg;
  extern bool HasBottle;
  extern bool BombBag;
  extern bool Bombchus;
  extern bool Bombchus5;
  extern bool Bombchus10;
  extern bool Bombchus20;
  extern bool MagicBean;
  extern bool MagicBeanPack;
  extern bool RutosLetter;
  extern bool Boomerang;
  extern bool DinsFire;
  extern bool FaroresWind;
  extern bool NayrusLove;
  extern bool LensOfTruth;
  extern bool ShardOfAgony;
  extern bool SkullMask;
  extern bool MaskOfTruth;

  //Adult logic
  extern bool Bow;
  extern bool Hammer;
  extern bool IronBoots;
  extern bool HoverBoots;
  extern bool MirrorShield;
  extern bool GoronTunic;
  extern bool ZoraTunic;
  extern bool Epona;
  extern bool BigPoe;
  extern bool GerudoToken;
  extern bool FireArrows;
  extern bool IceArrows;
  extern bool LightArrows;

  //Trade Quest
  extern bool PocketEgg;
  extern bool PocketCucco;
  extern bool Cojiro;
  extern bool OddMushroom;
  extern bool OddPoultice;
  extern bool PoachersSaw;
  extern bool BrokenSword;
  extern bool Prescription;
  extern bool EyeballFrog;
  extern bool Eyedrops;
  extern bool ClaimCheck;

  //Trade Quest Events
  extern bool WakeUpAdultTalon;
  extern bool CojiroAccess;
  extern bool OddMushroomAccess;
  extern bool OddPoulticeAccess;
  extern bool PoachersSawAccess;
  extern bool BrokenSwordAccess;
  extern bool PrescriptionAccess;
  extern bool EyeballFrogAccess;
  extern bool EyedropsAccess;
  extern bool DisableTradeRevert;

  //Songs
  extern bool ZeldasLullaby;
  extern bool SariasSong;
  extern bool SunsSong;
  extern bool SongOfStorms;
  extern bool EponasSong;
  extern bool SongOfTime;
  extern bool MinuetOfForest;
  extern bool BoleroOfFire;
  extern bool SerenadeOfWater;
  extern bool RequiemOfSpirit;
  extern bool NocturneOfShadow;
  extern bool PreludeOfLight;

  //Stones and Meddallions
  extern bool ForestMedallion;
  extern bool FireMedallion;
  extern bool WaterMedallion;
  extern bool SpiritMedallion;
  extern bool ShadowMedallion;
  extern bool LightMedallion;
  extern bool KokiriEmerald;
  extern bool GoronRuby;
  extern bool ZoraSapphire;

  //Dungeon Clears
  extern bool DekuTreeClear;
  extern bool DodongosCavernClear;
  extern bool JabuJabusBellyClear;
  extern bool ForestTempleClear;
  extern bool FireTempleClear;
  extern bool WaterTempleClear;
  extern bool SpiritTempleClear;
  extern bool ShadowTempleClear;

  //Trial Clears
  extern bool ForestTrialClear;
  extern bool FireTrialClear;
  extern bool WaterTrialClear;
  extern bool SpiritTrialClear;
  extern bool ShadowTrialClear;
  extern bool LightTrialClear;

  //Progression Items
  extern u8 ProgressiveBulletBag;
  extern u8 ProgressiveBombBag;
  extern u8 ProgressiveScale;
  extern u8 ProgressiveHookshot;
  extern u8 ProgressiveBow;
  extern u8 ProgressiveStrength;
  extern u8 ProgressiveWallet;
  extern u8 ProgressiveMagic;
  extern u8 ProgressiveOcarina;

  //Keys
  extern u8 ForestTempleKeys;
  extern u8 FireTempleKeys;
  extern u8 WaterTempleKeys;
  extern u8 SpiritTempleKeys;
  extern u8 ShadowTempleKeys;
  extern u8 BottomOfTheWellKeys;
  extern u8 GerudoTrainingGroundsKeys;
  extern u8 GerudoFortressKeys;
  extern u8 GanonsCastleKeys;

  //Boss Keys
  extern bool BossKeyForestTemple;
  extern bool BossKeyFireTemple;
  extern bool BossKeyWaterTemple;
  extern bool BossKeySpiritTemple;
  extern bool BossKeyShadowTemple;
  extern bool BossKeyGanonsCastle;

  //Gold Skulltula Count
  extern u8 GoldSkulltulaTokens;

  //item and bottle drops
  extern bool DekuNutDrop;
  extern bool NutPot;
  extern bool NutCrate;
  extern bool DekuBabaNuts;
  extern bool DekuStickDrop;
  extern bool StickPot;
  extern bool DekuBabaSticks;
  extern bool BugsAccess;
  extern bool BugShrub;
  extern bool WanderingBugs;
  extern bool BugRock;
  extern bool BlueFireAccess;
  extern bool FishAccess;
  extern bool FishGroup;
  extern bool LoneFish;
  extern bool FairyAccess;
  extern bool GossipStoneFairy;
  extern bool BeanPlantFairy;
  extern bool ButterflyFairy;
  extern bool FairyPot;
  extern bool FreeFairies;
  extern bool FairyPond;
  extern bool BombchuDrop;

  extern bool BuyBombchus5;
  extern bool BuyBombchus10;
  extern bool BuyBombchus20;

  /* --- HELPERS --- */
  /* These are used to simplify reading the logic, but need to be updated
  /  every time a base value is updated.                       */

  extern bool Ocarina;
  extern bool MagicMeter;
  extern bool Hookshot;
  extern bool Longshot;
  extern bool GoronBracelet;
  extern bool SilverGauntlets;
  extern bool GoldenGauntlets;
  extern bool SilverScale;
  extern bool GoldScale;
  extern bool AdultsWallet;

  extern bool ScarecrowSong;
  extern bool Scarecrow;
  extern bool DistantScarecrow;

  extern bool Bombs;
  extern bool DekuShield;
  extern bool HylianShield;
  extern bool Nuts;
  extern bool Sticks;
  extern bool Bugs;
  extern bool BlueFire;
  extern bool Fish;
  extern bool Fairy;
  extern bool BottleWithBigPoe;

  extern bool Bombs;
  extern bool HasBombchus;
  extern bool FoundBombchus;
  extern bool HasExplosives;
  extern bool IsChild;
  extern bool IsAdult;
//extern bool IsGlitched;
  extern bool CanBlastOrSmash;
  extern bool CanChildAttack;
  extern bool CanChildDamage;
  extern bool CanCutShrubs;
  extern bool CanDive;
  extern bool CanLeaveForest;
  extern bool CanPlantBugs;
  extern bool CanRideEpona;
  extern bool CanStunDeku;
  extern bool CanSummonGossipFairy;
  extern bool CanSummonGossipFairyWithoutSuns;
  extern bool CanTakeDamage;
  //extern bool CanPlantBean;
  extern bool CanOpenBombGrotto;
  extern bool CanOpenStormGrotto;
  extern bool HookshotOrBoomerang;
  extern bool CanGetNightTimeGS;
  extern bool BigPoeKill;

  extern bool GuaranteeTradePath;
  extern bool GuaranteeHint;
  extern bool HasFireSource;
  extern bool HasFireSourceWithTorch;

  //Gerudo Fortress
  extern bool CanFinishGerudoFortress;

  extern bool HasShield;
  extern bool CanShield;
  extern bool CanJumpslash;
  extern bool CanUseProjectile;

  //Bridge Requirements
  extern bool HasAllStones;
  extern bool HasAllMedallions;
  extern bool CanBuildRainbowBridge;
  extern bool CanTriggerLACS;

  //Other
  extern bool AtDay;
  extern bool AtNight;
  extern bool LinksCow;
  extern u8 Age;

  //Events
  extern bool ShowedMidoSwordAndShield;
  extern bool CarpenterRescue;
  extern bool DampesWindmillAccess;
  extern bool GF_GateOpen;
  extern bool DrainWell;
  extern bool GoronCityChildFire;
  extern bool GCWoodsWarpOpen;
  extern bool StopGCRollingGoronAsAdult;
  extern bool ChildWaterTemple;
  extern bool RaiseWaterLevel;
  extern bool KingZoraThawed;
  extern bool AtDampeTime;
  extern bool DeliverLetter;
  extern bool KakarikoVillageGateOpen;
  extern bool ForestTempleJoAndBeth;
  extern bool ForestTempleAmyAndMeg;
  extern bool TimeTravel;

  /* --- END OF HELPERS --- */

  extern u8 AddedProgressiveBulletBags;
  extern u8 AddedProgressiveBombBags;
  extern u8 AddedProgressiveMagics;
  extern u8 AddedProgressiveScales;
  extern u8 AddedProgressiveHookshots;
  extern u8 AddedProgressiveBows;
  extern u8 AddedProgressiveWallets;
  extern u8 AddedProgressiveStrengths;
  extern u8 AddedProgressiveOcarinas;
  extern u8 TokensInPool;

  //Enum values for CanUse() and related functions
  enum class CanUseItem {
    Dins_Fire,
    Farores_Wind,
    Nayrus_Love,
    Lens_of_Truth,
    Bow,
    Hammer,
    Iron_Boots,
    Hover_Boots,
    Hookshot,
    Longshot,
    Silver_Gauntlets,
    Golden_Gauntlets,
    Goron_Tunic,
    Zora_Tunic,
    Scarecrow,
    Distant_Scarecrow,
    Slingshot,
    Boomerang,
    Kokiri_Sword,
    Sticks,
    Deku_Shield,
    Fire_Arrows,
    Ice_Arrows,
    Light_Arrows,
  };

  enum class HasProjectileAge {
    Adult,
    Child,
    Both,
    Either,
  };

  void UpdateHelpers();
  bool CanPlay(bool song);
  bool CanUse(CanUseItem itemName);
  bool HasProjectile(HasProjectileAge age);
  bool SmallKeys(u8 dungeonKeyCount, u8 requiredAmount);
  bool EventsUpdated();
  void LogicReset();
}
