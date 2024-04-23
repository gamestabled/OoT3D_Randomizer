#include <3ds.h>
#include <cstdlib>
#include <filesystem>
#include <functional>

#include "music.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "sound_archive.hpp"
#include "sequence_data.hpp"
#include "cmeta_interpreter.hpp"

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
static MusicCategoryLeaf mcBgm_HyruleField("Hyrule Field", 9);
static MusicCategoryLeaf mcBgm_KakarikoAdult("Kakariko Adult", 11);
static MusicCategoryLeaf mcBgm_Market("Market", 15);
static MusicCategoryLeaf mcBgm_KakarikoChild("Kakariko Child", 25);
static MusicCategoryLeaf mcBgm_LonLonRanch("Lon Lon Ranch", 33);
static MusicCategoryLeaf mcBgm_GoronCity("Goron City", 34);
static MusicCategoryLeaf mcBgm_KokiriForest("Kokiri Forest", 45);
static MusicCategoryLeaf mcBgm_LostWoods("Lost Woods", 47);
static MusicCategoryLeaf mcBgm_ZorasDomain("Zora's Domain", 65);
static MusicCategoryLeaf mcBgm_GerudoValley("Gerudo Valley", 79);
// BGM: Interiors
static MusicCategoryLeaf mcBgm_HouseTheme("House Theme", 17);
static MusicCategoryLeaf mcBgm_FairyFountain("Fairy Fountain", 26);
static MusicCategoryLeaf mcBgm_TempleTime("Temple of Time", 43);
static MusicCategoryLeaf mcBgm_Windmill("Windmill", 61);
static MusicCategoryLeaf mcBgm_ShopTheme("Shop Theme", 70);
static MusicCategoryLeaf mcBgm_Drugstore("Drugstore", 80);
// BGM: Dungeons
static MusicCategoryLeaf mcBgm_MiscDungeon("Misc Dungeon", 10);
static MusicCategoryLeaf mcBgm_InsideDekuTree("Deku Tree", 14);
static MusicCategoryLeaf mcBgm_JabuJabu("Jabu Jabu", 24);
static MusicCategoryLeaf mcBgm_FireTemple("Fire Temple", 28);
static MusicCategoryLeaf mcBgm_ForestTemple("Forest Temple", 30);
static MusicCategoryLeaf mcBgm_GanonsTower("Ganon's Tower", 32);
static MusicCategoryLeaf mcBgm_SpiritTemple("Spirit Temple", 48);
static MusicCategoryLeaf mcBgm_IceCavern("Ice Cavern", 73);
static MusicCategoryLeaf mcBgm_ShadowTemple("Shadow Temple", 76);
static MusicCategoryLeaf mcBgm_WaterTemple("Water Temple", 77);
static MusicCategoryLeaf mcBgm_GanonsCastle("Ganon's Castle", 83);
// BGM: Area Themes
static MusicCategoryNode mcBgm_Overworld("Overworld", {
                                                          &mcBgm_HyruleField,
                                                          &mcBgm_KakarikoAdult,
                                                          &mcBgm_Market,
                                                          &mcBgm_KakarikoChild,
                                                          &mcBgm_LonLonRanch,
                                                          &mcBgm_GoronCity,
                                                          &mcBgm_KokiriForest,
                                                          &mcBgm_LostWoods,
                                                          &mcBgm_ZorasDomain,
                                                          &mcBgm_GerudoValley,
                                                      });
static MusicCategoryNode mcBgm_Interiors("Interiors", {
                                                          &mcBgm_HouseTheme,
                                                          &mcBgm_FairyFountain,
                                                          &mcBgm_TempleTime,
                                                          &mcBgm_Windmill,
                                                          &mcBgm_ShopTheme,
                                                          &mcBgm_Drugstore,
                                                      });
static MusicCategoryNode mcBgm_Dungeons("Dungeons", {
                                                        &mcBgm_MiscDungeon,
                                                        &mcBgm_InsideDekuTree,
                                                        &mcBgm_JabuJabu,
                                                        &mcBgm_FireTemple,
                                                        &mcBgm_ForestTemple,
                                                        &mcBgm_GanonsTower,
                                                        &mcBgm_SpiritTemple,
                                                        &mcBgm_IceCavern,
                                                        &mcBgm_ShadowTemple,
                                                        &mcBgm_WaterTemple,
                                                        &mcBgm_GanonsCastle,
                                                    });
// BGM: Event Music
static MusicCategoryLeaf mcBgm_TitleScreen("Title Screen", 16);
static MusicCategoryLeaf mcBgm_ZeldasTheme("Zelda's Theme", 27);
static MusicCategoryLeaf mcBgm_CastleCourtyard("Castle Courtyard", 31);
static MusicCategoryLeaf mcBgm_HorseRace("Horse Race", 49);
static MusicCategoryLeaf mcBgm_IngosTheme("Ingo's Theme", 51);
static MusicCategoryLeaf mcBgm_NaviIntro("Navi Intro", 59);
static MusicCategoryLeaf mcBgm_DekuTreeStorytime("Deku Tree Storytime", 60);
static MusicCategoryLeaf mcBgm_MinigameTheme01("Minigame Theme 1", 63);
static MusicCategoryLeaf mcBgm_SheiksTheme("Sheik's Theme", 64);
static MusicCategoryLeaf mcBgm_AdultLink("Adult Link", 67);
static MusicCategoryLeaf mcBgm_GanondorfsTheme("Ganondorf's Theme", 69);
static MusicCategoryLeaf mcBgm_GoddessTheme("Goddess Theme", 71);
static MusicCategoryLeaf mcBgm_FileSelect("File Select", 72);
static MusicCategoryLeaf mcBgm_OwlsTheme("Owl's Theme", 75);
static MusicCategoryLeaf mcBgm_KotakeKoume("Kotake & Koume", 81);
static MusicCategoryLeaf mcBgm_TowerEscape("Tower Escape", 82);
static MusicCategoryLeaf mcBgm_MinigameTheme02("Minigame Theme 2", 92);
// BGM: Boss Themes
static MusicCategoryLeaf mcBgm_Boss00("Boss Theme 1", 13);
static MusicCategoryLeaf mcBgm_Boss01("Boss Theme 2", 91);
// BGM: Battle Themes
static MusicCategoryLeaf mcBgm_Enemy("Enemy Theme", 12);
static MusicCategoryLeaf mcBgm_MiniBoss("Mini Boss", 41);
static MusicCategoryNode mcBgm_BossThemes("Boss Themes", {
                                                             &mcBgm_Boss00,
                                                             &mcBgm_Boss01,
                                                         });
static MusicCategoryLeaf mcBgm_GanondorfBattle("Ganondorf Battle", 84);
static MusicCategoryLeaf mcBgm_GanonBattle("Ganon Battle", 85);
// BGM: Root
static MusicCategoryNode mcBgm_AreaThemes("Area Themes", { &mcBgm_Overworld, &mcBgm_Interiors, &mcBgm_Dungeons });
static MusicCategoryNode mcBgm_EventMusic("Event Music", {
                                                             &mcBgm_TitleScreen,
                                                             &mcBgm_ZeldasTheme,
                                                             &mcBgm_CastleCourtyard,
                                                             &mcBgm_HorseRace,
                                                             &mcBgm_IngosTheme,
                                                             &mcBgm_NaviIntro,
                                                             &mcBgm_DekuTreeStorytime,
                                                             &mcBgm_MinigameTheme01,
                                                             &mcBgm_SheiksTheme,
                                                             &mcBgm_AdultLink,
                                                             &mcBgm_GanondorfsTheme,
                                                             &mcBgm_GoddessTheme,
                                                             &mcBgm_FileSelect,
                                                             &mcBgm_OwlsTheme,
                                                             &mcBgm_KotakeKoume,
                                                             &mcBgm_TowerEscape,
                                                             &mcBgm_MinigameTheme02,
                                                         });
static MusicCategoryNode mcBgm_BattleThemes("Battle Themes", {
                                                                 &mcBgm_Enemy,
                                                                 &mcBgm_MiniBoss,
                                                                 &mcBgm_BossThemes,
                                                                 &mcBgm_GanondorfBattle,
                                                                 &mcBgm_GanonBattle,
                                                             });
// BGM
static MusicCategoryNode mcBgm_Root("Background Music", { &mcBgm_AreaThemes, &mcBgm_EventMusic, &mcBgm_BattleThemes });

// Melodies: Item Jingles
static MusicCategoryLeaf mcMelodies_ItemGet("Item Get", 20);
static MusicCategoryLeaf mcMelodies_HeartContainerGet("Heart Container Get", 22);
static MusicCategoryLeaf mcMelodies_TreasureChestOpening("Treasure Chest Opening", 29);
static MusicCategoryLeaf mcMelodies_SpiritualStoneGet("Spiritual Stone Get", 35);
static MusicCategoryLeaf mcMelodies_SmallItemGet("Small Item Get", 42);
static MusicCategoryLeaf mcMelodies_SongLearned("Song Learned", 46);
static MusicCategoryLeaf mcMelodies_MedallionGet("Medallion Get", 52);
// Melodies: Misc Fanfares
static MusicCategoryLeaf mcMelodies_GameOver("Game Over", 18);
static MusicCategoryLeaf mcMelodies_BossClear("Boss Clear", 19);
static MusicCategoryLeaf mcMelodies_GanonAppears("Ganon Appears", 21);
static MusicCategoryLeaf mcMelodies_EventClear("Event Clear", 44);
static MusicCategoryLeaf mcMelodies_HorseGoal("Horse Goal", 50);
static MusicCategoryLeaf mcMelodies_Appearance("Appearance", 66);
static MusicCategoryLeaf mcMelodies_MasterSword("Master Sword", 68);
static MusicCategoryLeaf mcMelodies_DoorTimeOpened("Door of Time Opened", 74);
static MusicCategoryLeaf mcMelodies_RainbowBridge("Rainbow Bridge", 78);
// Melodies: Fanfares
static MusicCategoryNode mcMelodies_ItemJingles("Item Jingles", {
                                                                    &mcMelodies_ItemGet,
                                                                    &mcMelodies_HeartContainerGet,
                                                                    &mcMelodies_TreasureChestOpening,
                                                                    &mcMelodies_SpiritualStoneGet,
                                                                    &mcMelodies_SmallItemGet,
                                                                    &mcMelodies_SongLearned,
                                                                    &mcMelodies_MedallionGet,
                                                                });
static MusicCategoryNode mcMelodies_MiscFanfares("Misc Fanfares", {
                                                                      &mcMelodies_GameOver,
                                                                      &mcMelodies_BossClear,
                                                                      &mcMelodies_GanonAppears,
                                                                      &mcMelodies_EventClear,
                                                                      &mcMelodies_HorseGoal,
                                                                      &mcMelodies_Appearance,
                                                                      &mcMelodies_MasterSword,
                                                                      &mcMelodies_DoorTimeOpened,
                                                                      &mcMelodies_RainbowBridge,
                                                                  });
// Melodies: Child Songs
static MusicCategoryLeaf mcMelodies_SariasSong("Saria's Song", 53);
static MusicCategoryLeaf mcMelodies_EponasSong("Epona's Song", 54);
static MusicCategoryLeaf mcMelodies_ZeldasLullaby("Zelda's Lullaby", 55);
// static MusicCategoryLeaf mcMelodies_SunsSong("Sun's Song", 56); // Still unshuffled because of bugs
static MusicCategoryLeaf mcMelodies_SongTime("Song of Time", 57);
static MusicCategoryLeaf mcMelodies_SongStorms("Song of Storms", 58);
// Melodies: Warp Songs
static MusicCategoryLeaf mcMelodies_PreludeLight("Prelude of Light", 23);
static MusicCategoryLeaf mcMelodies_BoleroFire("Bolero of Fire", 36);
static MusicCategoryLeaf mcMelodies_MinuetForest("Minuet of Forest", 37);
static MusicCategoryLeaf mcMelodies_SerenadeWater("Serenade of Water", 38);
static MusicCategoryLeaf mcMelodies_RequiemSpirit("Requiem of Spirit", 39);
static MusicCategoryLeaf mcMelodies_NoctureShadow("Nocture of Shadow", 40);
// Melodies: Ocarina Songs
static MusicCategoryNode mcMelodies_ChildSongs("Child Songs", {
                                                                  &mcMelodies_SariasSong,
                                                                  &mcMelodies_EponasSong,
                                                                  &mcMelodies_ZeldasLullaby,
                                                                  //&mcMelodies_SunsSong,
                                                                  &mcMelodies_SongTime,
                                                                  &mcMelodies_SongStorms,
                                                              });
static MusicCategoryNode mcMelodies_WarpSongs("Warp Songs", {
                                                                &mcMelodies_PreludeLight,
                                                                &mcMelodies_BoleroFire,
                                                                &mcMelodies_MinuetForest,
                                                                &mcMelodies_SerenadeWater,
                                                                &mcMelodies_RequiemSpirit,
                                                                &mcMelodies_NoctureShadow,
                                                            });
// Melodies: Root
static MusicCategoryNode mcMelodies_Fanfares("Fanfares", { &mcMelodies_ItemJingles, &mcMelodies_MiscFanfares });
static MusicCategoryNode mcMelodies_OcarinaSongs("Ocarina Songs", { &mcMelodies_ChildSongs, &mcMelodies_WarpSongs });
// Melodies
static MusicCategoryNode mcMelodies_Root("Melodies", { &mcMelodies_Fanfares, &mcMelodies_OcarinaSongs });

bool archiveFound     = false;
bool musicDirsCreated = false;

void CreateMusicDirectories(FS_Archive sdmcArchive) {
    if (R_FAILED(FSUSER_OpenDirectory(nullptr, sdmcArchive, fsMakePath(PATH_ASCII, CustomMusicRootPath.c_str())))) {
        std::vector<std::string> dirs;

        dirs.push_back("/OoT3DR/");
        dirs.push_back(CustomMusicRootPath);

        auto bgmDirs = mcBgm_Root.GetDirectories();
        dirs.insert(dirs.end(), bgmDirs.begin(), bgmDirs.end());

        auto melodyDirs = mcMelodies_Root.GetDirectories();
        dirs.insert(dirs.end(), melodyDirs.begin(), melodyDirs.end());

        const auto printInfo = [&](int progress) {
            consoleClear();
            printf("\x1b[10;10HCreating Music Directories");
            printf("\x1b[11;10HProgress: %d/%d", progress, dirs.size());

            printf("\x1b[13;10HOnly needs to be done once.");
        };

        printInfo(0);
        for (size_t i = 0; i < dirs.size(); i++) {
            FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, dirs[i].c_str()), FS_ATTRIBUTE_DIRECTORY);
            printInfo(i + 1);
        }
    }
    musicDirsCreated = true;
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
    mcBgm_Root.ClearSeqDatas();
    mcMelodies_Root.ClearSeqDatas();

    // Find all leaves of the tree
    static std::vector<MusicCategoryLeaf*> allAudioCatLeaves;
    if (allAudioCatLeaves.empty()) {
        for (auto* root : { &mcBgm_Root, &mcMelodies_Root }) {
            auto newLeaves = root->GetAllLeaves();
            allAudioCatLeaves.insert(allAudioCatLeaves.begin(), newLeaves.begin(), newLeaves.end());
        }
    }

    // Add original sequences
    if (!Settings::CustomMusicOnly) {
        const auto musicNodeAddSeq = [&sar](MusicCategoryNode& audioCat, u16 fileIdx) {
            u32 origBank = sar.GetOriginalBank(fileIdx);
            audioCat.AddNewSeqData(SequenceData(sar.GetRawFilePtr(fileIdx), { origBank, origBank, origBank, origBank },
                                                sar.GetOriginalChFlags(fileIdx), sar.GetOriginalVolume(fileIdx)));
        };
        const auto fillNodeWithOriginals = [&](MusicCategoryNode& node) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&node)) {
                    musicNodeAddSeq(node, leaf->FileRep);
                }
            }
        };
        // BGM
        if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_MIXED)) {
            fillNodeWithOriginals(mcBgm_Root);
        } else if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_GROUPED)) {
            fillNodeWithOriginals(mcBgm_AreaThemes);
            fillNodeWithOriginals(mcBgm_EventMusic);
            fillNodeWithOriginals(mcBgm_BattleThemes);
        } else if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_OWN)) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&mcBgm_Root)) {
                    musicNodeAddSeq(*leaf, leaf->FileRep);
                }
            }
        }
        // Melodies
        if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_MIXED)) {
            fillNodeWithOriginals(mcMelodies_Root);
        } else if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_GROUPED)) {
            fillNodeWithOriginals(mcMelodies_Fanfares);
            fillNodeWithOriginals(mcMelodies_OcarinaSongs);
        } else if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_OWN)) {
            for (auto leaf : allAudioCatLeaves) {
                if (leaf->HasAncestor(&mcMelodies_Root)) {
                    musicNodeAddSeq(*leaf, leaf->FileRep);
                }
            }
        }
    }

    // Add external sequences
    if (Settings::CustomMusic) {
        // This adds the categorized sequences, inside the node folders
        mcBgm_Root.AddExternalSeqDatas(sdmcArchive);
        mcMelodies_Root.AddExternalSeqDatas(sdmcArchive);

        // This adds the sequences uncategorized in the Custom Music folder, but not in any node
        std::function<void(std::string)> addUncategorizedSeqDatas = [&](std::string folderPath) {
            namespace fs = std::filesystem;
            for (const auto& bcseq : fs::directory_iterator(folderPath)) {
                if (bcseq.is_directory()) {
                    // Exclamation mark indicates a tree node
                    if (bcseq.path().stem().string().front() == '!') {
                        continue;
                    } else {
                        addUncategorizedSeqDatas(bcseq.path().string());
                    }
                } else if (bcseq.is_regular_file() && bcseq.path().extension().string() == bcseqExtension) {
                    for (const auto& cmeta : fs::directory_iterator(folderPath)) {
                        if (cmeta.is_regular_file() && cmeta.path().stem().string() == bcseq.path().stem().string() &&
                            cmeta.path().extension().string() == cmetaExtension) {

                            CMetaInterpreter ci(cmeta.path().string());

                            MusicCategoryNode* n = nullptr;

                            n = mcBgm_Root.GetNodeByName(ci.GetCategory());
                            if (n != nullptr) {
                                if (Settings::ShuffleBGM.Is(SHUFFLEMUSIC_MIXED)) {
                                    mcBgm_Root.AddNewSeqData(SequenceData(bcseq.path().string(), ci));
                                } else {
                                    n->AddNewSeqData(SequenceData(bcseq.path().string(), ci));
                                }
                                break;
                            }
                            n = mcMelodies_Root.GetNodeByName(ci.GetCategory());
                            if (n != nullptr) {
                                if (Settings::ShuffleMelodies.Is(SHUFFLEMUSIC_MIXED)) {
                                    mcMelodies_Root.AddNewSeqData(SequenceData(bcseq.path().string(), ci));
                                } else {
                                    n->AddNewSeqData(SequenceData(bcseq.path().string(), ci));
                                }
                                break;
                            }
                            break;
                        }
                    }
                }
            }
        };
        addUncategorizedSeqDatas(CustomMusicRootPath);
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
