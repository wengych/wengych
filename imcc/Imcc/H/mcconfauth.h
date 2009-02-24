/*
 * The CenWave Multimedia Conference Authentication Interface Define
 * 
 * Copyright (C) 2004 by CenWave Communications Inc. All rights reserved
 * 
 */ 

/*
 * $Log: confauth.h,v $
 * Create 1.01  2004/04/16 jack feng
 *
 */

/*
 * General authentication procedures:
 * 1. user(client) login to a web site, request to create or join a conference
 *    in a secure mean (e.g https)
 * 2. the web site need authenticate this request, generate a secure ticket
 *    which itself can be verified to be authentic
 * 3. web site pass the authentication ticket back to the client in a secure way
 *     (e.g https)
 * 4. client will submit this authenticaiton ticket to the IMCC server alone 
 *    with the create/join conference request
 * 5. IMCC server will validate this ticket by decrypting the ticket using the 
 *    public key of the ticket issuer. If IMCC server doesn't have the public key, 
 *	  it can query the public key directly from the issuer web site.
 */

/*
 * Recommendation for the authentication ticket format:
 *
 * a. PKCS SignedData is recommended as the token format.
 *    CenWave will use RSA with MD5 as our asymmetric key algorithm to create 
 *    secure ticket
 * b. ticket is recommended to be base64 encoded in the communication method
 * c. XML is recommended as the format for the ticket content
 * d. recommendation for the ticket content:
 *		<? xml version="1.0"? >
 *		<!DOCTYPE AuthTicket[
 *		<!ELEMENT AuthTicket (Subject, Issuer, AuthMethod, TimeStamp, Timeout)>
 *		<!ATTLIST AuthTicket TicketId ID #REQUIRED
 *			Random CDATA #REQUIRED>
 *		<!ELEMENT Subject (UserId, UserType, UsreName, Action, ActonInfo)>
 *		<!ELEMENT UserId (#PCDATA)>
 *		<!ELEMENT UserType (#PCDATA)>
 *		<!ELEMENT UsreName (#PCDATA)>
 *		<!ELEMENT Action (#PCDATA)>
 *		<!ELEMENT ActionInfo (#PCDATA)>
 *		<!ELEMENT Issuer (#PCDATA)>
 *		<!ELEMENT AuthMethod (#PCDATA)>
 *		<!ELEMENT TimeStamp(#PCDATA)>
 *		<!ELEMENT TimeOut(#PCDATA)>
 *		]>
 *		
 *		<AuthTicket TicketId="4512323" Random="qe723we5">
 *		<Subject>
 *		<UserID>"32135"</UserID>
 *		<UserType>"host"</UserType>
 *		<UserName>"jack geng"</UserID>
 *		<Action>"create_conf"</Action>
 *		<ActionInfo>"213412"</ActionInfo> <!-- content of actioninfo depends on 
 *				the action. for create/join-conference, it is the confrence id-->
 *		</Subject>
 *		<Issuer>"auth.cenwave.com"</Issuer>
 *		<AuthMethod>"password"</AuthMethod>
 *		<TimeStamp>"2004-04-16T008:00:00Z"</TimeStamp>
 *		<TimeOut>"2004-04-16T008:10:00Z"</TimeOut>
 *		</AuthTicket>
 */

/*
 * HTTPS interface for public key query
 *
 *		<site_url>?sc=qapk&svr_ip=<svr_ip>
 *
 *		"sc": switch code
 *		"atv": query_authentication_public_key
 *
 * return content format:
 * 
 *		<? xml version="1.0"? >
 *		<!DOCTYPE qapk_rsp[
 *		<!ELEMENT qapk_rsp (Result, PublicKey))>
 *		<!ELEMENT Result (#PCDATA)>
 *		<!ELEMENT PublicKey (Key, NotBefore, NotAfter)>
 *		<!ELEMENT NotBefore (#PCDATA)>
 *		<!ELEMENT NotAfter (#PCDATA)>
 *		]>
 * 
 *		<qapk_rsp>
 *		<result>0<result>	<!--0: success. other: error code-->
 *		<PublicKey>
 *			<Key>"asfdsf3r4wqersfd32"</Key>
 *			<NotBefore>"2004-04-16T008:00:00Z"</NotBefore>
 *			<NotAfter>"2004-05-16T008:00:00Z"</NotAfter>
 *		</PublicKey>
 *		</qapk_rsp>
 */

/*
 * Conference routing and licensing
 * 1. After validate the ticket, if server check out it is a new conference 
 *    in the local server, it will query the conference routing info and 
 *    necessary licensing info from the issuer web site via https
 * 2. When issuer web server receive this request, if this is a new conference,
 *    it will make necessary check, log the requester as top server of this conference,
 *    and return with the necessary conference and lincesning infomation.
 *    if this is a existing conference, it will simply return the cinference info
 * 
 * HTTPS interface:
 *
 *		<site_url>?sc=qcrl&rid=<request_id>&svr_ip=<svr_ip>&cid=<conf_id>
 *
 *		"sc": switch code
 *		"qcrl": query_conference_routing_and_licensing_info
 *
 * Return content:
 *
 * 
 *		<? xml version="1.0"? >
 *		<!DOCTYPE qcrl_rsp[
 *		<!ELEMENT qcrl_rsp (Result, ConfInfo?, License?))>
 *		<!ATTLIST qcrl_rsp RequestID ID #REQUIRED 
 *			ConfID ID #REQUIRED >
 *		<!ELEMENT Result (#PCDATA)>
 *		<!ELEMENT ConfInfo (TopSvr, ConfKey, HostKey?)>
 *		<!ELEMENT TopSvr (#PCDATA)>
 *		<!ELEMENT ConfKey (#PCDATA)>
 *		<!ELEMENT HostKey (#PCDATA)>
 *		<!ELEMENT License (MaxConfNumUser, MaxConfDuration, Session*)>
 *		<!ELEMENT MaxConfNumUser (#PCDATA)>
 *		<!ELEMENT MaxConfDuration (#PCDATA)>
 *		<!ELEMENT Session (Allow, MaxSessNumUser?, MaxSessDuration?, SessInfo?)>
 *		<!ATTLIST Session SessType ID #REQUIRED>
 *		<!ELEMENT Allow (#PCDATA)>
 *		<!ELEMENT MaxSessNumUser (#PCDATA)>
 *		<!ELEMENT MaxSessDuration (#PCDATA)>
 *		<!ELEMENT SessInfo (#PCDATA)>
 *		]>
 *
 *		<qcrl_rsp RequestID="3242" ConfID="213412">
 *		<result>0<result>	<!--0: success. other: error code-->
 *		<ConfInfo>
 *			<TopSvr>"192.168.0.112"</TopSvr>
 *			<ConfKey>"2qwer23d2"</ConfKey>
 *			<HostKey>"iamhost"</HostKey>	<!-- only for the new conference-->
 *		</ConfInfo>
 *		<License>
 *			<MaxConfNumUser>999</MaxConfNumUser>
 *			<MaxConfDuration>999</MaxConfDuration> <!-- in minutes-->
 *			<Session SessType="audio">
 *				<Allow>"yes"</Allow>
 *				<MaxSessNumUser>999</MaxSessNumUser>
 *				<MaxSessDuration>999</MaxSessDuration> <!-- in minutes-->
 *			</Session>
 *			<Session SessType="video">
 *				<Allow>"no"</Allow>
 *			</Session>
 *		</License>
 *		</qcrl_rsp>
 */

/* 
 * HTTPS interface for the conference status report
 *
 *    <site_url>?sc=cscn&rid=<request_id>&cid=<conf_id>&status=<status>&svr_ip=<svr_ip>
 * 
 *		"sc": switch code
 *		"cscn": conference_status_change_notfication
 *		
 *		conference status:
 *			0: closed
 *			1: open_pending
 *			2: open
 *			3: locked
 *	
 *	Return content:
 *		<? xml version="1.0"? >
 *		<!DOCTYPE cscn_rsp[
 *		<!ELEMENT cscn_rsp (conf_id, status, svr_ip, result))>
 *		<!ATTLIST cscn_rsp RequestID ID #REQUIRED 
 *			ConfID ID #REQUIRED >
 *		<!ELEMENT status (#PCDATA)>
 *		<!ELEMENT result (#PCDATA)>
 *		<!ELEMENT top_svr_ip (#PCDATA)>
 *		]>
 *
 *		<cscn_rsp>
 *			<rid>3242</rid>
 *			<cid>213412</cid>
 *			<result>0</result> <!-- 0: ok -->
 *			<status>2</status>
 *			<top_svr_ip>top_svr_ip</top_svr_ip>
 *			<hk>host_key</hk>
 *		</cscn_rsp>
 *	
 *	Notes:
 *	1. If status is 2(open), the reporting server needs be logged as the top server.
 *	
*/

/* 
 * Temporary http interface for the conference status query
 *
 *		<site_url>?sc=qcs&rid=<request_id>&svr_ip=<svr_ip>&cid=<conf_id>&act=create
 *
 *		"sc": switch code
 *		"qcs": query_conference_status
 *
 * Return content:
 *
 *	<qcs_rsp>
 *		<rid>request_id</rid>
 *		<cid>conf_id</cid>
 *		<status>conf_status</status>
 *		<top_svr_ip>top_svr_ip</top_svr_ip>
 *	</qcs_rsp>
 */

/* 
 * Ping interface
 *
 *		http://imcc_server_ip/ping?sc=join_mtg&rid=<request_id>
 *			&sid=<site_id>&cid=<conf_id>&uid=<user_id>
 *
 * Return content:
 *
 *	<ping>
 *		<rid>request_id</rid>
 *		<sid>site_id</sid>
 *		<cid>conf_id</cid>
 *		<uid>user_id</uid>
 *		<result>result</result> //<!-- 0: ok -->
 *	</ping>
 */
