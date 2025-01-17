/*
* Copyright (C) 2014 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef RIL_UIM_SOCKET_H_INCLUDED
#define RIL_UIM_SOCKET_H_INCLUDED
#define RIL_SHLIB
//#include "telephony/ril.h"
#include <telephony/mtk_ril.h>
#include "RilSocket.h"
#include <hardware/ril/librilutils/proto/sap-api.pb.h>

/**
 * RilSapSocket is a derived class, derived from the RilSocket abstract
 * class, representing sockets for communication between bluetooth SAP module and
 * the ril daemon.
 * <p>
 * This class performs the following functions :
 * <ul>
 *     <li>Initialize the socket.
 *     <li>Process the requests coming on the socket.
 *     <li>Provide handlers for Unsolicited and request responses.
 *     <li>Request and pending response queue handling.
 * </ul>
 */
class RilSapSocket : public RilSocket {
    /**
     * Function pointer to the ril initialization funtion.
     *
     * @param Ril environment variable with place request and
     *        response handlers and timeout handler.
     *
     * @param Number of arguements for the initialization function.
     *
     * @param Arguements to the initialization function used to
     *        generate instance id of the ril daemon.
     *
     * @return Radio functions with handlers for onRequest, onStateRequest,
     *         supports, onCancel and getVersion.
     */
    RIL_RadioFunctionsSocket *(*UimInit)(const struct RIL_EnvSocket *, int argc, char **argv);

    /**
     * Place holder for the radio functions returned by the initialization
     * function. Currenty only onRequest handler is being used.
     */
    RIL_RadioFunctionsSocket* uimFuncs;

    /**
     * Wrapper struct for handling the requests in the queue.
     */
    typedef struct SapSocketRequest {
        int token;
        MsgHeader* curr;
        struct SapSocketRequest* p_next;
        RIL_SOCKET_ID socketId;
    } SapSocketRequest;

    /**
     * Queue for requests that are pending dispatch.
     */
    Ril_queue<SapSocketRequest> dispatchQueue;

    /**
     * Queue for requests that are dispatched but are pending response
     */
    Ril_queue<SapSocketRequest> pendingResponseQueue;

    public:
        /**
         * Initialize the socket and add the socket to the list.
         *
         * @param Name of the socket.
         * @param Radio functions to be used by the socket.
         */
        static void initSapSocket(const char *socketName,
        RIL_RadioFunctionsSocket *uimFuncs);

        /**
         * Process requests from the dispatch request queue.
         * @param Request to be dispatched.
         */
        int processRequest(MsgHeader *request);

        /**
         * Ril envoronment variable that holds the request and
         * unsol response handlers.
         */
        static struct RIL_EnvSocket uimRilEnv;

        /**
         * Function to print the socket list.
         */
        static void printList();

        /**
         * Clean up method to be called on command close.
         */
        void onCommandsSocketClosed(void);

        /**
         * Datatype to handle the socket list.
         */
        typedef struct RilSapSocketList {
            RilSapSocket* socket;
            RilSapSocketList *next;
        } RilSapSocketList;

    protected:
        /**
         * Process each record read from the socket and
         * push a new request created from that record to
         * the dispatch request queue.
         *
         * @param The record data.
         * @param The record length.
         */
        void pushRecord(void *record, size_t recordlen);

        /**
         * Socket handler to be called when a request has
         * been completed.
         *
         * @param Token associated with the request.
         * @param Error, if any, while processing the request.
         * @param The response payload.
         * @param Response payload length.
         */
        void onRequestComplete(RIL_Token t,RIL_Errno e,
        void *response, size_t response_len);

        /**
         * Socket handler to be called when there is an
         * unsolicited response.
         *
         * @param Message id.
         * @param Response data.
         * @param Response data length.
         */
        void onUnsolicitedResponse(int unsolResponse,
        void *data, size_t datalen);

        /**
         * Class method to get the socket from the socket list.
         *
         * @param Socket id.
         * @return the sap socket.
         */
        static RilSapSocket* getSocketById(RIL_SOCKET_ID socketId);

        /**
         * Method to send response to SAP. It does an atomic write operation on the
         * socket.
         *
         * @param the response header with the payload.
         */
        void sendResponse(MsgHeader *hdr);

        /**
         * A loop for processing the requests in the request dispatch queue.
         */
        void *processRequestsLoop(void);

        /**
         * Class method to add the sap socket to the list of sockets.
         * Does nothing if the socket is already present in the list.
         * Otherwise, calls the constructor of the parent class(To startlistening)
         * and add socket to the socket list.
         */
        static void addSocketToList(const char *socketName, RIL_SOCKET_ID socketid,
        RIL_RadioFunctionsSocket *uimFuncs);

        /**
         * Check if a socket of the given name exists in the socket list.
         *
         * @param Socket name.
         * @return true if exists, false otherwise.
         */
        static bool SocketExists(const char *socketName);

        /**
         * Send a clean up SAP DISCONNECT if the socket disconnects before doing a SAP
         * disconnect.
         */
        void sendDisconnect(void);

        /**
         * Dispatch the clean up disconnect request.
         */
        void dispatchDisconnect(MsgHeader *req);


    private:
        /**
         * Constructor.
         *
         * @param Socket name.
         * @param Socket id.
         * @param Radio functions.
         */
        RilSapSocket(const char *socketName,
        RIL_SOCKET_ID socketId,
        RIL_RadioFunctionsSocket *inputUimFuncs);

        /**
         * Called by the processRequest method to dispatch the request to
         * the lower layers. It calls the on request function.
         *
         * @param The request message.
         */
        void dispatchRequest(MsgHeader *request);

        /**
         * Class method that selects the socket on which the onRequestComplete
         * is called.
         *
         * @param Token associated with the request.
         * @param Error, if any, while processing the request.
         * @param The response payload.
         * @param Response payload length.
         */
        static void sOnRequestComplete(RIL_Token t,
        RIL_Errno e, void *response, size_t responselen);

#if defined(ANDROID_MULTI_SIM)
        /**
         * Class method that selects the socket on which the onUnsolicitedResponse
         * is called.
         *
         * @param Message id.
         * @param Response data.
         * @param Response data length.
         * @param Socket id.
         */
        static void sOnUnsolicitedResponse(int unsolResponse, const void *data,
        size_t datalen, RIL_SOCKET_ID socket_id);
#else
        /**
         * Class method that selects the socket on which the onUnsolicitedResponse
         * is called.
         *
         * @param Message id.
         * @param Response data.
         * @param Response data length.
         */
        static void sOnUnsolicitedResponse(int unsolResponse, const void *data,
        size_t datalen);
#endif

    static bool isCdmaLteDcSupport();
};

#endif /*RIL_UIM_SOCKET_H_INCLUDED*/
