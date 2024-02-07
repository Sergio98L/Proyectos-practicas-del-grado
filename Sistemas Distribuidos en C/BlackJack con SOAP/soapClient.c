/* soapClient.c
   Generated by gSOAP 2.8.75 for blackJack.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"
#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) soapClient.c ver 2.8.75 2023-11-16 14:56:32 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_blackJackns__register(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName, int *result)
{	if (soap_send_blackJackns__register(soap, soap_endpoint, soap_action, playerName) || soap_recv_blackJackns__register(soap, result))
		return soap->error;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send_blackJackns__register(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName)
{	struct blackJackns__register soap_tmp_blackJackns__register;
	if (soap_endpoint == NULL)
		soap_endpoint = "http//localhost:10000";
	soap_tmp_blackJackns__register.playerName = playerName;
	soap_begin(soap);
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__register(soap, &soap_tmp_blackJackns__register);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__register(soap, &soap_tmp_blackJackns__register, "blackJackns:register", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__register(soap, &soap_tmp_blackJackns__register, "blackJackns:register", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv_blackJackns__register(struct soap *soap, int *result)
{
	struct blackJackns__registerResponse *soap_tmp_blackJackns__registerResponse;
	if (!result)
		return soap_closesock(soap);
	soap_default_int(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_blackJackns__registerResponse = soap_get_blackJackns__registerResponse(soap, NULL, "", NULL);
	if (!soap_tmp_blackJackns__registerResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_blackJackns__registerResponse->result)
		*result = *soap_tmp_blackJackns__registerResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_blackJackns__getStatus(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName, int idPartida, struct tBlock *gameStatus)
{	if (soap_send_blackJackns__getStatus(soap, soap_endpoint, soap_action, playerName, idPartida) || soap_recv_blackJackns__getStatus(soap, gameStatus))
		return soap->error;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send_blackJackns__getStatus(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName, int idPartida)
{	struct blackJackns__getStatus soap_tmp_blackJackns__getStatus;
	if (soap_endpoint == NULL)
		soap_endpoint = "http//localhost:10000";
	soap_tmp_blackJackns__getStatus.playerName = playerName;
	soap_tmp_blackJackns__getStatus.idPartida = idPartida;
	soap_begin(soap);
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__getStatus(soap, &soap_tmp_blackJackns__getStatus);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__getStatus(soap, &soap_tmp_blackJackns__getStatus, "blackJackns:getStatus", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__getStatus(soap, &soap_tmp_blackJackns__getStatus, "blackJackns:getStatus", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv_blackJackns__getStatus(struct soap *soap, struct tBlock *gameStatus)
{
	struct blackJackns__getStatusResponse *soap_tmp_blackJackns__getStatusResponse;
	if (!gameStatus)
		return soap_closesock(soap);
	soap_default_blackJackns__tBlock(soap, gameStatus);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_blackJackns__getStatusResponse = soap_get_blackJackns__getStatusResponse(soap, NULL, "", NULL);
	if (!soap_tmp_blackJackns__getStatusResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (gameStatus && soap_tmp_blackJackns__getStatusResponse->gameStatus)
		*gameStatus = *soap_tmp_blackJackns__getStatusResponse->gameStatus;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_blackJackns__playerMove(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName, int playerMove, int idPartida, struct tBlock *gameStatus)
{	if (soap_send_blackJackns__playerMove(soap, soap_endpoint, soap_action, playerName, playerMove, idPartida) || soap_recv_blackJackns__playerMove(soap, gameStatus))
		return soap->error;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_send_blackJackns__playerMove(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct tMessage playerName, int playerMove, int idPartida)
{	struct blackJackns__playerMove soap_tmp_blackJackns__playerMove;
	if (soap_endpoint == NULL)
		soap_endpoint = "http//localhost:10000";
	soap_tmp_blackJackns__playerMove.playerName = playerName;
	soap_tmp_blackJackns__playerMove.playerMove = playerMove;
	soap_tmp_blackJackns__playerMove.idPartida = idPartida;
	soap_begin(soap);
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__playerMove(soap, &soap_tmp_blackJackns__playerMove);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__playerMove(soap, &soap_tmp_blackJackns__playerMove, "blackJackns:playerMove", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__playerMove(soap, &soap_tmp_blackJackns__playerMove, "blackJackns:playerMove", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_recv_blackJackns__playerMove(struct soap *soap, struct tBlock *gameStatus)
{
	struct blackJackns__playerMoveResponse *soap_tmp_blackJackns__playerMoveResponse;
	if (!gameStatus)
		return soap_closesock(soap);
	soap_default_blackJackns__tBlock(soap, gameStatus);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_blackJackns__playerMoveResponse = soap_get_blackJackns__playerMoveResponse(soap, NULL, "", NULL);
	if (!soap_tmp_blackJackns__playerMoveResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (gameStatus && soap_tmp_blackJackns__playerMoveResponse->gameStatus)
		*gameStatus = *soap_tmp_blackJackns__playerMoveResponse->gameStatus;
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.c */