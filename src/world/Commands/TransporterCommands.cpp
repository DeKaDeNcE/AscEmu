/*
Copyright (c) 2015 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#include "StdAfx.h"
#include <Exceptions/Exceptions.hpp>

bool ChatHandler::HandleGetTransporterTime(const char* /*args*/, WorldSession* m_session)
{
    auto transporter = objmgr.GetTransporter(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
    if (transporter == nullptr)
    {
        RedSystemMessage(m_session, "You must be on a transport to use this command.");
        return true;
    }

    SystemMessage(m_session, "Current period: %dms", transporter->GetPeriod());
    return true;
}

bool ChatHandler::HandleGetTransporterInfo(const char* /*args*/, WorldSession* m_session)
{
    auto transporter = objmgr.GetTransporter(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
    if (transporter == nullptr)
    {
        RedSystemMessage(m_session, "You must be on a transport to use this command.");
        return true;
    }

    auto gameobject_info = GameObjectNameStorage.LookupEntry(transporter->GetEntry());
    if (gameobject_info != nullptr)
    {
        SystemMessage(m_session, "Entry: %u", gameobject_info->entry);
        SystemMessage(m_session, "Name: %s", gameobject_info->name);
        SystemMessage(m_session, "Path: %u", gameobject_info->mo_transport.taxi_path_id);
        SystemMessage(m_session, "Time on Path: %u", transporter->m_timer);
        SystemMessage(m_session, "Period: %u", transporter->GetPeriod());
        //SystemMessage(m_session, "Current WP: %u", transporter->mCurrentWaypoint->first);
    }
    
    return true;
}

bool ChatHandler::HandleModPeriodCommand(const char* args, WorldSession* m_session)
{
    try
    {
        int32 time = args ? atol(args) : 0;
        if (time == 0)
            return false;

        Transporter* transport = objmgr.GetTransportOrThrow(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
        transport->SetPeriod(time);
        BlueSystemMessage(m_session, "Period of %s set to %u.", transport->GetInfo()->name, time);
    }
    catch (AscEmu::Exception::AscemuException e)
    {
        RedSystemMessage(m_session, e.what());
    }

    return true;
}

bool ChatHandler::HandleStopTransport(const char* /*args*/, WorldSession* m_session)
{
    try
    {
        Transporter* transport = objmgr.GetTransportOrThrow(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
        if (transport->GetState() == GO_STATE_OPEN)
        {
            transport->m_WayPoints.clear();
            transport->RemoveFlag(GAMEOBJECT_FLAGS, 1);
            transport->SetState(GO_STATE_CLOSED);
        }
    }
    catch (AscEmu::Exception::AscemuException e)
    {
        RedSystemMessage(m_session, e.what());
    }

    return true;
}

bool ChatHandler::HandleStartTransport(const char* /*args*/, WorldSession* m_session)
{
    try
    {
        Transporter* transport = objmgr.GetTransportOrThrow(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
        if (transport->GetState() == GO_STATE_CLOSED)
        {
            transport->SetFlag(GAMEOBJECT_FLAGS, 1);
            transport->SetState(GO_STATE_OPEN);
            transport->SetUInt32Value(GAMEOBJECT_DYNAMIC, 0x10830010); // Seen in sniffs
            transport->SetFloatValue(GAMEOBJECT_PARENTROTATION + 3, 1.0f);
            std::set<uint32> mapsUsed;
            GameObjectInfo const* goinfo = transport->GetInfo();

            transport->GenerateWaypoints(goinfo->raw.parameter_0);
        }
    }
    catch (AscEmu::Exception::AscemuException e)
    {
        RedSystemMessage(m_session, e.what());
    }

    return true;
}

bool ChatHandler::HandleSpawnInstanceTransport(const char* args, WorldSession* m_session)
{
    char* pEntry = strtok(const_cast<char*>(args), " ");
    if (!pEntry)
        return false;

    char* pPeriod = strtok(nullptr, " ");
    if (!pPeriod)
        return false;

    uint32 entry = atoi(pEntry);
    uint32 period = atoi(pPeriod);

    objmgr.LoadTransportInInstance(m_session->GetPlayerOrThrow()->GetMapMgr(), entry, period);

    return true;
}

bool ChatHandler::HandleDespawnInstanceTransport(const char* /*args*/, WorldSession* m_session)
{
    try
    {
        Transporter* transport = objmgr.GetTransportOrThrow(Arcemu::Util::GUID_LOPART(m_session->GetPlayerOrThrow()->obj_movement_info.transporter_info.guid));
        objmgr.UnloadTransportFromInstance(transport);
    }
    catch (AscEmu::Exception::AscemuException e)
    {
        RedSystemMessage(m_session, e.what());
    }
    return true;
}
