/**
* vim: set ts=4 :
* =============================================================================
* SourceMod SourceTV Manager Extension
* Copyright (C) 2004-2016 AlliedModders LLC.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, AlliedModders LLC gives you permission to link the
* code of this program (as well as its derivative works) to "Half-Life 2," the
* "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, AlliedModders LLC grants
* this exception to all derivative works.  AlliedModders LLC defines further
* exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
* or <http://www.sourcemod.net/license.php>.
*
* Version: $Id$
*/

#include "extension.h"
#include "commonhooks.h"
#include "forwards.h"
#include "hltvserverwrapper.h"

CCommonHooks g_pSTVCommonHooks;

// Declare the hook here so we can use it in hltvserverwrapper to fix crashes with the "status" command and host_client.
// And use it in forwards to hook spectator chat messages.
SH_DECL_HOOK1(IClient, ExecuteStringCommand, SH_NOATTRIB, 0, bool, const char *);

void CCommonHooks::AddSpectatorHook(CForwardManager *fwdmgr, IClient *client)
{
	SH_ADD_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(fwdmgr, &CForwardManager::OnSpectatorExecuteStringCommand), false);
}

void CCommonHooks::RemoveSpectatorHook(CForwardManager *fwdmgr, IClient *client)
{
	SH_REMOVE_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(fwdmgr, &CForwardManager::OnSpectatorExecuteStringCommand), false);
}

void CCommonHooks::AddHLTVClientHook(HLTVServerWrapper *wrapper, IClient *client)
{
	SH_ADD_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(wrapper, &HLTVServerWrapper::OnHLTVBotExecuteStringCommand), false);
	SH_ADD_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(wrapper, &HLTVServerWrapper::OnHLTVBotExecuteStringCommand_Post), true);
}

void CCommonHooks::RemoveHLTVClientHook(HLTVServerWrapper *wrapper, IClient *client)
{
	SH_REMOVE_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(wrapper, &HLTVServerWrapper::OnHLTVBotExecuteStringCommand), false);
	SH_REMOVE_HOOK(IClient, ExecuteStringCommand, client, SH_MEMBER(wrapper, &HLTVServerWrapper::OnHLTVBotExecuteStringCommand_Post), true);
}