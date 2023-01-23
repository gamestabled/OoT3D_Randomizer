#pragma once

#include <3ds.h>

// Code ported from Gota7's Citric Composer

class ReferenceTypes {
  public:
    // Base types.
    static const u16 Tables     = 0x100;
    static const u16 Parameters = 0x200;
    static const u16 Codecs     = 0x300;
    static const u16 General    = 0x1F00;

    static const u16 SAR_Blocks       = 0x2000;
    static const u16 SAR_InfoSections = 0x2100;
    static const u16 SAR_ItemInfos    = 0x2200;
    static const u16 SAR_Parameters   = 0x2300;
    static const u16 SAR_General      = 0x2400;

    static const u16 STRM_Blocks    = 0x4000;
    static const u16 STRM_ItemInfos = 0x4100;

    static const u16 WSF_Blocks    = 0x4800;
    static const u16 WSF_ItemInfos = 0x4900;

    static const u16 SEQ_Blocks    = 0x5000;
    static const u16 SEQ_ItemInfos = 0x5100;

    static const u16 BNK_Blocks     = 0x5800;
    static const u16 BNK_Items      = 0x5900;
    static const u16 BNK_ItemTables = 0x6000;

    static const u16 WAR_Blocks = 0x6800;

    static const u16 WAV_Blocks    = 0x7000;
    static const u16 WAV_ItemInfos = 0x7100;

    static const u16 GRP_Blocks    = 0x7800;
    static const u16 GRP_ItemInfos = 0x7900;

    static const u16 ASF_Blocks = 0x8000;
    static const u16 ASF_Items  = 0x8100;

    // Common sound.
    static const u16 Table_Embedding         = Tables;
    static const u16 Table_Reference         = Tables + 1;
    static const u16 Table_ReferenceWithSize = Tables + 2;

    static const u16 Param_Sound3D      = Parameters;
    static const u16 Param_Sends        = Parameters + 1;
    static const u16 Param_Envelope     = Parameters + 2;
    static const u16 Param_AdshrEnvelop = Parameters + 3;

    static const u16 Codec_DspAdpcmInfo = Codecs;
    static const u16 Codec_ImaAdpcmInfo = Codecs + 1;

    static const u16 General_ByteStream = General;
    static const u16 String             = General + 1;

    // Sound archive file.
    static const u16 SAR_Block_String = SAR_Blocks;
    static const u16 SAR_Block_Info   = SAR_Blocks + 1;
    static const u16 SAR_Block_File   = SAR_Blocks + 2;

    static const u16 SAR_Section_SoundInfo       = SAR_InfoSections;
    static const u16 SAR_Section_BankInfo        = SAR_InfoSections + 1;
    static const u16 SAR_Section_PlayerInfo      = SAR_InfoSections + 2;
    static const u16 SAR_Section_WaveArchiveInfo = SAR_InfoSections + 3;
    static const u16 SAR_Section_SoundGroupInfo  = SAR_InfoSections + 4;
    static const u16 SAR_Section_GroupInfo       = SAR_InfoSections + 5;
    static const u16 SAR_Section_FileInfo        = SAR_InfoSections + 6;

    static const u16 SAR_Info_Sound                = SAR_ItemInfos;
    static const u16 SAR_Info_StreamSound          = SAR_ItemInfos + 1;
    static const u16 SAR_Info_WaveSound            = SAR_ItemInfos + 2;
    static const u16 SAR_Info_SequenceSound        = SAR_ItemInfos + 3;
    static const u16 SAR_Info_SoundGroup           = SAR_ItemInfos + 4;
    static const u16 SAR_Info_WaveSoundGroup       = SAR_ItemInfos + 5;
    static const u16 SAR_Info_Bank                 = SAR_ItemInfos + 6;
    static const u16 SAR_Info_WaveArchive          = SAR_ItemInfos + 7;
    static const u16 SAR_Info_Group                = SAR_ItemInfos + 8;
    static const u16 SAR_Info_Player               = SAR_ItemInfos + 9;
    static const u16 SAR_Info_File                 = SAR_ItemInfos + 10;
    static const u16 SAR_Info_Project              = SAR_ItemInfos + 11;
    static const u16 SAR_Info_InternalFile         = SAR_ItemInfos + 12;
    static const u16 SAR_Info_ExternalFile         = SAR_ItemInfos + 13;
    static const u16 SAR_Info_StreamSoundTrack     = SAR_ItemInfos + 14;
    static const u16 SAR_Info_Send                 = SAR_ItemInfos + 15;
    static const u16 SAR_Info_StreamSoundExtension = SAR_ItemInfos + 16;

    static const u16 SAR_StringTable  = SAR_General;
    static const u16 SAR_PatriciaTree = SAR_General + 1;

    // Stream file.
    static const u16 STRM_Block_Info         = STRM_Blocks;
    static const u16 STRM_Block_Seek         = STRM_Blocks + 1;
    static const u16 STRM_Block_Data         = STRM_Blocks + 2;
    static const u16 STRM_Block_Region       = STRM_Blocks + 3;
    static const u16 STRM_Block_PrefetchData = STRM_Blocks + 4;

    static const u16 STRM_Info_StreamSound = STRM_ItemInfos;
    static const u16 STRM_Info_Track       = STRM_ItemInfos + 1;
    static const u16 STRM_Info_Channel     = STRM_ItemInfos + 2;

    // Wave sound file.
    static const u16 WSF_Block_Info = WSF_Blocks;

    static const u16 WSF_WaveSoundMetaData = WSF_ItemInfos;
    static const u16 WSF_WaveSoundInfo     = WSF_ItemInfos + 1;
    static const u16 WSF_NoteInfo          = WSF_ItemInfos + 2;
    static const u16 WSF_TrackInfo         = WSF_ItemInfos + 3;
    static const u16 WSF_NoteEvent         = WSF_ItemInfos + 4;

    // Wave archive file.
    static const u16 WAR_Block_Info = WAR_Blocks;
    static const u16 WAR_Block_File = WAR_Blocks + 1;

    // Wave file.
    static const u16 WAV_Block_Info = WAV_Blocks;
    static const u16 WAV_Block_Data = WAV_Blocks + 1;

    static const u16 WAV_ChannelInfo = WAV_ItemInfos;

    // Sequence file.
    static const u16 SEQ_Block_Data  = SEQ_Blocks;
    static const u16 SEQ_Block_Label = SEQ_Blocks + 1;

    static const u16 SEQ_LabelInfo = SEQ_ItemInfos;

    // Bank file.
    static const u16 BNK_Block_Info = BNK_Blocks;

    static const u16 BNK_Info_Instrument     = BNK_Items;
    static const u16 BNK_Info_KeyRegion      = BNK_Items + 1;
    static const u16 BNK_Info_VelocityRegion = BNK_Items + 2;
    static const u16 BNK_Info_Null           = BNK_Items + 3;

    static const u16 BNK_RefTable_Direct = BNK_ItemTables;
    static const u16 BNK_RefTable_Index  = BNK_ItemTables + 1;
    static const u16 BNK_RefTable_Range  = BNK_ItemTables + 2;

    // Group file.
    static const u16 GRP_Block_Info = GRP_Blocks;
    static const u16 GRP_Block_File = GRP_Blocks + 1;
    static const u16 GRP_Block_Infx = GRP_Blocks + 2;

    static const u16 GRP_Info_Item = GRP_ItemInfos;
    static const u16 GRP_Infx_Item = GRP_ItemInfos + 1;

    // Animation sound file.
    static const u16 ASF_Block_Data = ASF_Blocks;
    static const u16 ASF_EventInfo  = ASF_Items;
};
