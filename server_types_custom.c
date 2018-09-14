/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include <signal.h>
#include "open62541.h"
#include "custom_datatype.h"

UA_Boolean running = true;

static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

static void
addiValueFlagsPairDataType(UA_Server *server) {
    UA_VariableTypeAttributes dattr = UA_VariableTypeAttributes_default;
    dattr.description = UA_LOCALIZEDTEXT("en-US", "DiValueFlagsPair");
    dattr.displayName = UA_LOCALIZEDTEXT("en-US", "DiValueFlagsPair");
    dattr.dataType = DiValueFlagsPairType.typeId;
    dattr.valueRank = -1;

    DiValueFlagsPair p;
    p.value = 2;
    p.flags = 8;
    UA_Variant_setScalar(&dattr.value, &p, &DiValueFlagsPairType);

    UA_Server_addVariableTypeNode(server, DiValueFlagsPairType.typeId,
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                  UA_QUALIFIEDNAME(1, "DiValueFlagsPair"),
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                  dattr, NULL, NULL);

}

static void
addDiValueFlagsPairVariable(UA_Server *server) {
    DiValueFlagsPair p;
    p.value = 2;
    p.flags = 8;
    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.description = UA_LOCALIZEDTEXT("en-US", "DiValueFlagsPair");
    vattr.displayName = UA_LOCALIZEDTEXT("en-US", "DiValueFlagsPair");
    vattr.dataType = DiValueFlagsPairType.typeId;
    vattr.valueRank = -1;
    UA_Variant_setScalar(&vattr.value, &p, &DiValueFlagsPairType);

    UA_Server_addVariableNode(server, UA_NODEID_STRING(1, "DiValueFlagsPair"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                              UA_QUALIFIEDNAME(1, "DiValueFlagsPair"),
                              DiValueFlagsPairType.typeId, vattr, NULL, NULL);
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    /* Make your custom datatype known to the stack */
    UA_DataType types[1];
    types[0] = DiValueFlagsPairType;
    config->customDataTypes = types;
    config->customDataTypesSize = 1;

    UA_Server *server = UA_Server_new(config);

    addiValueFlagsPairDataType(server);
    addDiValueFlagsPairVariable(server);

    UA_Server_run(server, &running);

    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return 0;
}
