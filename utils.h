#pragma once
#define X64
namespace uwp
{
  namespace internal
  {
    using u64 = unsigned long long;
    using i64 = long long;
    using u32 = unsigned long;
    using i32 = long;
    using u16 = unsigned short;
    using i16 = short;
    using u8 = unsigned char;
    using i8 = char;

    struct list_entry_t {
      const char* flink;
      const char* blink;
    };

    struct unicode_string_t {
      u16 len;
      u16 max_len;
      wchar_t* buffer;
    };

    struct peb_ldr_data_t {
      unsigned long len;
      u8 initialized;
      void* ss_handle;
      list_entry_t in_load_order_module_list;
      list_entry_t in_memory_order_module_list;
      list_entry_t in_initialization_order_module_list;
      void* entry_in_progress;
      u8 shutdown_in_progress;
      void* shutdown_thread_id;
    };
    union _LARGE_INTEGER
    {
      struct
      {
        u32 LowPart;                                                      //0x0
        i32 HighPart;                                                      //0x4
      };
      struct
      {
        u32 LowPart;                                                      //0x0
        i32 HighPart;                                                      //0x4
      } u;                                                                    //0x0
      i64 QuadPart;                                                      //0x0
    };
    //0x8 bytes (sizeof)
    union _ULARGE_INTEGER
    {
      struct
      {
        u32 LowPart;                                                      //0x0
        u32 HighPart;                                                     //0x4
      };
      struct
      {
        u32 LowPart;                                                      //0x0
        u32 HighPart;                                                     //0x4
      } u;                                                                    //0x0
      u64 QuadPart;                                                     //0x0
    };

    //0x10 bytes (sizeof)
    struct string_t
    {
      u16 Length;                                                          //0x0
      u16 MaximumLength;                                                   //0x2
#ifdef X64
      u64 Buffer;
#else
      u32 Buffer;
#endif//0x8
    };
    struct ldr_data_table_entry_t {
      list_entry_t in_load_order_links;
      list_entry_t in_memory_order_links;
      list_entry_t in_init_order_links;
      void* dll_base;
      void* entry_point;
      union {
        unsigned long size_of_image;
        void* _dummy;
      };
      unicode_string_t full_dll_name;
      unicode_string_t base_dll_name;

      __forceinline const ldr_data_table_entry_t*
        load_order_next ( ) const noexcept
      {
        return reinterpret_cast< const ldr_data_table_entry_t* >(
          in_load_order_links.flink );
      }
    };
    struct peb_t
    {
      u8 InheritedAddressSpace;                                            //0x0
      u8 ReadImageFileExecOptions;                                         //0x1
      u8 BeingDebugged;                                                    //0x2
      union
      {
        u8 BitField;                                                     //0x3
        struct
        {
          u8 ImageUsesLargePages : 1;                                    //0x3
          u8 IsProtectedProcess : 1;                                     //0x3
          u8 IsImageDynamicallyRelocated : 1;                            //0x3
          u8 SkipPatchingUser32Forwarders : 1;                           //0x3
          u8 IsPackagedProcess : 1;                                      //0x3
          u8 IsAppContainer : 1;                                         //0x3
          u8 IsProtectedProcessLight : 1;                                //0x3
          u8 IsLongPathAwareProcess : 1;                                 //0x3
        };
      };
      u8 Padding0 [ 4 ];                                                      //0x4
      u64 Mutant;                                                       //0x8
      u64 ImageBaseAddress;                                             //0x10
      peb_ldr_data_t* ldr;                                                          //0x18
      u64 ProcessParameters;                                            //0x20
      u64 SubSystemData;                                                //0x28
      u64 ProcessHeap;                                                  //0x30
      u64 FastPebLock;                                                  //0x38
      u64 AtlThunkSListPtr;                                             //0x40
      u64 IFEOKey;                                                      //0x48
      union
      {
        u32 CrossProcessFlags;                                            //0x50
        struct
        {
          u32 ProcessInJob : 1;                                           //0x50
          u32 ProcessInitializing : 1;                                    //0x50
          u32 ProcessUsingVEH : 1;                                        //0x50
          u32 ProcessUsingVCH : 1;                                        //0x50
          u32 ProcessUsingFTH : 1;                                        //0x50
          u32 ProcessPreviouslyThrottled : 1;                             //0x50
          u32 ProcessCurrentlyThrottled : 1;                              //0x50
          u32 ProcessImagesHotPatched : 1;                                //0x50
          u32 ReservedBits0 : 24;                                         //0x50
        };
      };
      u8 Padding1 [ 4 ];                                                      //0x54
      union
      {
        u64 KernelCallbackTable;                                      //0x58
        u64 UserSharedInfoPtr;                                        //0x58
      };
      u32 SystemReserved;                                                   //0x60
      u32 AtlThunkSListPtr32;                                               //0x64
      u64 ApiSetMap;                                                    //0x68
      u32 TlsExpansionCounter;                                              //0x70
      u8 Padding2 [ 4 ];                                                      //0x74
      u64 TlsBitmap;                                                    //0x78
      u32 TlsBitmapBits [ 2 ];                                                 //0x80
      u64 ReadOnlySharedMemoryBase;                                     //0x88
      u64 SharedData;                                                   //0x90
      u64 ReadOnlyStaticServerData;                                     //0x98
      u64 AnsiCodePageData;                                             //0xa0
      u64 OemCodePageData;                                              //0xa8
      u64 UnicodeCaseTableData;                                         //0xb0
      u32 NumberOfProcessors;                                               //0xb8
      u32 NtGlobalFlag;                                                     //0xbc
      union _LARGE_INTEGER CriticalSectionTimeout;                            //0xc0
      u64 HeapSegmentReserve;                                           //0xc8
      u64 HeapSegmentCommit;                                            //0xd0
      u64 HeapDeCommitTotalFreeThreshold;                               //0xd8
      u64 HeapDeCommitFreeBlockThreshold;                               //0xe0
      u32 NumberOfHeaps;                                                    //0xe8
      u32 MaximumNumberOfHeaps;                                             //0xec
      u64 ProcessHeaps;                                                 //0xf0
      u64 GdiSharedHandleTable;                                         //0xf8
      u64 ProcessStarterHelper;                                         //0x100
      u32 GdiDCAttributeList;                                               //0x108
      u8 Padding3 [ 4 ];                                                      //0x10c
      u64 LoaderLock;                                                   //0x110
      u32 OSMajorVersion;                                                   //0x118
      u32 OSMinorVersion;                                                   //0x11c
      u16 OSBuildNumber;                                                   //0x120
      u16 OSCSDVersion;                                                    //0x122
      u32 OSPlatformId;                                                     //0x124
      u32 ImageSubsystem;                                                   //0x128
      u32 ImageSubsystemMajorVersion;                                       //0x12c
      u32 ImageSubsystemMinorVersion;                                       //0x130
      u8 Padding4 [ 4 ];                                                      //0x134
      u64 ActiveProcessAffinityMask;                                    //0x138
      u32 GdiHandleBuffer [ 60 ];                                              //0x140
      u64 PostProcessInitRoutine;                                       //0x230
      u64 TlsExpansionBitmap;                                           //0x238
      u32 TlsExpansionBitmapBits [ 32 ];                                       //0x240
      u32 SessionId;                                                        //0x2c0
      u8 Padding5 [ 4 ];                                                      //0x2c4
      union _ULARGE_INTEGER AppCompatFlags;                                   //0x2c8
      union _ULARGE_INTEGER AppCompatFlagsUser;                               //0x2d0
      u64 pShimData;                                                    //0x2d8
      u64 AppCompatInfo;                                                //0x2e0
      struct string_t CSDVersion;                                            //0x2e8
      u64 ActivationContextData;                                        //0x2f8
      u64 ProcessAssemblyStorageMap;                                    //0x300
      u64 SystemDefaultActivationContextData;                           //0x308
      u64 SystemAssemblyStorageMap;                                     //0x310
      u64 MinimumStackCommit;                                           //0x318
      u64 SparePointers [ 2 ];                                             //0x320
      u64 PatchLoaderData;                                              //0x330
      u64 ChpeV2ProcessInfo;                                            //0x338
      u32 AppModelFeatureState;                                             //0x340
      u32 Spareu32s [ 2 ];                                                   //0x344
      u16 ActiveCodePage;                                                  //0x34c
      u16 OemCodePage;                                                     //0x34e
      u16 UseCaseMapping;                                                  //0x350
      u16 UnusedNlsField;                                                  //0x352
      u64 WerRegistrationData;                                          //0x358
      u64 WerShipAssertPtr;                                             //0x360
      u64 EcCodeBitMap;                                                 //0x368
      u64 pImageHeaderHash;                                             //0x370
      union
      {
        u32 TracingFlags;                                                 //0x378
        struct
        {
          u32 HeapTracingEnabled : 1;                                     //0x378
          u32 CritSecTracingEnabled : 1;                                  //0x378
          u32 LibLoaderTracingEnabled : 1;                                //0x378
          u32 SpareTracingBits : 29;                                      //0x378
        };
      };
      u8 Padding6 [ 4 ];                                                      //0x37c
      u64 CsrServerReadOnlySharedMemoryBase;                            //0x380
      u64 TppWorkerpListLock;                                           //0x388
      list_entry_t TppWorkerpList;                                     //0x390
      u64 WaitOnAddressHashTable [ 128 ];                                  //0x3a0
      u64 TelemetryCoverageHeader;                                      //0x7a0
      u32 CloudFileFlags;                                                   //0x7a8
      u32 CloudFileDiagFlags;                                               //0x7ac
      char PlaceholderCompatibilityMode;                                      //0x7b0
      char PlaceholderCompatibilityModeReserved [ 7 ];                           //0x7b1
      u64 LeapSecondData;                                               //0x7b8
      union
      {
        u32 LeapSecondFlags;                                              //0x7c0
        struct
        {
          u32 SixtySecondEnabled : 1;                                     //0x7c0
          u32 Reserved : 31;                                              //0x7c0
        };
      };
      u32 NtGlobalFlag2;                                                    //0x7c4
      u64 ExtendedFeatureDisableMask;                                   //0x7c8
    };
  };

  const internal::peb_t* get_peb ( )
  {
#ifdef X64
    return reinterpret_cast< const internal::peb_t* >( __readgsqword ( 0x60 ) );
#else
    return reinterpret_cast< const internal::peb_t* >( __readfsdword ( 0x30 ) );
#endif
  }

  void* get_module_base(const wchar_t* module_name)
  {
    auto* peb = get_peb ( );
    auto* entry = reinterpret_cast< const internal::ldr_data_table_entry_t* >( peb->ldr->in_load_order_module_list.flink );
    auto* head = entry;

    while ( entry->dll_base )
    {
      if ( wcscmp ( entry->base_dll_name.buffer, module_name ) == 0 )
        return ( entry->dll_base );

      entry = entry->load_order_next ( );
      if ( entry == head )
        break;
    }
    return nullptr;
  }

  template <typename T, typename A>
  T read ( A address )
  {
#ifndef UWP_TEST_BUILD
    static_assert( false, "Are you sure your game doesn't require a read stub? If so, replace the code below, otherwise comment this out." );
#endif
    // in case you need to use a stub to read, replace here
    T temp;
    memcpy ( &temp, (void*)address, sizeof(T) );
    return temp;
  }
};