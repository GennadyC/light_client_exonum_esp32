/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 at Fri Feb 22 19:16:02 2019. */

#include "short_device_key.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif
#define PB_FIELD_16BIT 256



const pb_field_t BlockchainCore_PublicKey_fields[2] = {
    PB_FIELD(  1, FIXED_LENGTH_BYTES, SINGULAR, STATIC  , FIRST, BlockchainCore_PublicKey, mm, mm, 0),
    PB_LAST_FIELD
};

const pb_field_t BlockchainCore_ShortDeviceKey_fields[7] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, BlockchainCore_ShortDeviceKey, device_key_id, device_key_id, &BlockchainCore_PublicKey_fields),
    PB_FIELD(  2, FIXED_LENGTH_BYTES, SINGULAR, STATIC  , OTHER, BlockchainCore_ShortDeviceKey, authentication_key, device_key_id, 0),
    PB_FIELD(  3, FIXED_LENGTH_BYTES, SINGULAR, STATIC  , OTHER, BlockchainCore_ShortDeviceKey, biometrical_key, authentication_key, 0),
    PB_FIELD(  4, INT32   , SINGULAR, STATIC  , OTHER, BlockchainCore_ShortDeviceKey, wearout, biometrical_key, 0),
    PB_FIELD(  5, STRING  , SINGULAR, STATIC  , OTHER, BlockchainCore_ShortDeviceKey, application_data, wearout, 0),
    PB_FIELD(  6, STRING  , SINGULAR, STATIC  , OTHER, BlockchainCore_ShortDeviceKey, shedule, application_data, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(BlockchainCore_ShortDeviceKey, device_key_id) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_BlockchainCore_PublicKey_BlockchainCore_ShortDeviceKey)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(BlockchainCore_ShortDeviceKey, device_key_id) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_BlockchainCore_PublicKey_BlockchainCore_ShortDeviceKey)
#endif


/* @@protoc_insertion_point(eof) */
