/* soapServer.c
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

SOAP_SOURCE_STAMP("@(#) soapServer.c ver 2.8.75 2023-11-16 14:56:32 GMT")
SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	soap->keep_alive = soap->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->keep_alive > 0 && soap->max_keep_alive > 0)
			soap->keep_alive--;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if ((soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap))) && soap->error && soap->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "blackJackns:register"))
		return soap_serve_blackJackns__register(soap);
	if (!soap_match_tag(soap, soap->tag, "blackJackns:getStatus"))
		return soap_serve_blackJackns__getStatus(soap);
	if (!soap_match_tag(soap, soap->tag, "blackJackns:playerMove"))
		return soap_serve_blackJackns__playerMove(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_blackJackns__register(struct soap *soap)
{	struct blackJackns__register soap_tmp_blackJackns__register;
	struct blackJackns__registerResponse soap_tmp_blackJackns__registerResponse;
	int soap_tmp_int;
	soap_default_blackJackns__registerResponse(soap, &soap_tmp_blackJackns__registerResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_blackJackns__registerResponse.result = &soap_tmp_int;
	soap_default_blackJackns__register(soap, &soap_tmp_blackJackns__register);
	if (!soap_get_blackJackns__register(soap, &soap_tmp_blackJackns__register, "blackJackns:register", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = blackJackns__register(soap, soap_tmp_blackJackns__register.playerName, soap_tmp_blackJackns__registerResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__registerResponse(soap, &soap_tmp_blackJackns__registerResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__registerResponse(soap, &soap_tmp_blackJackns__registerResponse, "blackJackns:registerResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__registerResponse(soap, &soap_tmp_blackJackns__registerResponse, "blackJackns:registerResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_blackJackns__getStatus(struct soap *soap)
{	struct blackJackns__getStatus soap_tmp_blackJackns__getStatus;
	struct blackJackns__getStatusResponse soap_tmp_blackJackns__getStatusResponse;
	struct tBlock soap_tmp_blackJackns__tBlock;
	soap_default_blackJackns__getStatusResponse(soap, &soap_tmp_blackJackns__getStatusResponse);
	soap_default_blackJackns__tBlock(soap, &soap_tmp_blackJackns__tBlock);
	soap_tmp_blackJackns__getStatusResponse.gameStatus = &soap_tmp_blackJackns__tBlock;
	soap_default_blackJackns__getStatus(soap, &soap_tmp_blackJackns__getStatus);
	if (!soap_get_blackJackns__getStatus(soap, &soap_tmp_blackJackns__getStatus, "blackJackns:getStatus", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = blackJackns__getStatus(soap, soap_tmp_blackJackns__getStatus.playerName, soap_tmp_blackJackns__getStatus.idPartida, soap_tmp_blackJackns__getStatusResponse.gameStatus);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__getStatusResponse(soap, &soap_tmp_blackJackns__getStatusResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__getStatusResponse(soap, &soap_tmp_blackJackns__getStatusResponse, "blackJackns:getStatusResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__getStatusResponse(soap, &soap_tmp_blackJackns__getStatusResponse, "blackJackns:getStatusResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_blackJackns__playerMove(struct soap *soap)
{	struct blackJackns__playerMove soap_tmp_blackJackns__playerMove;
	struct blackJackns__playerMoveResponse soap_tmp_blackJackns__playerMoveResponse;
	struct tBlock soap_tmp_blackJackns__tBlock;
	soap_default_blackJackns__playerMoveResponse(soap, &soap_tmp_blackJackns__playerMoveResponse);
	soap_default_blackJackns__tBlock(soap, &soap_tmp_blackJackns__tBlock);
	soap_tmp_blackJackns__playerMoveResponse.gameStatus = &soap_tmp_blackJackns__tBlock;
	soap_default_blackJackns__playerMove(soap, &soap_tmp_blackJackns__playerMove);
	if (!soap_get_blackJackns__playerMove(soap, &soap_tmp_blackJackns__playerMove, "blackJackns:playerMove", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = blackJackns__playerMove(soap, soap_tmp_blackJackns__playerMove.playerName, soap_tmp_blackJackns__playerMove.playerMove, soap_tmp_blackJackns__playerMove.idPartida, soap_tmp_blackJackns__playerMoveResponse.gameStatus);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_blackJackns__playerMoveResponse(soap, &soap_tmp_blackJackns__playerMoveResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_blackJackns__playerMoveResponse(soap, &soap_tmp_blackJackns__playerMoveResponse, "blackJackns:playerMoveResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_blackJackns__playerMoveResponse(soap, &soap_tmp_blackJackns__playerMoveResponse, "blackJackns:playerMoveResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.c */