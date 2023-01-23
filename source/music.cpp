#include "music.hpp"
#include "random.hpp"
#include <3ds.h>
#include <cstdlib>
#include "settings.hpp"
#include "sound_archive.hpp"
#include "sequence_data.hpp"

namespace Music {
// clang-format off
const std::array<SeqType, SEQ_COUNT> seqTypesMusic = {
    /* NA_BGM_FIELD */              SEQ_BGM_WORLD,
    /* NA_BGM_DUNGEON */            SEQ_BGM_WORLD,
    /* NA_BGM_KAKARIKO_ADULT */     SEQ_BGM_WORLD,
    /* NA_BGM_ENEMY */              SEQ_NOSHUFFLE, // Temporarily unshuffled: Override plays incorrect in some areas, like Lake Hylia, by continuously repeating the start
    /* NA_BGM_BOSS00 */             SEQ_BGM_BATTLE,
    /* NA_BGM_FAIRY_DUNGEON */      SEQ_BGM_WORLD,
    /* NA_BGM_MARKET */             SEQ_BGM_WORLD,
    /* NA_BGM_TITLE */              SEQ_BGM_WORLD,
    /* NA_BGM_LINK_HOUSE */         SEQ_BGM_WORLD,
    /* NA_BGM_GAME_OVER */          SEQ_FANFARE,
    /* NA_BGM_BOSS_CLEAR */         SEQ_FANFARE,
    /* NA_BGM_ITEM_GET */           SEQ_FANFARE,
    /* NA_BGM_OPENING_GANON */      SEQ_FANFARE,
    /* NA_BGM_HEART_GET */          SEQ_FANFARE,
    /* NA_BGM_OCA_LIGHT */          SEQ_OCARINA,
    /* NA_BGM_BUYO_DUNGEON */       SEQ_BGM_WORLD,
    /* NA_BGM_KAKARIKO_KID */       SEQ_BGM_WORLD,
    /* NA_BGM_GODESS */             SEQ_BGM_EVENT,
    /* NA_BGM_HIME */               SEQ_BGM_EVENT,
    /* NA_BGM_FIRE_DUNGEON */       SEQ_BGM_WORLD,
    /* NA_BGM_OPEN_TRE_BOX */       SEQ_FANFARE,
    /* NA_BGM_FORST_DUNGEON */      SEQ_BGM_WORLD,
    /* NA_BGM_HIRAL_GARDEN */       SEQ_BGM_WORLD,
    /* NA_BGM_GANON_TOWER */        SEQ_BGM_WORLD,
    /* NA_BGM_RONRON */             SEQ_BGM_WORLD,
    /* NA_BGM_GORON */              SEQ_BGM_WORLD,
    /* NA_BGM_SPIRIT_STONE */       SEQ_FANFARE,
    /* NA_BGM_OCA_FLAME */          SEQ_OCARINA,
    /* NA_BGM_OCA_WIND */           SEQ_OCARINA,
    /* NA_BGM_OCA_WATER */          SEQ_OCARINA,
    /* NA_BGM_OCA_SOUL */           SEQ_OCARINA,
    /* NA_BGM_OCA_DARKNESS */       SEQ_OCARINA,
    /* NA_BGM_MIDDLE_BOSS */        SEQ_BGM_ERROR,
    /* NA_BGM_S_ITEM_GET */         SEQ_FANFARE,
    /* NA_BGM_SHRINE_OF_TIME */     SEQ_BGM_WORLD,
    /* NA_BGM_EVENT_CLEAR */        SEQ_FANFARE,
    /* NA_BGM_KOKIRI */             SEQ_BGM_WORLD,
    /* NA_BGM_OCA_YOUSEI */         SEQ_FANFARE,
    /* NA_BGM_MAYOIMORI */          SEQ_BGM_WORLD,
    /* NA_BGM_SOUL_DUNGEON */       SEQ_BGM_WORLD,
    /* NA_BGM_HORSE */              SEQ_BGM_EVENT,
    /* NA_BGM_HORSE_GOAL */         SEQ_FANFARE,
    /* NA_BGM_INGO */               SEQ_BGM_WORLD,
    /* NA_BGM_MEDAL_GET */          SEQ_FANFARE,
    /* NA_BGM_OCA_SARIA */          SEQ_OCARINA,
    /* NA_BGM_OCA_EPONA */          SEQ_OCARINA,
    /* NA_BGM_OCA_ZELDA */          SEQ_OCARINA,
    /* NA_BGM_OCA_SUNMOON */        SEQ_NOSHUFFLE, /* Remove Sun's Song from the Ocarina pool for now due to bugs */
    /* NA_BGM_OCA_TIME */           SEQ_OCARINA,
    /* NA_BGM_OCA_STORM */          SEQ_OCARINA,
    /* NA_BGM_NAVI */               SEQ_BGM_EVENT,
    /* NA_BGM_DEKUNOKI */           SEQ_BGM_EVENT,
    /* NA_BGM_FUSHA */              SEQ_BGM_WORLD,
    /* NA_BGM_HIRAL_DEMO */         SEQ_NOSHUFFLE,
    /* NA_BGM_MINI_GAME */          SEQ_BGM_EVENT,
    /* NA_BGM_SEAK */               SEQ_BGM_EVENT,
    /* NA_BGM_ZORA */               SEQ_BGM_WORLD,
    /* NA_BGM_APPEAR */             SEQ_FANFARE,
    /* NA_BGM_ADULT_LINK */         SEQ_BGM_EVENT,
    /* NA_BGM_MASTER_SWORD */       SEQ_FANFARE,
    /* NA_BGM_INTRO_GANON */        SEQ_BGM_EVENT,
    /* NA_BGM_SHOP */               SEQ_BGM_WORLD,
    /* NA_BGM_KENJA */              SEQ_BGM_EVENT,
    /* NA_BGM_FILE_SELECT */        SEQ_NOSHUFFLE,
    /* NA_BGM_ICE_DUNGEON */        SEQ_BGM_WORLD,
    /* NA_BGM_GATE_OPEN */          SEQ_NOSHUFFLE,
    /* NA_BGM_OWL */                SEQ_BGM_EVENT,
    /* NA_BGM_DARKNESS_DUNGEON */   SEQ_BGM_WORLD,
    /* NA_BGM_AQUA_DUNGEON */       SEQ_BGM_WORLD,
    /* NA_BGM_BRIDGE */             SEQ_NOSHUFFLE,
    /* NA_BGM_SARIA */              SEQ_NOSHUFFLE,
    /* NA_BGM_GERUDO */             SEQ_BGM_WORLD,
    /* NA_BGM_DRUGSTORE */          SEQ_BGM_WORLD,
    /* NA_BGM_KOTAKE_KOUME */       SEQ_BGM_EVENT,
    /* NA_BGM_ESCAPE */             SEQ_BGM_EVENT,
    /* NA_BGM_UNDERGROUND */        SEQ_BGM_WORLD,
    /* NA_BGM_GANON_BATTLE_1 */     SEQ_BGM_BATTLE,
    /* NA_BGM_GANON_BATTLE_2 */     SEQ_BGM_BATTLE,
    /* NA_BGM_END_DEMO */           SEQ_NOSHUFFLE,
    /* NA_BGM_STAFF_1 */            SEQ_NOSHUFFLE,
    /* NA_BGM_STAFF_2 */            SEQ_NOSHUFFLE,
    /* NA_BGM_STAFF_3 */            SEQ_NOSHUFFLE,
    /* NA_BGM_STAFF_4 */            SEQ_NOSHUFFLE,
    /* NA_BGM_BOSS01 */             SEQ_BGM_BATTLE,
    /* NA_BGM_MINI_GAME_2 */        SEQ_BGM_ERROR,
};
// clang-format on
std::array<u32, SEQ_COUNT> seqOverridesMusic;

/* Initializes the list of music overrides to unshuffled */
void InitMusicRandomizer() {
    for (int i = 0; i < SEQ_COUNT; i++)
        seqOverridesMusic[i] = BGM_BASE + i;
}

/* Shuffles the sequences grouping them by type */
/* type is a bitmask of SeqType */
void ShuffleSequences(int type) {
    std::vector<u32> seqs;

    // Get all sequences of the desired type(s) into a vector
    for (int i = 0; i < SEQ_COUNT; i++) {
        if (seqTypesMusic[i] & type) {
            seqs.push_back(seqOverridesMusic[i]);
        }
    }

    // Shuffle the vector...
    for (std::size_t i = 0; i < seqs.size(); i++) {
        std::swap(seqs[i], seqs[Random(0, seqs.size(), true)]);
    }

    // ...and feed it back into the overrides array
    for (int i = 0; i < SEQ_COUNT; i++) {
        if (seqTypesMusic[i] & type) {
            seqOverridesMusic[i] = seqs.back();
            seqs.pop_back();
        }
    }
}

// BGM: Overworld
static AudioCategoryLeaf acBgm_HyruleField("Hyrule Field", 9);
static AudioCategoryLeaf acBgm_KakarikoAdult("Kakariko Adult", 11);
static AudioCategoryLeaf acBgm_Market("Market", 15);
static AudioCategoryLeaf acBgm_KakarikoChild("Kakariko Child", 25);
static AudioCategoryLeaf acBgm_LonLonRanch("Lon Lon Ranch", 33);
static AudioCategoryLeaf acBgm_GoronCity("Goron City", 34);
static AudioCategoryLeaf acBgm_KokiriForest("Kokiri Forest", 45);
static AudioCategoryLeaf acBgm_LostWoods("Lost Woods", 47);
static AudioCategoryLeaf acBgm_ZorasDomain("Zora's Domain", 65);
static AudioCategoryLeaf acBgm_GerudoValley("Gerudo Valley", 79);
// BGM: Interiors
static AudioCategoryLeaf acBgm_HouseTheme("House Theme", 17);
static AudioCategoryLeaf acBgm_FairyFountain("Fairy Fountain", 26);
static AudioCategoryLeaf acBgm_TempleTime("Temple of Time", 43);
static AudioCategoryLeaf acBgm_Windmill("Windmill", 61);
static AudioCategoryLeaf acBgm_ShopTheme("Shop Theme", 70);
static AudioCategoryLeaf acBgm_GrannysPotionShop("Granny's Potion Shop", 80);
static AudioCategoryLeaf acBgm_Underground("Underground", 83);
// BGM: Dungeons
static AudioCategoryLeaf acBgm_MiscDungeon("Misc Dungeon", 10);
static AudioCategoryLeaf acBgm_InsideDekuTree("Deku Tree", 14);
static AudioCategoryLeaf acBgm_JabuJabu("Jabu Jabu", 24);
static AudioCategoryLeaf acBgm_FireTemple("Fire Temple", 28);
static AudioCategoryLeaf acBgm_ForestTemple("Forest Temple", 30);
static AudioCategoryLeaf acBgm_GanonsTower("Ganon's Tower", 32);
static AudioCategoryLeaf acBgm_SpiritTemple("Spirit Temple", 48);
static AudioCategoryLeaf acBgm_IceCavern("Ice Cavern", 73);
static AudioCategoryLeaf acBgm_ShadowTemple("Shadow Temple", 76);
static AudioCategoryLeaf acBgm_WaterTemple("Water Temple", 77);
// BGM: Area Themes
static AudioCategory acBgm_Overworld("Overworld", {
                                                      &acBgm_HyruleField,
                                                      &acBgm_KakarikoAdult,
                                                      &acBgm_Market,
                                                      &acBgm_KakarikoChild,
                                                      &acBgm_LonLonRanch,
                                                      &acBgm_GoronCity,
                                                      &acBgm_KokiriForest,
                                                      &acBgm_LostWoods,
                                                      &acBgm_ZorasDomain,
                                                      &acBgm_GerudoValley,
                                                  });
static AudioCategory acBgm_Interiors("Interiors", {
                                                      &acBgm_HouseTheme,
                                                      &acBgm_FairyFountain,
                                                      &acBgm_TempleTime,
                                                      &acBgm_Windmill,
                                                      &acBgm_ShopTheme,
                                                      &acBgm_GrannysPotionShop,
                                                      &acBgm_Underground,
                                                  });
static AudioCategory acBgm_Dungeons("Dungeons", {
                                                    &acBgm_MiscDungeon,
                                                    &acBgm_InsideDekuTree,
                                                    &acBgm_JabuJabu,
                                                    &acBgm_FireTemple,
                                                    &acBgm_ForestTemple,
                                                    &acBgm_GanonsTower,
                                                    &acBgm_SpiritTemple,
                                                    &acBgm_IceCavern,
                                                    &acBgm_ShadowTemple,
                                                    &acBgm_WaterTemple,
                                                });
// BGM: Event Music
static AudioCategoryLeaf acBgm_TitleScreen("Title Screen", 16);
static AudioCategoryLeaf acBgm_ZeldasTheme("Zelda's Theme", 27);
static AudioCategoryLeaf acBgm_CastleCourtyard("Castle Courtyard", 31);
static AudioCategoryLeaf acBgm_HorseRace("Horse Race", 49);
static AudioCategoryLeaf acBgm_IngosTheme("Ingo's Theme", 51);
static AudioCategoryLeaf acBgm_NaviIntro("Navi Intro", 59);
static AudioCategoryLeaf acBgm_DekuTreeTheme("Deku Tree's Theme", 60);
static AudioCategoryLeaf acBgm_MinigameTheme01("Minigame Theme 1", 63);
static AudioCategoryLeaf acBgm_SheiksTheme("Sheik's Theme", 64);
static AudioCategoryLeaf acBgm_AdultLink("Adult Link", 67); // Should probably be renamed
static AudioCategoryLeaf acBgm_GanondorfsTheme("Ganondorf's Theme", 69);
static AudioCategoryLeaf acBgm_GoddessTheme("Goddess Theme", 71);
static AudioCategoryLeaf acBgm_FileSelect("File Select", 72);
static AudioCategoryLeaf acBgm_OwlsTheme("Owl's Theme", 75);
static AudioCategoryLeaf acBgm_KotakeKoume("Kotake & Koume", 81);
static AudioCategoryLeaf acBgm_TowerEscape("Tower Escape", 82);
static AudioCategoryLeaf acBgm_MinigameTheme02("Minigame Theme 2", 92);
// BGM: Battle Themes
static AudioCategoryLeaf acBgm_Enemy("Enemy Theme", 12);
static AudioCategoryLeaf acBgm_Boss00("Boss Theme 1", 13);
static AudioCategoryLeaf acBgm_MiniBoss("Mini Boss", 41);
static AudioCategoryLeaf acBgm_GanondorfBattle("Ganondorf Battle", 84);
static AudioCategoryLeaf acBgm_GanonBattle("Ganon Battle", 85);
static AudioCategoryLeaf acBgm_Boss01("Boss Theme 2", 91);
// BGM: Root
static AudioCategory acBgm_AreaThemes("Area Themes", { &acBgm_Overworld, &acBgm_Interiors, &acBgm_Dungeons });
static AudioCategory acBgm_EventMusic("Event Music", {
                                                         &acBgm_TitleScreen,
                                                         &acBgm_ZeldasTheme,
                                                         &acBgm_CastleCourtyard,
                                                         &acBgm_HorseRace,
                                                         &acBgm_IngosTheme,
                                                         &acBgm_NaviIntro,
                                                         &acBgm_DekuTreeTheme,
                                                         &acBgm_MinigameTheme01,
                                                         &acBgm_SheiksTheme,
                                                         &acBgm_AdultLink,
                                                         &acBgm_GanondorfsTheme,
                                                         &acBgm_GoddessTheme,
                                                         &acBgm_FileSelect,
                                                         &acBgm_OwlsTheme,
                                                         &acBgm_KotakeKoume,
                                                         &acBgm_TowerEscape,
                                                         &acBgm_MinigameTheme02,
                                                     });
static AudioCategory acBgm_BattleThemes("Battle Themes", {
                                                             &acBgm_Enemy,
                                                             &acBgm_Boss00,
                                                             &acBgm_MiniBoss,
                                                             &acBgm_GanondorfBattle,
                                                             &acBgm_GanonBattle,
                                                             &acBgm_Boss01,
                                                         });
// BGM
static AudioCategory acBgm_Root("Background Music", { &acBgm_AreaThemes, &acBgm_EventMusic, &acBgm_BattleThemes });

// Melodies: Item Jingles
static AudioCategoryLeaf acMelodies_ItemGet("Item Get", 20);
static AudioCategoryLeaf acMelodies_HeartContainerGet("Heart Container Get", 22);
static AudioCategoryLeaf acMelodies_TreasureChestOpening("Treasure Chest Opening", 29);
static AudioCategoryLeaf acMelodies_SpiritualStoneGet("Spiritual Stone Get", 35);
static AudioCategoryLeaf acMelodies_SmallItemGet("Small Item Get", 42);
static AudioCategoryLeaf acMelodies_SongLearned("Song Learned", 46);
static AudioCategoryLeaf acMelodies_MedallionGet("Medallion Get", 52);
// Melodies: Misc Fanfares
static AudioCategoryLeaf acMelodies_GameOver("Game Over", 18);
static AudioCategoryLeaf acMelodies_BossClear("Boss Clear", 19);
static AudioCategoryLeaf acMelodies_GanonAppears("Ganon Appears", 21);
static AudioCategoryLeaf acMelodies_EventClear("Event Clear", 44);
static AudioCategoryLeaf acMelodies_HorseGoal("Horse Goal", 50);
static AudioCategoryLeaf acMelodies_Appearance("Appearance", 66);
static AudioCategoryLeaf acMelodies_MasterSword("Master Sword", 68);
static AudioCategoryLeaf acMelodies_DoorTimeOpened("Door of Time Opened", 74);
static AudioCategoryLeaf acMelodies_RainbowBridge("Rainbow Bridge", 78);
// Melodies: Fanfares
static AudioCategory acMelodies_ItemJingles("Item Jingles", {
                                                                &acMelodies_ItemGet,
                                                                &acMelodies_HeartContainerGet,
                                                                &acMelodies_TreasureChestOpening,
                                                                &acMelodies_SpiritualStoneGet,
                                                                &acMelodies_SmallItemGet,
                                                                &acMelodies_SongLearned,
                                                                &acMelodies_MedallionGet,
                                                            });
static AudioCategory acMelodies_MiscFanfares("Misc Fanfares", {
                                                                  &acMelodies_GameOver,
                                                                  &acMelodies_BossClear,
                                                                  &acMelodies_GanonAppears,
                                                                  &acMelodies_EventClear,
                                                                  &acMelodies_HorseGoal,
                                                                  &acMelodies_Appearance,
                                                                  &acMelodies_MasterSword,
                                                                  &acMelodies_DoorTimeOpened,
                                                                  &acMelodies_RainbowBridge,
                                                              });
// Melodies: Child Songs
static AudioCategoryLeaf acMelodies_SariasSong("Saria's Song", 53);
static AudioCategoryLeaf acMelodies_EponasSong("Epona's Song", 54);
static AudioCategoryLeaf acMelodies_ZeldasLullaby("Zelda's Lullaby", 55);
// static AudioCategoryLeaf acMelodies_SunsSong("Sun's Song", 56); // Still unshuffled because of bugs
static AudioCategoryLeaf acMelodies_SongTime("Song of Time", 57);
static AudioCategoryLeaf acMelodies_SongStorms("Song of Storms", 58);
// Melodies: Warp Songs
static AudioCategoryLeaf acMelodies_PreludeLight("Prelude of Light", 23);
static AudioCategoryLeaf acMelodies_BoleroFire("Bolero of Fire", 36);
static AudioCategoryLeaf acMelodies_MinuetForest("Minuet of Forest", 37);
static AudioCategoryLeaf acMelodies_SerenadeWater("Serenade of Water", 38);
static AudioCategoryLeaf acMelodies_RequiemSpirit("Requiem of Spirit", 39);
static AudioCategoryLeaf acMelodies_NoctureShadow("Nocture of Shadow", 40);
// Melodies: Ocarina Songs
static AudioCategory acMelodies_ChildSongs("Child Songs", {
                                                              &acMelodies_SariasSong,
                                                              &acMelodies_EponasSong,
                                                              &acMelodies_ZeldasLullaby,
                                                              //&acMelodies_SunsSong,
                                                              &acMelodies_SongTime,
                                                              &acMelodies_SongStorms,
                                                          });
static AudioCategory acMelodies_WarpSongs("Warp Songs", {
                                                            &acMelodies_PreludeLight,
                                                            &acMelodies_BoleroFire,
                                                            &acMelodies_MinuetForest,
                                                            &acMelodies_SerenadeWater,
                                                            &acMelodies_RequiemSpirit,
                                                            &acMelodies_NoctureShadow,
                                                        });
// Melodies: Root
static AudioCategory acMelodies_Fanfares("Fanfares", { &acMelodies_ItemJingles, &acMelodies_MiscFanfares });
static AudioCategory acMelodies_OcarinaSongs("Ocarina Songs", { &acMelodies_ChildSongs, &acMelodies_WarpSongs });
// Melodies
static AudioCategory acMelodies_Root("Melodies", { &acMelodies_Fanfares, &acMelodies_OcarinaSongs });

bool archiveFound     = false;
bool musicDirsCreated = false;

void CreateMusicDirectories() {
    FS_Archive sdmcArchive;

    // Open SD archive
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
        return;
    }

    // Create all dirs
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/OoT3DR"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, CustomMusicRootPath.c_str()), FS_ATTRIBUTE_DIRECTORY);
    acBgm_Root.CreateDirectories(sdmcArchive);
    acMelodies_Root.CreateDirectories(sdmcArchive);

    musicDirsCreated = true;
    FSUSER_CloseArchive(sdmcArchive);
}

int ShuffleMusic_Archive() {
    if (!musicDirsCreated) {
        return SARSHUFFLE_NO_DIRS;
    }

    FS_Archive sdmcArchive;
    if (!R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
        return SARSHUFFLE_SDMC_ARCHIVE_FAIL;
    }

    // Title ID
    std::string titleId;
    if (Settings::Region == REGION_EUR) {
        titleId = "0004000000033600";
    } else { // REGION_NA
        titleId = "0004000000033500";
    }

    // Archive Paths
    static const std::string bcsarPath    = CustomMusicRootPath + "QueenSound.bcsar";
    static const std::string newBcsarPath = "/luma/titles/" + titleId + "/romfs/sound/QueenSound.bcsar";

    // Delete previous
    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, newBcsarPath.c_str()));

    // Create new archive
    SoundArchive sar(sdmcArchive, bcsarPath);

    if (!sar.SuccessfullyInitialized()) {
        FSUSER_CloseArchive(sdmcArchive);
        archiveFound = false;
        return SARSHUFFLE_BCSAR_NOT_FOUND;
    }
    archiveFound = true;

    // Clear any previous sequence data
    acBgm_Root.ClearSeqDatas();
    acMelodies_Root.ClearSeqDatas();

    // Find all leaves of the tree
    static std::vector<AudioCategoryLeaf*> allAudioCatLeaves;
    if (allAudioCatLeaves.empty()) {
        for (auto* root : { &acBgm_Root, &acMelodies_Root }) {
            auto newLeaves = root->GetAllLeaves();
            allAudioCatLeaves.insert(allAudioCatLeaves.begin(), newLeaves.begin(), newLeaves.end());
        }
    }

    // Add original sequences
    if (!Settings::CustomMusicOnly) {
        const auto audioCatAddSeq = [&sar](AudioCategory& audioCat, u16 fileIdx) {
            audioCat.AddNewSeqData(SequenceData(sar.GetRawFilePtr(fileIdx), sar.GetOriginalBank(fileIdx),
                                                sar.GetOriginalChFlags(fileIdx)));
        };
        const auto fillNodeWithOriginals = [&](AudioCategory& node) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&node)) {
                    audioCatAddSeq(node, leaf->FileRep);
                }
            }
        };
        // BGM
        if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_MIXED)) {
            fillNodeWithOriginals(acBgm_Root);
        } else if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_GROUPED)) {
            fillNodeWithOriginals(acBgm_AreaThemes);
            fillNodeWithOriginals(acBgm_EventMusic);
            fillNodeWithOriginals(acBgm_BattleThemes);
        } else if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_OWN)) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&acBgm_Root)) {
                    audioCatAddSeq(*leaf, leaf->FileRep);
                }
            }
        }
        // Melodies
        if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_MIXED)) {
            fillNodeWithOriginals(acMelodies_Root);
        } else if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_GROUPED)) {
            fillNodeWithOriginals(acMelodies_Fanfares);
            fillNodeWithOriginals(acMelodies_OcarinaSongs);
        } else if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_OWN)) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&acMelodies_Root)) {
                    audioCatAddSeq(*leaf, leaf->FileRep);
                }
            }
        }
    }

    // Add external sequences
    if (Settings::CustomMusic) {
        acBgm_Root.AddExternalSeqDatas(sdmcArchive);
        acMelodies_Root.AddExternalSeqDatas(sdmcArchive);
    }

    // Shuffle
    auto leavesCopy = allAudioCatLeaves;
    Shuffle(leavesCopy);
    for (auto leaf : leavesCopy) {
        auto fileId  = leaf->FileRep;
        auto seqData = leaf->GetAndRemoveRandomSeqData();
        if (!seqData.GetData(sdmcArchive).empty()) {
            sar.ReplaceSeq(sdmcArchive, fileId, seqData);
        }
    }

    // Create output dirs
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles"), FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId).c_str()),
                           FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/romfs").c_str()),
                           FS_ATTRIBUTE_DIRECTORY);
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/romfs/sound").c_str()),
                           FS_ATTRIBUTE_DIRECTORY);

    // Create new archive
    sar.Write(sdmcArchive, newBcsarPath);

    FSUSER_CloseArchive(sdmcArchive);
    return SARSHUFFLE_SUCCESS;
}
} // namespace Music
