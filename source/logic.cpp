#include "logic.hpp"

#include <3ds.h>
#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "settings.hpp"
#include "dungeon.hpp"
#include "descriptions.hpp"

using namespace Settings;

namespace Logic {

bool noVariable = false;

// Child item logic
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

// Adult logic
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
bool MasterSword   = false;
bool BiggoronSword = false;

// Trade Quest
bool PocketEgg    = false;
bool Cojiro       = false;
bool OddMushroom  = false;
bool OddPoultice  = false;
bool PoachersSaw  = false;
bool BrokenSword  = false;
bool Prescription = false;
bool EyeballFrog  = false;
bool Eyedrops     = false;
bool ClaimCheck   = false;

// Trade Quest Events
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

// Songs
bool ZeldasLullaby_item    = false;
bool SariasSong_item       = false;
bool SunsSong_item         = false;
bool SongOfStorms_item     = false;
bool EponasSong_item       = false;
bool SongOfTime_item       = false;
bool MinuetOfForest_item   = false;
bool BoleroOfFire_item     = false;
bool SerenadeOfWater_item  = false;
bool RequiemOfSpirit_item  = false;
bool NocturneOfShadow_item = false;
bool PreludeOfLight_item   = false;
// Ocarina notes buttons
bool OcarinaButtonL    = false;
bool OcarinaButtonR    = false;
bool OcarinaButtonX    = false;
bool OcarinaButtonY    = false;
bool OcarinaButtonA    = false;
u8 OcarinaButtonsCount = 0;
// Songs + their ocarina notes
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

// Stones and Meddallions
bool ForestMedallion = false;
bool FireMedallion   = false;
bool WaterMedallion  = false;
bool SpiritMedallion = false;
bool ShadowMedallion = false;
bool LightMedallion  = false;
bool KokiriEmerald   = false;
bool GoronRuby       = false;
bool ZoraSapphire    = false;

// Dungeon Clears
bool DekuTreeClear       = false;
bool DodongosCavernClear = false;
bool JabuJabusBellyClear = false;
bool ForestTempleClear   = false;
bool FireTempleClear     = false;
bool WaterTempleClear    = false;
bool SpiritTempleClear   = false;
bool ShadowTempleClear   = false;

// Trial Clears
bool ForestTrialClear = false;
bool FireTrialClear   = false;
bool WaterTrialClear  = false;
bool SpiritTrialClear = false;
bool ShadowTrialClear = false;
bool LightTrialClear  = false;

// Progressive Items
u8 ProgressiveBulletBag  = 0;
u8 ProgressiveBombBag    = 0;
u8 ProgressiveMagic      = 0;
u8 ProgressiveScale      = 0;
u8 ProgressiveHookshot   = 0;
u8 ProgressiveBow        = 0;
u8 ProgressiveWallet     = 0;
u8 ProgressiveStrength   = 0;
u8 ProgressiveOcarina    = 0;
u8 ProgressiveGiantKnife = 0;

// Logical keysanity
bool IsKeysanity = false;

// Keys
u8 ForestTempleKeys          = 0;
u8 FireTempleKeys            = 0;
u8 WaterTempleKeys           = 0;
u8 SpiritTempleKeys          = 0;
u8 ShadowTempleKeys          = 0;
u8 GanonsCastleKeys          = 0;
u8 GerudoFortressKeys        = 0;
u8 GerudoTrainingGroundsKeys = 0;
u8 BottomOfTheWellKeys       = 0;
u8 TreasureGameKeys          = 0;

// Boss Keys
bool BossKeyForestTemple = false;
bool BossKeyFireTemple   = false;
bool BossKeyWaterTemple  = false;
bool BossKeySpiritTemple = false;
bool BossKeyShadowTemple = false;
bool BossKeyGanonsCastle = false;

// Gold Skulltula Count
u8 GoldSkulltulaTokens = 0;

// Bottle Count
u8 Bottles     = 0;
u8 NumBottles  = 0;
bool NoBottles = false;

// Drops and Bottle Contents Access
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
bool BombchuDrop      = false;
bool AmmoCanDrop      = false;

bool BuyBombchus5  = false;
bool BuyBombchus10 = false;
bool BuyBombchus20 = false;
bool BuySeed       = false;
bool BuyArrow      = false;
bool BuyBomb       = false;
bool BuyGPotion    = false;
bool BuyBPotion    = false;
bool MagicRefill   = false;

u8 PieceOfHeart    = 0;
u8 HeartContainer  = 0;
bool DoubleDefense = false;
u8 TriforcePieces  = 0;

bool SoulPoe               = false;
bool SoulOctorok           = false;
bool SoulKeese             = false;
bool SoulTektite           = false;
bool SoulLeever            = false;
bool SoulPeahat            = false;
bool SoulLizalfosDinolfos  = false;
bool SoulShabom            = false;
bool SoulBiriBari          = false;
bool SoulTailpasaran       = false;
bool SoulSkulltula         = false;
bool SoulTorchSlug         = false;
bool SoulStinger           = false;
bool SoulMoblin            = false;
bool SoulArmos             = false;
bool SoulDekuBaba          = false;
bool SoulBubble            = false;
bool SoulFlyingTrap        = false;
bool SoulBeamos            = false;
bool SoulWallmaster        = false;
bool SoulRedeadGibdo       = false;
bool SoulShellBlade        = false;
bool SoulLikeLike          = false;
bool SoulParasiticTentacle = false;
bool SoulAnubis            = false;
bool SoulSpike             = false;
bool SoulSkullKid          = false;
bool SoulFreezard          = false;
bool SoulDekuScrub         = false;
bool SoulWolfos            = false;
bool SoulStalchild         = false;
bool SoulGuay              = false;
bool SoulDoorMimic         = false;
bool SoulStalfos           = false;
bool SoulDarkLink          = false;
bool SoulFlareDancer       = false;
bool SoulDeadHand          = false;
bool SoulGerudo            = false;
bool SoulGohma             = false;
bool SoulDodongo           = false;
bool SoulBarinade          = false;
bool SoulPhantomGanon      = false;
bool SoulVolvagia          = false;
bool SoulMorpha            = false;
bool SoulBongoBongo        = false;
bool SoulTwinrova          = false;
bool SoulGanon             = false;

/* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
/* These are used to simplify reading the logic, but need to be updated
/  every time a base value is updated.                       */

bool Slingshot       = false;
bool Ocarina         = false;
bool OcarinaOfTime   = false;
bool BombBag         = false;
bool MagicMeter      = false;
bool Hookshot        = false;
bool Longshot        = false;
bool Bow             = false;
bool GoronBracelet   = false;
bool SilverGauntlets = false;
bool GoldenGauntlets = false;
bool SilverScale     = false;
bool GoldScale       = false;
bool AdultsWallet    = false;

bool ChildScarecrow   = false;
bool AdultScarecrow   = false;
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

bool FoundBombchus                   = false;
bool CanPlayBowling                  = false;
bool HasBombchus                     = false;
bool HasExplosives                   = false;
bool HasBoots                        = false;
bool IsChild                         = false;
bool IsAdult                         = false;
bool IsGlitched                      = false;
bool CanBlastOrSmash                 = false;
bool CanChildAttack                  = false;
bool CanChildDamage                  = false;
bool CanAdultAttack                  = false;
bool CanAdultDamage                  = false;
bool CanCutShrubs                    = false;
bool CanDive                         = false;
bool CanLeaveForest                  = false;
bool CanPlantBugs                    = false;
bool CanRideEpona                    = false;
bool CanStunDeku                     = false;
bool CanSummonGossipFairy            = false;
bool CanSummonGossipFairyWithoutSuns = false;
bool NeedNayrusLove                  = false;
bool CanSurviveDamage                = false;
bool CanTakeDamage                   = false;
bool CanTakeDamageTwice              = false;
// bool CanPlantBean        = false;
bool CanOpenBombGrotto   = false;
bool CanOpenStormGrotto  = false;
bool BigPoeKill          = false;
bool HookshotOrBoomerang = false;
bool CanGetNightTimeGS   = false;

u8 BaseHearts      = 0;
u8 Hearts          = 0;
u8 Multiplier      = 0;
u8 EffectiveHealth = 0;
u8 FireTimer       = 0;
u8 WaterTimer      = 0;

bool GuaranteeTradePath     = false;
bool GuaranteeHint          = false;
bool HasFireSource          = false;
bool HasFireSourceWithTorch = false;

bool CanFinishGerudoFortress = false;

bool HasShield        = false;
bool CanShield        = false;
bool CanJumpslash     = false;
bool CanUseProjectile = false;
bool CanUseMagicArrow = false;

// Bridge and LACS Requirements
u8 MedallionCount          = 0;
u8 StoneCount              = 0;
u8 DungeonCount            = 0;
bool HasAllStones          = false;
bool HasAllMedallions      = false;
bool CanBuildRainbowBridge = false;
bool BuiltRainbowBridge    = false;
bool CanTriggerLACS        = false;

// Other
bool AtDay   = false;
bool AtNight = false;
u8 Age       = 0;

// Events
bool ShowedMidoSwordAndShield  = false;
bool CarpenterRescue           = false;
bool GF_GateOpen               = false;
bool GtG_GateOpen              = false;
bool DampesWindmillAccess      = false;
bool DrainWell                 = false;
bool GoronCityChildFire        = false;
bool GCWoodsWarpOpen           = false;
bool GCDaruniasDoorOpenChild   = false;
bool StopGCRollingGoronAsAdult = false;
bool WaterTempleLow            = false;
bool WaterTempleMiddle         = false;
bool WaterTempleHigh           = false;
bool KakarikoVillageGateOpen   = false;
bool KingZoraThawed            = false;
bool ForestTempleJoelle        = false;
bool ForestTempleBeth          = false;
bool ForestTempleJoAndBeth     = false;
bool ForestTempleAmy           = false;
bool ForestTempleMeg           = false;
bool ForestTempleAmyAndMeg     = false;
bool FireLoopSwitch            = false;
bool LinksCow                  = false;
bool AtDampeTime               = false;
bool DeliverLetter             = false;
bool TimeTravel                = false;

/* --- END OF HELPERS AND LOCATION ACCESS --- */

// Placement Tracking
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

// Event checking past
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
bool TimeTravelPast           = false;

bool CanPlay(bool song) {
    return Ocarina && song;
}

static bool IsMagicItem(ItemKey item) {
    return item == DINS_FIRE || item == FARORES_WIND || item == NAYRUS_LOVE || item == LENS_OF_TRUTH;
}

static bool IsMagicArrow(ItemKey item) {
    return item == FIRE_ARROWS || item == ICE_ARROWS || item == LIGHT_ARROWS;
}

bool HasItem(ItemKey itemName) {
    return (itemName == DINS_FIRE && DinsFire) || (itemName == FARORES_WIND && FaroresWind) ||
           (itemName == NAYRUS_LOVE && NayrusLove) || (itemName == LENS_OF_TRUTH && LensOfTruth) ||
           (itemName == BOW && Bow) || (itemName == MEGATON_HAMMER && Hammer) ||
           (itemName == IRON_BOOTS && IronBoots) || (itemName == HOVER_BOOTS && HoverBoots) ||
           (itemName == HOOKSHOT && Hookshot) || (itemName == LONGSHOT && Longshot) ||
           (itemName == SILVER_GAUNTLETS && SilverGauntlets) || (itemName == GOLDEN_GAUNTLETS && GoldenGauntlets) ||
           (itemName == GORON_TUNIC && GoronTunic) || (itemName == ZORA_TUNIC && ZoraTunic) ||
           (itemName == SCARECROW && Scarecrow) || (itemName == DISTANT_SCARECROW && DistantScarecrow) ||
           (itemName == HYLIAN_SHIELD && HylianShield) || (itemName == MIRROR_SHIELD && MirrorShield) ||
           (itemName == MASTER_SWORD && MasterSword) || (itemName == BIGGORON_SWORD && BiggoronSword) ||
           (itemName == SLINGSHOT && Slingshot) || (itemName == BOOMERANG && Boomerang) ||
           (itemName == KOKIRI_SWORD && KokiriSword) || (itemName == STICKS && Sticks) ||
           (itemName == DEKU_SHIELD && DekuShield) || (itemName == FIRE_ARROWS && FireArrows) ||
           (itemName == ICE_ARROWS && IceArrows) || (itemName == LIGHT_ARROWS && LightArrows);
}

// Can the passed in item be used?
bool CanUse(ItemKey itemName) {
    if (!HasItem(itemName))
        return false;

    switch (itemName) {
        // Adult items
        case BOW:
            return IsAdult || (AgeItemsInLogic && BowAsChild);
        case MEGATON_HAMMER:
            return IsAdult || (AgeItemsInLogic && HammerAsChild);
        case IRON_BOOTS:
            return IsAdult || (AgeItemsInLogic && IronBootsAsChild);
        case HOVER_BOOTS:
            return IsAdult || (AgeItemsInLogic && HoverBootsAsChild);
        case HOOKSHOT:
            return IsAdult || (AgeItemsInLogic && HookshotAsChild);
        case LONGSHOT:
            return IsAdult || (AgeItemsInLogic && HookshotAsChild);
        case SILVER_GAUNTLETS:
            return IsAdult;
        case GOLDEN_GAUNTLETS:
            return IsAdult;
        case GORON_TUNIC:
            return IsAdult || (AgeItemsInLogic && GoronTunicAsChild);
        case ZORA_TUNIC:
            return IsAdult || (AgeItemsInLogic && ZoraTunicAsChild);
        case SCARECROW:
            return IsAdult || (AgeItemsInLogic && HookshotAsChild);
        case DISTANT_SCARECROW:
            return IsAdult || (AgeItemsInLogic && HookshotAsChild);
        case HYLIAN_SHIELD:
            return IsAdult;
        case MIRROR_SHIELD:
            return IsAdult || (AgeItemsInLogic && MirrorShieldAsChild);
        case MASTER_SWORD:
            return IsAdult || (AgeItemsInLogic && MasterSwordAsChild);
        case BIGGORON_SWORD:
            return IsAdult || (AgeItemsInLogic && BiggoronSwordAsChild);

        // Child items
        case SLINGSHOT:
            return IsChild || (AgeItemsInLogic && SlingshotAsAdult);
        case BOOMERANG:
            return IsChild || (AgeItemsInLogic && BoomerangAsAdult);
        case KOKIRI_SWORD:
            return IsChild || (AgeItemsInLogic && KokiriSwordAsAdult);
        case STICKS:
            return IsChild || (AgeItemsInLogic && StickAsAdult);
        case DEKU_SHIELD:
            return IsChild || (AgeItemsInLogic && DekuShieldAsAdult);

        // Magic items
        default:
            return MagicMeter && (IsMagicItem(itemName) || (IsMagicArrow(itemName) && CanUse(BOW)));
    }
}

bool HasProjectile(HasProjectileAge age) {
    return HasExplosives || (age == HasProjectileAge::Child && (Slingshot || Boomerang)) ||
           (age == HasProjectileAge::Adult && (Hookshot || Bow)) ||
           (age == HasProjectileAge::Both && (Slingshot || Boomerang) && (Hookshot || Bow)) ||
           (age == HasProjectileAge::Either && (Slingshot || Boomerang || Hookshot || Bow));
}

bool CanDoGlitch(GlitchType glitch, GlitchDifficulty difficulty) {
    switch (glitch) {
        // Restricted Items
        case GlitchType::RestrictedItems:
            if (!GlitchEnabled(GlitchRestrictedItems, difficulty)) {
                return false;
            }
            return true;

        // Super Stab
        case GlitchType::SuperStab:
            if (!GlitchEnabled(GlitchSuperStab, difficulty)) {
                return false;
            }
            return CanShield && CanUse(STICKS);

        // Infinite Sword Glitch
        case GlitchType::ISG:
            if (!GlitchEnabled(GlitchISG, difficulty)) {
                return false;
            }
            return CanShield && (CanJumpslash || CanUse(MEGATON_HAMMER));

        // Bomb Hover
        case GlitchType::BombHover:
            if (!GlitchEnabled(GlitchHover, difficulty)) {
                return false;
            }
            return CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                   (HasBombchus || (Bombs && GlitchEnabled(GlitchHover, GlitchDifficulty::ADVANCED)));

        // Bomb Ocarina Items
        case GlitchType::BombOI:
            if (!GlitchEnabled(GlitchBombOI, difficulty)) {
                return false;
            }
            return Bombs && CanSurviveDamage;
        case GlitchType::OutdoorBombOI:
            return (
                (CanUse(FARORES_WIND) &&
                 (DinsFire || NayrusLove || LensOfTruth || HasBottle || HasBombchus || Nuts || StartingConsumables ||
                  CanUse(STICKS) || CanUse(SLINGSHOT) || (IsChild && (MagicBean || MagicBeanPack || WeirdEgg)) ||
                  CanUse(BOOMERANG) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || CanUse(IRON_BOOTS) ||
                  CanUse(MEGATON_HAMMER) || (IsAdult && SkullMask && MasksAsAdult)) &&
                 CanDoGlitch(GlitchType::BombOI,
                             (static_cast<u8>(difficulty) >= 3) ? difficulty : GlitchDifficulty::ADVANCED) &&
                 CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE)) ||
                (((IsAdult && ClaimCheck) || Bugs || Fish || Fairy ||
                  (!NeedNayrusLove && (CanUse(NAYRUS_LOVE) || CanUse(DINS_FIRE))) ||
                  (CanUse(FARORES_WIND) && FaroresWindAnywhere)) &&
                 CanDoGlitch(GlitchType::BombOI, difficulty)));
        case GlitchType::WindmillBombOI:
            return (
                ((CanUse(FARORES_WIND) || (!NeedNayrusLove && (NayrusLove || DinsFire))) &&
                 (LensOfTruth || HasBottle || HasBombchus || Nuts || StartingConsumables || CanUse(STICKS) ||
                  CanUse(SLINGSHOT) || (IsChild && (MagicBean || MagicBeanPack || WeirdEgg)) || CanUse(BOOMERANG) ||
                  CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || CanUse(IRON_BOOTS) ||
                  CanUse(MEGATON_HAMMER) || (IsAdult && SkullMask && MasksAsAdult)) &&
                 CanDoGlitch(GlitchType::BombOI,
                             (static_cast<u8>(difficulty) >= 3) ? difficulty : GlitchDifficulty::ADVANCED) &&
                 CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE)) ||
                (((IsAdult && ClaimCheck) || Bugs || Fish || Fairy || (CanUse(FARORES_WIND) && FaroresWindAnywhere)) &&
                 CanDoGlitch(GlitchType::BombOI, difficulty)));
        case GlitchType::IndoorBombOI: // TODO: Update for item usability settings
            return (((IsAdult && ClaimCheck) &&
                     (HasBottle || HasBoots || (CanUse(FARORES_WIND) && FaroresWindAnywhere))) ||
                    ((Bugs || Fish || Fairy) &&
                     (NumBottles >= 2 || (IsAdult && (ClaimCheck || HasBoots)) || (IsChild && WeirdEgg) ||
                      (CanUse(FARORES_WIND) && FaroresWindAnywhere))) ||
                    ((CanUse(FARORES_WIND) && FaroresWindAnywhere) &&
                     (HasBottle || (IsAdult && (ClaimCheck || HasBoots)) || (IsChild && WeirdEgg))) ||
                    (((!NeedNayrusLove && (CanUse(NAYRUS_LOVE) || CanUse(DINS_FIRE))) || CanUse(FARORES_WIND)) &&
                     (NumBottles + ((IsChild)
                                        ? ((WeirdEgg) ? 1 : 0)
                                        : (((IronBoots) ? 1 : 0) + ((HoverBoots) ? 1 : 0) + ((ClaimCheck) ? 1 : 0))) >=
                      2))) &&
                   CanDoGlitch(GlitchType::BombOI, difficulty) &&
                   CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE);
        case GlitchType::DungeonBombOI:
            return ((IsAdult && ClaimCheck) || Bugs || Fish || Fairy ||
                    (!NeedNayrusLove && (CanUse(NAYRUS_LOVE) || CanUse(DINS_FIRE))) || (CanUse(FARORES_WIND))) &&
                   CanDoGlitch(GlitchType::BombOI, difficulty);

        // Hover Boost
        case GlitchType::HoverBoost:
            if (!GlitchEnabled(GlitchHoverBoost, difficulty)) {
                return false;
            }
            return Bombs && CanUse(HOVER_BOOTS) && CanSurviveDamage;

        // Super Slide
        case GlitchType::SuperSlide:
            if (!GlitchEnabled(GlitchSuperSlide, difficulty)) {
                return false;
            }
            return true;

        // Megaflip
        case GlitchType::Megaflip:
            if (!GlitchEnabled(GlitchMegaflip, difficulty)) {
                return false;
            }
            //                Bombchu megaflips should be considered 2 difficulty levels higher
            return CanShield &&
                   (Bombs || (HasBombchus && GlitchValue(GlitchMegaflip) >= static_cast<u8>(difficulty) + 2));

        // A-Slide
        case GlitchType::ASlide:
            if (!GlitchEnabled(GlitchASlide, difficulty)) {
                return false;
            }
            //                Same deal as bombchu megaflips
            return IsChild && CanShield &&
                   (Bombs || (HasBombchus && GlitchValue(GlitchASlide) >= static_cast<u8>(difficulty) + 2));

        // Hammer Slide
        case GlitchType::HammerSlide:
            if (!GlitchEnabled(GlitchHammerSlide, difficulty)) {
                return false;
            }
            return CanUse(MEGATON_HAMMER) && CanUse(HOVER_BOOTS) && CanShield;

        // Ledge Cancel
        case GlitchType::LedgeCancel:
            if (!GlitchEnabled(GlitchLedgeCancel, difficulty)) {
                return false;
            }
            //                Similar to bombchu megaflips / A-slides but doesn't scale beyond advanced
            return CanShield &&
                   (Bombs || (HasBombchus && GlitchEnabled(GlitchLedgeCancel, GlitchDifficulty::ADVANCED)));

        // Action Swap
        case GlitchType::ActionSwap:
            if (!GlitchEnabled(GlitchActionSwap, difficulty)) {
                return false;
            }
            return true;

        // Quick Put Away
        case GlitchType::QPA:
            if (!GlitchEnabled(GlitchQPA, difficulty)) {
                return false;
            }
            return (CanTakeDamage && Bombs &&
                    // Boot Put Away Delay Method
                    ((CanUse(HOVER_BOOTS) || CanUse(IRON_BOOTS)) ||
                     // Frame Perfect Method
                     GlitchEnabled(GlitchQPA, GlitchDifficulty::INTERMEDIATE))) ||
                   // Grab Method
                   GlitchEnabled(GlitchQPA, GlitchDifficulty::ADVANCED);

        // Hookshot Clip
        case GlitchType::HookshotClip:
            if (!GlitchEnabled(GlitchHookshotClip, difficulty)) {
                return false;
            }
            return CanUse(HOOKSHOT);

        // Hookshot Jump: Bonk
        case GlitchType::HookshotJump_Bonk:
            if (!GlitchEnabled(GlitchHookshotJump_Bonk, difficulty)) {
                return false;
            }
            return IsAdult && Hookshot; // Child hookshot jumps are tiny so these stay as adult only until I check

        // Hookshot Jump: Boots
        case GlitchType::HookshotJump_Boots:
            if (!GlitchEnabled(GlitchHookshotJump_Boots, difficulty)) {
                return false;
            }
            return IsAdult && Hookshot &&
                   HasBoots; // Child hookshot jumps are tiny so these stay as adult only until I check

        // Cutscene Dives
        case GlitchType::CutsceneDive:
            if (!GlitchEnabled(GlitchCutsceneDive, difficulty)) {
                return false;
            }
            return true;

        // Navi Dives without TSC
        case GlitchType::NaviDive_Stick:
            if (!GlitchEnabled(GlitchNaviDive_Stick, difficulty)) {
                return false;
            }
            return IsChild && Sticks;

        // Triple Slash Clip
        case GlitchType::TripleSlashClip:
            if (!GlitchEnabled(GlitchTripleSlashClip, difficulty)) {
                return false;
            }
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD);

        // Ledge Clip
        case GlitchType::LedgeClip:
            if (!GlitchEnabled(GlitchLedgeClip, difficulty)) {
                return false;
            }
            return IsAdult;

        // Seam Walks
        case GlitchType::SeamWalk:
            if (!GlitchEnabled(GlitchSeamWalk, difficulty)) {
                return false;
            }
            return true;
    }

    // Shouldn't be reached
    return false;
}

// Updates all logic helpers. Should be called whenever a non-helper is changed
void UpdateHelpers() {
    NumBottles      = ((NoBottles) ? 0 : (Bottles + ((DeliverLetter) ? 1 : 0)));
    HasBottle       = NumBottles >= 1;
    Slingshot       = (ProgressiveBulletBag >= 1) && (BuySeed || AmmoCanDrop);
    Ocarina         = ProgressiveOcarina >= 1;
    OcarinaOfTime   = ProgressiveOcarina >= 2;
    MagicMeter      = (ProgressiveMagic >= 1) && (AmmoCanDrop || (HasBottle && (BuyGPotion || BuyBPotion)));
    BombBag         = (ProgressiveBombBag >= 1) && (BuyBomb || AmmoCanDrop);
    Hookshot        = ProgressiveHookshot >= 1;
    Longshot        = ProgressiveHookshot >= 2;
    Bow             = (ProgressiveBow >= 1) && (BuyArrow || AmmoCanDrop);
    GoronBracelet   = ProgressiveStrength >= 1;
    SilverGauntlets = ProgressiveStrength >= 2;
    GoldenGauntlets = ProgressiveStrength >= 3;
    SilverScale     = ProgressiveScale >= 1;
    GoldScale       = ProgressiveScale >= 2;
    AdultsWallet    = ProgressiveWallet >= 1;
    BiggoronSword   = BiggoronSword || ProgressiveGiantKnife >= 2;

    OcarinaButtonsCount = OcarinaButtonL + OcarinaButtonR + OcarinaButtonX + OcarinaButtonY + OcarinaButtonA;
    ZeldasLullaby       = ZeldasLullaby_item && OcarinaButtonX && OcarinaButtonA && OcarinaButtonY;
    SariasSong          = SariasSong_item && OcarinaButtonR && OcarinaButtonY && OcarinaButtonX;
    SunsSong            = SunsSong_item && OcarinaButtonY && OcarinaButtonR && OcarinaButtonA;
    SongOfStorms        = SongOfStorms_item && OcarinaButtonL && OcarinaButtonR && OcarinaButtonA;
    EponasSong          = EponasSong_item && OcarinaButtonA && OcarinaButtonX && OcarinaButtonY;
    SongOfTime          = SongOfTime_item && OcarinaButtonY && OcarinaButtonL && OcarinaButtonR;
    MinuetOfForest      = MinuetOfForest_item && OcarinaButtonL && OcarinaButtonA && OcarinaButtonX && OcarinaButtonY;
    BoleroOfFire        = BoleroOfFire_item && OcarinaButtonR && OcarinaButtonL && OcarinaButtonY;
    SerenadeOfWater     = SerenadeOfWater_item && OcarinaButtonL && OcarinaButtonR && OcarinaButtonY && OcarinaButtonX;
    RequiemOfSpirit     = RequiemOfSpirit_item && OcarinaButtonL && OcarinaButtonR && OcarinaButtonY;
    NocturneOfShadow    = NocturneOfShadow_item && OcarinaButtonX && OcarinaButtonY && OcarinaButtonL && OcarinaButtonR;
    PreludeOfLight      = PreludeOfLight_item && OcarinaButtonA && OcarinaButtonY && OcarinaButtonX;

    ScarecrowSong    = ScarecrowSong || FreeScarecrow || (ChildScarecrow && AdultScarecrow);
    Scarecrow        = Hookshot && CanPlay(ScarecrowSong);
    DistantScarecrow = Longshot && CanPlay(ScarecrowSong);

    // Drop Access
    DekuStickDrop = StickPot || DekuBabaSticks;
    DekuNutDrop   = (NutPot || NutCrate || DekuBabaNuts) && AmmoCanDrop;
    BugsAccess    = BugShrub || WanderingBugs || BugRock;
    FishAccess    = LoneFish || FishGroup;
    FairyAccess   = FairyPot || GossipStoneFairy || BeanPlantFairy || ButterflyFairy || FreeFairies || FairyPond;

    // refills
    Bombs    = BombBag;
    Nuts     = DekuNutDrop || Nuts;
    Sticks   = DekuStickDrop || Sticks;
    Bugs     = HasBottle && BugsAccess;
    BlueFire = (HasBottle && BlueFireAccess) || (ExtraArrowEffects && CanUse(ICE_ARROWS));
    Fish     = HasBottle && FishAccess;
    Fairy    = HasBottle && FairyAccess && Hearts > 0;

    FoundBombchus  = (BombchuDrop || Bombchus || Bombchus5 || Bombchus10 || Bombchus20);
    CanPlayBowling = (BombchusInLogic && FoundBombchus) || (!BombchusInLogic && BombBag);
    HasBombchus =
        (BuyBombchus5 || BuyBombchus10 || BuyBombchus20 || (AmmoDrops.Is(AMMODROPS_BOMBCHU) && FoundBombchus));

    HasExplosives = Bombs || (BombchusInLogic && HasBombchus);

    HasBoots = IronBoots || HoverBoots;

    // Unshuffled adult trade quest
    Eyedrops     = Eyedrops || (!ShuffleAdultTradeQuest && ClaimCheck);
    EyeballFrog  = EyeballFrog || (!ShuffleAdultTradeQuest && Eyedrops);
    Prescription = Prescription || (!ShuffleAdultTradeQuest && EyeballFrog);
    BrokenSword  = BrokenSword || (!ShuffleAdultTradeQuest && Prescription);
    PoachersSaw  = PoachersSaw || (!ShuffleAdultTradeQuest && BrokenSword);
    OddPoultice  = OddPoultice || (!ShuffleAdultTradeQuest && PoachersSaw);
    OddMushroom  = OddMushroom || (!ShuffleAdultTradeQuest && OddPoultice);
    Cojiro       = Cojiro || (!ShuffleAdultTradeQuest && OddMushroom);
    PocketEgg    = PocketEgg || (!ShuffleAdultTradeQuest && Cojiro);

    // IsChild = Age == AGE_CHILD;
    // IsAdult = Age == AGE_ADULT;

    CanBlastOrSmash = HasExplosives || CanUse(MEGATON_HAMMER);
    CanChildAttack =
        IsChild && (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse(DINS_FIRE) ||
                    CanUse(MASTER_SWORD) || CanUse(MEGATON_HAMMER) || CanUse(BIGGORON_SWORD) || CanUse(HOOKSHOT));
    CanChildDamage = IsChild && (Slingshot || Sticks || KokiriSword || HasExplosives || CanUse(DINS_FIRE) ||
                                 CanUse(MASTER_SWORD) || CanUse(MEGATON_HAMMER) || CanUse(BIGGORON_SWORD));
    CanAdultAttack =
        IsAdult && (CanUse(SLINGSHOT) || CanUse(BOOMERANG) || CanUse(STICKS) || CanUse(KOKIRI_SWORD) || HasExplosives ||
                    CanUse(DINS_FIRE) || MasterSword || Hammer || BiggoronSword || Hookshot);
    CanAdultDamage = IsAdult && (CanUse(SLINGSHOT) || CanUse(STICKS) || CanUse(KOKIRI_SWORD) || HasExplosives ||
                                 CanUse(DINS_FIRE) || MasterSword || Hammer || BiggoronSword);
    CanStunDeku    = CanAdultAttack || CanChildAttack || Nuts || HasShield;
    CanCutShrubs   = CanUse(KOKIRI_SWORD) || CanUse(BOOMERANG) || HasExplosives || CanUse(MASTER_SWORD) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BIGGORON_SWORD);
    CanDive        = ProgressiveScale >= 1;
    CanLeaveForest = OpenForest.IsNot(OPENFOREST_CLOSED) || IsAdult || DekuTreeClear || ShuffleInteriorEntrances ||
                     ShuffleOverworldEntrances;
    CanPlantBugs                    = IsChild && Bugs;
    CanRideEpona                    = IsAdult && Epona && CanPlay(EponasSong);
    CanSummonGossipFairy            = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime || SunsSong);
    CanSummonGossipFairyWithoutSuns = Ocarina && (ZeldasLullaby || EponasSong || SongOfTime);
    Hearts                          = BaseHearts + HeartContainer + (PieceOfHeart >> 2);
    EffectiveHealth =
        ((Hearts << (2 + DoubleDefense)) >> Multiplier) + ((Hearts << (2 + DoubleDefense)) % (1 << Multiplier) >
                                                           0); // Number of half heart hits to die, ranges from 1 to 160
    FireTimer          = CanUse(GORON_TUNIC) ? 255 : (LogicFewerTunicRequirements) ? (Hearts * 8) : 0;
    WaterTimer         = CanUse(ZORA_TUNIC) ? 255 : (LogicFewerTunicRequirements) ? (Hearts * 8) : 0;
    NeedNayrusLove     = (EffectiveHealth <= 1);
    CanSurviveDamage   = !NeedNayrusLove || CanUse(NAYRUS_LOVE);
    CanTakeDamage      = Fairy || CanSurviveDamage;
    CanTakeDamageTwice = (Fairy && NumBottles >= 2) || ((EffectiveHealth == 2) && (CanUse(NAYRUS_LOVE) || Fairy)) ||
                         (EffectiveHealth > 2);
    // CanPlantBean        = IsChild && (MagicBean || MagicBeanPack);
    CanOpenBombGrotto   = CanBlastOrSmash && (ShardOfAgony || LogicGrottosWithoutAgony);
    CanOpenStormGrotto  = CanPlay(SongOfStorms) && (ShardOfAgony || LogicGrottosWithoutAgony);
    HookshotOrBoomerang = CanUse(HOOKSHOT) || CanUse(BOOMERANG);
    CanGetNightTimeGS   = AtNight && (CanPlay(SunsSong) || !NightGSExpectSuns);

    GuaranteeTradePath = ShuffleInteriorEntrances || ShuffleOverworldEntrances || LogicBiggoronBolero ||
                         CanBlastOrSmash || StopGCRollingGoronAsAdult;
    // GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints !=
    // "Agony");
    HasFireSource          = CanUse(DINS_FIRE) || CanUse(FIRE_ARROWS);
    HasFireSourceWithTorch = HasFireSource || CanUse(STICKS);

    // Gerudo Fortress
    CanFinishGerudoFortress =
        SoulGerudo &&
        ((GerudoFortress.Is(GERUDOFORTRESS_NORMAL) && GerudoFortressKeys >= 4 &&
          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)) &&
          (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(HOVER_BOOTS) || LogicGerudoKitchen)) ||
         (GerudoFortress.Is(GERUDOFORTRESS_FAST) && GerudoFortressKeys >= 1 &&
          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD))) ||
         (GerudoFortress.IsNot(GERUDOFORTRESS_NORMAL) && GerudoFortress.IsNot(GERUDOFORTRESS_FAST)));

    HasShield    = CanUse(HYLIAN_SHIELD) || CanUse(DEKU_SHIELD); // Mirror shield can't reflect attacks
    CanShield    = CanUse(MIRROR_SHIELD) || HasShield;
    CanJumpslash = CanUse(STICKS) || CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) ||
                   CanUse(BIGGORON_SWORD); // Not including hammer as hammer jump attacks can be weird
    CanUseProjectile = HasExplosives || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || CanUse(BOOMERANG);
    CanUseMagicArrow = CanUse(FIRE_ARROWS) || CanUse(ICE_ARROWS) || CanUse(LIGHT_ARROWS);

    // Bridge and LACS Requirements
    MedallionCount = (ForestMedallion ? 1 : 0) + (FireMedallion ? 1 : 0) + (WaterMedallion ? 1 : 0) +
                     (SpiritMedallion ? 1 : 0) + (ShadowMedallion ? 1 : 0) + (LightMedallion ? 1 : 0);
    StoneCount   = (KokiriEmerald ? 1 : 0) + (GoronRuby ? 1 : 0) + (ZoraSapphire ? 1 : 0);
    DungeonCount = (DekuTreeClear ? 1 : 0) + (DodongosCavernClear ? 1 : 0) + (JabuJabusBellyClear ? 1 : 0) +
                   (ForestTempleClear ? 1 : 0) + (FireTempleClear ? 1 : 0) + (WaterTempleClear ? 1 : 0) +
                   (SpiritTempleClear ? 1 : 0) + (ShadowTempleClear ? 1 : 0);
    HasAllStones     = StoneCount == 3;
    HasAllMedallions = MedallionCount == 6;

    CanBuildRainbowBridge =
        Bridge.Is(RAINBOWBRIDGE_OPEN) ||
        (Bridge.Is(RAINBOWBRIDGE_VANILLA) && ShadowMedallion && SpiritMedallion && LightArrows) ||
        (Bridge.Is(RAINBOWBRIDGE_STONES) && StoneCount >= BridgeStoneCount.Value<u8>()) ||
        (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS) && MedallionCount >= BridgeMedallionCount.Value<u8>()) ||
        (Bridge.Is(RAINBOWBRIDGE_REWARDS) && StoneCount + MedallionCount >= BridgeRewardCount.Value<u8>()) ||
        (Bridge.Is(RAINBOWBRIDGE_DUNGEONS) && DungeonCount >= BridgeDungeonCount.Value<u8>()) ||
        (Bridge.Is(RAINBOWBRIDGE_TOKENS) && GoldSkulltulaTokens >= BridgeTokenCount.Value<u8>()) ||
        (Bridge.Is(RAINBOWBRIDGE_HEARTS) && Hearts >= BridgeHeartCount.Value<u8>());

    CanTriggerLACS =
        (LACSCondition == LACSCONDITION_VANILLA && ShadowMedallion && SpiritMedallion) ||
        (LACSCondition == LACSCONDITION_STONES && StoneCount >= LACSStoneCount.Value<u8>()) ||
        (LACSCondition == LACSCONDITION_MEDALLIONS && MedallionCount >= LACSMedallionCount.Value<u8>()) ||
        (LACSCondition == LACSCONDITION_REWARDS && StoneCount + MedallionCount >= LACSRewardCount.Value<u8>()) ||
        (LACSCondition == LACSCONDITION_DUNGEONS && DungeonCount >= LACSDungeonCount.Value<u8>()) ||
        (LACSCondition == LACSCONDITION_TOKENS && GoldSkulltulaTokens >= LACSTokenCount.Value<u8>()) ||
        (LACSCondition == LACSCONDITION_HEARTS && Hearts >= LACSHeartCount.Value<u8>());
}

bool SmallKeys(Key dungeon, u8 requiredAmount) {
    return SmallKeys(dungeon, requiredAmount, requiredAmount);
}

bool SmallKeys(Key dungeon, u8 requiredAmountGlitchless, u8 requiredAmountGlitched) {
    switch (dungeon) {
        case FOREST_TEMPLE:
            if (IsGlitched && (GlitchEnabled(GlitchHookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) ||
                               GlitchEnabled(GlitchHoverBoost, GlitchDifficulty::NOVICE) ||
                               (GlitchEnabled(GlitchHover, GlitchDifficulty::NOVICE) &&
                                GlitchEnabled(GlitchISG, GlitchDifficulty::INTERMEDIATE)))) {
                return ForestTempleKeys >= requiredAmountGlitched;
            }
            return ForestTempleKeys >= requiredAmountGlitchless;

        case FIRE_TEMPLE:
            if (IsGlitched && (GlitchEnabled(GlitchLedgeClip, GlitchDifficulty::INTERMEDIATE) ||
                               GlitchEnabled(GlitchHover, GlitchDifficulty::INTERMEDIATE))) {
                return FireTempleKeys >= requiredAmountGlitched;
            }
            return FireTempleKeys >= requiredAmountGlitchless;

        case WATER_TEMPLE:
            if (IsGlitched && (false)) {
                return WaterTempleKeys >= requiredAmountGlitched;
            }
            return WaterTempleKeys >= requiredAmountGlitchless;

        case SPIRIT_TEMPLE:
            if (IsGlitched && (false)) {
                return SpiritTempleKeys >= requiredAmountGlitched;
            }
            return SpiritTempleKeys >= requiredAmountGlitchless;

        case SHADOW_TEMPLE:
            if (IsGlitched && (GlitchEnabled(GlitchHookshotClip, GlitchDifficulty::NOVICE))) {
                return ShadowTempleKeys >= requiredAmountGlitched;
            }
            return ShadowTempleKeys >= requiredAmountGlitchless;

        case BOTTOM_OF_THE_WELL:
            if (IsGlitched && (false)) {
                return BottomOfTheWellKeys >= requiredAmountGlitched;
            }
            return BottomOfTheWellKeys >= requiredAmountGlitchless;

        case GERUDO_TRAINING_GROUNDS:
            if (IsGlitched && (false)) {
                return GerudoTrainingGroundsKeys >= requiredAmountGlitched;
            }
            return GerudoTrainingGroundsKeys >= requiredAmountGlitchless;

        case GANONS_CASTLE:
            if (IsGlitched && (false)) {
                return GanonsCastleKeys >= requiredAmountGlitched;
            }
            return GanonsCastleKeys >= requiredAmountGlitchless;

        case MARKET_TREASURE_CHEST_GAME:
            if (IsGlitched && (false)) {
                return TreasureGameKeys >= requiredAmountGlitched;
            }
            return TreasureGameKeys >= requiredAmountGlitchless;

        default:
            return false;
    }
}

bool EventsUpdated() {

    if (DekuTreeClearPast != DekuTreeClear || GoronRubyPast != GoronRuby || ZoraSapphirePast != ZoraSapphire ||
        ForestTrialClearPast != ForestTrialClear || FireTrialClearPast != FireTrialClear ||
        WaterTrialClearPast != WaterTrialClear || ShadowTrialClearPast != ShadowTrialClear ||
        SpiritTrialClearPast != SpiritTrialClear || LightTrialClearPast != LightTrialClear ||
        DrainWellPast != DrainWell || DampesWindmillAccessPast != DampesWindmillAccess ||
        TimeTravelPast != TimeTravel) {
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

// Reset All Logic to false
void LogicReset() {
    // Settings-dependent variables
    IsKeysanity =
        Keysanity.Is(KEYSANITY_ANYWHERE) || Keysanity.Is(KEYSANITY_OVERWORLD) || Keysanity.Is(KEYSANITY_ANY_DUNGEON);
    AmmoCanDrop = AmmoDrops.IsNot(AMMODROPS_NONE);

    // Child item logic
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

    // Adult logic
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
    MasterSword   = false;
    BiggoronSword = false;

    // Trade Quest
    PocketEgg    = false;
    Cojiro       = false;
    OddMushroom  = false;
    OddPoultice  = false;
    PoachersSaw  = false;
    BrokenSword  = false;
    Prescription = false;
    EyeballFrog  = false;
    Eyedrops     = false;
    ClaimCheck   = false;

    // Trade Quest Events
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

    // Songs
    ZeldasLullaby_item    = false;
    SariasSong_item       = false;
    SunsSong_item         = false;
    SongOfStorms_item     = false;
    EponasSong_item       = false;
    SongOfTime_item       = false;
    MinuetOfForest_item   = false;
    BoleroOfFire_item     = false;
    SerenadeOfWater_item  = false;
    RequiemOfSpirit_item  = false;
    NocturneOfShadow_item = false;
    PreludeOfLight_item   = false;
    // Ocarina notes buttons
    OcarinaButtonL      = !ShuffleOcarinaButtons;
    OcarinaButtonR      = !ShuffleOcarinaButtons;
    OcarinaButtonX      = !ShuffleOcarinaButtons;
    OcarinaButtonY      = !ShuffleOcarinaButtons;
    OcarinaButtonA      = !ShuffleOcarinaButtons;
    OcarinaButtonsCount = 0;
    // Songs + their ocarina notes
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

    // Stones and Meddallions
    ForestMedallion = false;
    FireMedallion   = false;
    WaterMedallion  = false;
    SpiritMedallion = false;
    ShadowMedallion = false;
    LightMedallion  = false;
    KokiriEmerald   = false;
    GoronRuby       = false;
    ZoraSapphire    = false;

    // Dungeon Clears
    DekuTreeClear       = false;
    DodongosCavernClear = false;
    JabuJabusBellyClear = false;
    ForestTempleClear   = false;
    FireTempleClear     = false;
    WaterTempleClear    = false;
    SpiritTempleClear   = false;
    ShadowTempleClear   = false;

    // Trial Clears
    ForestTrialClear = false;
    FireTrialClear   = false;
    WaterTrialClear  = false;
    SpiritTrialClear = false;
    ShadowTrialClear = false;
    LightTrialClear  = false;

    // Progressive Items
    ProgressiveBulletBag  = 0;
    ProgressiveBombBag    = 0;
    ProgressiveMagic      = 0;
    ProgressiveScale      = 0;
    ProgressiveHookshot   = 0;
    ProgressiveBow        = 0;
    ProgressiveWallet     = 0;
    ProgressiveStrength   = 0;
    ProgressiveOcarina    = 0;
    ProgressiveGiantKnife = 0;

    // Keys
    ForestTempleKeys = 0;
    // If not keysanity, start with 1 logical key to account for automatically unlocking the basement door in vanilla
    // FiT
    FireTempleKeys            = IsKeysanity || Dungeon::FireTemple.IsMQ() ? 0 : 1;
    WaterTempleKeys           = 0;
    SpiritTempleKeys          = 0;
    ShadowTempleKeys          = 0;
    GanonsCastleKeys          = 0;
    GerudoFortressKeys        = 0;
    GerudoTrainingGroundsKeys = 0;
    BottomOfTheWellKeys       = 0;
    TreasureGameKeys          = 0;

    // Boss Keys
    BossKeyForestTemple = 0;
    BossKeyFireTemple   = 0;
    BossKeyWaterTemple  = 0;
    BossKeySpiritTemple = 0;
    BossKeyShadowTemple = 0;
    BossKeyGanonsCastle = 0;

    // Gold Skulltula Count
    GoldSkulltulaTokens = 0;

    // Bottle Count
    Bottles    = 0;
    NumBottles = 0;
    NoBottles  = false;

    // Drops and Bottle Contents Access
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
    BombchuDrop      = false;

    BuyBombchus5  = false;
    BuyBombchus10 = false;
    BuyBombchus20 = false;
    BuySeed       = false;
    BuyArrow      = false;
    BuyBomb       = false;
    BuyGPotion    = false;
    BuyBPotion    = false;
    MagicRefill   = false;

    PieceOfHeart   = 0;
    HeartContainer = 0;
    DoubleDefense  = false;
    TriforcePieces = 0;

    SoulPoe               = ShuffleEnemySouls.Is(OFF);
    SoulOctorok           = ShuffleEnemySouls.Is(OFF);
    SoulKeese             = ShuffleEnemySouls.Is(OFF);
    SoulTektite           = ShuffleEnemySouls.Is(OFF);
    SoulLeever            = ShuffleEnemySouls.Is(OFF);
    SoulPeahat            = ShuffleEnemySouls.Is(OFF);
    SoulLizalfosDinolfos  = ShuffleEnemySouls.Is(OFF);
    SoulShabom            = ShuffleEnemySouls.Is(OFF);
    SoulBiriBari          = ShuffleEnemySouls.Is(OFF);
    SoulTailpasaran       = ShuffleEnemySouls.Is(OFF);
    SoulSkulltula         = ShuffleEnemySouls.Is(OFF);
    SoulTorchSlug         = ShuffleEnemySouls.Is(OFF);
    SoulStinger           = ShuffleEnemySouls.Is(OFF);
    SoulMoblin            = ShuffleEnemySouls.Is(OFF);
    SoulArmos             = ShuffleEnemySouls.Is(OFF);
    SoulDekuBaba          = ShuffleEnemySouls.Is(OFF);
    SoulBubble            = ShuffleEnemySouls.Is(OFF);
    SoulFlyingTrap        = ShuffleEnemySouls.Is(OFF);
    SoulBeamos            = ShuffleEnemySouls.Is(OFF);
    SoulWallmaster        = ShuffleEnemySouls.Is(OFF);
    SoulRedeadGibdo       = ShuffleEnemySouls.Is(OFF);
    SoulShellBlade        = ShuffleEnemySouls.Is(OFF);
    SoulLikeLike          = ShuffleEnemySouls.Is(OFF);
    SoulParasiticTentacle = ShuffleEnemySouls.Is(OFF);
    SoulAnubis            = ShuffleEnemySouls.Is(OFF);
    SoulSpike             = ShuffleEnemySouls.Is(OFF);
    SoulSkullKid          = ShuffleEnemySouls.Is(OFF);
    SoulFreezard          = ShuffleEnemySouls.Is(OFF);
    SoulDekuScrub         = ShuffleEnemySouls.Is(OFF);
    SoulWolfos            = ShuffleEnemySouls.Is(OFF);
    SoulStalchild         = ShuffleEnemySouls.Is(OFF);
    SoulGuay              = ShuffleEnemySouls.Is(OFF);
    SoulDoorMimic         = ShuffleEnemySouls.Is(OFF);
    SoulStalfos           = ShuffleEnemySouls.Is(OFF);
    SoulDarkLink          = ShuffleEnemySouls.Is(OFF);
    SoulFlareDancer       = ShuffleEnemySouls.Is(OFF);
    SoulDeadHand          = ShuffleEnemySouls.Is(OFF);
    SoulGerudo            = ShuffleEnemySouls.Is(OFF);
    SoulGohma             = ShuffleEnemySouls.Is(OFF);
    SoulDodongo           = ShuffleEnemySouls.Is(OFF);
    SoulBarinade          = ShuffleEnemySouls.Is(OFF);
    SoulPhantomGanon      = ShuffleEnemySouls.Is(OFF);
    SoulVolvagia          = ShuffleEnemySouls.Is(OFF);
    SoulMorpha            = ShuffleEnemySouls.Is(OFF);
    SoulBongoBongo        = ShuffleEnemySouls.Is(OFF);
    SoulTwinrova          = ShuffleEnemySouls.Is(OFF);
    SoulGanon             = ShuffleEnemySouls.Is(OFF);

    /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
    /* These are used to simplify reading the logic, but need to be updated
    /  every time a base value is updated.                       */

    Slingshot       = false;
    Ocarina         = false;
    OcarinaOfTime   = false;
    BombBag         = false;
    MagicMeter      = false;
    Hookshot        = false;
    Longshot        = false;
    Bow             = false;
    GoronBracelet   = false;
    SilverGauntlets = false;
    GoldenGauntlets = false;
    SilverScale     = false;
    GoldScale       = false;
    AdultsWallet    = false;

    ChildScarecrow   = false;
    AdultScarecrow   = false;
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

    FoundBombchus                   = false;
    CanPlayBowling                  = false;
    HasBombchus                     = false;
    HasExplosives                   = false;
    HasBoots                        = false;
    IsChild                         = false;
    IsAdult                         = false;
    IsGlitched                      = Settings::Logic.Is(LOGIC_GLITCHED);
    CanBlastOrSmash                 = false;
    CanChildAttack                  = false;
    CanChildDamage                  = false;
    CanAdultAttack                  = false;
    CanAdultDamage                  = false;
    CanCutShrubs                    = false;
    CanDive                         = false;
    CanLeaveForest                  = false;
    CanPlantBugs                    = false;
    CanRideEpona                    = false;
    CanStunDeku                     = false;
    CanSummonGossipFairy            = false;
    CanSummonGossipFairyWithoutSuns = false;
    // CanPlantBean        = false;
    CanOpenBombGrotto   = false;
    CanOpenStormGrotto  = false;
    BigPoeKill          = false;
    HookshotOrBoomerang = false;

    BaseHearts      = StartingHearts.Value<u8>();
    Hearts          = 0;
    Multiplier      = (DamageMultiplier.Value<u8>() < 6) ? DamageMultiplier.Value<u8>() : 10;
    EffectiveHealth = 0;
    FireTimer       = 0;
    WaterTimer      = 0;

    GuaranteeTradePath     = false;
    GuaranteeHint          = false;
    HasFireSource          = false;
    HasFireSourceWithTorch = false;

    CanFinishGerudoFortress = false;

    HasShield        = false;
    CanShield        = false;
    CanJumpslash     = false;
    CanUseProjectile = false;
    CanUseMagicArrow = false;

    // Bridge Requirements
    HasAllStones          = false;
    HasAllMedallions      = false;
    CanBuildRainbowBridge = false;
    BuiltRainbowBridge    = false;
    CanTriggerLACS        = false;

    // Other
    AtDay   = false;
    AtNight = false;
    Age     = Settings::ResolvedStartingAge;

    // Events
    ShowedMidoSwordAndShield  = false;
    CarpenterRescue           = false;
    GF_GateOpen               = false;
    GtG_GateOpen              = false;
    DampesWindmillAccess      = false;
    DrainWell                 = false;
    GoronCityChildFire        = false;
    GCWoodsWarpOpen           = false;
    GCDaruniasDoorOpenChild   = false;
    StopGCRollingGoronAsAdult = false;
    WaterTempleLow            = false;
    WaterTempleMiddle         = false;
    WaterTempleHigh           = false;
    KakarikoVillageGateOpen   = false;
    KingZoraThawed            = false;
    ForestTempleJoelle        = false;
    ForestTempleBeth          = false;
    ForestTempleJoAndBeth     = false;
    ForestTempleAmy           = false;
    ForestTempleMeg           = false;
    ForestTempleAmyAndMeg     = false;
    FireLoopSwitch            = false;
    LinksCow                  = false;
    AtDampeTime               = false;
    DeliverLetter             = false;
    TimeTravel                = false;

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
    TimeTravelPast           = false;
}
} // namespace Logic
