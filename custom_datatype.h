typedef struct {
    UA_Byte     value;
    UA_UInt32   flags;
} DiValueFlagsPair;

#define DiValueFlagsPair_padding_value offsetof(DiValueFlagsPair,flags) - offsetof(DiValueFlagsPair,value) - sizeof(UA_Byte)

static UA_DataTypeMember DiValueFlagsPair_members[2] = {
        /* Value */
        {
                UA_TYPENAME("Value") /* .memberName */
                UA_TYPES_BYTE,   /* .memberTypeIndex, points into UA_TYPES since namespaceZero is true */
                0,               /* .padding */
                true,            /* .namespaceZero, see .memberTypeIndex */
                false            /* .isArray */
        },

        /* Flags */
        {
                UA_TYPENAME("Flags")
                UA_TYPES_UINT32, DiValueFlagsPair_padding_value, true, false
        }
};

static const UA_DataType DiValueFlagsPairType = {
        UA_TYPENAME("DiValueFlagsPair")             /* .typeName */
        {1, UA_NODEIDTYPE_NUMERIC, {4242}}, /* .typeId */
        sizeof(DiValueFlagsPair),                   /* .memSize */
        0,                               /* .typeIndex, in the array of custom types */
        2,                               /* .membersSize */
        false,                           /* .builtin */
        true,                            /* .pointerFree */
        false,                           /* .overlayable (depends on endianness and
                                         the absence of padding) */
        0,                               /* .binaryEncodingId, the numeric
                                         identifier used on the wire (the
                                         namespaceindex is from .typeId) */
        DiValueFlagsPair_members
};